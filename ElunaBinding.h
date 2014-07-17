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
    Eluna& E;
    const char* groupName;

    ElunaBind(const char* bindGroupName, Eluna& _E): E(_E), groupName(bindGroupName)
    {
    }

    virtual ~ElunaBind()
    {
        Clear();
    }

    // unregisters all registered functions and clears all registered events from the bindings
    virtual void Clear() {};
};

template<typename T>
class EventBind : public ElunaBind
{
public:
    typedef std::vector<int> ElunaBindingMap;
    typedef std::map<int, ElunaBindingMap> ElunaEntryMap;

    EventBind(const char* bindGroupName, Eluna& _E): ElunaBind(bindGroupName, _E)
    {
    }

    // unregisters all registered functions and clears all registered events from the bind std::maps (reset)
    void Clear() override
    {
        for (ElunaEntryMap::iterator itr = Bindings.begin(); itr != Bindings.end(); ++itr)
        {
            for (ElunaBindingMap::iterator it = itr->second.begin(); it != itr->second.end(); ++it)
                luaL_unref(E.L, LUA_REGISTRYINDEX, (*it));
            itr->second.clear();
        }
        Bindings.clear();
    }

    void Insert(int eventId, int funcRef) // Inserts a new registered event
    {
        Bindings[eventId].push_back(funcRef);
    }

    // Gets the binding std::map containing all registered events with the function refs for the entry
    ElunaBindingMap* GetBindMap(T eventId)
    {
        if (Bindings.empty())
            return NULL;
        ElunaEntryMap::iterator itr = Bindings.find(eventId);
        if (itr == Bindings.end())
            return NULL;

        return &itr->second;
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

    ElunaEntryMap Bindings; // Binding store Bindings[eventId] = {funcRef};
};

template<typename T>
class EntryBind : public ElunaBind
{
public:
    typedef std::map<int, int> ElunaBindingMap;
    typedef UNORDERED_MAP<uint32, ElunaBindingMap> ElunaEntryMap;

    EntryBind(const char* bindGroupName, Eluna& _E): ElunaBind(bindGroupName, _E)
    {
    }

    // unregisters all registered functions and clears all registered events from the bindmap
    void Clear() override
    {
        for (ElunaEntryMap::iterator itr = Bindings.begin(); itr != Bindings.end(); ++itr)
        {
            for (ElunaBindingMap::const_iterator it = itr->second.begin(); it != itr->second.end(); ++it)
                luaL_unref(E.L, LUA_REGISTRYINDEX, it->second);
            itr->second.clear();
        }
        Bindings.clear();
    }

    void Insert(uint32 entryId, int eventId, int funcRef) // Inserts a new registered event
    {
        if (Bindings[entryId][eventId])
        {
            luaL_unref(E.L, LUA_REGISTRYINDEX, funcRef); // free the unused ref
            luaL_error(E.L, "A function is already registered for entry (%d) event (%d)", entryId, eventId);
        }
        else
            Bindings[entryId][eventId] = funcRef;
    }

    // Gets the function ref of an entry for an event
    int GetBind(uint32 entryId, T eventId) const
    {
        if (Bindings.empty())
            return 0;
        ElunaEntryMap::const_iterator itr = Bindings.find(entryId);
        if (itr == Bindings.end() || itr->second.empty())
            return 0;
        ElunaBindingMap::const_iterator itr2 = itr->second.find(eventId);
        if (itr2 == itr->second.end())
            return 0;
        return itr2->second;
    }

    // Gets the binding std::map containing all registered events with the function refs for the entry
    const ElunaBindingMap* GetBindMap(uint32 entryId) const
    {
        if (Bindings.empty())
            return NULL;
        ElunaEntryMap::const_iterator itr = Bindings.find(entryId);
        if (itr == Bindings.end())
            return NULL;

        return &itr->second;
    }

    // Returns true if the entry has registered binds
    bool HasBinds(uint32 entryId) const
    {
        if (Bindings.empty())
            return false;
        return Bindings.find(entryId) != Bindings.end();
    }

    ElunaEntryMap Bindings; // Binding store Bindings[entryId][eventId] = funcRef;
};

#endif
