/*
 * Copyright (C) 2010 - 2024 Eluna Lua Engine <https://elunaluaengine.github.io/>
 * This program is free software licensed under GPL version 3
 * Please see the included DOCS/LICENSE.md for more information
 */

#include "Hooks.h"
#include "HookHelpers.h"
#include "LuaEngine.h"
#include "BindingMap.h"
#include "ElunaTemplate.h"

using namespace Hooks;

#define START_HOOK(EVENT) \
    auto key = EventKey<BGEvents>(EVENT);\
    if (!BGEventBindings->HasBindingsFor(key))\
        return;

void Eluna::OnBGStart(BattleGround* bg, BattleGroundTypeId bgId, uint32 instanceId)
{
    START_HOOK(BG_EVENT_ON_START);
    HookPush(bg);
    HookPush(bgId);
    HookPush(instanceId);
    CallAllFunctions(BGEventBindings, key);
}

void Eluna::OnBGEnd(BattleGround* bg, BattleGroundTypeId bgId, uint32 instanceId, Team winner)
{
    START_HOOK(BG_EVENT_ON_END);
    HookPush(bg);
    HookPush(bgId);
    HookPush(instanceId);
    HookPush(winner);
    CallAllFunctions(BGEventBindings, key);
}

void Eluna::OnBGCreate(BattleGround* bg, BattleGroundTypeId bgId, uint32 instanceId)
{
    START_HOOK(BG_EVENT_ON_CREATE);
    HookPush(bg);
    HookPush(bgId);
    HookPush(instanceId);
    CallAllFunctions(BGEventBindings, key);
}

void Eluna::OnBGDestroy(BattleGround* bg, BattleGroundTypeId bgId, uint32 instanceId)
{
    START_HOOK(BG_EVENT_ON_PRE_DESTROY);
    HookPush(bg);
    HookPush(bgId);
    HookPush(instanceId);
    CallAllFunctions(BGEventBindings, key);
}
