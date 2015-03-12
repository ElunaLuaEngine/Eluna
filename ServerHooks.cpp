/*
 * Copyright (C) 2010 - 2015 Eluna Lua Engine <http://emudevs.com/>
 * This program is free software licensed under GPL version 3
 * Please see the included DOCS/LICENSE.md for more information
 */

#ifndef _SERVER_HOOKS_H
#define _SERVER_HOOKS_H

#include "Hooks.h"
#include "HookHelpers.h"
#include "LuaEngine.h"
#include "ElunaBinding.h"
#include "ElunaEventMgr.h"
#include "ElunaIncludes.h"
#include "ElunaTemplate.h"

using namespace Hooks;

void Eluna::OnTimedEvent(int funcRef, uint32 delay, uint32 calls, WorldObject* obj)
{
    LOCK_ELUNA;
    ASSERT(!event_level);

    // Get function
    lua_rawgeti(L, LUA_REGISTRYINDEX, funcRef);

    // Push parameters
    Push(L, funcRef);
    Push(L, delay);
    Push(L, calls);
    Push(L, obj);

    // Call function
    ExecuteCall(4, 0);

    ASSERT(!event_level);
    InvalidateObjects();
}

void Eluna::OnLuaStateClose()
{
    if (!ServerEventBindings->HasEvents(ELUNA_EVENT_ON_LUA_STATE_CLOSE))
        return;

    LOCK_ELUNA;
    CallAllFunctions(ServerEventBindings, ELUNA_EVENT_ON_LUA_STATE_CLOSE);
}

void Eluna::OnLuaStateOpen()
{
    if (!ServerEventBindings->HasEvents(ELUNA_EVENT_ON_LUA_STATE_OPEN))
        return;

    LOCK_ELUNA;
    CallAllFunctions(ServerEventBindings, ELUNA_EVENT_ON_LUA_STATE_OPEN);
}

// areatrigger
bool Eluna::OnAreaTrigger(Player* pPlayer, AreaTriggerEntry const* pTrigger)
{
    if (!ServerEventBindings->HasEvents(TRIGGER_EVENT_ON_TRIGGER))
        return false;

    LOCK_ELUNA;
    Push(pPlayer);
    Push(pTrigger->id);
    return CallAllFunctionsBool(ServerEventBindings, TRIGGER_EVENT_ON_TRIGGER);
}

// weather
void Eluna::OnChange(Weather* weather, uint32 zone, WeatherState state, float grade)
{
    if (!ServerEventBindings->HasEvents(WEATHER_EVENT_ON_CHANGE))
        return;

    LOCK_ELUNA;
    Push(zone);
    Push(state);
    Push(grade);
    CallAllFunctions(ServerEventBindings, WEATHER_EVENT_ON_CHANGE);
}

// Auction House
void Eluna::OnAdd(AuctionHouseObject* /*ah*/, AuctionEntry* entry)
{
    if (!ServerEventBindings->HasEvents(AUCTION_EVENT_ON_ADD))
        return;

    Player* owner = eObjectAccessor->FindPlayer(MAKE_NEW_GUID(entry->owner, 0, HIGHGUID_PLAYER));
#ifdef TRINITY
    Item* item = eAuctionMgr->GetAItem(entry->itemGUIDLow);
    uint32 expiretime = entry->expire_time;
#else
    Item* item = eAuctionMgr->GetAItem(entry->itemGuidLow);
    uint32 expiretime = entry->expireTime;
#endif


    if (!owner || !item)
        return;

    LOCK_ELUNA;
    Push(entry->Id);
    Push(owner);
    Push(item);
    Push(expiretime);
    Push(entry->buyout);
    Push(entry->startbid);
    Push(entry->bid);
    Push(entry->bidder);
    CallAllFunctions(ServerEventBindings, AUCTION_EVENT_ON_ADD);
}

void Eluna::OnRemove(AuctionHouseObject* /*ah*/, AuctionEntry* entry)
{
    if (!ServerEventBindings->HasEvents(AUCTION_EVENT_ON_REMOVE))
        return;

    Player* owner = eObjectAccessor->FindPlayer(MAKE_NEW_GUID(entry->owner, 0, HIGHGUID_PLAYER));
#ifdef TRINITY
    Item* item = eAuctionMgr->GetAItem(entry->itemGUIDLow);
    uint32 expiretime = entry->expire_time;
#else
    Item* item = eAuctionMgr->GetAItem(entry->itemGuidLow);
    uint32 expiretime = entry->expireTime;
#endif


    if (!owner || !item)
        return;

    LOCK_ELUNA;
    Push(entry->Id);
    Push(owner);
    Push(item);
    Push(expiretime);
    Push(entry->buyout);
    Push(entry->startbid);
    Push(entry->bid);
    Push(entry->bidder);
    CallAllFunctions(ServerEventBindings, AUCTION_EVENT_ON_REMOVE);
}

void Eluna::OnSuccessful(AuctionHouseObject* /*ah*/, AuctionEntry* entry)
{
    if (!ServerEventBindings->HasEvents(AUCTION_EVENT_ON_SUCCESSFUL))
        return;

    Player* owner = eObjectAccessor->FindPlayer(MAKE_NEW_GUID(entry->owner, 0, HIGHGUID_PLAYER));
#ifdef TRINITY
    Item* item = eAuctionMgr->GetAItem(entry->itemGUIDLow);
    uint32 expiretime = entry->expire_time;
#else
    Item* item = eAuctionMgr->GetAItem(entry->itemGuidLow);
    uint32 expiretime = entry->expireTime;
#endif


    if (!owner || !item)
        return;

    LOCK_ELUNA;
    Push(entry->Id);
    Push(owner);
    Push(item);
    Push(expiretime);
    Push(entry->buyout);
    Push(entry->startbid);
    Push(entry->bid);
    Push(entry->bidder);
    CallAllFunctions(ServerEventBindings, AUCTION_EVENT_ON_SUCCESSFUL);
}

void Eluna::OnExpire(AuctionHouseObject* /*ah*/, AuctionEntry* entry)
{
    if (!ServerEventBindings->HasEvents(AUCTION_EVENT_ON_EXPIRE))
        return;

    Player* owner = eObjectAccessor->FindPlayer(MAKE_NEW_GUID(entry->owner, 0, HIGHGUID_PLAYER));
#ifdef TRINITY
    Item* item = eAuctionMgr->GetAItem(entry->itemGUIDLow);
    uint32 expiretime = entry->expire_time;
#else
    Item* item = eAuctionMgr->GetAItem(entry->itemGuidLow);
    uint32 expiretime = entry->expireTime;
#endif


    if (!owner || !item)
        return;

    LOCK_ELUNA;
    Push(entry->Id);
    Push(owner);
    Push(item);
    Push(expiretime);
    Push(entry->buyout);
    Push(entry->startbid);
    Push(entry->bid);
    Push(entry->bidder);
    CallAllFunctions(ServerEventBindings, AUCTION_EVENT_ON_EXPIRE);
}

// Packet
bool Eluna::OnPacketSend(WorldSession* session, WorldPacket& packet)
{
    bool result = true;
    Player* player = NULL;
    if (session)
        player = session->GetPlayer();
    OnPacketSendAny(player, packet, result);
    OnPacketSendOne(player, packet, result);
    return result;
}
void Eluna::OnPacketSendAny(Player* player, WorldPacket& packet, bool& result)
{
    if (!ServerEventBindings->HasEvents(SERVER_EVENT_ON_PACKET_SEND))
        return;

    LOCK_ELUNA;
    Push(new WorldPacket(packet));
    Push(player);
    int n = SetupStack(ServerEventBindings, SERVER_EVENT_ON_PACKET_SEND, 2);

    while (n > 0)
    {
        int r = CallOneFunction(n--, 2, 2);

        if (lua_isboolean(L, r + 0) && !lua_toboolean(L, r + 0))
            result = false;

        if (lua_isuserdata(L, r + 1))
            if (WorldPacket* data = CHECKOBJ<WorldPacket>(L, r + 1, false))
                packet = *data;

        lua_pop(L, 2);
    }

    CleanUpStack(2);
}

void Eluna::OnPacketSendOne(Player* player, WorldPacket& packet, bool& result)
{
    if (!PacketEventBindings->HasEvents(PACKET_EVENT_ON_PACKET_SEND, packet.GetOpcode()))
        return;

    LOCK_ELUNA;
    Push(new WorldPacket(packet));
    Push(player);
    int n = SetupStack(PacketEventBindings, PACKET_EVENT_ON_PACKET_SEND, OpcodesList(packet.GetOpcode()), 2);

    while (n > 0)
    {
        int r = CallOneFunction(n--, 2, 2);

        if (lua_isboolean(L, r + 0) && !lua_toboolean(L, r + 0))
            result = false;

        if (lua_isuserdata(L, r + 1))
            if (WorldPacket* data = CHECKOBJ<WorldPacket>(L, r + 1, false))
                packet = *data;

        lua_pop(L, 2);
    }

    CleanUpStack(2);
}

bool Eluna::OnPacketReceive(WorldSession* session, WorldPacket& packet)
{
    bool result = true;
    Player* player = NULL;
    if (session)
        player = session->GetPlayer();
    OnPacketReceiveAny(player, packet, result);
    OnPacketReceiveOne(player, packet, result);
    return result;
}

void Eluna::OnPacketReceiveAny(Player* player, WorldPacket& packet, bool& result)
{
    if (!ServerEventBindings->HasEvents(SERVER_EVENT_ON_PACKET_RECEIVE))
        return;

    LOCK_ELUNA;
    Push(new WorldPacket(packet));
    Push(player);
    int n = SetupStack(ServerEventBindings, SERVER_EVENT_ON_PACKET_RECEIVE, 2);

    while (n > 0)
    {
        int r = CallOneFunction(n--, 2, 2);

        if (lua_isboolean(L, r + 0) && !lua_toboolean(L, r + 0))
            result = false;

        if (lua_isuserdata(L, r + 1))
            if (WorldPacket* data = CHECKOBJ<WorldPacket>(L, r + 1, false))
                packet = *data;

        lua_pop(L, 2);
    }

    CleanUpStack(2);
}

void Eluna::OnPacketReceiveOne(Player* player, WorldPacket& packet, bool& result)
{
    if (!PacketEventBindings->HasEvents(PACKET_EVENT_ON_PACKET_RECEIVE, packet.GetOpcode()))
        return;

    LOCK_ELUNA;
    Push(new WorldPacket(packet));
    Push(player);
    int n = SetupStack(PacketEventBindings, PACKET_EVENT_ON_PACKET_RECEIVE, OpcodesList(), 2);

    while (n > 0)
    {
        int r = CallOneFunction(n--, 2, 2);

        if (lua_isboolean(L, r + 0) && !lua_toboolean(L, r + 0))
            result = false;

        if (lua_isuserdata(L, r + 1))
            if (WorldPacket* data = CHECKOBJ<WorldPacket>(L, r + 1, false))
                packet = *data;

        lua_pop(L, 2);
    }

    CleanUpStack(2);
}

void Eluna::OnOpenStateChange(bool open)
{
    if (!ServerEventBindings->HasEvents(WORLD_EVENT_ON_OPEN_STATE_CHANGE))
        return;

    LOCK_ELUNA;
    Push(open);
    CallAllFunctions(ServerEventBindings, WORLD_EVENT_ON_OPEN_STATE_CHANGE);
}

void Eluna::OnConfigLoad(bool reload)
{
    if (!ServerEventBindings->HasEvents(WORLD_EVENT_ON_CONFIG_LOAD))
        return;

    LOCK_ELUNA;
    Push(reload);
    CallAllFunctions(ServerEventBindings, WORLD_EVENT_ON_CONFIG_LOAD);
}

void Eluna::OnShutdownInitiate(ShutdownExitCode code, ShutdownMask mask)
{
    if (!ServerEventBindings->HasEvents(WORLD_EVENT_ON_SHUTDOWN_INIT))
        return;

    LOCK_ELUNA;
    Push(code);
    Push(mask);
    CallAllFunctions(ServerEventBindings, WORLD_EVENT_ON_SHUTDOWN_INIT);
}

void Eluna::OnShutdownCancel()
{
    if (!ServerEventBindings->HasEvents(WORLD_EVENT_ON_SHUTDOWN_CANCEL))
        return;

    LOCK_ELUNA;
    CallAllFunctions(ServerEventBindings, WORLD_EVENT_ON_SHUTDOWN_CANCEL);
}

void Eluna::OnWorldUpdate(uint32 diff)
{
    {
        LOCK_ELUNA;
        if (ShouldReload())
            _ReloadEluna();
    }

    eventMgr->globalProcessor->Update(diff);

    if (!ServerEventBindings->HasEvents(WORLD_EVENT_ON_UPDATE))
        return;

    LOCK_ELUNA;
    Push(diff);
    CallAllFunctions(ServerEventBindings, WORLD_EVENT_ON_UPDATE);
}

void Eluna::OnStartup()
{
    if (!ServerEventBindings->HasEvents(WORLD_EVENT_ON_STARTUP))
        return;

    LOCK_ELUNA;
    CallAllFunctions(ServerEventBindings, WORLD_EVENT_ON_STARTUP);
}

void Eluna::OnShutdown()
{
    if (!ServerEventBindings->HasEvents(WORLD_EVENT_ON_SHUTDOWN))
        return;

    LOCK_ELUNA;
    CallAllFunctions(ServerEventBindings, WORLD_EVENT_ON_SHUTDOWN);
}

/* Map */
void Eluna::OnCreate(Map* map)
{
    if (!ServerEventBindings->HasEvents(MAP_EVENT_ON_CREATE))
        return;

    LOCK_ELUNA;
    Push(map);
    CallAllFunctions(ServerEventBindings, MAP_EVENT_ON_CREATE);
}

void Eluna::OnDestroy(Map* map)
{
    if (!ServerEventBindings->HasEvents(MAP_EVENT_ON_DESTROY))
        return;

    LOCK_ELUNA;
    Push(map);
    CallAllFunctions(ServerEventBindings, MAP_EVENT_ON_DESTROY);
}

void Eluna::OnPlayerEnter(Map* map, Player* player)
{
    if (!ServerEventBindings->HasEvents(MAP_EVENT_ON_PLAYER_ENTER))
        return;

    LOCK_ELUNA;
    Push(map);
    Push(player);
    CallAllFunctions(ServerEventBindings, MAP_EVENT_ON_PLAYER_ENTER);
}

void Eluna::OnPlayerLeave(Map* map, Player* player)
{
    if (!ServerEventBindings->HasEvents(MAP_EVENT_ON_PLAYER_LEAVE))
        return;

    LOCK_ELUNA;
    Push(map);
    Push(player);
    CallAllFunctions(ServerEventBindings, MAP_EVENT_ON_PLAYER_LEAVE);
}

void Eluna::OnUpdate(Map* map, uint32 diff)
{
    if (!ServerEventBindings->HasEvents(MAP_EVENT_ON_UPDATE))
        return;

    LOCK_ELUNA;
    // enable this for multithread
    // eventMgr->globalProcessor->Update(diff);
    Push(map);
    Push(diff);
    CallAllFunctions(ServerEventBindings, MAP_EVENT_ON_UPDATE);
}

void Eluna::OnRemove(GameObject* gameobject)
{
    if (!ServerEventBindings->HasEvents(WORLD_EVENT_ON_DELETE_GAMEOBJECT))
        return;

    LOCK_ELUNA;
    Push(gameobject);
    CallAllFunctions(ServerEventBindings, WORLD_EVENT_ON_DELETE_GAMEOBJECT);
}

void Eluna::OnRemove(Creature* creature)
{
    if (!ServerEventBindings->HasEvents(WORLD_EVENT_ON_DELETE_CREATURE))
        return;

    LOCK_ELUNA;
    Push(creature);
    CallAllFunctions(ServerEventBindings, WORLD_EVENT_ON_DELETE_CREATURE);
}

#endif // _SERVER_HOOKS_H
