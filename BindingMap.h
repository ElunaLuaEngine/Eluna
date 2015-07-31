/*
* Copyright (C) 2010 - 2015 Eluna Lua Engine <http://emudevs.com/>
* This program is free software licensed under GPL version 3
* Please see the included DOCS/LICENSE.md for more information
*/

#ifndef _BINDING_MAP_H
#define _BINDING_MAP_H

#include <memory>
#include "Common.h"
#include "ElunaUtility.h"

extern "C"
{
#include "lua.h"
#include "lauxlib.h"
};


/*
 * A set of bindings from keys of type `K` to Lua references.
 */
template<typename K>
class BindingMap : public ElunaUtil::RWLockable
{
private:
    lua_State* L;
    uint64 maxBindingID;

    struct Binding
    {
        uint64 id;
        lua_State* L;
        uint32 remainingShots;
        int functionReference;

        Binding(lua_State* L, uint64 id, int functionReference, uint32 remainingShots) :
            id(id),
            L(L),
            remainingShots(remainingShots),
            functionReference(functionReference)
        { }

        ~Binding()
        {
            luaL_unref(L, LUA_REGISTRYINDEX, functionReference);
        }
    };

    typedef std::vector< std::unique_ptr<Binding> > BindingList;

    std::unordered_map<K, BindingList> bindings;
    /*
     * This table is for fast removal of bindings by ID.
     *
     * Instead of having to look through (potentially) every BindingList to find
     *   the Binding with the right ID, this allows you to go directly to the
     *   BindingList that might have the Binding with that ID.
     *
     * However, you must be careful not to store pointers to BindingLists
     *   that no longer exist (see `void Clear(const K& key)` implementation).
     */
    std::unordered_map<uint64, BindingList*> id_lookup_table;

public:
    BindingMap(lua_State* L) :
        L(L),
        maxBindingID(0)
    {
    }

    /*
     * Insert a new binding from `key` to `ref`, which lasts for `shots`-many pushes.
     *
     * If `shots` is 0, it will never automatically expire, but can still be
     *   removed with `Clear` or `Remove`.
     */
    uint64 Insert(const K& key, int ref, uint32 shots)
    {
        WriteGuard guard(GetLock());

        uint64 id = (++maxBindingID);
        BindingList& list = bindings[key];
        list.push_back(std::unique_ptr<Binding>(new Binding(L, id, ref, shots)));
        id_lookup_table[id] = &list;
        return id;
    }

    /*
     * Clear all bindings for `key`.
     */
    void Clear(const K& key)
    {
        WriteGuard guard(GetLock());

        if (bindings.empty())
            return;

        auto iter = bindings.find(key);
        if (iter == bindings.end())
            return;

        BindingList& list = iter->second;

        // Remove all pointers to `list` from `id_lookup_table`.
        for (auto i = list.begin(); i != list.end(); ++i)
        {
            std::unique_ptr<Binding>& binding = *i;
            id_lookup_table.erase(binding->id);
        }

        bindings.erase(key);
    }

    /*
     * Clear all bindings for all keys.
     */
    void Clear()
    {
        WriteGuard guard(GetLock());

        if (bindings.empty())
            return;

        id_lookup_table.clear();
        bindings.clear();
    }

    /*
     * Remove a specific binding identified by `id`.
     *
     * If `id` in invalid, nothing is removed.
     */
    void Remove(uint64 id)
    {
        WriteGuard guard(GetLock());

        auto iter = id_lookup_table.find(id);
        if (iter == id_lookup_table.end())
            return;

        BindingList* list = iter->second;
        auto i = list->begin();

        for (; i != list->end(); ++i)
        {
            std::unique_ptr<Binding>& binding = *i;
            if (binding->id == id)
                break;
        }

        if (i != list->end())
            list->erase(i);

        // Unconditionally erase the ID in the lookup table because
        //   it was either already invalid, or it's no longer valid.
        id_lookup_table.erase(id);
    }

    /*
     * Check whether `key` has any bindings.
     */
    bool HasBindingsFor(const K& key)
    {
        ReadGuard guard(GetLock());

        if (bindings.empty())
            return false;

        auto result = bindings.find(key);
        if (result == bindings.end())
            return false;

        BindingList& list = result->second;
        return !list.empty();
    }

    /*
     * Push all Lua references for `key` onto the stack.
     */
    void PushRefsFor(const K& key)
    {
        WriteGuard guard(GetLock());

        if (bindings.empty())
            return;

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
                {
                    id_lookup_table.erase(binding->id);
                    list.erase(i_prev);
                }
            }
        }
    }
};


/*
 * A `BindingMap` key type for simple event ID bindings
 *   (ServerEvents, GuildEvents, etc.).
 */
template <typename T>
struct EventKey
{
    T event_id;

    EventKey(T event_id) :
        event_id(event_id)
    {}
};

/*
 * A `BindingMap` key type for event ID/Object entry ID bindings
 *   (CreatureEvents, GameObjectEvents, etc.).
 */
template <typename T>
struct EntryKey
{
    T event_id;
    uint32 entry;

    EntryKey(T event_id, uint32 entry) :
        event_id(event_id),
        entry(entry)
    {}
};

/*
 * A `BindingMap` key type for event ID/unique Object bindings
 *   (currently just CreatureEvents).
 */
template <typename T>
struct UniqueObjectKey
{
    T event_id;
    uint64 guid;
    uint32 instance_id;

    UniqueObjectKey(T event_id, uint64 guid, uint32 instance_id) :
        event_id(event_id),
        guid(guid),
        instance_id(instance_id)
    {}
};


/*
 * Implementations of various std functions on the above key types,
 *   so that they can be used within an unordered_map.
 */
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

            return h1 ^ (h2 << 8); // `event_id` probably won't exceed 2^8.
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
            result_type const h2(std::hash<uint32>()(k.instance_id));
            result_type const h3(std::hash<uint64>()(k.guid));

            return h1 ^ (h2 << 8) ^ (h3 << 24); // `instance_id` probably won't exceed 2^16.
        }
    };
}

#endif // _BINDING_MAP_H
