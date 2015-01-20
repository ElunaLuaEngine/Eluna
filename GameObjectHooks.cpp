/*
 * Copyright (C) 2010 - 2015 Eluna Lua Engine <http://emudevs.com/>
 * This program is free software licensed under GPL version 3
 * Please see the included DOCS/LICENSE.md for more information
 */

#ifndef _GAMEOBJECT_HOOKS_H
#define _GAMEOBJECT_HOOKS_H

#include "Hooks.h"
#include "HookHelpers.h"
#include "LuaEngine.h"
#include "ElunaBinding.h"
#include "ElunaIncludes.h"
#include "ElunaEventMgr.h"
#include "ElunaTemplate.h"

using namespace Hooks;

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

bool Eluna::OnGameObjectUse(Player* pPlayer, GameObject* pGameObject)
{
    if (!GameObjectEventBindings->HasEvents(GAMEOBJECT_EVENT_ON_USE, pGameObject->GetEntry()))
        return false;

    LOCK_ELUNA;
    Push(pGameObject);
    Push(pPlayer);
    return CallAllFunctionsBool(GameObjectEventBindings, GAMEOBJECT_EVENT_ON_USE, pGameObject->GetEntry());
}

#endif // _GAMEOBJECT_HOOKS_H
