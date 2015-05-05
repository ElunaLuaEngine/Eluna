/*
 * Copyright (C) 2010 - 2015 Eluna Lua Engine <http://emudevs.com/>
 * This program is free software licensed under GPL version 3
 * Please see the included DOCS/LICENSE.md for more information
 */

#include "Hooks.h"
#include "HookHelpers.h"
#include "LuaEngine.h"
#include "ElunaBinding.h"
#include "ElunaTemplate.h"

using namespace Hooks;

#define START_HOOK(EVENT) \
    auto key = EventKey<BGEvents>(EVENT);\
    if (!BGEventBindings->HasEvents(key))\
        return;\
    LOCK_ELUNA

void Eluna::OnBGStart(BattleGround* bg, BattleGroundTypeId bgId, uint32 instanceId)
{
    START_HOOK(BG_EVENT_ON_START);
    Push(bg);
    Push(bgId);
    Push(instanceId);
    CallAllFunctions(BGEventBindings, key);
}

void Eluna::OnBGEnd(BattleGround* bg, BattleGroundTypeId bgId, uint32 instanceId, Team winner)
{
    START_HOOK(BG_EVENT_ON_END);
    Push(bg);
    Push(bgId);
    Push(instanceId);
    Push(winner);
    CallAllFunctions(BGEventBindings, key);
}

void Eluna::OnBGCreate(BattleGround* bg, BattleGroundTypeId bgId, uint32 instanceId)
{
    START_HOOK(BG_EVENT_ON_CREATE);
    Push(bg);
    Push(bgId);
    Push(instanceId);
    CallAllFunctions(BGEventBindings, key);
}

void Eluna::OnBGDestroy(BattleGround* bg, BattleGroundTypeId bgId, uint32 instanceId)
{
    START_HOOK(BG_EVENT_ON_PRE_DESTROY);
    Push(bg);
    Push(bgId);
    Push(instanceId);
    CallAllFunctions(BGEventBindings, key);
}
