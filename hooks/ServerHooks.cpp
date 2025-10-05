/*
 * Copyright (C) 2010 - 2024 Eluna Lua Engine <https://elunaluaengine.github.io/>
 * This program is free software licensed under GPL version 3
 * Please see the included DOCS/LICENSE.md for more information
 */

#include "Hooks.h"
#include "HookHelpers.h"
#include "LuaEngine.h"
#include "BindingMap.h"
#include "ElunaEventMgr.h"
#include "ElunaIncludes.h"
#include "ElunaTemplate.h"

using namespace Hooks;

#define START_HOOK(EVENT) \
    auto binding = GetBinding<EventKey<ServerEvents>>(REGTYPE_SERVER);\
    auto key = EventKey<ServerEvents>(EVENT);\
    if (!binding->HasBindingsFor(key))\
        return;

#define START_HOOK_WITH_RETVAL(EVENT, RETVAL) \
    auto binding = GetBinding<EventKey<ServerEvents>>(REGTYPE_SERVER);\
    auto key = EventKey<ServerEvents>(EVENT);\
    if (!binding->HasBindingsFor(key))\
        return RETVAL;

bool Eluna::OnAddonMessage(Player* sender, uint32 type, std::string& msg, Player* receiver, Guild* guild, Group* group, Channel* channel)
{
    START_HOOK_WITH_RETVAL(ADDON_EVENT_ON_MESSAGE, true);
    HookPush(sender);
    HookPush(type);

    auto delimeter_position = msg.find('\t');
    if (delimeter_position == std::string::npos)
    {
        HookPush(msg); // prefix
        HookPush(); // msg
    }
    else
    {
        std::string prefix = msg.substr(0, delimeter_position);
        std::string content = msg.substr(delimeter_position + 1, std::string::npos);
        HookPush(prefix);
        HookPush(content);
    }

    if (receiver)
        HookPush(receiver);
    else if (guild)
        HookPush(guild);
    else if (group)
        HookPush(group);
    else if (channel)
        HookPush(channel->GetChannelId());
    else
        HookPush();

    return CallAllFunctionsBool(binding, key, true);
}

void Eluna::OnTimedEvent(int funcRef, uint32 delay, uint32 calls, WorldObject* obj)
{
    ASSERT(!event_level);

    // Get function
    lua_rawgeti(L, LUA_REGISTRYINDEX, funcRef);

    // Push parameters
    Push(funcRef);
    Push(delay);
    Push(calls);
    Push(obj);

    // Call function
    ExecuteCall(4, 0);

    ASSERT(!event_level);
#if !defined TRACKABLE_PTR_NAMESPACE
    InvalidateObjects();
#endif
}

void Eluna::OnGameEventStart(uint32 eventid)
{
    START_HOOK(GAME_EVENT_START);
    HookPush(eventid);
    CallAllFunctions(binding, key);
}

void Eluna::OnGameEventStop(uint32 eventid)
{
    START_HOOK(GAME_EVENT_STOP);
    HookPush(eventid);
    CallAllFunctions(binding, key);
}

void Eluna::OnLuaStateClose()
{
    START_HOOK(ELUNA_EVENT_ON_LUA_STATE_CLOSE);
    CallAllFunctions(binding, key);
}

void Eluna::OnLuaStateOpen()
{
    START_HOOK(ELUNA_EVENT_ON_LUA_STATE_OPEN);
    CallAllFunctions(binding, key);
}

// AreaTrigger
bool Eluna::OnAreaTrigger(Player* pPlayer, AreaTriggerEntry const* pTrigger)
{
    START_HOOK_WITH_RETVAL(TRIGGER_EVENT_ON_TRIGGER, false);
    HookPush(pPlayer);
#if defined ELUNA_TRINITY
    HookPush(pTrigger->ID);
#else
    HookPush(pTrigger->id);
#endif

    return CallAllFunctionsBool(binding, key);
}

// Weather
void Eluna::OnChange(Weather* /*weather*/, uint32 zone, WeatherState state, float grade)
{
    START_HOOK(WEATHER_EVENT_ON_CHANGE);
    HookPush(zone);
    HookPush(state);
    HookPush(grade);
    CallAllFunctions(binding, key);
}

// Auction House
void Eluna::OnAdd(AuctionHouseObject* /*ah*/, AuctionEntry* entry)
{
#if defined ELUNA_TRINITY
    Player* owner = eObjectAccessor()FindPlayerByLowGUID(entry->owner);
    Item* item = eAuctionMgr->GetAItem(entry->itemGUIDLow);
    uint32 expiretime = entry->expire_time;
#else
    Player* owner = eObjectAccessor()FindPlayer(MAKE_NEW_GUID(entry->owner, 0, HIGHGUID_PLAYER));
    Item* item = eAuctionMgr->GetAItem(entry->itemGuidLow);
    uint32 expiretime = entry->expireTime;
#endif

    if (!owner || !item)
        return;

    START_HOOK(AUCTION_EVENT_ON_ADD);
    HookPush(entry->Id);
    HookPush(owner);
    HookPush(item);
    HookPush(expiretime);
    HookPush(entry->buyout);
    HookPush(entry->startbid);
    HookPush(entry->bid);
    HookPush(entry->bidder);
    CallAllFunctions(binding, key);
}

void Eluna::OnRemove(AuctionHouseObject* /*ah*/, AuctionEntry* entry)
{
#if defined ELUNA_TRINITY
    Player* owner = eObjectAccessor()FindPlayerByLowGUID(entry->owner);
    Item* item = eAuctionMgr->GetAItem(entry->itemGUIDLow);
    uint32 expiretime = entry->expire_time;
#else
    Player* owner = eObjectAccessor()FindPlayer(MAKE_NEW_GUID(entry->owner, 0, HIGHGUID_PLAYER));
    Item* item = eAuctionMgr->GetAItem(entry->itemGuidLow);
    uint32 expiretime = entry->expireTime;
#endif


    if (!owner || !item)
        return;

    START_HOOK(AUCTION_EVENT_ON_REMOVE);
    HookPush(entry->Id);
    HookPush(owner);
    HookPush(item);
    HookPush(expiretime);
    HookPush(entry->buyout);
    HookPush(entry->startbid);
    HookPush(entry->bid);
    HookPush(entry->bidder);
    CallAllFunctions(binding, key);
}

void Eluna::OnSuccessful(AuctionHouseObject* /*ah*/, AuctionEntry* entry)
{
#if defined ELUNA_TRINITY
    Player* owner = eObjectAccessor()FindPlayerByLowGUID(entry->owner);
    Item* item = eAuctionMgr->GetAItem(entry->itemGUIDLow);
    uint32 expiretime = entry->expire_time;
#else
    Player* owner = eObjectAccessor()FindPlayer(MAKE_NEW_GUID(entry->owner, 0, HIGHGUID_PLAYER));
    Item* item = eAuctionMgr->GetAItem(entry->itemGuidLow);
    uint32 expiretime = entry->expireTime;
#endif

    if (!owner || !item)
        return;

    START_HOOK(AUCTION_EVENT_ON_SUCCESSFUL);
    HookPush(entry->Id);
    HookPush(owner);
    HookPush(item);
    HookPush(expiretime);
    HookPush(entry->buyout);
    HookPush(entry->startbid);
    HookPush(entry->bid);
    HookPush(entry->bidder);
    CallAllFunctions(binding, key);
}

void Eluna::OnExpire(AuctionHouseObject* /*ah*/, AuctionEntry* entry)
{
#if defined ELUNA_TRINITY
    Player* owner = eObjectAccessor()FindPlayerByLowGUID(entry->owner);
    Item* item = eAuctionMgr->GetAItem(entry->itemGUIDLow);
    uint32 expiretime = entry->expire_time;
#else
    Player* owner = eObjectAccessor()FindPlayer(MAKE_NEW_GUID(entry->owner, 0, HIGHGUID_PLAYER));
    Item* item = eAuctionMgr->GetAItem(entry->itemGuidLow);
    uint32 expiretime = entry->expireTime;
#endif

    if (!owner || !item)
        return;

    START_HOOK(AUCTION_EVENT_ON_EXPIRE);
    HookPush(entry->Id);
    HookPush(owner);
    HookPush(item);
    HookPush(expiretime);
    HookPush(entry->buyout);
    HookPush(entry->startbid);
    HookPush(entry->bid);
    HookPush(entry->bidder);
    CallAllFunctions(binding, key);
}

void Eluna::OnOpenStateChange(bool open)
{
    START_HOOK(WORLD_EVENT_ON_OPEN_STATE_CHANGE);
    HookPush(open);
    CallAllFunctions(binding, key);
}

void Eluna::OnConfigLoad(bool reload)
{
    START_HOOK(WORLD_EVENT_ON_CONFIG_LOAD);
    HookPush(reload);
    CallAllFunctions(binding, key);
}

void Eluna::OnShutdownInitiate(ShutdownExitCode code, ShutdownMask mask)
{
    START_HOOK(WORLD_EVENT_ON_SHUTDOWN_INIT);
    HookPush(code);
    HookPush(mask);
    CallAllFunctions(binding, key);
}

void Eluna::OnShutdownCancel()
{
    START_HOOK(WORLD_EVENT_ON_SHUTDOWN_CANCEL);
    CallAllFunctions(binding, key);
}

void Eluna::OnWorldUpdate(uint32 diff)
{
    START_HOOK(WORLD_EVENT_ON_UPDATE);
    HookPush(diff);
    CallAllFunctions(binding, key);
}

void Eluna::OnStartup()
{
    START_HOOK(WORLD_EVENT_ON_STARTUP);
    CallAllFunctions(binding, key);
}

void Eluna::OnShutdown()
{
    START_HOOK(WORLD_EVENT_ON_SHUTDOWN);
    CallAllFunctions(binding, key);
}

/* Map */
void Eluna::OnCreate(Map* map)
{
    START_HOOK(MAP_EVENT_ON_CREATE);
    HookPush(map);
    CallAllFunctions(binding, key);
}

void Eluna::OnDestroy(Map* map)
{
    START_HOOK(MAP_EVENT_ON_DESTROY);
    HookPush(map);
    CallAllFunctions(binding, key);
}

void Eluna::OnPlayerEnter(Map* map, Player* player)
{
    START_HOOK(MAP_EVENT_ON_PLAYER_ENTER);
    HookPush(map);
    HookPush(player);
    CallAllFunctions(binding, key);
}

void Eluna::OnPlayerLeave(Map* map, Player* player)
{
    START_HOOK(MAP_EVENT_ON_PLAYER_LEAVE);
    HookPush(map);
    HookPush(player);
    CallAllFunctions(binding, key);
}

void Eluna::OnMapUpdate(Map* map, uint32 diff)
{
    START_HOOK(MAP_EVENT_ON_UPDATE);
    HookPush(map);
    HookPush(diff);
    CallAllFunctions(binding, key);
}

void Eluna::OnRemove(GameObject* gameobject)
{
    START_HOOK(WORLD_EVENT_ON_DELETE_GAMEOBJECT);
    HookPush(gameobject);
    CallAllFunctions(binding, key);
}

void Eluna::OnRemove(Creature* creature)
{
    START_HOOK(WORLD_EVENT_ON_DELETE_CREATURE);
    HookPush(creature);
    CallAllFunctions(binding, key);
}
