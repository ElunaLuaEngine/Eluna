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


static uint64 maxBindingID;


class BindingMapBase : public ElunaUtil::RWLockable
{
public:
    virtual void Remove(uint64 id) = 0;
};


template<typename K>
class BindingMap : public BindingMapBase
{
    lua_State* L;

    struct Binding
    {
        uint64 id;
        int functionReference;
        uint32 remainingShots;
        lua_State* L;

        Binding(lua_State* L, uint64 id, int functionReference, uint32 remainingShots) :
            L(L),
            id(id),
            functionReference(functionReference),
            remainingShots(remainingShots)
        {}

        ~Binding()
        {
            luaL_unref(L, LUA_REGISTRYINDEX, functionReference);
        }
    };

    typedef std::vector< std::unique_ptr<Binding> > BindingList;

    UNORDERED_MAP<K, BindingList> bindings;

public:
    BindingMap(lua_State* L) :
        L(L)
    {
    }

    uint64 Insert(const K& key, int ref, uint32 shots)
    {
        WriteGuard guard(GetLock());

        uint64 id = (++maxBindingID);
        bindings[key].push_back(std::unique_ptr<Binding>(new Binding(L, id, ref, shots)));
        return id;
    }

    void Clear(const K& key)
    {
        WriteGuard guard(GetLock());

        auto iter = bindings.find(key);
        if (iter != bindings.end())
            bindings.erase(iter);
    }

    void Remove(uint64 id) override
    {
        WriteGuard guard(GetLock());

        for (auto listIter = bindings.begin(); listIter != bindings.end(); ++listIter)
        {
            BindingList& list = listIter->second;

            auto i = list.begin();
            for (; i != list.end(); ++i)
            {
                std::unique_ptr<Binding>& binding = *i;
                if (binding->id == id)
                    break;
            }

            if (i != list.end())
                list.erase(i);
        }
    }

    void PushRefsFor(const K& key)
    {
        WriteGuard guard(GetLock());

        auto result = bindings.find(key);
        if (result == bindings.end())
            return;

        BindingList& list = result->second;
        for (auto i = list.begin(); i != list.end();)
        {
            std::unique_ptr<Binding>& binding = (*i);
            auto i_prev = (i++);

            lua_rawgeti(L, LUA_REGISTRYINDEX, binding->functionReference);

            if (binding->remainingShots > 0)
            {
                binding->remainingShots -= 1;

                if (binding->remainingShots == 0)
                    list.erase(i_prev);
            }
        }
    }

    bool HasEvents(const K& key);
};


template <typename T>
struct EventKey
{
    T event_id;
    bool is_wildcard;

    EventKey(T event_id) :
        event_id(event_id),
        is_wildcard(false)
    {}

    EventKey() :
        is_wildcard(true)
    {}
};

template <typename T>
struct EntryKey : public EventKey<T>
{
    uint32 entry;

    EntryKey(T event_type, uint32 entry) :
        EventKey(event_type),
        entry(entry)
    {}

    EntryKey(uint32 entry) :
        EventKey(),
        entry(entry)
    {}
};

template <typename T>
struct UniqueCreatureKey : public EventKey<T>
{
    uint64 guid;
    uint32 instance_id;

    UniqueCreatureKey(T event_type, uint64 guid, uint32 instance_id) :
        EventKey(event_type),
        guid(guid),
        instance_id(instance_id)
    {}

    UniqueCreatureKey(uint64 guid, uint32 instance_id) :
        EventKey(),
        guid(guid),
        instance_id(instance_id)
    {}
};


namespace std
{
    template<typename T>
    struct equal_to < EventKey<T> >
    {
        bool operator()(EventKey<T> const& lhs, EventKey<T> const& rhs) const
        {
            return lhs.event_id == rhs.event_id;
        }
    };

    template<typename T>
    struct equal_to < EntryKey<T> >
    {
        bool operator()(EntryKey<T> const& lhs, EntryKey<T> const& rhs) const
        {
            return lhs.event_id == rhs.event_id
                && lhs.entry == rhs.entry;
        }
    };

    template<typename T>
    struct equal_to < UniqueCreatureKey<T> >
    {
        bool operator()(UniqueCreatureKey<T> const& lhs, UniqueCreatureKey<T> const& rhs) const
        {
            return lhs.event_id == rhs.event_id
                && lhs.guid == rhs.guid
                && lhs.instance_id == rhs.instance_id;
        }
    };

    template<typename T>
    struct hash < EventKey<T> >
    {
        typedef EventKey<T> argument_type;
        typedef std::size_t result_type;

        result_type operator()(argument_type const& k) const
        {
            result_type const h1(std::hash<uint32>()(k.event_id));
            return h1;
        }
    };

    template<typename T>
    struct hash < EntryKey<T> >
    {
        typedef EntryKey<T> argument_type;
        typedef std::size_t result_type;

        result_type operator()(argument_type const& k) const
        {
            result_type const h1(std::hash<uint32>()(k.event_id));
            result_type const h2(std::hash<uint32>()(k.entry));
            return h1 ^ (h2 << 1);
        }
    };

    template<typename T>
    struct hash < UniqueCreatureKey<T> >
    {
        typedef UniqueCreatureKey<T> argument_type;
        typedef std::size_t result_type;

        result_type operator()(argument_type const& k) const
        {
            result_type const h1(std::hash<uint32>()(k.event_id));
            result_type const h2(std::hash<uint64>()(k.guid));
            result_type const h3(std::hash<uint32>()(k.instance_id));
            return h1 ^ (h2 << 1) ^ (h3 << 2);
        }
    };
}


template<typename T>
bool BindingMap< EventKey<T> >::HasEvents(const EventKey<T>& key)
{
    ReadGuard guard(GetLock());

    auto result = bindings.find(key);
    if (result == bindings.end())
        return false;

    BindingList& list = result->second;
    return !list.empty();
}

template<typename T>
bool BindingMap< EntryKey<T> >::HasEvents(const EntryKey<T>& key)
{
    ReadGuard guard(GetLock());

    if (!key.is_wildcard)
    {
        auto result = bindings.find(key);
        if (result == bindings.end())
            return false;

        BindingList& list = result->second;
        return !list.empty();
    }

    for (auto listIter = bindings.begin(); listIter != bindings.end(); ++listIter)
    {
        EntryKey<T> const& listKey = listIter->first;

        if (listKey.entry != key.entry)
            continue;

        BindingList& list = listIter->second;
        if (!list.empty())
            return true;
    }
    return false;
}

template<typename T>
bool BindingMap< UniqueCreatureKey<T> >::HasEvents(const UniqueCreatureKey<T>& key)
{
    ReadGuard guard(GetLock());

    if (!key.is_wildcard)
    {
        auto result = bindings.find(key);
        if (result == bindings.end())
            return false;

        BindingList& list = result->second;
        return !list.empty();
    }

    for (auto listIter = bindings.begin(); listIter != bindings.end(); ++listIter)
    {
        EntryKey<T> const& listKey = listIter->first;

        if (listKey.guid != key.guid || listKey.instance_id != key.instance_id)
            continue;

        BindingList& list = listIter->second;
        if (!list.empty())
            return true;
    }
    return false;
}

#endif
