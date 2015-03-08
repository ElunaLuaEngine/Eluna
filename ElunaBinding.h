/*
* Copyright (C) 2010 - 2015 Eluna Lua Engine <http://emudevs.com/>
* This program is free software licensed under GPL version 3
* Please see the included DOCS/LICENSE.md for more information
*/

#ifndef _ELUNA_BINDING_H
#define _ELUNA_BINDING_H

#include "Common.h"
#include "LuaEngine.h"
#include "ElunaUtility.h"

extern "C"
{
#include "lua.h"
#include "lauxlib.h"
};

#ifdef WIN32
// VC++ complains about UniqueBind because one of its template types is really long.
#pragma warning(disable:4503)
#endif

class ElunaBind : public ElunaUtil::RWLockable
{
public:
    struct Binding
    {
        int functionReference;
        bool isTemporary;
        uint32 remainingShots;
        int cancelCallbackRef; // Reference to a callback that will cancel this binding, or 0.
        Eluna& E;

        Binding(Eluna& _E, int funcRef, uint32 shots, int cancelCallbackRef) :
            functionReference(funcRef),
            isTemporary(shots != 0 && cancelCallbackRef == 0),
            remainingShots(shots),
            cancelCallbackRef(cancelCallbackRef),
            E(_E)
        {
        }

        ~Binding()
        {
            // Remove our function and cancel callback from the registry when the Binding is deleted.
            if (cancelCallbackRef > 0)
                luaL_unref(E.L, LUA_REGISTRYINDEX, cancelCallbackRef);

            luaL_unref(E.L, LUA_REGISTRYINDEX, functionReference);
        }
    };
    typedef std::vector<Binding*> FunctionRefVector;
    typedef UNORDERED_MAP<int, FunctionRefVector> EventToFunctionsMap;

    Eluna& E;
    const char* groupName;

    ElunaBind(const char* bindGroupName, Eluna& _E) : E(_E), groupName(bindGroupName)
    {
    }

    virtual ~ElunaBind()
    {
        Clear();
    }

    // unregisters all registered functions and clears all registered events from the bindings
    virtual void Clear() { };

    virtual void ClearOne(int ref, uint32 event_id, uint32 entry, uint64 guid) = 0;
};

template<typename T>
class EventBind : public ElunaBind
{
public:
    EventBind(const char* bindGroupName, Eluna& _E) : ElunaBind(bindGroupName, _E)
    {
    }

    // unregisters all registered functions and clears all registered events from the bind std::maps (reset)
    void Clear() override
    {
        WriteGuard guard(GetLock());

        for (EventToFunctionsMap::iterator itr = Bindings.begin(); itr != Bindings.end(); ++itr)
        {
            FunctionRefVector& funcrefvec = itr->second;
            std::vector<int> cancelRefVector;

            for (FunctionRefVector::iterator it = funcrefvec.begin(); it != funcrefvec.end(); ++it)
            {
                Binding* binding = (*it);

                // Can't call the callback now, since it might modify `v` and crash the server.
                // Just add the ref to a list and call them all after this loop.
                if (binding->cancelCallbackRef)
                    cancelRefVector.push_back(binding->cancelCallbackRef);
                else
                    delete binding; // Don't bother removing from list, clear is called at end anyway.
            }

            // Call all of the cancel callbacks for bindings with cancel callbacks.
            for (std::vector<int>::iterator i = cancelRefVector.begin(); i != cancelRefVector.end(); ++i)
            {
                lua_rawgeti(E.L, LUA_REGISTRYINDEX, (*i));
                lua_call(E.L, 0, 0);
            }

            funcrefvec.clear();
        }
        Bindings.clear();
    }

    void Clear(uint32 event_id)
    {
        WriteGuard guard(GetLock());
        FunctionRefVector& v = Bindings[event_id];
        std::vector<int> cancelRefVector;

        for (FunctionRefVector::iterator itr = v.begin(); itr != v.end(); ++itr)
        {
            Binding* binding = (*itr);

            // Can't call the callback now, since it might modify `v` and crash the server.
            // Just add the ref to a list and call them all after this loop.
            if (binding->cancelCallbackRef)
                cancelRefVector.push_back(binding->cancelCallbackRef);
            else
                delete binding; // Don't bother removing from list, clear is called at end anyway.
        }

        // Call all of the cancel callbacks for bindings with cancel callbacks.
        for (std::vector<int>::iterator i = cancelRefVector.begin(); i != cancelRefVector.end(); ++i)
        {
            lua_rawgeti(E.L, LUA_REGISTRYINDEX, (*i));
            lua_call(E.L, 0, 0);
        }

        v.clear();
    }

    void ClearOne(int ref, uint32 event_id, uint32 entry, uint64 guid) override
    {
        ASSERT(entry == 0 && guid == 0);
        WriteGuard guard(GetLock());

        FunctionRefVector& funcrefvec = Bindings[event_id];

        for (FunctionRefVector::iterator i = funcrefvec.begin(); i != funcrefvec.end(); ++i)
        {
            Binding* binding = (*i);

            if (binding->functionReference == ref)
            {
                i = funcrefvec.erase(i);
                delete binding;
                return;
            }
        }

        ASSERT(false && "tried to clear function ref that doesn't exist");
    }

    // Pushes the function references and updates the counters on the binds and erases them if the counter would reach 0
    void PushFuncRefs(lua_State* L, int event_id)
    {
        WriteGuard guard(GetLock());

        for (FunctionRefVector::iterator it = Bindings[event_id].begin(); it != Bindings[event_id].end();)
        {
            FunctionRefVector::iterator it_old = it++;
            Binding* binding = (*it_old);

            lua_rawgeti(L, LUA_REGISTRYINDEX, binding->functionReference);

            if (binding->isTemporary)
            {
                // Bad things will happen if there's a cancel callback (due to ref reuse).
                ASSERT(binding->cancelCallbackRef == 0);

                binding->remainingShots--;
                if (binding->remainingShots == 0)
                {
                    delete binding;
                    Bindings[event_id].erase(it_old);
                }
            }
        }

        if (Bindings[event_id].empty())
            Bindings.erase(event_id);
    };

    void Insert(int eventId, int funcRef, uint32 shots, int callbackRef = 0) // Inserts a new registered event
    {
        WriteGuard guard(GetLock());
        Bindings[eventId].push_back(new Binding(E, funcRef, shots, callbackRef));
    }

    // Checks if there are events for ID
    bool HasEvents(T eventId)
    {
        ReadGuard guard(GetLock());

        if (!E.IsEnabled())
            return false;

        if (Bindings.empty())
            return false;
        if (Bindings.find(eventId) == Bindings.end())
            return false;
        return true;
    }

    EventToFunctionsMap Bindings; // Binding store Bindings[eventId] = {(funcRef, counter)};
};

template<typename T>
class EntryBind : public ElunaBind
{
public:
    typedef UNORDERED_MAP<uint32, EventToFunctionsMap> EntryToEventsMap;

    EntryBind(const char* bindGroupName, Eluna& _E) : ElunaBind(bindGroupName, _E)
    {
    }

    // unregisters all registered functions and clears all registered events from the bindmap
    void Clear() override
    {
        WriteGuard guard(GetLock());

        for (EntryToEventsMap::iterator itr = Bindings.begin(); itr != Bindings.end(); ++itr)
        {
            EventToFunctionsMap& funcmap = itr->second;
            for (EventToFunctionsMap::iterator it = funcmap.begin(); it != funcmap.end(); ++it)
            {
                FunctionRefVector& funcrefvec = it->second;
                std::vector<int> cancelRefVector;

                for (FunctionRefVector::iterator i = funcrefvec.begin(); i != funcrefvec.end(); ++i)
                {
                    Binding* binding = (*i);

                    // Can't call the callback now, since it might modify `v` and crash the server.
                    // Just add the ref to a list and call them all after this loop.
                    if (binding->cancelCallbackRef)
                        cancelRefVector.push_back(binding->cancelCallbackRef);
                    else
                        delete binding; // Don't bother removing from list, clear is called at end anyway.
                }

                // Call all of the cancel callbacks for bindings with cancel callbacks.
                for (std::vector<int>::iterator i = cancelRefVector.begin(); i != cancelRefVector.end(); ++i)
                {
                    lua_rawgeti(E.L, LUA_REGISTRYINDEX, (*i));
                    lua_call(E.L, 0, 0);
                }

                funcrefvec.clear();
            }
            funcmap.clear();
        }
        Bindings.clear();
    }

    void Clear(uint32 entry, uint32 event_id)
    {
        WriteGuard guard(GetLock());
        FunctionRefVector& v = Bindings[entry][event_id];
        std::vector<int> cancelRefVector;

        for (FunctionRefVector::iterator itr = v.begin(); itr != v.end(); ++itr)
        {
            Binding* binding = (*itr);

            // Can't call the callback now, since it might modify `v` and crash the server.
            // Just add the ref to a list and call them all after this loop.
            if (binding->cancelCallbackRef)
                cancelRefVector.push_back(binding->cancelCallbackRef);
            else
                delete binding; // Don't bother removing from list, clear is called at end anyway.
        }

        // Call all of the cancel callbacks for bindings with cancel callbacks.
        for (std::vector<int>::iterator i = cancelRefVector.begin(); i != cancelRefVector.end(); ++i)
        {
            lua_rawgeti(E.L, LUA_REGISTRYINDEX, (*i));
            lua_call(E.L, 0, 0);
        }

        v.clear();
    }

    void ClearOne(int ref, uint32 event_id, uint32 entry, uint64 guid) override
    {
        ASSERT(entry != 0 && guid == 0);
        WriteGuard guard(GetLock());

        FunctionRefVector& funcrefvec = Bindings[entry][event_id];

        for (FunctionRefVector::iterator i = funcrefvec.begin(); i != funcrefvec.end(); ++i)
        {
            Binding* binding = (*i);

            if (binding->functionReference == ref)
            {
                i = funcrefvec.erase(i);
                delete binding;
                return;
            }
        }

        ASSERT(false && "tried to clear function ref that doesn't exist");
    }

    // Pushes the function references and updates the counters on the binds and erases them if the counter would reach 0
    void PushFuncRefs(lua_State* L, int event_id, uint32 entry)
    {
        WriteGuard guard(GetLock());

        for (FunctionRefVector::iterator it = Bindings[entry][event_id].begin(); it != Bindings[entry][event_id].end();)
        {
            FunctionRefVector::iterator it_old = it++;
            Binding* binding = (*it_old);

            lua_rawgeti(L, LUA_REGISTRYINDEX, binding->functionReference);

            if (binding->isTemporary)
            {
                // Bad things will happen if there's a cancel callback (due to ref reuse).
                ASSERT(binding->cancelCallbackRef == 0);

                binding->remainingShots--;
                if (binding->remainingShots == 0)
                {
                    delete binding;
                    Bindings[entry][event_id].erase(it_old);
                }
            }
        }

        if (Bindings[entry][event_id].empty())
            Bindings[entry].erase(event_id);

        if (Bindings[entry].empty())
            Bindings.erase(entry);
    };

    void Insert(uint32 entryId, int eventId, int funcRef, uint32 shots, int callbackRef = 0) // Inserts a new registered event
    {
        WriteGuard guard(GetLock());
        Bindings[entryId][eventId].push_back(new Binding(E, funcRef, shots, callbackRef));
    }

    // Returns true if the entry has registered binds
    bool HasEvents(T eventId, uint32 entryId)
    {
        ReadGuard guard(GetLock());

        if (Bindings.empty())
            return false;

        EntryToEventsMap::const_iterator itr = Bindings.find(entryId);
        if (itr == Bindings.end())
            return false;

        return itr->second.find(eventId) != itr->second.end();
    }

    bool HasEvents(uint32 entryId)
    {
        ReadGuard guard(GetLock());

        if (!E.IsEnabled())
            return false;

        if (Bindings.empty())
            return false;

        return Bindings.find(entryId) != Bindings.end();
    }

    EntryToEventsMap Bindings; // Binding store Bindings[entryId][eventId] = {(funcRef, counter)};
};

template<typename T>
class UniqueBind : public ElunaBind
{
public:
    typedef UNORDERED_MAP<uint32, EventToFunctionsMap> InstanceToEventsMap;
    typedef UNORDERED_MAP<uint64, InstanceToEventsMap> GUIDToInstancesMap;

    UniqueBind(const char* bindGroupName, Eluna& _E) : ElunaBind(bindGroupName, _E)
    {
    }

    // unregisters all registered functions and clears all registered events from the bindmap
    void Clear() override
    {
        WriteGuard guard(GetLock());

        for (GUIDToInstancesMap::iterator iter = Bindings.begin(); iter != Bindings.end(); ++iter)
        {
            InstanceToEventsMap& eventsMap = iter->second;
            for (InstanceToEventsMap::iterator itr = eventsMap.begin(); itr != eventsMap.end(); ++itr)
            {
                EventToFunctionsMap& funcmap = itr->second;
                for (EventToFunctionsMap::iterator it = funcmap.begin(); it != funcmap.end(); ++it)
                {
                    FunctionRefVector& funcrefvec = it->second;
                    std::vector<int> cancelRefVector;

                    for (FunctionRefVector::iterator i = funcrefvec.begin(); i != funcrefvec.end(); ++i)
                    {
                        Binding* binding = (*i);

                        // Can't call the callback now, since it might modify `v` and crash the server.
                        // Just add the ref to a list and call them all after this loop.
                        if (binding->cancelCallbackRef)
                            cancelRefVector.push_back(binding->cancelCallbackRef);
                        else
                            delete binding; // Don't bother removing from list, clear is called at end anyway.
                    }

                    // Call all of the cancel callbacks for bindings with cancel callbacks.
                    for (std::vector<int>::iterator i = cancelRefVector.begin(); i != cancelRefVector.end(); ++i)
                    {
                        lua_rawgeti(E.L, LUA_REGISTRYINDEX, (*i));
                        lua_call(E.L, 0, 0);
                    }
                    funcrefvec.clear();
                }
                funcmap.clear();
            }
            eventsMap.clear();
        }
        Bindings.clear();
    }

    void Clear(uint64 guid, uint32 instanceId, uint32 event_id)
    {
        WriteGuard guard(GetLock());
        FunctionRefVector& v = Bindings[guid][instanceId][event_id];
        std::vector<int> cancelRefVector;

        for (FunctionRefVector::iterator itr = v.begin(); itr != v.end(); ++itr)
        {
            Binding* binding = (*itr);

            // Can't call the callback now, since it might modify `v` and crash the server.
            // Just add the ref to a list and call them all after this loop.
            if (binding->cancelCallbackRef)
                cancelRefVector.push_back(binding->cancelCallbackRef);
            else
                delete binding; // Don't bother removing from list, clear is called at end anyway.
        }

        // Call all of the cancel callbacks for bindings with cancel callbacks.
        for (std::vector<int>::iterator i = cancelRefVector.begin(); i != cancelRefVector.end(); ++i)
        {
            lua_rawgeti(E.L, LUA_REGISTRYINDEX, (*i));
            lua_call(E.L, 0, 0);
        }

        v.clear();
    }

    void ClearOne(int ref, uint32 event_id, uint32 instance_id, uint64 guid) override
    {
        ASSERT(guid != 0);
        WriteGuard guard(GetLock());

        FunctionRefVector& funcrefvec = Bindings[guid][instance_id][event_id];

        for (FunctionRefVector::iterator i = funcrefvec.begin(); i != funcrefvec.end(); ++i)
        {
            Binding* binding = (*i);

            if (binding->functionReference == ref)
            {
                i = funcrefvec.erase(i);
                delete binding;
                return;
            }
        }

        ASSERT(false && "tried to clear function ref that doesn't exist");
    }

    // Pushes the function references and updates the counters on the binds and erases them if the counter would reach 0
    void PushFuncRefs(lua_State* L, int event_id, uint64 guid, uint32 instanceId)
    {
        WriteGuard guard(GetLock());
        FunctionRefVector& v = Bindings[guid][instanceId][event_id];

        for (FunctionRefVector::iterator it = v.begin(); it != v.end();)
        {
            FunctionRefVector::iterator it_old = it++;
            Binding* binding = (*it_old);

            lua_rawgeti(L, LUA_REGISTRYINDEX, binding->functionReference);

            if (binding->isTemporary)
            {
                // Bad things will happen if there's a cancel callback (due to ref reuse).
                ASSERT(binding->cancelCallbackRef == 0);

                binding->remainingShots--;
                if (binding->remainingShots == 0)
                {
                    delete binding;
                    v.erase(it_old);
                }
            }
        }

        if (Bindings[guid][instanceId][event_id].empty())
            Bindings[guid][instanceId].erase(event_id);

        if (Bindings[guid][instanceId].empty())
            Bindings[guid].erase(instanceId);

        if (Bindings[guid].empty())
            Bindings.erase(guid);
    };

    void Insert(uint64 guid, uint32 instanceId, int eventId, int funcRef, uint32 shots, int callbackRef = 0) // Inserts a new registered event
    {
        WriteGuard guard(GetLock());
        Bindings[guid][instanceId][eventId].push_back(new Binding(E, funcRef, shots, callbackRef));
    }

    // Returns true if the entry has registered binds
    bool HasEvents(T eventId, uint64 guid, uint32 instanceId)
    {
        ReadGuard guard(GetLock());

        if (Bindings.empty())
            return false;

        GUIDToInstancesMap::const_iterator itr = Bindings.find(guid);
        if (itr == Bindings.end())
            return false;

        InstanceToEventsMap::const_iterator it = itr->second.find(instanceId);
        if (it == itr->second.end())
            return false;

        return it->second.find(eventId) != it->second.end();
    }

    bool HasEvents(uint64 guid, uint32 instanceId)
    {
        ReadGuard guard(GetLock());

        if (Bindings.empty())
            return false;

        GUIDToInstancesMap::const_iterator itr = Bindings.find(guid);
        if (itr == Bindings.end())
            return false;

        return itr->second.find(instanceId) != itr->second.end();
    }

    GUIDToInstancesMap Bindings; // Binding store Bindings[guid][instanceId][eventId] = {(funcRef, counter)};
};

#endif
