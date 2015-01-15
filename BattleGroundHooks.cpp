/*
 * Copyright (C) 2010 - 2015 Eluna Lua Engine <http://emudevs.com/>
 * This program is free software licensed under GPL version 3
 * Please see the included DOCS/LICENSE.md for more information
 */

#ifndef _BATTLEGROUND_HOOKS_H
#define _BATTLEGROUND_HOOKS_H

#include "Hooks.h"
#include "HookHelpers.h"
#include "LuaEngine.h"
#include "ElunaBinding.h"
#include "ElunaTemplate.h"

using namespace Hooks;

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

#endif // _BATTLEGROUND_HOOKS_H
