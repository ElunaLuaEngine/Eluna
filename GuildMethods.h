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
    int GetMembers(Eluna* E, Guild* guild)
    {
        lua_newtable(E->L);
        int tbl = lua_gettop(E->L);
        uint32 i = 0;

        SessionMap const& sessions = eWorld->GetAllSessions();
        for (SessionMap::const_iterator it = sessions.begin(); it != sessions.end(); ++it)
        {
            if (Player* player = it->second->GetPlayer())
            {
                if (player->GetSession() && (player->GetGuildId() == guild->GetId()))
                {
                    ++i;
                    Eluna::Push(E->L, i);
                    Eluna::Push(E->L, player);
                    lua_settable(E->L, tbl);
                }
            }
        }

        lua_settop(E->L, tbl); // push table to top of stack
        return 1;
    }

    int GetMemberCount(Eluna* E, Guild* guild)
    {
        Eluna::Push(E->L, guild->GetMemberSize());
        return 1;
    }

    int GetLeader(Eluna* E, Guild* guild)
    {
#ifndef TRINITY
        Eluna::Push(E->L, eObjectAccessor->FindPlayer(guild->GetLeaderGuid()));
#else
        Eluna::Push(E->L, eObjectAccessor->FindPlayer(guild->GetLeaderGUID()));
#endif
        return 1;
    }

    int GetLeaderGUID(Eluna* E, Guild* guild)
    {
#ifndef TRINITY
        Eluna::Push(E->L, guild->GetLeaderGuid());
#else
        Eluna::Push(E->L, guild->GetLeaderGUID());
#endif
        return 1;
    }

    int GetId(Eluna* E, Guild* guild)
    {
        Eluna::Push(E->L, guild->GetId());
        return 1;
    }

    int GetName(Eluna* E, Guild* guild)
    {
        Eluna::Push(E->L, guild->GetName());
        return 1;
    }

    int GetMOTD(Eluna* E, Guild* guild)
    {
        Eluna::Push(E->L, guild->GetMOTD());
        return 1;
    }

    int GetInfo(Eluna* E, Guild* guild)
    {
#ifndef TRINITY
        Eluna::Push(E->L, guild->GetGINFO());
#else
        Eluna::Push(E->L, guild->GetInfo());
#endif
        return 1;
    }

    /* SETTERS */
#ifndef CATA
    int SetLeader(Eluna* E, Guild* guild)
    {
        Player* player = Eluna::CHECKOBJ<Player>(E->L, 2);

#ifndef TRINITY
        guild->SetLeader(player->GET_GUID());
#else
        guild->HandleSetLeader(player->GetSession(), player->GetName());
#endif
        return 0;
    }
#endif

#ifndef CLASSIC
    int SetBankTabText(Eluna* E, Guild* guild)
    {
        uint8 tabId = Eluna::CHECKVAL<uint8>(E->L, 2);
        const char* text = Eluna::CHECKVAL<const char*>(E->L, 3);
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
    int SendPacket(Eluna* E, Guild* guild)
    {
        WorldPacket* data = Eluna::CHECKOBJ<WorldPacket>(E->L, 2);

        guild->BroadcastPacket(data);
        return 0;
    }

    // SendPacketToRankedInGuild(packet, rankId)
    int SendPacketToRanked(Eluna* E, Guild* guild)
    {
        WorldPacket* data = Eluna::CHECKOBJ<WorldPacket>(E->L, 2);
        uint8 ranked = Eluna::CHECKVAL<uint8>(E->L, 3);

        guild->BroadcastPacketToRank(data, ranked);
        return 0;
    }

    int Disband(Eluna* /*E*/, Guild* guild)
    {
        guild->Disband();
        return 0;
    }

    int AddMember(Eluna* E, Guild* guild)
    {
        Player* player = Eluna::CHECKOBJ<Player>(E->L, 2);
        uint8 rankId = Eluna::CHECKVAL<uint8>(E->L, 3, GUILD_RANK_NONE);

        guild->AddMember(player->GET_GUID(), rankId);
        return 0;
    }

    int DeleteMember(Eluna* E, Guild* guild)
    {
        Player* player = Eluna::CHECKOBJ<Player>(E->L, 2);
        bool isDisbanding = Eluna::CHECKVAL<bool>(E->L, 3, false);

#ifndef TRINITY
        guild->DelMember(player->GET_GUID(), isDisbanding);
#else
        guild->DeleteMember(player->GET_GUID(), isDisbanding);
#endif
        return 0;
    }

    int SetMemberRank(Eluna* E, Guild* guild)
    {
        Player* player = Eluna::CHECKOBJ<Player>(E->L, 2);
        uint8 newRank = Eluna::CHECKVAL<uint8>(E->L, 3);

        guild->ChangeMemberRank(player->GET_GUID(), newRank);
        return 0;
    }

#ifndef CLASSIC
    // Move to Player methods
    int WithdrawBankMoney(Eluna* E, Guild* guild)
    {
        Player* player = Eluna::CHECKOBJ<Player>(E->L, 2);
        uint32 money = Eluna::CHECKVAL<uint32>(E->L, 3);
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
    int DepositBankMoney(Eluna* E, Guild* guild)
    {
        Player* player = Eluna::CHECKOBJ<Player>(E->L, 2);
        uint32 money = Eluna::CHECKVAL<uint32>(E->L, 3);

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
