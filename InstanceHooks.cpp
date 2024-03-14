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
#include "ElunaInstanceAI.h"

using namespace Hooks;

#define START_HOOK(EVENT, AI) \
    auto mapKey = EntryKey<InstanceEvents>(EVENT, AI->instance->GetId());\
    auto instanceKey = EntryKey<InstanceEvents>(EVENT, AI->instance->GetInstanceId());\
    if (!MapEventBindings->HasBindingsFor(mapKey) && !InstanceEventBindings->HasBindingsFor(instanceKey))\
        return;\
    PushInstanceData(AI);\
    HookPush<Map>(AI->instance)

#define START_HOOK_WITH_RETVAL(EVENT, AI, RETVAL) \
    auto mapKey = EntryKey<InstanceEvents>(EVENT, AI->instance->GetId());\
    auto instanceKey = EntryKey<InstanceEvents>(EVENT, AI->instance->GetInstanceId());\
    if (!MapEventBindings->HasBindingsFor(mapKey) && !InstanceEventBindings->HasBindingsFor(instanceKey))\
        return RETVAL;\
    PushInstanceData(AI);\
    HookPush<Map>(AI->instance)

void Eluna::OnInitialize(ElunaInstanceAI* ai)
{
    START_HOOK(INSTANCE_EVENT_ON_INITIALIZE, ai);
    CallAllFunctions(MapEventBindings, InstanceEventBindings, mapKey, instanceKey);
}

void Eluna::OnLoad(ElunaInstanceAI* ai)
{
    START_HOOK(INSTANCE_EVENT_ON_LOAD, ai);
    CallAllFunctions(MapEventBindings, InstanceEventBindings, mapKey, instanceKey);
}

void Eluna::OnUpdateInstance(ElunaInstanceAI* ai, uint32 diff)
{
    START_HOOK(INSTANCE_EVENT_ON_UPDATE, ai);
    HookPush(diff);
    CallAllFunctions(MapEventBindings, InstanceEventBindings, mapKey, instanceKey);
}

void Eluna::OnPlayerEnterInstance(ElunaInstanceAI* ai, Player* player)
{
    START_HOOK(INSTANCE_EVENT_ON_PLAYER_ENTER, ai);
    HookPush(player);
    CallAllFunctions(MapEventBindings, InstanceEventBindings, mapKey, instanceKey);
}

void Eluna::OnCreatureCreate(ElunaInstanceAI* ai, Creature* creature)
{
    START_HOOK(INSTANCE_EVENT_ON_CREATURE_CREATE, ai);
    HookPush(creature);
    CallAllFunctions(MapEventBindings, InstanceEventBindings, mapKey, instanceKey);
}

void Eluna::OnGameObjectCreate(ElunaInstanceAI* ai, GameObject* gameobject)
{
    START_HOOK(INSTANCE_EVENT_ON_GAMEOBJECT_CREATE, ai);
    HookPush(gameobject);
    CallAllFunctions(MapEventBindings, InstanceEventBindings, mapKey, instanceKey);
}

bool Eluna::OnCheckEncounterInProgress(ElunaInstanceAI* ai)
{
    START_HOOK_WITH_RETVAL(INSTANCE_EVENT_ON_CHECK_ENCOUNTER_IN_PROGRESS, ai, false);
    return CallAllFunctionsBool(MapEventBindings, InstanceEventBindings, mapKey, instanceKey);
}
