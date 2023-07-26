/*
* Copyright (C) 2010 - 2023 Eluna Lua Engine <https://elunaluaengine.github.io/>
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
#include "VehicleMethods.h"
#include "BattleGroundMethods.h"

luaL_Reg GlobalMethods[] =
{
    // Hooks
    { "RegisterPacketEvent", nullptr },
    { "RegisterServerEvent", nullptr },
    { "RegisterPlayerEvent", nullptr },
    { "RegisterGuildEvent", nullptr },
    { "RegisterGroupEvent", nullptr },
    { "RegisterCreatureEvent", nullptr },
    { "RegisterUniqueCreatureEvent", nullptr },
    { "RegisterCreatureGossipEvent", nullptr },
    { "RegisterGameObjectEvent", nullptr },
    { "RegisterGameObjectGossipEvent", nullptr },
    { "RegisterItemEvent", nullptr },
    { "RegisterItemGossipEvent", nullptr },
    { "RegisterPlayerGossipEvent", nullptr },
    { "RegisterBGEvent", nullptr },
    { "RegisterMapEvent", nullptr },
    { "RegisterInstanceEvent", nullptr },

    { "ClearBattleGroundEvents", nullptr },
    { "ClearCreatureEvents", nullptr },
    { "ClearUniqueCreatureEvents", nullptr },
    { "ClearCreatureGossipEvents", nullptr },
    { "ClearGameObjectEvents", nullptr },
    { "ClearGameObjectGossipEvents", nullptr },
    { "ClearGroupEvents", nullptr },
    { "ClearGuildEvents", nullptr },
    { "ClearItemEvents", nullptr },
    { "ClearItemGossipEvents", nullptr },
    { "ClearPacketEvents", nullptr },
    { "ClearPlayerEvents", nullptr },
    { "ClearPlayerGossipEvents", nullptr },
    { "ClearServerEvents", nullptr },
    { "ClearMapEvents", nullptr },
    { "ClearInstanceEvents", nullptr },

    // Getters
    { "GetLuaEngine", nullptr },
    { "GetCoreName", nullptr },
    { "GetRealmID", nullptr },
    { "GetCoreVersion", nullptr },
    { "GetCoreExpansion", nullptr },
    { "GetQuest", nullptr },
    { "GetPlayerByGUID", nullptr },
    { "GetPlayerByName", nullptr },
    { "GetGameTime", nullptr },
    { "GetPlayersInWorld", nullptr },
    { "GetGuildByName", nullptr },
    { "GetGuildByLeaderGUID", nullptr },
    { "GetPlayerCount", nullptr },
    { "GetPlayerGUID", nullptr },
    { "GetItemGUID", nullptr },
    { "GetObjectGUID", nullptr },
    { "GetUnitGUID", nullptr },
    { "GetGUIDLow", nullptr },
    { "GetGUIDType", nullptr },
    { "GetGUIDEntry", nullptr },
    { "GetAreaName", nullptr },
    { "bit_not", nullptr },
    { "bit_xor", nullptr },
    { "bit_rshift", nullptr },
    { "bit_lshift", nullptr },
    { "bit_or", nullptr },
    { "bit_and", nullptr },
    { "GetItemLink", nullptr },
    { "GetMapById", nullptr },
    { "GetCurrTime", nullptr },
    { "GetTimeDiff", nullptr },
    { "PrintInfo", nullptr },
    { "PrintError", nullptr },
    { "PrintDebug", nullptr },
    { "GetActiveGameEvents", nullptr },

    // Boolean
    { "IsInventoryPos", nullptr },
    { "IsEquipmentPos", nullptr },
    { "IsBankPos", nullptr },
    { "IsBagPos", nullptr },
    { "IsGameEventActive", nullptr },

    // Other
    { "ReloadEluna", nullptr },
    { "RunCommand", nullptr },
    { "SendWorldMessage", nullptr },
    { "WorldDBQuery", nullptr },
    { "WorldDBExecute", nullptr },
    { "CharDBQuery", nullptr },
    { "CharDBExecute", nullptr },
    { "AuthDBQuery", nullptr },
    { "AuthDBExecute", nullptr },
    { "CreateLuaEvent", nullptr },
    { "RemoveEventById", nullptr },
    { "RemoveEvents", nullptr },
    { "PerformIngameSpawn", nullptr },
    { "CreatePacket", nullptr },
    { "AddVendorItem", nullptr },
    { "VendorRemoveItem", nullptr },
    { "VendorRemoveAllItems", nullptr },
    { "Kick", nullptr },
    { "Ban", nullptr },
    { "SaveAllPlayers", nullptr },
    { "SendMail", nullptr },
    { "AddTaxiPath", nullptr },
    { "CreateInt64", nullptr },
    { "CreateUint64", nullptr },
    { "StartGameEvent", nullptr },
    { "StopGameEvent", nullptr },

    { NULL, NULL }
};

ElunaRegister<Object> ObjectMethods[] =
{
    // Getters
    { "GetEntry", nullptr },
    { "GetGUID", nullptr },
    { "GetGUIDLow", nullptr },
    { "GetInt32Value", nullptr },
    { "GetUInt32Value", nullptr },
    { "GetFloatValue", nullptr },
    { "GetByteValue", nullptr },
    { "GetUInt16Value", nullptr },
    { "GetUInt64Value", nullptr },
    { "GetScale", nullptr },
    { "GetTypeId", nullptr },

    // Setters
    { "SetInt32Value", nullptr },
    { "SetUInt32Value", nullptr },
    { "UpdateUInt32Value", nullptr },
    { "SetFloatValue", nullptr },
    { "SetByteValue", nullptr },
    { "SetUInt16Value", nullptr },
    { "SetInt16Value", nullptr },
    { "SetUInt64Value", nullptr },
    { "SetScale", nullptr },
    { "SetFlag", nullptr },

    // Boolean
    { "IsInWorld", nullptr },
    { "HasFlag", nullptr },

    // Other
    { "ToGameObject", nullptr },
    { "ToUnit", nullptr },
    { "ToCreature", nullptr },
    { "ToPlayer", nullptr },
    { "ToCorpse", nullptr },
    { "RemoveFlag", nullptr },

    { NULL, NULL }
};

ElunaRegister<WorldObject> WorldObjectMethods[] =
{
    // Getters
    { "GetName", nullptr },
    { "GetMap", nullptr },
                                        
    { "GetPhaseMask", nullptr },
    { "SetPhaseMask", nullptr },
      
    { "GetInstanceId", nullptr },
    { "GetAreaId", nullptr },
    { "GetZoneId", nullptr },
    { "GetMapId", nullptr },
    { "GetX", nullptr },
    { "GetY", nullptr },
    { "GetZ", nullptr },
    { "GetO", nullptr },
    { "GetLocation", nullptr },
    { "GetPlayersInRange", nullptr },
    { "GetCreaturesInRange", nullptr },
    { "GetGameObjectsInRange", nullptr },
    { "GetNearestPlayer", nullptr },
    { "GetNearestGameObject", nullptr },
    { "GetNearestCreature", nullptr },
    { "GetNearObject", nullptr },
    { "GetNearObjects", nullptr },
    { "GetDistance", nullptr },
    { "GetExactDistance", nullptr },
    { "GetDistance2d", nullptr },
    { "GetExactDistance2d", nullptr },
    { "GetRelativePoint", nullptr },
    { "GetAngle", nullptr },

    // Boolean
    { "IsWithinLoS", nullptr },
    { "IsInMap", nullptr },
    { "IsWithinDist3d", nullptr },
    { "IsWithinDist2d", nullptr },
    { "IsWithinDist", nullptr },
    { "IsWithinDistInMap", nullptr },
    { "IsInRange", nullptr },
    { "IsInRange2d", nullptr },
    { "IsInRange3d", nullptr },
    { "IsInFront", nullptr },
    { "IsInBack", nullptr },

    // Other
    { "SummonGameObject", nullptr },
    { "SpawnCreature", nullptr },
    { "SendPacket", nullptr },
    { "RegisterEvent", nullptr },
    { "RemoveEventById", nullptr },
    { "RemoveEvents", nullptr },
    { "PlayMusic", nullptr },
    { "PlayDirectSound", nullptr },
    { "PlayDistanceSound", nullptr },

    { NULL, NULL }
};

ElunaRegister<Unit> UnitMethods[] =
{
    // Getters
    { "GetLevel", nullptr },
    { "GetHealth", nullptr },
    { "GetDisplayId", nullptr },
    { "GetNativeDisplayId", nullptr },
    { "GetPower", nullptr },
    { "GetMaxPower", nullptr },
    { "GetPowerType", nullptr },
    { "GetMaxHealth", nullptr },
    { "GetHealthPct", nullptr },
    { "GetPowerPct", nullptr },
    { "GetGender", nullptr },
    { "GetRace", nullptr },
    { "GetClass", nullptr },
    { "GetRaceMask", nullptr },
    { "GetClassMask", nullptr },
    { "GetRaceAsString", nullptr },
    { "GetClassAsString", nullptr },
    { "GetAura", nullptr },
    { "GetFaction", nullptr },
    { "GetCurrentSpell", nullptr },
    { "GetCreatureType", nullptr },
    { "GetMountId", nullptr },
    { "GetOwner", nullptr },
    { "GetFriendlyUnitsInRange", nullptr },
    { "GetUnfriendlyUnitsInRange", nullptr },
    { "GetOwnerGUID", nullptr },
    { "GetCreatorGUID", nullptr },
    { "GetMinionGUID", nullptr },
    { "GetCharmerGUID", nullptr },
    { "GetCharmGUID", nullptr },
    { "GetPetGUID", nullptr },
                                        
    { "GetCritterGUID", nullptr },
      
    { "GetControllerGUID", nullptr },
    { "GetControllerGUIDS", nullptr },
    { "GetStandState", nullptr },
    { "GetVictim", nullptr },
    { "GetSpeed", nullptr },
    { "GetStat", nullptr },
    { "GetBaseSpellPower", nullptr },
                                        
    { "GetVehicleKit", nullptr },
    { "GetVehicle", nullptr },
      
    { "GetMovementType", nullptr },

    // Setters
    { "SetFaction", nullptr },
    { "SetLevel", nullptr },
    { "SetHealth", nullptr },
    { "SetMaxHealth", nullptr },
    { "SetPower", nullptr },
    { "SetMaxPower", nullptr },
    { "SetPowerType", nullptr },
    { "SetDisplayId", nullptr },
    { "SetNativeDisplayId", nullptr },
    { "SetFacing", nullptr },
    { "SetFacingToObject", nullptr },
    { "SetSpeed", nullptr },
    { "SetStunned", nullptr },
    { "SetRooted", nullptr },
    { "SetConfused", nullptr },
    { "SetFeared", nullptr },
    { "SetPvP", nullptr },
                                        
    { "SetFFA", nullptr },
    { "SetSanctuary", nullptr },
      
    { "SetCanFly", nullptr },
    { "SetVisible", nullptr },
    { "SetOwnerGUID", nullptr },
    { "SetName", nullptr },
    { "SetSheath", nullptr },
    { "SetCreatorGUID", nullptr },
    { "SetMinionGUID", nullptr },
    { "SetPetGUID", nullptr },
                                        
    { "SetCritterGUID", nullptr },
      
    { "SetWaterWalk", nullptr },
    { "SetStandState", nullptr },
    { "SetInCombatWith", nullptr },
    { "ModifyPower", nullptr },

    // Boolean
    { "IsAlive", nullptr },
    { "IsDead", nullptr },
    { "IsDying", nullptr },
    { "IsPvPFlagged", nullptr },
    { "IsInCombat", nullptr },
    { "IsBanker", nullptr },
    { "IsBattleMaster", nullptr },
    { "IsCharmed", nullptr },
    { "IsArmorer", nullptr },
    { "IsAttackingPlayer", nullptr },
    { "IsInWater", nullptr },
    { "IsUnderWater", nullptr },
    { "IsAuctioneer", nullptr },
    { "IsGuildMaster", nullptr },
    { "IsInnkeeper", nullptr },
    { "IsTrainer", nullptr },
    { "IsGossip", nullptr },
    { "IsTaxi", nullptr },
    { "IsSpiritHealer", nullptr },
    { "IsSpiritGuide", nullptr },
    { "IsTabardDesigner", nullptr },
    { "IsServiceProvider", nullptr },
    { "IsSpiritService", nullptr },
    { "HealthBelowPct", nullptr },
    { "HealthAbovePct", nullptr },
    { "IsMounted", nullptr },
    { "AttackStop", nullptr },
    { "Attack", nullptr },
    { "IsVisible", nullptr },
    { "IsMoving", nullptr },
    { "IsFlying", nullptr },
    { "IsStopped", nullptr },
    { "HasUnitState", nullptr },
    { "IsQuestGiver", nullptr },
    { "IsInAccessiblePlaceFor", nullptr },
    { "IsVendor", nullptr },
    { "IsRooted", nullptr },
    { "IsFullHealth", nullptr },
    { "HasAura", nullptr },
    { "IsCasting", nullptr },
    { "IsStandState", nullptr },
               
    { "IsOnVehicle", nullptr },
      

    // Other
    { "AddAura", nullptr },
    { "RemoveAura", nullptr },
    { "RemoveAllAuras", nullptr },
                     
    { "RemoveArenaAuras", nullptr },
      
    { "ClearInCombat", nullptr },
    { "DeMorph", nullptr },
    { "SendUnitWhisper", nullptr },
    { "SendUnitEmote", nullptr },
    { "SendUnitSay", nullptr },
    { "SendUnitYell", nullptr },
    { "CastSpell", nullptr },
    { "CastCustomSpell", nullptr },
    { "CastSpellAoF", nullptr },
    { "Kill", nullptr },
    { "StopSpellCast", nullptr },
    { "InterruptSpell", nullptr },
    { "SendChatMessageToPlayer", nullptr },
    { "PerformEmote", nullptr },
    { "EmoteState", nullptr },
    { "CountPctFromCurHealth", nullptr },
    { "CountPctFromMaxHealth", nullptr },
    { "Dismount", nullptr },
    { "Mount", nullptr },
    { "RestoreDisplayId", nullptr },
    { "RestoreFaction", nullptr },
    { "RemoveBindSightAuras", nullptr },
    { "RemoveCharmAuras", nullptr },
    { "ClearThreatList", nullptr },
    { "ClearUnitState", nullptr },
    { "AddUnitState", nullptr },
    { "DisableMelee", nullptr },
    { "SummonGuardian", nullptr },
    { "NearTeleport", nullptr },
    { "MoveIdle", nullptr },
    { "MoveRandom", nullptr },
    { "MoveHome", nullptr },
    { "MoveFollow", nullptr },
    { "MoveChase", nullptr },
    { "MoveConfused", nullptr },
    { "MoveFleeing", nullptr },
    { "MoveTo", nullptr },
                                        
    { "MoveJump", nullptr },
      
    { "MoveStop", nullptr },
    { "MoveExpire", nullptr },
    { "MoveClear", nullptr },
    { "DealDamage", nullptr },
    { "DealHeal", nullptr },
    { "AddThreat", nullptr },

    { NULL, NULL }
};

ElunaRegister<Player> PlayerMethods[] =
{
    // Getters
    { "GetSelection", nullptr },
    { "GetGMRank", nullptr },
    { "GetGuildId", nullptr },
    { "GetCoinage", nullptr },
    { "GetTeam", nullptr },
    { "GetItemCount", nullptr },
    { "GetGroup", nullptr },
    { "GetGuild", nullptr },
    { "GetAccountId", nullptr },
    { "GetAccountName", nullptr },
                                    
    { "GetArenaPoints", nullptr },
    { "GetHonorPoints", nullptr },
      
    { "GetLifetimeKills", nullptr },
    { "GetPlayerIP", nullptr },
    { "GetLevelPlayedTime", nullptr },
    { "GetTotalPlayedTime", nullptr },
    { "GetItemByPos", nullptr },
    { "GetItemByEntry", nullptr },
    { "GetItemByGUID", nullptr },
    { "GetMailItem", nullptr },
    { "GetReputation", nullptr },
    { "GetEquippedItemBySlot", nullptr },
    { "GetQuestLevel", nullptr },
    { "GetChatTag", nullptr },
    { "GetRestBonus", nullptr },
            
    { "GetPhaseMaskForSpawn", nullptr },
      
    { "GetReqKillOrCastCurrentCount", nullptr },
    { "GetQuestStatus", nullptr },
    { "GetInGameTime", nullptr },
    { "GetComboPoints", nullptr },
    { "GetComboTarget", nullptr },
    { "GetGuildName", nullptr },
    { "GetFreeTalentPoints", nullptr },
                                        
    { "GetActiveSpec", nullptr },
    { "GetSpecsCount", nullptr },
      
    { "GetSpellCooldownDelay", nullptr },
    { "GetGuildRank", nullptr },
    { "GetDifficulty", nullptr },
    { "GetHealthBonusFromStamina", nullptr },
    { "GetManaBonusFromIntellect", nullptr },
    { "GetMaxSkillValue", nullptr },
    { "GetPureMaxSkillValue", nullptr },
    { "GetSkillValue", nullptr },
    { "GetBaseSkillValue", nullptr },
    { "GetPureSkillValue", nullptr },
    { "GetSkillPermBonusValue", nullptr },
    { "GetSkillTempBonusValue", nullptr },
    { "GetReputationRank", nullptr },
    { "GetDrunkValue", nullptr },
    { "GetBattlegroundId", nullptr },
    { "GetBattlegroundTypeId", nullptr },
    { "GetXPRestBonus", nullptr },
    { "GetGroupInvite", nullptr },
    { "GetSubGroup", nullptr },
    { "GetNextRandomRaidMember", nullptr },
    { "GetOriginalGroup", nullptr },
    { "GetOriginalSubGroup", nullptr },
                                   
    { "GetChampioningFaction", nullptr },
      
    { "GetLatency", nullptr },
    { "GetRecruiterId", nullptr },
    { "GetDbLocaleIndex", nullptr },
    { "GetDbcLocale", nullptr },
    { "GetCorpse", nullptr },
    { "GetGossipTextId", nullptr },
    { "GetQuestRewardStatus", nullptr },
                                                      
    { "GetShieldBlockValue", nullptr },
      
              
    { "GetHonorStoredKills", nullptr },
    { "GetRankPoints", nullptr },
    { "GetHonorLastWeekStandingPos", nullptr },
      

    // Setters
    { "AdvanceSkillsToMax", nullptr },
    { "AdvanceSkill", nullptr },
    { "AdvanceAllSkills", nullptr },
    { "AddLifetimeKills", nullptr },
    { "SetCoinage", nullptr },
               
    { "SetKnownTitle", nullptr },
    { "UnsetKnownTitle", nullptr },
      
    { "SetBindPoint", nullptr },
                                  
    { "SetArenaPoints", nullptr },
    { "SetHonorPoints", nullptr },
      
              
    { "SetHonorStoredKills", nullptr },
    { "SetRankPoints", nullptr },
    { "SetHonorLastWeekStandingPos", nullptr },
      
    { "SetLifetimeKills", nullptr },
    { "SetGameMaster", nullptr },
    { "SetGMChat", nullptr },
    { "SetTaxiCheat", nullptr },
    { "SetGMVisible", nullptr },
    { "SetPvPDeath", nullptr },
    { "SetAcceptWhispers", nullptr },
    { "SetRestBonus", nullptr },
    { "SetQuestStatus", nullptr },
    { "SetReputation", nullptr },
    { "SetFreeTalentPoints", nullptr },
    { "SetGuildRank", nullptr },
    { "SetMovement", nullptr },
    { "SetSkill", nullptr },
    { "SetFactionForRace", nullptr },
    { "SetDrunkValue", nullptr },
    { "SetAtLoginFlag", nullptr },
    { "SetPlayerLock", nullptr },
    { "SetGender", nullptr },
    { "SetSheath", nullptr },
                                    
    { "SetFFA", nullptr },
      

    // Boolean
    { "IsInGroup", nullptr },
    { "IsInGuild", nullptr },
    { "IsGM", nullptr },
    { "IsImmuneToDamage", nullptr },
    { "IsAlliance", nullptr },
    { "IsHorde", nullptr },
               
    { "HasTitle", nullptr },
      
    { "HasItem", nullptr },
    { "Teleport", nullptr },
    { "AddItem", nullptr },
               
    { "IsInArenaTeam", nullptr },
      
    { "CanCompleteQuest", nullptr },
    { "CanEquipItem", nullptr },
    { "IsFalling", nullptr },
    { "ToggleAFK", nullptr },
    { "ToggleDND", nullptr },
    { "IsAFK", nullptr },
    { "IsDND", nullptr },
    { "IsAcceptingWhispers", nullptr },
    { "IsGMChat", nullptr },
    { "IsTaxiCheater", nullptr },
    { "IsGMVisible", nullptr },
    { "HasQuest", nullptr },
    { "InBattlegroundQueue", nullptr },
    { "IsImmuneToEnvironmentalDamage", nullptr },
    { "CanSpeak", nullptr },
    { "HasAtLoginFlag", nullptr },
    { "InRandomLfgDungeon", nullptr },
    { "HasPendingBind", nullptr },
                                        
    { "HasAchieved", nullptr },
                                            
    { "SetAchievement", nullptr },
      
      
    { "CanUninviteFromGroup", nullptr },
    { "IsRested", nullptr },
    { "CanFlyInZone", nullptr },
    { "IsNeverVisible", nullptr },
    { "IsVisibleForPlayer", nullptr },
    { "IsUsingLfg", nullptr },
    { "HasQuestForItem", nullptr },
    { "HasQuestForGO", nullptr },
    { "CanShareQuest", nullptr },
    { "HasReceivedQuestReward", nullptr },
                                        
    { "HasTalent", nullptr },
      
    { "IsInSameGroupWith", nullptr },
    { "IsInSameRaidWith", nullptr },
    { "IsGroupVisibleFor", nullptr },
    { "HasSkill", nullptr },
    { "IsHonorOrXPTarget", nullptr },
    { "CanParry", nullptr },
    { "CanBlock", nullptr },
                                        
    { "CanTitanGrip", nullptr },
      
    { "InBattleground", nullptr },
               
    { "InArena", nullptr },
      
    { "IsOutdoorPvPActive", nullptr },
    { "IsARecruiter", nullptr },
    { "CanUseItem", nullptr },
    { "HasSpell", nullptr },
    { "HasSpellCooldown", nullptr },
    { "IsInWater", nullptr },
               
    { "CanFly", nullptr },
      
    { "IsMoving", nullptr },
               
    { "IsFlying", nullptr },
      

    // Gossip
    { "GossipMenuAddItem", nullptr },
    { "GossipSendMenu", nullptr },
    { "GossipComplete", nullptr },
    { "GossipClearMenu", nullptr },

    // Other
    { "SendBroadcastMessage", nullptr },
    { "SendAreaTriggerMessage", nullptr },
    { "SendNotification", nullptr },
    { "SendPacket", nullptr },
    { "SendAddonMessage", nullptr },
    { "ModifyMoney", nullptr },
    { "LearnSpell", nullptr },
    { "LearnTalent", nullptr },
                     
    { "RemoveArenaSpellCooldowns", nullptr },
      
    { "RemoveItem", nullptr },
    { "RemoveLifetimeKills", nullptr },
    { "ResurrectPlayer", nullptr },
    { "EquipItem", nullptr },
    { "ResetSpellCooldown", nullptr },
    { "ResetTypeCooldowns", nullptr },
    { "ResetAllCooldowns", nullptr },
    { "GiveXP", nullptr },
    { "RemovePet", nullptr },
    { "SummonPet", nullptr },
    { "Say", nullptr },
    { "Yell", nullptr },
    { "TextEmote", nullptr },
    { "Whisper", nullptr },
    { "CompleteQuest", nullptr },
    { "IncompleteQuest", nullptr },
    { "FailQuest", nullptr },
    { "AddQuest", nullptr },
    { "RemoveQuest", nullptr },
    { "RemoveActiveQuest", nullptr },
    { "RemoveRewardedQuest", nullptr },
    { "AreaExploredOrEventHappens", nullptr },
    { "GroupEventHappens", nullptr },
    { "KilledMonsterCredit", nullptr },
    { "KilledPlayerCredit", nullptr },
    { "KillGOCredit", nullptr },
    { "TalkedToCreature", nullptr },
                                        
    { "ResetPetTalents", nullptr },
      
    { "AddComboPoints", nullptr },
    { "GainSpellComboPoints", nullptr },
    { "ClearComboPoints", nullptr },
    { "RemoveSpell", nullptr },
    { "ResetTalents", nullptr },
    { "ResetTalentsCost", nullptr },
    { "AddTalent", nullptr },
    { "RemoveFromGroup", nullptr },
    { "KillPlayer", nullptr },
    { "DurabilityLossAll", nullptr },
    { "DurabilityLoss", nullptr },
    { "DurabilityPointsLoss", nullptr },
    { "DurabilityPointsLossAll", nullptr },
    { "DurabilityPointLossForEquipSlot", nullptr },
    { "DurabilityRepairAll", nullptr },
    { "DurabilityRepair", nullptr },
                                  
    { "ModifyHonorPoints", nullptr },
    { "ModifyArenaPoints", nullptr },
      
    { "LeaveBattleground", nullptr },
    { "BindToInstance", nullptr },
    { "UnbindInstance", nullptr },
    { "UnbindAllInstances", nullptr },
    { "RemoveFromBattlegroundRaid", nullptr },
                                        
    { "ResetAchievements", nullptr },
      
    { "KickPlayer", nullptr },
    { "LogoutPlayer", nullptr },
    { "SendTrainerList", nullptr },
    { "SendListInventory", nullptr },
    { "SendShowBank", nullptr },
    { "SendTabardVendorActivate", nullptr },
    { "SendSpiritResurrect", nullptr },
    { "SendTaxiMenu", nullptr },
    { "SendUpdateWorldState", nullptr },
    { "RewardQuest", nullptr },
    { "SendAuctionMenu", nullptr },
    { "SendShowMailBox", nullptr },
    { "StartTaxi", nullptr },
    { "GossipSendPOI", nullptr },
    { "GossipAddQuests", nullptr },
    { "SendQuestTemplate", nullptr },
    { "SpawnBones", nullptr },
    { "RemovedInsignia", nullptr },
    { "SendGuildInvite", nullptr },
    { "Mute", nullptr },
    { "SummonPlayer", nullptr },
    { "SaveToDB", nullptr },
    { "GroupInvite", nullptr },
    { "GroupCreate", nullptr },
    { "SendCinematicStart", nullptr },
                                      
    { "SendMovieStart", nullptr },
      
              
    { "UpdateHonor", nullptr },
    { "ResetHonor", nullptr },
    { "ClearHonorInfo", nullptr },
      

    { NULL, NULL }
};

ElunaRegister<Creature> CreatureMethods[] =
{
    // Getters
    { "GetAITarget", nullptr },
    { "GetAITargets", nullptr },
    { "GetAITargetsCount", nullptr },
    { "GetHomePosition", nullptr },
    { "GetCorpseDelay", nullptr },
    { "GetCreatureSpellCooldownDelay", nullptr },
    { "GetScriptId", nullptr },
    { "GetAIName", nullptr },
    { "GetScriptName", nullptr },
                   
    { "GetAttackDistance", nullptr },
      
    { "GetAggroRange", nullptr },
    { "GetDefaultMovementType", nullptr },
    { "GetRespawnDelay", nullptr },
    { "GetWanderRadius", nullptr },
    { "GetCurrentWaypointId", nullptr },
                                   
    { "GetWaypointPath", nullptr },
    { "GetLootMode", nullptr },
      
    { "GetLootRecipient", nullptr },
    { "GetLootRecipientGroup", nullptr },
    { "GetNPCFlags", nullptr },
    { "GetExtraFlags", nullptr },
                                                      
    { "GetShieldBlockValue", nullptr },
      
    { "GetDBTableGUIDLow", nullptr },
    { "GetCreatureFamily", nullptr },

    // Setters
                                            
    { "SetRegeneratingHealth", nullptr },
      
    { "SetHover", nullptr },
    { "SetDisableGravity", nullptr },
    { "SetAggroEnabled", nullptr },
    { "SetNoCallAssistance", nullptr },
    { "SetNoSearchAssistance", nullptr },
    { "SetDefaultMovementType", nullptr },
    { "SetRespawnDelay", nullptr },
    { "SetWanderRadius", nullptr },
    { "SetInCombatWithZone", nullptr },
    { "SetDisableReputationGain", nullptr },
                                   
    { "SetLootMode", nullptr },
      
    { "SetNPCFlags", nullptr },
                                   
    { "SetReactState", nullptr },
      
    { "SetDeathState", nullptr },
    { "SetWalk", nullptr },
    { "SetHomePosition", nullptr },
    { "SetEquipmentSlots", nullptr },

    // Boolean
    { "IsRegeneratingHealth", nullptr },
                                            
    { "IsDungeonBoss", nullptr },
      
    { "IsWorldBoss", nullptr },
    { "IsRacialLeader", nullptr },
    { "IsCivilian", nullptr },
                                   
    { "IsTrigger", nullptr },
      
    { "IsGuard", nullptr },
    { "IsElite", nullptr },
    { "IsInEvadeMode", nullptr },
    { "HasCategoryCooldown", nullptr },
    { "CanWalk", nullptr },
    { "CanSwim", nullptr },
    { "CanAggro", nullptr },
                                   
    { "CanStartAttack", nullptr },
      
    { "HasSearchedAssistance", nullptr },
    { "IsTappedBy", nullptr },
    { "HasLootRecipient", nullptr },
    { "CanAssistTo", nullptr },
    { "IsTargetableForAttack", nullptr },
    { "CanCompleteQuest", nullptr },
    { "IsReputationGainDisabled", nullptr },
                                   
    { "IsDamageEnoughForLootingAndReward", nullptr },
    { "HasLootMode", nullptr },
      
    { "HasSpell", nullptr },
    { "HasQuest", nullptr },
    { "HasSpellCooldown", nullptr },
    { "CanFly", nullptr },

    // Other
    { "FleeToGetAssistance", nullptr },
    { "CallForHelp", nullptr },
    { "CallAssistance", nullptr },
    { "RemoveCorpse", nullptr },
    { "DespawnOrUnsummon", nullptr },
    { "Respawn", nullptr },
    { "AttackStart", nullptr },
                                   
    { "AddLootMode", nullptr },
    { "ResetLootMode", nullptr },
    { "RemoveLootMode", nullptr },
      
    { "SaveToDB", nullptr },
    { "SelectVictim", nullptr },
    { "MoveWaypoint", nullptr },
    { "UpdateEntry", nullptr },

    { NULL, NULL }
};

ElunaRegister<GameObject> GameObjectMethods[] =
{
    // Getters
    { "GetDisplayId", nullptr },
    { "GetGoState", nullptr },
    { "GetLootState", nullptr },
    { "GetLootRecipient", nullptr },
    { "GetLootRecipientGroup", nullptr },
    { "GetDBTableGUIDLow", nullptr },

    // Setters
    { "SetGoState", nullptr },
    { "SetLootState", nullptr },
    { "SetRespawnTime", nullptr },

    // Boolean
    { "IsTransport", nullptr },
    { "IsDestructible", nullptr },
    { "IsActive", nullptr },
    { "HasQuest", nullptr },
    { "IsSpawned", nullptr },

    // Other
    { "RemoveFromWorld", nullptr },
    { "UseDoorOrButton", nullptr },
    { "Despawn", nullptr },
    { "Respawn", nullptr },
    { "SaveToDB", nullptr },

    { NULL, NULL }
};

ElunaRegister<Item> ItemMethods[] =
{
    // Getters
    { "GetOwnerGUID", nullptr },
    { "GetOwner", nullptr },
    { "GetCount", nullptr },
    { "GetMaxStackCount", nullptr },
    { "GetSlot", nullptr },
    { "GetBagSlot", nullptr },
    { "GetEnchantmentId", nullptr },
    { "GetSpellId", nullptr },
    { "GetSpellTrigger", nullptr },
    { "GetItemLink", nullptr },
    { "GetClass", nullptr },
    { "GetSubClass", nullptr },
    { "GetName", nullptr },
    { "GetDisplayId", nullptr },
    { "GetQuality", nullptr },
    { "GetBuyCount", nullptr },
    { "GetBuyPrice", nullptr },
    { "GetSellPrice", nullptr },
    { "GetInventoryType", nullptr },
    { "GetAllowableClass", nullptr },
    { "GetAllowableRace", nullptr },
    { "GetItemLevel", nullptr },
    { "GetRequiredLevel", nullptr },
            
    { "GetStatsCount", nullptr },
      
    { "GetRandomProperty", nullptr },
               
    { "GetRandomSuffix", nullptr },
      
    { "GetItemSet", nullptr },
    { "GetBagSize", nullptr },

    // Setters
    { "SetOwner", nullptr },
    { "SetBinding", nullptr },
    { "SetCount", nullptr },

    // Boolean
    { "IsSoulBound", nullptr },
                                        
    { "IsBoundAccountWide", nullptr },
      
    { "IsBoundByEnchant", nullptr },
    { "IsNotBoundToPlayer", nullptr },
    { "IsLocked", nullptr },
    { "IsBag", nullptr },
               
    { "IsCurrencyToken", nullptr },
      
    { "IsNotEmptyBag", nullptr },
    { "IsBroken", nullptr },
    { "CanBeTraded", nullptr },
    { "IsInTrade", nullptr },
    { "IsInBag", nullptr },
    { "IsEquipped", nullptr },
    { "HasQuest", nullptr },
    { "IsPotion", nullptr },
                  
    { "IsWeaponVellum", nullptr },
    { "IsArmorVellum", nullptr },
      
    { "IsConjuredConsumable", nullptr },
    { "IsRefundExpired", nullptr },
    { "SetEnchantment", nullptr },
    { "ClearEnchantment", nullptr },

    // Other
    { "SaveToDB", nullptr },

    { NULL, NULL }
};

ElunaRegister<Aura> AuraMethods[] =
{
    // Getters
    { "GetCaster", nullptr },
    { "GetCasterGUID", nullptr },
    { "GetCasterLevel", nullptr },
    { "GetDuration", nullptr },
    { "GetMaxDuration", nullptr },
    { "GetAuraId", nullptr },
    { "GetStackAmount", nullptr },
    { "GetOwner", nullptr },

    // Setters
    { "SetDuration", nullptr },
    { "SetMaxDuration", nullptr },
    { "SetStackAmount", nullptr },

    // Other
    { "Remove", nullptr },

    { NULL, NULL }
};

ElunaRegister<Spell> SpellMethods[] =
{
    // Getters
    { "GetCaster", nullptr },
    { "GetCastTime", nullptr },
    { "GetEntry", nullptr },
    { "GetDuration", nullptr },
    { "GetPowerCost", nullptr },
    { "GetTargetDest", nullptr },
    { "GetTarget", nullptr },

    // Setters
    { "SetAutoRepeat", nullptr },

    // Boolean
    { "IsAutoRepeat", nullptr },

    // Other
    { "Cancel", nullptr },
    { "Cast", nullptr },
    { "Finish", nullptr },

    { NULL, NULL }
};

ElunaRegister<Quest> QuestMethods[] =
{
    // Getters
    { "GetId", nullptr },
    { "GetLevel", nullptr },
    { "GetMaxLevel", nullptr },
    { "GetMinLevel", nullptr },
    { "GetNextQuestId", nullptr },
    { "GetPrevQuestId", nullptr },
    { "GetNextQuestInChain", nullptr },
    { "GetFlags", nullptr },
    { "GetType", nullptr },

    // Boolean
    { "HasFlag", nullptr },
               
    { "IsDaily", nullptr },
      
    { "IsRepeatable", nullptr },

    { NULL, NULL }
};

ElunaRegister<Group> GroupMethods[] =
{
    // Getters
    { "GetMembers", nullptr },
    { "GetLeaderGUID", nullptr },
    { "GetGUID", nullptr },
    { "GetMemberGroup", nullptr },
    { "GetMemberGUID", nullptr },
    { "GetMembersCount", nullptr },

    // Setters
    { "SetLeader", nullptr },
    { "SetMembersGroup", nullptr },
    { "SetTargetIcon", nullptr },

    // Boolean
    { "IsLeader", nullptr },
    { "AddMember", nullptr },
    { "RemoveMember", nullptr },
    { "Disband", nullptr },
    { "IsFull", nullptr },
                                       
    { "IsLFGGroup", nullptr },
      
    { "IsRaidGroup", nullptr },
    { "IsBGGroup", nullptr },
    { "IsBFGroup", nullptr },
    { "IsMember", nullptr },
    { "IsAssistant", nullptr },
    { "SameSubGroup", nullptr },
    { "HasFreeSlotSubGroup", nullptr },

    // Other
    { "SendPacket", nullptr },
    { "ConvertToLFG", nullptr},
    { "ConvertToRaid", nullptr },

    { NULL, NULL }
};

ElunaRegister<Guild> GuildMethods[] =
{
    // Getters
    { "GetMembers", nullptr },
    { "GetLeader", nullptr },
    { "GetLeaderGUID", nullptr },
    { "GetId", nullptr },
    { "GetName", nullptr },
    { "GetMOTD", nullptr },
    { "GetInfo", nullptr },
    { "GetMemberCount", nullptr },

    // Setters
               
    { "SetBankTabText", nullptr },
      
    { "SetMemberRank", nullptr },
                                                      
    { "SetLeader", nullptr },
      

    // Other
    { "SendPacket", nullptr },
    { "SendPacketToRanked", nullptr },
    { "Disband", nullptr },
    { "AddMember", nullptr },
    { "DeleteMember", nullptr },

    { NULL, NULL }
};

#ifndef CLASSIC
#ifndef TBC
ElunaRegister<Vehicle> VehicleMethods[] =
{
    // Getters
    { "GetOwner", nullptr },
    { "GetEntry", nullptr },
    { "GetPassenger", nullptr },

    // Boolean
    { "IsOnBoard", nullptr },

    // Other
    { "AddPassenger", nullptr },
    { "RemovePassenger", nullptr },

    { NULL, NULL }
};
#endif
#endif

ElunaRegister<ElunaQuery> QueryMethods[] =
{
    // Getters
    { "GetColumnCount", nullptr },
    { "GetRowCount", nullptr },
    { "GetRow", nullptr },
    { "GetBool", nullptr },
    { "GetUInt8", nullptr },
    { "GetUInt16", nullptr },
    { "GetUInt32", nullptr },
    { "GetUInt64", nullptr },
    { "GetInt8", nullptr },
    { "GetInt16", nullptr },
    { "GetInt32", nullptr },
    { "GetInt64", nullptr },
    { "GetFloat", nullptr },
    { "GetDouble", nullptr },
    { "GetString", nullptr },

    // Boolean
    { "NextRow", nullptr },
    { "IsNull", nullptr },

    { NULL, NULL }
};

ElunaRegister<WorldPacket> PacketMethods[] =
{
    // Getters
    { "GetOpcode", nullptr },
    { "GetSize", nullptr },

    // Setters
    { "SetOpcode", nullptr },

    // Readers
    { "ReadByte", nullptr },
    { "ReadUByte", nullptr },
    { "ReadShort", nullptr },
    { "ReadUShort", nullptr },
    { "ReadLong", nullptr },
    { "ReadULong", nullptr },
    { "ReadGUID", nullptr },
    { "ReadString", nullptr },
    { "ReadFloat", nullptr },
    { "ReadDouble", nullptr },

    // Writers
    { "WriteByte", nullptr },
    { "WriteUByte", nullptr },
    { "WriteShort", nullptr },
    { "WriteUShort", nullptr },
    { "WriteLong", nullptr },
    { "WriteULong", nullptr },
    { "WriteGUID", nullptr },
    { "WriteString", nullptr },
    { "WriteFloat", nullptr },
    { "WriteDouble", nullptr },

    { NULL, NULL }
};

ElunaRegister<Map> MapMethods[] =
{
    // Getters
    { "GetName", nullptr },
    { "GetDifficulty", nullptr },
    { "GetInstanceId", nullptr },
    { "GetInstanceData", nullptr },
    { "GetPlayerCount", nullptr },
    { "GetPlayers", nullptr },
    { "GetMapId", nullptr },
    { "GetAreaId", nullptr },
    { "GetHeight", nullptr },
    { "GetWorldObject", nullptr },

    // Setters
    { "SetWeather", nullptr },

    // Boolean
               
    { "IsArena", nullptr },
      
    { "IsBattleground", nullptr },
    { "IsDungeon", nullptr },
    { "IsEmpty", nullptr },
               
    { "IsHeroic", nullptr },
      
    { "IsRaid", nullptr },

    // Other
    { "SaveInstanceData", nullptr },

    { NULL, NULL }
};

ElunaRegister<Corpse> CorpseMethods[] =
{
    // Getters
    { "GetOwnerGUID", nullptr },
    { "GetGhostTime", nullptr },
    { "GetType", nullptr },

    // Other
    { "ResetGhostTime", nullptr },
    { "SaveToDB", nullptr },

    { NULL, NULL }
};

ElunaRegister<BattleGround> BattleGroundMethods[] =
{
    // Getters
    { "GetName", nullptr },
    { "GetAlivePlayersCountByTeam", nullptr },
    { "GetMap", nullptr },
    { "GetBonusHonorFromKillCount", nullptr },
                   
    { "GetBracketId", nullptr },
      
    { "GetEndTime", nullptr },
    { "GetFreeSlotsForTeam", nullptr },
    { "GetInstanceId", nullptr },
    { "GetMapId", nullptr },
    { "GetTypeId", nullptr },
    { "GetMaxLevel", nullptr },
    { "GetMinLevel", nullptr },
    { "GetMaxPlayers", nullptr },
    { "GetMinPlayers", nullptr },
    { "GetMaxPlayersPerTeam", nullptr },
    { "GetMinPlayersPerTeam", nullptr },
    { "GetWinner", nullptr },
    { "GetStatus", nullptr },

    { NULL, NULL }
};

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
    ElunaGlobal::SetMethods(E, GlobalMethods, LuaGlobalFunctions::GlobalMethodsOverride);

    ElunaTemplate<Object>::Register(E, "Object");
    ElunaTemplate<Object>::SetMethods(E, ObjectMethods, LuaObject::ObjectMethodsOverride);

    ElunaTemplate<WorldObject>::Register(E, "WorldObject");
    ElunaTemplate<WorldObject>::SetMethods(E, ObjectMethods, LuaObject::ObjectMethodsOverride);
    ElunaTemplate<WorldObject>::SetMethods(E, WorldObjectMethods, LuaWorldObject::WorldObjectMethodsOverride);

    ElunaTemplate<Unit>::Register(E, "Unit");
    ElunaTemplate<Unit>::SetMethods(E, ObjectMethods, LuaObject::ObjectMethodsOverride);
    ElunaTemplate<Unit>::SetMethods(E, WorldObjectMethods, LuaWorldObject::WorldObjectMethodsOverride);
    ElunaTemplate<Unit>::SetMethods(E, UnitMethods, LuaUnit::UnitMethodsOverride);

    ElunaTemplate<Player>::Register(E, "Player");
    ElunaTemplate<Player>::SetMethods(E, ObjectMethods, LuaObject::ObjectMethodsOverride);
    ElunaTemplate<Player>::SetMethods(E, WorldObjectMethods, LuaWorldObject::WorldObjectMethodsOverride);
    ElunaTemplate<Player>::SetMethods(E, UnitMethods, LuaUnit::UnitMethodsOverride);
    ElunaTemplate<Player>::SetMethods(E, PlayerMethods, LuaPlayer::PlayerMethodsOverride);

    ElunaTemplate<Creature>::Register(E, "Creature");
    ElunaTemplate<Creature>::SetMethods(E, ObjectMethods, LuaObject::ObjectMethodsOverride);
    ElunaTemplate<Creature>::SetMethods(E, WorldObjectMethods, LuaWorldObject::WorldObjectMethodsOverride);
    ElunaTemplate<Creature>::SetMethods(E, UnitMethods, LuaUnit::UnitMethodsOverride);
    ElunaTemplate<Creature>::SetMethods(E, CreatureMethods, LuaCreature::CreatureMethodsOverride);

    ElunaTemplate<GameObject>::Register(E, "GameObject");
    ElunaTemplate<GameObject>::SetMethods(E, ObjectMethods, LuaObject::ObjectMethodsOverride);
    ElunaTemplate<GameObject>::SetMethods(E, WorldObjectMethods, LuaWorldObject::WorldObjectMethodsOverride);
    ElunaTemplate<GameObject>::SetMethods(E, GameObjectMethods, LuaGameObject::GameObjectMethodsOverride);

    ElunaTemplate<Corpse>::Register(E, "Corpse");
    ElunaTemplate<Corpse>::SetMethods(E, ObjectMethods, LuaObject::ObjectMethodsOverride);
    ElunaTemplate<Corpse>::SetMethods(E, WorldObjectMethods, LuaWorldObject::WorldObjectMethodsOverride);
    ElunaTemplate<Corpse>::SetMethods(E, CorpseMethods, LuaCorpse::CorpseMethodsOverride);

    ElunaTemplate<Item>::Register(E, "Item");
    ElunaTemplate<Item>::SetMethods(E, ObjectMethods, LuaObject::ObjectMethodsOverride);
    ElunaTemplate<Item>::SetMethods(E, ItemMethods, LuaItem::ItemMethodsOverride);

#ifndef CLASSIC
#ifndef TBC
    ElunaTemplate<Vehicle>::Register(E, "Vehicle");
    ElunaTemplate<Vehicle>::SetMethods(E, VehicleMethods, LuaVehicle::VehicleMethodsOverride);
#endif
#endif

    ElunaTemplate<Group>::Register(E, "Group");
    ElunaTemplate<Group>::SetMethods(E, GroupMethods, LuaGroup::GroupMethodsOverride);

    ElunaTemplate<Guild>::Register(E, "Guild");
    ElunaTemplate<Guild>::SetMethods(E, GuildMethods, LuaGuild::GuildMethodsOverride);

    ElunaTemplate<Aura>::Register(E, "Aura");
    ElunaTemplate<Aura>::SetMethods(E, AuraMethods, LuaAura::AuraMethodsOverride);

    ElunaTemplate<Spell>::Register(E, "Spell");
    ElunaTemplate<Spell>::SetMethods(E, SpellMethods, LuaSpell::SpellMethodsOverride);

    ElunaTemplate<Quest>::Register(E, "Quest");
    ElunaTemplate<Quest>::SetMethods(E, QuestMethods, LuaQuest::QuestMethodsOverride);

    ElunaTemplate<Map>::Register(E, "Map");
    ElunaTemplate<Map>::SetMethods(E, MapMethods, LuaMap::MapMethodsOverride);

    ElunaTemplate<BattleGround>::Register(E, "BattleGround");
    ElunaTemplate<BattleGround>::SetMethods(E, BattleGroundMethods, LuaBattleGround::BattleGroundMethodsOverride);

    ElunaTemplate<WorldPacket>::Register(E, "WorldPacket", true);
    ElunaTemplate<WorldPacket>::SetMethods(E, PacketMethods, LuaPacket::PacketMethodsOverride);

    ElunaTemplate<ElunaQuery>::Register(E, "ElunaQuery", true);
    ElunaTemplate<ElunaQuery>::SetMethods(E, QueryMethods, LuaQuery::QueryMethodsOverride);

    ElunaTemplate<long long>::Register(E, "long long", true);

    ElunaTemplate<unsigned long long>::Register(E, "unsigned long long", true);
}
