/*
 * Copyright (C) 2010 - 2015 Eluna Lua Engine <http://emudevs.com/>
 * This program is free software licensed under GPL version 3
 * Please see the included DOCS/LICENSE.md for more information
 */

#ifndef _INSTANCE_HOOKS_H
#define _INSTANCE_HOOKS_H

#include "Hooks.h"
#include "HookHelpers.h"
#include "LuaEngine.h"
#include "ElunaBinding.h"
#include "ElunaIncludes.h"
#include "ElunaTemplate.h"
#include "ElunaInstanceAI.h"

using namespace Hooks;

void Eluna::OnInitialize(ElunaInstanceAI* ai)
{
    Map* map = ai->instance;

    if (!MapEventBindings->HasEvents(INSTANCE_EVENT_ON_INITIALIZE, map->GetId()) &&
        !InstanceEventBindings->HasEvents(INSTANCE_EVENT_ON_INITIALIZE, map->GetInstanceId()))
        return;

    LOCK_ELUNA;

    PushInstanceData(ai);
    CallAllFunctions(MapEventBindings, INSTANCE_EVENT_ON_INITIALIZE, map->GetId());

    PushInstanceData(ai);
    CallAllFunctions(InstanceEventBindings, INSTANCE_EVENT_ON_INITIALIZE, map->GetInstanceId());
}

void Eluna::OnLoad(ElunaInstanceAI* ai)
{
    Map* map = ai->instance;

    if (!MapEventBindings->HasEvents(INSTANCE_EVENT_ON_LOAD, map->GetId()) &&
        !InstanceEventBindings->HasEvents(INSTANCE_EVENT_ON_LOAD, map->GetInstanceId()))
        return;

    LOCK_ELUNA;

    PushInstanceData(ai);
    CallAllFunctions(MapEventBindings, INSTANCE_EVENT_ON_LOAD, map->GetId());

    PushInstanceData(ai);
    CallAllFunctions(InstanceEventBindings, INSTANCE_EVENT_ON_LOAD, map->GetInstanceId());
}

void Eluna::OnUpdateInstance(ElunaInstanceAI* ai, uint32 diff)
{
    Map* map = ai->instance;

    if (!MapEventBindings->HasEvents(INSTANCE_EVENT_ON_UPDATE, map->GetId()) &&
        !InstanceEventBindings->HasEvents(INSTANCE_EVENT_ON_UPDATE, map->GetInstanceId()))
        return;

    LOCK_ELUNA;

    PushInstanceData(ai);
    Push(diff);
    CallAllFunctions(MapEventBindings, INSTANCE_EVENT_ON_UPDATE, map->GetId());

    PushInstanceData(ai);
    Push(diff);
    CallAllFunctions(InstanceEventBindings, INSTANCE_EVENT_ON_UPDATE, map->GetInstanceId());
}

void Eluna::OnPlayerEnterInstance(ElunaInstanceAI* ai, Player* player)
{
    Map* map = ai->instance;

    if (!MapEventBindings->HasEvents(INSTANCE_EVENT_ON_PLAYER_ENTER, map->GetId()) &&
        !InstanceEventBindings->HasEvents(INSTANCE_EVENT_ON_PLAYER_ENTER, map->GetInstanceId()))
        return;

    LOCK_ELUNA;

    PushInstanceData(ai);
    Push(player);
    CallAllFunctions(MapEventBindings, INSTANCE_EVENT_ON_PLAYER_ENTER, map->GetId());

    PushInstanceData(ai);
    Push(player);
    CallAllFunctions(InstanceEventBindings, INSTANCE_EVENT_ON_PLAYER_ENTER, map->GetInstanceId());
}

void Eluna::OnCreatureCreate(ElunaInstanceAI* ai, Creature* creature)
{
    Map* map = ai->instance;

    if (!MapEventBindings->HasEvents(INSTANCE_EVENT_ON_CREATURE_CREATE, map->GetId()) &&
        !InstanceEventBindings->HasEvents(INSTANCE_EVENT_ON_CREATURE_CREATE, map->GetInstanceId()))
        return;

    LOCK_ELUNA;

    PushInstanceData(ai);
    Push(creature);
    CallAllFunctions(MapEventBindings, INSTANCE_EVENT_ON_CREATURE_CREATE, map->GetId());

    PushInstanceData(ai);
    Push(creature);
    CallAllFunctions(InstanceEventBindings, INSTANCE_EVENT_ON_CREATURE_CREATE, map->GetInstanceId());
}

void Eluna::OnGameObjectCreate(ElunaInstanceAI* ai, GameObject* gameobject)
{
    Map* map = ai->instance;

    if (!MapEventBindings->HasEvents(INSTANCE_EVENT_ON_GAMEOBJECT_CREATE, map->GetId()) &&
        !InstanceEventBindings->HasEvents(INSTANCE_EVENT_ON_GAMEOBJECT_CREATE, map->GetInstanceId()))
        return;

    LOCK_ELUNA;

    PushInstanceData(ai);
    Push(gameobject);
    CallAllFunctions(MapEventBindings, INSTANCE_EVENT_ON_GAMEOBJECT_CREATE, map->GetId());

    PushInstanceData(ai);
    Push(gameobject);
    CallAllFunctions(InstanceEventBindings, INSTANCE_EVENT_ON_GAMEOBJECT_CREATE, map->GetInstanceId());
}

bool Eluna::OnCheckEncounterInProgress(ElunaInstanceAI* ai)
{
    Map* map = ai->instance;

    if (!MapEventBindings->HasEvents(INSTANCE_EVENT_ON_CHECK_ENCOUNTER_IN_PROGRESS, map->GetId()) &&
        !InstanceEventBindings->HasEvents(INSTANCE_EVENT_ON_CHECK_ENCOUNTER_IN_PROGRESS, map->GetInstanceId()))
        return false;

    LOCK_ELUNA;
    bool ret1, ret2;

    PushInstanceData(ai);
    ret1 = CallAllFunctionsBool(MapEventBindings, INSTANCE_EVENT_ON_CHECK_ENCOUNTER_IN_PROGRESS, map->GetId());

    PushInstanceData(ai);
    ret2 = CallAllFunctionsBool(InstanceEventBindings, INSTANCE_EVENT_ON_CHECK_ENCOUNTER_IN_PROGRESS, map->GetInstanceId());

    return ret1 || ret2;
}

#endif // _INSTANCE_HOOKS_H
