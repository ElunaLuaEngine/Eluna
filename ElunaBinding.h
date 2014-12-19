/*
* Copyright (C) 2010 - 2014 Eluna Lua Engine <http://emudevs.com/>
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

class ElunaBind
{
public:
    struct Binding
    {
        int functionReference;
        bool isTemporary;
        uint32 remainingShots;

        Binding(int funcRef, uint32 shots) :
            functionReference(funcRef),
            isTemporary(shots != 0),
            remainingShots(shots)
        {
        }
    };
    typedef std::vector<Binding> FunctionRefVector;
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
        for (EventToFunctionsMap::iterator itr = Bindings.begin(); itr != Bindings.end(); ++itr)
        {
            for (FunctionRefVector::iterator it = itr->second.begin(); it != itr->second.end(); ++it)
                luaL_unref(E.L, LUA_REGISTRYINDEX, (*it).functionReference);
            itr->second.clear();
        }
        Bindings.clear();
    }

    // Pushes the function references and updates the counters on the binds and erases them if the counter would reach 0
    void PushFuncRefs(lua_State* L, int event_id)
    {
        for (FunctionRefVector::iterator it = Bindings[event_id].begin(); it != Bindings[event_id].end();)
        {
            FunctionRefVector::iterator it_old = it++;

            lua_rawgeti(L, LUA_REGISTRYINDEX, (it_old->functionReference));

            if (it_old->isTemporary)
            {
                --it_old->remainingShots;
                if (it_old->remainingShots == 0)
                {
                    luaL_unref(L, LUA_REGISTRYINDEX, it_old->functionReference);
                    Bindings[event_id].erase(it_old);
                }
            }
        }

        if (Bindings[event_id].empty())
            Bindings.erase(event_id);
    };

    void Insert(int eventId, int funcRef, uint32 shots) // Inserts a new registered event
    {
        Bindings[eventId].push_back(Binding(funcRef, shots));
    }

    // Checks if there are events for ID
    bool HasEvents(T eventId) const
    {
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
        for (EntryToEventsMap::iterator itr = Bindings.begin(); itr != Bindings.end(); ++itr)
        {
            for (EventToFunctionsMap::iterator it = itr->second.begin(); it != itr->second.end(); ++it)
            {
                for (FunctionRefVector::iterator i = it->second.begin(); i != it->second.end(); ++i)
                    luaL_unref(E.L, LUA_REGISTRYINDEX, (*i).functionReference);
                it->second.clear();
            }
            itr->second.clear();
        }
        Bindings.clear();
    }

    // Pushes the function references and updates the counters on the binds and erases them if the counter would reach 0
    void PushFuncRefs(lua_State* L, int event_id, uint32 entry)
    {
        for (FunctionRefVector::iterator it = Bindings[entry][event_id].begin(); it != Bindings[entry][event_id].end();)
        {
            FunctionRefVector::iterator it_old = it++;

            lua_rawgeti(L, LUA_REGISTRYINDEX, (it_old->functionReference));

            if (it_old->isTemporary)
            {
                --it_old->remainingShots;
                if (it_old->remainingShots == 0)
                {
                    luaL_unref(L, LUA_REGISTRYINDEX, it_old->functionReference);
                    Bindings[entry][event_id].erase(it_old);
                }
            }
        }

        if (Bindings[entry][event_id].empty())
            Bindings[entry].erase(event_id);

        if (Bindings[entry].empty())
            Bindings.erase(entry);
    };

    void Insert(uint32 entryId, int eventId, int funcRef, uint32 shots) // Inserts a new registered event
    {
        Bindings[entryId][eventId].push_back(Binding(funcRef, shots));
    }

    // Returns true if the entry has registered binds
    bool HasEvents(uint32 entryId, int eventId) const
    {
        if (Bindings.empty())
            return false;

        EntryToEventsMap::const_iterator itr = Bindings.find(entryId);
        if (itr == Bindings.end())
            return false;

        return itr->second.find(eventId) != itr->second.end();
    }

    bool HasEvents(uint32 entryId) const
    {
        if (Bindings.empty())
            return false;

        return Bindings.find(entryId) != Bindings.end();
    }

    EntryToEventsMap Bindings; // Binding store Bindings[entryId][eventId] = {(funcRef, counter)};
};

#endif
