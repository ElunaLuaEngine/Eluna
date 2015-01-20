/*
 * Copyright (C) 2010 - 2015 Eluna Lua Engine <http://emudevs.com/>
 * This program is free software licensed under GPL version 3
 * Please see the included DOCS/LICENSE.md for more information
 */

#ifndef _ITEM_HOOKS_H
#define _ITEM_HOOKS_H

#include "Hooks.h"
#include "HookHelpers.h"
#include "LuaEngine.h"
#include "ElunaBinding.h"
#include "ElunaIncludes.h"
#include "ElunaTemplate.h"

using namespace Hooks;

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

#endif // _ITEM_HOOKS_H
