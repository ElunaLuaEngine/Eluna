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


template<typename K>
class BindingMap : public ElunaUtil::RWLockable
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

    typedef std::vector<Binding*> BindingList;

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
        bindings[key].push_back(new Binding(L, id, ref, shots));
        return id;
    }

    void Clear(const K& key)
    {
        WriteGuard guard(GetLock());

        auto iter = bindings.find(key);
        if (iter != bindings.end())
        {
            BindingList& list = iter->second;

            for (auto i = list.begin(); i != list.end;)
            {
                auto i_prev = (i++);
                Binding* binding = *i_prev;
                list.erase(i_prev);
                delete binding;
            }

            bindings.erase(iter);
        }
    }

    void Remove(uint64 id)
    {
        WriteGuard guard(GetLock());

        for (auto listIter = bindings.begin(); listIter != bindings.end(); ++listIter)
        {
            BindingList& list = listIter->second;

            auto i = list.begin();
            Binding* binding;

            for (; i != list.end(); ++i)
            {
                binding = *i;
                if (binding->id == id)
                    break;
            }

            if (i != list.end())
            {
                list.erase(i);
                delete binding;
            }
        }
    }

    bool HasEvents(const K& key)
    {
        ReadGuard guard(GetLock());

        auto result = bindings.find(key);
        if (result == bindings.end())
            return false;

        BindingList& list = result->second;
        return !list.empty();
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
            Binding* binding = (*i);
            auto i_prev = (i++);

            lua_rawgeti(L, LUA_REGISTRYINDEX, binding->functionReference);

            if (binding->remainingShots > 0)
            {
                binding->remainingShots -= 1;

                if (binding->remainingShots == 0)
                {
                    list.erase(i_prev);
                    delete binding;
                }
            }
        }
    }
};


template <typename T>
struct EventKey
{
    T event_id;

    EventKey(T event_id) :
        event_id(event_id)
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
};

template <typename T>
struct UniqueObjectKey : public EventKey<T>
{
    uint64 guid;
    uint32 instance_id;

    UniqueObjectKey(T event_type, uint64 guid, uint32 instance_id) :
        EventKey(event_type),
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
    struct equal_to < UniqueObjectKey<T> >
    {
        bool operator()(UniqueObjectKey<T> const& lhs, UniqueObjectKey<T> const& rhs) const
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
    struct hash < UniqueObjectKey<T> >
    {
        typedef UniqueObjectKey<T> argument_type;
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

#endif
