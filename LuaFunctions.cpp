/*
* Copyright (C) 2010 - 2015 Eluna Lua Engine <http://emudevs.com/>
* This program is free software licensed under GPL version 3
* Please see the included DOCS/LICENSE.md for more information
*/

extern "C"
{
#include "lua.h"
};

// Eluna
#include "LuaEngine.h"
#include "ElunaEventMgr.h"
#include "ElunaIncludes.h"
#include "ElunaTemplate.h"
#include "ElunaUtility.h"

// Method includes
#include "GlobalMethods.h"
#include "ObjectMethods.h"
#include "WorldObjectMethods.h"
#include "UnitMethods.h"
#include "PlayerMethods.h"
#include "CreatureMethods.h"
#include "GroupMethods.h"
#include "GuildMethods.h"
#include "GameObjectMethods.h"
#include "ElunaQueryMethods.h"
#include "AuraMethods.h"
#include "ItemMethods.h"
#include "WorldPacketMethods.h"
#include "SpellMethods.h"
#include "QuestMethods.h"
#include "MapMethods.h"
#include "CorpseMethods.h"
#include "WeatherMethods.h"
#include "VehicleMethods.h"
#include "BattleGroundMethods.h"

ElunaGlobal::ElunaRegister GlobalMethods[] =
{
    // Hooks
    { "RegisterPacketEvent", &LuaGlobalFunctions::RegisterPacketEvent },                       // RegisterPacketEvent(opcodeID, event, function)
    { "RegisterServerEvent", &LuaGlobalFunctions::RegisterServerEvent },                       // RegisterServerEvent(event, function)
    { "RegisterPlayerEvent", &LuaGlobalFunctions::RegisterPlayerEvent },                       // RegisterPlayerEvent(event, function)
    { "RegisterGuildEvent", &LuaGlobalFunctions::RegisterGuildEvent },                         // RegisterGuildEvent(event, function)
    { "RegisterGroupEvent", &LuaGlobalFunctions::RegisterGroupEvent },                         // RegisterGroupEvent(event, function)
    { "RegisterCreatureEvent", &LuaGlobalFunctions::RegisterCreatureEvent },                   // RegisterCreatureEvent(entry, event, function)
    { "RegisterUniqueCreatureEvent", &LuaGlobalFunctions::RegisterUniqueCreatureEvent },             // RegisterUniqueCreatureEvent(guid, instance, event, function)
    { "RegisterCreatureGossipEvent", &LuaGlobalFunctions::RegisterCreatureGossipEvent },       // RegisterCreatureGossipEvent(entry, event, function)
    { "RegisterGameObjectEvent", &LuaGlobalFunctions::RegisterGameObjectEvent },               // RegisterGameObjectEvent(entry, event, function)
    { "RegisterGameObjectGossipEvent", &LuaGlobalFunctions::RegisterGameObjectGossipEvent },   // RegisterGameObjectGossipEvent(entry, event, function)
    { "RegisterItemEvent", &LuaGlobalFunctions::RegisterItemEvent },                           // RegisterItemEvent(entry, event, function)
    { "RegisterItemGossipEvent", &LuaGlobalFunctions::RegisterItemGossipEvent },               // RegisterItemGossipEvent(entry, event, function)
    { "RegisterPlayerGossipEvent", &LuaGlobalFunctions::RegisterPlayerGossipEvent },           // RegisterPlayerGossipEvent(menu_id, event, function)
    { "RegisterBGEvent", &LuaGlobalFunctions::RegisterBGEvent },                               // RegisterBGEvent(event, function)

    { "ClearBattleGroundEvents", &LuaGlobalFunctions::ClearBattleGroundEvents },
    { "ClearCreatureEvents", &LuaGlobalFunctions::ClearCreatureEvents },
    { "ClearUniqueCreatureEvents", &LuaGlobalFunctions::ClearUniqueCreatureEvents },
    { "ClearCreatureGossipEvents", &LuaGlobalFunctions::ClearCreatureGossipEvents },
    { "ClearGameObjectEvents", &LuaGlobalFunctions::ClearGameObjectEvents },
    { "ClearGameObjectGossipEvents", &LuaGlobalFunctions::ClearGameObjectGossipEvents },
    { "ClearGroupEvents", &LuaGlobalFunctions::ClearGroupEvents },
    { "ClearGuildEvents", &LuaGlobalFunctions::ClearGuildEvents },
    { "ClearItemEvents", &LuaGlobalFunctions::ClearItemEvents },
    { "ClearItemGossipEvents", &LuaGlobalFunctions::ClearItemGossipEvents },
    { "ClearPacketEvents", &LuaGlobalFunctions::ClearPacketEvents },
    { "ClearPlayerEvents", &LuaGlobalFunctions::ClearPlayerEvents },
    { "ClearPlayerGossipEvents", &LuaGlobalFunctions::ClearPlayerGossipEvents },
    { "ClearServerEvents", &LuaGlobalFunctions::ClearServerEvents },

    // Getters
    { "GetLuaEngine", &LuaGlobalFunctions::GetLuaEngine },
    { "GetCoreName", &LuaGlobalFunctions::GetCoreName },
    { "GetCoreVersion", &LuaGlobalFunctions::GetCoreVersion },
    { "GetCoreExpansion", &LuaGlobalFunctions::GetCoreExpansion },
    { "GetQuest", &LuaGlobalFunctions::GetQuest },
    { "GetPlayerByGUID", &LuaGlobalFunctions::GetPlayerByGUID },
    { "GetPlayerByName", &LuaGlobalFunctions::GetPlayerByName },
    { "GetGameTime", &LuaGlobalFunctions::GetGameTime },
    { "GetPlayersInWorld", &LuaGlobalFunctions::GetPlayersInWorld },
    { "GetPlayersInMap", &LuaGlobalFunctions::GetPlayersInMap },
    { "GetGuildByName", &LuaGlobalFunctions::GetGuildByName },
    { "GetGuildByLeaderGUID", &LuaGlobalFunctions::GetGuildByLeaderGUID },
    { "GetPlayerCount", &LuaGlobalFunctions::GetPlayerCount },
    { "GetPlayerGUID", &LuaGlobalFunctions::GetPlayerGUID },
    { "GetItemGUID", &LuaGlobalFunctions::GetItemGUID },
    { "GetObjectGUID", &LuaGlobalFunctions::GetObjectGUID },
    { "GetUnitGUID", &LuaGlobalFunctions::GetUnitGUID },
    { "GetGUIDLow", &LuaGlobalFunctions::GetGUIDLow },
    { "GetGUIDType", &LuaGlobalFunctions::GetGUIDType },
    { "GetGUIDEntry", &LuaGlobalFunctions::GetGUIDEntry },
    { "GetAreaName", &LuaGlobalFunctions::GetAreaName },
    { "bit_not", &LuaGlobalFunctions::bit_not },
    { "bit_xor", &LuaGlobalFunctions::bit_xor },
    { "bit_rshift", &LuaGlobalFunctions::bit_rshift },
    { "bit_lshift", &LuaGlobalFunctions::bit_lshift },
    { "bit_or", &LuaGlobalFunctions::bit_or },
    { "bit_and", &LuaGlobalFunctions::bit_and },
    { "GetItemLink", &LuaGlobalFunctions::GetItemLink },
    { "GetMapById", &LuaGlobalFunctions::GetMapById },
    { "GetCurrTime", &LuaGlobalFunctions::GetCurrTime },
    { "GetTimeDiff", &LuaGlobalFunctions::GetTimeDiff },
    { "PrintInfo", &LuaGlobalFunctions::PrintInfo },
    { "PrintError", &LuaGlobalFunctions::PrintError },
    { "PrintDebug", &LuaGlobalFunctions::PrintDebug },

    // Boolean
    { "IsInventoryPos", &LuaGlobalFunctions::IsInventoryPos },
    { "IsEquipmentPos", &LuaGlobalFunctions::IsEquipmentPos },
    { "IsBankPos", &LuaGlobalFunctions::IsBankPos },
    { "IsBagPos", &LuaGlobalFunctions::IsBagPos },

    // Other
    { "ReloadEluna", &LuaGlobalFunctions::ReloadEluna },
    { "SendWorldMessage", &LuaGlobalFunctions::SendWorldMessage },
    { "WorldDBQuery", &LuaGlobalFunctions::WorldDBQuery },
    { "WorldDBExecute", &LuaGlobalFunctions::WorldDBExecute },
    { "CharDBQuery", &LuaGlobalFunctions::CharDBQuery },
    { "CharDBExecute", &LuaGlobalFunctions::CharDBExecute },
    { "AuthDBQuery", &LuaGlobalFunctions::AuthDBQuery },
    { "AuthDBExecute", &LuaGlobalFunctions::AuthDBExecute },
    { "CreateLuaEvent", &LuaGlobalFunctions::CreateLuaEvent },
    { "RemoveEventById", &LuaGlobalFunctions::RemoveEventById },
    { "RemoveEvents", &LuaGlobalFunctions::RemoveEvents },
    { "PerformIngameSpawn", &LuaGlobalFunctions::PerformIngameSpawn },
    { "CreatePacket", &LuaGlobalFunctions::CreatePacket },
    { "AddVendorItem", &LuaGlobalFunctions::AddVendorItem },
    { "VendorRemoveItem", &LuaGlobalFunctions::VendorRemoveItem },
    { "VendorRemoveAllItems", &LuaGlobalFunctions::VendorRemoveAllItems },
    { "Kick", &LuaGlobalFunctions::Kick },
    { "Ban", &LuaGlobalFunctions::Ban },
    { "SaveAllPlayers", &LuaGlobalFunctions::SaveAllPlayers },
    { "SendMail", &LuaGlobalFunctions::SendMail },
    { "AddTaxiPath", &LuaGlobalFunctions::AddTaxiPath },
    { "AddCorpse", &LuaGlobalFunctions::AddCorpse },
    { "RemoveCorpse", &LuaGlobalFunctions::RemoveCorpse },
    { "ConvertCorpseForPlayer", &LuaGlobalFunctions::ConvertCorpseForPlayer },
    { "RemoveOldCorpses", &LuaGlobalFunctions::RemoveOldCorpses },
    { "FindWeather", &LuaGlobalFunctions::FindWeather },
    { "AddWeather", &LuaGlobalFunctions::AddWeather },
    { "RemoveWeather", &LuaGlobalFunctions::RemoveWeather },
    { "SendFineWeatherToPlayer", &LuaGlobalFunctions::SendFineWeatherToPlayer },
    { "CreateInt64", &LuaGlobalFunctions::CreateLongLong },
    { "CreateUint64", &LuaGlobalFunctions::CreateULongLong },

    { NULL, NULL },
};

ElunaRegister<Object> ObjectMethods[] =
{
    // Getters
    { "GetEntry", &LuaObject::GetEntry },                     // :GetEntry() - Returns the object's entryId
    { "GetGUID", &LuaObject::GetGUID },                       // :GetGUID() - Returns uint64 guid as hex string
    { "GetGUIDLow", &LuaObject::GetGUIDLow },                 // :GetGUIDLow() - Returns uint32 guid (low guid) that is used in database.
    { "GetInt32Value", &LuaObject::GetInt32Value },           // :GetInt32Value(index) - returns an int value from object fields
    { "GetUInt32Value", &LuaObject::GetUInt32Value },         // :GetUInt32Value(index) - returns an uint value from object fields
    { "GetFloatValue", &LuaObject::GetFloatValue },           // :GetFloatValue(index) - returns a float value from object fields
    { "GetByteValue", &LuaObject::GetByteValue },             // :GetByteValue(index, offset) - returns a byte value from object fields
    { "GetUInt16Value", &LuaObject::GetUInt16Value },         // :GetUInt16Value(index, offset) - returns a uint16 value from object fields
    { "GetUInt64Value", &LuaObject::GetUInt64Value },         // :GetUInt64Value(index) - returns a uint64 value from object fields
    { "GetScale", &LuaObject::GetScale },                     // :GetScale()
    { "GetTypeId", &LuaObject::GetTypeId },                   // :GetTypeId() - Returns the object's typeId

    // Setters
    { "SetInt32Value", &LuaObject::SetInt32Value },           // :SetInt32Value(index, value) - Sets an int value for the object
    { "SetUInt32Value", &LuaObject::SetUInt32Value },         // :SetUInt32Value(index, value) - Sets an uint value for the object
    { "SetFloatValue", &LuaObject::SetFloatValue },           // :SetFloatValue(index, value) - Sets a float value for the object
    { "SetByteValue", &LuaObject::SetByteValue },             // :SetByteValue(index, offset, value) - Sets a byte value for the object
    { "SetUInt16Value", &LuaObject::SetUInt16Value },         // :SetUInt16Value(index, offset, value) - Sets an uint16 value for the object
    { "SetInt16Value", &LuaObject::SetInt16Value },           // :SetInt16Value(index, offset, value) - Sets an int16 value for the object
    { "SetUInt64Value", &LuaObject::SetUInt64Value },         // :SetUInt64Value(index, value) - Sets an uint64 value for the object
    { "SetScale", &LuaObject::SetScale },                     // :SetScale(scale)
    { "SetFlag", &LuaObject::SetFlag },                       // :SetFlag(index, flag)

    // Boolean
    { "IsInWorld", &LuaObject::IsInWorld },                   // :IsInWorld() - Returns if the object is in world
    { "HasFlag", &LuaObject::HasFlag },                       // :HasFlag(index, flag)

    // Other
    { "ToGameObject", &LuaObject::ToGameObject },             // :ToGameObject()
    { "ToUnit", &LuaObject::ToUnit },                         // :ToUnit()
    { "ToCreature", &LuaObject::ToCreature },                 // :ToCreature()
    { "ToPlayer", &LuaObject::ToPlayer },                     // :ToPlayer()
    { "ToCorpse", &LuaObject::ToCorpse },                     // :ToCorpse()
    { "RemoveFlag", &LuaObject::RemoveFlag },                 // :RemoveFlag(index, flag)

    { NULL, NULL },
};

ElunaRegister<WorldObject> WorldObjectMethods[] =
{
    // Getters
    { "GetName", &LuaWorldObject::GetName },                              // :GetName()
    { "GetMap", &LuaWorldObject::GetMap },                                // :GetMap() - Returns the WorldObject's current map object
#if (!defined(TBC) && !defined(CLASSIC))
    { "GetPhaseMask", &LuaWorldObject::GetPhaseMask },                    // :GetPhaseMask()
#endif
    { "GetInstanceId", &LuaWorldObject::GetInstanceId },                  // :GetInstanceId()
    { "GetAreaId", &LuaWorldObject::GetAreaId },                          // :GetAreaId()
    { "GetZoneId", &LuaWorldObject::GetZoneId },                          // :GetZoneId()
    { "GetMapId", &LuaWorldObject::GetMapId },                            // :GetMapId() - Returns the WorldObject's current map ID
    { "GetX", &LuaWorldObject::GetX },                                    // :GetX()
    { "GetY", &LuaWorldObject::GetY },                                    // :GetY()
    { "GetZ", &LuaWorldObject::GetZ },                                    // :GetZ()
    { "GetO", &LuaWorldObject::GetO },                                    // :GetO()
    { "GetLocation", &LuaWorldObject::GetLocation },                      // :GetLocation() - returns X, Y, Z and O co - ords (in that order)
    { "GetPlayersInRange", &LuaWorldObject::GetPlayersInRange },          // :GetPlayersInRange([range]) - Returns a table with players in range of the WorldObject.
    { "GetCreaturesInRange", &LuaWorldObject::GetCreaturesInRange },      // :GetCreaturesInRange([range, entry]) - Returns a table with creatures of given entry in range of the WorldObject.
    { "GetGameObjectsInRange", &LuaWorldObject::GetGameObjectsInRange },  // :GetGameObjectsInRange([range, entry]) - Returns a table with gameobjects of given entry in range of the WorldObject.
    { "GetNearestPlayer", &LuaWorldObject::GetNearestPlayer },            // :GetNearestPlayer([range]) - Returns nearest player in sight or given range.
    { "GetNearestGameObject", &LuaWorldObject::GetNearestGameObject },    // :GetNearestGameObject([range, entry]) - Returns nearest gameobject with given entry in sight or given range entry can be 0 or nil for any.
    { "GetNearestCreature", &LuaWorldObject::GetNearestCreature },        // :GetNearestCreature([range, entry]) - Returns nearest creature with given entry in sight or given range entry can be 0 or nil for any.
    { "GetNearObject", &LuaWorldObject::GetNearObject },
    { "GetNearObjects", &LuaWorldObject::GetNearObjects },
    { "GetDistance", &LuaWorldObject::GetDistance },                      // :GetDistance(WorldObject or x, y, z) - Returns the distance between 2 objects or location
    { "GetRelativePoint", &LuaWorldObject::GetRelativePoint },            // :GetRelativePoint(dist, rad) - Returns the x, y and z of a point dist away from worldobject.
    { "GetAngle", &LuaWorldObject::GetAngle },                            // :GetAngle(WorldObject or x, y) - Returns angle between world object and target or x and y coords.

    // Boolean
    { "IsWithinLoS", &LuaWorldObject::IsWithinLoS },

    // Other
    { "SummonGameObject", &LuaWorldObject::SummonGameObject },            // :SummonGameObject(entry, x, y, z, o[, respawnDelay]) - Spawns an object to location. Returns the object or nil
    { "SpawnCreature", &LuaWorldObject::SpawnCreature },                  // :SpawnCreature(entry, x, y, z, o[, spawnType, despawnDelay]) - Spawns a creature to location that despawns after given time (0 for infinite). Returns the creature or nil
    { "SendPacket", &LuaWorldObject::SendPacket },                        // :SendPacket(packet) - Sends a specified packet to everyone around
    { "RegisterEvent", &LuaWorldObject::RegisterEvent },
    { "RemoveEventById", &LuaWorldObject::RemoveEventById },
    { "RemoveEvents", &LuaWorldObject::RemoveEvents },

    { NULL, NULL },
};

ElunaRegister<Unit> UnitMethods[] =
{
    // Getters
    { "GetLevel", &LuaUnit::GetLevel },                                   // :GetLevel()
    { "GetHealth", &LuaUnit::GetHealth },                                 // :GetHealth()
    { "GetDisplayId", &LuaUnit::GetDisplayId },                           // :GetDisplayId()
    { "GetNativeDisplayId", &LuaUnit::GetNativeDisplayId },               // :GetNativeDisplayId()
    { "GetPower", &LuaUnit::GetPower },                                   // :GetPower([type]) - returns power for power type. type can be omitted
    { "GetMaxPower", &LuaUnit::GetMaxPower },                             // :GetMaxPower([type]) - returns max power for power type. type can be omitted
    { "GetPowerType", &LuaUnit::GetPowerType },                           // :GetPowerType() - Returns the power type tye unit uses
    { "GetMaxHealth", &LuaUnit::GetMaxHealth },                           // :GetMaxHealth()
    { "GetHealthPct", &LuaUnit::GetHealthPct },                           // :GetHealthPct()
    { "GetPowerPct", &LuaUnit::GetPowerPct },                             // :GetPowerPct([type]) - returns power percent for power type. type can be omitted
    { "GetGender", &LuaUnit::GetGender },                                 // :GetGender() - returns the gender where male = 0 female = 1
    { "GetRace", &LuaUnit::GetRace },                                     // :GetRace()
    { "GetClass", &LuaUnit::GetClass },                                   // :GetClass()
    { "GetRaceAsString", &LuaUnit::GetRaceAsString },                     // :GetRaceAsString([locale])
    { "GetClassAsString", &LuaUnit::GetClassAsString },                   // :GetClassAsString([locale])
    { "GetAura", &LuaUnit::GetAura },                                     // :GetAura(spellID) - returns aura object
    { "GetCombatTime", &LuaUnit::GetCombatTime },                         // :GetCombatTime() - Returns how long the unit has been in combat
    { "GetFaction", &LuaUnit::GetFaction },                               // :GetFaction() - Returns the unit's factionId
    { "GetCurrentSpell", &LuaUnit::GetCurrentSpell },                     // :GetCurrentSpell(type) - Returns the currently casted spell of given type if any
    { "GetCreatureType", &LuaUnit::GetCreatureType },                     // :GetCreatureType() - Returns the unit's type
    { "GetMountId", &LuaUnit::GetMountId },                               // :GetMountId()
    { "GetOwner", &LuaUnit::GetOwner },                                   // :GetOwner() - Returns the owner
    { "GetFriendlyUnitsInRange", &LuaUnit::GetFriendlyUnitsInRange },     // :GetFriendlyUnitsInRange([range]) - Returns a list of friendly units in range, can return nil
    { "GetUnfriendlyUnitsInRange", &LuaUnit::GetUnfriendlyUnitsInRange }, // :GetUnfriendlyUnitsInRange([range]) - Returns a list of unfriendly units in range, can return nil
    { "GetOwnerGUID", &LuaUnit::GetOwnerGUID },                           // :GetOwnerGUID() - Returns the UNIT_FIELD_SUMMONEDBY owner
    { "GetCreatorGUID", &LuaUnit::GetCreatorGUID },                       // :GetCreatorGUID() - Returns the UNIT_FIELD_CREATEDBY creator
    { "GetMinionGUID", &LuaUnit::GetPetGUID },                            // :GetMinionGUID() - Decapreted. GetMinionGUID is same as GetPetGUID
    { "GetCharmerGUID", &LuaUnit::GetCharmerGUID },                       // :GetCharmerGUID() - Returns the UNIT_FIELD_CHARMEDBY charmer
    { "GetCharmGUID", &LuaUnit::GetCharmGUID },                           // :GetCharmGUID() - Returns the unit's UNIT_FIELD_CHARM guid
    { "GetPetGUID", &LuaUnit::GetPetGUID },                               // :GetPetGUID() - Returns the unit's pet GUID
#if (!defined(TBC) && !defined(CLASSIC))
    { "GetCritterGUID", &LuaUnit::GetCritterGUID },                       // :GetCritterGUID() - Returns the critter's GUID
#endif
    { "GetControllerGUID", &LuaUnit::GetControllerGUID },                 // :GetControllerGUID() - Returns the Charmer or Owner GUID
    { "GetControllerGUIDS", &LuaUnit::GetControllerGUIDS },               // :GetControllerGUIDS() - Returns the charmer, owner or unit's own GUID
    { "GetStandState", &LuaUnit::GetStandState },                         // :GetStandState() - Returns the unit's stand state
    { "GetVictim", &LuaUnit::GetVictim },                                 // :GetVictim() - Returns creature's current target
    { "GetSpeed", &LuaUnit::GetSpeed },                                   // :GetSpeed(movementType) - Returns the unit's speed
    { "GetStat", &LuaUnit::GetStat },                                     // :GetStat(stat)
    { "GetBaseSpellPower", &LuaUnit::GetBaseSpellPower },                 // :GetBaseSpellPower()
#if (!defined(TBC) && !defined(CLASSIC))
    { "GetVehicleKit", &LuaUnit::GetVehicleKit },                         // :GetVehicleKit() - Gets unit's Vehicle kit if the unit is a vehicle
    // {"GetVehicle", &LuaUnit::GetVehicle},                            // :GetVehicle() - Gets the Vehicle kit of the vehicle the unit is on
#endif
#ifdef MANGOS
    { "GetMovementType", &LuaUnit::GetMovementType },
#endif

    // Setters
    { "SetFaction", &LuaUnit::SetFaction },                   // :SetFaction(factionId) - Sets the unit's faction
    { "SetLevel", &LuaUnit::SetLevel },                       // :SetLevel(amount)
    { "SetHealth", &LuaUnit::SetHealth },                     // :SetHealth(amount)
    { "SetMaxHealth", &LuaUnit::SetMaxHealth },               // :SetMaxHealth(amount)
    { "SetPower", &LuaUnit::SetPower },                       // :SetPower([type,] amount)
    { "SetMaxPower", &LuaUnit::SetMaxPower },                 // :SetMaxPower([type,] amount)
    { "SetPowerType", &LuaUnit::SetPowerType },               // :SetPowerType(type)
    { "SetDisplayId", &LuaUnit::SetDisplayId },               // :SetDisplayId(id)
    { "SetNativeDisplayId", &LuaUnit::SetNativeDisplayId },   // :SetNativeDisplayId(id)
    { "SetFacing", &LuaUnit::SetFacing },                     // :SetFacing(o) - Sets the Unit facing / orientation to arg
    { "SetFacingToObject", &LuaUnit::SetFacingToObject },     // :SetFacingToObject(worldObject) - Sets the Unit facing / orientation towards the WorldObject
#if (!defined(TBC) && !defined(CLASSIC))
    { "SetPhaseMask", &LuaUnit::SetPhaseMask },               // :SetPhaseMask(Phase[, update]) - Sets the phase of the unit
#endif
    { "SetSpeed", &LuaUnit::SetSpeed },                       // :SetSpeed(type, speed[, forced]) - Sets speed for the movement type (0 = walk, 1 = run ..)
    // {"SetStunned", &LuaUnit::SetStunned},                // :SetStunned([enable]) - Stuns or removes stun
    {"SetRooted", &LuaUnit::SetRooted},                       // :SetRooted([enable]) - Roots or removes root
    {"SetConfused", &LuaUnit::SetConfused},                   // :SetConfused([enable]) - Sets confused or removes confusion
    {"SetFeared", &LuaUnit::SetFeared},                       // :SetFeared([enable]) - Fears or removes fear
    { "SetPvP", &LuaUnit::SetPvP },                           // :SetPvP([apply]) - Sets the units PvP on or off
#if (!defined(TBC) && !defined(CLASSIC))
    { "SetFFA", &LuaUnit::SetFFA },                           // :SetFFA([apply]) - Sets the units FFA tag on or off
    { "SetSanctuary", &LuaUnit::SetSanctuary },               // :SetSanctuary([apply]) - Enables or disables units sanctuary flag
#endif
    // {"SetCanFly", &LuaUnit::SetCanFly},                  // :SetCanFly(apply)
    // {"SetVisible", &LuaUnit::SetVisible},                // :SetVisible(x)
    { "SetOwnerGUID", &LuaUnit::SetOwnerGUID },               // :SetOwnerGUID(guid) - Sets the guid of the owner
    { "SetName", &LuaUnit::SetName },                         // :SetName(name) - Sets the unit's name
    { "SetSheath", &LuaUnit::SetSheath },                     // :SetSheath(SheathState) - Sets unit's sheathstate
    { "SetCreatorGUID", &LuaUnit::SetCreatorGUID },           // :SetOwnerGUID(uint64 ownerGUID) - Sets the owner's guid of a summoned creature, etc
    { "SetMinionGUID", &LuaUnit::SetPetGUID },                // Decapreted. Same as SetPetGUID
    { "SetCharmerGUID", &LuaUnit::SetCharmerGUID },           // :SetCharmerGUID(uint64 ownerGUID) - Sets the UNIT_FIELD_CHARMEDBY charmer GUID
    { "SetPetGUID", &LuaUnit::SetPetGUID },                   // :SetPetGUID(uint64 guid) - Sets the pet's guid
#if (!defined(TBC) && !defined(CLASSIC))
    { "SetCritterGUID", &LuaUnit::SetCritterGUID },           // :SetCritterGUID(uint64 guid) - Sets the critter's guid
#endif
    { "SetWaterWalk", &LuaUnit::SetWaterWalk },               // :SetWaterWalk([enable]) - Sets WaterWalk on or off
    { "SetStandState", &LuaUnit::SetStandState },             // :SetStandState(state) - Sets the stand state (Stand, Kneel, sleep, etc) of the unit

    // Boolean
    { "IsAlive", &LuaUnit::IsAlive },                                 // :IsAlive()
    { "IsDead", &LuaUnit::IsDead },                                   // :IsDead() - Returns true if the unit is dead, false if they are alive
    { "IsDying", &LuaUnit::IsDying },                                 // :IsDying() - Returns true if the unit death state is JUST_DIED.
    { "IsPvPFlagged", &LuaUnit::IsPvPFlagged },                       // :IsPvPFlagged()
    { "IsInCombat", &LuaUnit::IsInCombat },                           // :IsInCombat()
    { "IsBanker", &LuaUnit::IsBanker },                               // :IsBanker() - Returns true if the unit is a banker, false if not
    { "IsBattleMaster", &LuaUnit::IsBattleMaster },                   // :IsBattleMaster() - Returns true if the unit is a battle master, false if not
    { "IsCharmed", &LuaUnit::IsCharmed },                             // :IsCharmed() - Returns true if the unit is charmed, false if not
    { "IsArmorer", &LuaUnit::IsArmorer },                             // :IsArmorer() - Returns true if the unit is an Armorer, false if not
    { "IsAttackingPlayer", &LuaUnit::IsAttackingPlayer },             // :IsAttackingPlayer() - Returns true if the unit is attacking a player, false if not
    { "IsInWater", &LuaUnit::IsInWater },                             // :IsInWater() - Returns true if the unit is in water
    { "IsUnderWater", &LuaUnit::IsUnderWater },                       // :IsUnderWater() - Returns true if the unit is under water
    { "IsAuctioneer", &LuaUnit::IsAuctioneer },                       // :IsAuctioneer()
    { "IsGuildMaster", &LuaUnit::IsGuildMaster },                     // :IsGuildMaster()
    { "IsInnkeeper", &LuaUnit::IsInnkeeper },                         // :IsInnkeeper()
    { "IsTrainer", &LuaUnit::IsTrainer },                             // :IsTrainer()
    { "IsGossip", &LuaUnit::IsGossip },                               // :IsGossip()
    { "IsTaxi", &LuaUnit::IsTaxi },                                   // :IsTaxi()
    { "IsSpiritHealer", &LuaUnit::IsSpiritHealer },                   // :IsSpiritHealer()
    { "IsSpiritGuide", &LuaUnit::IsSpiritGuide },                     // :IsSpiritGuide()
    { "IsTabardDesigner", &LuaUnit::IsTabardDesigner },               // :IsTabardDesigner()
    { "IsServiceProvider", &LuaUnit::IsServiceProvider },             // :IsServiceProvider()
    { "IsSpiritService", &LuaUnit::IsSpiritService },                 // :IsSpiritService()
    { "HealthBelowPct", &LuaUnit::HealthBelowPct },                   // :HealthBelowPct(int32 pct)
    { "HealthAbovePct", &LuaUnit::HealthAbovePct },                   // :HealthAbovePct(int32 pct)
    { "IsMounted", &LuaUnit::IsMounted },                             // :IsMounted()
    { "AttackStop", &LuaUnit::AttackStop },                           // :AttackStop()
    { "Attack", &LuaUnit::Attack },                                   // :Attack(who[, meleeAttack])
    // {"IsVisible", &LuaUnit::IsVisible},                          // :IsVisible()
    // {"IsMoving", &LuaUnit::IsMoving},                            // :IsMoving()
    // {"IsFlying", &LuaUnit::IsFlying},                            // :IsFlying()
    { "IsStopped", &LuaUnit::IsStopped },                             // :IsStopped()
    { "HasUnitState", &LuaUnit::HasUnitState },                       // :HasUnitState(state) - state from UnitState enum
    { "IsQuestGiver", &LuaUnit::IsQuestGiver },                       // :IsQuestGiver() - Returns true if the unit is a quest giver, false if not
    { "IsWithinDistInMap", &LuaUnit::IsWithinDistInMap },             // :IsWithinDistInMap(worldObject, radius) - Returns if the unit is within distance in map of the worldObject
    { "IsInAccessiblePlaceFor", &LuaUnit::IsInAccessiblePlaceFor },   // :IsInAccessiblePlaceFor(creature) - Returns if the unit is in an accessible place for the specified creature
    { "IsVendor", &LuaUnit::IsVendor },                               // :IsVendor() - Returns if the unit is a vendor or not
    { "IsRooted", &LuaUnit::IsRooted },                               // :IsRooted()
    { "IsFullHealth", &LuaUnit::IsFullHealth },                       // :IsFullHealth() - Returns if the unit is full health
    { "HasAura", &LuaUnit::HasAura },                                 // :HasAura(spellId) - Returns true if the unit has the aura from the spell
    { "IsStandState", &LuaUnit::IsStandState },                       // :IsStandState() - Returns true if the unit is standing
#ifndef CLASSIC
    { "IsOnVehicle", &LuaUnit::IsOnVehicle },                         // :IsOnVehicle() - Checks if the unit is on a vehicle
#endif

    // Other
    { "AddAura", &LuaUnit::AddAura },                                 // :AddAura(spellId, target) - Adds an aura to the specified target
    { "RemoveAura", &LuaUnit::RemoveAura },                           // :RemoveAura(spellId[, casterGUID]) - Removes an aura from the unit by the spellId, casterGUID(Original caster) is optional
    { "RemoveAllAuras", &LuaUnit::RemoveAllAuras },                   // :RemoveAllAuras() - Removes all the unit's auras
    { "ClearInCombat", &LuaUnit::ClearInCombat },                     // :ClearInCombat() - Clears the unit's combat list (unit will be out of combat), resets the timer to 0, etc
    { "DeMorph", &LuaUnit::DeMorph },                                 // :DeMorph() - Sets display back to native
    { "SendUnitWhisper", &LuaUnit::SendUnitWhisper },                 // :SendUnitWhisper(msg, lang, receiver[, bossWhisper]) - Sends a whisper to the receiver
    { "SendUnitEmote", &LuaUnit::SendUnitEmote },                     // :SendUnitEmote(msg[, receiver, bossEmote]) - Sends a text emote
    { "SendUnitSay", &LuaUnit::SendUnitSay },                         // :SendUnitSay(msg, language) - Sends a "Say" message with the specified language (all languages: 0)
    { "SendUnitYell", &LuaUnit::SendUnitYell },                       // :SendUnitYell(msg, language) - Sends a "Yell" message with the specified language (all languages: 0)
    { "CastSpell", &LuaUnit::CastSpell },                             // :CastSpell(target, spellID[, triggered]) - Casts spell on target (player/npc/creature), if triggered is true then instant cast
    { "CastCustomSpell", &LuaUnit::CastCustomSpell },                 // :CastCustomSpell([Unit] target, uint32 spell, bool triggered = false, int32 bp0 = nil, int32 bp1 = nil, int32 bp2 = nil, [Item] castItem = nil, uint64 originalCaster = 0) - Casts spell on target (player/npc/creature), if triggered is true then instant cast. pb0, 1 and 2 are modifiers for the base points of the spell.
    { "CastSpellAoF", &LuaUnit::CastSpellAoF },                       // :CastSpellAoF(x, y, z, spellID[, triggered]) - Casts the spell on coordinates, if triggered is false has mana cost and cast time
    { "PlayDirectSound", &LuaUnit::PlayDirectSound },                 // :PlayDirectSound(soundId[, player]) - Unit plays soundID to player, or everyone around if no player
    { "PlayDistanceSound", &LuaUnit::PlayDistanceSound },             // :PlayDistanceSound(soundId[, player]) - Unit plays soundID to player, or everyone around if no player. The sound fades the further you are
    { "Kill", &LuaUnit::Kill },                                       // :Kill(target, durabilityLoss) - Unit kills the target. Durabilityloss is true by default
    { "StopSpellCast", &LuaUnit::StopSpellCast },                     // :StopSpellCast([spellId]) - Stops the unit from casting a spell. If a spellId is defined, it will stop that unit from casting that spell
    { "InterruptSpell", &LuaUnit::InterruptSpell },                   // :InterruptSpell(spellType[, delayed]) - Interrupts the unit's spell by the spellType. If delayed is true it will skip if the spell is delayed.
    { "SendChatMessageToPlayer", &LuaUnit::SendChatMessageToPlayer }, // :SendChatMessageToPlayer(type, lang, msg, target) - Unit sends a chat message to the given target player
    { "Emote", &LuaUnit::Emote },                                     // :Emote(emote)
    { "CountPctFromCurHealth", &LuaUnit::CountPctFromCurHealth },     // :CountPctFromCurHealth(int32 pct)
    { "CountPctFromMaxHealth", &LuaUnit::CountPctFromMaxHealth },     // :CountPctFromMaxHealth()
    { "Dismount", &LuaUnit::Dismount },                               // :Dismount() - Dismounts the unit.
    { "Mount", &LuaUnit::Mount },                                     // :Mount(displayId) - Mounts the unit on the specified displayId.
    // {"RestoreDisplayId", &LuaUnit::RestoreDisplayId},            // :RestoreDisplayId()
    // {"RestoreFaction", &LuaUnit::RestoreFaction},                // :RestoreFaction()
    // {"RemoveBindSightAuras", &LuaUnit::RemoveBindSightAuras},    // :RemoveBindSightAuras()
    // {"RemoveCharmAuras", &LuaUnit::RemoveCharmAuras},            // :RemoveCharmAuras()
    { "ClearThreatList", &LuaUnit::ClearThreatList },                 // :ClearThreatList()
    { "ClearUnitState", &LuaUnit::ClearUnitState },                   // :ClearUnitState(state)
    { "AddUnitState", &LuaUnit::AddUnitState },                       // :AddUnitState(state)
    // {"DisableMelee", &LuaUnit::DisableMelee},                    // :DisableMelee([disable]) - if true, enables
    // {"SummonGuardian", &LuaUnit::SummonGuardian},                // :SummonGuardian(entry, x, y, z, o[, duration]) - summons a guardian to location. Scales with summoner, is friendly to him and guards him.
    { "NearTeleport", &LuaUnit::NearTeleport },                       // :NearTeleport(x, y, z, o) - Teleports to give coordinates. Does not leave combat or unsummon pet.
    { "MoveIdle", &LuaUnit::MoveIdle },                               // :MoveIdle()
    { "MoveRandom", &LuaUnit::MoveRandom },                           // :MoveRandom(radius)
    { "MoveHome", &LuaUnit::MoveHome },                               // :MoveHome()
    { "MoveFollow", &LuaUnit::MoveFollow },                           // :MoveFollow(target[, dist, angle])
    { "MoveChase", &LuaUnit::MoveChase },                             // :MoveChase(target[, dist, angle])
    { "MoveConfused", &LuaUnit::MoveConfused },                       // :MoveConfused()
    { "MoveFleeing", &LuaUnit::MoveFleeing },                         // :MoveFleeing(enemy[, time])
    { "MoveTo", &LuaUnit::MoveTo },                                   // :MoveTo(id, x, y, z[, genPath]) - Moves to point. id is sent to WP reach hook. genPath defaults to true
#if (!defined(TBC) && !defined(CLASSIC))
    { "MoveJump", &LuaUnit::MoveJump },                               // :MoveJump(x, y, z, zSpeed, maxHeight, id)
#endif
    { "MoveStop", &LuaUnit::MoveStop },                               // :MoveStop()
    { "MoveExpire", &LuaUnit::MoveExpire },                           // :MoveExpire([reset])
    { "MoveClear", &LuaUnit::MoveClear },                             // :MoveClear([reset])
    { "DealDamage", &LuaUnit::DealDamage },                           // :DealDamage(target, amount[, durabilityloss]) - Deals damage to target, durabilityloss is true by default
    { "DealHeal", &LuaUnit::DealHeal },                               // :DealDamage(target, amount, spell[, critical]) - Heals target by given amount. This will be logged as being healed by spell as critical if true.
    { "AddThreat", &LuaUnit::AddThreat },

    { NULL, NULL },
};

ElunaRegister<Player> PlayerMethods[] =
{
    // Getters
    { "GetSelection", &LuaPlayer::GetSelection },                                 // :GetSelection()
    { "GetGMRank", &LuaPlayer::GetGMRank },                                       // :GetSecurity()
    { "GetGuildId", &LuaPlayer::GetGuildId },                                     // :GetGuildId() - nil on no guild
    { "GetCoinage", &LuaPlayer::GetCoinage },                                     // :GetCoinage()
    { "GetTeam", &LuaPlayer::GetTeam },                                           // :GetTeam() - returns the player's team. 0 for ally, 1 for horde
    { "GetItemCount", &LuaPlayer::GetItemCount },                                 // :GetItemCount(item_id[, check_bank])
    { "GetGroup", &LuaPlayer::GetGroup },                                         // :GetGroup()
    { "GetGuild", &LuaPlayer::GetGuild },                                         // :GetGuild()
    { "GetAccountId", &LuaPlayer::GetAccountId },                                 // :GetAccountId()
    { "GetAccountName", &LuaPlayer::GetAccountName },                             // :GetAccountName()
#ifndef CATA
#ifndef CLASSIC
    { "GetArenaPoints", &LuaPlayer::GetArenaPoints },                             // :GetArenaPoints()
    { "GetHonorPoints", &LuaPlayer::GetHonorPoints },                             // :GetHonorPoints()
#endif
#endif
    { "GetLifetimeKills", &LuaPlayer::GetLifetimeKills },                         // :GetLifetimeKills() - Returns the player's lifetime (honorable) kills
    { "GetPlayerIP", &LuaPlayer::GetPlayerIP },                                   // :GetPlayerIP() - Returns the player's IP Address
    { "GetLevelPlayedTime", &LuaPlayer::GetLevelPlayedTime },                     // :GetLevelPlayedTime() - Returns the player's played time at that level
    { "GetTotalPlayedTime", &LuaPlayer::GetTotalPlayedTime },                     // :GetTotalPlayedTime() - Returns the total played time of that player
    { "GetItemByPos", &LuaPlayer::GetItemByPos },                                 // :GetItemByPos(bag, slot) - Returns item in given slot in a bag (bag: 19-22 slot: 0-35) or inventory (bag: 255 slot : 0-38)
    { "GetItemByEntry", &LuaPlayer::GetItemByEntry },                             // :GetItemByEntry(entry) - Gets an item if the player has it
    { "GetItemByGUID", &LuaPlayer::GetItemByGUID },
    { "GetReputation", &LuaPlayer::GetReputation },                               // :GetReputation(faction) - Gets player's reputation with given faction
    { "GetEquippedItemBySlot", &LuaPlayer::GetEquippedItemBySlot },               // :GetEquippedItemBySlot(slotId) - Returns equipped item by slot
    { "GetQuestLevel", &LuaPlayer::GetQuestLevel },                               // :GetQuestLevel(quest) - Returns quest's level
    { "GetChatTag", &LuaPlayer::GetChatTag },                                     // :GetChatTag() - Returns player chat tag ID
    { "GetRestBonus", &LuaPlayer::GetRestBonus },                                 // :GetRestBonus() - Gets player's rest bonus
    { "GetRestType", &LuaPlayer::GetRestType },                                   // :GetRestType() - Returns the player's rest type
#ifdef WOTLK
    { "GetPhaseMaskForSpawn", &LuaPlayer::GetPhaseMaskForSpawn },                 // :GetPhaseMaskForSpawn() - Gets the real phasemask for spawning things. Used if the player is in GM mode
#endif
    { "GetReqKillOrCastCurrentCount", &LuaPlayer::GetReqKillOrCastCurrentCount }, // :GetReqKillOrCastCurrentCount(questId, entry) - Gets the objective (kill or cast) current count done
    { "GetQuestStatus", &LuaPlayer::GetQuestStatus },                             // :GetQuestStatus(entry) - Gets the quest's status
    { "GetInGameTime", &LuaPlayer::GetInGameTime },                               // :GetInGameTime() - Returns player's ingame time
    { "GetComboPoints", &LuaPlayer::GetComboPoints },                             // :GetComboPoints() - Returns player's combo points
    { "GetComboTarget", &LuaPlayer::GetComboTarget },                             // :GetComboTarget() - Returns the player's combo target
    { "GetGuildName", &LuaPlayer::GetGuildName },                                 // :GetGuildName() - Returns player's guild's name or nil
    { "GetFreeTalentPoints", &LuaPlayer::GetFreeTalentPoints },                   // :GetFreeTalentPoints() - Returns the amount of unused talent points
#if (!defined(TBC) && !defined(CLASSIC))
    { "GetActiveSpec", &LuaPlayer::GetActiveSpec },                               // :GetActiveSpec() - Returns the active specID
    { "GetSpecsCount", &LuaPlayer::GetSpecsCount },                               // :GetSpecsCount() - Returns the player's spec count
#endif
    { "GetSpellCooldownDelay", &LuaPlayer::GetSpellCooldownDelay },               // :GetSpellCooldownDelay(spellId) - Returns the spell's cooldown
    { "GetGuildRank", &LuaPlayer::GetGuildRank },                                 // :GetGuildRank() - Gets the player's guild rank
    { "GetDifficulty", &LuaPlayer::GetDifficulty },                               // :GetDifficulty([isRaid]) - Returns the current difficulty
    { "GetHealthBonusFromStamina", &LuaPlayer::GetHealthBonusFromStamina },       // :GetHealthBonusFromStamina() - Returns the HP bonus from stamina
    { "GetManaBonusFromIntellect", &LuaPlayer::GetManaBonusFromIntellect },       // :GetManaBonusFromIntellect() - Returns the mana bonus from intellect
    { "GetMaxSkillValue", &LuaPlayer::GetMaxSkillValue },                         // :GetMaxSkillValue(skill) - Gets max skill value for the given skill
    { "GetPureMaxSkillValue", &LuaPlayer::GetPureMaxSkillValue },                 // :GetPureMaxSkillValue(skill) - Gets max base skill value
    { "GetSkillValue", &LuaPlayer::GetSkillValue },                               // :GetSkillValue(skill) - Gets current skill value
    { "GetBaseSkillValue", &LuaPlayer::GetBaseSkillValue },                       // :GetBaseSkillValue(skill) - Gets current base skill value (no temp bonus)
    { "GetPureSkillValue", &LuaPlayer::GetPureSkillValue },                       // :GetPureSkillValue(skill) - Gets current base skill value (no bonuses)
    { "GetSkillPermBonusValue", &LuaPlayer::GetSkillPermBonusValue },             // :GetSkillPermBonusValue(skill) - Returns current permanent bonus
    { "GetSkillTempBonusValue", &LuaPlayer::GetSkillTempBonusValue },             // :GetSkillTempBonusValue(skill) - Returns current temp bonus
    { "GetReputationRank", &LuaPlayer::GetReputationRank },                       // :GetReputationRank(faction) - Returns the reputation rank with given faction
    { "GetSpellCooldowns", &LuaPlayer::GetSpellCooldowns },                       // :GetSpellCooldowns() - Gets a table where spellIDs are the keys and values are cooldowns
    { "GetDrunkValue", &LuaPlayer::GetDrunkValue },                               // :GetDrunkValue() - Returns the current drunkness value
    { "GetBattlegroundId", &LuaPlayer::GetBattlegroundId },                       // :GetBattlegroundId() - Returns the player's current battleground ID
    { "GetBattlegroundTypeId", &LuaPlayer::GetBattlegroundTypeId },               // :GetBattlegroundTypeId() - Returns the player's current battleground type ID
    { "GetXPRestBonus", &LuaPlayer::GetXPRestBonus },                             // :GetXPRestBonus(xp) - Returns the rested bonus XP from given XP
    { "GetRestTime", &LuaPlayer::GetRestTime },                                   // :GetRestTime() - Returns the timed rested
    { "GetGroupInvite", &LuaPlayer::GetGroupInvite },                             // :GetGroupInvite() - Returns the group invited to
    { "GetSubGroup", &LuaPlayer::GetSubGroup },                                   // :GetSubGroup() - Gets the player's current subgroup ID
    { "GetNextRandomRaidMember", &LuaPlayer::GetNextRandomRaidMember },           // :GetNextRandomRaidMember(radius) - Gets a random raid member in given radius
    { "GetOriginalGroup", &LuaPlayer::GetOriginalGroup },                         // :GetOriginalGroup() - Gets the original group object
    { "GetOriginalSubGroup", &LuaPlayer::GetOriginalSubGroup },                   // :GetOriginalSubGroup() - Returns the original subgroup ID
#ifdef TRINITY
    { "GetChampioningFaction", &LuaPlayer::GetChampioningFaction },               // :GetChampioningFaction() - Returns the player's championing faction
#endif
    { "GetLatency", &LuaPlayer::GetLatency },                                     // :GetLatency() - Returns player's latency
    // {"GetRecruiterId", &LuaPlayer::GetRecruiterId},                          // :GetRecruiterId() - Returns player's recruiter's ID
    { "GetDbLocaleIndex", &LuaPlayer::GetDbLocaleIndex },                         // :GetDbLocaleIndex() - Returns locale index
    { "GetDbcLocale", &LuaPlayer::GetDbcLocale },                                 // :GetDbcLocale() - Returns DBC locale
    { "GetCorpse", &LuaPlayer::GetCorpse },                                       // :GetCorpse() - Returns the player's corpse
    { "GetGossipTextId", &LuaPlayer::GetGossipTextId },                           // :GetGossipTextId(worldObject) - Returns the WorldObject's gossip textId
    { "GetQuestRewardStatus", &LuaPlayer::GetQuestRewardStatus },                 // :GetQuestRewardStatus(questId) - Returns the true/false of the quest reward status
#ifndef CATA
    { "GetShieldBlockValue", &LuaPlayer::GetShieldBlockValue },                   // :GetShieldBlockValue() - Returns block value
#endif
#ifdef CLASSIC
    { "GetHonorStoredKills", &LuaPlayer::GetHonorStoredKills },                     // :GetHonorStoredKills(on/off)
    { "GetRankPoints", &LuaPlayer::GetRankPoints },                                 // :GetRankPoints()
    { "GetHonorLastWeekStandingPos", &LuaPlayer::GetHonorLastWeekStandingPos },     // :GetHonorLastWeekStandingPos()
#endif

    // Setters
    { "AdvanceSkillsToMax", &LuaPlayer::AdvanceSkillsToMax },     // :AdvanceSkillsToMax() - Advances all currently known skills to the currently known max level
    { "AdvanceSkill", &LuaPlayer::AdvanceSkill },                 // :AdvanceSkill(skill_id, step) - Advances skill by ID and the amount(step)
    { "AdvanceAllSkills", &LuaPlayer::AdvanceAllSkills },         // :AdvanceAllSkills(value) - Advances all current skills to your input(value)
    { "AddLifetimeKills", &LuaPlayer::AddLifetimeKills },         // :AddLifetimeKills(val) - Adds lifetime (honorable) kills to your current lifetime kills
    { "SetCoinage", &LuaPlayer::SetCoinage },                     // :SetCoinage(amount) - sets plr's coinage to this
#ifndef CLASSIC
    { "SetKnownTitle", &LuaPlayer::SetKnownTitle },               // :SetKnownTitle(id)
    { "UnsetKnownTitle", &LuaPlayer::UnsetKnownTitle },           // :UnsetKnownTitle(id)
#endif
    { "SetBindPoint", &LuaPlayer::SetBindPoint },                 // :SetBindPoint(x, y, z, map, areaid) - sets home for hearthstone
#ifndef CATA
#ifndef CLASSIC
    { "SetArenaPoints", &LuaPlayer::SetArenaPoints },             // :SetArenaPoints(amount)
    { "SetHonorPoints", &LuaPlayer::SetHonorPoints },             // :SetHonorPoints(amount)
#endif
#endif
#ifdef CLASSIC
    { "SetHonorStoredKills", &LuaPlayer::SetHonorStoredKills },     // :SetHonorStoredKills(kills, [on/off])
    { "SetRankPoints", &LuaPlayer::SetRankPoints },                 // :SetRankPoints(rankPoints)
    { "SetHonorLastWeekStandingPos", &LuaPlayer::SetHonorLastWeekStandingPos }, // :SetHonorLastWeekStandingPos(standingPos)
#endif
    { "SetLifetimeKills", &LuaPlayer::SetLifetimeKills },         // :SetLifetimeKills(val) - Sets the overall lifetime (honorable) kills of the player
    { "SetGameMaster", &LuaPlayer::SetGameMaster },               // :SetGameMaster([on]) - Sets GM mode on or off
    { "SetGMChat", &LuaPlayer::SetGMChat },                       // :SetGMChat([on]) - Sets GM chat on or off
    { "SetTaxiCheat", &LuaPlayer::SetTaxiCheat },                 // :SetTaxiCheat([on]) - Sets taxi cheat on or off
    { "SetGMVisible", &LuaPlayer::SetGMVisible },                 // :SetGMVisible([on]) - Sets gm visibility on or off
    { "SetPvPDeath", &LuaPlayer::SetPvPDeath },                   // :SetPvPDeath([on]) - Sets PvP death on or off
    { "SetAcceptWhispers", &LuaPlayer::SetAcceptWhispers },       // :SetAcceptWhispers([on]) - Sets whisper accepting death on or off
    { "SetRestBonus", &LuaPlayer::SetRestBonus },                 // :SetRestBonus(bonusrate) - Sets new restbonus rate
    { "SetRestType", &LuaPlayer::SetRestType },                   // :SetRestType() - Sets rest type
    { "SetQuestStatus", &LuaPlayer::SetQuestStatus },             // :SetQuestStatus(entry, status) - Sets the quest's status
    { "SetReputation", &LuaPlayer::SetReputation },               // :SetReputation(faction, value) - Sets the faction reputation for the player
    { "SetFreeTalentPoints", &LuaPlayer::SetFreeTalentPoints },   // :SetFreeTalentPoints(points) - Sets the amount of unused talent points
    { "SetGuildRank", &LuaPlayer::SetGuildRank },                 // :SetGuildRank(rank) - Sets player's guild rank
    // {"SetMovement", &LuaPlayer::SetMovement},                // :SetMovement(type) - Sets player's movement type
    { "SetSkill", &LuaPlayer::SetSkill },                         // :SetSkill(skill, step, currVal, maxVal) - Sets the skill's boundaries and value
    { "SetFactionForRace", &LuaPlayer::SetFactionForRace },       // :SetFactionForRace(race) - Sets the faction by raceID
    { "SetDrunkValue", &LuaPlayer::SetDrunkValue },               // :SetDrunkValue(newDrunkValue) - Sets drunkness value
    { "SetRestTime", &LuaPlayer::SetRestTime },                   // :SetRestTime(value) - Sets the rested time
    { "SetAtLoginFlag", &LuaPlayer::SetAtLoginFlag },             // :SetAtLoginFlag(flag) - Adds an at login flag
    { "SetPlayerLock", &LuaPlayer::SetPlayerLock },               // :SetPlayerLock(on/off)
    { "SetGender", &LuaPlayer::SetGender },                       // :SetGender(value) - 0 = male 1 = female
    { "SetSheath", &LuaPlayer::SetSheath },                       // :SetSheath(SheathState) - Sets player's sheathstate
#ifndef TRINITY
    { "SetFFA", &LuaPlayer::SetFFA },                             // :SetFFA([apply]) - Sets the units FFA tag on or off
#endif

    // Boolean
    { "IsInGroup", &LuaPlayer::IsInGroup },                                               // :IsInGroup()
    { "IsInGuild", &LuaPlayer::IsInGuild },                                               // :IsInGuild()
    { "IsGM", &LuaPlayer::IsGM },                                                         // :IsGM()
    { "IsAlliance", &LuaPlayer::IsAlliance },                                             // :IsAlliance()
    { "IsHorde", &LuaPlayer::IsHorde },                                                   // :IsHorde()
#ifndef CLASSIC
    { "HasTitle", &LuaPlayer::HasTitle },                                                 // :HasTitle(id)
#endif
    { "HasItem", &LuaPlayer::HasItem },                                                   // :HasItem(itemId[, count, check_bank]) - Returns true if the player has the item(itemId) and specified count, else it will return false
    { "Teleport", &LuaPlayer::Teleport },                                                 // :Teleport(Map, X, Y, Z, O) - Teleports player to specified co - ordinates. Returns true if success and false if not
    { "AddItem", &LuaPlayer::AddItem },                                                   // :AddItem(id, amount) - Adds amount of item to player. Returns true if success and false if not
#ifndef CLASSIC
    { "IsInArenaTeam", &LuaPlayer::IsInArenaTeam },                                       // :IsInArenaTeam(type) - type : 0 = 2v2, 1 = 3v3, 2 = 5v5
#endif
    { "CanEquipItem", &LuaPlayer::CanEquipItem },                                         // :CanEquipItem(entry/item, slot) - Returns true if the player can equip given item/item entry
    { "IsFalling", &LuaPlayer::IsFalling },                                               // :IsFalling() - Returns true if the unit is falling
    { "ToggleAFK", &LuaPlayer::ToggleAFK },                                               // :ToggleAFK() - Toggles AFK state for player
    { "ToggleDND", &LuaPlayer::ToggleDND },                                               // :ToggleDND() - Toggles DND state for player
    { "IsAFK", &LuaPlayer::IsAFK },                                                       // :IsAFK() - Returns true if the player is afk
    { "IsDND", &LuaPlayer::IsDND },                                                       // :IsDND() - Returns true if the player is in dnd mode
    { "IsAcceptingWhispers", &LuaPlayer::IsAcceptingWhispers },                           // :IsAcceptWhispers() - Returns true if the player accepts whispers
    { "IsGMChat", &LuaPlayer::IsGMChat },                                                 // :IsGMChat() - Returns true if the player has GM chat on
    { "IsTaxiCheater", &LuaPlayer::IsTaxiCheater },                                       // :IsTaxiCheater() - Returns true if the player has taxi cheat on
    { "IsGMVisible", &LuaPlayer::IsGMVisible },                                           // :IsGMVisible() - Returns true if the player is GM visible
    { "HasQuest", &LuaPlayer::HasQuest },                                                 // :HasQuest(entry) - Returns true if player has the quest
    { "InBattlegroundQueue", &LuaPlayer::InBattlegroundQueue },                           // :InBattlegroundQueue() - Returns true if the player is in a battleground queue
    // {"IsImmuneToEnvironmentalDamage", &LuaPlayer::IsImmuneToEnvironmentalDamage},    // :IsImmuneToEnvironmentalDamage() - Returns true if the player is immune to enviromental damage
    { "CanSpeak", &LuaPlayer::CanSpeak },                                                 // :CanSpeak() - Returns true if the player can speak
    { "HasAtLoginFlag", &LuaPlayer::HasAtLoginFlag },                                     // :HasAtLoginFlag(flag) - returns true if the player has the login flag
    // {"InRandomLfgDungeon", &LuaPlayer::InRandomLfgDungeon},                          // :InRandomLfgDungeon() - Returns true if the player is in a random LFG dungeon
    // {"HasPendingBind", &LuaPlayer::HasPendingBind},                                  // :HasPendingBind() - Returns true if the player has a pending instance bind
#if (!defined(TBC) && !defined(CLASSIC))
    { "HasAchieved", &LuaPlayer::HasAchieved },                                           // :HasAchieved(achievementID) - Returns true if the player has achieved the achievement
#endif
    { "CanUninviteFromGroup", &LuaPlayer::CanUninviteFromGroup },                         // :CanUninviteFromGroup() - Returns true if the player can uninvite from group
    { "IsRested", &LuaPlayer::IsRested },                                                 // :IsRested() - Returns true if the player is rested
    // {"CanFlyInZone", &LuaPlayer::CanFlyInZone},                                      // :CanFlyInZone(mapid, zone) - Returns true if the player can fly in the area
    // {"IsNeverVisible", &LuaPlayer::IsNeverVisible},                                  // :IsNeverVisible() - Returns true if the player is never visible
    { "IsVisibleForPlayer", &LuaPlayer::IsVisibleForPlayer },                             // :IsVisibleForPlayer(player) - Returns true if the player is visible for the target player
    // {"IsUsingLfg", &LuaPlayer::IsUsingLfg},                                          // :IsUsingLfg() - Returns true if the player is using LFG
    { "HasQuestForItem", &LuaPlayer::HasQuestForItem },                                   // :HasQuestForItem(entry) - Returns true if the player has the quest for the item
    { "HasQuestForGO", &LuaPlayer::HasQuestForGO },                                       // :HasQuestForGO(entry) - Returns true if the player has the quest for the gameobject
    { "CanShareQuest", &LuaPlayer::CanShareQuest },                                       // :CanShareQuest(entry) - Returns true if the quest entry is shareable by the player
    // {"HasReceivedQuestReward", &LuaPlayer::HasReceivedQuestReward},                  // :HasReceivedQuestReward(entry) - Returns true if the player has recieved the quest's reward
#if (!defined(TBC) && !defined(CLASSIC))
    { "HasTalent", &LuaPlayer::HasTalent },                                               // :HasTalent(talentId, spec) - Returns true if the player has the talent in given spec
#endif
    { "IsInSameGroupWith", &LuaPlayer::IsInSameGroupWith },                               // :IsInSameGroupWith(player) - Returns true if the players are in the same group
    { "IsInSameRaidWith", &LuaPlayer::IsInSameRaidWith },                                 // :IsInSameRaidWith(player) - Returns true if the players are in the same raid
    { "IsGroupVisibleFor", &LuaPlayer::IsGroupVisibleFor },                               // :IsGroupVisibleFor(player) - Player is group visible for the target
    { "HasSkill", &LuaPlayer::HasSkill },                                                 // :HasSkill(skill) - Returns true if the player has the skill
    { "IsHonorOrXPTarget", &LuaPlayer::IsHonorOrXPTarget },                               // :IsHonorOrXPTarget(victim) - Returns true if the victim gives honor or XP
    { "CanParry", &LuaPlayer::CanParry },                                                 // :CanParry() - Returns true if the player can parry
    { "CanBlock", &LuaPlayer::CanBlock },                                                 // :CanBlock() - Returns true if the player can block
#if (!defined(TBC) && !defined(CLASSIC))
    { "CanTitanGrip", &LuaPlayer::CanTitanGrip },                                         // :CanTitanGrip() - Returns true if the player has titan grip
#endif
    { "InBattleground", &LuaPlayer::InBattleground },                                     // :InBattleground() - Returns true if the player is in a battleground
#ifndef CLASSIC
    { "InArena", &LuaPlayer::InArena },                                                   // :InArena() - Returns true if the player is in an arena
#endif
    // {"IsOutdoorPvPActive", &LuaPlayer::IsOutdoorPvPActive},                          // :IsOutdoorPvPActive() - Returns true if the player is outdoor pvp active
    // {"IsARecruiter", &LuaPlayer::IsARecruiter},                                      // :IsARecruiter() - Returns true if the player is a recruiter
    { "CanUseItem", &LuaPlayer::CanUseItem },                                             // :CanUseItem(item/entry) - Returns true if the player can use the item or item entry
    { "HasSpell", &LuaPlayer::HasSpell },                                                 // :HasSpell(id)
    { "HasSpellCooldown", &LuaPlayer::HasSpellCooldown },                                 // :HasSpellCooldown(spellId) - Returns true if the spell is on cooldown
    { "IsInWater", &LuaPlayer::IsInWater },                                               // :IsInWater() - Returns true if the player is in water
#ifndef CLASSIC
    { "CanFly", &LuaPlayer::CanFly },                                                     // :CanFly() - Returns true if the player can fly
#endif
    { "IsMoving", &LuaPlayer::IsMoving },                                                 // :IsMoving()
#ifndef CLASSIC
    { "IsFlying", &LuaPlayer::IsFlying },                                                 // :IsFlying()
#endif

    // Gossip
    { "GossipMenuAddItem", &LuaPlayer::GossipMenuAddItem },                               // :GossipMenuAddItem(icon, msg, sender, intid[, code, popup, money])
    { "GossipSendMenu", &LuaPlayer::GossipSendMenu },                                     // :GossipSendMenu(npc_text, unit[, menu_id]) - If unit is a player, you need to use a menu_id. menu_id is used to hook the gossip select function to the menu
    { "GossipComplete", &LuaPlayer::GossipComplete },                                     // :GossipComplete()
    { "GossipClearMenu", &LuaPlayer::GossipClearMenu },                                   // :GossipClearMenu() - Clears the gossip menu of options. Pretty much only useful with player gossip. Need to use before creating a new menu for the player

    // Other
    { "SendClearCooldowns", &LuaPlayer::SendClearCooldowns },                            // :SendClearCooldowns(spellId, (unit)target) - Clears the cooldown of the target with a specified spellId
    { "SendBroadcastMessage", &LuaPlayer::SendBroadcastMessage },                         // :SendBroadcastMessage(message)
    { "SendAreaTriggerMessage", &LuaPlayer::SendAreaTriggerMessage },                     // :SendAreaTriggerMessage(message) - Sends a yellow message in the middle of your screen
    { "SendNotification", &LuaPlayer::SendNotification },                                 // :SendNotification(message) - Sends a red message in the middle of your screen
    { "SendPacket", &LuaPlayer::SendPacket },                                             // :SendPacket(packet, selfOnly) - Sends a packet to player or everyone around also if selfOnly is false
    { "SendAddonMessage", &LuaPlayer::SendAddonMessage },                                 // :SendAddonMessage(prefix, message, channel, receiver) - Sends an addon message to the player. 
    { "SendVendorWindow", &LuaPlayer::SendVendorWindow },                                 // :SendVendorWindow(unit) - Sends the unit's vendor window to the player
    { "ModifyMoney", &LuaPlayer::ModifyMoney },                                           // :ModifyMoney(amount[, sendError]) - Modifies (does not set) money (copper count) of the player. Amount can be negative to remove copper
    { "LearnSpell", &LuaPlayer::LearnSpell },                                             // :LearnSpell(id) - learns the given spell
    { "RemoveItem", &LuaPlayer::RemoveItem },                                             // :RemoveItem(item/entry, amount) - Removes amount of item from player
    { "RemoveLifetimeKills", &LuaPlayer::RemoveLifetimeKills },                           // :RemoveLifetimeKills(val) - Removes a specified amount(val) of the player's lifetime (honorable) kills
    { "ResurrectPlayer", &LuaPlayer::ResurrectPlayer },                                   // :ResurrectPlayer([percent[, sickness(bool)]]) - Resurrects the player at percentage, player gets resurrection sickness if sickness set to true
    { "PlaySoundToPlayer", &LuaPlayer::PlaySoundToPlayer },                               // :PlaySoundToPlayer(soundId) - Plays the specified sound to the player
    { "EquipItem", &LuaPlayer::EquipItem },                                               // :EquipItem(entry/item, slot) - Equips given item or item entry for player to given slot. Returns the equipped item or nil
    { "ResetSpellCooldown", &LuaPlayer::ResetSpellCooldown },                             // :ResetSpellCooldown(spellId, update(bool~optional)) - Resets cooldown of the specified spellId. If update is true, it will send WorldPacket SMSG_CLEAR_COOLDOWN to the player, else it will just clear the spellId from m_spellCooldowns. This is true by default
    { "ResetTypeCooldowns", &LuaPlayer::ResetTypeCooldowns },                             // :ResetTypeCooldowns(category, update(bool~optional)) - Resets all cooldowns for the spell category(type). If update is true, it will send WorldPacket SMSG_CLEAR_COOLDOWN to the player, else it will just clear the spellId from m_spellCooldowns. This is true by default
    { "ResetAllCooldowns", &LuaPlayer::ResetAllCooldowns },                               // :ResetAllCooldowns() - Resets all spell cooldowns
    { "GiveLevel", &LuaPlayer::GiveLevel },                                               // :GiveLevel(level) - Gives levels to the player
    { "GiveXP", &LuaPlayer::GiveXP },                                                     // :GiveXP(xp[, victim, pureXP, triggerHook]) - Gives XP to the player. If pure is false, bonuses are count in. If triggerHook is false, GiveXp hook is not triggered.
    // {"RemovePet", &LuaPlayer::RemovePet},                                            // :RemovePet([mode, returnreagent]) - Removes the player's pet. Mode determines if the pet is saved and how
    // {"SummonPet", &LuaPlayer::SummonPet},                                            // :SummonPet(entry, x, y, z, o, petType, despwtime) - Summons a pet for the player
    { "Say", &LuaPlayer::Say },                                                           // :Say(text, lang) - The player says the text
    { "Yell", &LuaPlayer::Yell },                                                         // :Yell(text, lang) - The player yells the text
    { "TextEmote", &LuaPlayer::TextEmote },                                               // :TextEmote(text) - The player does a textemote with the text
    { "Whisper", &LuaPlayer::Whisper },                                                   // :Whisper(text, lang, receiver) - The player whispers the text to the receiver
    { "CompleteQuest", &LuaPlayer::CompleteQuest },                                       // :CompleteQuest(entry) - Completes a quest by entry
    { "IncompleteQuest", &LuaPlayer::IncompleteQuest },                                   // :IncompleteQuest(entry) - Uncompletes the quest by entry for the player
    { "FailQuest", &LuaPlayer::FailQuest },                                               // :FailQuest(entry) - Player fails the quest entry
    // {"RemoveActiveQuest", &LuaPlayer::RemoveActiveQuest},                            // :RemoveActiveQuest(entry) - Removes an active quest
    // {"RemoveRewardedQuest", &LuaPlayer::RemoveRewardedQuest},                        // :RemoveRewardedQuest(entry) - Removes a rewarded quest
    { "AreaExploredOrEventHappens", &LuaPlayer::AreaExploredOrEventHappens },             // :AreaExploredOrEventHappens(questId) - Satisfies an area or event requrement for the questId
    { "GroupEventHappens", &LuaPlayer::GroupEventHappens },                               // :GroupEventHappens(questId, worldObject) - Satisfies a group event for the questId with the world object
    { "KilledMonsterCredit", &LuaPlayer::KilledMonsterCredit },                           // :KilledMonsterCredit(entry) - Satisfies a monsterkill for the player
    // {"KilledPlayerCredit", &LuaPlayer::KilledPlayerCredit},                          // :KilledPlayerCredit() - Satisfies a player kill for the player
    // {"KillGOCredit", &LuaPlayer::KillGOCredit},                                      // :KillGOCredit(GOEntry[, GUID]) - Credits the player for destroying a GO, guid is optional
    { "TalkedToCreature", &LuaPlayer::TalkedToCreature },                                 // :TalkedToCreature(npcEntry, creature) - Satisfies creature talk objective for the player
#if (!defined(TBC) && !defined(CLASSIC))
    { "ResetPetTalents", &LuaPlayer::ResetPetTalents },                                   // :ResetPetTalents() - Resets player's pet's talents
#endif
    { "AddComboPoints", &LuaPlayer::AddComboPoints },                                     // :AddComboPoints(target, count[, spell]) - Adds combo points to the target for the player
    // {"GainSpellComboPoints", &LuaPlayer::GainSpellComboPoints},                      // :GainSpellComboPoints(amount) - Player gains spell combo points
    { "ClearComboPoints", &LuaPlayer::ClearComboPoints },                                 // :ClearComboPoints() - Clears player's combo points
    { "RemoveSpell", &LuaPlayer::RemoveSpell },                                           // :RemoveSpell(entry[, disabled, learn_low_rank]) - Removes (unlearn) the given spell
    { "ResetTalents", &LuaPlayer::ResetTalents },                                         // :ResetTalents([no_cost]) - Resets player's talents
    { "ResetTalentsCost", &LuaPlayer::ResetTalentsCost },                                 // :ResetTalentsCost() - Returns the reset talents cost
    // {"AddTalent", &LuaPlayer::AddTalent},                                            // :AddTalent(spellid, spec, learning) - Adds a talent spell for the player to given spec
    { "RemoveFromGroup", &LuaPlayer::RemoveFromGroup },                                   // :RemoveFromGroup() - Removes the player from his group
    { "KillPlayer", &LuaPlayer::KillPlayer },                                             // :KillPlayer() - Kills the player
    { "DurabilityLossAll", &LuaPlayer::DurabilityLossAll },                               // :DurabilityLossAll(percent[, inventory]) - The player's items lose durability. Inventory true by default
    { "DurabilityLoss", &LuaPlayer::DurabilityLoss },                                     // :DurabilityLoss(item, percent) - The given item loses durability
    { "DurabilityPointsLoss", &LuaPlayer::DurabilityPointsLoss },                         // :DurabilityPointsLoss(item, points) - The given item loses durability
    { "DurabilityPointsLossAll", &LuaPlayer::DurabilityPointsLossAll },                   // :DurabilityPointsLossAll(points, inventory) - Player's items lose durability
    { "DurabilityPointLossForEquipSlot", &LuaPlayer::DurabilityPointLossForEquipSlot },   // :DurabilityPointLossForEquipSlot(slot) - Causes durability loss for the item in the given slot
    { "DurabilityRepairAll", &LuaPlayer::DurabilityRepairAll },                           // :DurabilityRepairAll([has_cost, discount, guildBank]) - Repairs all durability
    { "DurabilityRepair", &LuaPlayer::DurabilityRepair },                                 // :DurabilityRepair(position[, has_cost, discount, guildBank]) - Repairs item durability of item in given position
#ifndef CATA
#ifndef CLASSIC
    { "ModifyHonorPoints", &LuaPlayer::ModifyHonorPoints },                               // :ModifyHonorPoints(amount) - Modifies the player's honor points
    { "ModifyArenaPoints", &LuaPlayer::ModifyArenaPoints },                               // :ModifyArenaPoints(amount) - Modifies the player's arena points
#endif
#endif
    { "LeaveBattleground", &LuaPlayer::LeaveBattleground },                               // :LeaveBattleground([teleToEntryPoint]) - The player leaves the battleground
    // {"BindToInstance", &LuaPlayer::BindToInstance},                                  // :BindToInstance() - Binds the player to the current instance
    { "UnbindInstance", &LuaPlayer::UnbindInstance },                                     // :UnbindInstance(map, difficulty) - Unbinds the player from an instance
    { "RemoveFromBattlegroundRaid", &LuaPlayer::RemoveFromBattlegroundRaid },             // :RemoveFromBattlegroundRaid() - Removes the player from a battleground or battlefield raid
#if (!defined(TBC) && !defined(CLASSIC))
    { "ResetAchievements", &LuaPlayer::ResetAchievements },                               // :ResetAchievements() - Resets player�s achievements
#endif
    { "KickPlayer", &LuaPlayer::KickPlayer },                                             // :KickPlayer() - Kicks player from server
    { "LogoutPlayer", &LuaPlayer::LogoutPlayer },                                         // :LogoutPlayer([save]) - Logs the player out and saves if true
    { "SendTrainerList", &LuaPlayer::SendTrainerList },                                   // :SendTrainerList(WorldObject) - Sends trainer list from object to player
    { "SendListInventory", &LuaPlayer::SendListInventory },                               // :SendListInventory(WorldObject) - Sends vendor list from object to player
    { "SendShowBank", &LuaPlayer::SendShowBank },                                         // :SendShowBank(WorldObject) - Sends bank window from object to player
    { "SendTabardVendorActivate", &LuaPlayer::SendTabardVendorActivate },                 // :SendTabardVendorActivate(WorldObject) - Sends tabard vendor window from object to player
    { "SendSpiritResurrect", &LuaPlayer::SendSpiritResurrect },                           // :SendSpiritResurrect() - Sends resurrect window to player
    { "SendTaxiMenu", &LuaPlayer::SendTaxiMenu },                                         // :SendTaxiMenu(creature) - Sends flight window to player from creature
    { "RewardQuest", &LuaPlayer::RewardQuest },                                           // :RewardQuest(entry) - Gives quest rewards for the player
    { "SendAuctionMenu", &LuaPlayer::SendAuctionMenu },                                   // :SendAuctionMenu(unit) - Sends auction window to player. Auction house is sent by object.
    { "SendShowMailBox", &LuaPlayer::SendShowMailBox },                                   // :SendShowMailBox([mailboxguid]) - Sends the mail window to player from the mailbox gameobject. The guid is required on patches below wotlk.
    { "StartTaxi", &LuaPlayer::StartTaxi },                                               // :StartTaxi(pathId) - player starts the given flight path
    { "GossipSendPOI", &LuaPlayer::GossipSendPOI },                                       // :GossipSendPOI(X, Y, Icon, Flags, Data, Name) - Sends a point of interest to the player
    { "GossipAddQuests", &LuaPlayer::GossipAddQuests },                                   // :GossipAddQuests(unit) - Adds unit's quests to player's gossip menu
    { "SendQuestTemplate", &LuaPlayer::SendQuestTemplate },                               // :SendQuestTemplate(questId, activeAccept) -- Sends quest template to player
    { "SpawnBones", &LuaPlayer::SpawnBones },                                             // :SpawnBones() - Removes the player's corpse and spawns bones
    { "RemovedInsignia", &LuaPlayer::RemovedInsignia },                                   // :RemovedInsignia(looter) - Looter removes the player's corpse, looting the player and replacing with lootable bones
    { "SendGuildInvite", &LuaPlayer::SendGuildInvite },                                   // :SendGuildInvite(player) - Sends a guild invite to the specific player
    { "CreateCorpse", &LuaPlayer::CreateCorpse },                                         // :CreateCorpse() - Creates the player's corpse
    { "Mute", &LuaPlayer::Mute },                                                         // :Mute(time[, reason]) - Mutes the player for given time in seconds.
    { "SummonPlayer", &LuaPlayer::SummonPlayer },                                         // :SummonPlayer(player, map, x, y, z, zoneId[, delay]) - Sends a popup to the player asking if he wants to be summoned if yes, teleported to coords. ZoneID defines the location name shown in the popup Delay is the time until the popup closes automatically.
    { "SaveToDB", &LuaPlayer::SaveToDB },                                                 // :SaveToDB() - Saves to database
#ifdef CLASSIC
    { "UpdateHonor", &LuaPlayer::UpdateHonor },                                             // :UpdateHonor() - Updates Player Honor
    { "ResetHonor", &LuaPlayer::ResetHonor },                                               // :ResetHonor() - Resets Player Honor
    { "ClearHonorInfo", &LuaPlayer::ClearHonorInfo },                                       // :ClearHonorInfo() - Clear Player Honor Info
#endif

    { NULL, NULL },
};

ElunaRegister<Creature> CreatureMethods[] =
{
    // Getters
    { "GetAITarget", &LuaCreature::GetAITarget },
    { "GetAITargets", &LuaCreature::GetAITargets },
    { "GetAITargetsCount", &LuaCreature::GetAITargetsCount },
    { "GetHomePosition", &LuaCreature::GetHomePosition },
    { "GetCorpseDelay", &LuaCreature::GetCorpseDelay },
    { "GetCreatureSpellCooldownDelay", &LuaCreature::GetCreatureSpellCooldownDelay },
    { "GetScriptId", &LuaCreature::GetScriptId },
    { "GetAIName", &LuaCreature::GetAIName },
    { "GetScriptName", &LuaCreature::GetScriptName },
    { "GetAttackDistance", &LuaCreature::GetAttackDistance },
    { "GetAggroRange", &LuaCreature::GetAggroRange },
    { "GetDefaultMovementType", &LuaCreature::GetDefaultMovementType },
    { "GetRespawnDelay", &LuaCreature::GetRespawnDelay },
    { "GetWanderRadius", &LuaCreature::GetWanderRadius },
    { "GetCurrentWaypointId", &LuaCreature::GetCurrentWaypointId },
#ifdef TRINITY
    { "GetWaypointPath", &LuaCreature::GetWaypointPath },
    { "GetLootMode", &LuaCreature::GetLootMode },
#endif
    { "GetLootRecipient", &LuaCreature::GetLootRecipient },
    { "GetLootRecipientGroup", &LuaCreature::GetLootRecipientGroup },
    { "GetNPCFlags", &LuaCreature::GetNPCFlags },
#ifndef CATA
    { "GetShieldBlockValue", &LuaCreature::GetShieldBlockValue },
#endif

    // Setters
    { "SetHover", &LuaCreature::SetHover },
    { "SetDisableGravity", &LuaCreature::SetDisableGravity },
    { "SetAggroEnabled", &LuaCreature::SetAggroEnabled },
    { "SetNoCallAssistance", &LuaCreature::SetNoCallAssistance },
    { "SetNoSearchAssistance", &LuaCreature::SetNoSearchAssistance },
    { "SetDefaultMovementType", &LuaCreature::SetDefaultMovementType },
    { "SetRespawnDelay", &LuaCreature::SetRespawnDelay },
    { "SetWanderRadius", &LuaCreature::SetWanderRadius },
    { "SetInCombatWithZone", &LuaCreature::SetInCombatWithZone },
    { "SetDisableReputationGain", &LuaCreature::SetDisableReputationGain },
#ifdef TRINITY
    { "SetLootMode", &LuaCreature::SetLootMode },
#endif
    { "SetNPCFlags", &LuaCreature::SetNPCFlags },
    { "SetDeathState", &LuaCreature::SetDeathState },
    { "SetWalk", &LuaCreature::SetWalk },
    { "SetHomePosition", &LuaCreature::SetHomePosition },
    { "SetEquipmentSlots", &LuaCreature::SetEquipmentSlots },

    // Booleans
    { "IsWorldBoss", &LuaCreature::IsWorldBoss },
    { "IsRacialLeader", &LuaCreature::IsRacialLeader },
    { "IsCivilian", &LuaCreature::IsCivilian },
#ifdef TRINITY
    { "IsTrigger", &LuaCreature::IsTrigger },
#endif
    { "IsGuard", &LuaCreature::IsGuard },
    { "IsElite", &LuaCreature::IsElite },
    { "IsInEvadeMode", &LuaCreature::IsInEvadeMode },
    { "HasCategoryCooldown", &LuaCreature::HasCategoryCooldown },
    { "CanWalk", &LuaCreature::CanWalk },
    { "CanSwim", &LuaCreature::CanSwim },
    { "CanAggro", &LuaCreature::CanAggro },
#ifdef TRINITY
    { "CanStartAttack", &LuaCreature::CanStartAttack },
#endif
    { "HasSearchedAssistance", &LuaCreature::HasSearchedAssistance },
    { "IsTappedBy", &LuaCreature::IsTappedBy },
    { "HasLootRecipient", &LuaCreature::HasLootRecipient },
    { "CanAssistTo", &LuaCreature::CanAssistTo },
    { "IsTargetableForAttack", &LuaCreature::IsTargetableForAttack },
    { "CanCompleteQuest", &LuaCreature::CanCompleteQuest },
    { "CanRegenerateHealth", &LuaCreature::CanRegenerateHealth },
    { "IsReputationGainDisabled", &LuaCreature::IsReputationGainDisabled },
#ifdef TRINITY
    { "IsDamageEnoughForLootingAndReward", &LuaCreature::IsDamageEnoughForLootingAndReward },
    { "HasLootMode", &LuaCreature::HasLootMode },
#endif
    { "HasSpell", &LuaCreature::HasSpell },
    { "HasQuest", &LuaCreature::HasQuest },
    { "HasSpellCooldown", &LuaCreature::HasSpellCooldown },
    { "CanFly", &LuaCreature::CanFly },

    // Other
    { "FleeToGetAssistance", &LuaCreature::FleeToGetAssistance },
    { "CallForHelp", &LuaCreature::CallForHelp },
    { "CallAssistance", &LuaCreature::CallAssistance },
    { "RemoveCorpse", &LuaCreature::RemoveCorpse },
    { "DespawnOrUnsummon", &LuaCreature::DespawnOrUnsummon },
    { "Respawn", &LuaCreature::Respawn },
    { "AttackStart", &LuaCreature::AttackStart },
#ifdef TRINITY
    { "AddLootMode", &LuaCreature::AddLootMode },
    { "ResetLootMode", &LuaCreature::ResetLootMode },
    { "RemoveLootMode", &LuaCreature::RemoveLootMode },
#endif
    { "SaveToDB", &LuaCreature::SaveToDB },
    { "SelectVictim", &LuaCreature::SelectVictim },
    { "MoveWaypoint", &LuaCreature::MoveWaypoint },
    { "UpdateEntry", &LuaCreature::UpdateEntry },

    { NULL, NULL },
};

ElunaRegister<GameObject> GameObjectMethods[] =
{
    // Getters
    { "GetDisplayId", &LuaGameObject::GetDisplayId },
    { "GetGoState", &LuaGameObject::GetGoState },
    { "GetLootState", &LuaGameObject::GetLootState },

    // Setters
    { "SetGoState", &LuaGameObject::SetGoState },
    { "SetLootState", &LuaGameObject::SetLootState },

    // Boolean
    { "IsTransport", &LuaGameObject::IsTransport },
    // {"IsDestructible", &LuaGameObject::IsDestructible},    // :IsDestructible()
    { "IsActive", &LuaGameObject::IsActive },
    { "HasQuest", &LuaGameObject::HasQuest },
    { "IsSpawned", &LuaGameObject::IsSpawned },

    // Other
    { "RemoveFromWorld", &LuaGameObject::RemoveFromWorld },
    { "UseDoorOrButton", &LuaGameObject::UseDoorOrButton },
    { "Despawn", &LuaGameObject::Despawn },
    { "Respawn", &LuaGameObject::Respawn },
    { "SaveToDB", &LuaGameObject::SaveToDB },

    { NULL, NULL },
};

ElunaRegister<Item> ItemMethods[] =
{
    // Getters
    { "GetOwnerGUID", &LuaItem::GetOwnerGUID },                   // :GetOwnerGUID() - Returns the owner's guid
    { "GetOwner", &LuaItem::GetOwner },                           // :GetOwner() - Returns the owner object (player)
    { "GetCount", &LuaItem::GetCount },                           // :GetCount() - Returns item stack count
    { "GetMaxStackCount", &LuaItem::GetMaxStackCount },           // :GetMaxStackCount() - Returns item max stack count
    { "GetSlot", &LuaItem::GetSlot },                             // :GetSlot() - returns the slot the item is in
    { "GetBagSlot", &LuaItem::GetBagSlot },                       // :GetBagSlot() - returns the bagslot of the bag the item is in
    { "GetEnchantmentId", &LuaItem::GetEnchantmentId },           // :GetEnchantmentId(enchant_slot) - Returns the enchantment in given slot. (permanent = 0)
    { "GetSpellId", &LuaItem::GetSpellId },                       // :GetSpellId(index) - Returns spellID at given index (0 - 4)
    { "GetSpellTrigger", &LuaItem::GetSpellTrigger },             // :GetSpellTrigger(index) - Returns spell trigger at given index (0 - 4)
    { "GetItemLink", &LuaItem::GetItemLink },                     // :GetItemLink([localeID]) - Returns the shift clickable link of the item. Name translated if locale given and exists
    { "GetClass", &LuaItem::GetClass },                           // :GetClass()
    { "GetSubClass", &LuaItem::GetSubClass },                     // :GetSubClass()
    { "GetName", &LuaItem::GetName },                             // :GetName()
    { "GetDisplayId", &LuaItem::GetDisplayId },                   // :GetDisplayId()
    { "GetQuality", &LuaItem::GetQuality },                       // :GetQuality()
    { "GetBuyCount", &LuaItem::GetBuyCount },                     // :GetBuyCount()
    { "GetBuyPrice", &LuaItem::GetBuyPrice },                     // :GetBuyPrice()
    { "GetSellPrice", &LuaItem::GetSellPrice },                   // :GetSellPrice()
    { "GetInventoryType", &LuaItem::GetInventoryType },           // :GetInventoryType()
    { "GetAllowableClass", &LuaItem::GetAllowableClass },         // :GetAllowableClass()
    { "GetAllowableRace", &LuaItem::GetAllowableRace },           // :GetAllowableRace()
    { "GetItemLevel", &LuaItem::GetItemLevel },                   // :GetItemLevel()
    { "GetRequiredLevel", &LuaItem::GetRequiredLevel },           // :GetRequiredLevel()
#ifdef WOTLK
    { "GetStatsCount", &LuaItem::GetStatsCount },                 // :GetStatsCount()
#endif
    { "GetRandomProperty", &LuaItem::GetRandomProperty },         // :GetRandomProperty()
#ifndef CLASSIC
    { "GetRandomSuffix", &LuaItem::GetRandomSuffix },             // :GetRandomSuffix()
#endif
    { "GetItemSet", &LuaItem::GetItemSet },                       // :GetItemSet()
    { "GetBagSize", &LuaItem::GetBagSize },                       // :GetBagSize()

    // Setters
    { "SetOwner", &LuaItem::SetOwner },                           // :SetOwner(player) - Sets the owner of the item
    { "SetBinding", &LuaItem::SetBinding },                       // :SetBinding(bound) - Sets the item binding to true or false
    { "SetCount", &LuaItem::SetCount },                           // :SetCount(count) - Sets the item count

    // Boolean
    { "IsSoulBound", &LuaItem::IsSoulBound },                     // :IsSoulBound() - Returns true if the item is soulbound
#if (!defined(TBC) && !defined(CLASSIC))
    { "IsBoundAccountWide", &LuaItem::IsBoundAccountWide },       // :IsBoundAccountWide() - Returns true if the item is account bound
#endif
    { "IsBoundByEnchant", &LuaItem::IsBoundByEnchant },           // :IsBoundByEnchant() - Returns true if the item is bound with an enchant
    { "IsNotBoundToPlayer", &LuaItem::IsNotBoundToPlayer },       // :IsNotBoundToPlayer(player) - Returns true if the item is not bound with player
    { "IsLocked", &LuaItem::IsLocked },                           // :IsLocked() - Returns true if the item is locked
    { "IsBag", &LuaItem::IsBag },                                 // :IsBag() - Returns true if the item is a bag
#ifndef CLASSIC
    { "IsCurrencyToken", &LuaItem::IsCurrencyToken },             // :IsCurrencyToken() - Returns true if the item is a currency token
#endif
    { "IsNotEmptyBag", &LuaItem::IsNotEmptyBag },                 // :IsNotEmptyBag() - Returns true if the item is not an empty bag
    { "IsBroken", &LuaItem::IsBroken },                           // :IsBroken() - Returns true if the item is broken
    { "CanBeTraded", &LuaItem::CanBeTraded },                     // :CanBeTraded() - Returns true if the item can be traded
    { "IsInTrade", &LuaItem::IsInTrade },                         // :IsInTrade() - Returns true if the item is in trade
    { "IsInBag", &LuaItem::IsInBag },                             // :IsInBag() - Returns true if the item is in a bag
    { "IsEquipped", &LuaItem::IsEquipped },                       // :IsEquipped() - Returns true if the item is equipped
    { "HasQuest", &LuaItem::HasQuest },                           // :HasQuest(questId) - Returns true if the item starts the quest
    { "IsPotion", &LuaItem::IsPotion },                           // :IsPotion() - Returns true if the item is a potion
#ifndef CATA
    { "IsWeaponVellum", &LuaItem::IsWeaponVellum },               // :IsWeaponVellum() - Returns true if the item is a weapon vellum
    { "IsArmorVellum", &LuaItem::IsArmorVellum },                 // :IsArmorVellum() - Returns true if the item is an armor vellum
#endif
    { "IsConjuredConsumable", &LuaItem::IsConjuredConsumable },   // :IsConjuredConsumable() - Returns true if the item is a conjured consumable
    // {"IsRefundExpired", &LuaItem::IsRefundExpired},          // :IsRefundExpired() - Returns true if the item's refund time has expired
    { "SetEnchantment", &LuaItem::SetEnchantment },               // :SetEnchantment(enchantid, enchantmentslot) - Sets a new enchantment for the item. Returns true on success
    { "ClearEnchantment", &LuaItem::ClearEnchantment },           // :ClearEnchantment(enchantmentslot) - Removes the enchantment from the item if one exists. Returns true on success

    // Other
    { "SaveToDB", &LuaItem::SaveToDB },                           // :SaveToDB() - Saves to database

    { NULL, NULL },
};

ElunaRegister<Aura> AuraMethods[] =
{
    // Getters
    { "GetCaster", &LuaAura::GetCaster },
    { "GetCasterGUID", &LuaAura::GetCasterGUID },
    { "GetCasterLevel", &LuaAura::GetCasterLevel },
    { "GetDuration", &LuaAura::GetDuration },
    { "GetMaxDuration", &LuaAura::GetMaxDuration },
    { "GetAuraId", &LuaAura::GetAuraId },
    { "GetStackAmount", &LuaAura::GetStackAmount },
    { "GetOwner", &LuaAura::GetOwner },

    // Setters
    { "SetDuration", &LuaAura::SetDuration },
    { "SetMaxDuration", &LuaAura::SetMaxDuration },
    { "SetStackAmount", &LuaAura::SetStackAmount },

    // Other
    { "Remove", &LuaAura::Remove },

    { NULL, NULL },
};

ElunaRegister<Spell> SpellMethods[] =
{
    // Getters
    { "GetCaster", &LuaSpell::GetCaster },
    { "GetCastTime", &LuaSpell::GetCastTime },
    { "GetEntry", &LuaSpell::GetEntry },
    { "GetDuration", &LuaSpell::GetDuration },
    { "GetPowerCost", &LuaSpell::GetPowerCost },
    { "GetTargetDest", &LuaSpell::GetTargetDest },
    { "GetTarget", &LuaSpell::GetTarget },

    // Setters
    { "SetAutoRepeat", &LuaSpell::SetAutoRepeat },

    // Boolean
    { "IsAutoRepeat", &LuaSpell::IsAutoRepeat },

    // Other
    { "Cancel", &LuaSpell::Cancel },
    { "Cast", &LuaSpell::Cast },
    { "Finish", &LuaSpell::Finish },

    { NULL, NULL },
};

ElunaRegister<Quest> QuestMethods[] =
{
    // Getters
    { "GetId", &LuaQuest::GetId },
    { "GetLevel", &LuaQuest::GetLevel },
    // {"GetMaxLevel", &LuaQuest::GetMaxLevel},                   // :GetMaxLevel() - Returns the quest's max level
    { "GetMinLevel", &LuaQuest::GetMinLevel },
    { "GetNextQuestId", &LuaQuest::GetNextQuestId },
    { "GetPrevQuestId", &LuaQuest::GetPrevQuestId },
    { "GetNextQuestInChain", &LuaQuest::GetNextQuestInChain },
    { "GetFlags", &LuaQuest::GetFlags },
    { "GetType", &LuaQuest::GetType },

    // Boolean
    { "HasFlag", &LuaQuest::HasFlag },
#ifndef CLASSIC
    { "IsDaily", &LuaQuest::IsDaily },
#endif
    { "IsRepeatable", &LuaQuest::IsRepeatable },

    { NULL, NULL },
};

ElunaRegister<Group> GroupMethods[] =
{
    // Getters
    { "GetMembers", &LuaGroup::GetMembers },
    { "GetLeaderGUID", &LuaGroup::GetLeaderGUID },
    { "GetLeader", &LuaGroup::GetLeader },
    { "GetGUID", &LuaGroup::GetGUID },
    { "GetMemberGroup", &LuaGroup::GetMemberGroup },
    { "GetMemberGUID", &LuaGroup::GetMemberGUID },
    { "GetMembersCount", &LuaGroup::GetMembersCount },

    // Setters
    { "SetLeader", &LuaGroup::SetLeader },
    { "SetMembersGroup", &LuaGroup::SetMembersGroup },
    { "SetTargetIcon", &LuaGroup::SetTargetIcon },

    // Boolean
    { "IsLeader", &LuaGroup::IsLeader },
    { "AddInvite", &LuaGroup::AddInvite },
    { "RemoveMember", &LuaGroup::RemoveMember },
    { "Disband", &LuaGroup::Disband },
    { "IsFull", &LuaGroup::IsFull },
    // {"IsLFGGroup", &LuaGroup::IsLFGGroup},                     // :IsLFGGroup() - Returns true if the group is an LFG group
    { "IsRaidGroup", &LuaGroup::IsRaidGroup },
    { "IsBGGroup", &LuaGroup::IsBGGroup },
    // {"IsBFGroup", &LuaGroup::IsBFGroup},                       // :IsBFGroup() - Returns true if the group is a battlefield group
    { "IsMember", &LuaGroup::IsMember },
    { "IsAssistant", &LuaGroup::IsAssistant },
    { "SameSubGroup", &LuaGroup::SameSubGroup },
    { "HasFreeSlotSubGroup", &LuaGroup::HasFreeSlotSubGroup },

    // Other
    { "SendPacket", &LuaGroup::SendPacket },
    // {"ConvertToLFG", &LuaGroup::ConvertToLFG},                 // :ConvertToLFG() - Converts the group to an LFG group
    { "ConvertToRaid", &LuaGroup::ConvertToRaid },

    { NULL, NULL },
};

ElunaRegister<Guild> GuildMethods[] =
{
    // Getters
    { "GetMembers", &LuaGuild::GetMembers },                  // :GetMembers() - returns a table containing the players in this guild. (Online?)
    { "GetLeader", &LuaGuild::GetLeader },                    // :GetLeader() - Returns the guild learder's object
    { "GetLeaderGUID", &LuaGuild::GetLeaderGUID },            // :GetLeaderGUID() - Returns the guild learder's guid
    { "GetId", &LuaGuild::GetId },                            // :GetId() - Gets the guild's ID
    { "GetName", &LuaGuild::GetName },                        // :GetName() - Gets the guild name
    { "GetMOTD", &LuaGuild::GetMOTD },                        // :GetMOTD() - Gets the guild MOTD string
    { "GetInfo", &LuaGuild::GetInfo },                        // :GetInfo() - Gets the guild info string
    { "GetMemberCount", &LuaGuild::GetMemberCount },          // :GetMemberCount() - Returns the amount of players in the guild

    // Setters
#ifndef CLASSIC
    { "SetBankTabText", &LuaGuild::SetBankTabText },          // :SetBankTabText(tabId, text)
#endif
    { "SetMemberRank", &LuaGuild::SetMemberRank },         // :SetMemberRank(player, newRank) - Sets the player rank in the guild to the new rank
#ifndef CATA
    { "SetLeader", &LuaGuild::SetLeader },                    // :SetLeader() - Sets the guild's leader
#endif

    // Boolean

    // Other
    { "SendPacket", &LuaGuild::SendPacket },                  // :SendPacket(packet) - sends packet to guild
    { "SendPacketToRanked", &LuaGuild::SendPacketToRanked },  // :SendPacketToRanked(packet, rankId) - sends packet to guild, specifying a rankId will only send the packet to your ranked members
    { "Disband", &LuaGuild::Disband },                        // :Disband() - Disbands the guild
    { "AddMember", &LuaGuild::AddMember },                    // :AddMember(player, rank) - adds the player to the guild. Rank is optional
    { "DeleteMember", &LuaGuild::DeleteMember },              // :DeleteMember(player, disbanding, kicked) - Deletes the player from the guild. Disbanding and kicked are optional bools
#ifndef CLASSIC
    { "DepositBankMoney", &LuaGuild::DepositBankMoney },      // :DepositBankMoney(money) - Deposits money into the guild bank
    { "WithdrawBankMoney", &LuaGuild::WithdrawBankMoney },    // :WithdrawBankMoney(money) - Withdraws money from the guild bank
#endif

    { NULL, NULL },
};

#ifndef CLASSIC
#ifndef TBC
ElunaRegister<Vehicle> VehicleMethods[] =
{
    // Getters
    { "GetOwner", &LuaVehicle::GetOwner },                    // :GetOwner() - Returns the the vehicle unit
    { "GetEntry", &LuaVehicle::GetEntry },                    // :GetEntry() - Returns vehicle ID
    { "GetPassenger", &LuaVehicle::GetPassenger },            // :GetPassenger(seatId) - Returns the passenger by seatId

    // Boolean
    { "IsOnBoard", &LuaVehicle::IsOnBoard },                  // :IsOnBoard(unit) - Returns true if the unit is on board

    // Other
    { "AddPassenger", &LuaVehicle::AddPassenger },            // :AddPassenger(passenger, seatId) - Adds a vehicle passenger
    { "RemovePassenger", &LuaVehicle::RemovePassenger },      // :RemovePassenger(passenger) - Removes the passenger from the vehicle

    { NULL, NULL },
};
#endif
#endif

ElunaRegister<ElunaQuery> QueryMethods[] =
{
    { "NextRow", &LuaQuery::NextRow },                        // :NextRow() - Advances to next rown in the query. Returns true if there is a next row, otherwise false
    { "GetColumnCount", &LuaQuery::GetColumnCount },          // :GetColumnCount() - Gets the column count of the query
    { "GetRowCount", &LuaQuery::GetRowCount },                // :GetRowCount() - Gets the row count of the query
    { "GetRow", &LuaQuery::GetRow },

    { "GetBool", &LuaQuery::GetBool },                        // :GetBool(column) - returns a bool from a number column (for example tinyint)
    { "GetUInt8", &LuaQuery::GetUInt8 },                      // :GetUInt8(column) - returns the value of an unsigned tinyint column
    { "GetUInt16", &LuaQuery::GetUInt16 },                    // :GetUInt16(column) - returns the value of a unsigned smallint column
    { "GetUInt32", &LuaQuery::GetUInt32 },                    // :GetUInt32(column) - returns the value of an unsigned int or mediumint column
    { "GetUInt64", &LuaQuery::GetUInt64 },                    // :GetUInt64(column) - returns the value of an unsigned bigint column as string
    { "GetInt8", &LuaQuery::GetInt8 },                        // :GetInt8(column) - returns the value of an tinyint column
    { "GetInt16", &LuaQuery::GetInt16 },                      // :GetInt16(column) - returns the value of a smallint column
    { "GetInt32", &LuaQuery::GetInt32 },                      // :GetInt32(column) - returns the value of an int or mediumint column
    { "GetInt64", &LuaQuery::GetInt64 },                      // :GetInt64(column) - returns the value of a bigint column as string
    { "GetFloat", &LuaQuery::GetFloat },                      // :GetFloat(column) - returns the value of a float column
    { "GetDouble", &LuaQuery::GetDouble },                    // :GetDouble(column) - returns the value of a double column
    { "GetString", &LuaQuery::GetString },                    // :GetString(column) - returns the value of a string column, always returns a string
    { "IsNull", &LuaQuery::IsNull },                          // :IsNull(column) - returns true if the column is null

    { NULL, NULL },
};

ElunaRegister<WorldPacket> PacketMethods[] =
{
    // Getters
    { "GetOpcode", &LuaPacket::GetOpcode },
    { "GetSize", &LuaPacket::GetSize },

    // Setters
    { "SetOpcode", &LuaPacket::SetOpcode },

    // Readers
    { "ReadByte", &LuaPacket::ReadByte },
    { "ReadUByte", &LuaPacket::ReadUByte },
    { "ReadShort", &LuaPacket::ReadShort },
    { "ReadUShort", &LuaPacket::ReadUShort },
    { "ReadLong", &LuaPacket::ReadLong },
    { "ReadULong", &LuaPacket::ReadULong },
    { "ReadGUID", &LuaPacket::ReadGUID },
    { "ReadString", &LuaPacket::ReadString },
    { "ReadFloat", &LuaPacket::ReadFloat },
    { "ReadDouble", &LuaPacket::ReadDouble },

    // Writers
    { "WriteByte", &LuaPacket::WriteByte },                   // :WriteByte(val) - Writes an int8 value
    { "WriteUByte", &LuaPacket::WriteUByte },                 // :WriteUByte(val) - Writes a uint8 value
    { "WriteShort", &LuaPacket::WriteShort },                 // :WriteShort(val) - Writes an int16 value
    { "WriteUShort", &LuaPacket::WriteUShort },               // :WriteUShort(val) - Writes a uint16 value
    { "WriteLong", &LuaPacket::WriteLong },                   // :WriteLong(val) - Writes an int32 value
    { "WriteULong", &LuaPacket::WriteULong },                 // :WriteULong(val) - Writes a uint32 value
    { "WriteGUID", &LuaPacket::WriteGUID },                   // :WriteGUID(guid) - Writes a uint64 value
    { "WriteString", &LuaPacket::WriteString },               // :WriteString(val) - Writes a string value
    { "WriteFloat", &LuaPacket::WriteFloat },                 // :WriteFloat(val) - Writes a float value
    { "WriteDouble", &LuaPacket::WriteDouble },               // :WriteDouble(val) - Writes a double value

    { NULL, NULL },
};

ElunaRegister<Map> MapMethods[] =
{
    // Getters
    { "GetName", &LuaMap::GetName },                          // :GetName() - Returns the map's name UNDOCUMENTED
    { "GetDifficulty", &LuaMap::GetDifficulty },              // :GetDifficulty() - Returns the map's difficulty UNDOCUMENTED
    { "GetInstanceId", &LuaMap::GetInstanceId },              // :GetInstanceId() - Returns the map's instance ID UNDOCUMENTED
    { "GetPlayerCount", &LuaMap::GetPlayerCount },            // :GetPlayerCount() - Returns the amount of players on map except GM's UNDOCUMENTED
    { "GetMapId", &LuaMap::GetMapId },                        // :GetMapId() - Returns the map's ID UNDOCUMENTED
    { "GetAreaId", &LuaMap::GetAreaId },                      // :GetAreaId(x, y, z) - Returns the map's area ID based on coords UNDOCUMENTED
    { "GetHeight", &LuaMap::GetHeight },                      // :GetHeight(x, y[, phasemask]) - Returns ground Z coordinate. UNDOCUMENTED
    { "GetWorldObject", &LuaMap::GetWorldObject },            // :GetWorldObject(guid) - Returns a worldobject (player, creature, gameobject..) from the map by it's guid

    // Booleans
#ifndef CLASSIC
    { "IsArena", &LuaMap::IsArena },                          // :IsArena() - Returns the true if the map is an arena, else false UNDOCUMENTED
#endif
    { "IsBattleground", &LuaMap::IsBattleground },            // :IsBattleground() - Returns the true if the map is a battleground, else false UNDOCUMENTED
    { "IsDungeon", &LuaMap::IsDungeon },                      // :IsDungeon() - Returns the true if the map is a dungeon , else false UNDOCUMENTED
    { "IsEmpty", &LuaMap::IsEmpty },                          // :IsEmpty() - Returns the true if the map is empty, else false UNDOCUMENTED
#ifndef CLASSIC
    { "IsHeroic", &LuaMap::IsHeroic },                        // :IsHeroic() - Returns the true if the map is a heroic dungeon, else false UNDOCUMENTED
#endif
    { "IsRaid", &LuaMap::IsRaid },                            // :IsRaid() - Returns the true if the map is a raid map, else false UNDOCUMENTED

    { NULL, NULL },
};

ElunaRegister<Corpse> CorpseMethods[] =
{
    { "GetOwnerGUID", &LuaCorpse::GetOwnerGUID },
    { "GetGhostTime", &LuaCorpse::GetGhostTime },
    { "GetType", &LuaCorpse::GetType },
    { "ResetGhostTime", &LuaCorpse::ResetGhostTime },
    { "SaveToDB", &LuaCorpse::SaveToDB },
    { "DeleteBonesFromWorld", &LuaCorpse::DeleteBonesFromWorld },

    { NULL, NULL }
};

ElunaRegister<Weather> WeatherMethods[] =
{
    // Getters
    { "GetZoneId", &LuaWeather::GetZoneId },

    // Setters
    { "SetWeather", &LuaWeather::SetWeather },

    // Boolean
    { "Regenerate", &LuaWeather::Regenerate },
    { "UpdateWeather", &LuaWeather::UpdateWeather },

    // Other
    { "SendWeatherUpdateToPlayer", &LuaWeather::SendWeatherUpdateToPlayer },

    { NULL, NULL }
};

ElunaRegister<AuctionHouseObject> AuctionMethods[] =
{
    { NULL, NULL }
};

ElunaRegister<BattleGround> BattleGroundMethods[] =
{
    // Getters
    { "GetName", &LuaBattleGround::GetName },
    { "GetAlivePlayersCountByTeam", &LuaBattleGround::GetAlivePlayersCountByTeam },
    { "GetMap", &LuaBattleGround::GetMap },
    { "GetBonusHonorFromKillCount", &LuaBattleGround::GetBonusHonorFromKillCount },
    { "GetBracketId", &LuaBattleGround::GetBracketId },
    { "GetEndTime", &LuaBattleGround::GetEndTime },
    { "GetFreeSlotsForTeam", &LuaBattleGround::GetFreeSlotsForTeam },
    { "GetInstanceId", &LuaBattleGround::GetInstanceId },
    { "GetMapId", &LuaBattleGround::GetMapId },
    { "GetTypeId", &LuaBattleGround::GetTypeId },
    { "GetMaxLevel", &LuaBattleGround::GetMaxLevel },
    { "GetMinLevel", &LuaBattleGround::GetMinLevel },
    { "GetMaxPlayers", &LuaBattleGround::GetMaxPlayers },
    { "GetMinPlayers", &LuaBattleGround::GetMinPlayers },
    { "GetMaxPlayersPerTeam", &LuaBattleGround::GetMaxPlayersPerTeam },
    { "GetMinPlayersPerTeam", &LuaBattleGround::GetMinPlayersPerTeam },
    { "GetWinner", &LuaBattleGround::GetWinner },
    { "GetStatus", &LuaBattleGround::GetStatus },

    // Setters

    { NULL, NULL }
};

template<typename T> const char* ElunaTemplate<T>::tname = NULL;
template<typename T> bool ElunaTemplate<T>::manageMemory = false;

#if (!defined(TBC) && !defined(CLASSIC))
// fix compile error about accessing vehicle destructor
template<> int ElunaTemplate<Vehicle>::CollectGarbage(lua_State* L)
{
    ASSERT(!manageMemory);

    // Get object pointer (and check type, no error)
    ElunaObject* obj = Eluna::CHECKOBJ<ElunaObject>(L, 1, false);
    delete obj;
    return 0;
}
#endif

// Template by Mud from http://stackoverflow.com/questions/4484437/lua-integer-type/4485511#4485511
template<> int ElunaTemplate<unsigned long long>::Add(lua_State* L) { Eluna::Push(L, Eluna::CHECKVAL<unsigned long long>(L, 1) + Eluna::CHECKVAL<unsigned long long>(L, 2)); return 1; }
template<> int ElunaTemplate<unsigned long long>::Substract(lua_State* L) { Eluna::Push(L, Eluna::CHECKVAL<unsigned long long>(L, 1) - Eluna::CHECKVAL<unsigned long long>(L, 2)); return 1; }
template<> int ElunaTemplate<unsigned long long>::Multiply(lua_State* L) { Eluna::Push(L, Eluna::CHECKVAL<unsigned long long>(L, 1) * Eluna::CHECKVAL<unsigned long long>(L, 2)); return 1; }
template<> int ElunaTemplate<unsigned long long>::Divide(lua_State* L) { Eluna::Push(L, Eluna::CHECKVAL<unsigned long long>(L, 1) / Eluna::CHECKVAL<unsigned long long>(L, 2)); return 1; }
template<> int ElunaTemplate<unsigned long long>::Mod(lua_State* L) { Eluna::Push(L, Eluna::CHECKVAL<unsigned long long>(L, 1) % Eluna::CHECKVAL<unsigned long long>(L, 2)); return 1; }
// template<> int ElunaTemplate<unsigned long long>::UnaryMinus(lua_State* L) { Eluna::Push(L, -Eluna::CHECKVAL<unsigned long long>(L, 1)); return 1; }
template<> int ElunaTemplate<unsigned long long>::Equal(lua_State* L) { Eluna::Push(L, Eluna::CHECKVAL<unsigned long long>(L, 1) == Eluna::CHECKVAL<unsigned long long>(L, 2)); return 1; }
template<> int ElunaTemplate<unsigned long long>::Less(lua_State* L) { Eluna::Push(L, Eluna::CHECKVAL<unsigned long long>(L, 1) < Eluna::CHECKVAL<unsigned long long>(L, 2)); return 1; }
template<> int ElunaTemplate<unsigned long long>::LessOrEqual(lua_State* L) { Eluna::Push(L, Eluna::CHECKVAL<unsigned long long>(L, 1) <= Eluna::CHECKVAL<unsigned long long>(L, 2)); return 1; }
template<> int ElunaTemplate<unsigned long long>::Pow(lua_State* L)
{
    Eluna::Push(L, static_cast<unsigned long long>(powl(static_cast<long double>(Eluna::CHECKVAL<unsigned long long>(L, 1)), static_cast<long double>(Eluna::CHECKVAL<unsigned long long>(L, 2)))));
    return 1;
}
template<> int ElunaTemplate<unsigned long long>::ToString(lua_State* L)
{
    unsigned long long l = Eluna::CHECKVAL<unsigned long long>(L, 1);
    std::ostringstream ss;
    ss << l;
    Eluna::Push(L, ss.str());
    return 1;
}

template<> int ElunaTemplate<long long>::Add(lua_State* L) { Eluna::Push(L, Eluna::CHECKVAL<long long>(L, 1) + Eluna::CHECKVAL<long long>(L, 2)); return 1; }
template<> int ElunaTemplate<long long>::Substract(lua_State* L) { Eluna::Push(L, Eluna::CHECKVAL<long long>(L, 1) - Eluna::CHECKVAL<long long>(L, 2)); return 1; }
template<> int ElunaTemplate<long long>::Multiply(lua_State* L) { Eluna::Push(L, Eluna::CHECKVAL<long long>(L, 1) * Eluna::CHECKVAL<long long>(L, 2)); return 1; }
template<> int ElunaTemplate<long long>::Divide(lua_State* L) { Eluna::Push(L, Eluna::CHECKVAL<long long>(L, 1) / Eluna::CHECKVAL<long long>(L, 2)); return 1; }
template<> int ElunaTemplate<long long>::Mod(lua_State* L) { Eluna::Push(L, Eluna::CHECKVAL<long long>(L, 1) % Eluna::CHECKVAL<long long>(L, 2)); return 1; }
template<> int ElunaTemplate<long long>::UnaryMinus(lua_State* L) { Eluna::Push(L, -Eluna::CHECKVAL<long long>(L, 1)); return 1; }
template<> int ElunaTemplate<long long>::Equal(lua_State* L) { Eluna::Push(L, Eluna::CHECKVAL<long long>(L, 1) == Eluna::CHECKVAL<long long>(L, 2)); return 1; }
template<> int ElunaTemplate<long long>::Less(lua_State* L) { Eluna::Push(L, Eluna::CHECKVAL<long long>(L, 1) < Eluna::CHECKVAL<long long>(L, 2)); return 1; }
template<> int ElunaTemplate<long long>::LessOrEqual(lua_State* L) { Eluna::Push(L, Eluna::CHECKVAL<long long>(L, 1) <= Eluna::CHECKVAL<long long>(L, 2)); return 1; }
template<> int ElunaTemplate<long long>::Pow(lua_State* L)
{
    Eluna::Push(L, static_cast<long long>(powl(static_cast<long double>(Eluna::CHECKVAL<long long>(L, 1)), static_cast<long double>(Eluna::CHECKVAL<long long>(L, 2)))));
    return 1;
}
template<> int ElunaTemplate<long long>::ToString(lua_State* L)
{
    long long l = Eluna::CHECKVAL<long long>(L, 1);
    std::ostringstream ss;
    ss << l;
    Eluna::Push(L, ss.str());
    return 1;
}

void RegisterFunctions(Eluna* E)
{
    ElunaGlobal::SetMethods(E, GlobalMethods);

    ElunaTemplate<Object>::Register(E, "Object");
    ElunaTemplate<Object>::SetMethods(E, ObjectMethods);

    ElunaTemplate<WorldObject>::Register(E, "WorldObject");
    ElunaTemplate<WorldObject>::SetMethods(E, ObjectMethods);
    ElunaTemplate<WorldObject>::SetMethods(E, WorldObjectMethods);

    ElunaTemplate<Unit>::Register(E, "Unit");
    ElunaTemplate<Unit>::SetMethods(E, ObjectMethods);
    ElunaTemplate<Unit>::SetMethods(E, WorldObjectMethods);
    ElunaTemplate<Unit>::SetMethods(E, UnitMethods);

    ElunaTemplate<Player>::Register(E, "Player");
    ElunaTemplate<Player>::SetMethods(E, ObjectMethods);
    ElunaTemplate<Player>::SetMethods(E, WorldObjectMethods);
    ElunaTemplate<Player>::SetMethods(E, UnitMethods);
    ElunaTemplate<Player>::SetMethods(E, PlayerMethods);

    ElunaTemplate<Creature>::Register(E, "Creature");
    ElunaTemplate<Creature>::SetMethods(E, ObjectMethods);
    ElunaTemplate<Creature>::SetMethods(E, WorldObjectMethods);
    ElunaTemplate<Creature>::SetMethods(E, UnitMethods);
    ElunaTemplate<Creature>::SetMethods(E, CreatureMethods);

    ElunaTemplate<GameObject>::Register(E, "GameObject");
    ElunaTemplate<GameObject>::SetMethods(E, ObjectMethods);
    ElunaTemplate<GameObject>::SetMethods(E, WorldObjectMethods);
    ElunaTemplate<GameObject>::SetMethods(E, GameObjectMethods);

    ElunaTemplate<Corpse>::Register(E, "Corpse");
    ElunaTemplate<Corpse>::SetMethods(E, ObjectMethods);
    ElunaTemplate<Corpse>::SetMethods(E, WorldObjectMethods);
    ElunaTemplate<Corpse>::SetMethods(E, CorpseMethods);

    ElunaTemplate<Item>::Register(E, "Item");
    ElunaTemplate<Item>::SetMethods(E, ObjectMethods);
    ElunaTemplate<Item>::SetMethods(E, ItemMethods);

#ifndef CLASSIC
#ifndef TBC
    ElunaTemplate<Vehicle>::Register(E, "Vehicle");
    ElunaTemplate<Vehicle>::SetMethods(E, VehicleMethods);
#endif
#endif

    ElunaTemplate<Group>::Register(E, "Group");
    ElunaTemplate<Group>::SetMethods(E, GroupMethods);

    ElunaTemplate<Guild>::Register(E, "Guild");
    ElunaTemplate<Guild>::SetMethods(E, GuildMethods);

    ElunaTemplate<Aura>::Register(E, "Aura");
    ElunaTemplate<Aura>::SetMethods(E, AuraMethods);

    ElunaTemplate<Spell>::Register(E, "Spell");
    ElunaTemplate<Spell>::SetMethods(E, SpellMethods);

    ElunaTemplate<Quest>::Register(E, "Quest");
    ElunaTemplate<Quest>::SetMethods(E, QuestMethods);

    ElunaTemplate<Map>::Register(E, "Map");
    ElunaTemplate<Map>::SetMethods(E, MapMethods);

    ElunaTemplate<Weather>::Register(E, "Weather");
    ElunaTemplate<Weather>::SetMethods(E, WeatherMethods);

    ElunaTemplate<AuctionHouseObject>::Register(E, "AuctionHouseObject");
    ElunaTemplate<AuctionHouseObject>::SetMethods(E, AuctionMethods);

    ElunaTemplate<BattleGround>::Register(E, "BattleGround");
    ElunaTemplate<BattleGround>::SetMethods(E, BattleGroundMethods);

    ElunaTemplate<WorldPacket>::Register(E, "WorldPacket", true);
    ElunaTemplate<WorldPacket>::SetMethods(E, PacketMethods);

    ElunaTemplate<ElunaQuery>::Register(E, "ElunaQuery", true);
    ElunaTemplate<ElunaQuery>::SetMethods(E, QueryMethods);

    ElunaTemplate<long long>::Register(E, "long long", true);

    ElunaTemplate<unsigned long long>::Register(E, "unsigned long long", true);
}
