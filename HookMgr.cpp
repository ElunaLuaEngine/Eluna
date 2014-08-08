/*
* Copyright (C) 2010 - 2014 Eluna Lua Engine <http://emudevs.com/>
* This program is free software licensed under GPL version 3
* Please see the included DOCS/LICENSE.md for more information
*/

#include "HookMgr.h"
#include "LuaEngine.h"
#include "ElunaBinding.h"
#include "ElunaEventMgr.h"
#include "ElunaIncludes.h"
#include "ElunaTemplate.h"

extern "C"
{
#include "lua.h"
#include "lualib.h"
#include "lauxlib.h"
};

#ifndef TRINITY
class ReactorAI;
typedef ReactorAI ScriptedAI;
#else
struct ScriptedAI;
#endif

using namespace HookMgr;

/*
Call model for EventBind:

// Begin the call if should
EVENT_BEGIN(bindmap, eventid, return returnvalue);
// push arguments
Push(L, pPlayer);
EVENT_EXECUTE(returnedargs);
FOR_RET(iter)
{
// process returned arguments
}
ENDCALL();
*/

// RET is a return statement
#define EVENT_BEGIN(BINDMAP, EVENT, RET) \
    if (!BINDMAP->HasEvents(EVENT)) \
        RET; \
    lua_State* L = sEluna->L; \
    const char* _LuaBindType = sEluna->BINDMAP->groupName; \
    uint32 _LuaEvent = EVENT; \
    int _LuaStackTop = lua_gettop(L); \
    for (size_t i = 0; i < sEluna->BINDMAP->Bindings[_LuaEvent].size(); ++i) \
        lua_rawgeti(L, LUA_REGISTRYINDEX, (sEluna->BINDMAP->Bindings[_LuaEvent][i])); \
    int _LuaFuncTop = lua_gettop(L); \
    int _LuaFuncCount = _LuaFuncTop-_LuaStackTop; \
    Eluna::Push(L, _LuaEvent);

// use LUA_MULTRET for multiple return values
// return values will be at top of stack if any
#define EVENT_EXECUTE(RETVALS) \
    int _LuaReturnValues = RETVALS; \
    int _LuaParams = lua_gettop(L) - _LuaFuncTop; \
    if (_LuaParams < 1) \
    { \
        ELUNA_LOG_ERROR("[Eluna]: Executing event %u for %s, params was %i. Report to devs", _LuaEvent, _LuaBindType, _LuaParams); \
    } \
    for (int j = _LuaFuncTop-_LuaStackTop; j > 0; --j) \
    { \
        for (int i = 0; i <= _LuaParams; ++i) \
            lua_pushvalue(L, _LuaFuncTop+i); \
        Eluna::ExecuteCall(L, _LuaParams, _LuaReturnValues); \
        lua_remove(L, _LuaFuncTop--); \
    } \
    for (int i = _LuaParams; i > 0; --i) \
        if (!lua_isnone(L, i)) \
            lua_remove(L, i);

// RET is a return statement
#define ENTRY_BEGIN(BINDMAP, ENTRY, EVENT, RET) \
    int _Luabind = sEluna->BINDMAP->GetBind(ENTRY, EVENT); \
    if (!_Luabind) \
        RET; \
    lua_State* L = sEluna->L; \
    const char* _LuaBindType = sEluna->BINDMAP->groupName; \
    uint32 _LuaEvent = EVENT; \
    int _LuaStackTop = lua_gettop(L); \
    lua_rawgeti(L, LUA_REGISTRYINDEX, _Luabind); \
    int _LuaFuncTop = lua_gettop(L); \
    int _LuaFuncCount = _LuaFuncTop-_LuaStackTop; \
    Eluna::Push(L, _LuaEvent);

#define ENTRY_EXECUTE(RETVALS) \
    int _LuaReturnValues = RETVALS; \
    int _LuaParams = lua_gettop(L) - _LuaStackTop - 1; \
    Eluna::ExecuteCall(L, _LuaParams, _LuaReturnValues);

#define FOR_RETS(IT) \
    for (int IT = _LuaStackTop + 1; IT <= lua_gettop(L); ++IT)

#define ENDCALL() \
    if (lua_gettop(L) < _LuaStackTop) \
    { \
        ELUNA_LOG_ERROR("[Eluna]: Ending event %u for %s, stack top was %i and was supposed to be >= %i. Report to devs", _LuaEvent, _LuaBindType, lua_gettop(L), _LuaStackTop); \
    } \
    if (_LuaReturnValues != LUA_MULTRET && lua_gettop(L) > _LuaStackTop + _LuaFuncCount * _LuaReturnValues) \
    { \
        ELUNA_LOG_ERROR("[Eluna]: Ending event %u for %s, stack top was %i and was supposed to be between %i and %i. Report to devs", _LuaEvent, _LuaBindType, lua_gettop(L), _LuaStackTop, _LuaStackTop + _LuaFuncCount * _LuaReturnValues); \
    } \
    lua_settop(L, _LuaStackTop);

void Eluna::OnLuaStateClose()
{
    EVENT_BEGIN(ServerEventBindings, ELUNA_EVENT_ON_LUA_STATE_CLOSE, return);
    EVENT_EXECUTE(0);
    ENDCALL();
}

// areatrigger
bool Eluna::OnAreaTrigger(Player* pPlayer, AreaTriggerEntry const* pTrigger)
{
    EVENT_BEGIN(ServerEventBindings, TRIGGER_EVENT_ON_TRIGGER, return false);
    Push(L, pPlayer);
    Push(L, pTrigger->id);
    EVENT_EXECUTE(0);
    ENDCALL();
    return false;
}
// weather
void Eluna::OnChange(Weather* weather, WeatherState state, float grade)
{
    EVENT_BEGIN(ServerEventBindings, WEATHER_EVENT_ON_CHANGE, return);
    Push(L, weather->GetZone());
    Push(L, state);
    Push(L, grade);
    EVENT_EXECUTE(0);
    ENDCALL();
}
// Auction House
void Eluna::OnAdd(AuctionHouseObject* ah)
{
    EVENT_BEGIN(ServerEventBindings, AUCTION_EVENT_ON_ADD, return);
    Push(L, (ah));
    EVENT_EXECUTE(0);
    ENDCALL();
}

void Eluna::OnRemove(AuctionHouseObject* ah)
{
    EVENT_BEGIN(ServerEventBindings, AUCTION_EVENT_ON_REMOVE, return);
    Push(L, (ah));
    EVENT_EXECUTE(0);
    ENDCALL();
}

void Eluna::OnSuccessful(AuctionHouseObject* ah)
{
    EVENT_BEGIN(ServerEventBindings, AUCTION_EVENT_ON_SUCCESSFUL, return);
    Push(L, (ah));
    EVENT_EXECUTE(0);
    ENDCALL();
}

void Eluna::OnExpire(AuctionHouseObject* ah)
{
    EVENT_BEGIN(ServerEventBindings, AUCTION_EVENT_ON_EXPIRE, return);
    Push(L, (ah));
    EVENT_EXECUTE(0);
    ENDCALL();
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
    EVENT_BEGIN(ServerEventBindings, SERVER_EVENT_ON_PACKET_SEND, return);
    Push(L, new WorldPacket(packet));
    Push(L, player);
    EVENT_EXECUTE(2);
    FOR_RETS(i)
    {
        if (lua_isnoneornil(L, i))
            continue;
        if (lua_isuserdata(L, i))
            if (WorldPacket* data = CHECKOBJ<WorldPacket>(L, i, false))
                packet = *data;
        if (lua_isboolean(L, i) && !CHECKVAL<bool>(L, i, true))
        {
            result = false;
            break;
        }
    }
    ENDCALL();
}
void Eluna::OnPacketSendOne(Player* player, WorldPacket& packet, bool& result)
{
    ENTRY_BEGIN(PacketEventBindings, OpcodesList(packet.GetOpcode()), PACKET_EVENT_ON_PACKET_SEND, return);
    Push(L, new WorldPacket(packet));
    Push(L, player);
    ENTRY_EXECUTE(2);
    FOR_RETS(i)
    {
        if (lua_isnoneornil(L, i))
            continue;
        if (lua_isuserdata(L, i))
            if (WorldPacket* data = CHECKOBJ<WorldPacket>(L, i, false))
                packet = *data;
        if (lua_isboolean(L, i) && !CHECKVAL<bool>(L, i, true))
        {
            result = false;
            break;
        }
    }
    ENDCALL();
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
    EVENT_BEGIN(ServerEventBindings, SERVER_EVENT_ON_PACKET_RECEIVE, return);
    Push(L, new WorldPacket(packet));
    Push(L, player);
    EVENT_EXECUTE(2);
    FOR_RETS(i)
    {
        if (lua_isnoneornil(L, i))
            continue;
        if (lua_isuserdata(L, i))
            if (WorldPacket* data = CHECKOBJ<WorldPacket>(L, i, false))
                packet = *data;
        if (lua_isboolean(L, i) && !CHECKVAL<bool>(L, i, true))
        {
            result = false;
            break;
        }
    }
    ENDCALL();
}
void Eluna::OnPacketReceiveOne(Player* player, WorldPacket& packet, bool& result)
{
    ENTRY_BEGIN(PacketEventBindings, OpcodesList(packet.GetOpcode()), PACKET_EVENT_ON_PACKET_RECEIVE, return);
    Push(L, new WorldPacket(packet));
    Push(L, player);
    ENTRY_EXECUTE(2);
    FOR_RETS(i)
    {
        if (lua_isnoneornil(L, i))
            continue;
        if (lua_isuserdata(L, i))
            if (WorldPacket* data = CHECKOBJ<WorldPacket>(L, i, false))
                packet = *data;
        if (lua_isboolean(L, i) && !CHECKVAL<bool>(L, i, true))
        {
            result = false;
            break;
        }
    }
    ENDCALL();
}

// AddOns
bool Eluna::OnAddonMessage(Player* sender, uint32 type, std::string& msg, Player* receiver, Guild* guild, Group* group, Channel* channel)
{
    EVENT_BEGIN(ServerEventBindings, ADDON_EVENT_ON_MESSAGE, return false);
    Push(L, sender);
    Push(L, type);
    const char* c_msg = msg.c_str();
    Push(L, strtok((char*)c_msg, "\t")); // prefix
    Push(L, strtok(NULL, "")); // msg
    if (receiver)
        Push(L, receiver);
    else if (guild)
        Push(L, guild);
    else if (group)
        Push(L, group);
    else if (channel)
        Push(L, channel->GetChannelId());
    else
        Push(L);
    EVENT_EXECUTE(0);
    ENDCALL();
    return true;
}

void Eluna::OnOpenStateChange(bool open)
{
    EVENT_BEGIN(ServerEventBindings, WORLD_EVENT_ON_OPEN_STATE_CHANGE, return);
    Push(L, open);
    EVENT_EXECUTE(0);
    ENDCALL();
}

void Eluna::OnConfigLoad(bool reload)
{
    EVENT_BEGIN(ServerEventBindings, WORLD_EVENT_ON_CONFIG_LOAD, return);
    Push(L, reload);
    EVENT_EXECUTE(0);
    ENDCALL();
}

void Eluna::OnShutdownInitiate(ShutdownExitCode code, ShutdownMask mask)
{
    EVENT_BEGIN(ServerEventBindings, WORLD_EVENT_ON_SHUTDOWN_INIT, return);
    Push(L, code);
    Push(L, mask);
    EVENT_EXECUTE(0);
    ENDCALL();
}

void Eluna::OnShutdownCancel()
{
    EVENT_BEGIN(ServerEventBindings, WORLD_EVENT_ON_SHUTDOWN_CANCEL, return);
    EVENT_EXECUTE(0);
    ENDCALL();
}

void Eluna::OnWorldUpdate(uint32 diff)
{
    if (reload)
    {
        ReloadEluna();
        return;
    }

    m_EventMgr->Update(diff);
    EVENT_BEGIN(ServerEventBindings, WORLD_EVENT_ON_UPDATE, return);
    Push(L, diff);
    EVENT_EXECUTE(0);
    ENDCALL();
}

void Eluna::OnStartup()
{
    EVENT_BEGIN(ServerEventBindings, WORLD_EVENT_ON_STARTUP, return);
    EVENT_EXECUTE(0);
    ENDCALL();
}

void Eluna::OnShutdown()
{
    EVENT_BEGIN(ServerEventBindings, WORLD_EVENT_ON_SHUTDOWN, return);
    EVENT_EXECUTE(0);
    ENDCALL();
}

void Eluna::HandleGossipSelectOption(Player* pPlayer, Item* item, uint32 sender, uint32 action, std::string code)
{
    ENTRY_BEGIN(ItemGossipBindings, item->GetEntry(), GOSSIP_EVENT_ON_SELECT, return);
    pPlayer->PlayerTalkClass->ClearMenus();
    Push(L, pPlayer);
    Push(L, item);
    Push(L, sender);
    Push(L, action);
    if (code.empty())
        Push(L);
    else
        Push(L, code);
    ENTRY_EXECUTE(0);
    ENDCALL();
}

void Eluna::HandleGossipSelectOption(Player* pPlayer, uint32 menuId, uint32 sender, uint32 action, std::string code)
{
    ENTRY_BEGIN(playerGossipBindings, menuId, GOSSIP_EVENT_ON_SELECT, return);
    pPlayer->PlayerTalkClass->ClearMenus();
    Push(L, pPlayer); // receiver
    Push(L, pPlayer); // sender, just not to mess up the amount of args.
    Push(L, sender);
    Push(L, action);
    if (code.empty())
        Push(L);
    else
        Push(L, code);
    ENTRY_EXECUTE(0);
    ENDCALL();
}

// item
bool Eluna::OnDummyEffect(Unit* pCaster, uint32 spellId, SpellEffIndex effIndex, Item* pTarget)
{
    ENTRY_BEGIN(ItemEventBindings, pTarget->GetEntry(), ITEM_EVENT_ON_DUMMY_EFFECT, return false);
    Push(L, pCaster);
    Push(L, spellId);
    Push(L, effIndex);
    Push(L, pTarget);
    ENTRY_EXECUTE(0);
    ENDCALL();
    return true;
}

bool Eluna::OnQuestAccept(Player* pPlayer, Item* pItem, Quest const* pQuest)
{
    ENTRY_BEGIN(ItemEventBindings, pItem->GetEntry(), ITEM_EVENT_ON_QUEST_ACCEPT, return false);
    Push(L, pPlayer);
    Push(L, pItem);
    Push(L, pQuest);
    ENTRY_EXECUTE(0);
    ENDCALL();
    return true;
}

bool Eluna::OnUse(Player* pPlayer, Item* pItem, SpellCastTargets const& targets)
{
    ObjectGuid guid = pItem->GET_GUID();
    bool castSpell = true;

    if (!OnItemUse(pPlayer, pItem, targets))
        castSpell = false;

    pItem = pPlayer->GetItemByGuid(guid);
    if (pItem)
    {
        if (!OnItemGossip(pPlayer, pItem, targets))
            castSpell = false;
        pItem = pPlayer->GetItemByGuid(guid);
    }

    if (pItem && castSpell)
        return true;

    // Send equip error that shows no message
    // This is a hack fix to stop spell casting visual bug when a spell is not cast on use
    WorldPacket data(SMSG_INVENTORY_CHANGE_FAILURE, 18);
    data << uint8(59); // EQUIP_ERR_NONE / EQUIP_ERR_CANT_BE_DISENCHANTED
    data << ObjectGuid(guid);
    data << ObjectGuid(uint64(0));
    data << uint8(0);
    pPlayer->GetSession()->SendPacket(&data);
    return false;
}

bool Eluna::OnItemUse(Player* pPlayer, Item* pItem, SpellCastTargets const& targets)
{
    bool result = true;
    ENTRY_BEGIN(ItemEventBindings, pItem->GetEntry(), ITEM_EVENT_ON_USE, return result);
    Push(L, pPlayer);
    Push(L, pItem);
#ifndef TRINITY
    if (GameObject* target = targets.getGOTarget())
        Push(L, target);
    else if (Item* target = targets.getItemTarget())
        Push(L, target);
    else if (Corpse* target = pPlayer->GetMap()->GetCorpse(targets.getCorpseTargetGuid()))
        Push(L, target);
    else if (Unit* target = targets.getUnitTarget())
        Push(L, target);
    else
        Push(L);
#else
    if (GameObject* target = targets.GetGOTarget())
        Push(L, target);
    else if (Item* target = targets.GetItemTarget())
        Push(L, target);
    else if (Corpse* target = targets.GetCorpseTarget())
        Push(L, target);
    else if (Unit* target = targets.GetUnitTarget())
        Push(L, target);
    else if (WorldObject* target = targets.GetObjectTarget())
        Push(L, target);
    else
        Push(L);
#endif
    ENTRY_EXECUTE(1);
    FOR_RETS(i)
    {
        if (lua_isboolean(L, i))
            result = CHECKVAL<bool>(L, i, result);
    }
    ENDCALL();
    return result;
}

bool Eluna::OnItemGossip(Player* pPlayer, Item* pItem, SpellCastTargets const& /*targets*/)
{
    bool result = true;
    ENTRY_BEGIN(ItemGossipBindings, pItem->GetEntry(), GOSSIP_EVENT_ON_HELLO, return result);
    pPlayer->PlayerTalkClass->ClearMenus();
    Push(L, pPlayer);
    Push(L, pItem);
    ENTRY_EXECUTE(1);
    FOR_RETS(i)
    {
        if (lua_isboolean(L, i))
            result = CHECKVAL<bool>(L, i, result);
    }
    ENDCALL();
    return result;
}

bool Eluna::OnExpire(Player* pPlayer, ItemTemplate const* pProto)
{
    ENTRY_BEGIN(ItemEventBindings, pProto->ItemId, ITEM_EVENT_ON_EXPIRE, return false);
    Push(L, pPlayer);
    Push(L, pProto->ItemId);
    ENTRY_EXECUTE(0);
    ENDCALL();
    return true;
}

bool Eluna::OnRemove(Player* pPlayer, Item* item)
{
    ENTRY_BEGIN(ItemEventBindings, item->GetEntry(), ITEM_EVENT_ON_REMOVE, return false);
    Push(L, pPlayer);
    Push(L, item);
    ENTRY_EXECUTE(0);
    ENDCALL();
    return true;
}

// Player
bool Eluna::OnCommand(Player* player, const char* text)
{
    // If from console, player is NULL
    std::string fullcmd(text);
    if (!player || player->GetSession()->GetSecurity() >= SEC_ADMINISTRATOR)
    {
        char* creload = strtok((char*)text, " ");
        char* celuna = strtok(NULL, "");
        if (creload && celuna)
        {
            std::string reload(creload);
            std::string eluna(celuna);
            std::transform(reload.begin(), reload.end(), reload.begin(), ::tolower);
            if (reload == "reload")
            {
                std::transform(eluna.begin(), eluna.end(), eluna.begin(), ::tolower);
                if (std::string("eluna").find(eluna) == 0)
                {
                    Eluna::reload = true;
                    return false;
                }
            }
        }
    }

    bool result = true;
    EVENT_BEGIN(PlayerEventBindings, PLAYER_EVENT_ON_COMMAND, return result);
    Push(L, player);
    Push(L, fullcmd);
    EVENT_EXECUTE(1);
    FOR_RETS(i)
    {
        if (lua_isboolean(L, i))
            result = CHECKVAL<bool>(L, i, result);
    }
    ENDCALL();
    return result;
}

void Eluna::OnLootItem(Player* pPlayer, Item* pItem, uint32 count, uint64 guid)
{
    EVENT_BEGIN(PlayerEventBindings, PLAYER_EVENT_ON_LOOT_ITEM, return);
    Push(L, pPlayer);
    Push(L, pItem);
    Push(L, count);
    Push(L, guid);
    EVENT_EXECUTE(0);
    ENDCALL();
}

void Eluna::OnLootMoney(Player* pPlayer, uint32 amount)
{
    EVENT_BEGIN(PlayerEventBindings, PLAYER_EVENT_ON_LOOT_MONEY, return);
    Push(L, pPlayer);
    Push(L, amount);
    EVENT_EXECUTE(0);
    ENDCALL();
}

void Eluna::OnFirstLogin(Player* pPlayer)
{
    EVENT_BEGIN(PlayerEventBindings, PLAYER_EVENT_ON_FIRST_LOGIN, return);
    Push(L, pPlayer);
    EVENT_EXECUTE(0);
    ENDCALL();
}

void Eluna::OnRepop(Player* pPlayer)
{
    EVENT_BEGIN(PlayerEventBindings, PLAYER_EVENT_ON_REPOP, return);
    Push(L, pPlayer);
    EVENT_EXECUTE(0);
    ENDCALL();
}

void Eluna::OnResurrect(Player* pPlayer)
{
    EVENT_BEGIN(PlayerEventBindings, PLAYER_EVENT_ON_RESURRECT, return);
    Push(L, pPlayer);
    EVENT_EXECUTE(0);
    ENDCALL();
}

void Eluna::OnQuestAbandon(Player* pPlayer, uint32 questId)
{
    EVENT_BEGIN(PlayerEventBindings, PLAYER_EVENT_ON_QUEST_ABANDON, return);
    Push(L, pPlayer);
    Push(L, questId);
    EVENT_EXECUTE(0);
    ENDCALL();
}

void Eluna::OnEquip(Player* pPlayer, Item* pItem, uint8 bag, uint8 slot)
{
    EVENT_BEGIN(PlayerEventBindings, PLAYER_EVENT_ON_EQUIP, return);
    Push(L, pPlayer);
    Push(L, pItem);
    Push(L, bag);
    Push(L, slot);
    EVENT_EXECUTE(0);
    ENDCALL();
}

InventoryResult Eluna::OnCanUseItem(const Player* pPlayer, uint32 itemEntry)
{
    InventoryResult result = EQUIP_ERR_OK;
    EVENT_BEGIN(PlayerEventBindings, PLAYER_EVENT_ON_CAN_USE_ITEM, return result);
    Push(L, pPlayer);
    Push(L, itemEntry);
    EVENT_EXECUTE(1);
    FOR_RETS(i)
    {
        if (!lua_isnumber(L, i))
            continue;
        uint32 res = CHECKVAL<uint32>(L, i, EQUIP_ERR_OK);
        if (res != EQUIP_ERR_OK)
            result = (InventoryResult)res;
    }
    ENDCALL();
    return result;
}
void Eluna::OnPlayerEnterCombat(Player* pPlayer, Unit* pEnemy)
{
    EVENT_BEGIN(PlayerEventBindings, PLAYER_EVENT_ON_ENTER_COMBAT, return);
    Push(L, pPlayer);
    Push(L, pEnemy);
    EVENT_EXECUTE(0);
    ENDCALL();
}

void Eluna::OnPlayerLeaveCombat(Player* pPlayer)
{
    EVENT_BEGIN(PlayerEventBindings, PLAYER_EVENT_ON_LEAVE_COMBAT, return);
    Push(L, pPlayer);
    EVENT_EXECUTE(0);
    ENDCALL();
}

void Eluna::OnPVPKill(Player* pKiller, Player* pKilled)
{
    EVENT_BEGIN(PlayerEventBindings, PLAYER_EVENT_ON_KILL_PLAYER, return);
    Push(L, pKiller);
    Push(L, pKilled);
    EVENT_EXECUTE(0);
    ENDCALL();
}

void Eluna::OnCreatureKill(Player* pKiller, Creature* pKilled)
{
    EVENT_BEGIN(PlayerEventBindings, PLAYER_EVENT_ON_KILL_CREATURE, return);
    Push(L, pKiller);
    Push(L, pKilled);
    EVENT_EXECUTE(0);
    ENDCALL();
}

void Eluna::OnPlayerKilledByCreature(Creature* pKiller, Player* pKilled)
{
    EVENT_BEGIN(PlayerEventBindings, PLAYER_EVENT_ON_KILLED_BY_CREATURE, return);
    Push(L, pKiller);
    Push(L, pKilled);
    EVENT_EXECUTE(0);
    ENDCALL();
}

void Eluna::OnLevelChanged(Player* pPlayer, uint8 oldLevel)
{
    EVENT_BEGIN(PlayerEventBindings, PLAYER_EVENT_ON_LEVEL_CHANGE, return);
    Push(L, pPlayer);
    Push(L, oldLevel);
    EVENT_EXECUTE(0);
    ENDCALL();
}

void Eluna::OnFreeTalentPointsChanged(Player* pPlayer, uint32 newPoints)
{
    EVENT_BEGIN(PlayerEventBindings, PLAYER_EVENT_ON_TALENTS_CHANGE, return);
    Push(L, pPlayer);
    Push(L, newPoints);
    EVENT_EXECUTE(0);
    ENDCALL();
}

void Eluna::OnTalentsReset(Player* pPlayer, bool noCost)
{
    EVENT_BEGIN(PlayerEventBindings, PLAYER_EVENT_ON_TALENTS_RESET, return);
    Push(L, pPlayer);
    Push(L, noCost);
    EVENT_EXECUTE(0);
    ENDCALL();
}

void Eluna::OnMoneyChanged(Player* pPlayer, int32& amount)
{
    EVENT_BEGIN(PlayerEventBindings, PLAYER_EVENT_ON_MONEY_CHANGE, return);
    Push(L, pPlayer);
    Push(L, amount);
    EVENT_EXECUTE(0);
    ENDCALL();
}

void Eluna::OnGiveXP(Player* pPlayer, uint32& amount, Unit* pVictim)
{
    EVENT_BEGIN(PlayerEventBindings, PLAYER_EVENT_ON_GIVE_XP, return);
    Push(L, pPlayer);
    Push(L, amount);
    Push(L, pVictim);
    EVENT_EXECUTE(1);
    FOR_RETS(i)
    {
        if (lua_isnumber(L, i))
            amount = CHECKVAL<uint32>(L, i, amount);
    }
    ENDCALL();
}

void Eluna::OnReputationChange(Player* pPlayer, uint32 factionID, int32& standing, bool incremental)
{
    EVENT_BEGIN(PlayerEventBindings, PLAYER_EVENT_ON_REPUTATION_CHANGE, return);
    Push(L, pPlayer);
    Push(L, factionID);
    Push(L, standing);
    Push(L, incremental);
    EVENT_EXECUTE(1);
    FOR_RETS(i)
    {
        if (lua_isnumber(L, i))
            standing = CHECKVAL<uint32>(L, i, standing);
    }
    ENDCALL();
}

void Eluna::OnDuelRequest(Player* pTarget, Player* pChallenger)
{
    EVENT_BEGIN(PlayerEventBindings, PLAYER_EVENT_ON_DUEL_REQUEST, return);
    Push(L, pTarget);
    Push(L, pChallenger);
    EVENT_EXECUTE(0);
    ENDCALL();
}

void Eluna::OnDuelStart(Player* pStarter, Player* pChallenger)
{
    EVENT_BEGIN(PlayerEventBindings, PLAYER_EVENT_ON_DUEL_START, return);
    Push(L, pStarter);
    Push(L, pChallenger);
    EVENT_EXECUTE(0);
    ENDCALL();
}

void Eluna::OnDuelEnd(Player* pWinner, Player* pLoser, DuelCompleteType type)
{
    EVENT_BEGIN(PlayerEventBindings, PLAYER_EVENT_ON_DUEL_END, return);
    Push(L, pWinner);
    Push(L, pLoser);
    Push(L, type);
    EVENT_EXECUTE(0);
    ENDCALL();
}

void Eluna::OnEmote(Player* pPlayer, uint32 emote)
{
    EVENT_BEGIN(PlayerEventBindings, PLAYER_EVENT_ON_EMOTE, return);
    Push(L, pPlayer);
    Push(L, emote);
    EVENT_EXECUTE(0);
    ENDCALL();
}

void Eluna::OnTextEmote(Player* pPlayer, uint32 textEmote, uint32 emoteNum, uint64 guid)
{
    EVENT_BEGIN(PlayerEventBindings, PLAYER_EVENT_ON_TEXT_EMOTE, return);
    Push(L, pPlayer);
    Push(L, textEmote);
    Push(L, emoteNum);
    Push(L, guid);
    EVENT_EXECUTE(0);
    ENDCALL();
}

void Eluna::OnSpellCast(Player* pPlayer, Spell* pSpell, bool skipCheck)
{
    EVENT_BEGIN(PlayerEventBindings, PLAYER_EVENT_ON_SPELL_CAST, return);
    Push(L, pPlayer);
    Push(L, pSpell);
    Push(L, skipCheck);
    EVENT_EXECUTE(0);
    ENDCALL();
}

void Eluna::OnLogin(Player* pPlayer)
{
    EVENT_BEGIN(PlayerEventBindings, PLAYER_EVENT_ON_LOGIN, return);
    Push(L, pPlayer);
    EVENT_EXECUTE(0);
    ENDCALL();
}

void Eluna::OnLogout(Player* pPlayer)
{
    EVENT_BEGIN(PlayerEventBindings, PLAYER_EVENT_ON_LOGOUT, return);
    Push(L, pPlayer);
    EVENT_EXECUTE(0);
    ENDCALL();
}

void Eluna::OnCreate(Player* pPlayer)
{
    EVENT_BEGIN(PlayerEventBindings, PLAYER_EVENT_ON_CHARACTER_CREATE, return);
    Push(L, pPlayer);
    EVENT_EXECUTE(0);
    ENDCALL();
}

void Eluna::OnDelete(uint32 guidlow)
{
    EVENT_BEGIN(PlayerEventBindings, PLAYER_EVENT_ON_CHARACTER_DELETE, return);
    Push(L, guidlow);
    EVENT_EXECUTE(0);
    ENDCALL();
}

void Eluna::OnSave(Player* pPlayer)
{
    EVENT_BEGIN(PlayerEventBindings, PLAYER_EVENT_ON_SAVE, return);
    Push(L, pPlayer);
    EVENT_EXECUTE(0);
    ENDCALL();
}

void Eluna::OnBindToInstance(Player* pPlayer, Difficulty difficulty, uint32 mapid, bool permanent)
{
    EVENT_BEGIN(PlayerEventBindings, PLAYER_EVENT_ON_BIND_TO_INSTANCE, return);
    Push(L, pPlayer);
    Push(L, difficulty);
    Push(L, mapid);
    Push(L, permanent);
    EVENT_EXECUTE(0);
    ENDCALL();
}

void Eluna::OnUpdateZone(Player* pPlayer, uint32 newZone, uint32 newArea)
{
    EVENT_BEGIN(PlayerEventBindings, PLAYER_EVENT_ON_UPDATE_ZONE, return);
    Push(L, pPlayer);
    Push(L, newZone);
    Push(L, newArea);
    EVENT_EXECUTE(0);
    ENDCALL();
}

void Eluna::OnMapChanged(Player* player)
{
    EVENT_BEGIN(PlayerEventBindings, PLAYER_EVENT_ON_MAP_CHANGE, return);
    Push(L, player);
    EVENT_EXECUTE(0);
    ENDCALL();
}

bool Eluna::OnChat(Player* pPlayer, uint32 type, uint32 lang, std::string& msg)
{
    if (lang == LANG_ADDON && OnAddonMessage(pPlayer, type, msg, NULL, NULL, NULL, NULL))
        return true;
    bool result = true;
    EVENT_BEGIN(PlayerEventBindings, PLAYER_EVENT_ON_CHAT, return result);
    Push(L, pPlayer);
    Push(L, msg);
    Push(L, type);
    Push(L, lang);
    EVENT_EXECUTE(2);
    FOR_RETS(i)
    {
        if (lua_isnoneornil(L, i))
            continue;
        if (lua_isstring(L, i))
            if (const char* c_str = CHECKVAL<const char*>(L, i, NULL))
                msg = std::string(c_str);
        else if (lua_isboolean(L, i) && !CHECKVAL<bool>(L, i, true))
        {
            result = false;
            break;
        }
    }
    ENDCALL();
    return result;
}

bool Eluna::OnChat(Player* pPlayer, uint32 type, uint32 lang, std::string& msg, Group* pGroup)
{
    if (lang == LANG_ADDON && OnAddonMessage(pPlayer, type, msg, NULL, NULL, pGroup, NULL))
        return true;
    bool result = true;
    EVENT_BEGIN(PlayerEventBindings, PLAYER_EVENT_ON_GROUP_CHAT, return result);
    Push(L, pPlayer);
    Push(L, msg);
    Push(L, type);
    Push(L, lang);
    Push(L, pGroup);
    EVENT_EXECUTE(2);
    FOR_RETS(i)
    {
        if (lua_isnoneornil(L, i))
            continue;
        if (lua_isstring(L, i))
            if (const char* c_str = CHECKVAL<const char*>(L, i, NULL))
                msg = std::string(c_str);
        else if (lua_isboolean(L, i) && !CHECKVAL<bool>(L, i, true))
        {
            result = false;
            break;
        }
    }
    ENDCALL();
    return result;
}

bool Eluna::OnChat(Player* pPlayer, uint32 type, uint32 lang, std::string& msg, Guild* pGuild)
{
    if (lang == LANG_ADDON && OnAddonMessage(pPlayer, type, msg, NULL, pGuild, NULL, NULL))
        return true;
    bool result = true;
    EVENT_BEGIN(PlayerEventBindings, PLAYER_EVENT_ON_GUILD_CHAT, return result);
    Push(L, pPlayer);
    Push(L, msg);
    Push(L, type);
    Push(L, lang);
    Push(L, pGuild);
    EVENT_EXECUTE(2);
    FOR_RETS(i)
    {
        if (lua_isnoneornil(L, i))
            continue;
        if (lua_isstring(L, i))
            if (const char* c_str = CHECKVAL<const char*>(L, i, NULL))
                msg = std::string(c_str);
        else if (lua_isboolean(L, i) && !CHECKVAL<bool>(L, i, true))
        {
            result = false;
            break;
        }
    }
    ENDCALL();
    return result;
}

bool Eluna::OnChat(Player* pPlayer, uint32 type, uint32 lang, std::string& msg, Channel* pChannel)
{
    if (lang == LANG_ADDON && OnAddonMessage(pPlayer, type, msg, NULL, NULL, NULL, pChannel))
        return true;
    bool result = true;
    EVENT_BEGIN(PlayerEventBindings, PLAYER_EVENT_ON_CHANNEL_CHAT, return result);
    Push(L, pPlayer);
    Push(L, msg);
    Push(L, type);
    Push(L, lang);
    Push(L, pChannel->GetChannelId());
    EVENT_EXECUTE(2);
    FOR_RETS(i)
    {
        if (lua_isnoneornil(L, i))
            continue;
        if (lua_isstring(L, i))
            if (const char* c_str = CHECKVAL<const char*>(L, i, NULL))
                msg = std::string(c_str);
        else if (lua_isboolean(L, i) && !CHECKVAL<bool>(L, i, true))
        {
            result = false;
            break;
        }
    }
    ENDCALL();
    return result;
}

bool Eluna::OnChat(Player* pPlayer, uint32 type, uint32 lang, std::string& msg, Player* pReceiver)
{
    if (lang == LANG_ADDON && OnAddonMessage(pPlayer, type, msg, pReceiver, NULL, NULL, NULL))
        return true;
    bool result = true;
    EVENT_BEGIN(PlayerEventBindings, PLAYER_EVENT_ON_WHISPER, return result);
    Push(L, pPlayer);
    Push(L, msg);
    Push(L, type);
    Push(L, lang);
    Push(L, pReceiver);
    EVENT_EXECUTE(2);
    FOR_RETS(i)
    {
        if (lua_isnoneornil(L, i))
            continue;
        if (lua_isstring(L, i))
            if (const char* c_str = CHECKVAL<const char*>(L, i, NULL))
                msg = std::string(c_str);
        else if (lua_isboolean(L, i) && !CHECKVAL<bool>(L, i, true))
        {
            result = false;
            break;
        }
    }
    ENDCALL();
    return result;
}

#ifndef CLASSIC
#ifndef TBC
// Vehicle
void Eluna::OnInstall(Vehicle* vehicle)
{
    EVENT_BEGIN(VehicleEventBindings, VEHICLE_EVENT_ON_INSTALL, return);
    Push(L, vehicle);
    EVENT_EXECUTE(0);
    ENDCALL();
}

void Eluna::OnUninstall(Vehicle* vehicle)
{
    EVENT_BEGIN(VehicleEventBindings, VEHICLE_EVENT_ON_UNINSTALL, return);
    Push(L, vehicle);
    EVENT_EXECUTE(0);
    ENDCALL();
}

void Eluna::OnInstallAccessory(Vehicle* vehicle, Creature* accessory)
{
    EVENT_BEGIN(VehicleEventBindings, VEHICLE_EVENT_ON_INSTALL_ACCESSORY, return);
    Push(L, vehicle);
    Push(L, accessory);
    EVENT_EXECUTE(0);
    ENDCALL();
}

void Eluna::OnAddPassenger(Vehicle* vehicle, Unit* passenger, int8 seatId)
{
    EVENT_BEGIN(VehicleEventBindings, VEHICLE_EVENT_ON_ADD_PASSENGER, return);
    Push(L, vehicle);
    Push(L, passenger);
    Push(L, seatId);
    EVENT_EXECUTE(0);
    ENDCALL();
}

void Eluna::OnRemovePassenger(Vehicle* vehicle, Unit* passenger)
{
    EVENT_BEGIN(VehicleEventBindings, VEHICLE_EVENT_ON_REMOVE_PASSENGER, return);
    Push(L, vehicle);
    Push(L, passenger);
    EVENT_EXECUTE(0);
    ENDCALL();
}
#endif
#endif

void Eluna::OnAddMember(Guild* guild, Player* player, uint32 plRank)
{
    EVENT_BEGIN(GuildEventBindings, GUILD_EVENT_ON_ADD_MEMBER, return);
    Push(L, guild);
    Push(L, player);
    Push(L, plRank);
    EVENT_EXECUTE(0);
    ENDCALL();
}

void Eluna::OnRemoveMember(Guild* guild, Player* player, bool isDisbanding)
{
    EVENT_BEGIN(GuildEventBindings, GUILD_EVENT_ON_REMOVE_MEMBER, return);
    Push(L, guild);
    Push(L, player);
    Push(L, isDisbanding);
    EVENT_EXECUTE(0);
    ENDCALL();
}

void Eluna::OnMOTDChanged(Guild* guild, const std::string& newMotd)
{
    EVENT_BEGIN(GuildEventBindings, GUILD_EVENT_ON_MOTD_CHANGE, return);
    Push(L, guild);
    Push(L, newMotd);
    EVENT_EXECUTE(0);
    ENDCALL();
}

void Eluna::OnInfoChanged(Guild* guild, const std::string& newInfo)
{
    EVENT_BEGIN(GuildEventBindings, GUILD_EVENT_ON_INFO_CHANGE, return);
    Push(L, guild);
    Push(L, newInfo);
    EVENT_EXECUTE(0);
    ENDCALL();
}

void Eluna::OnCreate(Guild* guild, Player* leader, const std::string& name)
{
    EVENT_BEGIN(GuildEventBindings, GUILD_EVENT_ON_CREATE, return);
    Push(L, guild);
    Push(L, leader);
    Push(L, name);
    EVENT_EXECUTE(0);
    ENDCALL();
}

void Eluna::OnDisband(Guild* guild)
{
    EVENT_BEGIN(GuildEventBindings, GUILD_EVENT_ON_DISBAND, return);
    Push(L, guild);
    EVENT_EXECUTE(0);
    ENDCALL();
}

void Eluna::OnMemberWitdrawMoney(Guild* guild, Player* player, uint32 &amount, bool isRepair) // isRepair not a part of Mangos, implement?
{
    EVENT_BEGIN(GuildEventBindings, GUILD_EVENT_ON_MONEY_WITHDRAW, return);
    Push(L, guild);
    Push(L, player);
    Push(L, amount);
    Push(L, isRepair); // isRepair not a part of Mangos, implement?
    EVENT_EXECUTE(0);
    ENDCALL();
}

void Eluna::OnMemberDepositMoney(Guild* guild, Player* player, uint32 &amount)
{
    EVENT_BEGIN(GuildEventBindings, GUILD_EVENT_ON_MONEY_DEPOSIT, return);
    Push(L, guild);
    Push(L, player);
    Push(L, amount);
    EVENT_EXECUTE(0);
    ENDCALL();
}

void Eluna::OnItemMove(Guild* guild, Player* player, Item* pItem, bool isSrcBank, uint8 srcContainer, uint8 srcSlotId,
    bool isDestBank, uint8 destContainer, uint8 destSlotId)
{
    EVENT_BEGIN(GuildEventBindings, GUILD_EVENT_ON_ITEM_MOVE, return);
    Push(L, guild);
    Push(L, player);
    Push(L, pItem);
    Push(L, isSrcBank);
    Push(L, srcContainer);
    Push(L, srcSlotId);
    Push(L, isDestBank);
    Push(L, destContainer);
    Push(L, destSlotId);
    EVENT_EXECUTE(0);
    ENDCALL();
}

void Eluna::OnEvent(Guild* guild, uint8 eventType, uint32 playerGuid1, uint32 playerGuid2, uint8 newRank)
{
    EVENT_BEGIN(GuildEventBindings, GUILD_EVENT_ON_EVENT, return);
    Push(L, guild);
    Push(L, eventType);
    Push(L, playerGuid1);
    Push(L, playerGuid2);
    Push(L, newRank);
    EVENT_EXECUTE(0);
    ENDCALL();
}

void Eluna::OnBankEvent(Guild* guild, uint8 eventType, uint8 tabId, uint32 playerGuid, uint32 itemOrMoney, uint16 itemStackCount, uint8 destTabId)
{
    EVENT_BEGIN(GuildEventBindings, GUILD_EVENT_ON_BANK_EVENT, return);
    Push(L, guild);
    Push(L, eventType);
    Push(L, tabId);
    Push(L, playerGuid);
    Push(L, itemOrMoney);
    Push(L, itemStackCount);
    Push(L, destTabId);
    EVENT_EXECUTE(0);
    ENDCALL();
}
// Group
void Eluna::OnAddMember(Group* group, uint64 guid)
{
    EVENT_BEGIN(GroupEventBindings, GROUP_EVENT_ON_MEMBER_ADD, return);
    Push(L, group);
    Push(L, guid);
    EVENT_EXECUTE(0);
    ENDCALL();
}

void Eluna::OnInviteMember(Group* group, uint64 guid)
{
    EVENT_BEGIN(GroupEventBindings, GROUP_EVENT_ON_MEMBER_INVITE, return);
    Push(L, group);
    Push(L, guid);
    EVENT_EXECUTE(0);
    ENDCALL();
}

void Eluna::OnRemoveMember(Group* group, uint64 guid, uint8 method)
{
    EVENT_BEGIN(GroupEventBindings, GROUP_EVENT_ON_MEMBER_REMOVE, return);
    Push(L, group);
    Push(L, guid);
    Push(L, method);
    EVENT_EXECUTE(0);
    ENDCALL();
}

void Eluna::OnChangeLeader(Group* group, uint64 newLeaderGuid, uint64 oldLeaderGuid)
{
    EVENT_BEGIN(GroupEventBindings, GROUP_EVENT_ON_LEADER_CHANGE, return);
    Push(L, group);
    Push(L, newLeaderGuid);
    Push(L, oldLeaderGuid);
    EVENT_EXECUTE(0);
    ENDCALL();
}

void Eluna::OnDisband(Group* group)
{
    EVENT_BEGIN(GroupEventBindings, GROUP_EVENT_ON_DISBAND, return);
    Push(L, group);
    EVENT_EXECUTE(0);
    ENDCALL();
}

void Eluna::OnCreate(Group* group, uint64 leaderGuid, GroupType groupType)
{
    EVENT_BEGIN(GroupEventBindings, GROUP_EVENT_ON_CREATE, return);
    Push(L, group);
    Push(L, leaderGuid);
    Push(L, groupType);
    EVENT_EXECUTE(0);
    ENDCALL();
}

/* Map */
void Eluna::OnCreate(Map* map)
{
    EVENT_BEGIN(ServerEventBindings, MAP_EVENT_ON_CREATE, return);
    Push(L, map);
    EVENT_EXECUTE(0);
    ENDCALL();
}
void Eluna::OnDestroy(Map* map)
{
    EVENT_BEGIN(ServerEventBindings, MAP_EVENT_ON_DESTROY, return);
    Push(L, map);
    EVENT_EXECUTE(0);
    ENDCALL();
}
void Eluna::OnPlayerEnter(Map* map, Player* player)
{
    EVENT_BEGIN(ServerEventBindings, MAP_EVENT_ON_PLAYER_ENTER, return);
    Push(L, map);
    Push(L, player);
    EVENT_EXECUTE(0);
    ENDCALL();
}
void Eluna::OnPlayerLeave(Map* map, Player* player)
{
    EVENT_BEGIN(ServerEventBindings, MAP_EVENT_ON_PLAYER_LEAVE, return);
    Push(L, map);
    Push(L, player);
    EVENT_EXECUTE(0);
    ENDCALL();
}
void Eluna::OnUpdate(Map* map, uint32 diff)
{
    EVENT_BEGIN(ServerEventBindings, MAP_EVENT_ON_UPDATE, return);
    Push(L, map);
    Push(L, diff);
    EVENT_EXECUTE(0);
    ENDCALL();
}
void Eluna::OnRemove(GameObject* gameobject)
{
    EVENT_BEGIN(ServerEventBindings, WORLD_EVENT_ON_DELETE_GAMEOBJECT, return);
    Push(L, gameobject);
    EVENT_EXECUTE(0);
    ENDCALL();
}
void Eluna::OnRemove(Creature* creature)
{
    EVENT_BEGIN(ServerEventBindings, WORLD_EVENT_ON_DELETE_CREATURE, return);
    Push(L, creature);
    EVENT_EXECUTE(0);
    ENDCALL();
}

// creature
bool Eluna::OnDummyEffect(Unit* pCaster, uint32 spellId, SpellEffIndex effIndex, Creature* pTarget)
{
    ENTRY_BEGIN(CreatureEventBindings, pTarget->GetEntry(), CREATURE_EVENT_ON_DUMMY_EFFECT, return false);
    Push(L, pCaster);
    Push(L, spellId);
    Push(L, effIndex);
    Push(L, pTarget);
    ENTRY_EXECUTE(0);
    ENDCALL();
    return true;
}

bool Eluna::OnGossipHello(Player* pPlayer, Creature* pCreature)
{
    ENTRY_BEGIN(CreatureGossipBindings, pCreature->GetEntry(), GOSSIP_EVENT_ON_HELLO, return false);
    pPlayer->PlayerTalkClass->ClearMenus();
    Push(L, pPlayer);
    Push(L, pCreature);
    ENTRY_EXECUTE(0);
    ENDCALL();
    return true;
}

bool Eluna::OnGossipSelect(Player* pPlayer, Creature* pCreature, uint32 sender, uint32 action)
{
    ENTRY_BEGIN(CreatureGossipBindings, pCreature->GetEntry(), GOSSIP_EVENT_ON_SELECT, return false);
    pPlayer->PlayerTalkClass->ClearMenus();
    Push(L, pPlayer);
    Push(L, pCreature);
    Push(L, sender);
    Push(L, action);
    ENTRY_EXECUTE(0);
    ENDCALL();
    return true;
}

bool Eluna::OnGossipSelectCode(Player* pPlayer, Creature* pCreature, uint32 sender, uint32 action, const char* code)
{
    ENTRY_BEGIN(CreatureGossipBindings, pCreature->GetEntry(), GOSSIP_EVENT_ON_SELECT, return false);
    pPlayer->PlayerTalkClass->ClearMenus();
    Push(L, pPlayer);
    Push(L, pCreature);
    Push(L, sender);
    Push(L, action);
    Push(L, code);
    ENTRY_EXECUTE(0);
    ENDCALL();
    return true;
}

bool Eluna::OnQuestAccept(Player* pPlayer, Creature* pCreature, Quest const* pQuest)
{
    ENTRY_BEGIN(CreatureEventBindings, pCreature->GetEntry(), CREATURE_EVENT_ON_QUEST_ACCEPT, return false);
    Push(L, pPlayer);
    Push(L, pCreature);
    Push(L, pQuest);
    ENTRY_EXECUTE(0);
    ENDCALL();
    return true;
}

bool Eluna::OnQuestComplete(Player* pPlayer, Creature* pCreature, Quest const* pQuest)
{
    ENTRY_BEGIN(CreatureEventBindings, pCreature->GetEntry(), CREATURE_EVENT_ON_QUEST_COMPLETE, return false);
    Push(L, pPlayer);
    Push(L, pCreature);
    Push(L, pQuest);
    ENTRY_EXECUTE(0);
    ENDCALL();
    return true;
}

bool Eluna::OnQuestReward(Player* pPlayer, Creature* pCreature, Quest const* pQuest)
{
    ENTRY_BEGIN(CreatureEventBindings, pCreature->GetEntry(), CREATURE_EVENT_ON_QUEST_REWARD, return false);
    Push(L, pPlayer);
    Push(L, pCreature);
    Push(L, pQuest);
    ENTRY_EXECUTE(0);
    ENDCALL();
    return true;
}

uint32 Eluna::GetDialogStatus(Player* pPlayer, Creature* pCreature)
{
    ENTRY_BEGIN(CreatureEventBindings, pCreature->GetEntry(), CREATURE_EVENT_ON_DIALOG_STATUS, return 0);
    Push(L, pPlayer);
    Push(L, pCreature);
    ENTRY_EXECUTE(0);
    ENDCALL();
    return DIALOG_STATUS_SCRIPTED_NO_STATUS;
}

void Eluna::OnSummoned(Creature* pCreature, Unit* pSummoner)
{
    ENTRY_BEGIN(CreatureEventBindings, pCreature->GetEntry(), CREATURE_EVENT_ON_SUMMONED, return);
    Push(L, pCreature);
    Push(L, pSummoner);
    ENTRY_EXECUTE(0);
    ENDCALL();
}

void Eluna::OnAddToWorld(Creature* creature)
{
    ENTRY_BEGIN(CreatureEventBindings, creature->GetEntry(), CREATURE_EVENT_ON_ADD, return);
    Push(L, creature);
    ENTRY_EXECUTE(0);
    ENDCALL();
}

void Eluna::OnRemoveFromWorld(Creature* creature)
{
    ENTRY_BEGIN(CreatureEventBindings, creature->GetEntry(), CREATURE_EVENT_ON_REMOVE, return);
    Push(L, creature);
    ENTRY_EXECUTE(0);
    ENDCALL();
}

struct ElunaCreatureAI : ScriptedAI
{
#ifndef TRINITY
#define me  m_creature
#endif

    ElunaCreatureAI(Creature* creature): ScriptedAI(creature)
    {
        JustRespawned();
    }
    ~ElunaCreatureAI() {}

    //Called at World update tick
#ifndef TRINITY
    void UpdateAI(const uint32 diff) override
#else
    void UpdateAI(uint32 diff) override
#endif
    {
#ifndef TRINITY
        if (IsCombatMovement())
            ScriptedAI::UpdateAI(diff);
#else
        if (!me->HasReactState(REACT_PASSIVE))
            ScriptedAI::UpdateAI(diff);
#endif
        ENTRY_BEGIN(CreatureEventBindings, me->GetEntry(), CREATURE_EVENT_ON_AIUPDATE, return);
        Eluna::Push(L, me);
        Eluna::Push(L, diff);
        ENTRY_EXECUTE(0);
        ENDCALL();
    }

    //Called for reaction at enter to combat if not in combat yet (enemy can be NULL)
    //Called at creature aggro either by MoveInLOS or Attack Start
    void EnterCombat(Unit* target) override
    {
        ScriptedAI::EnterCombat(target);
        ENTRY_BEGIN(CreatureEventBindings, me->GetEntry(), CREATURE_EVENT_ON_ENTER_COMBAT, return);
        Eluna::Push(L, me);
        Eluna::Push(L, target);
        ENTRY_EXECUTE(0);
        ENDCALL();
    }

    // Called at any Damage from any attacker (before damage apply)
    void DamageTaken(Unit* attacker, uint32& damage) override
    {
        ScriptedAI::DamageTaken(attacker, damage);
        ENTRY_BEGIN(CreatureEventBindings, me->GetEntry(), CREATURE_EVENT_ON_DAMAGE_TAKEN, return);
        Eluna::Push(L, me);
        Eluna::Push(L, attacker);
        Eluna::Push(L, damage);
        ENTRY_EXECUTE(1);
        FOR_RETS(i)
        {
            if (lua_isnumber(L, i))
                damage = Eluna::CHECKVAL<uint32>(L, i, damage);
        }
        ENDCALL();
    }

    //Called at creature death
    void JustDied(Unit* killer) override
    {
        ScriptedAI::JustDied(killer);
        On_Reset();
        ENTRY_BEGIN(CreatureEventBindings, me->GetEntry(), CREATURE_EVENT_ON_DIED, return);
        Eluna::Push(L, me);
        Eluna::Push(L, killer);
        ENTRY_EXECUTE(0);
        ENDCALL();
    }

    //Called at creature killing another unit
    void KilledUnit(Unit* victim) override
    {
        ScriptedAI::KilledUnit(victim);
        ENTRY_BEGIN(CreatureEventBindings, me->GetEntry(), CREATURE_EVENT_ON_TARGET_DIED, return);
        Eluna::Push(L, me);
        Eluna::Push(L, victim);
        ENTRY_EXECUTE(0);
        ENDCALL();
    }

    // Called when the creature summon successfully other creature
    void JustSummoned(Creature* summon) override
    {
        ScriptedAI::JustSummoned(summon);
        ENTRY_BEGIN(CreatureEventBindings, me->GetEntry(), CREATURE_EVENT_ON_JUST_SUMMONED_CREATURE, return);
        Eluna::Push(L, me);
        Eluna::Push(L, summon);
        ENTRY_EXECUTE(0);
        ENDCALL();
    }

    // Called when a summoned creature is despawned
    void SummonedCreatureDespawn(Creature* summon) override
    {
        ScriptedAI::SummonedCreatureDespawn(summon);
        ENTRY_BEGIN(CreatureEventBindings, me->GetEntry(), CREATURE_EVENT_ON_SUMMONED_CREATURE_DESPAWN, return);
        Eluna::Push(L, me);
        Eluna::Push(L, summon);
        ENTRY_EXECUTE(0);
        ENDCALL();
    }

    //Called at waypoint reached or PointMovement end
    void MovementInform(uint32 type, uint32 id) override
    {
        ScriptedAI::MovementInform(type, id);
        ENTRY_BEGIN(CreatureEventBindings, me->GetEntry(), CREATURE_EVENT_ON_REACH_WP, return);
        Eluna::Push(L, me);
        Eluna::Push(L, type);
        Eluna::Push(L, id);
        ENTRY_EXECUTE(0);
        ENDCALL();
    }

    // Called before EnterCombat even before the creature is in combat.
    void AttackStart(Unit* target) override
    {
        ScriptedAI::AttackStart(target);
        ENTRY_BEGIN(CreatureEventBindings, me->GetEntry(), CREATURE_EVENT_ON_PRE_COMBAT, return);
        Eluna::Push(L, me);
        Eluna::Push(L, target);
        ENTRY_EXECUTE(0);
        ENDCALL();
    }

    // Called for reaction at stopping attack at no attackers or targets
    void EnterEvadeMode() override
    {
        ScriptedAI::EnterEvadeMode();
        On_Reset();
        ENTRY_BEGIN(CreatureEventBindings, me->GetEntry(), CREATURE_EVENT_ON_LEAVE_COMBAT, return);
        Eluna::Push(L, me);
        ENTRY_EXECUTE(0);
        ENDCALL();
    }

    // Called when the creature is target of hostile action: swing, hostile spell landed, fear/etc)
    void AttackedBy(Unit* attacker) override
    {
        ScriptedAI::AttackedBy(attacker);
        ENTRY_BEGIN(CreatureEventBindings, me->GetEntry(), CREATURE_EVENT_ON_ATTACKED_AT, return);
        Eluna::Push(L, me);
        Eluna::Push(L, attacker);
        ENTRY_EXECUTE(0);
        ENDCALL();
    }

    // Called when creature is spawned or respawned (for reseting variables)
    void JustRespawned() override
    {
        ScriptedAI::JustRespawned();
        On_Reset();
        ENTRY_BEGIN(CreatureEventBindings, me->GetEntry(), CREATURE_EVENT_ON_SPAWN, return);
        Eluna::Push(L, me);
        ENTRY_EXECUTE(0);
        ENDCALL();
    }

    // Called at reaching home after evade
    void JustReachedHome() override
    {
        ScriptedAI::JustReachedHome();
        ENTRY_BEGIN(CreatureEventBindings, me->GetEntry(), CREATURE_EVENT_ON_REACH_HOME, return);
        Eluna::Push(L, me);
        ENTRY_EXECUTE(0);
        ENDCALL();
    }

    // Called at text emote receive from player
    void ReceiveEmote(Player* player, uint32 emoteId) override
    {
        ScriptedAI::ReceiveEmote(player, emoteId);
        ENTRY_BEGIN(CreatureEventBindings, me->GetEntry(), CREATURE_EVENT_ON_RECEIVE_EMOTE, return);
        Eluna::Push(L, me);
        Eluna::Push(L, player);
        Eluna::Push(L, emoteId);
        ENTRY_EXECUTE(0);
        ENDCALL();
    }

    // called when the corpse of this creature gets removed
    void CorpseRemoved(uint32& respawnDelay) override
    {
        ScriptedAI::CorpseRemoved(respawnDelay);
        ENTRY_BEGIN(CreatureEventBindings, me->GetEntry(), CREATURE_EVENT_ON_CORPSE_REMOVED, return);
        Eluna::Push(L, me);
        Eluna::Push(L, respawnDelay);
        ENTRY_EXECUTE(1);
        FOR_RETS(i)
        {
            if (lua_isnumber(L, i))
                respawnDelay = Eluna::CHECKVAL<uint32>(L, i, respawnDelay);
        }
        ENDCALL();
    }

#ifndef TRINITY
    // Enables use of MoveInLineOfSight
    bool IsVisible(Unit* who) const override
    {
        return true;
    }
#endif

    void MoveInLineOfSight(Unit* who) override
    {
        ScriptedAI::MoveInLineOfSight(who);
        ENTRY_BEGIN(CreatureEventBindings, me->GetEntry(), CREATURE_EVENT_ON_MOVE_IN_LOS, return);
        Eluna::Push(L, me);
        Eluna::Push(L, who);
        ENTRY_EXECUTE(0);
        ENDCALL();
    }

    // Called on creature initial spawn, respawn, death, evade (leave combat)
    void On_Reset() // Not an override, custom
    {
        ENTRY_BEGIN(CreatureEventBindings, me->GetEntry(), CREATURE_EVENT_ON_RESET, return);
        Eluna::Push(L, me);
        ENTRY_EXECUTE(0);
        ENDCALL();
    }

    // Called when hit by a spell
    void SpellHit(Unit* caster, SpellInfo const* spell) override
    {
        ScriptedAI::SpellHit(caster, spell);
        ENTRY_BEGIN(CreatureEventBindings, me->GetEntry(), CREATURE_EVENT_ON_HIT_BY_SPELL, return);
        Eluna::Push(L, me);
        Eluna::Push(L, caster);
        Eluna::Push(L, spell->Id); // Pass spell object?
        ENTRY_EXECUTE(0);
        ENDCALL();
    }

    // Called when spell hits a target
    void SpellHitTarget(Unit* target, SpellInfo const* spell) override
    {
        ScriptedAI::SpellHitTarget(target, spell);
        ENTRY_BEGIN(CreatureEventBindings, me->GetEntry(), CREATURE_EVENT_ON_SPELL_HIT_TARGET, return);
        Eluna::Push(L, me);
        Eluna::Push(L, target);
        Eluna::Push(L, spell->Id); // Pass spell object?
        ENTRY_EXECUTE(0);
        ENDCALL();
    }

#ifdef TRINITY

    // Called when the creature is summoned successfully by other creature
    void IsSummonedBy(Unit* summoner) override
    {
        ScriptedAI::IsSummonedBy(summoner);
        sEluna->OnSummoned(me, summoner);
    }

    void SummonedCreatureDies(Creature* summon, Unit* killer) override
    {
        ScriptedAI::SummonedCreatureDies(summon, killer);
        ENTRY_BEGIN(CreatureEventBindings, me->GetEntry(), CREATURE_EVENT_ON_SUMMONED_CREATURE_DIED, return);
        Eluna::Push(L, me);
        Eluna::Push(L, summon);
        Eluna::Push(L, killer);
        ENTRY_EXECUTE(0);
        ENDCALL();
    }

    // Called when owner takes damage
    void OwnerAttackedBy(Unit* attacker) override
    {
        ScriptedAI::OwnerAttackedBy(attacker);
        ENTRY_BEGIN(CreatureEventBindings, me->GetEntry(), CREATURE_EVENT_ON_OWNER_ATTACKED_AT, return);
        Eluna::Push(L, me);
        Eluna::Push(L, attacker);
        ENTRY_EXECUTE(0);
        ENDCALL();
    }

    // Called when owner attacks something
    void OwnerAttacked(Unit* target) override
    {
        ScriptedAI::OwnerAttacked(target);
        ENTRY_BEGIN(CreatureEventBindings, me->GetEntry(), CREATURE_EVENT_ON_OWNER_ATTACKED, return);
        Eluna::Push(L, me);
        Eluna::Push(L, target);
        ENTRY_EXECUTE(0);
        ENDCALL();
    }
#endif

#ifndef TRINITY
#undef me
#endif
};

// gameobject
bool Eluna::OnDummyEffect(Unit* pCaster, uint32 spellId, SpellEffIndex effIndex, GameObject* pTarget)
{
    ENTRY_BEGIN(GameObjectEventBindings, pTarget->GetEntry(), GAMEOBJECT_EVENT_ON_DUMMY_EFFECT, return false);
    Push(L, pCaster);
    Push(L, spellId);
    Push(L, effIndex);
    Push(L, pTarget);
    ENTRY_EXECUTE(0);
    ENDCALL();
    return true;
}

bool Eluna::OnGossipHello(Player* pPlayer, GameObject* pGameObject)
{
    ENTRY_BEGIN(GameObjectGossipBindings, pGameObject->GetEntry(), GOSSIP_EVENT_ON_HELLO, return false);
    pPlayer->PlayerTalkClass->ClearMenus();
    Push(L, pPlayer);
    Push(L, pGameObject);
    ENTRY_EXECUTE(0);
    ENDCALL();
    return true;
}

bool Eluna::OnGossipSelect(Player* pPlayer, GameObject* pGameObject, uint32 sender, uint32 action)
{
    ENTRY_BEGIN(GameObjectGossipBindings, pGameObject->GetEntry(), GOSSIP_EVENT_ON_SELECT, return false);
    pPlayer->PlayerTalkClass->ClearMenus();
    Push(L, pPlayer);
    Push(L, pGameObject);
    Push(L, sender);
    Push(L, action);
    ENTRY_EXECUTE(0);
    ENDCALL();
    return true;
}

bool Eluna::OnGossipSelectCode(Player* pPlayer, GameObject* pGameObject, uint32 sender, uint32 action, const char* code)
{
    ENTRY_BEGIN(GameObjectGossipBindings, pGameObject->GetEntry(), GOSSIP_EVENT_ON_SELECT, return false);
    pPlayer->PlayerTalkClass->ClearMenus();
    Push(L, pPlayer);
    Push(L, pGameObject);
    Push(L, sender);
    Push(L, action);
    Push(L, code);
    ENTRY_EXECUTE(0);
    ENDCALL();
    return true;
}

bool Eluna::OnQuestAccept(Player* pPlayer, GameObject* pGameObject, Quest const* pQuest)
{
    ENTRY_BEGIN(GameObjectEventBindings, pGameObject->GetEntry(), GAMEOBJECT_EVENT_ON_QUEST_ACCEPT, return false);
    Push(L, pPlayer);
    Push(L, pGameObject);
    Push(L, pQuest);
    ENTRY_EXECUTE(0);
    ENDCALL();
    return true;
}

bool Eluna::OnQuestComplete(Player* pPlayer, GameObject* pGameObject, Quest const* pQuest)
{
    ENTRY_BEGIN(GameObjectEventBindings, pGameObject->GetEntry(), GAMEOBJECT_EVENT_ON_QUEST_COMPLETE, return false);
    Push(L, pPlayer);
    Push(L, pGameObject);
    Push(L, pQuest);
    ENTRY_EXECUTE(0);
    ENDCALL();
    return true;
}

void Eluna::UpdateAI(GameObject* pGameObject, uint32 diff)
{
    ENTRY_BEGIN(GameObjectEventBindings, pGameObject->GetEntry(), GAMEOBJECT_EVENT_ON_AIUPDATE, return);
    Push(L, pGameObject);
    Push(L, diff);
    ENTRY_EXECUTE(0);
    ENDCALL();
}

bool Eluna::OnQuestReward(Player* pPlayer, GameObject* pGameObject, Quest const* pQuest)
{
    ENTRY_BEGIN(GameObjectEventBindings, pGameObject->GetEntry(), GAMEOBJECT_EVENT_ON_QUEST_REWARD, return false);
    Push(L, pPlayer);
    Push(L, pGameObject);
    Push(L, pQuest);
    ENTRY_EXECUTE(0);
    ENDCALL();
    return true;
}

uint32 Eluna::GetDialogStatus(Player* pPlayer, GameObject* pGameObject)
{
    ENTRY_BEGIN(GameObjectEventBindings, pGameObject->GetEntry(), GAMEOBJECT_EVENT_ON_DIALOG_STATUS, return 0);
    Push(L, pPlayer);
    Push(L, pGameObject);
    ENTRY_EXECUTE(0);
    ENDCALL();
    return DIALOG_STATUS_SCRIPTED_NO_STATUS; // DIALOG_STATUS_UNDEFINED
}

#ifndef CLASSIC
#ifndef TBC
void Eluna::OnDestroyed(GameObject* pGameObject, Player* pPlayer)
{
    ENTRY_BEGIN(GameObjectEventBindings, pGameObject->GetEntry(), GAMEOBJECT_EVENT_ON_DESTROYED, return);
    Push(L, pGameObject);
    Push(L, pPlayer);
    ENTRY_EXECUTE(0);
    ENDCALL();
}

void Eluna::OnDamaged(GameObject* pGameObject, Player* pPlayer)
{
    ENTRY_BEGIN(GameObjectEventBindings, pGameObject->GetEntry(), GAMEOBJECT_EVENT_ON_DAMAGED, return);
    Push(L, pGameObject);
    Push(L, pPlayer);
    ENTRY_EXECUTE(0);
    ENDCALL();
}
#endif
#endif

void Eluna::OnLootStateChanged(GameObject* pGameObject, uint32 state)
{
    ENTRY_BEGIN(GameObjectEventBindings, pGameObject->GetEntry(), GAMEOBJECT_EVENT_ON_LOOT_STATE_CHANGE, return);
    Push(L, pGameObject);
    Push(L, state);
    ENTRY_EXECUTE(0);
    ENDCALL();
}

void Eluna::OnGameObjectStateChanged(GameObject* pGameObject, uint32 state)
{
    ENTRY_BEGIN(GameObjectEventBindings, pGameObject->GetEntry(), GAMEOBJECT_EVENT_ON_GO_STATE_CHANGED, return);
    Push(L, pGameObject);
    Push(L, state);
    ENTRY_EXECUTE(0);
    ENDCALL();
}

void Eluna::OnSpawn(GameObject* gameobject)
{
    ENTRY_BEGIN(GameObjectEventBindings, gameobject->GetEntry(), GAMEOBJECT_EVENT_ON_SPAWN, return);
    Push(L, gameobject);
    ENTRY_EXECUTE(0);
    ENDCALL();
}

void Eluna::OnAddToWorld(GameObject* gameobject)
{
    ENTRY_BEGIN(GameObjectEventBindings, gameobject->GetEntry(), GAMEOBJECT_EVENT_ON_ADD, return);
    Push(L, gameobject);
    ENTRY_EXECUTE(0);
    ENDCALL();
}

void Eluna::OnRemoveFromWorld(GameObject* gameobject)
{
    ENTRY_BEGIN(GameObjectEventBindings, gameobject->GetEntry(), GAMEOBJECT_EVENT_ON_REMOVE, return);
    Push(L, gameobject);
    ENTRY_EXECUTE(0);
    ENDCALL();
}

CreatureAI* Eluna::GetAI(Creature* creature)
{
    if (!CreatureEventBindings->GetBindMap(creature->GetEntry()))
        return NULL;
    return new ElunaCreatureAI(creature);
}
