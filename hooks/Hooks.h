/*
 * Copyright (C) 2010 - 2024 Eluna Lua Engine <https://elunaluaengine.github.io/>
 * This program is free software licensed under GPL version 3
 * Please see the included DOCS/LICENSE.md for more information
 */

#ifndef _HOOKS_H
#define _HOOKS_H

#if defined ELUNA_CMANGOS
#include "Platform/Define.h"
#endif
#include <utility>

/*
 * A hook should be written in one of the following forms:
 *
 * A. If results will be IGNORED:
 *
 *     // Return early if there are no bindings.
 *     if (!WhateverBindings->HasBindingsFor(SOME_EVENT_TYPE))
 *         return;
 *
 *     // Lock out any other threads.
 *     LOCK_ELUNA;
 *
 *     // Push extra arguments, if any.
 *     Push(a);
 *     Push(b);
 *     Push(c);
 *
 *     // Call all event handlers.
 *     CallAllFunctions(WhateverBindings, SOME_EVENT_TYPE);
 *
 *
 * B. If results will be USED:
 *
 *     // Return early if there are no bindings.
 *     if (!WhateverBindings->HasBindingsFor(SOME_EVENT_TYPE))
 *          return;
 *
 *     // Lock out any other threads.
 *     LOCK_ELUNA;
 *
 *     // Push extra arguments, if any.
 *     Push(a);
 *     Push(b);
 *     Push(c);
 *
 *     // Setup the stack and get the number of functions pushed.
 *     // Last argument is 3 because we did 3 Pushes.
 *     int n = SetupStack(WhateverBindings, SOME_EVENT_TYPE, 3);
 *
 *     // Call each event handler in order and check results.
 *     while (n > 0)
 *     {
 *         // Call an event handler and decrement the function counter afterward.
 *         // Second-last argument is 3 because we did 3 Pushes.
 *         // Last argument is 2 because we want 2 results.
 *         int r = CallOneFunction(n--, 3, 2);
 *
 *         // Results can be popped using `r`.
 *         int first = CHECKVAL<int>(L, r + 0);
 *         int second = CHECKVAL<int>(L, r + 1);
 *
 *         // Pop the results off the stack.
 *         lua_pop(L, 2);
 *     }
 *
 *     // Clean-up the stack. Argument is 3 because we did 3 Pushes.
 *     CleanUpStack(3);
 */

namespace Hooks
{
    enum RegisterTypes : uint8
    {
        REGTYPE_PACKET,
        REGTYPE_SERVER,
        REGTYPE_PLAYER,
        REGTYPE_GUILD,
        REGTYPE_GROUP,
        REGTYPE_CREATURE,
        REGTYPE_CREATURE_UNIQUE,
        REGTYPE_VEHICLE,
        REGTYPE_CREATURE_GOSSIP,
        REGTYPE_GAMEOBJECT,
        REGTYPE_GAMEOBJECT_GOSSIP,
        REGTYPE_SPELL,
        REGTYPE_ITEM,
        REGTYPE_ITEM_GOSSIP,
        REGTYPE_PLAYER_GOSSIP,
        REGTYPE_BG,
        REGTYPE_MAP,
        REGTYPE_INSTANCE,
        REGTYPE_COUNT
    };

    enum PacketEvents
    {
        PACKET_EVENT_ON_PACKET_RECEIVE          =     5,       // (event, packet, player) - Player only if accessible. Can return false, newPacket
        PACKET_EVENT_ON_PACKET_RECEIVE_UNKNOWN  =     6,       // Not Implemented
        PACKET_EVENT_ON_PACKET_SEND             =     7,       // (event, packet, player) - Player only if accessible. Can return false

        PACKET_EVENT_COUNT
    };

    enum ServerEvents
    {
        // Server
        SERVER_EVENT_ON_NETWORK_START           =     1,       // Not Implemented
        SERVER_EVENT_ON_NETWORK_STOP            =     2,       // Not Implemented
        SERVER_EVENT_ON_SOCKET_OPEN             =     3,       // Not Implemented
        SERVER_EVENT_ON_SOCKET_CLOSE            =     4,       // Not Implemented
        SERVER_EVENT_ON_PACKET_RECEIVE          =     5,       // (event, packet, player) - Player only if accessible. Can return false, newPacket
        SERVER_EVENT_ON_PACKET_RECEIVE_UNKNOWN  =     6,       // Not Implemented
        SERVER_EVENT_ON_PACKET_SEND             =     7,       // (event, packet, player) - Player only if accessible. Can return false

        // World
        WORLD_EVENT_ON_OPEN_STATE_CHANGE        =     8,        // (event, open) - Needs core support on Mangos
        WORLD_EVENT_ON_CONFIG_LOAD              =     9,        // (event, reload)
        // UNUSED                               =     10,
        WORLD_EVENT_ON_SHUTDOWN_INIT            =     11,       // (event, code, mask)
        WORLD_EVENT_ON_SHUTDOWN_CANCEL          =     12,       // (event)
        WORLD_EVENT_ON_UPDATE                   =     13,       // (event, diff)
        WORLD_EVENT_ON_STARTUP                  =     14,       // (event)
        WORLD_EVENT_ON_SHUTDOWN                 =     15,       // (event)

        // Eluna
        ELUNA_EVENT_ON_LUA_STATE_CLOSE          =     16,       // (event) - triggers just before shutting down eluna (on shutdown and restart)

        // Map
        MAP_EVENT_ON_CREATE                     =     17,       // (event, map)
        MAP_EVENT_ON_DESTROY                    =     18,       // (event, map)
        MAP_EVENT_ON_GRID_LOAD                  =     19,       // Not Implemented
        MAP_EVENT_ON_GRID_UNLOAD                =     20,       // Not Implemented
        MAP_EVENT_ON_PLAYER_ENTER               =     21,       // (event, map, player)
        MAP_EVENT_ON_PLAYER_LEAVE               =     22,       // (event, map, player)
        MAP_EVENT_ON_UPDATE                     =     23,       // (event, map, diff)

        // Area trigger
        TRIGGER_EVENT_ON_TRIGGER                =     24,       // (event, player, triggerId) - Can return true

        // Weather
        WEATHER_EVENT_ON_CHANGE                 =     25,       // (event, zoneId, state, grade)

        // Auction house
        AUCTION_EVENT_ON_ADD                    =     26,       // (event, auctionId, owner, item, expireTime, buyout, startBid, currentBid, bidderGUIDLow)
        AUCTION_EVENT_ON_REMOVE                 =     27,       // (event, auctionId, owner, item, expireTime, buyout, startBid, currentBid, bidderGUIDLow)
        AUCTION_EVENT_ON_SUCCESSFUL             =     28,       // (event, auctionId, owner, item, expireTime, buyout, startBid, currentBid, bidderGUIDLow)
        AUCTION_EVENT_ON_EXPIRE                 =     29,       // (event, auctionId, owner, item, expireTime, buyout, startBid, currentBid, bidderGUIDLow)

        // AddOns
        ADDON_EVENT_ON_MESSAGE                  =     30,       // (event, sender, type, prefix, msg, target) - target can be nil/whisper_target/guild/group/channel. Can return false
        
        WORLD_EVENT_ON_DELETE_CREATURE          =     31,       // (event, creature)
        WORLD_EVENT_ON_DELETE_GAMEOBJECT        =     32,       // (event, gameobject)

        // Eluna
        ELUNA_EVENT_ON_LUA_STATE_OPEN           =     33,       // (event) - triggers after all scripts are loaded

        GAME_EVENT_START                        =     34,       // (event, gameeventid)
        GAME_EVENT_STOP                         =     35,       // (event, gameeventid)

        SERVER_EVENT_COUNT
    };

    enum PlayerEvents
    {
        PLAYER_EVENT_ON_CHARACTER_CREATE        =     1,        // (event, player)
        PLAYER_EVENT_ON_CHARACTER_DELETE        =     2,        // (event, guid)
        PLAYER_EVENT_ON_LOGIN                   =     3,        // (event, player)
        PLAYER_EVENT_ON_LOGOUT                  =     4,        // (event, player)
        PLAYER_EVENT_ON_SPELL_CAST              =     5,        // (event, player, spell, skipCheck)
        PLAYER_EVENT_ON_KILL_PLAYER             =     6,        // (event, killer, killed)
        PLAYER_EVENT_ON_KILL_CREATURE           =     7,        // (event, killer, killed)
        PLAYER_EVENT_ON_KILLED_BY_CREATURE      =     8,        // (event, killer, killed)
        PLAYER_EVENT_ON_DUEL_REQUEST            =     9,        // (event, target, challenger)
        PLAYER_EVENT_ON_DUEL_START              =     10,       // (event, player1, player2)
        PLAYER_EVENT_ON_DUEL_END                =     11,       // (event, winner, loser, type)
        PLAYER_EVENT_ON_GIVE_XP                 =     12,       // (event, player, amount, victim) - Can return new XP amount
        PLAYER_EVENT_ON_LEVEL_CHANGE            =     13,       // (event, player, oldLevel)
        PLAYER_EVENT_ON_MONEY_CHANGE            =     14,       // (event, player, amount) - Can return new money amount
        PLAYER_EVENT_ON_REPUTATION_CHANGE       =     15,       // (event, player, factionId, standing, incremental) - Can return new standing
        PLAYER_EVENT_ON_TALENTS_CHANGE          =     16,       // (event, player, points)
        PLAYER_EVENT_ON_TALENTS_RESET           =     17,       // (event, player, noCost)
        PLAYER_EVENT_ON_CHAT                    =     18,       // (event, player, msg, Type, lang) - Can return false, newMessage
        PLAYER_EVENT_ON_WHISPER                 =     19,       // (event, player, msg, Type, lang, receiver) - Can return false, newMessage
        PLAYER_EVENT_ON_GROUP_CHAT              =     20,       // (event, player, msg, Type, lang, group) - Can return false, newMessage
        PLAYER_EVENT_ON_GUILD_CHAT              =     21,       // (event, player, msg, Type, lang, guild) - Can return false, newMessage
        PLAYER_EVENT_ON_CHANNEL_CHAT            =     22,       // (event, player, msg, Type, lang, channel) - Can return false, newMessage
        PLAYER_EVENT_ON_EMOTE                   =     23,       // (event, player, emote) - Not triggered on any known emote
        PLAYER_EVENT_ON_TEXT_EMOTE              =     24,       // (event, player, textEmote, emoteNum, guid)
        PLAYER_EVENT_ON_SAVE                    =     25,       // (event, player)
        PLAYER_EVENT_ON_BIND_TO_INSTANCE        =     26,       // (event, player, difficulty, mapid, permanent)
        PLAYER_EVENT_ON_UPDATE_ZONE             =     27,       // (event, player, newZone, newArea)
        PLAYER_EVENT_ON_MAP_CHANGE              =     28,       // (event, player)

        // Custom
        PLAYER_EVENT_ON_EQUIP                   =     29,       // (event, player, item, bag, slot)
        PLAYER_EVENT_ON_FIRST_LOGIN             =     30,       // (event, player)
        PLAYER_EVENT_ON_CAN_USE_ITEM            =     31,       // (event, player, itemEntry) - Can return InventoryResult enum value
        PLAYER_EVENT_ON_LOOT_ITEM               =     32,       // (event, player, item, count)
        PLAYER_EVENT_ON_ENTER_COMBAT            =     33,       // (event, player, enemy)
        PLAYER_EVENT_ON_LEAVE_COMBAT            =     34,       // (event, player)
        PLAYER_EVENT_ON_REPOP                   =     35,       // (event, player)
        PLAYER_EVENT_ON_RESURRECT               =     36,       // (event, player)
        PLAYER_EVENT_ON_LOOT_MONEY              =     37,       // (event, player, amount)
        PLAYER_EVENT_ON_QUEST_ABANDON           =     38,       // (event, player, questId)
        PLAYER_EVENT_ON_LEARN_TALENTS           =     39,       // (event, player, talentId, talentRank, spellid)
        PLAYER_EVENT_ON_ENVIRONMENTAL_DEATH     =     40,       // (event, player, environmentalDamageType)
        PLAYER_EVENT_ON_TRADE_ACCEPT            =     41,       // (event, player, target) - Can return false to interrupt trade
        PLAYER_EVENT_ON_COMMAND                 =     42,       // (event, player, command) - player is nil if command used from console. Can return false
        PLAYER_EVENT_ON_SKILL_CHANGE            =     43,       // (event, player, skillId, skillValue) - Returns new skill level value
        PLAYER_EVENT_ON_LEARN_SPELL             =     44,       // (event, player, spellId)
        PLAYER_EVENT_ON_ACHIEVEMENT_COMPLETE    =     45,       // (event, player, achievementId)
        PLAYER_EVENT_ON_DISCOVER_AREA           =     46,       // (event, player, area)
        PLAYER_EVENT_ON_UPDATE_AREA             =     47,       // (event, player, oldArea, newArea)
        PLAYER_EVENT_ON_TRADE_INIT              =     48,       // (event, player, target) - Can return false to interrupt trade
        PLAYER_EVENT_ON_SEND_MAIL               =     49,       // (event, player, recipientGuid) - Can return false to interrupt sending
        // UNUSED                               =     50,       // (event, player)
        // UNUSED                               =     51,       // (event, player)
        // UNUSED                               =     52,       // (event, player)
        // UNUSED                               =     53,       // (event, player)
        PLAYER_EVENT_ON_QUEST_STATUS_CHANGED    =     54,       // (event, player, questId, status)

        PLAYER_EVENT_COUNT
    };

    enum GuildEvents
    {
        // Guild
        GUILD_EVENT_ON_ADD_MEMBER               =     1,       // (event, guild, player, rank)
        GUILD_EVENT_ON_REMOVE_MEMBER            =     2,       // (event, guild, player, isDisbanding)
        GUILD_EVENT_ON_MOTD_CHANGE              =     3,       // (event, guild, newMotd)
        GUILD_EVENT_ON_INFO_CHANGE              =     4,       // (event, guild, newInfo)
        GUILD_EVENT_ON_CREATE                   =     5,       // (event, guild, leader, name)  // Not on TC
        GUILD_EVENT_ON_DISBAND                  =     6,       // (event, guild)
        GUILD_EVENT_ON_MONEY_WITHDRAW           =     7,       // (event, guild, player, amount, isRepair) - Can return new money amount
        GUILD_EVENT_ON_MONEY_DEPOSIT            =     8,       // (event, guild, player, amount) - Can return new money amount
        GUILD_EVENT_ON_ITEM_MOVE                =     9,       // (event, guild, player, item, isSrcBank, srcContainer, srcSlotId, isDestBank, destContainer, destSlotId)   // TODO
        GUILD_EVENT_ON_EVENT                    =     10,      // (event, guild, eventType, plrGUIDLow1, plrGUIDLow2, newRank)  // TODO
        GUILD_EVENT_ON_BANK_EVENT               =     11,      // (event, guild, eventType, tabId, playerGUIDLow, itemOrMoney, itemStackCount, destTabId)

        GUILD_EVENT_COUNT
    };

    enum GroupEvents
    {
        // Group
        GROUP_EVENT_ON_MEMBER_ADD               =     1,       // (event, group, guid)
        GROUP_EVENT_ON_MEMBER_INVITE            =     2,       // (event, group, guid)
        GROUP_EVENT_ON_MEMBER_REMOVE            =     3,       // (event, group, guid, method, kicker, reason)
        GROUP_EVENT_ON_LEADER_CHANGE            =     4,       // (event, group, newLeaderGuid, oldLeaderGuid)
        GROUP_EVENT_ON_DISBAND                  =     5,       // (event, group)
        GROUP_EVENT_ON_CREATE                   =     6,       // (event, group, leaderGuid, groupType)
        GROUP_EVENT_ON_MEMBER_ACCEPT            =     7,       // (event, group, player) - Can return false to disable accepting

        GROUP_EVENT_COUNT
    };

    enum VehicleEvents
    {
        VEHICLE_EVENT_ON_INSTALL                =     1,    // (event, vehicle)
        VEHICLE_EVENT_ON_UNINSTALL              =     2,    // (event, vehicle)
        // UNUSED                               =     3,    // (event, vehicle)
        VEHICLE_EVENT_ON_INSTALL_ACCESSORY      =     4,    // (event, vehicle, creature)
        VEHICLE_EVENT_ON_ADD_PASSENGER          =     5,    // (event, vehicle, unit, seatId)
        VEHICLE_EVENT_ON_REMOVE_PASSENGER       =     6,    // (event, vehicle, unit)

        VEHICLE_EVENT_COUNT
    };

    enum CreatureEvents
    {
        CREATURE_EVENT_ON_ENTER_COMBAT                    = 1,  // (event, creature, target) - Can return true to stop normal action
        CREATURE_EVENT_ON_LEAVE_COMBAT                    = 2,  // (event, creature) - Can return true to stop normal action
        CREATURE_EVENT_ON_TARGET_DIED                     = 3,  // (event, creature, victim) - Can return true to stop normal action
        CREATURE_EVENT_ON_DIED                            = 4,  // (event, creature, killer) - Can return true to stop normal action
        CREATURE_EVENT_ON_SPAWN                           = 5,  // (event, creature) - Can return true to stop normal action
        CREATURE_EVENT_ON_REACH_WP                        = 6,  // (event, creature, type, id) - Can return true to stop normal action
        CREATURE_EVENT_ON_AIUPDATE                        = 7,  // (event, creature, diff) - Can return true to stop normal action
        CREATURE_EVENT_ON_RECEIVE_EMOTE                   = 8,  // (event, creature, player, emoteid) - Can return true to stop normal action
        CREATURE_EVENT_ON_DAMAGE_TAKEN                    = 9,  // (event, creature, attacker, damage) - Can return true to stop normal action, can return new damage as second return value.
        CREATURE_EVENT_ON_PRE_COMBAT                      = 10, // (event, creature, target) - Can return true to stop normal action
        // UNUSED
        CREATURE_EVENT_ON_OWNER_ATTACKED                  = 12, // (event, creature, target) - Can return true to stop normal action            // Not on mangos
        CREATURE_EVENT_ON_OWNER_ATTACKED_AT               = 13, // (event, creature, attacker) - Can return true to stop normal action          // Not on mangos
        CREATURE_EVENT_ON_HIT_BY_SPELL                    = 14, // (event, creature, caster, spellid) - Can return true to stop normal action
        CREATURE_EVENT_ON_SPELL_HIT_TARGET                = 15, // (event, creature, target, spellid) - Can return true to stop normal action
        // UNUSED                                         = 16, // (event, creature)
        // UNUSED                                         = 17, // (event, creature)
        // UNUSED                                         = 18, // (event, creature)
        CREATURE_EVENT_ON_JUST_SUMMONED_CREATURE          = 19, // (event, creature, summon) - Can return true to stop normal action
        CREATURE_EVENT_ON_SUMMONED_CREATURE_DESPAWN       = 20, // (event, creature, summon) - Can return true to stop normal action
        CREATURE_EVENT_ON_SUMMONED_CREATURE_DIED          = 21, // (event, creature, summon, killer) - Can return true to stop normal action    // Not on mangos
        CREATURE_EVENT_ON_SUMMONED                        = 22, // (event, creature, summoner) - Can return true to stop normal action
        CREATURE_EVENT_ON_RESET                           = 23, // (event, creature)
        CREATURE_EVENT_ON_REACH_HOME                      = 24, // (event, creature) - Can return true to stop normal action
        // UNUSED                                         = 25, // (event, creature)
        CREATURE_EVENT_ON_CORPSE_REMOVED                  = 26, // (event, creature, respawndelay) - Can return true to stop normal action, can return new respawndelay as second return value
        CREATURE_EVENT_ON_MOVE_IN_LOS                     = 27, // (event, creature, unit) - Can return true to stop normal action. Does not actually check LOS, just uses the sight range
        // UNUSED                                         = 28, // (event, creature)
        // UNUSED                                         = 29, // (event, creature)
        CREATURE_EVENT_ON_DUMMY_EFFECT                    = 30, // (event, caster, spellid, effindex, creature)
        CREATURE_EVENT_ON_QUEST_ACCEPT                    = 31, // (event, player, creature, quest) - Can return true
        // UNUSED                                         = 32, // (event, creature)
        // UNUSED                                         = 33, // (event, creature)
        CREATURE_EVENT_ON_QUEST_REWARD                    = 34, // (event, player, creature, quest, opt) - Can return true
        CREATURE_EVENT_ON_DIALOG_STATUS                   = 35, // (event, player, creature)
        CREATURE_EVENT_ON_ADD                             = 36, // (event, creature)
        CREATURE_EVENT_ON_REMOVE                          = 37, // (event, creature)
        CREATURE_EVENT_COUNT
    };

    enum GameObjectEvents
    {
        GAMEOBJECT_EVENT_ON_AIUPDATE                    = 1,    // (event, go, diff)
        GAMEOBJECT_EVENT_ON_SPAWN                       = 2,    // (event, go)
        GAMEOBJECT_EVENT_ON_DUMMY_EFFECT                = 3,    // (event, caster, spellid, effindex, go) - Can return true to stop normal action
        GAMEOBJECT_EVENT_ON_QUEST_ACCEPT                = 4,    // (event, player, go, quest) - Can return true to stop normal action
        GAMEOBJECT_EVENT_ON_QUEST_REWARD                = 5,    // (event, player, go, quest, opt) - Can return true to stop normal action
        GAMEOBJECT_EVENT_ON_DIALOG_STATUS               = 6,    // (event, player, go)
        GAMEOBJECT_EVENT_ON_DESTROYED                   = 7,    // (event, go, attacker)
        GAMEOBJECT_EVENT_ON_DAMAGED                     = 8,    // (event, go, attacker)
        GAMEOBJECT_EVENT_ON_LOOT_STATE_CHANGE           = 9,    // (event, go, state)
        GAMEOBJECT_EVENT_ON_GO_STATE_CHANGED            = 10,   // (event, go, state)
        // UNUSED                                       = 11,   // (event, gameobject)
        GAMEOBJECT_EVENT_ON_ADD                         = 12,   // (event, gameobject)
        GAMEOBJECT_EVENT_ON_REMOVE                      = 13,   // (event, gameobject)
        GAMEOBJECT_EVENT_ON_USE                         = 14,   // (event, go, player) - Can return true to stop normal action
        GAMEOBJECT_EVENT_COUNT
    };

    enum SpellEvents
    {
        SPELL_EVENT_ON_CAST                             = 1,    // (event, spell, skipCheck)
        SPELL_EVENT_COUNT
    };

    enum ItemEvents
    {
        ITEM_EVENT_ON_DUMMY_EFFECT                      = 1,    // (event, caster, spellid, effindex, item)
        ITEM_EVENT_ON_USE                               = 2,    // (event, player, item, target) - Can return false to stop the spell casting
        ITEM_EVENT_ON_QUEST_ACCEPT                      = 3,    // (event, player, item, quest) - Can return true
        ITEM_EVENT_ON_EXPIRE                            = 4,    // (event, player, itemid) - Can return true
        ITEM_EVENT_ON_REMOVE                            = 5,    // (event, player, item) - Can return true

        // Custom
        ITEM_EVENT_ON_ADD                               = 6,    // (event, player, item)
        ITEM_EVENT_ON_EQUIP                             = 7,    // (event, player, item, slot)
        ITEM_EVENT_ON_UNEQUIP                           = 8,    // (event, player, item, slot)

        ITEM_EVENT_COUNT
    };

    enum GossipEvents
    {
        GOSSIP_EVENT_ON_HELLO                           = 1,    // (event, player, object) - Object is the Creature/GameObject/Item. Can return false to do default action. For item gossip can return false to stop spell casting.
        GOSSIP_EVENT_ON_SELECT                          = 2,    // (event, player, object, sender, intid, code, menu_id) - Object is the Creature/GameObject/Item/Player, menu_id is only for player gossip. Can return false to do default action.
        GOSSIP_EVENT_COUNT
    };

    enum BGEvents
    {
        BG_EVENT_ON_START                               = 1,    // (event, bg, bgId, instanceId) - Needs to be added to TC
        BG_EVENT_ON_END                                 = 2,    // (event, bg, bgId, instanceId, winner) - Needs to be added to TC
        BG_EVENT_ON_CREATE                              = 3,    // (event, bg, bgId, instanceId) - Needs to be added to TC
        BG_EVENT_ON_PRE_DESTROY                         = 4,    // (event, bg, bgId, instanceId) - Needs to be added to TC
        BG_EVENT_COUNT
    };

    enum InstanceEvents
    {
        INSTANCE_EVENT_ON_INITIALIZE                    = 1,    // (event, instance_data, map)
        INSTANCE_EVENT_ON_LOAD                          = 2,    // (event, instance_data, map)
        INSTANCE_EVENT_ON_UPDATE                        = 3,    // (event, instance_data, map, diff)
        INSTANCE_EVENT_ON_PLAYER_ENTER                  = 4,    // (event, instance_data, map, player)
        INSTANCE_EVENT_ON_CREATURE_CREATE               = 5,    // (event, instance_data, map, creature)
        INSTANCE_EVENT_ON_GAMEOBJECT_CREATE             = 6,    // (event, instance_data, map, go)
        INSTANCE_EVENT_ON_CHECK_ENCOUNTER_IN_PROGRESS   = 7,    // (event, instance_data, map)
        INSTANCE_EVENT_COUNT
    };

};
struct EventEntry
{
    uint8 id;
    const char* name;
};

struct HookStorage
{
    const char* category;
    const EventEntry* events;
    size_t eventCount;
};

class HookToReadableString
{
public:
    static const HookStorage* getHooks() { return HookMegaTable; }

private:
    static constexpr EventEntry PacketEventsTable[] = {
        {Hooks::PACKET_EVENT_ON_PACKET_RECEIVE,"receive"},
        {Hooks::PACKET_EVENT_ON_PACKET_RECEIVE_UNKNOWN,"receive_unknown"},
        {Hooks::PACKET_EVENT_ON_PACKET_SEND,"packet_send"}
    };

    static constexpr EventEntry ServerEventsTable[] = {
        {Hooks::SERVER_EVENT_ON_NETWORK_START,"network_start"},
        {Hooks::SERVER_EVENT_ON_NETWORK_STOP,"network_stop"},
        {Hooks::SERVER_EVENT_ON_SOCKET_OPEN,"socket_open"},
        {Hooks::SERVER_EVENT_ON_SOCKET_CLOSE,"socket_close"},
        {Hooks::SERVER_EVENT_ON_PACKET_RECEIVE,"packet_receive"},
        {Hooks::SERVER_EVENT_ON_PACKET_RECEIVE_UNKNOWN,"packet_receive_unknown"},
        {Hooks::SERVER_EVENT_ON_PACKET_SEND,"packet_send"},
        {Hooks::WORLD_EVENT_ON_OPEN_STATE_CHANGE,"open_state_change"},
        {Hooks::WORLD_EVENT_ON_CONFIG_LOAD,"config_load"},
        {Hooks::WORLD_EVENT_ON_SHUTDOWN_INIT,"shutdown_init"},
        {Hooks::WORLD_EVENT_ON_SHUTDOWN_CANCEL,"shutdown_cancel"},
        {Hooks::WORLD_EVENT_ON_UPDATE,"world_update"},
        {Hooks::WORLD_EVENT_ON_STARTUP,"world_startup"},
        {Hooks::WORLD_EVENT_ON_SHUTDOWN,"world_shutdown"},
        {Hooks::ELUNA_EVENT_ON_LUA_STATE_CLOSE,"eluna_lua_state_close"},
        {Hooks::MAP_EVENT_ON_CREATE,"map_create"},
        {Hooks::MAP_EVENT_ON_DESTROY,"map_destroy"},
        {Hooks::MAP_EVENT_ON_GRID_LOAD,"map_grid_load"},
        {Hooks::MAP_EVENT_ON_GRID_UNLOAD,"map_grid_unload"},
        {Hooks::MAP_EVENT_ON_PLAYER_ENTER,"map_player_enter"},
        {Hooks::MAP_EVENT_ON_PLAYER_LEAVE,"map_player_leave"},
        {Hooks::MAP_EVENT_ON_UPDATE,"map_update"},
        {Hooks::TRIGGER_EVENT_ON_TRIGGER,"trigger_trigger"},
        {Hooks::WEATHER_EVENT_ON_CHANGE,"weather_change"},
        {Hooks::AUCTION_EVENT_ON_ADD,"auction_add"},
        {Hooks::AUCTION_EVENT_ON_REMOVE,"auction_remove"},
        {Hooks::AUCTION_EVENT_ON_SUCCESSFUL,"auction_successful"},
        {Hooks::AUCTION_EVENT_ON_EXPIRE,"auction_expire"},
        {Hooks::ADDON_EVENT_ON_MESSAGE,"addon_message"},
        {Hooks::WORLD_EVENT_ON_DELETE_CREATURE,"world_delete_creature"},
        {Hooks::WORLD_EVENT_ON_DELETE_GAMEOBJECT,"world_delete_gameobject"},
        {Hooks::ELUNA_EVENT_ON_LUA_STATE_OPEN,"eluna_lua_state_open"},
        {Hooks::GAME_EVENT_START,"game_start"},
        {Hooks::GAME_EVENT_STOP,"game_stop"}
    };

    static constexpr EventEntry PlayerEventsTable[] = {
        {Hooks::PLAYER_EVENT_ON_CHARACTER_CREATE,"character_create"},
        {Hooks::PLAYER_EVENT_ON_CHARACTER_DELETE,"character_delete"},
        {Hooks::PLAYER_EVENT_ON_LOGIN,"login"},
        {Hooks::PLAYER_EVENT_ON_LOGOUT,"logout"},
        {Hooks::PLAYER_EVENT_ON_SPELL_CAST,"spell_cast"},
        {Hooks::PLAYER_EVENT_ON_KILL_PLAYER,"kill_player"},
        {Hooks::PLAYER_EVENT_ON_KILL_CREATURE,"kill_creature"},
        {Hooks::PLAYER_EVENT_ON_KILLED_BY_CREATURE,"killed_by_creature"},
        {Hooks::PLAYER_EVENT_ON_DUEL_REQUEST,"duel_request"},
        {Hooks::PLAYER_EVENT_ON_DUEL_START,"duel_start"},
        {Hooks::PLAYER_EVENT_ON_DUEL_END,"duel_end"},
        {Hooks::PLAYER_EVENT_ON_GIVE_XP,"give_xp"},
        {Hooks::PLAYER_EVENT_ON_LEVEL_CHANGE,"level_change"},
        {Hooks::PLAYER_EVENT_ON_MONEY_CHANGE,"money_change"},
        {Hooks::PLAYER_EVENT_ON_REPUTATION_CHANGE,"reputation_change"},
        {Hooks::PLAYER_EVENT_ON_TALENTS_CHANGE,"talents_change"},
        {Hooks::PLAYER_EVENT_ON_TALENTS_RESET,"talents_reset"},
        {Hooks::PLAYER_EVENT_ON_CHAT,"chat"},
        {Hooks::PLAYER_EVENT_ON_WHISPER,"whisper"},
        {Hooks::PLAYER_EVENT_ON_GROUP_CHAT,"group_chat"},
        {Hooks::PLAYER_EVENT_ON_GUILD_CHAT,"guild_chat"},
        {Hooks::PLAYER_EVENT_ON_CHANNEL_CHAT,"channel_chat"},
        {Hooks::PLAYER_EVENT_ON_EMOTE,"emote"},
        {Hooks::PLAYER_EVENT_ON_TEXT_EMOTE,"text_emote"},
        {Hooks::PLAYER_EVENT_ON_SAVE,"save"},
        {Hooks::PLAYER_EVENT_ON_BIND_TO_INSTANCE,"bind_to_instance"},
        {Hooks::PLAYER_EVENT_ON_UPDATE_ZONE,"update_zone"},
        {Hooks::PLAYER_EVENT_ON_MAP_CHANGE,"map_change"},
        {Hooks::PLAYER_EVENT_ON_EQUIP,"equip"},
        {Hooks::PLAYER_EVENT_ON_FIRST_LOGIN,"first_login"},
        {Hooks::PLAYER_EVENT_ON_CAN_USE_ITEM,"can_use_item"},
        {Hooks::PLAYER_EVENT_ON_LOOT_ITEM,"loot_item"},
        {Hooks::PLAYER_EVENT_ON_ENTER_COMBAT,"enter_combat"},
        {Hooks::PLAYER_EVENT_ON_LEAVE_COMBAT,"leave_combat"},
        {Hooks::PLAYER_EVENT_ON_REPOP,"repop"},
        {Hooks::PLAYER_EVENT_ON_RESURRECT,"resurrect"},
        {Hooks::PLAYER_EVENT_ON_LOOT_MONEY,"loot_money"},
        {Hooks::PLAYER_EVENT_ON_QUEST_ABANDON,"quest_abandon"},
        {Hooks::PLAYER_EVENT_ON_LEARN_TALENTS,"learn_talents"},
        {Hooks::PLAYER_EVENT_ON_ENVIRONMENTAL_DEATH,"environmental_death"},
        {Hooks::PLAYER_EVENT_ON_TRADE_ACCEPT,"trade_accept"},
        {Hooks::PLAYER_EVENT_ON_COMMAND,"command"},
        {Hooks::PLAYER_EVENT_ON_SKILL_CHANGE,"skill_change"},
        {Hooks::PLAYER_EVENT_ON_LEARN_SPELL,"learn_spell"},
        {Hooks::PLAYER_EVENT_ON_ACHIEVEMENT_COMPLETE,"achievement_complete"},
        {Hooks::PLAYER_EVENT_ON_DISCOVER_AREA,"discover_area"},
        {Hooks::PLAYER_EVENT_ON_UPDATE_AREA,"update_area"},
        {Hooks::PLAYER_EVENT_ON_TRADE_INIT,"trade_init"},
        {Hooks::PLAYER_EVENT_ON_SEND_MAIL,"send_mail"},
        {Hooks::PLAYER_EVENT_ON_QUEST_STATUS_CHANGED,"quest_status_changed"}
    };

    static constexpr EventEntry GuildEventsTable[] = {
        {Hooks::GUILD_EVENT_ON_ADD_MEMBER,"add_member"},
        {Hooks::GUILD_EVENT_ON_REMOVE_MEMBER,"remove_member"},
        {Hooks::GUILD_EVENT_ON_MOTD_CHANGE,"motd_change"},
        {Hooks::GUILD_EVENT_ON_INFO_CHANGE,"info_change"},
        {Hooks::GUILD_EVENT_ON_CREATE,"create"},
        {Hooks::GUILD_EVENT_ON_DISBAND,"disband"},
        {Hooks::GUILD_EVENT_ON_MONEY_WITHDRAW,"money_withdraw"},
        {Hooks::GUILD_EVENT_ON_MONEY_DEPOSIT,"money_deposit"},
        {Hooks::GUILD_EVENT_ON_ITEM_MOVE,"item_move"},
        {Hooks::GUILD_EVENT_ON_EVENT,"event"},
        {Hooks::GUILD_EVENT_ON_BANK_EVENT,"bank_event"}
    };

    static constexpr EventEntry GroupEventsTable[] = {
        {Hooks::GROUP_EVENT_ON_MEMBER_ADD,"member_add"},
        {Hooks::GROUP_EVENT_ON_MEMBER_INVITE,"member_invite"},
        {Hooks::GROUP_EVENT_ON_MEMBER_REMOVE,"member_remove"},
        {Hooks::GROUP_EVENT_ON_LEADER_CHANGE,"leader_change"},
        {Hooks::GROUP_EVENT_ON_DISBAND,"disband"},
        {Hooks::GROUP_EVENT_ON_CREATE,"create"},
        {Hooks::GROUP_EVENT_ON_MEMBER_ACCEPT,"member_accept"},
    };

    static constexpr EventEntry VehicleEventsTable[] = {
        {Hooks::VEHICLE_EVENT_ON_INSTALL,"install"},
        {Hooks::VEHICLE_EVENT_ON_UNINSTALL,"uninstall"},
        {Hooks::VEHICLE_EVENT_ON_INSTALL_ACCESSORY,"install_accessory"},
        {Hooks::VEHICLE_EVENT_ON_ADD_PASSENGER,"add_passenger"},
        {Hooks::VEHICLE_EVENT_ON_REMOVE_PASSENGER,"remove_passenger"}
    };

    static constexpr EventEntry CreatureEventsTable[] = {
        {Hooks::CREATURE_EVENT_ON_ENTER_COMBAT,"enter_combat"},
        {Hooks::CREATURE_EVENT_ON_LEAVE_COMBAT,"leave_combat"},
        {Hooks::CREATURE_EVENT_ON_TARGET_DIED,"target_died"},
        {Hooks::CREATURE_EVENT_ON_DIED,"died"},
        {Hooks::CREATURE_EVENT_ON_SPAWN,"spawn"},
        {Hooks::CREATURE_EVENT_ON_REACH_WP,"reach_wp"},
        {Hooks::CREATURE_EVENT_ON_AIUPDATE,"aiupdate"},
        {Hooks::CREATURE_EVENT_ON_RECEIVE_EMOTE,"receive_emote"},
        {Hooks::CREATURE_EVENT_ON_DAMAGE_TAKEN,"damage_taken"},
        {Hooks::CREATURE_EVENT_ON_PRE_COMBAT,"pre_combat"},
        {Hooks::CREATURE_EVENT_ON_OWNER_ATTACKED,"owner_attacked"},
        {Hooks::CREATURE_EVENT_ON_OWNER_ATTACKED_AT,"owner_attacked_at"},
        {Hooks::CREATURE_EVENT_ON_HIT_BY_SPELL,"hit_by_spell"},
        {Hooks::CREATURE_EVENT_ON_SPELL_HIT_TARGET,"spell_hit_target"},
        {Hooks::CREATURE_EVENT_ON_JUST_SUMMONED_CREATURE,"just_summoned_creature"},
        {Hooks::CREATURE_EVENT_ON_SUMMONED_CREATURE_DESPAWN,"summoned_creature_despawn"},
        {Hooks::CREATURE_EVENT_ON_SUMMONED_CREATURE_DIED,"summoned_creature_died"},
        {Hooks::CREATURE_EVENT_ON_SUMMONED,"summoned"},
        {Hooks::CREATURE_EVENT_ON_RESET,"reset"},
        {Hooks::CREATURE_EVENT_ON_REACH_HOME,"reach_home"},
        {Hooks::CREATURE_EVENT_ON_CORPSE_REMOVED,"corpse_removed"},
        {Hooks::CREATURE_EVENT_ON_MOVE_IN_LOS,"move_in_los"},
        {Hooks::CREATURE_EVENT_ON_DUMMY_EFFECT,"dummy_effect"},
        {Hooks::CREATURE_EVENT_ON_QUEST_ACCEPT,"quest_accept"},
        {Hooks::CREATURE_EVENT_ON_QUEST_REWARD,"quest_reward"},
        {Hooks::CREATURE_EVENT_ON_DIALOG_STATUS,"dialog_status"},
        {Hooks::CREATURE_EVENT_ON_ADD,"add"},
        {Hooks::CREATURE_EVENT_ON_REMOVE,"remove"}
    };

    static constexpr EventEntry GameObjectEventsTable[] = {
        {Hooks::GAMEOBJECT_EVENT_ON_AIUPDATE,"aiupdate"},
        {Hooks::GAMEOBJECT_EVENT_ON_SPAWN,"spawn"},
        {Hooks::GAMEOBJECT_EVENT_ON_DUMMY_EFFECT,"dummy_effect"},
        {Hooks::GAMEOBJECT_EVENT_ON_QUEST_ACCEPT,"quest_accept"},
        {Hooks::GAMEOBJECT_EVENT_ON_QUEST_REWARD,"quest_reward"},
        {Hooks::GAMEOBJECT_EVENT_ON_DIALOG_STATUS,"dialog_status"},
        {Hooks::GAMEOBJECT_EVENT_ON_DESTROYED,"destroyed"},
        {Hooks::GAMEOBJECT_EVENT_ON_DAMAGED,"damaged"},
        {Hooks::GAMEOBJECT_EVENT_ON_LOOT_STATE_CHANGE,"loot_state_change"},
        {Hooks::GAMEOBJECT_EVENT_ON_GO_STATE_CHANGED,"go_state_changed"},
        {Hooks::GAMEOBJECT_EVENT_ON_ADD,"add"},
        {Hooks::GAMEOBJECT_EVENT_ON_REMOVE,"remove"},
        {Hooks::GAMEOBJECT_EVENT_ON_USE,"use"}
    };

    static constexpr EventEntry SpellEventsTable[] = {
        {Hooks::SPELL_EVENT_ON_CAST,"spell_cast"}
    };

    static constexpr EventEntry ItemEventsTable[] = {
        {Hooks::ITEM_EVENT_ON_DUMMY_EFFECT,"dummy_effect"},
        {Hooks::ITEM_EVENT_ON_USE,"use"},
        {Hooks::ITEM_EVENT_ON_QUEST_ACCEPT,"quest_accept"},
        {Hooks::ITEM_EVENT_ON_EXPIRE,"expire"},
        {Hooks::ITEM_EVENT_ON_REMOVE,"remove"},
        {Hooks::ITEM_EVENT_ON_ADD,"add"},
        {Hooks::ITEM_EVENT_ON_EQUIP,"equip"},
        {Hooks::ITEM_EVENT_ON_UNEQUIP,"unequip"}
    };

    static constexpr EventEntry GossipEventsTable[] = {
        {Hooks::GOSSIP_EVENT_ON_HELLO,"hello"},
        {Hooks::GOSSIP_EVENT_ON_SELECT,"select"}
    };

    static constexpr EventEntry BGEventsTable[] = {
        {Hooks::BG_EVENT_ON_START,"start"},
        {Hooks::BG_EVENT_ON_END,"end"},
        {Hooks::BG_EVENT_ON_CREATE,"create"},
        {Hooks::BG_EVENT_ON_PRE_DESTROY,"pre_destroy"}
    };

    static constexpr EventEntry InstanceEventsTable[] = {
        {Hooks::INSTANCE_EVENT_ON_INITIALIZE,"initialize"},
        {Hooks::INSTANCE_EVENT_ON_LOAD,"load"},
        {Hooks::INSTANCE_EVENT_ON_UPDATE,"update"},
        {Hooks::INSTANCE_EVENT_ON_PLAYER_ENTER,"player_enter"},
        {Hooks::INSTANCE_EVENT_ON_CREATURE_CREATE,"creature_create"},
        {Hooks::INSTANCE_EVENT_ON_GAMEOBJECT_CREATE,"gameobject_create"},
        {Hooks::INSTANCE_EVENT_ON_CHECK_ENCOUNTER_IN_PROGRESS,"check_encounter_in_progress"}
    };


    static constexpr HookStorage HookMegaTable[] =
    {
        { "packet", PacketEventsTable, sizeof(PacketEventsTable) / sizeof(PacketEventsTable[0])},
        { "server", ServerEventsTable, sizeof(ServerEventsTable) / sizeof(ServerEventsTable[0])},
        { "player", PlayerEventsTable, sizeof(PlayerEventsTable) / sizeof(PlayerEventsTable[0])},
        { "guild", GuildEventsTable, sizeof(GuildEventsTable) / sizeof(GuildEventsTable[0])},
        { "group", GroupEventsTable, sizeof(GroupEventsTable) / sizeof(GroupEventsTable[0])},
        { "vehicle", VehicleEventsTable, sizeof(VehicleEventsTable) / sizeof(VehicleEventsTable[0])},
        { "creature", CreatureEventsTable, sizeof(CreatureEventsTable) / sizeof(CreatureEventsTable[0])},
        { "gameobject", GameObjectEventsTable, sizeof(GameObjectEventsTable) / sizeof(GameObjectEventsTable[0])},
        { "spell", SpellEventsTable, sizeof(SpellEventsTable) / sizeof(SpellEventsTable[0])},
        { "item", ItemEventsTable, sizeof(ItemEventsTable) / sizeof(ItemEventsTable[0])},
        { "gossip", GossipEventsTable, sizeof(GossipEventsTable) / sizeof(GossipEventsTable[0])},
        { "bg", BGEventsTable, sizeof(BGEventsTable) / sizeof(BGEventsTable[0])},
        { "instance", InstanceEventsTable, sizeof(InstanceEventsTable) / sizeof(InstanceEventsTable[0])},
    };

};

#endif // _HOOKS_H
