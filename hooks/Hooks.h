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
        SPELL_EVENT_ON_AURA_APPLICATION                 = 2,    // (event, aura, mode, apply)
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
    static std::pair<const HookStorage*, size_t> getHooks() { return { HookTypeTable, HookTypeTableSize}; }

private:
    static constexpr EventEntry PacketEventsTable[] = {
        {Hooks::PACKET_EVENT_ON_PACKET_RECEIVE,                 "on_receive"},
        {Hooks::PACKET_EVENT_ON_PACKET_RECEIVE_UNKNOWN,         "on_receive_unk"},
        {Hooks::PACKET_EVENT_ON_PACKET_SEND,                    "on_send"}
    };

    static constexpr EventEntry ServerEventsTable[] = {
        {Hooks::SERVER_EVENT_ON_NETWORK_START,                  "on_network_start"},
        {Hooks::SERVER_EVENT_ON_NETWORK_STOP,                   "on_network_stop"},
        {Hooks::SERVER_EVENT_ON_SOCKET_OPEN,                    "on_socket_open"},
        {Hooks::SERVER_EVENT_ON_SOCKET_CLOSE,                   "on_socket_close"},
        {Hooks::SERVER_EVENT_ON_PACKET_RECEIVE,                 "on_packet_receive"},
        {Hooks::SERVER_EVENT_ON_PACKET_RECEIVE_UNKNOWN,         "on_packet_receive_unk"},
        {Hooks::SERVER_EVENT_ON_PACKET_SEND,                    "on_packet_send"},
        {Hooks::WORLD_EVENT_ON_OPEN_STATE_CHANGE,               "on_open_state_change"},
        {Hooks::WORLD_EVENT_ON_CONFIG_LOAD,                     "on_config_load"},
        {Hooks::WORLD_EVENT_ON_SHUTDOWN_INIT,                   "on_shutdown_init"},
        {Hooks::WORLD_EVENT_ON_SHUTDOWN_CANCEL,                 "on_shutdown_cancel"},
        {Hooks::WORLD_EVENT_ON_UPDATE,                          "on_world_update"},
        {Hooks::WORLD_EVENT_ON_STARTUP,                         "on_world_startup"},
        {Hooks::WORLD_EVENT_ON_SHUTDOWN,                        "on_world_shutdown"},
        {Hooks::ELUNA_EVENT_ON_LUA_STATE_CLOSE,                 "on_lua_state_close"},
        {Hooks::MAP_EVENT_ON_CREATE,                            "on_map_create"},
        {Hooks::MAP_EVENT_ON_DESTROY,                           "on_map_destroy"},
        {Hooks::MAP_EVENT_ON_GRID_LOAD,                         "on_map_grid_load"},
        {Hooks::MAP_EVENT_ON_GRID_UNLOAD,                       "on_map_grid_unload"},
        {Hooks::MAP_EVENT_ON_PLAYER_ENTER,                      "on_map_player_enter"},
        {Hooks::MAP_EVENT_ON_PLAYER_LEAVE,                      "on_map_player_leave"},
        {Hooks::MAP_EVENT_ON_UPDATE,                            "on_map_update"},
        {Hooks::TRIGGER_EVENT_ON_TRIGGER,                       "on_event_trigger"},
        {Hooks::WEATHER_EVENT_ON_CHANGE,                        "on_weather_change"},
        {Hooks::AUCTION_EVENT_ON_ADD,                           "on_auction_add"},
        {Hooks::AUCTION_EVENT_ON_REMOVE,                        "on_auction_remove"},
        {Hooks::AUCTION_EVENT_ON_SUCCESSFUL,                    "on_auction_successful"},
        {Hooks::AUCTION_EVENT_ON_EXPIRE,                        "on_auction_expire"},
        {Hooks::ADDON_EVENT_ON_MESSAGE,                         "on_addon_message"},
        {Hooks::WORLD_EVENT_ON_DELETE_CREATURE,                 "on_world_delete_creature"},
        {Hooks::WORLD_EVENT_ON_DELETE_GAMEOBJECT,               "on_world_delete_gameobject"},
        {Hooks::ELUNA_EVENT_ON_LUA_STATE_OPEN,                  "on_lua_state_open"},
        {Hooks::GAME_EVENT_START,                               "on_game_start"},
        {Hooks::GAME_EVENT_STOP,                                "on_game_stop"}
    };

    static constexpr EventEntry PlayerEventsTable[] = {
        {Hooks::PLAYER_EVENT_ON_CHARACTER_CREATE,               "on_character_create"},
        {Hooks::PLAYER_EVENT_ON_CHARACTER_DELETE,               "on_character_delete"},
        {Hooks::PLAYER_EVENT_ON_LOGIN,                          "on_login"},
        {Hooks::PLAYER_EVENT_ON_LOGOUT,                         "on_logout"},
        {Hooks::PLAYER_EVENT_ON_SPELL_CAST,                     "on_spell_cast"},
        {Hooks::PLAYER_EVENT_ON_KILL_PLAYER,                    "on_kill_player"},
        {Hooks::PLAYER_EVENT_ON_KILL_CREATURE,                  "on_kill_creature"},
        {Hooks::PLAYER_EVENT_ON_KILLED_BY_CREATURE,             "on_killed_by_creature"},
        {Hooks::PLAYER_EVENT_ON_DUEL_REQUEST,                   "on_duel_request"},
        {Hooks::PLAYER_EVENT_ON_DUEL_START,                     "on_duel_start"},
        {Hooks::PLAYER_EVENT_ON_DUEL_END,                       "on_duel_end"},
        {Hooks::PLAYER_EVENT_ON_GIVE_XP,                        "on_give_xp"},
        {Hooks::PLAYER_EVENT_ON_LEVEL_CHANGE,                   "on_level_change"},
        {Hooks::PLAYER_EVENT_ON_MONEY_CHANGE,                   "on_money_change"},
        {Hooks::PLAYER_EVENT_ON_REPUTATION_CHANGE,              "on_reputation_change"},
        {Hooks::PLAYER_EVENT_ON_TALENTS_CHANGE,                 "on_talents_change"},
        {Hooks::PLAYER_EVENT_ON_TALENTS_RESET,                  "on_talents_reset"},
        {Hooks::PLAYER_EVENT_ON_CHAT,                           "on_chat"},
        {Hooks::PLAYER_EVENT_ON_WHISPER,                        "on_whisper"},
        {Hooks::PLAYER_EVENT_ON_GROUP_CHAT,                     "on_group_chat"},
        {Hooks::PLAYER_EVENT_ON_GUILD_CHAT,                     "on_guild_chat"},
        {Hooks::PLAYER_EVENT_ON_CHANNEL_CHAT,                   "on_channel_chat"},
        {Hooks::PLAYER_EVENT_ON_EMOTE,                          "on_emote"},
        {Hooks::PLAYER_EVENT_ON_TEXT_EMOTE,                     "on_text_emote"},
        {Hooks::PLAYER_EVENT_ON_SAVE,                           "on_save"},
        {Hooks::PLAYER_EVENT_ON_BIND_TO_INSTANCE,               "on_bind_to_instance"},
        {Hooks::PLAYER_EVENT_ON_UPDATE_ZONE,                    "on_update_zone"},
        {Hooks::PLAYER_EVENT_ON_MAP_CHANGE,                     "on_map_change"},
        {Hooks::PLAYER_EVENT_ON_EQUIP,                          "on_equip"},
        {Hooks::PLAYER_EVENT_ON_FIRST_LOGIN,                    "on_first_login"},
        {Hooks::PLAYER_EVENT_ON_CAN_USE_ITEM,                   "on_can_use_item"},
        {Hooks::PLAYER_EVENT_ON_LOOT_ITEM,                      "on_loot_item"},
        {Hooks::PLAYER_EVENT_ON_ENTER_COMBAT,                   "on_enter_combat"},
        {Hooks::PLAYER_EVENT_ON_LEAVE_COMBAT,                   "on_leave_combat"},
        {Hooks::PLAYER_EVENT_ON_REPOP,                          "on_repop"},
        {Hooks::PLAYER_EVENT_ON_RESURRECT,                      "on_resurrect"},
        {Hooks::PLAYER_EVENT_ON_LOOT_MONEY,                     "on_loot_money"},
        {Hooks::PLAYER_EVENT_ON_QUEST_ABANDON,                  "on_quest_abandon"},
        {Hooks::PLAYER_EVENT_ON_LEARN_TALENTS,                  "on_learn_talents"},
        {Hooks::PLAYER_EVENT_ON_ENVIRONMENTAL_DEATH,            "on_environmental_death"},
        {Hooks::PLAYER_EVENT_ON_TRADE_ACCEPT,                   "on_trade_accept"},
        {Hooks::PLAYER_EVENT_ON_COMMAND,                        "on_command"},
        {Hooks::PLAYER_EVENT_ON_SKILL_CHANGE,                   "on_skill_change"},
        {Hooks::PLAYER_EVENT_ON_LEARN_SPELL,                    "on_learn_spell"},
        {Hooks::PLAYER_EVENT_ON_ACHIEVEMENT_COMPLETE,           "on_achievement_complete"},
        {Hooks::PLAYER_EVENT_ON_DISCOVER_AREA,                  "on_discover_area"},
        {Hooks::PLAYER_EVENT_ON_UPDATE_AREA,                    "on_update_area"},
        {Hooks::PLAYER_EVENT_ON_TRADE_INIT,                     "on_trade_init"},
        {Hooks::PLAYER_EVENT_ON_SEND_MAIL,                      "on_send_mail"},
        {Hooks::PLAYER_EVENT_ON_QUEST_STATUS_CHANGED,           "on_quest_status_changed"}
    };

    static constexpr EventEntry GuildEventsTable[] = {
        {Hooks::GUILD_EVENT_ON_ADD_MEMBER,                      "on_add_member"},
        {Hooks::GUILD_EVENT_ON_REMOVE_MEMBER,                   "on_remove_member"},
        {Hooks::GUILD_EVENT_ON_MOTD_CHANGE,                     "on_motd_change"},
        {Hooks::GUILD_EVENT_ON_INFO_CHANGE,                     "on_info_change"},
        {Hooks::GUILD_EVENT_ON_CREATE,                          "on_create"},
        {Hooks::GUILD_EVENT_ON_DISBAND,                         "on_disband"},
        {Hooks::GUILD_EVENT_ON_MONEY_WITHDRAW,                  "on_money_withdraw"},
        {Hooks::GUILD_EVENT_ON_MONEY_DEPOSIT,                   "on_money_deposit"},
        {Hooks::GUILD_EVENT_ON_ITEM_MOVE,                       "on_item_move"},
        {Hooks::GUILD_EVENT_ON_EVENT,                           "on_event"},
        {Hooks::GUILD_EVENT_ON_BANK_EVENT,                      "on_bank_event"}
    };

    static constexpr EventEntry GroupEventsTable[] = {
        {Hooks::GROUP_EVENT_ON_MEMBER_ADD,                      "on_add_member"},
        {Hooks::GROUP_EVENT_ON_MEMBER_INVITE,                   "on_invite_member"},
        {Hooks::GROUP_EVENT_ON_MEMBER_REMOVE,                   "on_remove_member"},
        {Hooks::GROUP_EVENT_ON_LEADER_CHANGE,                   "on_leader_change"},
        {Hooks::GROUP_EVENT_ON_DISBAND,                         "on_disband"},
        {Hooks::GROUP_EVENT_ON_CREATE,                          "on_create"},
        {Hooks::GROUP_EVENT_ON_MEMBER_ACCEPT,                   "on_member_accept"},
    };

    static constexpr EventEntry VehicleEventsTable[] = {
        {Hooks::VEHICLE_EVENT_ON_INSTALL,                       "on_install"},
        {Hooks::VEHICLE_EVENT_ON_UNINSTALL,                     "on_uninstall"},
        {Hooks::VEHICLE_EVENT_ON_INSTALL_ACCESSORY,             "on_install_accessory"},
        {Hooks::VEHICLE_EVENT_ON_ADD_PASSENGER,                 "on_add_passenger"},
        {Hooks::VEHICLE_EVENT_ON_REMOVE_PASSENGER,              "on_remove_passenger"}
    };

    static constexpr EventEntry CreatureEventsTable[] = {
        {Hooks::CREATURE_EVENT_ON_ENTER_COMBAT,                 "on_enter_combat"},
        {Hooks::CREATURE_EVENT_ON_LEAVE_COMBAT,                 "on_leave_combat"},
        {Hooks::CREATURE_EVENT_ON_TARGET_DIED,                  "on_target_died"},
        {Hooks::CREATURE_EVENT_ON_DIED,                         "on_died"},
        {Hooks::CREATURE_EVENT_ON_SPAWN,                        "on_spawn"},
        {Hooks::CREATURE_EVENT_ON_REACH_WP,                     "on_reach_wp"},
        {Hooks::CREATURE_EVENT_ON_AIUPDATE,                     "on_ai_update"},
        {Hooks::CREATURE_EVENT_ON_RECEIVE_EMOTE,                "on_receive_emote"},
        {Hooks::CREATURE_EVENT_ON_DAMAGE_TAKEN,                 "on_damage_taken"},
        {Hooks::CREATURE_EVENT_ON_PRE_COMBAT,                   "on_pre_combat"},
        {Hooks::CREATURE_EVENT_ON_OWNER_ATTACKED,               "on_owner_attacked"},
        {Hooks::CREATURE_EVENT_ON_OWNER_ATTACKED_AT,            "on_owner_attacked_at"},
        {Hooks::CREATURE_EVENT_ON_HIT_BY_SPELL,                 "on_hit_by_spell"},
        {Hooks::CREATURE_EVENT_ON_SPELL_HIT_TARGET,             "on_spell_hit_target"},
        {Hooks::CREATURE_EVENT_ON_JUST_SUMMONED_CREATURE,       "on_just_summoned_creature"},
        {Hooks::CREATURE_EVENT_ON_SUMMONED_CREATURE_DESPAWN,    "on_summoned_creature_despawn"},
        {Hooks::CREATURE_EVENT_ON_SUMMONED_CREATURE_DIED,       "on_summoned_creature_died"},
        {Hooks::CREATURE_EVENT_ON_SUMMONED,                     "on_summoned"},
        {Hooks::CREATURE_EVENT_ON_RESET,                        "on_reset"},
        {Hooks::CREATURE_EVENT_ON_REACH_HOME,                   "on_reach_home"},
        {Hooks::CREATURE_EVENT_ON_CORPSE_REMOVED,               "on_corpse_removed"},
        {Hooks::CREATURE_EVENT_ON_MOVE_IN_LOS,                  "on_move_in_los"},
        {Hooks::CREATURE_EVENT_ON_DUMMY_EFFECT,                 "on_dummy_effect"},
        {Hooks::CREATURE_EVENT_ON_QUEST_ACCEPT,                 "on_quest_accept"},
        {Hooks::CREATURE_EVENT_ON_QUEST_REWARD,                 "on_quest_reward"},
        {Hooks::CREATURE_EVENT_ON_DIALOG_STATUS,                "on_dialog_status"},
        {Hooks::CREATURE_EVENT_ON_ADD,                          "on_add"},
        {Hooks::CREATURE_EVENT_ON_REMOVE,                       "on_remove"}
    };

    static constexpr EventEntry GameObjectEventsTable[] = {
        {Hooks::GAMEOBJECT_EVENT_ON_AIUPDATE,                   "on_ai_update"},
        {Hooks::GAMEOBJECT_EVENT_ON_SPAWN,                      "on_spawn"},
        {Hooks::GAMEOBJECT_EVENT_ON_DUMMY_EFFECT,               "on_dummy_effect"},
        {Hooks::GAMEOBJECT_EVENT_ON_QUEST_ACCEPT,               "on_quest_accept"},
        {Hooks::GAMEOBJECT_EVENT_ON_QUEST_REWARD,               "on_quest_reward"},
        {Hooks::GAMEOBJECT_EVENT_ON_DIALOG_STATUS,              "on_dialog_status"},
        {Hooks::GAMEOBJECT_EVENT_ON_DESTROYED,                  "on_destroyed"},
        {Hooks::GAMEOBJECT_EVENT_ON_DAMAGED,                    "on_damaged"},
        {Hooks::GAMEOBJECT_EVENT_ON_LOOT_STATE_CHANGE,          "on_loot_state_change"},
        {Hooks::GAMEOBJECT_EVENT_ON_GO_STATE_CHANGED,           "on_go_state_changed"},
        {Hooks::GAMEOBJECT_EVENT_ON_ADD,                        "on_add"},
        {Hooks::GAMEOBJECT_EVENT_ON_REMOVE,                     "on_remove"},
        {Hooks::GAMEOBJECT_EVENT_ON_USE,                        "on_use"}
    };

    static constexpr EventEntry SpellEventsTable[] = {
        {Hooks::SPELL_EVENT_ON_CAST,                            "on_cast"},
        {Hooks::SPELL_EVENT_ON_AURA_APPLICATION,                "on_aura_application" }
    };

    static constexpr EventEntry ItemEventsTable[] = {
        {Hooks::ITEM_EVENT_ON_DUMMY_EFFECT,                     "on_dummy_effect"},
        {Hooks::ITEM_EVENT_ON_USE,                              "on_use"},
        {Hooks::ITEM_EVENT_ON_QUEST_ACCEPT,                     "on_quest_accept"},
        {Hooks::ITEM_EVENT_ON_EXPIRE,                           "on_expire"},
        {Hooks::ITEM_EVENT_ON_REMOVE,                           "on_remove"},
        {Hooks::ITEM_EVENT_ON_ADD,                              "on_add"},
        {Hooks::ITEM_EVENT_ON_EQUIP,                            "on_equip"},
        {Hooks::ITEM_EVENT_ON_UNEQUIP,                          "on_unequip"}
    };

    static constexpr EventEntry GossipEventsTable[] = {
        {Hooks::GOSSIP_EVENT_ON_HELLO,                          "on_hello"},
        {Hooks::GOSSIP_EVENT_ON_SELECT,                         "on_select"}
    };

    static constexpr EventEntry BGEventsTable[] = {
        {Hooks::BG_EVENT_ON_START,                              "on_start"},
        {Hooks::BG_EVENT_ON_END,                                "on_end"},
        {Hooks::BG_EVENT_ON_CREATE,                             "on_create"},
        {Hooks::BG_EVENT_ON_PRE_DESTROY,                        "on_pre_destroy"}
    };


    static constexpr EventEntry InstanceEventsTable[] = {
        {Hooks::INSTANCE_EVENT_ON_INITIALIZE,                   "on_initialize"},
        {Hooks::INSTANCE_EVENT_ON_LOAD,                         "on_load"},
        {Hooks::INSTANCE_EVENT_ON_UPDATE,                       "on_update"},
        {Hooks::INSTANCE_EVENT_ON_PLAYER_ENTER,                 "on_player_enter"},
        {Hooks::INSTANCE_EVENT_ON_CREATURE_CREATE,              "on_creature_create"},
        {Hooks::INSTANCE_EVENT_ON_GAMEOBJECT_CREATE,            "on_gameobject_create"},
        {Hooks::INSTANCE_EVENT_ON_CHECK_ENCOUNTER_IN_PROGRESS,  "on_check_encounter_in_progress"}
    };

    static constexpr HookStorage HookTypeTable[] =
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
        { "map", InstanceEventsTable, sizeof(InstanceEventsTable) / sizeof(InstanceEventsTable[0])},
        { "instance", InstanceEventsTable, sizeof(InstanceEventsTable) / sizeof(InstanceEventsTable[0])},
    };
    static constexpr size_t HookTypeTableSize = sizeof(HookTypeTable) / sizeof(HookTypeTable[0]);
};

#endif // _HOOKS_H
