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

class ElunaInstanceData : public InstanceData
{
public:
    ElunaInstanceData(Map* map) : InstanceData(map) {}

    // On creation, NOT load.
    void Initialize()
    {
        sEluna->OnInitialize(instance);
    }

    // On load
    void Load(const char* data)
    {
        Initialize();
        sEluna->OnLoad(instance);
    }

    // When save is needed, this function generates the data
    const char* Save() const
    {
        return "";
    }

    // Called every map update
    void Update(uint32 diff)
    {
        sEluna->OnUpdateInstance(instance, diff);
    }

    // This is to prevent players from entering during boss encounters.
    bool IsEncounterInProgress() const
    {
        return sEluna->OnCheckEncounterInProgress(instance);
    }

    // Called when a player successfully enters the instance (after really added to map)
    void OnPlayerEnter(Player* player)
    {
        sEluna->OnPlayerEnterInstance(instance, player);
    }

    // Called when a player dies inside instance
    void OnPlayerDeath(Player* player)
    {
        sEluna->OnPlayerDeath(instance, player);
    }

    // Called when a player leaves the instance (before really removed from map (or possibly world))
    void OnPlayerLeave(Player* player)
    {
        sEluna->OnPlayerLeaveInstance(instance, player);
    }

    // Called when a gameobject is created
    void OnObjectCreate(GameObject* gameobject)
    {
        sEluna->OnGameObjectCreate(instance, gameobject);
    }

    // called on creature creation
    void OnCreatureCreate(Creature* creature)
    {
        sEluna->OnCreatureCreate(instance, creature);
    }

    // called on creature enter combat
    void OnCreatureEnterCombat(Creature* creature)
    {
        sEluna->OnCreatureEnterCombat(instance, creature);
    }

    // called on creature evade
    void OnCreatureEvade(Creature* creature)
    {
        sEluna->OnCreatureEvade(instance, creature);
    }

    // called on creature death
    void OnCreatureDeath(Creature* creature)
    {
        sEluna->OnCreatureDeath(instance, creature);
    }

    // Condition criteria additional requirements check
    // This is used for such things are heroic loot
    // See ObjectMgr.h enum ConditionSource for possible values of conditionSourceType
    bool CheckConditionCriteriaMeet(Player const* source, uint32 instance_condition_id, WorldObject const* conditionSource, uint32 conditionSourceType) const
    {
        return sEluna->OnCheckCondition(instance, source, instance_condition_id, conditionSource, conditionSourceType);
    }
};

#endif // TRINITY
#endif // _ELUNA_INSTANCE_DATA_H