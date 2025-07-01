/*
* Copyright (C) 2010 - 2024 Eluna Lua Engine <https://elunaluaengine.github.io/>
* This program is free software licensed under GPL version 3
* Please see the included DOCS/LICENSE.md for more information
*/

#include "Hooks.h"
#include "HookHelpers.h"
#include "LuaEngine.h"
#include "BindingMap.h"
#include "ElunaIncludes.h"
#include "ElunaTemplate.h"

using namespace Hooks;

#define START_HOOK(REGTYPE, EVENT, ENTRY) \
    auto binding = GetBinding<EntryKey<GossipEvents>>(REGTYPE);\
    auto key = EntryKey<GossipEvents>(EVENT, ENTRY);\
    if (!binding->HasBindingsFor(key))\
        return;

#define START_HOOK_WITH_RETVAL(REGTYPE, EVENT, ENTRY, RETVAL) \
    auto binding = GetBinding<EntryKey<GossipEvents>>(REGTYPE);\
    auto key = EntryKey<GossipEvents>(EVENT, ENTRY);\
    if (!binding->HasBindingsFor(key))\
        return RETVAL;

bool Eluna::OnGossipHello(Player* pPlayer, GameObject* pGameObject)
{
    START_HOOK_WITH_RETVAL(REGTYPE_GAMEOBJECT_GOSSIP, GOSSIP_EVENT_ON_HELLO, pGameObject->GetEntry(), false);
#if defined ELUNA_CMANGOS && ELUNA_EXPANSION < EXP_CATA
    pPlayer->GetPlayerMenu()->ClearMenus();
#else
    pPlayer->PlayerTalkClass->ClearMenus();
#endif
    HookPush(pPlayer);
    HookPush(pGameObject);
    return CallAllFunctionsBool(binding, key, true);
}

bool Eluna::OnGossipSelect(Player* pPlayer, GameObject* pGameObject, uint32 sender, uint32 action)
{
    START_HOOK_WITH_RETVAL(REGTYPE_GAMEOBJECT_GOSSIP, GOSSIP_EVENT_ON_SELECT, pGameObject->GetEntry(), false);
#if defined ELUNA_CMANGOS && ELUNA_EXPANSION < EXP_CATA
    pPlayer->GetPlayerMenu()->ClearMenus();
#else
    pPlayer->PlayerTalkClass->ClearMenus();
#endif
    HookPush(pPlayer);
    HookPush(pGameObject);
    HookPush(sender);
    HookPush(action);
    return CallAllFunctionsBool(binding, key, true);
}

bool Eluna::OnGossipSelectCode(Player* pPlayer, GameObject* pGameObject, uint32 sender, uint32 action, const char* code)
{
    START_HOOK_WITH_RETVAL(REGTYPE_GAMEOBJECT_GOSSIP, GOSSIP_EVENT_ON_SELECT, pGameObject->GetEntry(), false);
#if defined ELUNA_CMANGOS && ELUNA_EXPANSION < EXP_CATA
    pPlayer->GetPlayerMenu()->ClearMenus();
#else
    pPlayer->PlayerTalkClass->ClearMenus();
#endif
    HookPush(pPlayer);
    HookPush(pGameObject);
    HookPush(sender);
    HookPush(action);
    HookPush(code);
    return CallAllFunctionsBool(binding, key, true);
}

void Eluna::HandleGossipSelectOption(Player* pPlayer, uint32 menuId, uint32 sender, uint32 action, const std::string& code)
{
    START_HOOK(REGTYPE_PLAYER_GOSSIP, GOSSIP_EVENT_ON_SELECT, menuId);
#if defined ELUNA_CMANGOS && ELUNA_EXPANSION < EXP_CATA
    pPlayer->GetPlayerMenu()->ClearMenus();
#else
    pPlayer->PlayerTalkClass->ClearMenus();
#endif

    HookPush(pPlayer); // receiver
    HookPush(pPlayer); // sender, just not to mess up the amount of args.
    HookPush(sender);
    HookPush(action);
    if (code.empty())
        HookPush();
    else
        HookPush(code);

    CallAllFunctions(binding, key);
}

bool Eluna::OnItemGossip(Player* pPlayer, Item* pItem, SpellCastTargets const& /*targets*/)
{
    START_HOOK_WITH_RETVAL(REGTYPE_ITEM_GOSSIP, GOSSIP_EVENT_ON_HELLO, pItem->GetEntry(), true);
#if defined ELUNA_CMANGOS && ELUNA_EXPANSION < EXP_CATA
    pPlayer->GetPlayerMenu()->ClearMenus();
#else
    pPlayer->PlayerTalkClass->ClearMenus();
#endif
    HookPush(pPlayer);
    HookPush(pItem);
    return CallAllFunctionsBool(binding, key, true);
}

void Eluna::HandleGossipSelectOption(Player* pPlayer, Item* pItem, uint32 sender, uint32 action, const std::string& code)
{
    START_HOOK(REGTYPE_ITEM_GOSSIP, GOSSIP_EVENT_ON_SELECT, pItem->GetEntry());
#if defined ELUNA_CMANGOS && ELUNA_EXPANSION < EXP_CATA
    pPlayer->GetPlayerMenu()->ClearMenus();
#else
    pPlayer->PlayerTalkClass->ClearMenus();
#endif

    HookPush(pPlayer);
    HookPush(pItem);
    HookPush(sender);
    HookPush(action);
    if (code.empty())
        HookPush();
    else
        HookPush(code);

    CallAllFunctions(binding, key);
}

bool Eluna::OnGossipHello(Player* pPlayer, Creature* pCreature)
{
    START_HOOK_WITH_RETVAL(REGTYPE_CREATURE_GOSSIP, GOSSIP_EVENT_ON_HELLO, pCreature->GetEntry(), false);
#if defined ELUNA_CMANGOS && ELUNA_EXPANSION < EXP_CATA
    pPlayer->GetPlayerMenu()->ClearMenus();
#else
    pPlayer->PlayerTalkClass->ClearMenus();
#endif
    HookPush(pPlayer);
    HookPush(pCreature);
    return CallAllFunctionsBool(binding, key, true);
}

bool Eluna::OnGossipSelect(Player* pPlayer, Creature* pCreature, uint32 sender, uint32 action)
{
    START_HOOK_WITH_RETVAL(REGTYPE_CREATURE_GOSSIP, GOSSIP_EVENT_ON_SELECT, pCreature->GetEntry(), false);
#if defined ELUNA_CMANGOS && ELUNA_EXPANSION < EXP_CATA
    auto original_menu = *pPlayer->GetPlayerMenu();
    pPlayer->GetPlayerMenu()->ClearMenus();
#else
    auto original_menu = *pPlayer->PlayerTalkClass;
    pPlayer->PlayerTalkClass->ClearMenus();
#endif
    HookPush(pPlayer);
    HookPush(pCreature);
    HookPush(sender);
    HookPush(action);
    auto preventDefault = CallAllFunctionsBool(binding, key, true);
    if (!preventDefault) {
#if defined ELUNA_CMANGOS && ELUNA_EXPANSION < EXP_CATA
        *pPlayer->GetPlayerMenu() = original_menu;
#else
        *pPlayer->PlayerTalkClass = original_menu;
#endif
    }
    return preventDefault;
}

bool Eluna::OnGossipSelectCode(Player* pPlayer, Creature* pCreature, uint32 sender, uint32 action, const char* code)
{
    START_HOOK_WITH_RETVAL(REGTYPE_CREATURE_GOSSIP, GOSSIP_EVENT_ON_SELECT, pCreature->GetEntry(), false);
#if defined ELUNA_CMANGOS && ELUNA_EXPANSION < EXP_CATA
    auto original_menu = *pPlayer->GetPlayerMenu();
    pPlayer->GetPlayerMenu()->ClearMenus();
#else
    auto original_menu = *pPlayer->PlayerTalkClass;
    pPlayer->PlayerTalkClass->ClearMenus();
#endif
    HookPush(pPlayer);
    HookPush(pCreature);
    HookPush(sender);
    HookPush(action);
    HookPush(code);
    auto preventDefault = CallAllFunctionsBool(binding, key, true);
    if (!preventDefault) {
#if defined ELUNA_CMANGOS && ELUNA_EXPANSION < EXP_CATA
        *pPlayer->GetPlayerMenu() = original_menu;
#else
        *pPlayer->PlayerTalkClass = original_menu;
#endif
    }
    return preventDefault;
}
