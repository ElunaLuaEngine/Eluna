/*
 * Copyright (C) 2010 - 2015 Eluna Lua Engine <http://emudevs.com/>
 * This program is free software licensed under GPL version 3
 * Please see the included DOCS/LICENSE.md for more information
 */

#ifndef _GROUP_HOOKS_H
#define _GROUP_HOOKS_H

#include "Hooks.h"
#include "HookHelpers.h"
#include "LuaEngine.h"
#include "ElunaBinding.h"
#include "ElunaTemplate.h"

using namespace Hooks;

void Eluna::OnAddMember(Group* group, uint64 guid)
{
    if (!GroupEventBindings->HasEvents(GROUP_EVENT_ON_MEMBER_ADD))
        return;

    LOCK_ELUNA;
    Push(group);
    Push(guid);
    CallAllFunctions(GroupEventBindings, GROUP_EVENT_ON_MEMBER_ADD);
}

void Eluna::OnInviteMember(Group* group, uint64 guid)
{
    if (!GroupEventBindings->HasEvents(GROUP_EVENT_ON_MEMBER_INVITE))
        return;

    LOCK_ELUNA;
    Push(group);
    Push(guid);
    CallAllFunctions(GroupEventBindings, GROUP_EVENT_ON_MEMBER_INVITE);
}

void Eluna::OnRemoveMember(Group* group, uint64 guid, uint8 method)
{
    if (!GroupEventBindings->HasEvents(GROUP_EVENT_ON_MEMBER_REMOVE))
        return;

    LOCK_ELUNA;
    Push(group);
    Push(guid);
    Push(method);
    CallAllFunctions(GroupEventBindings, GROUP_EVENT_ON_MEMBER_REMOVE);
}

void Eluna::OnChangeLeader(Group* group, uint64 newLeaderGuid, uint64 oldLeaderGuid)
{
    if (!GroupEventBindings->HasEvents(GROUP_EVENT_ON_LEADER_CHANGE))
        return;

    LOCK_ELUNA;
    Push(group);
    Push(newLeaderGuid);
    Push(oldLeaderGuid);
    CallAllFunctions(GroupEventBindings, GROUP_EVENT_ON_LEADER_CHANGE);
}

void Eluna::OnDisband(Group* group)
{
    if (!GroupEventBindings->HasEvents(GROUP_EVENT_ON_DISBAND))
        return;

    LOCK_ELUNA;
    Push(group);
    CallAllFunctions(GroupEventBindings, GROUP_EVENT_ON_DISBAND);
}

void Eluna::OnCreate(Group* group, uint64 leaderGuid, GroupType groupType)
{
    if (!GroupEventBindings->HasEvents(GROUP_EVENT_ON_CREATE))
        return;

    LOCK_ELUNA;
    Push(group);
    Push(leaderGuid);
    Push(groupType);
    CallAllFunctions(GroupEventBindings, GROUP_EVENT_ON_CREATE);
}

#endif // _GROUP_HOOKS_H
