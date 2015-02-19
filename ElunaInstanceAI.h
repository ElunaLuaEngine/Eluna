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
 * When `Save` is called, the string returned is not freed, so it
 *   cannot be dynamically allocated.
 *
 * Instead I just reserve a buffer that's `MAX_SAVE_DATA` big and
 *   return a pointer to it.
 *
 * I have assumed 1 kiB is enough, if you need to save more data
 *   than the buffer can hold, just make this constant larger.
 *   (1 kiB is enough for 100's of fields).
 */
#define MAX_SAVE_DATA 1024


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
    char lastSaveData[MAX_SAVE_DATA];

public:
    ElunaInstanceAI(Map* map) : InstanceData(map)
    {
        memset(lastSaveData, 0, MAX_SAVE_DATA);
    }

    void Initialize() override;

    /*
     * These are responsible for serializing/deserializing the instance's
     *   data table to/from the core.
     */
    void Load(const char* data) override;
    const char* Save() const override;

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

    /*
     * These methods allow non-Lua scripts (e.g. DB, C++) to get/set instance data.
     */
    uint32 GetData(uint32 key) const override;
    void SetData(uint32 key, uint32 value) override;

    uint64 GetData64(uint32 key) const override;
    void SetData64(uint32 key, uint64 value) override;

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
};

#endif // TRINITY
#endif // _ELUNA_INSTANCE_DATA_H