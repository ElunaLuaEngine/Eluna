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
    auto key = EventKey<ServerEvents>(EVENT);\
    if (!ServerEventBindings->HasBindingsFor(key))\
        return;

#define START_HOOK_WITH_RETVAL(EVENT, RETVAL) \
    auto key = EventKey<ServerEvents>(EVENT);\
    if (!ServerEventBindings->HasBindingsFor(key))\
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

    return CallAllFunctionsBool(ServerEventBindings, key, true);
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
    InvalidateObjects();
}

void Eluna::OnGameEventStart(uint32 eventid)
{
    START_HOOK(GAME_EVENT_START);
    HookPush(eventid);
    CallAllFunctions(ServerEventBindings, key);
}

void Eluna::OnGameEventStop(uint32 eventid)
{
    START_HOOK(GAME_EVENT_STOP);
    HookPush(eventid);
    CallAllFunctions(ServerEventBindings, key);
}

void Eluna::OnLuaStateClose()
{
    START_HOOK(ELUNA_EVENT_ON_LUA_STATE_CLOSE);
    CallAllFunctions(ServerEventBindings, key);
}

void Eluna::OnLuaStateOpen()
{
    START_HOOK(ELUNA_EVENT_ON_LUA_STATE_OPEN);
    CallAllFunctions(ServerEventBindings, key);
}

// AreaTrigger
bool Eluna::OnAreaTrigger(Player* pPlayer, AreaTriggerEntry const* pTrigger)
{
    START_HOOK_WITH_RETVAL(TRIGGER_EVENT_ON_TRIGGER, false);
    HookPush(pPlayer);
#ifdef TRINITY
    HookPush(pTrigger->ID);
#elif AZEROTHCORE
    HookPush(pTrigger->entry);
#else
    HookPush(pTrigger->id);

#endif
    return CallAllFunctionsBool(ServerEventBindings, key);
}

// Weather
void Eluna::OnChange(Weather* /*weather*/, uint32 zone, WeatherState state, float grade)
{
    START_HOOK(WEATHER_EVENT_ON_CHANGE);
    HookPush(zone);
    HookPush(state);
    HookPush(grade);
    CallAllFunctions(ServerEventBindings, key);
}

// Auction House
void Eluna::OnAdd(AuctionHouseObject* /*ah*/, AuctionEntry* entry)
{
#ifdef AZEROTHCORE
    Player* owner = eObjectAccessor()FindPlayer(entry->owner);
#else
    Player* owner = eObjectAccessor()FindPlayer(MAKE_NEW_GUID(entry->owner, 0, HIGHGUID_PLAYER));
#endif

#ifdef TRINITY
    Item* item = eAuctionMgr->GetAItem(entry->itemGUIDLow);
    uint32 expiretime = entry->expire_time;
#elif AZEROTHCORE
    Item* item = eAuctionMgr->GetAItem(entry->item_guid);
    uint32 expiretime = entry->expire_time;
#else
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
    CallAllFunctions(ServerEventBindings, key);
}

void Eluna::OnRemove(AuctionHouseObject* /*ah*/, AuctionEntry* entry)
{
#ifdef AZEROTHCORE
    Player* owner = eObjectAccessor()FindPlayer(entry->owner);
#else
    Player* owner = eObjectAccessor()FindPlayer(MAKE_NEW_GUID(entry->owner, 0, HIGHGUID_PLAYER));
#endif

#ifdef TRINITY
    Item* item = eAuctionMgr->GetAItem(entry->itemGUIDLow);
    uint32 expiretime = entry->expire_time;
#elif AZEROTHCORE
    Item* item = eAuctionMgr->GetAItem(entry->item_guid);
    uint32 expiretime = entry->expire_time;
#else
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
    CallAllFunctions(ServerEventBindings, key);
}

void Eluna::OnSuccessful(AuctionHouseObject* /*ah*/, AuctionEntry* entry)
{
#ifdef AZEROTHCORE
    Player* owner = eObjectAccessor()FindPlayer(entry->owner);
#else
    Player* owner = eObjectAccessor()FindPlayer(MAKE_NEW_GUID(entry->owner, 0, HIGHGUID_PLAYER));
#endif

#ifdef TRINITY
    Item* item = eAuctionMgr->GetAItem(entry->itemGUIDLow);
    uint32 expiretime = entry->expire_time;
#elif AZEROTHCORE
    Item* item = eAuctionMgr->GetAItem(entry->item_guid);
    uint32 expiretime = entry->expire_time;
#else
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
    CallAllFunctions(ServerEventBindings, key);
}

void Eluna::OnExpire(AuctionHouseObject* /*ah*/, AuctionEntry* entry)
{
#ifdef AZEROTHCORE
    Player* owner = eObjectAccessor()FindPlayer(entry->owner);
#else
    Player* owner = eObjectAccessor()FindPlayer(MAKE_NEW_GUID(entry->owner, 0, HIGHGUID_PLAYER));
#endif

#ifdef TRINITY
    Item* item = eAuctionMgr->GetAItem(entry->itemGUIDLow);
    uint32 expiretime = entry->expire_time;
#elif AZEROTHCORE
    Item* item = eAuctionMgr->GetAItem(entry->item_guid);
    uint32 expiretime = entry->expire_time;
#else
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
    CallAllFunctions(ServerEventBindings, key);
}

void Eluna::OnOpenStateChange(bool open)
{
    START_HOOK(WORLD_EVENT_ON_OPEN_STATE_CHANGE);
    HookPush(open);
    CallAllFunctions(ServerEventBindings, key);
}

#ifndef AZEROTHCORE
void Eluna::OnConfigLoad(bool reload)
#else
void Eluna::OnConfigLoad(bool reload, bool isBefore)
#endif
{
    START_HOOK(WORLD_EVENT_ON_CONFIG_LOAD);
    HookPush(reload);
#ifdef AZEROTHCORE
    HookPush(isBefore);
#endif
    CallAllFunctions(ServerEventBindings, key);
}

void Eluna::OnShutdownInitiate(ShutdownExitCode code, ShutdownMask mask)
{
    START_HOOK(WORLD_EVENT_ON_SHUTDOWN_INIT);
    HookPush(code);
    HookPush(mask);
    CallAllFunctions(ServerEventBindings, key);
}

void Eluna::OnShutdownCancel()
{
    START_HOOK(WORLD_EVENT_ON_SHUTDOWN_CANCEL);
    CallAllFunctions(ServerEventBindings, key);
}

void Eluna::OnWorldUpdate(uint32 diff)
{
    START_HOOK(WORLD_EVENT_ON_UPDATE);
    HookPush(diff);
    CallAllFunctions(ServerEventBindings, key);
}

void Eluna::OnStartup()
{
    START_HOOK(WORLD_EVENT_ON_STARTUP);
    CallAllFunctions(ServerEventBindings, key);
}

void Eluna::OnShutdown()
{
    START_HOOK(WORLD_EVENT_ON_SHUTDOWN);
    CallAllFunctions(ServerEventBindings, key);
}

/* Map */
void Eluna::OnCreate(Map* map)
{
    START_HOOK(MAP_EVENT_ON_CREATE);
    HookPush(map);
    CallAllFunctions(ServerEventBindings, key);
}

void Eluna::OnDestroy(Map* map)
{
    START_HOOK(MAP_EVENT_ON_DESTROY);
    HookPush(map);
    CallAllFunctions(ServerEventBindings, key);
}

void Eluna::OnPlayerEnter(Map* map, Player* player)
{
    START_HOOK(MAP_EVENT_ON_PLAYER_ENTER);
    HookPush(map);
    HookPush(player);
    CallAllFunctions(ServerEventBindings, key);
}

void Eluna::OnPlayerLeave(Map* map, Player* player)
{
    START_HOOK(MAP_EVENT_ON_PLAYER_LEAVE);
    HookPush(map);
    HookPush(player);
    CallAllFunctions(ServerEventBindings, key);
}

void Eluna::OnUpdate(Map* map, uint32 diff)
{
    START_HOOK(MAP_EVENT_ON_UPDATE);
    HookPush(map);
    HookPush(diff);
    CallAllFunctions(ServerEventBindings, key);
}

void Eluna::OnRemove(GameObject* gameobject)
{
    START_HOOK(WORLD_EVENT_ON_DELETE_GAMEOBJECT);
    HookPush(gameobject);
    CallAllFunctions(ServerEventBindings, key);
}

void Eluna::OnRemove(Creature* creature)
{
    START_HOOK(WORLD_EVENT_ON_DELETE_CREATURE);
    HookPush(creature);
    CallAllFunctions(ServerEventBindings, key);
}
