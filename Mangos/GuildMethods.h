/*
* Copyright (C) 2010 - 2024 Eluna Lua Engine <https://elunaluaengine.github.io/>
* This program is free software licensed under GPL version 3
* Please see the included DOCS/LICENSE.md for more information
*/

#ifndef GUILDMETHODS_H
#define GUILDMETHODS_H

/***
 * Inherits all methods from: none
 */
namespace LuaGuild
{
    /**
     * Returns a table with the [Player]s in this [Guild]
     *
     * Only the players that are online and on some map.
     *
     * @return table guildPlayers : table of [Player]s
     */
    int GetMembers(Eluna* E, Guild* guild)
    {
        lua_newtable(E->L);
        int tbl = lua_gettop(E->L);
        uint32 i = 0;

#if defined(MANGOS)
        eObjectAccessor()DoForAllPlayers([&](Player* player)
        {
            if (player->IsInWorld() && player->GetGuildId() == guild->GetId())
            {
                E->Push(player);
                lua_rawseti(E->L, tbl, ++i);
            }
        });
#else
        {
#if defined TRINITY || AZEROTHCORE
            std::shared_lock<std::shared_mutex> lock(*HashMapHolder<Player>::GetLock());
#else
            HashMapHolder<Player>::ReadGuard g(HashMapHolder<Player>::GetLock());
#endif
            const HashMapHolder<Player>::MapType& m = eObjectAccessor()GetPlayers();
            for (HashMapHolder<Player>::MapType::const_iterator it = m.begin(); it != m.end(); ++it)
            {
                if (Player* player = it->second)
                {
                    if (player->IsInWorld() && player->GetGuildId() == guild->GetId())
                    {
                        E->Push(player);
                        lua_rawseti(E->L, tbl, ++i);
                    }
                }
            }
        }
#endif
        lua_settop(E->L, tbl); // push table to top of stack
        return 1;
    }

    /**
     * Returns the member count of this [Guild]
     *
     * @return uint32 memberCount
     */
    int GetMemberCount(Eluna* E, Guild* guild)
    {
#if defined TRINITY || AZEROTHCORE
        E->Push(guild->GetMemberCount());
#else
        E->Push(guild->GetMemberSize());
#endif
        return 1;
    }

    /**
     * Finds and returns the [Guild] leader by their GUID if logged in
     *
     * @return [Player] leader
     */
    int GetLeader(Eluna* E, Guild* guild)
    {
#if defined TRINITY || AZEROTHCORE
        E->Push(eObjectAccessor()FindPlayer(guild->GetLeaderGUID()));
#else
        E->Push(eObjectAccessor()FindPlayer(guild->GetLeaderGuid()));
#endif
        return 1;
    }

    /**
     * Returns [Guild] leader GUID
     *
     * @return ObjectGuid leaderGUID
     */
    int GetLeaderGUID(Eluna* E, Guild* guild)
    {
#if defined TRINITY || AZEROTHCORE
        E->Push(guild->GetLeaderGUID());
#else
        E->Push(guild->GetLeaderGuid());
#endif
        return 1;
    }

    /**
     * Returns the [Guild]s entry ID
     *
     * @return uint32 entryId
     */
    int GetId(Eluna* E, Guild* guild)
    {
        E->Push(guild->GetId());
        return 1;
    }

    /**
     * Returns the [Guild]s name
     *
     * @return string guildName
     */
    int GetName(Eluna* E, Guild* guild)
    {
        E->Push(guild->GetName());
        return 1;
    }

    /**
     * Returns the [Guild]s current Message Of The Day
     *
     * @return string guildMOTD
     */
    int GetMOTD(Eluna* E, Guild* guild)
    {
        E->Push(guild->GetMOTD());
        return 1;
    }

    /**
     * Returns the [Guild]s current info
     *
     * @return string guildInfo
     */
    int GetInfo(Eluna* E, Guild* guild)
    {
#if defined TRINITY || AZEROTHCORE
        E->Push(guild->GetInfo());
#else
        E->Push(guild->GetGINFO());
#endif
        return 1;
    }

#if defined(CLASSIC) || defined(TBC) || defined(WOTLK)
    /**
     * Sets the leader of this [Guild]
     *
     * @param [Player] leader : the [Player] leader to change
     */
    int SetLeader(Eluna* E, Guild* guild)
    {
        Player* player = E->CHECKOBJ<Player>(2);

#if defined TRINITY || AZEROTHCORE
        guild->HandleSetLeader(player->GetSession(), player->GetName());
#else
        guild->SetLeader(player->GET_GUID());
#endif
        return 0;
    }
#endif

#ifndef CLASSIC
    /**
     * Sets the information of the bank tab specified
     *
     * @param uint8 tabId : the ID of the tab specified
     * @param string info : the information to be set to the bank tab
     */
    int SetBankTabText(Eluna* E, Guild* guild)
    {
        uint8 tabId = E->CHECKVAL<uint8>(2);
        const char* text = E->CHECKVAL<const char*>(3);
#if defined TRINITY || AZEROTHCORE
        guild->SetBankTabText(tabId, text);
#else
        guild->SetGuildBankTabText(tabId, text);
#endif
        return 0;
    }
#endif

    // SendPacketToGuild(packet)
    /**
     * Sends a [WorldPacket] to all the [Player]s in the [Guild]
     *
     * @param [WorldPacket] packet : the [WorldPacket] to be sent to the [Player]s
     */
    int SendPacket(Eluna* E, Guild* guild)
    {
        WorldPacket* data = E->CHECKOBJ<WorldPacket>(2);

#ifdef CMANGOS
        guild->BroadcastPacket(*data);
#else
        guild->BroadcastPacket(data);
#endif
        return 0;
    }

    // SendPacketToRankedInGuild(packet, rankId)
    /**
     * Sends a [WorldPacket] to all the [Player]s at the specified rank in the [Guild]
     *
     * @param [WorldPacket] packet : the [WorldPacket] to be sent to the [Player]s
     * @param uint8 rankId : the rank ID
     */
    int SendPacketToRanked(Eluna* E, Guild* guild)
    {
        WorldPacket* data = E->CHECKOBJ<WorldPacket>(2);
        uint8 ranked = E->CHECKVAL<uint8>(3);

#ifdef CMANGOS
        guild->BroadcastPacketToRank(*data, ranked);
#else
        guild->BroadcastPacketToRank(data, ranked);
#endif
        return 0;
    }

    /**
     * Disbands the [Guild]
     */
    int Disband(Eluna* /*E*/, Guild* guild)
    {
        guild->Disband();
        return 0;
    }

    /**
     * Adds the specified [Player] to the [Guild] at the specified rank.
     *
     * If no rank is specified, defaults to none.
     *
     * @param [Player] player : the [Player] to be added to the guild
     * @param uint8 rankId : the rank ID
     */
    int AddMember(Eluna* E, Guild* guild)
    {
        Player* player = E->CHECKOBJ<Player>(2);
        uint8 rankId = E->CHECKVAL<uint8>(3, GUILD_RANK_NONE);

#ifdef TRINITY
        CharacterDatabaseTransaction trans(nullptr);
        guild->AddMember(trans, player->GET_GUID(), rankId);
#else
        guild->AddMember(player->GET_GUID(), rankId);
#endif
        return 0;
    }

    /**
     * Removes the specified [Player] from the [Guild].
     *
     * @param [Player] player : the [Player] to be removed from the guild
     * @param bool isDisbanding : default 'false', should only be set to 'true' if the guild is triggered to disband
     */
    int DeleteMember(Eluna* E, Guild* guild)
    {
        Player* player = E->CHECKOBJ<Player>(2);
        bool isDisbanding = E->CHECKVAL<bool>(3, false);

#if defined TRINITY
        CharacterDatabaseTransaction trans(nullptr);
        guild->DeleteMember(trans, player->GET_GUID(), isDisbanding);
#elif defined AZEROTHCORE
        guild->DeleteMember(player->GET_GUID(), isDisbanding);
#else
        guild->DelMember(player->GET_GUID(), isDisbanding);
#endif
        return 0;
    }

    /**
     * Promotes/demotes the [Player] to the specified rank.
     *
     * @param [Player] player : the [Player] to be promoted/demoted
     * @param uint8 rankId : the rank ID
     */
    int SetMemberRank(Eluna* E, Guild* guild)
    {
        Player* player = E->CHECKOBJ<Player>(2);
        uint8 newRank = E->CHECKVAL<uint8>(3);

#ifdef TRINITY
        CharacterDatabaseTransaction trans(nullptr);
        guild->ChangeMemberRank(trans, player->GET_GUID(), newRank);
#else
        guild->ChangeMemberRank(player->GET_GUID(), newRank);
#endif
        return 0;
    }
    
    ElunaRegister<Guild> GuildMethods[] =
    {
        // Getters
        { "GetMembers", &LuaGuild::GetMembers },
        { "GetLeader", &LuaGuild::GetLeader },
        { "GetLeaderGUID", &LuaGuild::GetLeaderGUID },
        { "GetId", &LuaGuild::GetId },
        { "GetName", &LuaGuild::GetName },
        { "GetMOTD", &LuaGuild::GetMOTD },
        { "GetInfo", &LuaGuild::GetInfo },
        { "GetMemberCount", &LuaGuild::GetMemberCount },

        // Setters
        { "SetMemberRank", &LuaGuild::SetMemberRank },
        { "SetLeader", &LuaGuild::SetLeader },
#ifndef CLASSIC
        { "SetBankTabText", &LuaGuild::SetBankTabText },
#endif

        // Other
        { "SendPacket", &LuaGuild::SendPacket },
        { "SendPacketToRanked", &LuaGuild::SendPacketToRanked },
        { "Disband", &LuaGuild::Disband },
        { "AddMember", &LuaGuild::AddMember },
        { "DeleteMember", &LuaGuild::DeleteMember },

        { NULL, NULL }
    };
};
#endif
