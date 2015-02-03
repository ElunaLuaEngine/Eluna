/*
* Copyright (C) 2010 - 2015 Eluna Lua Engine <http://emudevs.com/>
* This program is free software licensed under GPL version 3
* Please see the included DOCS/LICENSE.md for more information
*/

#ifndef _ELUNA_INSTANCE_DATA_H
#define _ELUNA_INSTANCE_DATA_H

#include "LuaEngine.h"

#ifndef TRINITY
#include "InstanceData.h"

/*
 * This class is a small wrapper around `InstanceData`,
 *   allowing instances to be scripted with Eluna.
 *
 *
 * Note 1
 * ======
 *
 * Instances of `ElunaInstanceAI` are owned by the core, so they
 *   are not deleted when Eluna is reloaded. Thus `Load` is only called
 *   by the core once, no matter how many times Eluna is reloaded.
 *
 * However, when Eluna reloads, all instance data in Eluna is lost.
 * So the solution is as follows:
 *
 *   1. Store the last save data in the member var `lastSaveData`.
 *
 *      At first this is just the data given to us by the core when it calls `Load`,
 *        but later on once we start saving new data this is from Eluna.
 *
 *   2. When retrieving instance data from Eluna, check if it's missing.
 *
 *      The data will be missing if Eluna is reloaded, since a new Lua state is created.
 *
 *   3. If it *is* missing, call `Reload`.
 *
 *      This reloads the last known instance save data into Eluna, and calls the appropriate hooks.
 *
 *
 * Note 2
 * ======
 *
 * CMaNGOS expects some of these methods to be `const`. However, any of these
 *   methods are free to call `Save`, resulting in mutation of `lastSaveData`.
 *
 * Therefore, none of the hooks are `const`-safe, and `const_cast` is used
 *   to escape from these restrictions.
 */
class ElunaInstanceAI : public InstanceData
{
private:
    // The last save data to pass through this class,
    //   either through `Load` or `Save`.
    std::string lastSaveData;

public:
    ElunaInstanceAI(Map* map) : InstanceData(map), lastSaveData() {}

    void Initialize() override
    {
        LOCK_ELUNA;

        // We might have instance data if this method was called from `Load`.
        if (!sEluna->HasInstanceData(instance))
        {
            // Create a new table for instance data.
            lua_State* L = sEluna->L;
            lua_newtable(L);
            sEluna->CreateInstanceData(instance);
        }
       
        sEluna->OnInitialize(this);
    }

    /*
     * These are responsible for serializing/deserializing the instance's
     *   data table to/from the core.
     */
    void Load(const char* data) override
    {
        LOCK_ELUNA;

        if (data)
            lastSaveData = data;

        Initialize();
        sEluna->OnLoad(this);
    }

    const char* Save() const override
    {
        return lastSaveData.c_str();
    }

    static int SaveFromLua(Eluna* E, lua_State* L, ElunaInstanceAI* iAI)
    {
        return 0;
    }

    /*
     * These methods are just thin wrappers around Eluna.
     */
    void Update(uint32 diff) override
    {
        sEluna->OnUpdateInstance(this, diff);
    }

    bool IsEncounterInProgress() const override
    {
        return sEluna->OnCheckEncounterInProgress(const_cast<ElunaInstanceAI*>(this));
    }

    void OnPlayerEnter(Player* player) override
    {
        sEluna->OnPlayerEnterInstance(this, player);
    }

    void OnPlayerDeath(Player* player) override
    {
        sEluna->OnPlayerDeath(this, player);
    }

    void OnPlayerLeave(Player* player) override
    {
        sEluna->OnPlayerLeaveInstance(this, player);
    }

    void OnObjectCreate(GameObject* gameobject) override
    {
        sEluna->OnGameObjectCreate(this, gameobject);
    }

    void OnCreatureCreate(Creature* creature) override
    {
        sEluna->OnCreatureCreate(this, creature);
    }

    void OnCreatureEnterCombat(Creature* creature) override
    {
        sEluna->OnCreatureEnterCombat(this, creature);
    }

    void OnCreatureEvade(Creature* creature) override
    {
        sEluna->OnCreatureEvade(this, creature);
    }

    void OnCreatureDeath(Creature* creature) override
    {
        sEluna->OnCreatureDeath(this, creature);
    }

    bool CheckConditionCriteriaMeet(Player const* source, uint32 instance_condition_id, WorldObject const* conditionSource, uint32 conditionSourceType) const override
    {
        return sEluna->OnCheckCondition(const_cast<ElunaInstanceAI*>(this), source, instance_condition_id, conditionSource, conditionSourceType);
    }

    /*
     * These methods allow non-Lua scripts (e.g. DB, C++) to get/set instance data.
     */
    uint32 GetData(uint32 key) const override
    {
        LOCK_ELUNA;
        lua_State* L = sEluna->L;
        // Stack: (empty)

        sEluna->PushInstanceData(const_cast<ElunaInstanceAI*>(this), false);
        // Stack: instance_data

        Eluna::Push(L, key);
        // Stack: instance_data, key

        lua_gettable(L, -2);
        // Stack: instance_data, value

        uint32 value = Eluna::CHECKVAL<uint32>(L, -1, 0);
        lua_pop(L, 2);
        // Stack: (empty)

        return value;
    }

    void SetData(uint32 key, uint32 value) override
    {
        LOCK_ELUNA;
        lua_State* L = sEluna->L;
        // Stack: (empty)

        sEluna->PushInstanceData(this, false);
        // Stack: instance_data

        Eluna::Push(L, key);
        Eluna::Push(L, value);
        // Stack: instance_data, key, value

        lua_settable(L, -3);
        // Stack: instance_data

        lua_pop(L, 1);
        // Stack: (empty)
    }

    uint64 GetData64(uint32 key) const override
    {
        LOCK_ELUNA;
        lua_State* L = sEluna->L;
        // Stack: (empty)

        sEluna->PushInstanceData(const_cast<ElunaInstanceAI*>(this), false);
        // Stack: instance_data

        Eluna::Push(L, key);
        // Stack: instance_data, key

        lua_gettable(L, -2);
        // Stack: instance_data, value

        uint64 value = Eluna::CHECKVAL<uint64>(L, -1, 0);
        lua_pop(L, 2);
        // Stack: (empty)

        return value;
    }

    void SetData64(uint32 key, uint64 value) override
    {
        LOCK_ELUNA;
        lua_State* L = sEluna->L;
        // Stack: (empty)

        sEluna->PushInstanceData(this, false);
        // Stack: instance_data

        Eluna::Push(L, key);
        Eluna::Push(L, value);
        // Stack: instance_data, key, value

        lua_settable(L, -3);
        // Stack: instance_data

        lua_pop(L, 1);
        // Stack: (empty)
    }

    /*
     * Calls `Load` with the last save data that was passed to
     * or from Eluna.
     *
     * See: big documentation blurb at the top of this class.
     */
    void Reload()
    {
        Load(NULL);
    }
};

#endif // TRINITY
#endif // _ELUNA_INSTANCE_DATA_H