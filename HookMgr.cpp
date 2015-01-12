/*
 * Copyright (C) 2010 - 2015 Eluna Lua Engine <http://emudevs.com/>
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
class AggressorAI;
typedef AggressorAI ScriptedAI;
#else
struct ScriptedAI;
#endif

using namespace HookMgr;

/*
 * A hook should be written in one of the following forms:
 *
 * A. If results will be IGNORED:
 *
 *     // Return early if there are no bindings.
 *     if (!WhateverBindings->HasEvents(SOME_EVENT_TYPE))
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
 *     if (!WhateverBindings->HasEvents(SOME_EVENT_TYPE))
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

/*
 * Sets up the stack so that event handlers can be called.
 *
 * Returns the number of functions that were pushed onto the stack.
 *
 * Use the simpler overloads for just EventBind or EntryBind instead of this overload in hooks.
 */
template<typename T>
int Eluna::SetupStack(EventBind<T>* event_bindings, EntryBind<T>* entry_bindings, UniqueBind<T>* guid_bindings, T event_id, uint32 entry, uint64 guid, uint32 instanceId, int number_of_arguments)
{
    // Ensure that if `entry_bindings` is not NULL, a valid entry is supplied.
    ASSERT(!entry_bindings || (entry_bindings && entry > 0));
    ASSERT(number_of_arguments == this->push_counter);
    // Stack: [arguments]

    Push(event_id);
    this->push_counter = 0;
    ++number_of_arguments;
    // Stack: [arguments], event_id

    int arguments_top = lua_gettop(L);
    int first_argument_index = arguments_top - number_of_arguments + 1;
    ASSERT(arguments_top >= number_of_arguments);

    lua_insert(L, first_argument_index);
    // Stack: event_id, [arguments]

    if (event_bindings)
        event_bindings->PushFuncRefs(L, (int)event_id);

    if (entry_bindings)
        entry_bindings->PushFuncRefs(L, (int)event_id, entry);

    if (guid_bindings)
        guid_bindings->PushFuncRefs(L, (int)event_id, guid, instanceId);
    // Stack: event_id, [arguments], [functions]

    int number_of_functions = lua_gettop(L) - arguments_top;
    return number_of_functions;
}

/*
 * Replace one of the arguments pushed before `SetupStack` with a new value.
 */
template<typename T>
void Eluna::ReplaceArgument(T value, uint8 index)
{
    ASSERT(index < lua_gettop(L) && index > 0);
    // Stack: event_id, [arguments], [functions], [results]

    Eluna::Push(L, value);
    // Stack: event_id, [arguments], [functions], [results], value

    lua_replace(L, index + 1);
    // Stack: event_id, [arguments and value], [functions], [results]
}

/*
 * Call a single event handler that was put on the stack with `Setup` and removes it from the stack.
 *
 * The caller is responsible for keeping track of how many times this should be called.
 */
int Eluna::CallOneFunction(int number_of_functions, int number_of_arguments, int number_of_results)
{
    ++number_of_arguments; // Caller doesn't know about `event_id`.
    ASSERT(number_of_functions > 0 && number_of_arguments > 0 && number_of_results >= 0);
    // Stack: event_id, [arguments], [functions]

    int functions_top        = lua_gettop(L);
    int first_function_index = functions_top - number_of_functions + 1;
    int arguments_top        = first_function_index - 1;
    int first_argument_index = arguments_top - number_of_arguments + 1;

    // Copy the arguments from the bottom of the stack to the top.
    for (int argument_index = first_argument_index; argument_index <= arguments_top; ++argument_index)
    {
        lua_pushvalue(L, argument_index);
    }
    // Stack: event_id, [arguments], [functions], event_id, [arguments]

    ExecuteCall(number_of_arguments, number_of_results);
    --functions_top;
    // Stack: event_id, [arguments], [functions - 1], [results]

    return functions_top + 1; // Return the location of the first result (if any exist).
}

/*
 * Cleans up the stack, effectively undoing all Push calls and the Setup call.
 */
void Eluna::CleanUpStack(int number_of_arguments)
{
    // Stack: event_id, [arguments]

    lua_pop(L, number_of_arguments + 1); // Add 1 because the caller doesn't know about `event_id`.
    // Stack: (empty)

    if (event_level == 0)
        InvalidateObjects();
}

/*
 * Call all event handlers registered to the event ID/entry combination and ignore any results.
 */
template<typename T>
void Eluna::CallAllFunctions(EventBind<T>* event_bindings, EntryBind<T>* entry_bindings, UniqueBind<T>* guid_bindings, T event_id, uint32 entry, uint64 guid, uint32 instanceId)
{
    int number_of_arguments = this->push_counter;
    // Stack: [arguments]

    int number_of_functions = SetupStack(event_bindings, entry_bindings, guid_bindings, event_id, entry, guid, instanceId, number_of_arguments);
    // Stack: event_id, [arguments], [functions]

    while (number_of_functions > 0)
    {
        CallOneFunction(number_of_functions, number_of_arguments, 0);
        --number_of_functions;
        // Stack: event_id, [arguments], [functions - 1]
    }
    // Stack: event_id, [arguments]

    CleanUpStack(number_of_arguments);
    // Stack: (empty)
}

/*
 * Call all event handlers registered to the event ID/entry combination,
 *   and returns `default_value` if ALL event handlers returned `default_value`,
 *   otherwise returns the opposite of `default_value`.
 */
template<typename T>
bool Eluna::CallAllFunctionsBool(EventBind<T>* event_bindings, EntryBind<T>* entry_bindings, UniqueBind<T>* guid_bindings, T event_id, uint32 entry, uint64 guid, uint32 instanceId, bool default_value)
{
    bool result = default_value;
    // Note: number_of_arguments here does not count in eventID, which is pushed in SetupStack
    int number_of_arguments = this->push_counter;
    // Stack: [arguments]

    int number_of_functions = SetupStack(event_bindings, entry_bindings, guid_bindings, event_id, entry, guid, instanceId, number_of_arguments);
    // Stack: event_id, [arguments], [functions]

    while (number_of_functions > 0)
    {
        int r = CallOneFunction(number_of_functions, number_of_arguments, 1);
        --number_of_functions;
        // Stack: event_id, [arguments], [functions - 1], result

        if (lua_isboolean(L, r) && (lua_toboolean(L, r) == 1) != default_value)
            result = !default_value;

        lua_pop(L, 1);
        // Stack: event_id, [arguments], [functions - 1]
    }
    // Stack: event_id, [arguments]

    CleanUpStack(number_of_arguments);
    // Stack: (empty)
    return result;
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
void Eluna::OnAdd(AuctionHouseObject* ah)
{
    if (!ServerEventBindings->HasEvents(AUCTION_EVENT_ON_ADD))
        return;

    LOCK_ELUNA;
    Push(ah);
    CallAllFunctions(ServerEventBindings, AUCTION_EVENT_ON_ADD);
}

void Eluna::OnRemove(AuctionHouseObject* ah)
{
    if (!ServerEventBindings->HasEvents(AUCTION_EVENT_ON_REMOVE))
        return;

    LOCK_ELUNA;
    Push(ah);
    CallAllFunctions(ServerEventBindings, AUCTION_EVENT_ON_REMOVE);
}

void Eluna::OnSuccessful(AuctionHouseObject* ah)
{
    if (!ServerEventBindings->HasEvents(AUCTION_EVENT_ON_SUCCESSFUL))
        return;

    LOCK_ELUNA;
    Push(ah);
    CallAllFunctions(ServerEventBindings, AUCTION_EVENT_ON_SUCCESSFUL);
}

void Eluna::OnExpire(AuctionHouseObject* ah)
{
    if (!ServerEventBindings->HasEvents(AUCTION_EVENT_ON_EXPIRE))
        return;

    LOCK_ELUNA;
    Push(ah);
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
    LOCK_ELUNA;

    if (reload)
    {
        ReloadEluna();
        return;
    }

    eventMgr->globalProcessor->Update(diff);

    if (!ServerEventBindings->HasEvents(WORLD_EVENT_ON_UPDATE))
        return;

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

void Eluna::HandleGossipSelectOption(Player* pPlayer, Item* item, uint32 sender, uint32 action, const std::string& code)
{
    if (!ItemGossipBindings->HasEvents(GOSSIP_EVENT_ON_SELECT, item->GetEntry()))
        return;

    LOCK_ELUNA;
    pPlayer->PlayerTalkClass->ClearMenus();

    Push(pPlayer);
    Push(item);
    Push(sender);
    Push(action);
    if (code.empty())
        Push();
    else
        Push(code);

    CallAllFunctions(ItemGossipBindings, GOSSIP_EVENT_ON_SELECT, item->GetEntry());
}

void Eluna::HandleGossipSelectOption(Player* pPlayer, uint32 menuId, uint32 sender, uint32 action, const std::string& code)
{
    if (!playerGossipBindings->HasEvents(GOSSIP_EVENT_ON_SELECT, menuId))
        return;

    LOCK_ELUNA;
    pPlayer->PlayerTalkClass->ClearMenus();

    Push(pPlayer); // receiver
    Push(pPlayer); // sender, just not to mess up the amount of args.
    Push(sender);
    Push(action);
    if (code.empty())
        Push();
    else
        Push(code);

    CallAllFunctions(playerGossipBindings, GOSSIP_EVENT_ON_SELECT, menuId);
}

// item
bool Eluna::OnDummyEffect(Unit* pCaster, uint32 spellId, SpellEffIndex effIndex, Item* pTarget)
{
    if (!ItemEventBindings->HasEvents(ITEM_EVENT_ON_DUMMY_EFFECT, pTarget->GetEntry()))
        return false;

    LOCK_ELUNA;
    Push(pCaster);
    Push(spellId);
    Push(effIndex);
    Push(pTarget);
    return CallAllFunctionsBool(ItemEventBindings, ITEM_EVENT_ON_DUMMY_EFFECT, pTarget->GetEntry());
}

bool Eluna::OnQuestAccept(Player* pPlayer, Item* pItem, Quest const* pQuest)
{
    if (!ItemEventBindings->HasEvents(ITEM_EVENT_ON_QUEST_ACCEPT, pItem->GetEntry()))
        return false;

    LOCK_ELUNA;
    Push(pPlayer);
    Push(pItem);
    Push(pQuest);
    return CallAllFunctionsBool(ItemEventBindings, ITEM_EVENT_ON_QUEST_ACCEPT, pItem->GetEntry());
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
    if (!ItemEventBindings->HasEvents(ITEM_EVENT_ON_USE, pItem->GetEntry()))
        return true;

    LOCK_ELUNA;
    Push(pPlayer);
    Push(pItem);
#ifndef TRINITY
    if (GameObject* target = targets.getGOTarget())
        Push(target);
    else if (Item* target = targets.getItemTarget())
        Push(target);
    else if (Corpse* target = pPlayer->GetMap()->GetCorpse(targets.getCorpseTargetGuid()))
        Push(target);
    else if (Unit* target = targets.getUnitTarget())
        Push(target);
    else
        Push();
#else
    if (GameObject* target = targets.GetGOTarget())
        Push(target);
    else if (Item* target = targets.GetItemTarget())
        Push(target);
    else if (Corpse* target = targets.GetCorpseTarget())
        Push(target);
    else if (Unit* target = targets.GetUnitTarget())
        Push(target);
    else if (WorldObject* target = targets.GetObjectTarget())
        Push(target);
    else
        Push();
#endif

    return CallAllFunctionsBool(ItemEventBindings, ITEM_EVENT_ON_USE, pItem->GetEntry(), true);
}

bool Eluna::OnItemGossip(Player* pPlayer, Item* pItem, SpellCastTargets const& /*targets*/)
{
    if (!ItemGossipBindings->HasEvents(GOSSIP_EVENT_ON_HELLO, pItem->GetEntry()))
        return true;

    LOCK_ELUNA;
    pPlayer->PlayerTalkClass->ClearMenus();
    Push(pPlayer);
    Push(pItem);
    return CallAllFunctionsBool(ItemGossipBindings, GOSSIP_EVENT_ON_HELLO, pItem->GetEntry(), true);
}

bool Eluna::OnExpire(Player* pPlayer, ItemTemplate const* pProto)
{
    if (!ItemEventBindings->HasEvents(ITEM_EVENT_ON_EXPIRE, pProto->ItemId))
        return false;

    LOCK_ELUNA;
    Push(pPlayer);
    Push(pProto->ItemId);
    return CallAllFunctionsBool(ItemEventBindings, ITEM_EVENT_ON_EXPIRE, pProto->ItemId);
}

bool Eluna::OnRemove(Player* pPlayer, Item* item)
{
    if (!ItemEventBindings->HasEvents(ITEM_EVENT_ON_REMOVE, item->GetEntry()))
        return false;

    LOCK_ELUNA;
    Push(pPlayer);
    Push(item);
    return CallAllFunctionsBool(ItemEventBindings, ITEM_EVENT_ON_REMOVE, item->GetEntry());
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

    if (!PlayerEventBindings->HasEvents(PLAYER_EVENT_ON_COMMAND))
        return true;

    LOCK_ELUNA;
    Push(player);
    Push(fullcmd);
    return CallAllFunctionsBool(PlayerEventBindings, PLAYER_EVENT_ON_COMMAND, true);
}

void Eluna::OnLootItem(Player* pPlayer, Item* pItem, uint32 count, uint64 guid)
{
    if (!PlayerEventBindings->HasEvents(PLAYER_EVENT_ON_LOOT_ITEM))
        return;

    LOCK_ELUNA;
    Push(pPlayer);
    Push(pItem);
    Push(count);
    Push(guid);
    CallAllFunctions(PlayerEventBindings, PLAYER_EVENT_ON_LOOT_ITEM);
}

void Eluna::OnLootMoney(Player* pPlayer, uint32 amount)
{
    if (!PlayerEventBindings->HasEvents(PLAYER_EVENT_ON_LOOT_MONEY))
        return;

    LOCK_ELUNA;
    Push(pPlayer);
    Push(amount);
    CallAllFunctions(PlayerEventBindings, PLAYER_EVENT_ON_LOOT_MONEY);
}

void Eluna::OnFirstLogin(Player* pPlayer)
{
    if (!PlayerEventBindings->HasEvents(PLAYER_EVENT_ON_FIRST_LOGIN))
        return;

    LOCK_ELUNA;
    Push(pPlayer);
    CallAllFunctions(PlayerEventBindings, PLAYER_EVENT_ON_FIRST_LOGIN);
}

void Eluna::OnRepop(Player* pPlayer)
{
    if (!PlayerEventBindings->HasEvents(PLAYER_EVENT_ON_REPOP))
        return;

    LOCK_ELUNA;
    Push(pPlayer);
    CallAllFunctions(PlayerEventBindings, PLAYER_EVENT_ON_REPOP);
}

void Eluna::OnResurrect(Player* pPlayer)
{
    if (!PlayerEventBindings->HasEvents(PLAYER_EVENT_ON_RESURRECT))
        return;

    LOCK_ELUNA;
    Push(pPlayer);
    CallAllFunctions(PlayerEventBindings, PLAYER_EVENT_ON_RESURRECT);
}

void Eluna::OnQuestAbandon(Player* pPlayer, uint32 questId)
{
    if (!PlayerEventBindings->HasEvents(PLAYER_EVENT_ON_QUEST_ABANDON))
        return;

    LOCK_ELUNA;
    Push(pPlayer);
    Push(questId);
    CallAllFunctions(PlayerEventBindings, PLAYER_EVENT_ON_QUEST_ABANDON);
}

void Eluna::OnEquip(Player* pPlayer, Item* pItem, uint8 bag, uint8 slot)
{
    if (!PlayerEventBindings->HasEvents(PLAYER_EVENT_ON_EQUIP))
        return;

    LOCK_ELUNA;
    Push(pPlayer);
    Push(pItem);
    Push(bag);
    Push(slot);
    CallAllFunctions(PlayerEventBindings, PLAYER_EVENT_ON_EQUIP);
}

InventoryResult Eluna::OnCanUseItem(const Player* pPlayer, uint32 itemEntry)
{
    if (!PlayerEventBindings->HasEvents(PLAYER_EVENT_ON_CAN_USE_ITEM))
        return EQUIP_ERR_OK;

    LOCK_ELUNA;
    InventoryResult result = EQUIP_ERR_OK;
    Push(pPlayer);
    Push(itemEntry);
    int n = SetupStack(PlayerEventBindings, PLAYER_EVENT_ON_CAN_USE_ITEM, 2);

    while (n > 0)
    {
        int r = CallOneFunction(n--, 2, 1);

        if (lua_isnumber(L, r))
            result = (InventoryResult)CHECKVAL<uint32>(L, r);

        lua_pop(L, 1);
    }

    CleanUpStack(2);
    return result;
}
void Eluna::OnPlayerEnterCombat(Player* pPlayer, Unit* pEnemy)
{
    if (!PlayerEventBindings->HasEvents(PLAYER_EVENT_ON_ENTER_COMBAT))
        return;

    LOCK_ELUNA;
    Push(pPlayer);
    Push(pEnemy);
    CallAllFunctions(PlayerEventBindings, PLAYER_EVENT_ON_ENTER_COMBAT);
}

void Eluna::OnPlayerLeaveCombat(Player* pPlayer)
{
    if (!PlayerEventBindings->HasEvents(PLAYER_EVENT_ON_LEAVE_COMBAT))
        return;

    LOCK_ELUNA;
    Push(pPlayer);
    CallAllFunctions(PlayerEventBindings, PLAYER_EVENT_ON_LEAVE_COMBAT);
}

void Eluna::OnPVPKill(Player* pKiller, Player* pKilled)
{
    if (!PlayerEventBindings->HasEvents(PLAYER_EVENT_ON_KILL_PLAYER))
        return;

    LOCK_ELUNA;
    Push(pKiller);
    Push(pKilled);
    CallAllFunctions(PlayerEventBindings, PLAYER_EVENT_ON_KILL_PLAYER);
}

void Eluna::OnCreatureKill(Player* pKiller, Creature* pKilled)
{
    if (!PlayerEventBindings->HasEvents(PLAYER_EVENT_ON_KILL_CREATURE))
        return;

    LOCK_ELUNA;
    Push(pKiller);
    Push(pKilled);
    CallAllFunctions(PlayerEventBindings, PLAYER_EVENT_ON_KILL_CREATURE);
}

void Eluna::OnPlayerKilledByCreature(Creature* pKiller, Player* pKilled)
{
    if (!PlayerEventBindings->HasEvents(PLAYER_EVENT_ON_KILLED_BY_CREATURE))
        return;

    LOCK_ELUNA;
    Push(pKiller);
    Push(pKilled);
    CallAllFunctions(PlayerEventBindings, PLAYER_EVENT_ON_KILLED_BY_CREATURE);
}

void Eluna::OnLevelChanged(Player* pPlayer, uint8 oldLevel)
{
    if (!PlayerEventBindings->HasEvents(PLAYER_EVENT_ON_LEVEL_CHANGE))
        return;

    LOCK_ELUNA;
    Push(pPlayer);
    Push(oldLevel);
    CallAllFunctions(PlayerEventBindings, PLAYER_EVENT_ON_LEVEL_CHANGE);
}

void Eluna::OnFreeTalentPointsChanged(Player* pPlayer, uint32 newPoints)
{
    if (!PlayerEventBindings->HasEvents(PLAYER_EVENT_ON_TALENTS_CHANGE))
        return;

    LOCK_ELUNA;
    Push(pPlayer);
    Push(newPoints);
    CallAllFunctions(PlayerEventBindings, PLAYER_EVENT_ON_TALENTS_CHANGE);
}

void Eluna::OnTalentsReset(Player* pPlayer, bool noCost)
{
    if (!PlayerEventBindings->HasEvents(PLAYER_EVENT_ON_TALENTS_RESET))
        return;

    LOCK_ELUNA;
    Push(pPlayer);
    Push(noCost);
    CallAllFunctions(PlayerEventBindings, PLAYER_EVENT_ON_TALENTS_RESET);
}

void Eluna::OnMoneyChanged(Player* pPlayer, int32& amount)
{
    if (!PlayerEventBindings->HasEvents(PLAYER_EVENT_ON_MONEY_CHANGE))
        return;

    LOCK_ELUNA;
    Push(pPlayer);
    Push(amount);
    int amountIndex = lua_gettop(L);
    int n = SetupStack(PlayerEventBindings, PLAYER_EVENT_ON_MONEY_CHANGE, 2);

    while (n > 0)
    {
        int r = CallOneFunction(n--, 2, 1);

        if (lua_isnumber(L, r))
        {
            amount = CHECKVAL<int32>(L, r);
            // Update the stack for subsequent calls.
            ReplaceArgument(amount, amountIndex);
        }

        lua_pop(L, 1);
    }

    CleanUpStack(2);
}

void Eluna::OnGiveXP(Player* pPlayer, uint32& amount, Unit* pVictim)
{
    if (!PlayerEventBindings->HasEvents(PLAYER_EVENT_ON_GIVE_XP))
        return;

    LOCK_ELUNA;
    Push(pPlayer);
    Push(amount);
    Push(pVictim);
    int amountIndex = lua_gettop(L) - 1;
    int n = SetupStack(PlayerEventBindings, PLAYER_EVENT_ON_GIVE_XP, 3);

    while (n > 0)
    {
        int r = CallOneFunction(n--, 3, 1);

        if (lua_isnumber(L, r))
        {
            amount = CHECKVAL<uint32>(L, r);
            // Update the stack for subsequent calls.
            ReplaceArgument(amount, amountIndex);
        }

        lua_pop(L, 1);
    }

    CleanUpStack(3);
}

void Eluna::OnReputationChange(Player* pPlayer, uint32 factionID, int32& standing, bool incremental)
{
    if (!PlayerEventBindings->HasEvents(PLAYER_EVENT_ON_REPUTATION_CHANGE))
        return;

    LOCK_ELUNA;
    Push(pPlayer);
    Push(factionID);
    Push(standing);
    Push(incremental);
    int standingIndex = lua_gettop(L) - 1;
    int n = SetupStack(PlayerEventBindings, PLAYER_EVENT_ON_REPUTATION_CHANGE, 4);

    while (n > 0)
    {
        int r = CallOneFunction(n--, 4, 1);

        if (lua_isnumber(L, r))
        {
            standing = CHECKVAL<int32>(L, r);
            // Update the stack for subsequent calls.
            ReplaceArgument(standing, standingIndex);
        }

        lua_pop(L, 1);
    }

    CleanUpStack(4);
}

void Eluna::OnDuelRequest(Player* pTarget, Player* pChallenger)
{
    if (!PlayerEventBindings->HasEvents(PLAYER_EVENT_ON_DUEL_REQUEST))
        return;

    LOCK_ELUNA;
    Push(pTarget);
    Push(pChallenger);
    CallAllFunctions(PlayerEventBindings, PLAYER_EVENT_ON_DUEL_REQUEST);
}

void Eluna::OnDuelStart(Player* pStarter, Player* pChallenger)
{
    if (!PlayerEventBindings->HasEvents(PLAYER_EVENT_ON_DUEL_START))
        return;

    LOCK_ELUNA;
    Push(pStarter);
    Push(pChallenger);
    CallAllFunctions(PlayerEventBindings, PLAYER_EVENT_ON_DUEL_START);
}

void Eluna::OnDuelEnd(Player* pWinner, Player* pLoser, DuelCompleteType type)
{
    if (!PlayerEventBindings->HasEvents(PLAYER_EVENT_ON_DUEL_END))
        return;

    LOCK_ELUNA;
    Push(pWinner);
    Push(pLoser);
    Push(type);
    CallAllFunctions(PlayerEventBindings, PLAYER_EVENT_ON_DUEL_END);
}

void Eluna::OnEmote(Player* pPlayer, uint32 emote)
{
    if (!PlayerEventBindings->HasEvents(PLAYER_EVENT_ON_EMOTE))
        return;

    LOCK_ELUNA;
    Push(pPlayer);
    Push(emote);
    CallAllFunctions(PlayerEventBindings, PLAYER_EVENT_ON_EMOTE);
}

void Eluna::OnTextEmote(Player* pPlayer, uint32 textEmote, uint32 emoteNum, uint64 guid)
{
    if (!PlayerEventBindings->HasEvents(PLAYER_EVENT_ON_TEXT_EMOTE))
        return;

    LOCK_ELUNA;
    Push(pPlayer);
    Push(textEmote);
    Push(emoteNum);
    Push(guid);
    CallAllFunctions(PlayerEventBindings, PLAYER_EVENT_ON_TEXT_EMOTE);
}

void Eluna::OnSpellCast(Player* pPlayer, Spell* pSpell, bool skipCheck)
{
    if (!PlayerEventBindings->HasEvents(PLAYER_EVENT_ON_SPELL_CAST))
        return;

    LOCK_ELUNA;
    Push(pPlayer);
    Push(pSpell);
    Push(skipCheck);
    CallAllFunctions(PlayerEventBindings, PLAYER_EVENT_ON_SPELL_CAST);
}

void Eluna::OnLogin(Player* pPlayer)
{
    if (!PlayerEventBindings->HasEvents(PLAYER_EVENT_ON_LOGIN))
        return;

    LOCK_ELUNA;
    Push(pPlayer);
    CallAllFunctions(PlayerEventBindings, PLAYER_EVENT_ON_LOGIN);
}

void Eluna::OnLogout(Player* pPlayer)
{
    if (!PlayerEventBindings->HasEvents(PLAYER_EVENT_ON_LOGOUT))
        return;

    LOCK_ELUNA;
    Push(pPlayer);
    CallAllFunctions(PlayerEventBindings, PLAYER_EVENT_ON_LOGOUT);
}

void Eluna::OnCreate(Player* pPlayer)
{
    if (!PlayerEventBindings->HasEvents(PLAYER_EVENT_ON_CHARACTER_CREATE))
        return;

    LOCK_ELUNA;
    Push(pPlayer);
    CallAllFunctions(PlayerEventBindings, PLAYER_EVENT_ON_CHARACTER_CREATE);
}

void Eluna::OnDelete(uint32 guidlow)
{
    if (!PlayerEventBindings->HasEvents(PLAYER_EVENT_ON_CHARACTER_DELETE))
        return;

    LOCK_ELUNA;
    Push(guidlow);
    CallAllFunctions(PlayerEventBindings, PLAYER_EVENT_ON_CHARACTER_DELETE);
}

void Eluna::OnSave(Player* pPlayer)
{
    if (!PlayerEventBindings->HasEvents(PLAYER_EVENT_ON_SAVE))
        return;

    LOCK_ELUNA;
    Push(pPlayer);
    CallAllFunctions(PlayerEventBindings, PLAYER_EVENT_ON_SAVE);
}

void Eluna::OnBindToInstance(Player* pPlayer, Difficulty difficulty, uint32 mapid, bool permanent)
{
    if (!PlayerEventBindings->HasEvents(PLAYER_EVENT_ON_BIND_TO_INSTANCE))
        return;

    LOCK_ELUNA;
    Push(pPlayer);
    Push(difficulty);
    Push(mapid);
    Push(permanent);
    CallAllFunctions(PlayerEventBindings, PLAYER_EVENT_ON_BIND_TO_INSTANCE);
}

void Eluna::OnUpdateZone(Player* pPlayer, uint32 newZone, uint32 newArea)
{
    if (!PlayerEventBindings->HasEvents(PLAYER_EVENT_ON_UPDATE_ZONE))
        return;

    LOCK_ELUNA;
    Push(pPlayer);
    Push(newZone);
    Push(newArea);
    CallAllFunctions(PlayerEventBindings, PLAYER_EVENT_ON_UPDATE_ZONE);
}

void Eluna::OnMapChanged(Player* player)
{
    if (!PlayerEventBindings->HasEvents(PLAYER_EVENT_ON_MAP_CHANGE))
        return;

    LOCK_ELUNA;
    Push(player);
    CallAllFunctions(PlayerEventBindings, PLAYER_EVENT_ON_MAP_CHANGE);
}

// AddOns
bool Eluna::OnAddonMessage(Player* sender, uint32 type, std::string& msg, Player* receiver, Guild* guild, Group* group, Channel* channel)
{
    if (!ServerEventBindings->HasEvents(ADDON_EVENT_ON_MESSAGE))
        return true;

    LOCK_ELUNA;
    Push(sender);
    Push(type);
    const char* c_msg = msg.c_str();
    Push(strtok((char*)c_msg, "\t")); // prefix
    Push(strtok(NULL, "")); // msg
    if (receiver)
        Push(receiver);
    else if (guild)
        Push(guild);
    else if (group)
        Push(group);
    else if (channel)
        Push(channel->GetChannelId());
    else
        Push();

    return CallAllFunctionsBool(ServerEventBindings, ADDON_EVENT_ON_MESSAGE, true);
}

bool Eluna::OnChat(Player* pPlayer, uint32 type, uint32 lang, std::string& msg)
{
    if (lang == LANG_ADDON)
        return OnAddonMessage(pPlayer, type, msg, NULL, NULL, NULL, NULL);

    if (!PlayerEventBindings->HasEvents(PLAYER_EVENT_ON_CHAT))
        return true;

    LOCK_ELUNA;
    bool result = true;
    Push(pPlayer);
    Push(msg);
    Push(type);
    Push(lang);
    int n = SetupStack(PlayerEventBindings, PLAYER_EVENT_ON_CHAT, 4);

    while (n > 0)
    {
        int r = CallOneFunction(n--, 4, 2);

        if (lua_isboolean(L, r + 0) && !lua_toboolean(L, r + 0))
            result = false;

        if (lua_isstring(L, r + 1))
            msg = std::string(lua_tostring(L, r + 1));

        lua_pop(L, 2);
    }

    CleanUpStack(4);
    return result;
}

bool Eluna::OnChat(Player* pPlayer, uint32 type, uint32 lang, std::string& msg, Group* pGroup)
{
    if (lang == LANG_ADDON)
        return OnAddonMessage(pPlayer, type, msg, NULL, NULL, pGroup, NULL);

    if (!PlayerEventBindings->HasEvents(PLAYER_EVENT_ON_GROUP_CHAT))
        return true;

    LOCK_ELUNA;
    bool result = true;
    Push(pPlayer);
    Push(msg);
    Push(type);
    Push(lang);
    Push(pGroup);
    int n = SetupStack(PlayerEventBindings, PLAYER_EVENT_ON_GROUP_CHAT, 5);

    while (n > 0)
    {
        int r = CallOneFunction(n--, 5, 2);

        if (lua_isboolean(L, r + 0) && !lua_toboolean(L, r + 0))
            result = false;

        if (lua_isstring(L, r + 1))
            msg = std::string(lua_tostring(L, r + 1));

        lua_pop(L, 2);
    }

    CleanUpStack(5);
    return result;
}

bool Eluna::OnChat(Player* pPlayer, uint32 type, uint32 lang, std::string& msg, Guild* pGuild)
{
    if (lang == LANG_ADDON)
        return OnAddonMessage(pPlayer, type, msg, NULL, pGuild, NULL, NULL);

    if (!PlayerEventBindings->HasEvents(PLAYER_EVENT_ON_GUILD_CHAT))
        return true;

    LOCK_ELUNA;
    bool result = true;
    Push(pPlayer);
    Push(msg);
    Push(type);
    Push(lang);
    Push(pGuild);
    int n = SetupStack(PlayerEventBindings, PLAYER_EVENT_ON_GUILD_CHAT, 5);

    while (n > 0)
    {
        int r = CallOneFunction(n--, 5, 2);

        if (lua_isboolean(L, r + 0) && !lua_toboolean(L, r + 0))
            result = false;

        if (lua_isstring(L, r + 1))
            msg = std::string(lua_tostring(L, r + 1));

        lua_pop(L, 2);
    }

    CleanUpStack(5);
    return result;
}

bool Eluna::OnChat(Player* pPlayer, uint32 type, uint32 lang, std::string& msg, Channel* pChannel)
{
    if (lang == LANG_ADDON)
        return OnAddonMessage(pPlayer, type, msg, NULL, NULL, NULL, pChannel);

    if (!PlayerEventBindings->HasEvents(PLAYER_EVENT_ON_CHANNEL_CHAT))
        return true;

    LOCK_ELUNA;
    bool result = true;
    Push(pPlayer);
    Push(msg);
    Push(type);
    Push(lang);
    Push(pChannel->GetChannelId());
    int n = SetupStack(PlayerEventBindings, PLAYER_EVENT_ON_CHANNEL_CHAT, 5);

    while (n > 0)
    {
        int r = CallOneFunction(n--, 5, 2);

        if (lua_isboolean(L, r + 0) && !lua_toboolean(L, r + 0))
            result = false;

        if (lua_isstring(L, r + 1))
            msg = std::string(lua_tostring(L, r + 1));

        lua_pop(L, 2);
    }

    CleanUpStack(5);
    return result;
}

bool Eluna::OnChat(Player* pPlayer, uint32 type, uint32 lang, std::string& msg, Player* pReceiver)
{
    if (lang == LANG_ADDON)
        return OnAddonMessage(pPlayer, type, msg, pReceiver, NULL, NULL, NULL);

    if (!PlayerEventBindings->HasEvents(PLAYER_EVENT_ON_WHISPER))
        return true;

    LOCK_ELUNA;
    bool result = true;
    Push(pPlayer);
    Push(msg);
    Push(type);
    Push(lang);
    Push(pReceiver);
    int n = SetupStack(PlayerEventBindings, PLAYER_EVENT_ON_WHISPER, 5);

    while (n > 0)
    {
        int r = CallOneFunction(n--, 5, 2);

        if (lua_isboolean(L, r + 0) && !lua_toboolean(L, r + 0))
            result = false;

        if (lua_isstring(L, r + 1))
            msg = std::string(lua_tostring(L, r + 1));

        lua_pop(L, 2);
    }

    CleanUpStack(5);
    return result;
}

#ifndef CLASSIC
#ifndef TBC
// Vehicle
void Eluna::OnInstall(Vehicle* vehicle)
{
    if (!VehicleEventBindings->HasEvents(VEHICLE_EVENT_ON_INSTALL))
        return;

    LOCK_ELUNA;
    Push(vehicle);
    CallAllFunctions(VehicleEventBindings, VEHICLE_EVENT_ON_INSTALL);
}

void Eluna::OnUninstall(Vehicle* vehicle)
{
    if (!VehicleEventBindings->HasEvents(VEHICLE_EVENT_ON_UNINSTALL))
        return;

    LOCK_ELUNA;
    Push(vehicle);
    CallAllFunctions(VehicleEventBindings, VEHICLE_EVENT_ON_UNINSTALL);
}

void Eluna::OnInstallAccessory(Vehicle* vehicle, Creature* accessory)
{
    if (!VehicleEventBindings->HasEvents(VEHICLE_EVENT_ON_INSTALL_ACCESSORY))
        return;

    LOCK_ELUNA;
    Push(vehicle);
    Push(accessory);
    CallAllFunctions(VehicleEventBindings, VEHICLE_EVENT_ON_INSTALL_ACCESSORY);
}

void Eluna::OnAddPassenger(Vehicle* vehicle, Unit* passenger, int8 seatId)
{
    if (!VehicleEventBindings->HasEvents(VEHICLE_EVENT_ON_ADD_PASSENGER))
        return;

    LOCK_ELUNA;
    Push(vehicle);
    Push(passenger);
    Push(seatId);
    CallAllFunctions(VehicleEventBindings, VEHICLE_EVENT_ON_ADD_PASSENGER);
}

void Eluna::OnRemovePassenger(Vehicle* vehicle, Unit* passenger)
{
    if (!VehicleEventBindings->HasEvents(VEHICLE_EVENT_ON_REMOVE_PASSENGER))
        return;

    LOCK_ELUNA;
    Push(vehicle);
    Push(passenger);
    CallAllFunctions(VehicleEventBindings, VEHICLE_EVENT_ON_REMOVE_PASSENGER);
}
#endif
#endif

void Eluna::OnAddMember(Guild* guild, Player* player, uint32 plRank)
{
    if (!GuildEventBindings->HasEvents(GUILD_EVENT_ON_ADD_MEMBER))
        return;

    LOCK_ELUNA;
    Push(guild);
    Push(player);
    Push(plRank);
    CallAllFunctions(GuildEventBindings, GUILD_EVENT_ON_ADD_MEMBER);
}

void Eluna::OnRemoveMember(Guild* guild, Player* player, bool isDisbanding)
{
    if (!GuildEventBindings->HasEvents(GUILD_EVENT_ON_REMOVE_MEMBER))
        return;

    LOCK_ELUNA;
    Push(guild);
    Push(player);
    Push(isDisbanding);
    CallAllFunctions(GuildEventBindings, GUILD_EVENT_ON_REMOVE_MEMBER);
}

void Eluna::OnMOTDChanged(Guild* guild, const std::string& newMotd)
{
    if (!GuildEventBindings->HasEvents(GUILD_EVENT_ON_MOTD_CHANGE))
        return;

    LOCK_ELUNA;
    Push(guild);
    Push(newMotd);
    CallAllFunctions(GuildEventBindings, GUILD_EVENT_ON_MOTD_CHANGE);
}

void Eluna::OnInfoChanged(Guild* guild, const std::string& newInfo)
{
    if (!GuildEventBindings->HasEvents(GUILD_EVENT_ON_INFO_CHANGE))
        return;

    LOCK_ELUNA;
    Push(guild);
    Push(newInfo);
    CallAllFunctions(GuildEventBindings, GUILD_EVENT_ON_INFO_CHANGE);
}

void Eluna::OnCreate(Guild* guild, Player* leader, const std::string& name)
{
    if (!GuildEventBindings->HasEvents(GUILD_EVENT_ON_CREATE))
        return;

    LOCK_ELUNA;
    Push(guild);
    Push(leader);
    Push(name);
    CallAllFunctions(GuildEventBindings, GUILD_EVENT_ON_CREATE);
}

void Eluna::OnDisband(Guild* guild)
{
    if (!GuildEventBindings->HasEvents(GUILD_EVENT_ON_DISBAND))
        return;

    LOCK_ELUNA;
    Push(guild);
    CallAllFunctions(GuildEventBindings, GUILD_EVENT_ON_DISBAND);
}

void Eluna::OnMemberWitdrawMoney(Guild* guild, Player* player, uint32& amount, bool isRepair) // isRepair not a part of Mangos, implement?
{
    if (!GuildEventBindings->HasEvents(GUILD_EVENT_ON_MONEY_WITHDRAW))
        return;

    LOCK_ELUNA;
    Push(guild);
    Push(player);
    Push(amount);
    Push(isRepair); // isRepair not a part of Mangos, implement?
    int amountIndex = lua_gettop(L) - 1;
    int n = SetupStack(GuildEventBindings, GUILD_EVENT_ON_MONEY_WITHDRAW, 4);

    while (n > 0)
    {
        int r = CallOneFunction(n--, 4, 1);

        if (lua_isnumber(L, r))
        {
            amount = CHECKVAL<uint32>(L, r);
            // Update the stack for subsequent calls.
            ReplaceArgument(amount, amountIndex);
        }

        lua_pop(L, 1);
    }

    CleanUpStack(4);
}

void Eluna::OnMemberDepositMoney(Guild* guild, Player* player, uint32& amount)
{
    if (!GuildEventBindings->HasEvents(GUILD_EVENT_ON_MONEY_DEPOSIT))
        return;

    LOCK_ELUNA;
    Push(guild);
    Push(player);
    Push(amount);
    int amountIndex = lua_gettop(L);
    int n = SetupStack(GuildEventBindings, GUILD_EVENT_ON_MONEY_DEPOSIT, 3);

    while (n > 0)
    {
        int r = CallOneFunction(n--, 3, 1);

        if (lua_isnumber(L, r))
        {
            amount = CHECKVAL<uint32>(L, r);
            // Update the stack for subsequent calls.
            ReplaceArgument(amount, amountIndex);
        }

        lua_pop(L, 1);
    }

    CleanUpStack(3);
}

void Eluna::OnItemMove(Guild* guild, Player* player, Item* pItem, bool isSrcBank, uint8 srcContainer, uint8 srcSlotId,
    bool isDestBank, uint8 destContainer, uint8 destSlotId)
{
    if (!GuildEventBindings->HasEvents(GUILD_EVENT_ON_ITEM_MOVE))
        return;

    LOCK_ELUNA;
    Push(guild);
    Push(player);
    Push(pItem);
    Push(isSrcBank);
    Push(srcContainer);
    Push(srcSlotId);
    Push(isDestBank);
    Push(destContainer);
    Push(destSlotId);
    CallAllFunctions(GuildEventBindings, GUILD_EVENT_ON_ITEM_MOVE);
}

void Eluna::OnEvent(Guild* guild, uint8 eventType, uint32 playerGuid1, uint32 playerGuid2, uint8 newRank)
{
    if (!GuildEventBindings->HasEvents(GUILD_EVENT_ON_EVENT))
        return;

    LOCK_ELUNA;
    Push(guild);
    Push(eventType);
    Push(playerGuid1);
    Push(playerGuid2);
    Push(newRank);
    CallAllFunctions(GuildEventBindings, GUILD_EVENT_ON_EVENT);
}

void Eluna::OnBankEvent(Guild* guild, uint8 eventType, uint8 tabId, uint32 playerGuid, uint32 itemOrMoney, uint16 itemStackCount, uint8 destTabId)
{
    if (!GuildEventBindings->HasEvents(GUILD_EVENT_ON_BANK_EVENT))
        return;

    LOCK_ELUNA;
    Push(guild);
    Push(eventType);
    Push(tabId);
    Push(playerGuid);
    Push(itemOrMoney);
    Push(itemStackCount);
    Push(destTabId);
    CallAllFunctions(GuildEventBindings, GUILD_EVENT_ON_BANK_EVENT);
}
// Group
void Eluna::OnAddMember(Group* group, uint64 guid)
{
    if (!GroupEventBindings->HasEvents(GROUP_EVENT_ON_MEMBER_ADD))
        return;

    LOCK_ELUNA;
    Push(group);
    Push(guid);
    CallAllFunctions(GroupEventBindings, GROUP_EVENT_ON_MEMBER_ADD);
}

void Eluna::OnInviteMember(Group* group, uint64 guid)
{
    if (!GroupEventBindings->HasEvents(GROUP_EVENT_ON_MEMBER_INVITE))
        return;

    LOCK_ELUNA;
    Push(group);
    Push(guid);
    CallAllFunctions(GroupEventBindings, GROUP_EVENT_ON_MEMBER_INVITE);
}

void Eluna::OnRemoveMember(Group* group, uint64 guid, uint8 method)
{
    if (!GroupEventBindings->HasEvents(GROUP_EVENT_ON_MEMBER_REMOVE))
        return;

    LOCK_ELUNA;
    Push(group);
    Push(guid);
    Push(method);
    CallAllFunctions(GroupEventBindings, GROUP_EVENT_ON_MEMBER_REMOVE);
}

void Eluna::OnChangeLeader(Group* group, uint64 newLeaderGuid, uint64 oldLeaderGuid)
{
    if (!GroupEventBindings->HasEvents(GROUP_EVENT_ON_LEADER_CHANGE))
        return;

    LOCK_ELUNA;
    Push(group);
    Push(newLeaderGuid);
    Push(oldLeaderGuid);
    CallAllFunctions(GroupEventBindings, GROUP_EVENT_ON_LEADER_CHANGE);
}

void Eluna::OnDisband(Group* group)
{
    if (!GroupEventBindings->HasEvents(GROUP_EVENT_ON_DISBAND))
        return;

    LOCK_ELUNA;
    Push(group);
    CallAllFunctions(GroupEventBindings, GROUP_EVENT_ON_DISBAND);
}

void Eluna::OnCreate(Group* group, uint64 leaderGuid, GroupType groupType)
{
    if (!GroupEventBindings->HasEvents(GROUP_EVENT_ON_CREATE))
        return;

    LOCK_ELUNA;
    Push(group);
    Push(leaderGuid);
    Push(groupType);
    CallAllFunctions(GroupEventBindings, GROUP_EVENT_ON_CREATE);
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

// creature
bool Eluna::OnDummyEffect(Unit* pCaster, uint32 spellId, SpellEffIndex effIndex, Creature* pTarget)
{
    if (!CreatureEventBindings->HasEvents(CREATURE_EVENT_ON_DUMMY_EFFECT, pTarget->GetEntry()))
        if (!CreatureUniqueBindings->HasEvents(CREATURE_EVENT_ON_DUMMY_EFFECT, pTarget->GET_GUID(), pTarget->GetInstanceId()))
            return false;

    LOCK_ELUNA;
    Push(pCaster);
    Push(spellId);
    Push(effIndex);
    Push(pTarget);
    return CallAllFunctionsBool(CreatureEventBindings, CreatureUniqueBindings, CREATURE_EVENT_ON_DUMMY_EFFECT, pTarget->GetEntry(), pTarget->GET_GUID(), pTarget->GetInstanceId());
}

bool Eluna::OnGossipHello(Player* pPlayer, Creature* pCreature)
{
    if (!CreatureGossipBindings->HasEvents(GOSSIP_EVENT_ON_HELLO, pCreature->GetEntry()))
        return false;

    LOCK_ELUNA;
    pPlayer->PlayerTalkClass->ClearMenus();
    Push(pPlayer);
    Push(pCreature);
    return CallAllFunctionsBool(CreatureGossipBindings, GOSSIP_EVENT_ON_HELLO, pCreature->GetEntry(), true);
}

bool Eluna::OnGossipSelect(Player* pPlayer, Creature* pCreature, uint32 sender, uint32 action)
{
    if (!CreatureGossipBindings->HasEvents(GOSSIP_EVENT_ON_SELECT, pCreature->GetEntry()))
        return false;

    LOCK_ELUNA;
    pPlayer->PlayerTalkClass->ClearMenus();
    Push(pPlayer);
    Push(pCreature);
    Push(sender);
    Push(action);
    return CallAllFunctionsBool(CreatureGossipBindings, GOSSIP_EVENT_ON_SELECT, pCreature->GetEntry(), true);
}

bool Eluna::OnGossipSelectCode(Player* pPlayer, Creature* pCreature, uint32 sender, uint32 action, const char* code)
{
    if (!CreatureGossipBindings->HasEvents(GOSSIP_EVENT_ON_SELECT, pCreature->GetEntry()))
        return false;

    LOCK_ELUNA;
    pPlayer->PlayerTalkClass->ClearMenus();
    Push(pPlayer);
    Push(pCreature);
    Push(sender);
    Push(action);
    Push(code);
    return CallAllFunctionsBool(CreatureGossipBindings, GOSSIP_EVENT_ON_SELECT, pCreature->GetEntry(), true);
}

bool Eluna::OnQuestAccept(Player* pPlayer, Creature* pCreature, Quest const* pQuest)
{
    if (!CreatureEventBindings->HasEvents(CREATURE_EVENT_ON_QUEST_ACCEPT, pCreature->GetEntry()))
        if (!CreatureUniqueBindings->HasEvents(CREATURE_EVENT_ON_QUEST_ACCEPT, pCreature->GET_GUID(), pCreature->GetInstanceId()))
            return false;

    LOCK_ELUNA;
    Push(pPlayer);
    Push(pCreature);
    Push(pQuest);
    return CallAllFunctionsBool(CreatureEventBindings, CreatureUniqueBindings, CREATURE_EVENT_ON_QUEST_ACCEPT, pCreature->GetEntry(), pCreature->GET_GUID(), pCreature->GetInstanceId());
}

bool Eluna::OnQuestReward(Player* pPlayer, Creature* pCreature, Quest const* pQuest, uint32 opt)
{
    if (!CreatureEventBindings->HasEvents(CREATURE_EVENT_ON_QUEST_REWARD, pCreature->GetEntry()))
        if (!CreatureUniqueBindings->HasEvents(CREATURE_EVENT_ON_QUEST_REWARD, pCreature->GET_GUID(), pCreature->GetInstanceId()))
            return false;

    LOCK_ELUNA;
    Push(pPlayer);
    Push(pCreature);
    Push(pQuest);
    Push(opt);
    return CallAllFunctionsBool(CreatureEventBindings, CreatureUniqueBindings, CREATURE_EVENT_ON_QUEST_REWARD, pCreature->GetEntry(), pCreature->GET_GUID(), pCreature->GetInstanceId());
}

uint32 Eluna::GetDialogStatus(Player* pPlayer, Creature* pCreature)
{
    if (!CreatureEventBindings->HasEvents(CREATURE_EVENT_ON_DIALOG_STATUS, pCreature->GetEntry()))
        if (!CreatureUniqueBindings->HasEvents(CREATURE_EVENT_ON_DIALOG_STATUS, pCreature->GET_GUID(), pCreature->GetInstanceId()))
            return DIALOG_STATUS_SCRIPTED_NO_STATUS;

    LOCK_ELUNA;
    Push(pPlayer);
    Push(pCreature);
    CallAllFunctions(CreatureEventBindings, CreatureUniqueBindings, CREATURE_EVENT_ON_DIALOG_STATUS, pCreature->GetEntry(), pCreature->GET_GUID(), pCreature->GetInstanceId());
    return DIALOG_STATUS_SCRIPTED_NO_STATUS;
}

void Eluna::OnAddToWorld(Creature* creature)
{
    if (!CreatureEventBindings->HasEvents(CREATURE_EVENT_ON_ADD, creature->GetEntry()))
        if (!CreatureUniqueBindings->HasEvents(CREATURE_EVENT_ON_ADD, creature->GET_GUID(), creature->GetInstanceId()))
            return;

    LOCK_ELUNA;
    Push(creature);
    CallAllFunctions(CreatureEventBindings, CreatureUniqueBindings, CREATURE_EVENT_ON_ADD, creature->GetEntry(), creature->GET_GUID(), creature->GetInstanceId());
}

void Eluna::OnRemoveFromWorld(Creature* creature)
{
    if (!CreatureEventBindings->HasEvents(CREATURE_EVENT_ON_REMOVE, creature->GetEntry()))
        if (!CreatureUniqueBindings->HasEvents(CREATURE_EVENT_ON_REMOVE, creature->GET_GUID(), creature->GetInstanceId()))
            return;

    LOCK_ELUNA;
    Push(creature);
    CallAllFunctions(CreatureEventBindings, CreatureUniqueBindings, CREATURE_EVENT_ON_REMOVE, creature->GetEntry(), creature->GET_GUID(), creature->GetInstanceId());
}

bool Eluna::OnSummoned(Creature* pCreature, Unit* pSummoner)
{
    if (!CreatureEventBindings->HasEvents(CREATURE_EVENT_ON_SUMMONED, pCreature->GetEntry()))
        if (!CreatureUniqueBindings->HasEvents(CREATURE_EVENT_ON_SUMMONED, pCreature->GET_GUID(), pCreature->GetInstanceId()))
            return false;

    LOCK_ELUNA;
    Push(pCreature);
    Push(pSummoner);
    return CallAllFunctionsBool(CreatureEventBindings, CreatureUniqueBindings, CREATURE_EVENT_ON_SUMMONED, pCreature->GetEntry(), pCreature->GET_GUID(), pCreature->GetInstanceId());
}

bool Eluna::UpdateAI(Creature* me, const uint32 diff)
{
    if (!CreatureEventBindings->HasEvents(CREATURE_EVENT_ON_AIUPDATE, me->GetEntry()))
        if (!CreatureUniqueBindings->HasEvents(CREATURE_EVENT_ON_AIUPDATE, me->GET_GUID(), me->GetInstanceId()))
            return false;

    LOCK_ELUNA;
    Push(me);
    Push(diff);
    return CallAllFunctionsBool(CreatureEventBindings, CreatureUniqueBindings, CREATURE_EVENT_ON_AIUPDATE, me->GetEntry(), me->GET_GUID(), me->GetInstanceId());
}

//Called for reaction at enter to combat if not in combat yet (enemy can be NULL)
//Called at creature aggro either by MoveInLOS or Attack Start
bool Eluna::EnterCombat(Creature* me, Unit* target)
{
    if (!CreatureEventBindings->HasEvents(CREATURE_EVENT_ON_ENTER_COMBAT, me->GetEntry()))
        if (!CreatureUniqueBindings->HasEvents(CREATURE_EVENT_ON_ENTER_COMBAT, me->GET_GUID(), me->GetInstanceId()))
            return false;

    LOCK_ELUNA;
    Push(me);
    Push(target);
    return CallAllFunctionsBool(CreatureEventBindings, CreatureUniqueBindings, CREATURE_EVENT_ON_ENTER_COMBAT, me->GetEntry(), me->GET_GUID(), me->GetInstanceId());
}

// Called at any Damage from any attacker (before damage apply)
bool Eluna::DamageTaken(Creature* me, Unit* attacker, uint32& damage)
{
    if (!CreatureEventBindings->HasEvents(CREATURE_EVENT_ON_DAMAGE_TAKEN, me->GetEntry()))
        if (!CreatureUniqueBindings->HasEvents(CREATURE_EVENT_ON_DAMAGE_TAKEN, me->GET_GUID(), me->GetInstanceId()))
            return false;

    LOCK_ELUNA;
    bool result = false;
    Push(me);
    Push(attacker);
    Push(damage);
    int damageIndex = lua_gettop(L);
    int n = SetupStack(CreatureEventBindings, CreatureUniqueBindings, CREATURE_EVENT_ON_DAMAGE_TAKEN, me->GetEntry(), me->GET_GUID(), me->GetInstanceId(), 3);

    while (n > 0)
    {
        int r = CallOneFunction(n--, 3, 2);

        if (lua_isboolean(L, r + 0) && lua_toboolean(L, r + 0))
            result = true;

        if (lua_isnumber(L, r + 1))
        {
            damage = Eluna::CHECKVAL<uint32>(L, r + 1);
            // Update the stack for subsequent calls.
            ReplaceArgument(damage, damageIndex);
        }

        lua_pop(L, 2);
    }

    CleanUpStack(3);
    return result;
}

//Called at creature death
bool Eluna::JustDied(Creature* me, Unit* killer)
{
    On_Reset(me);

    if (!CreatureEventBindings->HasEvents(CREATURE_EVENT_ON_DIED, me->GetEntry()))
        if (!CreatureUniqueBindings->HasEvents(CREATURE_EVENT_ON_DIED, me->GET_GUID(), me->GetInstanceId()))
            return false;

    LOCK_ELUNA;
    Push(me);
    Push(killer);
    return CallAllFunctionsBool(CreatureEventBindings, CreatureUniqueBindings, CREATURE_EVENT_ON_DIED, me->GetEntry(), me->GET_GUID(), me->GetInstanceId());
}

//Called at creature killing another unit
bool Eluna::KilledUnit(Creature* me, Unit* victim)
{
    if (!CreatureEventBindings->HasEvents(CREATURE_EVENT_ON_TARGET_DIED, me->GetEntry()))
        if (!CreatureUniqueBindings->HasEvents(CREATURE_EVENT_ON_TARGET_DIED, me->GET_GUID(), me->GetInstanceId()))
            return false;

    LOCK_ELUNA;
    Push(me);
    Push(victim);
    return CallAllFunctionsBool(CreatureEventBindings, CreatureUniqueBindings, CREATURE_EVENT_ON_TARGET_DIED, me->GetEntry(), me->GET_GUID(), me->GetInstanceId());
}

// Called when the creature summon successfully other creature
bool Eluna::JustSummoned(Creature* me, Creature* summon)
{
    if (!CreatureEventBindings->HasEvents(CREATURE_EVENT_ON_JUST_SUMMONED_CREATURE, me->GetEntry()))
        if (!CreatureUniqueBindings->HasEvents(CREATURE_EVENT_ON_JUST_SUMMONED_CREATURE, me->GET_GUID(), me->GetInstanceId()))
            return false;

    LOCK_ELUNA;
    Push(me);
    Push(summon);
    return CallAllFunctionsBool(CreatureEventBindings, CreatureUniqueBindings, CREATURE_EVENT_ON_JUST_SUMMONED_CREATURE, me->GetEntry(), me->GET_GUID(), me->GetInstanceId());
}

// Called when a summoned creature is despawned
bool Eluna::SummonedCreatureDespawn(Creature* me, Creature* summon)
{
    if (!CreatureEventBindings->HasEvents(CREATURE_EVENT_ON_SUMMONED_CREATURE_DESPAWN, me->GetEntry()))
        if (!CreatureUniqueBindings->HasEvents(CREATURE_EVENT_ON_SUMMONED_CREATURE_DESPAWN, me->GET_GUID(), me->GetInstanceId()))
            return false;

    LOCK_ELUNA;
    Push(me);
    Push(summon);
    return CallAllFunctionsBool(CreatureEventBindings, CreatureUniqueBindings, CREATURE_EVENT_ON_SUMMONED_CREATURE_DESPAWN, me->GetEntry(), me->GET_GUID(), me->GetInstanceId());
}

//Called at waypoint reached or PointMovement end
bool Eluna::MovementInform(Creature* me, uint32 type, uint32 id)
{
    if (!CreatureEventBindings->HasEvents(CREATURE_EVENT_ON_REACH_WP, me->GetEntry()))
        if (!CreatureUniqueBindings->HasEvents(CREATURE_EVENT_ON_REACH_WP, me->GET_GUID(), me->GetInstanceId()))
            return false;

    LOCK_ELUNA;
    Push(me);
    Push(type);
    Push(id);
    return CallAllFunctionsBool(CreatureEventBindings, CreatureUniqueBindings, CREATURE_EVENT_ON_REACH_WP, me->GetEntry(), me->GET_GUID(), me->GetInstanceId());
}

// Called before EnterCombat even before the creature is in combat.
bool Eluna::AttackStart(Creature* me, Unit* target)
{
    if (!CreatureEventBindings->HasEvents(CREATURE_EVENT_ON_PRE_COMBAT, me->GetEntry()))
        if (!CreatureUniqueBindings->HasEvents(CREATURE_EVENT_ON_PRE_COMBAT, me->GET_GUID(), me->GetInstanceId()))
            return false;

    LOCK_ELUNA;
    Push(me);
    Push(target);
    return CallAllFunctionsBool(CreatureEventBindings, CreatureUniqueBindings, CREATURE_EVENT_ON_PRE_COMBAT, me->GetEntry(), me->GET_GUID(), me->GetInstanceId());
}

// Called for reaction at stopping attack at no attackers or targets
bool Eluna::EnterEvadeMode(Creature* me)
{
    On_Reset(me);

    if (!CreatureEventBindings->HasEvents(CREATURE_EVENT_ON_LEAVE_COMBAT, me->GetEntry()))
        if (!CreatureUniqueBindings->HasEvents(CREATURE_EVENT_ON_LEAVE_COMBAT, me->GET_GUID(), me->GetInstanceId()))
            return false;

    LOCK_ELUNA;
    Push(me);
    return CallAllFunctionsBool(CreatureEventBindings, CreatureUniqueBindings, CREATURE_EVENT_ON_LEAVE_COMBAT, me->GetEntry(), me->GET_GUID(), me->GetInstanceId());
}

// Called when the creature is target of hostile action: swing, hostile spell landed, fear/etc)
bool Eluna::AttackedBy(Creature* me, Unit* attacker)
{
    if (!CreatureEventBindings->HasEvents(CREATURE_EVENT_ON_ATTACKED_AT, me->GetEntry()))
        if (!CreatureUniqueBindings->HasEvents(CREATURE_EVENT_ON_ATTACKED_AT, me->GET_GUID(), me->GetInstanceId()))
            return false;

    LOCK_ELUNA;
    Push(me);
    Push(attacker);
    return CallAllFunctionsBool(CreatureEventBindings, CreatureUniqueBindings, CREATURE_EVENT_ON_ATTACKED_AT, me->GetEntry(), me->GET_GUID(), me->GetInstanceId());
}

// Called when creature is spawned or respawned (for reseting variables)
bool Eluna::JustRespawned(Creature* me)
{
    On_Reset(me);

    if (!CreatureEventBindings->HasEvents(CREATURE_EVENT_ON_SPAWN, me->GetEntry()))
        if (!CreatureUniqueBindings->HasEvents(CREATURE_EVENT_ON_SPAWN, me->GET_GUID(), me->GetInstanceId()))
            return false;

    LOCK_ELUNA;
    Push(me);
    return CallAllFunctionsBool(CreatureEventBindings, CreatureUniqueBindings, CREATURE_EVENT_ON_SPAWN, me->GetEntry(), me->GET_GUID(), me->GetInstanceId());
}

// Called at reaching home after evade
bool Eluna::JustReachedHome(Creature* me)
{
    if (!CreatureEventBindings->HasEvents(CREATURE_EVENT_ON_REACH_HOME, me->GetEntry()))
        if (!CreatureUniqueBindings->HasEvents(CREATURE_EVENT_ON_REACH_HOME, me->GET_GUID(), me->GetInstanceId()))
            return false;

    LOCK_ELUNA;
    Push(me);
    return CallAllFunctionsBool(CreatureEventBindings, CreatureUniqueBindings, CREATURE_EVENT_ON_REACH_HOME, me->GetEntry(), me->GET_GUID(), me->GetInstanceId());
}

// Called at text emote receive from player
bool Eluna::ReceiveEmote(Creature* me, Player* player, uint32 emoteId)
{
    if (!CreatureEventBindings->HasEvents(CREATURE_EVENT_ON_RECEIVE_EMOTE, me->GetEntry()))
        if (!CreatureUniqueBindings->HasEvents(CREATURE_EVENT_ON_RECEIVE_EMOTE, me->GET_GUID(), me->GetInstanceId()))
            return false;

    LOCK_ELUNA;
    Push(me);
    Push(player);
    Push(emoteId);
    return CallAllFunctionsBool(CreatureEventBindings, CreatureUniqueBindings, CREATURE_EVENT_ON_RECEIVE_EMOTE, me->GetEntry(), me->GET_GUID(), me->GetInstanceId());
}

// called when the corpse of this creature gets removed
bool Eluna::CorpseRemoved(Creature* me, uint32& respawnDelay)
{
    if (!CreatureEventBindings->HasEvents(CREATURE_EVENT_ON_CORPSE_REMOVED, me->GetEntry()))
        if (!CreatureUniqueBindings->HasEvents(CREATURE_EVENT_ON_CORPSE_REMOVED, me->GET_GUID(), me->GetInstanceId()))
            return false;

    LOCK_ELUNA;
    bool result = false;
    Push(me);
    Push(respawnDelay);
    int respawnDelayIndex = lua_gettop(L);
    int n = SetupStack(CreatureEventBindings, CreatureUniqueBindings, CREATURE_EVENT_ON_CORPSE_REMOVED, me->GetEntry(), me->GET_GUID(), me->GetInstanceId(), 2);

    while (n > 0)
    {
        int r = CallOneFunction(n--, 2, 2);

        if (lua_isboolean(L, r + 0) && lua_toboolean(L, r + 0))
            result = true;

        if (lua_isnumber(L, r + 1))
        {
            respawnDelay = Eluna::CHECKVAL<uint32>(L, r + 1);
            // Update the stack for subsequent calls.
            ReplaceArgument(respawnDelay, respawnDelayIndex);
        }

        lua_pop(L, 2);
    }

    CleanUpStack(2);
    return result;
}

bool Eluna::MoveInLineOfSight(Creature* me, Unit* who)
{
    if (!CreatureEventBindings->HasEvents(CREATURE_EVENT_ON_MOVE_IN_LOS, me->GetEntry()))
        if (!CreatureUniqueBindings->HasEvents(CREATURE_EVENT_ON_MOVE_IN_LOS, me->GET_GUID(), me->GetInstanceId()))
            return false;

    LOCK_ELUNA;
    Push(me);
    Push(who);
    return CallAllFunctionsBool(CreatureEventBindings, CreatureUniqueBindings, CREATURE_EVENT_ON_MOVE_IN_LOS, me->GetEntry(), me->GET_GUID(), me->GetInstanceId());
}

// Called on creature initial spawn, respawn, death, evade (leave combat)
void Eluna::On_Reset(Creature* me) // Not an override, custom
{
    if (!CreatureEventBindings->HasEvents(CREATURE_EVENT_ON_RESET, me->GetEntry()))
        if (!CreatureUniqueBindings->HasEvents(CREATURE_EVENT_ON_RESET, me->GET_GUID(), me->GetInstanceId()))
            return;

    LOCK_ELUNA;
    Push(me);
    CallAllFunctions(CreatureEventBindings, CreatureUniqueBindings, CREATURE_EVENT_ON_RESET, me->GetEntry(), me->GET_GUID(), me->GetInstanceId());
}

// Called when hit by a spell
bool Eluna::SpellHit(Creature* me, Unit* caster, SpellInfo const* spell)
{
    if (!CreatureEventBindings->HasEvents(CREATURE_EVENT_ON_HIT_BY_SPELL, me->GetEntry()))
        if (!CreatureUniqueBindings->HasEvents(CREATURE_EVENT_ON_HIT_BY_SPELL, me->GET_GUID(), me->GetInstanceId()))
            return false;

    LOCK_ELUNA;
    Push(me);
    Push(caster);
    Push(spell->Id); // Pass spell object?
    return CallAllFunctionsBool(CreatureEventBindings, CreatureUniqueBindings, CREATURE_EVENT_ON_HIT_BY_SPELL, me->GetEntry(), me->GET_GUID(), me->GetInstanceId());
}

// Called when spell hits a target
bool Eluna::SpellHitTarget(Creature* me, Unit* target, SpellInfo const* spell)
{
    if (!CreatureEventBindings->HasEvents(CREATURE_EVENT_ON_SPELL_HIT_TARGET, me->GetEntry()))
        if (!CreatureUniqueBindings->HasEvents(CREATURE_EVENT_ON_SPELL_HIT_TARGET, me->GET_GUID(), me->GetInstanceId()))
            return false;

    LOCK_ELUNA;
    Push(me);
    Push(target);
    Push(spell->Id); // Pass spell object?
    return CallAllFunctionsBool(CreatureEventBindings, CreatureUniqueBindings, CREATURE_EVENT_ON_SPELL_HIT_TARGET, me->GetEntry(), me->GET_GUID(), me->GetInstanceId());
}

#ifdef TRINITY

bool Eluna::SummonedCreatureDies(Creature* me, Creature* summon, Unit* killer)
{
    if (!CreatureEventBindings->HasEvents(CREATURE_EVENT_ON_SUMMONED_CREATURE_DIED, me->GetEntry()))
        if (!CreatureUniqueBindings->HasEvents(CREATURE_EVENT_ON_SUMMONED_CREATURE_DIED, me->GET_GUID(), me->GetInstanceId()))
            return false;

    LOCK_ELUNA;
    Push(me);
    Push(summon);
    Push(killer);
    return CallAllFunctionsBool(CreatureEventBindings, CreatureUniqueBindings, CREATURE_EVENT_ON_SUMMONED_CREATURE_DIED, me->GetEntry(), me->GET_GUID(), me->GetInstanceId());
}

// Called when owner takes damage
bool Eluna::OwnerAttackedBy(Creature* me, Unit* attacker)
{
    if (!CreatureEventBindings->HasEvents(CREATURE_EVENT_ON_OWNER_ATTACKED_AT, me->GetEntry()))
        if (!CreatureUniqueBindings->HasEvents(CREATURE_EVENT_ON_OWNER_ATTACKED_AT, me->GET_GUID(), me->GetInstanceId()))
            return false;

    LOCK_ELUNA;
    Push(me);
    Push(attacker);
    return CallAllFunctionsBool(CreatureEventBindings, CreatureUniqueBindings, CREATURE_EVENT_ON_OWNER_ATTACKED_AT, me->GetEntry(), me->GET_GUID(), me->GetInstanceId());
}

// Called when owner attacks something
bool Eluna::OwnerAttacked(Creature* me, Unit* target)
{
    if (!CreatureEventBindings->HasEvents(CREATURE_EVENT_ON_OWNER_ATTACKED, me->GetEntry()))
        if (!CreatureUniqueBindings->HasEvents(CREATURE_EVENT_ON_OWNER_ATTACKED, me->GET_GUID(), me->GetInstanceId()))
            return false;

    LOCK_ELUNA;
    Push(me);
    Push(target);
    return CallAllFunctionsBool(CreatureEventBindings, CreatureUniqueBindings, CREATURE_EVENT_ON_OWNER_ATTACKED, me->GetEntry(), me->GET_GUID(), me->GetInstanceId());
}
#endif

struct ElunaCreatureAI : ScriptedAI
{
#ifndef TRINITY
#define me  m_creature
#endif

    ElunaCreatureAI(Creature* creature) : ScriptedAI(creature)
    {
        JustRespawned();
    }
    ~ElunaCreatureAI() { }

    //Called at World update tick
#ifndef TRINITY
    void UpdateAI(const uint32 diff) override
#else
    void UpdateAI(uint32 diff) override
#endif
    {
        if (!sEluna->UpdateAI(me, diff))
        {
#ifdef TRINITY
            if (!me->HasFlag(UNIT_FIELD_FLAGS, UNIT_FLAG_IMMUNE_TO_NPC))
                ScriptedAI::UpdateAI(diff);
#else
            if (!me->HasFlag(UNIT_FIELD_FLAGS, UNIT_FLAG_PASSIVE))
                ScriptedAI::UpdateAI(diff);
#endif
        }
    }

    //Called for reaction at enter to combat if not in combat yet (enemy can be NULL)
    //Called at creature aggro either by MoveInLOS or Attack Start
    void EnterCombat(Unit* target) override
    {
        if (!sEluna->EnterCombat(me, target))
            ScriptedAI::EnterCombat(target);
    }

    // Called at any Damage from any attacker (before damage apply)
    void DamageTaken(Unit* attacker, uint32& damage) override
    {
        if (!sEluna->DamageTaken(me, attacker, damage))
            ScriptedAI::DamageTaken(attacker, damage);
    }

    //Called at creature death
    void JustDied(Unit* killer) override
    {
        if (!sEluna->JustDied(me, killer))
            ScriptedAI::JustDied(killer);
    }

    //Called at creature killing another unit
    void KilledUnit(Unit* victim) override
    {
        if (!sEluna->KilledUnit(me, victim))
            ScriptedAI::KilledUnit(victim);
    }

    // Called when the creature summon successfully other creature
    void JustSummoned(Creature* summon) override
    {
        if (!sEluna->JustSummoned(me, summon))
            ScriptedAI::JustSummoned(summon);
    }

    // Called when a summoned creature is despawned
    void SummonedCreatureDespawn(Creature* summon) override
    {
        if (!sEluna->SummonedCreatureDespawn(me, summon))
            ScriptedAI::SummonedCreatureDespawn(summon);
    }

    //Called at waypoint reached or PointMovement end
    void MovementInform(uint32 type, uint32 id) override
    {
        if (!sEluna->MovementInform(me, type, id))
            ScriptedAI::MovementInform(type, id);
    }

    // Called before EnterCombat even before the creature is in combat.
    void AttackStart(Unit* target) override
    {
        if (!sEluna->AttackStart(me, target))
            ScriptedAI::AttackStart(target);
    }

    // Called for reaction at stopping attack at no attackers or targets
    void EnterEvadeMode() override
    {
        if (!sEluna->EnterEvadeMode(me))
            ScriptedAI::EnterEvadeMode();
    }

    // Called when the creature is target of hostile action: swing, hostile spell landed, fear/etc)
    void AttackedBy(Unit* attacker) override
    {
        if (!sEluna->AttackedBy(me, attacker))
            ScriptedAI::AttackedBy(attacker);
    }

    // Called when creature is spawned or respawned (for reseting variables)
    void JustRespawned() override
    {
        if (!sEluna->JustRespawned(me))
            ScriptedAI::JustRespawned();
    }

    // Called at reaching home after evade
    void JustReachedHome() override
    {
        if (!sEluna->JustReachedHome(me))
            ScriptedAI::JustReachedHome();
    }

    // Called at text emote receive from player
    void ReceiveEmote(Player* player, uint32 emoteId) override
    {
        if (!sEluna->ReceiveEmote(me, player, emoteId))
            ScriptedAI::ReceiveEmote(player, emoteId);
    }

    // called when the corpse of this creature gets removed
    void CorpseRemoved(uint32& respawnDelay) override
    {
        if (!sEluna->CorpseRemoved(me, respawnDelay))
            ScriptedAI::CorpseRemoved(respawnDelay);
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
        if (!sEluna->MoveInLineOfSight(me, who))
            ScriptedAI::MoveInLineOfSight(who);
    }

    // Called when hit by a spell
    void SpellHit(Unit* caster, SpellInfo const* spell) override
    {
        if (!sEluna->SpellHit(me, caster, spell))
            ScriptedAI::SpellHit(caster, spell);
    }

    // Called when spell hits a target
    void SpellHitTarget(Unit* target, SpellInfo const* spell) override
    {
        if (!sEluna->SpellHitTarget(me, target, spell))
            ScriptedAI::SpellHitTarget(target, spell);
    }

#ifdef TRINITY

    // Called when the creature is summoned successfully by other creature
    void IsSummonedBy(Unit* summoner) override
    {
        if (!sEluna->OnSummoned(me, summoner))
            ScriptedAI::IsSummonedBy(summoner);
    }

    void SummonedCreatureDies(Creature* summon, Unit* killer) override
    {
        if (!sEluna->SummonedCreatureDies(me, summon, killer))
            ScriptedAI::SummonedCreatureDies(summon, killer);
    }

    // Called when owner takes damage
    void OwnerAttackedBy(Unit* attacker) override
    {
        if (!sEluna->OwnerAttackedBy(me, attacker))
            ScriptedAI::OwnerAttackedBy(attacker);
    }

    // Called when owner attacks something
    void OwnerAttacked(Unit* target) override
    {
        if (!sEluna->OwnerAttacked(me, target))
            ScriptedAI::OwnerAttacked(target);
    }
#endif

#ifndef TRINITY
#undef me
#endif
};

// gameobject
bool Eluna::OnDummyEffect(Unit* pCaster, uint32 spellId, SpellEffIndex effIndex, GameObject* pTarget)
{
    if (!GameObjectEventBindings->HasEvents(GAMEOBJECT_EVENT_ON_DUMMY_EFFECT, pTarget->GetEntry()))
        return false;

    LOCK_ELUNA;
    Push(pCaster);
    Push(spellId);
    Push(effIndex);
    Push(pTarget);
    return CallAllFunctionsBool(GameObjectEventBindings, GAMEOBJECT_EVENT_ON_DUMMY_EFFECT, pTarget->GetEntry());
}

bool Eluna::OnGossipHello(Player* pPlayer, GameObject* pGameObject)
{
    if (!GameObjectGossipBindings->HasEvents(GOSSIP_EVENT_ON_HELLO, pGameObject->GetEntry()))
        return false;

    LOCK_ELUNA;
    pPlayer->PlayerTalkClass->ClearMenus();
    Push(pPlayer);
    Push(pGameObject);
    return CallAllFunctionsBool(GameObjectGossipBindings, GOSSIP_EVENT_ON_HELLO, pGameObject->GetEntry(), true);
}

bool Eluna::OnGossipSelect(Player* pPlayer, GameObject* pGameObject, uint32 sender, uint32 action)
{
    if (!GameObjectGossipBindings->HasEvents(GOSSIP_EVENT_ON_SELECT, pGameObject->GetEntry()))
        return false;

    LOCK_ELUNA;
    pPlayer->PlayerTalkClass->ClearMenus();
    Push(pPlayer);
    Push(pGameObject);
    Push(sender);
    Push(action);
    return CallAllFunctionsBool(GameObjectGossipBindings, GOSSIP_EVENT_ON_SELECT, pGameObject->GetEntry(), true);
}

bool Eluna::OnGossipSelectCode(Player* pPlayer, GameObject* pGameObject, uint32 sender, uint32 action, const char* code)
{
    if (!GameObjectGossipBindings->HasEvents(GOSSIP_EVENT_ON_SELECT, pGameObject->GetEntry()))
        return false;

    LOCK_ELUNA;
    pPlayer->PlayerTalkClass->ClearMenus();
    Push(pPlayer);
    Push(pGameObject);
    Push(sender);
    Push(action);
    Push(code);
    return CallAllFunctionsBool(GameObjectGossipBindings, GOSSIP_EVENT_ON_SELECT, pGameObject->GetEntry(), true);
}

bool Eluna::OnQuestAccept(Player* pPlayer, GameObject* pGameObject, Quest const* pQuest)
{
    if (!GameObjectEventBindings->HasEvents(GAMEOBJECT_EVENT_ON_QUEST_ACCEPT, pGameObject->GetEntry()))
        return false;

    LOCK_ELUNA;
    Push(pPlayer);
    Push(pGameObject);
    Push(pQuest);
    return CallAllFunctionsBool(GameObjectEventBindings, GAMEOBJECT_EVENT_ON_QUEST_ACCEPT, pGameObject->GetEntry());
}

void Eluna::UpdateAI(GameObject* pGameObject, uint32 diff)
{
    if (!GameObjectEventBindings->HasEvents(GAMEOBJECT_EVENT_ON_AIUPDATE, pGameObject->GetEntry()))
        return;

    LOCK_ELUNA;
    pGameObject->elunaEvents->Update(diff);
    Push(pGameObject);
    Push(diff);
    CallAllFunctions(GameObjectEventBindings, GAMEOBJECT_EVENT_ON_AIUPDATE, pGameObject->GetEntry());
}

bool Eluna::OnQuestReward(Player* pPlayer, GameObject* pGameObject, Quest const* pQuest, uint32 opt)
{
    if (!GameObjectEventBindings->HasEvents(GAMEOBJECT_EVENT_ON_QUEST_REWARD, pGameObject->GetEntry()))
        return false;

    LOCK_ELUNA;
    Push(pPlayer);
    Push(pGameObject);
    Push(pQuest);
    Push(opt);
    return CallAllFunctionsBool(GameObjectEventBindings, GAMEOBJECT_EVENT_ON_QUEST_REWARD, pGameObject->GetEntry());
}

uint32 Eluna::GetDialogStatus(Player* pPlayer, GameObject* pGameObject)
{
    if (!GameObjectEventBindings->HasEvents(GAMEOBJECT_EVENT_ON_DIALOG_STATUS, pGameObject->GetEntry()))
        return DIALOG_STATUS_SCRIPTED_NO_STATUS;

    LOCK_ELUNA;
    Push(pPlayer);
    Push(pGameObject);
    CallAllFunctions(GameObjectEventBindings, GAMEOBJECT_EVENT_ON_DIALOG_STATUS, pGameObject->GetEntry());
    return DIALOG_STATUS_SCRIPTED_NO_STATUS; // DIALOG_STATUS_UNDEFINED
}

#ifndef CLASSIC
#ifndef TBC
void Eluna::OnDestroyed(GameObject* pGameObject, Player* pPlayer)
{
    if (!GameObjectEventBindings->HasEvents(GAMEOBJECT_EVENT_ON_DESTROYED, pGameObject->GetEntry()))
        return;

    LOCK_ELUNA;
    Push(pGameObject);
    Push(pPlayer);
    CallAllFunctions(GameObjectEventBindings, GAMEOBJECT_EVENT_ON_DESTROYED, pGameObject->GetEntry());
}

void Eluna::OnDamaged(GameObject* pGameObject, Player* pPlayer)
{
    if (!GameObjectEventBindings->HasEvents(GAMEOBJECT_EVENT_ON_DAMAGED, pGameObject->GetEntry()))
        return;

    LOCK_ELUNA;
    Push(pGameObject);
    Push(pPlayer);
    CallAllFunctions(GameObjectEventBindings, GAMEOBJECT_EVENT_ON_DAMAGED, pGameObject->GetEntry());
}
#endif
#endif

void Eluna::OnLootStateChanged(GameObject* pGameObject, uint32 state)
{
    if (!GameObjectEventBindings->HasEvents(GAMEOBJECT_EVENT_ON_LOOT_STATE_CHANGE, pGameObject->GetEntry()))
        return;

    LOCK_ELUNA;
    Push(pGameObject);
    Push(state);
    CallAllFunctions(GameObjectEventBindings, GAMEOBJECT_EVENT_ON_LOOT_STATE_CHANGE, pGameObject->GetEntry());
}

void Eluna::OnGameObjectStateChanged(GameObject* pGameObject, uint32 state)
{
    if (!GameObjectEventBindings->HasEvents(GAMEOBJECT_EVENT_ON_GO_STATE_CHANGED, pGameObject->GetEntry()))
        return;

    LOCK_ELUNA;
    Push(pGameObject);
    Push(state);
    CallAllFunctions(GameObjectEventBindings, GAMEOBJECT_EVENT_ON_GO_STATE_CHANGED, pGameObject->GetEntry());
}

void Eluna::OnSpawn(GameObject* gameobject)
{
    if (!GameObjectEventBindings->HasEvents(GAMEOBJECT_EVENT_ON_SPAWN, gameobject->GetEntry()))
        return;

    LOCK_ELUNA;
    Push(gameobject);
    CallAllFunctions(GameObjectEventBindings, GAMEOBJECT_EVENT_ON_SPAWN, gameobject->GetEntry());
}

void Eluna::OnAddToWorld(GameObject* gameobject)
{
    if (!GameObjectEventBindings->HasEvents(GAMEOBJECT_EVENT_ON_ADD, gameobject->GetEntry()))
        return;

    LOCK_ELUNA;
    Push(gameobject);
    CallAllFunctions(GameObjectEventBindings, GAMEOBJECT_EVENT_ON_ADD, gameobject->GetEntry());
}

void Eluna::OnRemoveFromWorld(GameObject* gameobject)
{
    if (!GameObjectEventBindings->HasEvents(GAMEOBJECT_EVENT_ON_REMOVE, gameobject->GetEntry()))
        return;

    LOCK_ELUNA;
    Push(gameobject);
    CallAllFunctions(GameObjectEventBindings, GAMEOBJECT_EVENT_ON_REMOVE, gameobject->GetEntry());
}

CreatureAI* Eluna::GetAI(Creature* creature)
{
    if (!CreatureEventBindings->HasEvents(creature->GetEntry()) && !CreatureUniqueBindings->HasEvents(creature->GET_GUID(), creature->GetInstanceId()))
        return NULL;
    return new ElunaCreatureAI(creature);
}

void Eluna::OnBGStart(BattleGround* bg, BattleGroundTypeId bgId, uint32 instanceId)
{
    if (!BGEventBindings->HasEvents(BG_EVENT_ON_START))
        return;

    LOCK_ELUNA;
    Push(bg);
    Push(bgId);
    Push(instanceId);
    CallAllFunctions(BGEventBindings, BG_EVENT_ON_START);
}

void Eluna::OnBGEnd(BattleGround* bg, BattleGroundTypeId bgId, uint32 instanceId, Team winner)
{
    if (!BGEventBindings->HasEvents(BG_EVENT_ON_END))
        return;

    LOCK_ELUNA;
    Push(bg);
    Push(bgId);
    Push(instanceId);
    Push(winner);
    CallAllFunctions(BGEventBindings, BG_EVENT_ON_END);
}

void Eluna::OnBGCreate(BattleGround* bg, BattleGroundTypeId bgId, uint32 instanceId)
{
    if (!BGEventBindings->HasEvents(BG_EVENT_ON_CREATE))
        return;

    LOCK_ELUNA;
    Push(bg);
    Push(bgId);
    Push(instanceId);
    CallAllFunctions(BGEventBindings, BG_EVENT_ON_CREATE);
}

void Eluna::OnBGDestroy(BattleGround* bg, BattleGroundTypeId bgId, uint32 instanceId)
{
    if (!BGEventBindings->HasEvents(BG_EVENT_ON_PRE_DESTROY))
        return;

    LOCK_ELUNA;
    Push(bg);
    Push(bgId);
    Push(instanceId);
    CallAllFunctions(BGEventBindings, BG_EVENT_ON_PRE_DESTROY);
}
