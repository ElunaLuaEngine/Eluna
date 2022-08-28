/*
 * Copyright (C) 2010 - 2016 Eluna Lua Engine <http://emudevs.com/>
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
    if (!IsEnabled())\
        return;\
    auto key = EventKey<GroupEvents>(EVENT);\
    if (!GroupEventBindings->HasBindingsFor(key))\
        return;

void Eluna::OnAddMember(Group* group, ObjectGuid guid)
{
    START_HOOK(GROUP_EVENT_ON_MEMBER_ADD);
    HookPush(group);
    HookPush(guid);
    CallAllFunctions(GroupEventBindings, key);
}

void Eluna::OnInviteMember(Group* group, ObjectGuid guid)
{
    START_HOOK(GROUP_EVENT_ON_MEMBER_INVITE);
    HookPush(group);
    HookPush(guid);
    CallAllFunctions(GroupEventBindings, key);
}

void Eluna::OnRemoveMember(Group* group, ObjectGuid guid, uint8 method)
{
    START_HOOK(GROUP_EVENT_ON_MEMBER_REMOVE);
    HookPush(group);
    HookPush(guid);
    HookPush(method);
    CallAllFunctions(GroupEventBindings, key);
}

void Eluna::OnChangeLeader(Group* group, ObjectGuid newLeaderGuid, ObjectGuid oldLeaderGuid)
{
    START_HOOK(GROUP_EVENT_ON_LEADER_CHANGE);
    HookPush(group);
    HookPush(newLeaderGuid);
    HookPush(oldLeaderGuid);
    CallAllFunctions(GroupEventBindings, key);
}

void Eluna::OnDisband(Group* group)
{
    START_HOOK(GROUP_EVENT_ON_DISBAND);
    HookPush(group);
    CallAllFunctions(GroupEventBindings, key);
}

void Eluna::OnCreate(Group* group, ObjectGuid leaderGuid, GroupType groupType)
{
    START_HOOK(GROUP_EVENT_ON_CREATE);
    HookPush(group);
    HookPush(leaderGuid);
    HookPush(groupType);
    CallAllFunctions(GroupEventBindings, key);
}
