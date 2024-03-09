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

#define START_HOOK(EVENT, ENTRY) \
    auto key = EntryKey<ItemEvents>(EVENT, ENTRY);\
    if (!ItemEventBindings->HasBindingsFor(key))\
        return;

#define START_HOOK_WITH_RETVAL(EVENT, ENTRY, RETVAL) \
    auto key = EntryKey<ItemEvents>(EVENT, ENTRY);\
    if (!ItemEventBindings->HasBindingsFor(key))\
        return RETVAL;

void Eluna::OnDummyEffect(WorldObject* pCaster, uint32 spellId, SpellEffIndex effIndex, Item* pTarget)
{
    START_HOOK(ITEM_EVENT_ON_DUMMY_EFFECT, pTarget->GetEntry());
    HookPush(pCaster);
    HookPush(spellId);
    HookPush(effIndex);
    HookPush(pTarget);
    CallAllFunctions(ItemEventBindings, key);
}

bool Eluna::OnQuestAccept(Player* pPlayer, Item* pItem, Quest const* pQuest)
{
    START_HOOK_WITH_RETVAL(ITEM_EVENT_ON_QUEST_ACCEPT, pItem->GetEntry(), false);
    HookPush(pPlayer);
    HookPush(pItem);
    HookPush(pQuest);
    return CallAllFunctionsBool(ItemEventBindings, key);
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
    data << guid;
    data << ObjectGuid(uint64(0));
    data << uint8(0);
#ifdef CMANGOS
    pPlayer->GetSession()->SendPacket(data);
#else
    pPlayer->GetSession()->SendPacket(&data);
#endif
    return false;
}

bool Eluna::OnItemUse(Player* pPlayer, Item* pItem, SpellCastTargets const& targets)
{
    START_HOOK_WITH_RETVAL(ITEM_EVENT_ON_USE, pItem->GetEntry(), true);
    HookPush(pPlayer);
    HookPush(pItem);
#if defined TRINITY || AZEROTHCORE
    if (GameObject* target = targets.GetGOTarget())
        HookPush(target);
    else if (Item* target = targets.GetItemTarget())
        HookPush(target);
    else if (Corpse* target = targets.GetCorpseTarget())
        HookPush(target);
    else if (Unit* target = targets.GetUnitTarget())
        HookPush(target);
    else if (WorldObject* target = targets.GetObjectTarget())
        HookPush(target);
    else
        HookPush();
#else
    if (GameObject* target = targets.getGOTarget())
        HookPush(target);
    else if (Item* target = targets.getItemTarget())
        HookPush(target);
    else if (Corpse* target = pPlayer->GetMap()->GetCorpse(targets.getCorpseTargetGuid()))
        HookPush(target);
    else if (Unit* target = targets.getUnitTarget())
        HookPush(target);
    else
        HookPush();
#endif

    return CallAllFunctionsBool(ItemEventBindings, key, true);
}

bool Eluna::OnExpire(Player* pPlayer, ItemTemplate const* pProto)
{
    START_HOOK_WITH_RETVAL(ITEM_EVENT_ON_EXPIRE, pProto->ItemId, false);
    HookPush(pPlayer);
    HookPush(pProto->ItemId);
    return CallAllFunctionsBool(ItemEventBindings, key);
}

bool Eluna::OnRemove(Player* pPlayer, Item* pItem)
{
    START_HOOK_WITH_RETVAL(ITEM_EVENT_ON_REMOVE, pItem->GetEntry(), false);
    HookPush(pPlayer);
    HookPush(pItem);
    return CallAllFunctionsBool(ItemEventBindings, key);
}

void Eluna::OnAdd(Player* pPlayer, Item* pItem)
{
    START_HOOK(ITEM_EVENT_ON_ADD, pItem->GetEntry());
    HookPush(pPlayer);
    HookPush(pItem);
    CallAllFunctions(ItemEventBindings, key);
}

void Eluna::OnItemEquip(Player* pPlayer, Item* pItem, uint8 slot)
{
    START_HOOK(ITEM_EVENT_ON_EQUIP, pItem->GetEntry());
    HookPush(pPlayer);
    HookPush(pItem);
    HookPush(slot);
    CallAllFunctions(ItemEventBindings, key);
}

void Eluna::OnItemUnEquip(Player* pPlayer, Item* pItem, uint8 slot)
{
    START_HOOK(ITEM_EVENT_ON_UNEQUIP, pItem->GetEntry());
    HookPush(pPlayer);
    HookPush(pItem);
    HookPush(slot);
    CallAllFunctions(ItemEventBindings, key);
}
