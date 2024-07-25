/*
* Copyright (C) 2010 - 2024 Eluna Lua Engine <https://elunaluaengine.github.io/>
* This program is free software licensed under GPL version 3
* Please see the included DOCS/LICENSE.md for more information
*/

#ifndef _ELUNA_INSTANCE_DATA_H
#define _ELUNA_INSTANCE_DATA_H

#include "LuaEngine.h"
#if defined ELUNA_TRINITY
#include "InstanceScript.h"
#include "Map.h"
#elif defined ELUNA_CMANGOS
#include "Maps/InstanceData.h"
#else
#include "InstanceData.h"
#endif

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
#if defined ELUNA_TRINITY
    ElunaInstanceAI(Map* map) : InstanceData(map->ToInstanceMap())
    {
    }
#else
    ElunaInstanceAI(Map* map) : InstanceData(map)
    {
    }
#endif

#if !defined ELUNA_TRINITY
    void Initialize() override;
#endif

    /*
     * These are responsible for serializing/deserializing the instance's
     *   data table to/from the core.
     */
    void Load(const char* data) override;
#if defined ELUNA_TRINITY
    // Simply calls Save, since the functions are a bit different in name and data types on different cores
    std::string GetSaveData() override
    {
        return Save();
    }
    const char* Save() const;
#elif defined ELUNA_VMANGOS
    const char* Save() const;
#else
    const char* Save() const override;
#endif


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
#if !defined ELUNA_VMANGOS
    uint32 GetData(uint32 key) const override;
#else
    uint32 GetData(uint32 key) const;
#endif
    void SetData(uint32 key, uint32 value) override;

#if !defined ELUNA_VMANGOS
    uint64 GetData64(uint32 key) const override;
#else
    uint64 GetData64(uint32 key) const;
#endif
    void SetData64(uint32 key, uint64 value) override;

    /*
     * These methods are just thin wrappers around Eluna.
     */
    void Update(uint32 diff) override
    {
        // If Eluna is reloaded, it will be missing our instance data.
        // Reload here instead of waiting for the next hook call (possibly never).
        // This avoids having to have an empty Update hook handler just to trigger the reload.
        if (!instance->GetEluna()->HasInstanceData(instance))
            Reload();

        instance->GetEluna()->OnUpdateInstance(this, diff);
    }

    bool IsEncounterInProgress() const override
    {
        return instance->GetEluna()->OnCheckEncounterInProgress(const_cast<ElunaInstanceAI*>(this));
    }

    void OnPlayerEnter(Player* player) override
    {
        instance->GetEluna()->OnPlayerEnterInstance(this, player);
    }

#if defined ELUNA_TRINITY
    void OnGameObjectCreate(GameObject* gameobject) override
#else
    void OnObjectCreate(GameObject* gameobject) override
#endif
    {
        instance->GetEluna()->OnGameObjectCreate(this, gameobject);
    }

    void OnCreatureCreate(Creature* creature) override
    {
        instance->GetEluna()->OnCreatureCreate(this, creature);
    }
};

#endif // _ELUNA_INSTANCE_DATA_H
