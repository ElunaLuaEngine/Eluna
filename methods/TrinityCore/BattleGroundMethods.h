/*
* Copyright (C) 2010 - 2024 Eluna Lua Engine <https://elunaluaengine.github.io/>
* This program is free software licensed under GPL version 3
* Please see the included DOCS/LICENSE.md for more information
*/

#ifndef BATTLEGROUNDMETHODS_H
#define BATTLEGROUNDMETHODS_H

/***
 * Contains the state of a battleground, e.g. Warsong Gulch, Arathi Basin, etc.
 *
 * Inherits all methods from: none
 */
namespace LuaBattleGround
{
    /**
     * Returns the name of the [BattleGround].
     *
     * @return string name
     */
    int GetName(Eluna* E, BattleGround* bg)
    {
        E->Push(bg->GetName());
        return 1;
    }

    /**
     * Returns the amount of alive players in the [BattleGround] by the team ID.
     *
     * @param [Team] team : team ID
     * @return uint32 count
     */
    int GetAlivePlayersCountByTeam(Eluna* E, BattleGround* bg)
    {
        uint32 team = E->CHECKVAL<uint32>(2);

        E->Push(bg->GetAlivePlayersCountByTeam((Team)team));
        return 1;
    }

    /**
     * Returns the [Map] of the [BattleGround].
     *
     * @return [Map] map
     */
    int GetMap(Eluna* E, BattleGround* bg)
    {
        E->Push(static_cast<Map*>(bg->GetBgMap()));
        return 1;
    }

    /**
     * Returns the bonus honor given by amount of kills in the specific [BattleGround].
     *
     * @param uint32 kills : amount of kills
     * @return uint32 bonusHonor
     */
    int GetBonusHonorFromKillCount(Eluna* E, BattleGround* bg)
    {
        uint32 kills = E->CHECKVAL<uint32>(2);

        E->Push(bg->GetBonusHonorFromKill(kills));
        return 1;
    }

    /**
     * Returns the bracket ID of the specific [BattleGround].
     *
     * @return [BattleGroundBracketId] bracketId
     */
    int GetBracketId(Eluna* E, BattleGround* bg)
    {
        E->Push(bg->GetBracketId());
        return 1;
    }

    /**
     * Returns the end time of the [BattleGround].
     *
     * @return uint32 endTime
     */
    int GetEndTime(Eluna* E, BattleGround* bg)
    {
#ifdef CATA
        E->Push(bg->GetRemainingTime());
#else
        E->Push(bg->GetEndTime());
#endif
        return 1;
    }

    /**
     * Returns the amount of free slots for the selected team in the specific [BattleGround].
     *
     * @param [Team] team : team ID
     * @return uint32 freeSlots
     */
    int GetFreeSlotsForTeam(Eluna* E, BattleGround* bg)
    {
        uint32 team = E->CHECKVAL<uint32>(2);

        E->Push(bg->GetFreeSlotsForTeam((Team)team));
        return 1;
    }

    /**
     * Returns the instance ID of the [BattleGround].
     *
     * @return uint32 instanceId
     */
    int GetInstanceId(Eluna* E, BattleGround* bg)
    {
        E->Push(bg->GetInstanceID());
        return 1;
    }

    /**
     * Returns the map ID of the [BattleGround].
     *
     * @return uint32 mapId
     */
    int GetMapId(Eluna* E, BattleGround* bg)
    {
        E->Push(bg->GetMapId());
        return 1;
    }

    /**
     * Returns the type ID of the [BattleGround].
     *
     * @return [BattleGroundTypeId] typeId
     */
    int GetTypeId(Eluna* E, BattleGround* bg)
    {
        E->Push(bg->GetTypeID());
        return 1;
    }

    /**
     * Returns the max allowed [Player] level of the specific [BattleGround].
     *
     * @return uint32 maxLevel
     */
    int GetMaxLevel(Eluna* E, BattleGround* bg)
    {
        E->Push(bg->GetMaxLevel());
        return 1;
    }

    /**
     * Returns the minimum allowed [Player] level of the specific [BattleGround].
     *
     * @return uint32 minLevel
     */
    int GetMinLevel(Eluna* E, BattleGround* bg)
    {
        E->Push(bg->GetMinLevel());
        return 1;
    }

    /**
     * Returns the maximum allowed [Player] count of the specific [BattleGround].
     *
     * @return uint32 maxPlayerCount
     */
    int GetMaxPlayers(Eluna* E, BattleGround* bg)
    {
        E->Push(bg->GetMaxPlayers());
        return 1;
    }

    /**
     * Returns the minimum allowed [Player] count of the specific [BattleGround].
     *
     * @return uint32 minPlayerCount
     */
    int GetMinPlayers(Eluna* E, BattleGround* bg)
    {
        E->Push(bg->GetMinPlayers());
        return 1;
    }

    /**
     * Returns the maximum allowed [Player] count per team of the specific [BattleGround].
     *
     * @return uint32 maxTeamPlayerCount
     */
    int GetMaxPlayersPerTeam(Eluna* E, BattleGround* bg)
    {
        E->Push(bg->GetMaxPlayersPerTeam());
        return 1;
    }

    /**
     * Returns the minimum allowed [Player] count per team of the specific [BattleGround].
     *
     * @return uint32 minTeamPlayerCount
     */
    int GetMinPlayersPerTeam(Eluna* E, BattleGround* bg)
    {
        E->Push(bg->GetMinPlayersPerTeam());
        return 1;
    }

    /**
     * Returns the winning team of the specific [BattleGround].
     *
     * @return [Team] team
     */
    int GetWinner(Eluna* E, BattleGround* bg)
    {
        E->Push(bg->GetWinner());
        return 1;
    }

    /**
     * Returns the status of the specific [BattleGround].
     *
     * @return [BattleGroundStatus] status
     */
    int GetStatus(Eluna* E, BattleGround* bg)
    {
        E->Push(bg->GetStatus());
        return 1;
    }
    
    ElunaRegister<BattleGround> BattleGroundMethods[] =
    {
        // Getters
        { "GetName", &LuaBattleGround::GetName },
        { "GetAlivePlayersCountByTeam", &LuaBattleGround::GetAlivePlayersCountByTeam },
        { "GetMap", &LuaBattleGround::GetMap },
        { "GetBonusHonorFromKillCount", &LuaBattleGround::GetBonusHonorFromKillCount },
        { "GetBracketId", &LuaBattleGround::GetBracketId },
        { "GetEndTime", &LuaBattleGround::GetEndTime },
        { "GetFreeSlotsForTeam", &LuaBattleGround::GetFreeSlotsForTeam },
        { "GetInstanceId", &LuaBattleGround::GetInstanceId },
        { "GetMapId", &LuaBattleGround::GetMapId },
        { "GetTypeId", &LuaBattleGround::GetTypeId },
        { "GetMaxLevel", &LuaBattleGround::GetMaxLevel },
        { "GetMinLevel", &LuaBattleGround::GetMinLevel },
        { "GetMaxPlayers", &LuaBattleGround::GetMaxPlayers },
        { "GetMinPlayers", &LuaBattleGround::GetMinPlayers },
        { "GetMaxPlayersPerTeam", &LuaBattleGround::GetMaxPlayersPerTeam },
        { "GetMinPlayersPerTeam", &LuaBattleGround::GetMinPlayersPerTeam },
        { "GetWinner", &LuaBattleGround::GetWinner },
        { "GetStatus", &LuaBattleGround::GetStatus },

        { NULL, NULL, METHOD_REG_NONE }
    };
};
#endif
