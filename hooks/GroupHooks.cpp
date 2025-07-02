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
    auto binding = GetBinding<EventKey<GroupEvents>>(REGTYPE_GROUP);\
    auto key = EventKey<GroupEvents>(EVENT);\
    if (!binding->HasBindingsFor(key))\
        return;

#define START_HOOK_WITH_RETVAL(EVENT, RETVAL) \
    auto binding = GetBinding<EventKey<GroupEvents>>(REGTYPE_GROUP);\
    auto key = EventKey<GroupEvents>(EVENT);\
    if (!binding->HasBindingsFor(key))\
        return RETVAL;

void Eluna::OnAddMember(Group* group, ObjectGuid guid)
{
    START_HOOK(GROUP_EVENT_ON_MEMBER_ADD);
    HookPush(group);
    HookPush(guid);
    CallAllFunctions(binding, key);
}

void Eluna::OnInviteMember(Group* group, ObjectGuid guid)
{
    START_HOOK(GROUP_EVENT_ON_MEMBER_INVITE);
    HookPush(group);
    HookPush(guid);
    CallAllFunctions(binding, key);
}

void Eluna::OnRemoveMember(Group* group, ObjectGuid guid, uint8 method)
{
    START_HOOK(GROUP_EVENT_ON_MEMBER_REMOVE);
    HookPush(group);
    HookPush(guid);
    HookPush(method);
    CallAllFunctions(binding, key);
}

void Eluna::OnChangeLeader(Group* group, ObjectGuid newLeaderGuid, ObjectGuid oldLeaderGuid)
{
    START_HOOK(GROUP_EVENT_ON_LEADER_CHANGE);
    HookPush(group);
    HookPush(newLeaderGuid);
    HookPush(oldLeaderGuid);
    CallAllFunctions(binding, key);
}

void Eluna::OnDisband(Group* group)
{
    START_HOOK(GROUP_EVENT_ON_DISBAND);
    HookPush(group);
    CallAllFunctions(binding, key);
}

void Eluna::OnCreate(Group* group, ObjectGuid leaderGuid, GroupType groupType)
{
    START_HOOK(GROUP_EVENT_ON_CREATE);
    HookPush(group);
    HookPush(leaderGuid);
    HookPush(groupType);
    CallAllFunctions(binding, key);
}

bool Eluna::OnMemberAccept(Group* group, Player* player)
{
    START_HOOK_WITH_RETVAL(GROUP_EVENT_ON_MEMBER_ACCEPT, true);
    HookPush(group);
    HookPush(player);
    return CallAllFunctionsBool(binding, key, true);
}
