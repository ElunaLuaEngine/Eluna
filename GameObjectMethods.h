/*
* Copyright (C) 2010 - 2014 Eluna Lua Engine <http://emudevs.com/>
* This program is free software licensed under GPL version 3
* Please see the included DOCS/LICENSE.md for more information
*/

#ifndef GAMEOBJECTMETHODS_H
#define GAMEOBJECTMETHODS_H

namespace LuaGameObject
{
    /**
     * Returns 'true' if the [GameObject] can give the specified [Quest]
     *
     * @param uint32 questId : quest entry Id to check
     * @return bool hasQuest
     */
    int HasQuest(lua_State* L, GameObject* go)
    {
        uint32 questId = Eluna::CHECKVAL<uint32>(L, 2);

#ifndef TRINITY
        Eluna::Push(L, go->HasQuest(questId));
#else
        Eluna::Push(L, go->hasQuest(questId));
#endif
        return 1;
    }

    /**
     * Returns 'true' if the [GameObject] is spawned
     *
     * @return bool isSpawned
     */
    int IsSpawned(lua_State* L, GameObject* go)
    {
        Eluna::Push(L, go->isSpawned());
        return 1;
    }

    /**
     * Returns 'true' if the [GameObject] is a transport
     *
     * @return bool isTransport
     */
    int IsTransport(lua_State* L, GameObject* go)
    {
        Eluna::Push(L, go->IsTransport());
        return 1;
    }

    /**
     * Returns 'true' if the [GameObject] is active
     *
     * @return bool isActive
     */
    int IsActive(lua_State* L, GameObject* go)
    {
        Eluna::Push(L, go->isActiveObject());
        return 1;
    }

    /*int IsDestructible(lua_State* L, GameObject* go) // TODO: Implementation core side
    {
    Eluna::Push(L, go->IsDestructibleBuilding());
    return 1;
    }*/

    /**
     * Returns display ID of the [GameObject]
     *
     * @return uint32 displayId
     */
    int GetDisplayId(lua_State* L, GameObject* go)
    {
        Eluna::Push(L, go->GetDisplayId());
        return 1;
    }

    /**
     * Returns the state of a [GameObject]
     * Below are client side [GOState]s off of 3.3.5a
     *
     * <pre>
     * enum GOState
     * {
     *     GO_STATE_ACTIVE             = 0,                        // show in world as used and not reset (closed door open)
     *     GO_STATE_READY              = 1,                        // show in world as ready (closed door close)
     *     GO_STATE_ACTIVE_ALTERNATIVE = 2                         // show in world as used in alt way and not reset (closed door open by cannon fire)
     * };
     * </pre>
     *
     * @return [GOState] goState
     */
    int GetGoState(lua_State* L, GameObject* go)
    {
        Eluna::Push(L, go->GetGoState());
        return 1;
    }

    /**
     * Returns the [LootState] of a [GameObject]
     * Below are [LootState]s off of 3.3.5a
     *
     * <pre>
     * enum LootState
     * {
     *     GO_NOT_READY = 0,
     *     GO_READY,                                               // can be ready but despawned, and then not possible activate until spawn
     *     GO_ACTIVATED,
     *     GO_JUST_DEACTIVATED
     * };
     * </pre>
     *
     * @return [LootState] lootState
     */
    int GetLootState(lua_State* L, GameObject* go)
    {
        Eluna::Push(L, go->getLootState());
        return 1;
    }

    /**
     * Sets the state of a [GameObject]
     *
     * <pre>
     * enum GOState
     * {
     *     GO_STATE_ACTIVE             = 0,                        // show in world as used and not reset (closed door open)
     *     GO_STATE_READY              = 1,                        // show in world as ready (closed door close)
     *     GO_STATE_ACTIVE_ALTERNATIVE = 2                         // show in world as used in alt way and not reset (closed door open by cannon fire)
     * };
     * </pre>
     *
     * @param [GOState] state : all available go states can be seen above
     */
    int SetGoState(lua_State* L, GameObject* go)
    {
        uint32 state = Eluna::CHECKVAL<uint32>(L, 2, 0);

        if (state == 0)
            go->SetGoState(GO_STATE_ACTIVE);
        else if (state == 1)
            go->SetGoState(GO_STATE_READY);
        else if (state == 2)
            go->SetGoState(GO_STATE_ACTIVE_ALTERNATIVE);

        return 0;
    }

    /**
     * Sets the [LootState] of a [GameObject]
     * Below are [LootState]s off of 3.3.5a
     *
     * <pre>
     * enum LootState
     * {
     *     GO_NOT_READY = 0,
     *     GO_READY,                                               // can be ready but despawned, and then not possible activate until spawn
     *     GO_ACTIVATED,
     *     GO_JUST_DEACTIVATED
     * };
     * </pre>
     *
     * @param [LootState] state : all available loot states can be seen above
     */
    int SetLootState(lua_State* L, GameObject* go)
    {
        uint32 state = Eluna::CHECKVAL<uint32>(L, 2, 0);

        if (state == 0)
            go->SetLootState(GO_NOT_READY);
        else if (state == 1)
            go->SetLootState(GO_READY);
        else if (state == 2)
            go->SetLootState(GO_ACTIVATED);
        else if (state == 3)
            go->SetLootState(GO_JUST_DEACTIVATED);

        return 0;
    }

    /**
     * Saves [GameObject] to the database
     *
     */
    int SaveToDB(lua_State* /*L*/, GameObject* go)
    {
        go->SaveToDB();
        return 0;
    }

    /**
     * Removes [GameObject] from the world
     *
     * @param bool deleteFromDB : if true, it will delete the [GameObject] from the database
     */
    int RemoveFromWorld(lua_State* L, GameObject* go)
    {
        bool deldb = Eluna::CHECKVAL<bool>(L, 2, false);
        if (deldb)
            go->DeleteFromDB();
        go->RemoveFromWorld();
        return 0;
    }

    /**
     * Registers a timed event to the [GameObject]
     *
     * @param function function : function to trigger when the time has passed
     * @param uint32 delay : set time in milliseconds for the event to trigger
     * @param uint32 repeats : how many times for the event to repeat, 0 is infinite
     * @return int32 eventId : unique ID for the timed event used to cancel it
     */
    int RegisterEvent(lua_State* L, GameObject* go)
    {
        luaL_checktype(L, 2, LUA_TFUNCTION);
        uint32 delay = Eluna::CHECKVAL<uint32>(L, 3);
        uint32 repeats = Eluna::CHECKVAL<uint32>(L, 4);

        lua_pushvalue(L, 2);
        int functionRef = luaL_ref(L, LUA_REGISTRYINDEX);
        functionRef = sEluna->m_EventMgr->AddEvent(&go->m_Events, functionRef, delay, repeats, go);
        if (functionRef)
            Eluna::Push(L, functionRef);
        return 1;
    }

    /**
     * Removes the timed event from a [GameObject] by the specified event ID
     *
     * @param int32 eventId : event Id to remove
     */
    int RemoveEventById(lua_State* L, GameObject* go)
    {
        int eventId = Eluna::CHECKVAL<int>(L, 2);
        sEluna->m_EventMgr->RemoveEvent(&go->m_Events, eventId);
        return 0;
    }

    /**
     * Removes all timed events from a [GameObject]
     *
     */
    int RemoveEvents(lua_State* /*L*/, GameObject* go)
    {
        sEluna->m_EventMgr->RemoveEvents(&go->m_Events);
        return 0;
    }

    /**
     * Changes uses a door or a button type [GameObject]
     *
     * @param uint32 delay : cooldown time in seconds to restore the [GameObject] back to normal
     */
    int UseDoorOrButton(lua_State* L, GameObject* go)
    {
        uint32 delay = Eluna::CHECKVAL<uint32>(L, 2, 0);

        go->UseDoorOrButton(delay);
        return 0;
    }

    /**
     * Despawns a [GameObject]
     *
     * @param uint32 delay : time in seconds to despawn
     */
    int Despawn(lua_State* L, GameObject* go)
    {
        uint32 delay = Eluna::CHECKVAL<uint32>(L, 2, 1);
        if (!delay)
            delay = 1;

        go->SetSpawnedByDefault(false);
        go->SetRespawnTime(delay);
        return 0;
    }

    /**
     * Respawns a [GameObject]
     *
     * @param uint32 delay : time of respawn in seconds
     */
    int Respawn(lua_State* L, GameObject* go)
    {
        uint32 delay = Eluna::CHECKVAL<uint32>(L, 2, 1);
        if (!delay)
            delay = 1;

        go->SetSpawnedByDefault(true);
        go->SetRespawnTime(delay);
        return 0;
    }
};
#endif
