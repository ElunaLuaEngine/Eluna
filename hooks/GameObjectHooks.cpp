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
#include "ElunaEventMgr.h"
#include "ElunaTemplate.h"

using namespace Hooks;

#define START_HOOK(EVENT, ENTRY) \
    auto binding = GetBinding<EntryKey<GameObjectEvents>>(REGTYPE_GAMEOBJECT);\
    auto key = EntryKey<GameObjectEvents>(EVENT, ENTRY);\
    if (!binding->HasBindingsFor(key))\
        return;

#define START_HOOK_WITH_RETVAL(EVENT, ENTRY, RETVAL) \
    auto binding = GetBinding<EntryKey<GameObjectEvents>>(REGTYPE_GAMEOBJECT);\
    auto key = EntryKey<GameObjectEvents>(EVENT, ENTRY);\
    if (!binding->HasBindingsFor(key))\
        return RETVAL;

void Eluna::OnDummyEffect(WorldObject* pCaster, uint32 spellId, SpellEffIndex effIndex, GameObject* pTarget)
{
    START_HOOK(GAMEOBJECT_EVENT_ON_DUMMY_EFFECT, pTarget->GetEntry());
    HookPush(pCaster);
    HookPush(spellId);
    HookPush(effIndex);
    HookPush(pTarget);
    CallAllFunctions(binding, key);
}

void Eluna::UpdateAI(GameObject* pGameObject, uint32 diff)
{
    START_HOOK(GAMEOBJECT_EVENT_ON_AIUPDATE, pGameObject->GetEntry());
    HookPush(pGameObject);
    HookPush(diff);
    CallAllFunctions(binding, key);
}

bool Eluna::OnQuestAccept(Player* pPlayer, GameObject* pGameObject, Quest const* pQuest)
{
    START_HOOK_WITH_RETVAL(GAMEOBJECT_EVENT_ON_QUEST_ACCEPT, pGameObject->GetEntry(), false);
    HookPush(pPlayer);
    HookPush(pGameObject);
    HookPush(pQuest);
    return CallAllFunctionsBool(binding, key);
}

bool Eluna::OnQuestReward(Player* pPlayer, GameObject* pGameObject, Quest const* pQuest, uint32 opt)
{
    START_HOOK_WITH_RETVAL(GAMEOBJECT_EVENT_ON_QUEST_REWARD, pGameObject->GetEntry(), false);
    HookPush(pPlayer);
    HookPush(pGameObject);
    HookPush(pQuest);
    HookPush(opt);
    return CallAllFunctionsBool(binding, key);
}

void Eluna::GetDialogStatus(const Player* pPlayer, const GameObject* pGameObject)
{
    START_HOOK(GAMEOBJECT_EVENT_ON_DIALOG_STATUS, pGameObject->GetEntry());
    HookPush(pPlayer);
    HookPush(pGameObject);
    CallAllFunctions(binding, key);
}

#if ELUNA_EXPANSION >= EXP_WOTLK
void Eluna::OnDestroyed(GameObject* pGameObject, WorldObject* attacker)
{
    START_HOOK(GAMEOBJECT_EVENT_ON_DESTROYED, pGameObject->GetEntry());
    HookPush(pGameObject);
    HookPush(attacker);
    CallAllFunctions(binding, key);
}

void Eluna::OnDamaged(GameObject* pGameObject, WorldObject* attacker)
{
    START_HOOK(GAMEOBJECT_EVENT_ON_DAMAGED, pGameObject->GetEntry());
    HookPush(pGameObject);
    HookPush(attacker);
    CallAllFunctions(binding, key);
}
#endif

void Eluna::OnLootStateChanged(GameObject* pGameObject, uint32 state)
{
    START_HOOK(GAMEOBJECT_EVENT_ON_LOOT_STATE_CHANGE, pGameObject->GetEntry());
    HookPush(pGameObject);
    HookPush(state);
    CallAllFunctions(binding, key);
}

void Eluna::OnGameObjectStateChanged(GameObject* pGameObject, uint32 state)
{
    START_HOOK(GAMEOBJECT_EVENT_ON_GO_STATE_CHANGED, pGameObject->GetEntry());
    HookPush(pGameObject);
    HookPush(state);
    CallAllFunctions(binding, key);
}

void Eluna::OnSpawn(GameObject* pGameObject)
{
    START_HOOK(GAMEOBJECT_EVENT_ON_SPAWN, pGameObject->GetEntry());
    HookPush(pGameObject);
    CallAllFunctions(binding, key);
}

void Eluna::OnAddToWorld(GameObject* pGameObject)
{
    START_HOOK(GAMEOBJECT_EVENT_ON_ADD, pGameObject->GetEntry());
    HookPush(pGameObject);
    CallAllFunctions(binding, key);
}

void Eluna::OnRemoveFromWorld(GameObject* pGameObject)
{
    START_HOOK(GAMEOBJECT_EVENT_ON_REMOVE, pGameObject->GetEntry());
    HookPush(pGameObject);
    CallAllFunctions(binding, key);
}

bool Eluna::OnGameObjectUse(Player* pPlayer, GameObject* pGameObject)
{
    START_HOOK_WITH_RETVAL(GAMEOBJECT_EVENT_ON_USE, pGameObject->GetEntry(), false);
    HookPush(pGameObject);
    HookPush(pPlayer);
    return CallAllFunctionsBool(binding, key);
}
