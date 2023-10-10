/*
* Copyright (C) 2010 - 2016 Eluna Lua Engine <http://emudevs.com/>
* This program is free software licensed under GPL version 3
* Please see the included DOCS/LICENSE.md for more information
*/

#ifndef GROUPMETHODS_H
#define GROUPMETHODS_H

/***
 * Inherits all methods from: none
 */
namespace LuaGroup
{
    /**
     * Returns 'true' if the [Player] is the [Group] leader
     *
     * @param ObjectGuid guid : guid of a possible leader
     * @return bool isLeader
     */
    int IsLeader(lua_State* L, Group* group)
    {
        ObjectGuid guid = Eluna::CHECKVAL<ObjectGuid>(L, 2);
        Eluna::Push(L, group->IsLeader(guid));
        return 1;
    }

    /**
     * Returns 'true' if the [Group] is full
     *
     * @return bool isFull
     */
    int IsFull(lua_State* L, Group* group)
    {
        Eluna::Push(L, group->IsFull());
        return 1;
    }

    /**
     * Returns 'true' if the [Group] is a LFG group
     *
     * @return bool isLFGGroup
     */
    int IsLFGGroup(lua_State* L, Group* group)
    {
        Eluna::Push(L, group->isLFGGroup());
        return 1;
    }
    
    /**
     * Returns 'true' if the [Group] is a raid [Group]
     *
     * @return bool isRaid
     */
    int IsRaidGroup(lua_State* L, Group* group)
    {
        Eluna::Push(L, group->isRaidGroup());
        return 1;
    }

    /**
     * Returns 'true' if the [Group] is a battleground [Group]
     *
     * @return bool isBG
     */
    int IsBGGroup(lua_State* L, Group* group)
    {
        Eluna::Push(L, group->isBGGroup());
        return 1;
    }

    /**
     * Returns 'true' if the [Player] is a member of this [Group]
     *
     * @param ObjectGuid guid : guid of a player
     * @return bool isMember
     */
    int IsMember(lua_State* L, Group* group)
    {
        ObjectGuid guid = Eluna::CHECKVAL<ObjectGuid>(L, 2);
        Eluna::Push(L, group->IsMember(guid));
        return 1;
    }

    /**
     * Returns 'true' if the [Player] is an assistant of this [Group]
     *
     * @param ObjectGuid guid : guid of a player
     * @return bool isAssistant
     */
    int IsAssistant(lua_State* L, Group* group)
    {
        ObjectGuid guid = Eluna::CHECKVAL<ObjectGuid>(L, 2);
        Eluna::Push(L, group->IsAssistant(guid));
        return 1;
    }

    /**
     * Returns 'true' if the [Player]s are in the same subgroup in this [Group]
     *
     * @param [Player] player1 : first [Player] to check
     * @param [Player] player2 : second [Player] to check
     * @return bool sameSubGroup
     */
    int SameSubGroup(lua_State* L, Group* group)
    {
        Player* player1 = Eluna::CHECKOBJ<Player>(L, 2);
        Player* player2 = Eluna::CHECKOBJ<Player>(L, 3);
        Eluna::Push(L, group->SameSubGroup(player1, player2));
        return 1;
    }

    /**
     * Returns 'true' if the subgroup has free slots in this [Group]
     *
     * @param uint8 subGroup : subGroup ID to check
     * @return bool hasFreeSlot
     */
    int HasFreeSlotSubGroup(lua_State* L, Group* group)
    {
        uint8 subGroup = Eluna::CHECKVAL<uint8>(L, 2);

        if (subGroup >= MAX_RAID_SUBGROUPS)
        {
            luaL_argerror(L, 2, "valid subGroup ID expected");
            return 0;
        }

        Eluna::Push(L, group->HasFreeSlotSubGroup(subGroup));
        return 1;
    }

    /**
     * Adds a new member to the [Group]
     *
     * @param [Player] player : [Player] to add to the group
     * @return bool added : true if member was added
     */
    int AddMember(lua_State* L, Group* group)
    {
        Player* player = Eluna::CHECKOBJ<Player>(L, 2);

        if (player->GetGroup() || !group->IsCreated() || group->IsFull())
        {
            Eluna::Push(L, false);
            return 1;
        }

        if (player->GetGroupInvite())
            player->UninviteFromGroup();

        bool success = group->AddMember(player);
        if (success)
            group->BroadcastGroupUpdate();

        Eluna::Push(L, success);
        return 1;
    }

    int IsBFGroup(lua_State* L, Group* group)
    {
        Eluna::Push(L, group->isBFGroup());
        return 1;
    }

    /**
     * Returns a table with the [Player]s in this [Group]
     *
     * @return table groupPlayers : table of [Player]s
     */
    int GetMembers(lua_State* L, Group* group)
    {
        lua_newtable(L);
        int tbl = lua_gettop(L);
        uint32 i = 0;

        for (GroupReference* itr = group->GetFirstMember(); itr; itr = itr->next())
        {
            Player* member = itr->GetSource();
            if (!member || !member->GetSession())
                continue;

            Eluna::Push(L, member);
            lua_rawseti(L, tbl, ++i);
        }

        lua_settop(L, tbl); // push table to top of stack
        return 1;
    }

    /**
     * Returns [Group] leader GUID
     *
     * @return ObjectGuid leaderGUID
     */
    int GetLeaderGUID(lua_State* L, Group* group)
    {
        Eluna::Push(L, group->GetLeaderGUID());
        return 1;
    }

    /**
     * Returns the [Group]'s GUID
     *
     * @return ObjectGuid groupGUID
     */
    int GetGUID(lua_State* L, Group* group)
    {
        Eluna::Push(L, group->GET_GUID());
        return 1;
    }

    /**
     * Returns a [Group] member's GUID by their name
     *
     * @param string name : the [Player]'s name
     * @return ObjectGuid memberGUID
     */
    int GetMemberGUID(lua_State* L, Group* group)
    {
        const char* name = Eluna::CHECKVAL<const char*>(L, 2);
        Eluna::Push(L, group->GetMemberGUID(name));
        return 1;
    }

    /**
     * Returns the member count of this [Group]
     *
     * @return uint32 memberCount
     */
    int GetMembersCount(lua_State* L, Group* group)
    {
        Eluna::Push(L, group->GetMembersCount());
        return 1;
    }

    /**
     * Returns the [Player]'s subgroup ID of this [Group]
     *
     * @param ObjectGuid guid : guid of the player
     * @return uint8 subGroupID : a valid subgroup ID or MAX_RAID_SUBGROUPS+1
     */
    int GetMemberGroup(lua_State* L, Group* group)
    {
        ObjectGuid guid = Eluna::CHECKVAL<ObjectGuid>(L, 2);
        Eluna::Push(L, group->GetMemberGroup(guid));
        return 1;
    }

    /**
     * Sets the leader of this [Group]
     *
     * @param ObjectGuid guid : guid of the new leader
     */
    int SetLeader(lua_State* L, Group* group)
    {
        ObjectGuid guid = Eluna::CHECKVAL<ObjectGuid>(L, 2);
        group->ChangeLeader(guid);
        group->SendUpdate();
        return 0;
    }

    /**
     * Sends a specified [WorldPacket] to this [Group]
     *
     * @param [WorldPacket] packet : the [WorldPacket] to send
     * @param bool ignorePlayersInBg : ignores [Player]s in a battleground
     * @param ObjectGuid ignore : ignore a [Player] by their GUID
     */
    int SendPacket(lua_State* L, Group* group)
    {
        WorldPacket* data = Eluna::CHECKOBJ<WorldPacket>(L, 2);
        bool ignorePlayersInBg = Eluna::CHECKVAL<bool>(L, 3);
        ObjectGuid ignore = Eluna::CHECKVAL<ObjectGuid>(L, 4);

        group->BroadcastPacket(data, ignorePlayersInBg, -1, ignore);
        return 0;
    }

    /**
     * Removes a [Player] from this [Group] and returns 'true' if successful
     *
     * <pre>
     * enum RemoveMethod
     * {
     *     GROUP_REMOVEMETHOD_DEFAULT  = 0,
     *     GROUP_REMOVEMETHOD_KICK     = 1,
     *     GROUP_REMOVEMETHOD_LEAVE    = 2,
     *     GROUP_REMOVEMETHOD_KICK_LFG = 3
     * };
     * </pre>
     *
     * @param ObjectGuid guid : guid of the player to remove
     * @param [RemoveMethod] method : method used to remove the player
     * @return bool removed
     */
    int RemoveMember(lua_State* L, Group* group)
    {
        ObjectGuid guid = Eluna::CHECKVAL<ObjectGuid>(L, 2);
        uint32 method = Eluna::CHECKVAL<uint32>(L, 3, 0);

        Eluna::Push(L, group->RemoveMember(guid, (RemoveMethod)method));
        return 1;
    }

    /**
     * Disbands this [Group]
     *
     */
    int Disband(lua_State* /*L*/, Group* group)
    {
        group->Disband();
        return 0;
    }

    /**
     * Converts this [Group] to a raid [Group]
     *
     */
    int ConvertToRaid(lua_State* /*L*/, Group* group)
    {
        group->ConvertToRaid();
        return 0;
    }

    /**
     * Sets the member's subGroup
     *
     * @param ObjectGuid guid : guid of the player to move
     * @param uint8 groupID : the subGroup's ID
     */
    int SetMembersGroup(lua_State* L, Group* group)
    {
        ObjectGuid guid = Eluna::CHECKVAL<ObjectGuid>(L, 2);
        uint8 subGroup = Eluna::CHECKVAL<uint8>(L, 3);

        if (subGroup >= MAX_RAID_SUBGROUPS)
        {
            luaL_argerror(L, 3, "valid subGroup ID expected");
            return 0;
        }

        if (!group->HasFreeSlotSubGroup(subGroup))
            return 0;

        group->ChangeMembersGroup(guid, subGroup);
        return 0;
    }

    /**
     * Sets the target icon of an object for the [Group]
     *
     * @param uint8 icon : the icon (Skull, Square, etc)
     * @param ObjectGuid target : GUID of the icon target, 0 is to clear the icon
     * @param ObjectGuid setter : GUID of the icon setter
     */
    int SetTargetIcon(lua_State* L, Group* group)
    {
        uint8 icon = Eluna::CHECKVAL<uint8>(L, 2);
        ObjectGuid target = Eluna::CHECKVAL<ObjectGuid>(L, 3);
        ObjectGuid setter = Eluna::CHECKVAL<ObjectGuid>(L, 4, ObjectGuid());

        if (icon >= TARGET_ICONS_COUNT)
            return luaL_argerror(L, 2, "valid target icon expected");

        group->SetTargetIcon(icon, setter, target);
        return 0;
    }

    int ConvertToLFG(lua_State* /*L*/, Group* group)
    {
        group->ConvertToLFG();
        return 0;
    }
    
    ElunaRegister<Group> GroupMethods[] =
    {
        // Getters
        { "GetMembers", &LuaGroup::GetMembers },
        { "GetLeaderGUID", &LuaGroup::GetLeaderGUID },
        { "GetGUID", &LuaGroup::GetGUID },
        { "GetMemberGroup", &LuaGroup::GetMemberGroup },
        { "GetMemberGUID", &LuaGroup::GetMemberGUID },
        { "GetMembersCount", &LuaGroup::GetMembersCount },

        // Setters
        { "SetLeader", &LuaGroup::SetLeader },
        { "SetMembersGroup", &LuaGroup::SetMembersGroup },
        { "SetTargetIcon", &LuaGroup::SetTargetIcon },

        // Boolean
        { "IsLeader", &LuaGroup::IsLeader },
        { "AddMember", &LuaGroup::AddMember },
        { "RemoveMember", &LuaGroup::RemoveMember },
        { "Disband", &LuaGroup::Disband },
        { "IsFull", &LuaGroup::IsFull },
        { "IsLFGGroup", &LuaGroup::IsLFGGroup },
        { "IsRaidGroup", &LuaGroup::IsRaidGroup },
        { "IsBGGroup", &LuaGroup::IsBGGroup },
        { "IsBFGroup", &LuaGroup::IsBFGroup },
        { "IsMember", &LuaGroup::IsMember },
        { "IsAssistant", &LuaGroup::IsAssistant },
        { "SameSubGroup", &LuaGroup::SameSubGroup },
        { "HasFreeSlotSubGroup", &LuaGroup::HasFreeSlotSubGroup },

        // Other
        { "SendPacket", &LuaGroup::SendPacket },
        { "ConvertToLFG", &LuaGroup::ConvertToLFG },
        { "ConvertToRaid", &LuaGroup::ConvertToRaid },

        { NULL, NULL }
    };
};

#endif
