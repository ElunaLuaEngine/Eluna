/*
* Copyright (C) 2010 - 2014 Eluna Lua Engine <http://emudevs.com/>
* This program is free software licensed under GPL version 3
* Please see the included DOCS/LICENSE.md for more information
*/

#ifndef GUILDMETHODS_H
#define GUILDMETHODS_H

namespace LuaGuild
{
    /* GETTERS */
    int GetMembers(lua_State* L, Guild* guild)
    {
        lua_newtable(L);
        int tbl = lua_gettop(L);
        uint32 i = 0;

        SessionMap const& sessions = eWorld->GetAllSessions();
        for (SessionMap::const_iterator it = sessions.begin(); it != sessions.end(); ++it)
        {
            if (Player* player = it->second->GetPlayer())
            {
                if (player->GetSession() && (player->GetGuildId() == guild->GetId()))
                {
                    ++i;
                    Eluna::Push(L, i);
                    Eluna::Push(L, player);
                    lua_settable(L, tbl);
                }
            }
        }

        lua_settop(L, tbl); // push table to top of stack
        return 1;
    }

    int GetMemberCount(lua_State* L, Guild* guild)
    {
        Eluna::Push(L, guild->GetMemberSize());
        return 1;
    }

    int GetLeader(lua_State* L, Guild* guild)
    {
#ifndef TRINITY
        Eluna::Push(L, eObjectAccessor->FindPlayer(guild->GetLeaderGuid()));
#else
        Eluna::Push(L, eObjectAccessor->FindPlayer(guild->GetLeaderGUID()));
#endif
        return 1;
    }

    int GetLeaderGUID(lua_State* L, Guild* guild)
    {
#ifndef TRINITY
        Eluna::Push(L, guild->GetLeaderGuid());
#else
        Eluna::Push(L, guild->GetLeaderGUID());
#endif
        return 1;
    }

    int GetId(lua_State* L, Guild* guild)
    {
        Eluna::Push(L, guild->GetId());
        return 1;
    }

    int GetName(lua_State* L, Guild* guild)
    {
        Eluna::Push(L, guild->GetName());
        return 1;
    }

    int GetMOTD(lua_State* L, Guild* guild)
    {
        Eluna::Push(L, guild->GetMOTD());
        return 1;
    }

    int GetInfo(lua_State* L, Guild* guild)
    {
#ifndef TRINITY
        Eluna::Push(L, guild->GetGINFO());
#else
        Eluna::Push(L, guild->GetInfo());
#endif
        return 1;
    }

    /* SETTERS */
#ifndef CATA
    int SetLeader(lua_State* L, Guild* guild)
    {
        Player* player = Eluna::CHECKOBJ<Player>(L, 2);

#ifndef TRINITY
        guild->SetLeader(player->GET_GUID());
#else
        guild->HandleSetLeader(player->GetSession(), player->GetName());
#endif
        return 0;
    }
#endif

#ifndef CLASSIC
    int SetBankTabText(lua_State* L, Guild* guild)
    {
        uint8 tabId = Eluna::CHECKVAL<uint8>(L, 2);
        const char* text = Eluna::CHECKVAL<const char*>(L, 3);
#ifndef TRINITY
        guild->SetGuildBankTabText(tabId, text);
#else
        guild->SetBankTabText(tabId, text);
#endif
        return 0;
    }
#endif

    /* OTHER */
    // SendPacketToGuild(packet)
    int SendPacket(lua_State* L, Guild* guild)
    {
        WorldPacket* data = Eluna::CHECKOBJ<WorldPacket>(L, 2);

        guild->BroadcastPacket(data);
        return 0;
    }

    // SendPacketToRankedInGuild(packet, rankId)
    int SendPacketToRanked(lua_State* L, Guild* guild)
    {
        WorldPacket* data = Eluna::CHECKOBJ<WorldPacket>(L, 2);
        uint8 ranked = Eluna::CHECKVAL<uint8>(L, 3);

        guild->BroadcastPacketToRank(data, ranked);
        return 0;
    }

    int Disband(lua_State* /*L*/, Guild* guild)
    {
        guild->Disband();
        return 0;
    }

    int AddMember(lua_State* L, Guild* guild)
    {
        Player* player = Eluna::CHECKOBJ<Player>(L, 2);
        uint8 rankId = Eluna::CHECKVAL<uint8>(L, 3, GUILD_RANK_NONE);

        guild->AddMember(player->GET_GUID(), rankId);
        return 0;
    }

    int DeleteMember(lua_State* L, Guild* guild)
    {
        Player* player = Eluna::CHECKOBJ<Player>(L, 2);
        bool isDisbanding = Eluna::CHECKVAL<bool>(L, 3, false);

#ifndef TRINITY
        guild->DelMember(player->GET_GUID(), isDisbanding);
#else
        guild->DeleteMember(player->GET_GUID(), isDisbanding);
#endif
        return 0;
    }

    int SetMemberRank(lua_State* L, Guild* guild)
    {
        Player* player = Eluna::CHECKOBJ<Player>(L, 2);
        uint8 newRank = Eluna::CHECKVAL<uint8>(L, 3);

        guild->ChangeMemberRank(player->GET_GUID(), newRank);
        return 0;
    }

#ifndef CLASSIC
    // Move to Player methods
    int WithdrawBankMoney(lua_State* L, Guild* guild)
    {
        Player* player = Eluna::CHECKOBJ<Player>(L, 2);
        uint32 money = Eluna::CHECKVAL<uint32>(L, 3);
#ifndef TRINITY
        if (guild->GetGuildBankMoney() < money)
            return 0;
        guild->SetBankMoney(guild->GetGuildBankMoney() - money);
#else
        guild->HandleMemberWithdrawMoney(player->GetSession(), money);
#endif
        return 0;
    }

    // Move to Player methods
    int DepositBankMoney(lua_State* L, Guild* guild)
    {
        Player* player = Eluna::CHECKOBJ<Player>(L, 2);
        uint32 money = Eluna::CHECKVAL<uint32>(L, 3);

#ifndef TRINITY
        guild->SetBankMoney(guild->GetGuildBankMoney() + money);
#else
        guild->HandleMemberDepositMoney(player->GetSession(), money);
#endif
        return 0;
    }
#endif
};
#endif
