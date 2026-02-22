/*
 * Copyright (C) 2010 - 2025 Eluna Lua Engine <https://elunaluaengine.github.io/>
 * This program is free software licensed under GPL version 3
 * Please see the included DOCS/LICENSE.md for more information
 */

#ifndef _HOOKS_H
#define _HOOKS_H

#if defined ELUNA_CMANGOS
#include "Platform/Define.h"
#endif
#include <utility>

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

template <typename T, size_t N>
constexpr size_t CountOf(const T(&)[N]) { return N; }

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

    // PACKET EVENTS
    #define PACKET_EVENTS_LIST(X) \
        X(PACKET_EVENT_ON_PACKET_RECEIVE,         5,  "on_receive")      \
        X(PACKET_EVENT_ON_PACKET_RECEIVE_UNKNOWN, 6,  "on_receive_unk")  \
        X(PACKET_EVENT_ON_PACKET_SEND,            7,  "on_send")

    enum PacketEvents
    {
    #define X(ID, VALUE, NAME) ID = VALUE,
        PACKET_EVENTS_LIST(X)
    #undef X
        PACKET_EVENT_COUNT
    };

    static constexpr EventEntry PacketEventsTable[] = {
    #define X(ID, VALUE, NAME) { Hooks::ID, NAME },
        PACKET_EVENTS_LIST(X)
    #undef X
    };

    // SERVER EVENTS
    #define SERVER_EVENTS_LIST(X) \
        /* Server */ \
        X(SERVER_EVENT_ON_NETWORK_START,          1,  "on_network_start")         \
        X(SERVER_EVENT_ON_NETWORK_STOP,           2,  "on_network_stop")          \
        X(SERVER_EVENT_ON_SOCKET_OPEN,            3,  "on_socket_open")           \
        X(SERVER_EVENT_ON_SOCKET_CLOSE,           4,  "on_socket_close")          \
        X(SERVER_EVENT_ON_PACKET_RECEIVE,         5,  "on_packet_receive")        \
        X(SERVER_EVENT_ON_PACKET_RECEIVE_UNKNOWN, 6,  "on_packet_receive_unk")    \
        X(SERVER_EVENT_ON_PACKET_SEND,            7,  "on_packet_send")           \
        /* World */ \
        X(WORLD_EVENT_ON_OPEN_STATE_CHANGE,       8,  "on_open_state_change")     \
        X(WORLD_EVENT_ON_CONFIG_LOAD,             9,  "on_config_load")           \
        /* 10 unused */ \
        X(WORLD_EVENT_ON_SHUTDOWN_INIT,           11, "on_shutdown_init")         \
        X(WORLD_EVENT_ON_SHUTDOWN_CANCEL,         12, "on_shutdown_cancel")       \
        X(WORLD_EVENT_ON_UPDATE,                  13, "on_world_update")          \
        X(WORLD_EVENT_ON_STARTUP,                 14, "on_world_startup")         \
        X(WORLD_EVENT_ON_SHUTDOWN,                15, "on_world_shutdown")        \
        /* Eluna */ \
        X(ELUNA_EVENT_ON_LUA_STATE_CLOSE,         16, "on_lua_state_close")       \
        /* Map */ \
        X(MAP_EVENT_ON_CREATE,                    17, "on_map_create")            \
        X(MAP_EVENT_ON_DESTROY,                   18, "on_map_destroy")           \
        X(MAP_EVENT_ON_GRID_LOAD,                 19, "on_map_grid_load")         \
        X(MAP_EVENT_ON_GRID_UNLOAD,               20, "on_map_grid_unload")       \
        X(MAP_EVENT_ON_PLAYER_ENTER,              21, "on_map_player_enter")      \
        X(MAP_EVENT_ON_PLAYER_LEAVE,              22, "on_map_player_leave")      \
        X(MAP_EVENT_ON_UPDATE,                    23, "on_map_update")            \
        /* Area trigger */ \
        X(TRIGGER_EVENT_ON_TRIGGER,               24, "on_event_trigger")         \
        /* Weather */ \
        X(WEATHER_EVENT_ON_CHANGE,                25, "on_weather_change")        \
        /* Auction house */ \
        X(AUCTION_EVENT_ON_ADD,                   26, "on_auction_add")           \
        X(AUCTION_EVENT_ON_REMOVE,                27, "on_auction_remove")        \
        X(AUCTION_EVENT_ON_SUCCESSFUL,            28, "on_auction_successful")    \
        X(AUCTION_EVENT_ON_EXPIRE,                29, "on_auction_expire")        \
        /* AddOns */ \
        X(ADDON_EVENT_ON_MESSAGE,                 30, "on_addon_message")         \
        X(WORLD_EVENT_ON_DELETE_CREATURE,         31, "on_world_delete_creature") \
        X(WORLD_EVENT_ON_DELETE_GAMEOBJECT,       32, "on_world_delete_gameobject") \
        /* Eluna */ \
        X(ELUNA_EVENT_ON_LUA_STATE_OPEN,          33, "on_lua_state_open")        \
        /* Game events */ \
        X(GAME_EVENT_START,                       34, "on_game_start")            \
        X(GAME_EVENT_STOP,                        35, "on_game_stop")

    enum ServerEvents
    {
    #define X(ID, VALUE, NAME) ID = VALUE,
        SERVER_EVENTS_LIST(X)
    #undef X
        SERVER_EVENT_COUNT
    };

    static constexpr EventEntry ServerEventsTable[] = {
    #define X(ID, VALUE, NAME) { Hooks::ID, NAME },
        SERVER_EVENTS_LIST(X)
    #undef X
    };

    // PLAYER EVENTS
    #define PLAYER_EVENTS_LIST(X) \
        X(PLAYER_EVENT_ON_CHARACTER_CREATE,        1,  "on_character_create")      \
        X(PLAYER_EVENT_ON_CHARACTER_DELETE,        2,  "on_character_delete")      \
        X(PLAYER_EVENT_ON_LOGIN,                   3,  "on_login")                 \
        X(PLAYER_EVENT_ON_LOGOUT,                  4,  "on_logout")                \
        X(PLAYER_EVENT_ON_SPELL_CAST,              5,  "on_spell_cast")            \
        X(PLAYER_EVENT_ON_KILL_PLAYER,             6,  "on_kill_player")           \
        X(PLAYER_EVENT_ON_KILL_CREATURE,           7,  "on_kill_creature")         \
        X(PLAYER_EVENT_ON_KILLED_BY_CREATURE,      8,  "on_killed_by_creature")    \
        X(PLAYER_EVENT_ON_DUEL_REQUEST,            9,  "on_duel_request")          \
        X(PLAYER_EVENT_ON_DUEL_START,              10, "on_duel_start")            \
        X(PLAYER_EVENT_ON_DUEL_END,                11, "on_duel_end")              \
        X(PLAYER_EVENT_ON_GIVE_XP,                 12, "on_give_xp")               \
        X(PLAYER_EVENT_ON_LEVEL_CHANGE,            13, "on_level_change")          \
        X(PLAYER_EVENT_ON_MONEY_CHANGE,            14, "on_money_change")          \
        X(PLAYER_EVENT_ON_REPUTATION_CHANGE,       15, "on_reputation_change")     \
        X(PLAYER_EVENT_ON_TALENTS_CHANGE,          16, "on_talents_change")        \
        X(PLAYER_EVENT_ON_TALENTS_RESET,           17, "on_talents_reset")         \
        X(PLAYER_EVENT_ON_CHAT,                    18, "on_chat")                  \
        X(PLAYER_EVENT_ON_WHISPER,                 19, "on_whisper")               \
        X(PLAYER_EVENT_ON_GROUP_CHAT,              20, "on_group_chat")            \
        X(PLAYER_EVENT_ON_GUILD_CHAT,              21, "on_guild_chat")            \
        X(PLAYER_EVENT_ON_CHANNEL_CHAT,            22, "on_channel_chat")          \
        X(PLAYER_EVENT_ON_EMOTE,                   23, "on_emote")                 \
        X(PLAYER_EVENT_ON_TEXT_EMOTE,              24, "on_text_emote")            \
        X(PLAYER_EVENT_ON_SAVE,                    25, "on_save")                  \
        X(PLAYER_EVENT_ON_BIND_TO_INSTANCE,        26, "on_bind_to_instance")      \
        X(PLAYER_EVENT_ON_UPDATE_ZONE,             27, "on_update_zone")           \
        X(PLAYER_EVENT_ON_MAP_CHANGE,              28, "on_map_change")            \
        X(PLAYER_EVENT_ON_EQUIP,                   29, "on_equip")                 \
        X(PLAYER_EVENT_ON_FIRST_LOGIN,             30, "on_first_login")           \
        X(PLAYER_EVENT_ON_CAN_USE_ITEM,            31, "on_can_use_item")          \
        X(PLAYER_EVENT_ON_LOOT_ITEM,               32, "on_loot_item")             \
        X(PLAYER_EVENT_ON_ENTER_COMBAT,            33, "on_enter_combat")          \
        X(PLAYER_EVENT_ON_LEAVE_COMBAT,            34, "on_leave_combat")          \
        X(PLAYER_EVENT_ON_REPOP,                   35, "on_repop")                 \
        X(PLAYER_EVENT_ON_RESURRECT,               36, "on_resurrect")             \
        X(PLAYER_EVENT_ON_LOOT_MONEY,              37, "on_loot_money")            \
        X(PLAYER_EVENT_ON_QUEST_ABANDON,           38, "on_quest_abandon")         \
        X(PLAYER_EVENT_ON_LEARN_TALENTS,           39, "on_learn_talents")         \
        X(PLAYER_EVENT_ON_ENVIRONMENTAL_DEATH,     40, "on_environmental_death")   \
        X(PLAYER_EVENT_ON_TRADE_ACCEPT,            41, "on_trade_accept")          \
        X(PLAYER_EVENT_ON_COMMAND,                 42, "on_command")               \
        X(PLAYER_EVENT_ON_SKILL_CHANGE,            43, "on_skill_change")          \
        X(PLAYER_EVENT_ON_LEARN_SPELL,             44, "on_learn_spell")           \
        X(PLAYER_EVENT_ON_ACHIEVEMENT_COMPLETE,    45, "on_achievement_complete")  \
        X(PLAYER_EVENT_ON_DISCOVER_AREA,           46, "on_discover_area")         \
        X(PLAYER_EVENT_ON_UPDATE_AREA,             47, "on_update_area")           \
        X(PLAYER_EVENT_ON_TRADE_INIT,              48, "on_trade_init")            \
        X(PLAYER_EVENT_ON_SEND_MAIL,               49, "on_send_mail")             \
        /* 50–53 unused */ \
        X(PLAYER_EVENT_ON_QUEST_STATUS_CHANGED,    54, "on_quest_status_changed")

    enum PlayerEvents
    {
    #define X(ID, VALUE, NAME) ID = VALUE,
        PLAYER_EVENTS_LIST(X)
    #undef X
        PLAYER_EVENT_COUNT
    };

    static constexpr EventEntry PlayerEventsTable[] = {
    #define X(ID, VALUE, NAME) { Hooks::ID, NAME },
        PLAYER_EVENTS_LIST(X)
    #undef X
    };

    // GUILD EVENTS
    #define GUILD_EVENTS_LIST(X) \
        X(GUILD_EVENT_ON_ADD_MEMBER,      1,  "on_add_member")      \
        X(GUILD_EVENT_ON_REMOVE_MEMBER,   2,  "on_remove_member")   \
        X(GUILD_EVENT_ON_MOTD_CHANGE,     3,  "on_motd_change")     \
        X(GUILD_EVENT_ON_INFO_CHANGE,     4,  "on_info_change")     \
        X(GUILD_EVENT_ON_CREATE,          5,  "on_create")          \
        X(GUILD_EVENT_ON_DISBAND,         6,  "on_disband")         \
        X(GUILD_EVENT_ON_MONEY_WITHDRAW,  7,  "on_money_withdraw")  \
        X(GUILD_EVENT_ON_MONEY_DEPOSIT,   8,  "on_money_deposit")   \
        X(GUILD_EVENT_ON_ITEM_MOVE,       9,  "on_item_move")       \
        X(GUILD_EVENT_ON_EVENT,           10, "on_event")           \
        X(GUILD_EVENT_ON_BANK_EVENT,      11, "on_bank_event")

    enum GuildEvents
    {
    #define X(ID, VALUE, NAME) ID = VALUE,
        GUILD_EVENTS_LIST(X)
    #undef X
        GUILD_EVENT_COUNT
    };

    static constexpr EventEntry GuildEventsTable[] = {
    #define X(ID, VALUE, NAME) { Hooks::ID, NAME },
        GUILD_EVENTS_LIST(X)
    #undef X
    };

    // GROUP EVENTS
    #define GROUP_EVENTS_LIST(X) \
        X(GROUP_EVENT_ON_MEMBER_ADD,     1, "on_add_member")     \
        X(GROUP_EVENT_ON_MEMBER_INVITE,  2, "on_invite_member")  \
        X(GROUP_EVENT_ON_MEMBER_REMOVE,  3, "on_remove_member")  \
        X(GROUP_EVENT_ON_LEADER_CHANGE,  4, "on_leader_change")  \
        X(GROUP_EVENT_ON_DISBAND,        5, "on_disband")        \
        X(GROUP_EVENT_ON_CREATE,         6, "on_create")         \
        X(GROUP_EVENT_ON_MEMBER_ACCEPT,  7, "on_member_accept")

    enum GroupEvents
    {
    #define X(ID, VALUE, NAME) ID = VALUE,
        GROUP_EVENTS_LIST(X)
    #undef X
        GROUP_EVENT_COUNT
    };

    static constexpr EventEntry GroupEventsTable[] = {
    #define X(ID, VALUE, NAME) { Hooks::ID, NAME },
        GROUP_EVENTS_LIST(X)
    #undef X
    };

    // VEHICLE EVENTS
    #define VEHICLE_EVENTS_LIST(X) \
        X(VEHICLE_EVENT_ON_INSTALL,           1, "on_install")           \
        X(VEHICLE_EVENT_ON_UNINSTALL,         2, "on_uninstall")         \
        /* 3 unused */ \
        X(VEHICLE_EVENT_ON_INSTALL_ACCESSORY, 4, "on_install_accessory") \
        X(VEHICLE_EVENT_ON_ADD_PASSENGER,     5, "on_add_passenger")     \
        X(VEHICLE_EVENT_ON_REMOVE_PASSENGER,  6, "on_remove_passenger")

    enum VehicleEvents
    {
    #define X(ID, VALUE, NAME) ID = VALUE,
        VEHICLE_EVENTS_LIST(X)
    #undef X
        VEHICLE_EVENT_COUNT
    };

    static constexpr EventEntry VehicleEventsTable[] = {
    #define X(ID, VALUE, NAME) { Hooks::ID, NAME },
        VEHICLE_EVENTS_LIST(X)
    #undef X
    };

    // CREATURE EVENTS
    #define CREATURE_EVENTS_LIST(X) \
        X(CREATURE_EVENT_ON_ENTER_COMBAT,               1,  "on_enter_combat")               \
        X(CREATURE_EVENT_ON_LEAVE_COMBAT,               2,  "on_leave_combat")               \
        X(CREATURE_EVENT_ON_TARGET_DIED,                3,  "on_target_died")                \
        X(CREATURE_EVENT_ON_DIED,                       4,  "on_died")                       \
        X(CREATURE_EVENT_ON_SPAWN,                      5,  "on_spawn")                      \
        X(CREATURE_EVENT_ON_REACH_WP,                   6,  "on_reach_wp")                   \
        X(CREATURE_EVENT_ON_AIUPDATE,                   7,  "on_ai_update")                  \
        X(CREATURE_EVENT_ON_RECEIVE_EMOTE,              8,  "on_receive_emote")              \
        X(CREATURE_EVENT_ON_DAMAGE_TAKEN,               9,  "on_damage_taken")               \
        X(CREATURE_EVENT_ON_PRE_COMBAT,                 10, "on_pre_combat")                 \
        /* 11 unused */ \
        X(CREATURE_EVENT_ON_OWNER_ATTACKED,             12, "on_owner_attacked")             \
        X(CREATURE_EVENT_ON_OWNER_ATTACKED_AT,          13, "on_owner_attacked_at")          \
        X(CREATURE_EVENT_ON_HIT_BY_SPELL,               14, "on_hit_by_spell")               \
        X(CREATURE_EVENT_ON_SPELL_HIT_TARGET,           15, "on_spell_hit_target")           \
        /* 16,17,18 unused */ \
        X(CREATURE_EVENT_ON_JUST_SUMMONED_CREATURE,     19, "on_just_summoned_creature")     \
        X(CREATURE_EVENT_ON_SUMMONED_CREATURE_DESPAWN,  20, "on_summoned_creature_despawn")  \
        X(CREATURE_EVENT_ON_SUMMONED_CREATURE_DIED,     21, "on_summoned_creature_died")     \
        X(CREATURE_EVENT_ON_SUMMONED,                   22, "on_summoned")                   \
        X(CREATURE_EVENT_ON_RESET,                      23, "on_reset")                      \
        X(CREATURE_EVENT_ON_REACH_HOME,                 24, "on_reach_home")                 \
        /* 25 unused */ \
        X(CREATURE_EVENT_ON_CORPSE_REMOVED,             26, "on_corpse_removed")             \
        X(CREATURE_EVENT_ON_MOVE_IN_LOS,                27, "on_move_in_los")                \
        /* 28,29 unused */ \
        X(CREATURE_EVENT_ON_DUMMY_EFFECT,               30, "on_dummy_effect")               \
        X(CREATURE_EVENT_ON_QUEST_ACCEPT,               31, "on_quest_accept")               \
        /* 32,33 unused */ \
        X(CREATURE_EVENT_ON_QUEST_REWARD,               34, "on_quest_reward")               \
        X(CREATURE_EVENT_ON_DIALOG_STATUS,              35, "on_dialog_status")              \
        X(CREATURE_EVENT_ON_ADD,                        36, "on_add")                        \
        X(CREATURE_EVENT_ON_REMOVE,                     37, "on_remove")

    enum CreatureEvents
    {
    #define X(ID, VALUE, NAME) ID = VALUE,
        CREATURE_EVENTS_LIST(X)
    #undef X
        CREATURE_EVENT_COUNT
    };

    static constexpr EventEntry CreatureEventsTable[] = {
    #define X(ID, VALUE, NAME) { Hooks::ID, NAME },
        CREATURE_EVENTS_LIST(X)
    #undef X
    };

    // GAMEOBJECT EVENTS
    #define GAMEOBJECT_EVENTS_LIST(X) \
        X(GAMEOBJECT_EVENT_ON_AIUPDATE,          1,  "on_ai_update")         \
        X(GAMEOBJECT_EVENT_ON_SPAWN,             2,  "on_spawn")             \
        X(GAMEOBJECT_EVENT_ON_DUMMY_EFFECT,      3,  "on_dummy_effect")      \
        X(GAMEOBJECT_EVENT_ON_QUEST_ACCEPT,      4,  "on_quest_accept")      \
        X(GAMEOBJECT_EVENT_ON_QUEST_REWARD,      5,  "on_quest_reward")      \
        X(GAMEOBJECT_EVENT_ON_DIALOG_STATUS,     6,  "on_dialog_status")     \
        X(GAMEOBJECT_EVENT_ON_DESTROYED,         7,  "on_destroyed")         \
        X(GAMEOBJECT_EVENT_ON_DAMAGED,           8,  "on_damaged")           \
        X(GAMEOBJECT_EVENT_ON_LOOT_STATE_CHANGE, 9,  "on_loot_state_change") \
        X(GAMEOBJECT_EVENT_ON_GO_STATE_CHANGED,  10, "on_go_state_changed")  \
        /* 11 unused */ \
        X(GAMEOBJECT_EVENT_ON_ADD,               12, "on_add")               \
        X(GAMEOBJECT_EVENT_ON_REMOVE,            13, "on_remove")            \
        X(GAMEOBJECT_EVENT_ON_USE,               14, "on_use")

    enum GameObjectEvents
    {
    #define X(ID, VALUE, NAME) ID = VALUE,
        GAMEOBJECT_EVENTS_LIST(X)
    #undef X
        GAMEOBJECT_EVENT_COUNT
    };

    static constexpr EventEntry GameObjectEventsTable[] = {
    #define X(ID, VALUE, NAME) { Hooks::ID, NAME },
        GAMEOBJECT_EVENTS_LIST(X)
    #undef X
    };

    // SPELL EVENTS
    #define SPELL_EVENTS_LIST(X) \
        X(SPELL_EVENT_ON_CAST, 1, "on_cast") \
        X(SPELL_EVENT_ON_AURA_APPLICATION, 2, "on_aura_application") \
        X(SPELL_EVENT_ON_DISPEL, 3, "on_dispel") \
        X(SPELL_EVENT_ON_PERIODIC_TICK, 4, "on_periodic_tick") \
        X(SPELL_EVENT_ON_PERIODIC_UPDATE, 5, "on_periodic_update") \
        X(SPELL_EVENT_ON_AURA_CALC_AMOUNT, 6, "on_aura_calc_amount") \
        X(SPELL_EVENT_ON_CALC_PERIODIC, 7, "on_calc_periodic") \
        X(SPELL_EVENT_ON_CHECK_PROC, 8, "on_check_proc") \
        X(SPELL_EVENT_ON_PROC, 9, "on_proc") \
        X(SPELL_EVENT_ON_CHECK_CAST, 10, "on_check_cast") \
        X(SPELL_EVENT_ON_BEFORE_CAST, 11, "on_before_cast") \
        X(SPELL_EVENT_ON_AFTER_CAST, 12, "on_after_cast") \
        X(SPELL_EVENT_ON_OBJECT_AREA_TARGET, 13, "on_object_area_target") \
        X(SPELL_EVENT_ON_OBJECT_TARGET, 14, "on_object_target") \
        X(SPELL_EVENT_ON_DEST_TARGET, 15, "on_dest_target") \
        X(SPELL_EVENT_ON_EFFECT_LAUNCH, 16, "on_effect_launch") \
        X(SPELL_EVENT_ON_EFFECT_LAUNCH_TARGET, 17, "on_effect_launch_target") \
        X(SPELL_EVENT_ON_EFFECT_CALC_ABSORB, 18, "on_effect_calc_absorb") \
        X(SPELL_EVENT_ON_EFFECT_HIT, 19, "on_effect_hit") \
        X(SPELL_EVENT_ON_BEFORE_HIT, 20, "on_before_hit") \
        X(SPELL_EVENT_ON_EFFECT_HIT_TARGET, 21, "on_effect_hit_target") \
        X(SPELL_EVENT_ON_HIT, 22, "on_hit") \
        X(SPELL_EVENT_ON_AFTER_HIT, 23, "on_after_hit")

    enum SpellEvents
    {
    #define X(ID, VALUE, NAME) ID = VALUE,
        SPELL_EVENTS_LIST(X)
    #undef X
        SPELL_EVENT_COUNT
    };

    static constexpr EventEntry SpellEventsTable[] = {
    #define X(ID, VALUE, NAME) { Hooks::ID, NAME },
        SPELL_EVENTS_LIST(X)
    #undef X
    };

    // ITEM EVENTS
    #define ITEM_EVENTS_LIST(X) \
        X(ITEM_EVENT_ON_DUMMY_EFFECT, 1, "on_dummy_effect") \
        X(ITEM_EVENT_ON_USE,          2, "on_use")          \
        X(ITEM_EVENT_ON_QUEST_ACCEPT, 3, "on_quest_accept") \
        X(ITEM_EVENT_ON_EXPIRE,       4, "on_expire")       \
        X(ITEM_EVENT_ON_REMOVE,       5, "on_remove")       \
        /* Custom */ \
        X(ITEM_EVENT_ON_ADD,          6, "on_add")          \
        X(ITEM_EVENT_ON_EQUIP,        7, "on_equip")        \
        X(ITEM_EVENT_ON_UNEQUIP,      8, "on_unequip")

    enum ItemEvents
    {
    #define X(ID, VALUE, NAME) ID = VALUE,
        ITEM_EVENTS_LIST(X)
    #undef X
        ITEM_EVENT_COUNT
    };

    static constexpr EventEntry ItemEventsTable[] = {
    #define X(ID, VALUE, NAME) { Hooks::ID, NAME },
        ITEM_EVENTS_LIST(X)
    #undef X
    };

    // GOSSIP EVENTS
    #define GOSSIP_EVENTS_LIST(X) \
        X(GOSSIP_EVENT_ON_HELLO,  1, "on_hello") \
        X(GOSSIP_EVENT_ON_SELECT, 2, "on_select")

    enum GossipEvents
    {
    #define X(ID, VALUE, NAME) ID = VALUE,
        GOSSIP_EVENTS_LIST(X)
    #undef X
        GOSSIP_EVENT_COUNT
    };

    static constexpr EventEntry GossipEventsTable[] = {
    #define X(ID, VALUE, NAME) { Hooks::ID, NAME },
        GOSSIP_EVENTS_LIST(X)
    #undef X
    };

    // BG EVENTS
    #define BG_EVENTS_LIST(X) \
        X(BG_EVENT_ON_START,      1, "on_start")      \
        X(BG_EVENT_ON_END,        2, "on_end")        \
        X(BG_EVENT_ON_CREATE,     3, "on_create")     \
        X(BG_EVENT_ON_PRE_DESTROY,4, "on_pre_destroy")

    enum BGEvents
    {
    #define X(ID, VALUE, NAME) ID = VALUE,
        BG_EVENTS_LIST(X)
    #undef X
        BG_EVENT_COUNT
    };

    static constexpr EventEntry BGEventsTable[] = {
    #define X(ID, VALUE, NAME) { Hooks::ID, NAME },
        BG_EVENTS_LIST(X)
    #undef X
    };

    // INSTANCE EVENTS
    #define INSTANCE_EVENTS_LIST(X) \
        X(INSTANCE_EVENT_ON_INITIALIZE,                  1, "on_initialize")                 \
        X(INSTANCE_EVENT_ON_LOAD,                        2, "on_load")                       \
        X(INSTANCE_EVENT_ON_UPDATE,                      3, "on_update")                     \
        X(INSTANCE_EVENT_ON_PLAYER_ENTER,                4, "on_player_enter")               \
        X(INSTANCE_EVENT_ON_CREATURE_CREATE,             5, "on_creature_create")            \
        X(INSTANCE_EVENT_ON_GAMEOBJECT_CREATE,           6, "on_gameobject_create")          \
        X(INSTANCE_EVENT_ON_CHECK_ENCOUNTER_IN_PROGRESS, 7, "on_check_encounter_in_progress")

    enum InstanceEvents
    {
    #define X(ID, VALUE, NAME) ID = VALUE,
        INSTANCE_EVENTS_LIST(X)
    #undef X
        INSTANCE_EVENT_COUNT
    };

    static constexpr EventEntry InstanceEventsTable[] = {
    #define X(ID, VALUE, NAME) { Hooks::ID, NAME },
        INSTANCE_EVENTS_LIST(X)
    #undef X
    };

    // Per-category global event table
    static constexpr HookStorage HookTypeTable[] =
    {
        { "packet",   PacketEventsTable,   CountOf(PacketEventsTable)   },
        { "server",   ServerEventsTable,   CountOf(ServerEventsTable)   },
        { "player",   PlayerEventsTable,   CountOf(PlayerEventsTable)   },
        { "guild",    GuildEventsTable,    CountOf(GuildEventsTable)    },
        { "group",    GroupEventsTable,    CountOf(GroupEventsTable)    },
        { "vehicle",  VehicleEventsTable,  CountOf(VehicleEventsTable)  },
        { "creature", CreatureEventsTable, CountOf(CreatureEventsTable) },
        { "gameobject", GameObjectEventsTable, CountOf(GameObjectEventsTable) },
        { "spell",    SpellEventsTable,    CountOf(SpellEventsTable)    },
        { "item",     ItemEventsTable,     CountOf(ItemEventsTable)     },
        { "gossip",   GossipEventsTable,   CountOf(GossipEventsTable)   },
        { "bg",       BGEventsTable,       CountOf(BGEventsTable)       },
        { "map",      InstanceEventsTable, CountOf(InstanceEventsTable) },
        { "instance", InstanceEventsTable, CountOf(InstanceEventsTable) },
    };

    static constexpr std::pair<const HookStorage*, size_t> getHooks()
    {
        return { HookTypeTable, CountOf(HookTypeTable) };
    }
};

#endif // _HOOKS_H
