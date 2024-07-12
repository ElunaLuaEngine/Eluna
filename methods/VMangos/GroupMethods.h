/*
* Copyright (C) 2010 - 2024 Eluna Lua Engine <https://elunaluaengine.github.io/>
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
    int IsLeader(Eluna* E, Group* group)
    {
        ObjectGuid guid = E->CHECKVAL<ObjectGuid>(2);
        E->Push(group->IsLeader(guid));
        return 1;
    }

    /**
     * Returns 'true' if the [Group] is full
     *
     * @return bool isFull
     */
    int IsFull(Eluna* E, Group* group)
    {
        E->Push(group->IsFull());
        return 1;
    }
    
    /**
     * Returns 'true' if the [Group] is a raid [Group]
     *
     * @return bool isRaid
     */
    int IsRaidGroup(Eluna* E, Group* group)
    {
        E->Push(group->isRaidGroup());
        return 1;
    }

    /**
     * Returns 'true' if the [Group] is a battleground [Group]
     *
     * @return bool isBG
     */
    int IsBGGroup(Eluna* E, Group* group)
    {
        E->Push(group->isBGGroup());
        return 1;
    }

    /**
     * Returns 'true' if the [Player] is a member of this [Group]
     *
     * @param ObjectGuid guid : guid of a player
     * @return bool isMember
     */
    int IsMember(Eluna* E, Group* group)
    {
        ObjectGuid guid = E->CHECKVAL<ObjectGuid>(2);
        E->Push(group->IsMember(guid));
        return 1;
    }

    /**
     * Returns 'true' if the [Player] is an assistant of this [Group]
     *
     * @param ObjectGuid guid : guid of a player
     * @return bool isAssistant
     */
    int IsAssistant(Eluna* E, Group* group)
    {
        ObjectGuid guid = E->CHECKVAL<ObjectGuid>(2);
        E->Push(group->IsAssistant(guid));
        return 1;
    }

    /**
     * Returns 'true' if the [Player]s are in the same subgroup in this [Group]
     *
     * @param [Player] player1 : first [Player] to check
     * @param [Player] player2 : second [Player] to check
     * @return bool sameSubGroup
     */
    int SameSubGroup(Eluna* E, Group* group)
    {
        Player* player1 = E->CHECKOBJ<Player>(2);
        Player* player2 = E->CHECKOBJ<Player>(3);
        E->Push(group->SameSubGroup(player1, player2));
        return 1;
    }

    /**
     * Returns 'true' if the subgroup has free slots in this [Group]
     *
     * @param uint8 subGroup : subGroup ID to check
     * @return bool hasFreeSlot
     */
    int HasFreeSlotSubGroup(Eluna* E, Group* group)
    {
        uint8 subGroup = E->CHECKVAL<uint8>(2);

        if (subGroup >= MAX_RAID_SUBGROUPS)
        {
            luaL_argerror(E->L, 2, "valid subGroup ID expected");
            return 0;
        }

        E->Push(group->HasFreeSlotSubGroup(subGroup));
        return 1;
    }

    /**
     * Adds a new member to the [Group]
     *
     * @param [Player] player : [Player] to add to the group
     * @return bool added : true if member was added
     */
    int AddMember(Eluna* E, Group* group)
    {
        Player* player = E->CHECKOBJ<Player>(2);

        if (player->GetGroup() || !group->IsCreated() || group->IsFull())
        {
            E->Push(false);
            return 1;
        }

        if (player->GetGroupInvite())
            player->UninviteFromGroup();

        bool success = group->AddMember(player->GetObjectGuid(), player->GetName());

        E->Push(success);
        return 1;
    }

    /**
     * Returns a table with the [Player]s in this [Group]
     *
     * @return table groupPlayers : table of [Player]s
     */
    int GetMembers(Eluna* E, Group* group)
    {
        lua_newtable(E->L);
        int tbl = lua_gettop(E->L);
        uint32 i = 0;

        for (GroupReference* itr = group->GetFirstMember(); itr; itr = itr->next())
        {
            Player* member = itr->getSource();

            if (!member || !member->GetSession())
                continue;

            E->Push(member);
            lua_rawseti(E->L, tbl, ++i);
        }

        lua_settop(E->L, tbl); // push table to top of stack
        return 1;
    }

    /**
     * Returns [Group] leader GUID
     *
     * @return ObjectGuid leaderGUID
     */
    int GetLeaderGUID(Eluna* E, Group* group)
    {
        E->Push(group->GetLeaderGuid());
        return 1;
    }

    /**
     * Returns the [Group]'s GUID
     *
     * @return ObjectGuid groupGUID
     */
    int GetGUID(Eluna* E, Group* group)
    {
        E->Push(group->GetId());
        return 1;
    }

    /**
     * Returns a [Group] member's GUID by their name
     *
     * @param string name : the [Player]'s name
     * @return ObjectGuid memberGUID
     */
    int GetMemberGUID(Eluna* E, Group* group)
    {
        const char* name = E->CHECKVAL<const char*>(2);

        E->Push(group->GetMemberGuid(name));
        return 1;
    }

    /**
     * Returns the member count of this [Group]
     *
     * @return uint32 memberCount
     */
    int GetMembersCount(Eluna* E, Group* group)
    {
        E->Push(group->GetMembersCount());
        return 1;
    }

    /**
     * Returns the [Player]'s subgroup ID of this [Group]
     *
     * @param ObjectGuid guid : guid of the player
     * @return uint8 subGroupID : a valid subgroup ID or MAX_RAID_SUBGROUPS+1
     */
    int GetMemberGroup(Eluna* E, Group* group)
    {
        ObjectGuid guid = E->CHECKVAL<ObjectGuid>(2);
        E->Push(group->GetMemberGroup(guid));
        return 1;
    }

    /**
     * Sets the leader of this [Group]
     *
     * @param ObjectGuid guid : guid of the new leader
     */
    int SetLeader(Eluna* E, Group* group)
    {
        ObjectGuid guid = E->CHECKVAL<ObjectGuid>(2);
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
    int SendPacket(Eluna* E, Group* group)
    {
        WorldPacket* data = E->CHECKOBJ<WorldPacket>(2);
        bool ignorePlayersInBg = E->CHECKVAL<bool>(3);
        ObjectGuid ignore = E->CHECKVAL<ObjectGuid>(4);

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
    int RemoveMember(Eluna* E, Group* group)
    {
        ObjectGuid guid = E->CHECKVAL<ObjectGuid>(2);
        uint32 method = E->CHECKVAL<uint32>(3, 0);

        E->Push(group->RemoveMember(guid, method));
        return 1;
    }

    /**
     * Disbands this [Group]
     *
     */
    int Disband(Eluna* /*E*/, Group* group)
    {
        group->Disband();
        return 0;
    }

    /**
     * Converts this [Group] to a raid [Group]
     *
     */
    int ConvertToRaid(Eluna* /*E*/, Group* group)
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
    int SetMembersGroup(Eluna* E, Group* group)
    {
        ObjectGuid guid = E->CHECKVAL<ObjectGuid>(2);
        uint8 subGroup = E->CHECKVAL<uint8>(3);

        if (subGroup >= MAX_RAID_SUBGROUPS)
        {
            luaL_argerror(E->L, 3, "valid subGroup ID expected");
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
    int SetTargetIcon(Eluna* E, Group* group)
    {
        uint8 icon = E->CHECKVAL<uint8>(2);
        ObjectGuid target = E->CHECKVAL<ObjectGuid>(3);
        ObjectGuid setter = E->CHECKVAL<ObjectGuid>(4, ObjectGuid());

        if (icon >= TARGETICONCOUNT)
            return luaL_argerror(E->L, 2, "valid target icon expected");

        group->SetTargetIcon(icon, target);
        return 0;
    }
    
    ElunaRegister<Group> GroupMethods[] =
    {
        // Getters
        { "GetMembers", &LuaGroup::GetMembers, METHOD_REG_WORLD }, // World state method only in multistate
        { "GetLeaderGUID", &LuaGroup::GetLeaderGUID },
        { "GetGUID", &LuaGroup::GetGUID },
        { "GetMemberGroup", &LuaGroup::GetMemberGroup },
        { "GetMemberGUID", &LuaGroup::GetMemberGUID },
        { "GetMembersCount", &LuaGroup::GetMembersCount },

        // Setters
        { "SetLeader", &LuaGroup::SetLeader, METHOD_REG_WORLD }, // World state method only in multistate
        { "SetMembersGroup", &LuaGroup::SetMembersGroup, METHOD_REG_WORLD }, // World state method only in multistate
        { "SetTargetIcon", &LuaGroup::SetTargetIcon, METHOD_REG_WORLD }, // World state method only in multistate

        // Boolean
        { "IsLeader", &LuaGroup::IsLeader },
        { "AddMember", &LuaGroup::AddMember, METHOD_REG_WORLD }, // World state method only in multistate
        { "RemoveMember", &LuaGroup::RemoveMember, METHOD_REG_WORLD }, // World state method only in multistate
        { "Disband", &LuaGroup::Disband, METHOD_REG_WORLD }, // World state method only in multistate
        { "IsFull", &LuaGroup::IsFull },
        { "IsRaidGroup", &LuaGroup::IsRaidGroup },
        { "IsBGGroup", &LuaGroup::IsBGGroup },
        { "IsMember", &LuaGroup::IsMember },
        { "IsAssistant", &LuaGroup::IsAssistant },
        { "SameSubGroup", &LuaGroup::SameSubGroup },
        { "HasFreeSlotSubGroup", &LuaGroup::HasFreeSlotSubGroup },

        // Other
        { "SendPacket", &LuaGroup::SendPacket },
        { "ConvertToRaid", &LuaGroup::ConvertToRaid, METHOD_REG_WORLD }, // World state method only in multistate

        // Not implemented methods
        { "IsLFGGroup", nullptr, METHOD_REG_NONE },       // not implemented
        { "IsBFGroup", nullptr, METHOD_REG_NONE  },       // not implemented
        { "ConvertToLFG", nullptr, METHOD_REG_NONE  },    // not implemented
        { "GetMemberFlags", nullptr, METHOD_REG_NONE  },  // not implemented
        { "SetMemberFlag", nullptr, METHOD_REG_NONE  },   // not implemented

        { NULL, NULL, METHOD_REG_NONE }
    };
};

#endif
