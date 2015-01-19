/*
* Copyright (C) 2010 - 2015 Eluna Lua Engine <http://emudevs.com/>
* This program is free software licensed under GPL version 3
* Please see the included DOCS/LICENSE.md for more information
*/

#ifndef _ELUNA_INSTANCE_DATA_H
#define _ELUNA_INSTANCE_DATA_H

#ifndef TRINITY
#include "LuaEngine.h"
#include "InstanceData.h"

extern "C"
{
#include "lauxlib.h"
}

class ElunaInstanceData : public InstanceData
{
public:
    ElunaInstanceData(Map* map) : InstanceData(map) {}

    // On creation, NOT load.
    void Initialize() {}

    // On load
    void Load(const char* /*data*/) {}

    // When save is needed, this function generates the data
    const char* Save() const { return ""; }

    // Called every map update
    void Update(uint32 /*diff*/) {}

    // This is to prevent players from entering during boss encounters.
    bool IsEncounterInProgress() const { return false; };

    // Called when a player successfully enters the instance (after really added to map)
    void OnPlayerEnter(Player*) {}

    // Called when a player dies inside instance
    void OnPlayerDeath(Player*) {}

    // Called when a player leaves the instance (before really removed from map (or possibly world))
    void OnPlayerLeave(Player*) {}

    // Called when a gameobject is created
    void OnObjectCreate(GameObject*) {}

    // called on creature creation
    void OnCreatureCreate(Creature* /*creature*/) {}

    // called on creature enter combat
    void OnCreatureEnterCombat(Creature* /*creature*/) {}

    // called on creature evade
    void OnCreatureEvade(Creature* /*creature*/) {}

    // called on creature death
    void OnCreatureDeath(Creature* /*creature*/) {}

    // All-purpose data storage 64 bit
    uint64 GetData64(uint32 /*Data*/) const { return 0; }
    void SetData64(uint32 /*Data*/, uint64 /*Value*/) { }

    // Guid data storage (wrapper for set/get from uint64 storage
    ObjectGuid GetGuid(uint32 dataIdx) const { return ObjectGuid(GetData64(dataIdx)); }
    void SetGuid(uint32 dataIdx, ObjectGuid value) { SetData64(dataIdx, value.GetRawValue()); }

    // All-purpose data storage 32 bit
    uint32 GetData(uint32 /*Type*/) const { return 0; }
    void SetData(uint32 /*Type*/, uint32 /*Data*/) {}

    // Condition criteria additional requirements check
    // This is used for such things are heroic loot
    // See ObjectMgr.h enum ConditionSource for possible values of conditionSourceType
    bool CheckConditionCriteriaMeet(Player const* source, uint32 instance_condition_id, WorldObject const* conditionSource, uint32 conditionSourceType) const { return false; }
};

#endif // TRINITY
#endif // _ELUNA_INSTANCE_DATA_H