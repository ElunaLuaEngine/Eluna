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
    int HasQuest(Eluna* E, GameObject* go)
    {
        uint32 questId = Eluna::CHECKVAL<uint32>(E->L, 2);

#ifndef TRINITY
        Eluna::Push(E->L, go->HasQuest(questId));
#else
        Eluna::Push(E->L, go->hasQuest(questId));
#endif
        return 1;
    }

    /**
     * Returns 'true' if the [GameObject] is spawned
     *
     * @return bool isSpawned
     */
    int IsSpawned(Eluna* E, GameObject* go)
    {
        Eluna::Push(E->L, go->isSpawned());
        return 1;
    }

    /**
     * Returns 'true' if the [GameObject] is a transport
     *
     * @return bool isTransport
     */
    int IsTransport(Eluna* E, GameObject* go)
    {
        Eluna::Push(E->L, go->IsTransport());
        return 1;
    }

    /**
     * Returns 'true' if the [GameObject] is active
     *
     * @return bool isActive
     */
    int IsActive(Eluna* E, GameObject* go)
    {
        Eluna::Push(E->L, go->isActiveObject());
        return 1;
    }

    /*int IsDestructible(Eluna* E, GameObject* go) // TODO: Implementation core side
    {
    Eluna::Push(E->L, go->IsDestructibleBuilding());
    return 1;
    }*/

    /**
     * Returns display ID of the [GameObject]
     *
     * @return uint32 displayId
     */
    int GetDisplayId(Eluna* E, GameObject* go)
    {
        Eluna::Push(E->L, go->GetDisplayId());
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
    int GetGoState(Eluna* E, GameObject* go)
    {
        Eluna::Push(E->L, go->GetGoState());
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
    int GetLootState(Eluna* E, GameObject* go)
    {
        Eluna::Push(E->L, go->getLootState());
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
    int SetGoState(Eluna* E, GameObject* go)
    {
        uint32 state = Eluna::CHECKVAL<uint32>(E->L, 2, 0);

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
    int SetLootState(Eluna* E, GameObject* go)
    {
        uint32 state = Eluna::CHECKVAL<uint32>(E->L, 2, 0);

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
    int SaveToDB(Eluna* /*E*/, GameObject* go)
    {
        go->SaveToDB();
        return 0;
    }

    /**
     * Removes [GameObject] from the world
     *
     * @param bool deleteFromDB : if true, it will delete the [GameObject] from the database
     */
    int RemoveFromWorld(Eluna* E, GameObject* go)
    {
        bool deldb = Eluna::CHECKVAL<bool>(E->L, 2, false);
        if (deldb)
            go->DeleteFromDB();
        go->RemoveFromWorld();
        return 0;
    }

    /**
     * Changes uses a door or a button type [GameObject]
     *
     * @param uint32 delay : cooldown time in seconds to restore the [GameObject] back to normal
     */
    int UseDoorOrButton(Eluna* E, GameObject* go)
    {
        uint32 delay = Eluna::CHECKVAL<uint32>(E->L, 2, 0);

        go->UseDoorOrButton(delay);
        return 0;
    }

    /**
     * Despawns a [GameObject]
     *
     * @param uint32 delay : time in seconds to despawn
     */
    int Despawn(Eluna* E, GameObject* go)
    {
        uint32 delay = Eluna::CHECKVAL<uint32>(E->L, 2, 1);
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
    int Respawn(Eluna* E, GameObject* go)
    {
        uint32 delay = Eluna::CHECKVAL<uint32>(E->L, 2, 1);
        if (!delay)
            delay = 1;

        go->SetSpawnedByDefault(true);
        go->SetRespawnTime(delay);
        return 0;
    }
};
#endif
