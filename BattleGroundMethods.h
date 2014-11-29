/*
* Copyright (C) 2010 - 2014 Eluna Lua Engine <http://emudevs.com/>
* This program is free software licensed under GPL version 3
* Please see the included DOCS/LICENSE.md for more information
*/

#ifndef BATTLEGROUNDMETHODS_H
#define BATTLEGROUNDMETHODS_H

namespace LuaBattleGround
{
    /**
     * Returns the name of the [Battleground]
     *
     * @return string name
     */
    int GetName(Eluna* E, BattleGround* bg)
    {
        Eluna::Push(E->L, bg->GetName());
        return 1;
    }

    /**
     * Returns the amount of alive players in the [Battleground] by the team ID.
     *
     * @param uint32 team : team ID
     * @return uint32 count
     */
    int GetAlivePlayersCountByTeam(Eluna* E, BattleGround* bg)
    {
        uint32 team = Eluna::CHECKVAL<uint32>(E->L, 2);

        Eluna::Push(E->L, bg->GetAlivePlayersCountByTeam((Team)team));
        return 1;
    }

    /**
     * Returns the [Map] of the [Battleground].
     *
     * @return [Map] map
     */
    int GetMap(Eluna* E, BattleGround* bg)
    {
        Eluna::Push(E->L, bg->GetBgMap());
        return 1;
    }

    /**
     * Returns the bonus honor given by amount of kills in the specific [Battleground].
     *
     * @param uint32 kills : amount of kills
     * @return uint32 bonusHonor
     */
    int GetBonusHonorFromKillCount(Eluna* E, BattleGround* bg)
    {
        uint32 kills = Eluna::CHECKVAL<uint32>(E->L, 2);

        Eluna::Push(E->L, bg->GetBonusHonorFromKill(kills));
        return 1;
    }

    /**
     * Returns the bracket ID of the specific [Battleground].
     *
     * @return BattleGroundBracketId bracketId
     */
    int GetBracketId(Eluna* E, BattleGround* bg)
    {
        Eluna::Push(E->L, bg->GetBracketId());
        return 1;
    }

    /**
     * Returns the end time of the [Battleground].
     *
     * @return uint32 endTime
     */
    int GetEndTime(Eluna* E, BattleGround* bg)
    {
#ifdef CATA
        Eluna::Push(E->L, bg->GetRemainingTime());
#else
        Eluna::Push(E->L, bg->GetEndTime());
#endif
        return 1;
    }

    /**
     * Returns the amount of free slots for the selected team in the specific [Battleground].
     *
     * @param uint32 team : team ID
     * @return uint32 freeSlots
     */
    int GetFreeSlotsForTeam(Eluna* E, BattleGround* bg)
    {
        uint32 team = Eluna::CHECKVAL<uint32>(E->L, 2);

        Eluna::Push(E->L, bg->GetFreeSlotsForTeam((Team)team));
        return 1;
    }

    /**
     * Returns the instance ID of the [Battleground].
     *
     * @return uint32 instanceId
     */
    int GetInstanceId(Eluna* E, BattleGround* bg)
    {
        Eluna::Push(E->L, bg->GetInstanceID());
        return 1;
    }

    /**
     * Returns the map ID of the [Battleground].
     *
     * @return uint32 mapId
     */
    int GetMapId(Eluna* E, BattleGround* bg)
    {
        Eluna::Push(E->L, bg->GetMapId());
        return 1;
    }

    /**
     * Returns the type ID of the [Battleground].
     *
     * @return BattleGroundTypeId typeId
     */
    int GetTypeId(Eluna* E, BattleGround* bg)
    {
        Eluna::Push(E->L, bg->GetTypeID());
        return 1;
    }

    /**
     * Returns the max allowed [Player] level of the specific [Battleground].
     *
     * @return uint32 maxLevel
     */
    int GetMaxLevel(Eluna* E, BattleGround* bg)
    {
        Eluna::Push(E->L, bg->GetMaxLevel());
        return 1;
    }

    /**
     * Returns the minimum allowed [Player] level of the specific [Battleground].
     *
     * @return uint32 minLevel
     */
    int GetMinLevel(Eluna* E, BattleGround* bg)
    {
        Eluna::Push(E->L, bg->GetMinLevel());
        return 1;
    }

    /**
     * Returns the maximum allowed [Player] count of the specific [Battleground].
     *
     * @return uint32 maxPlayerCount
     */
    int GetMaxPlayers(Eluna* E, BattleGround* bg)
    {
        Eluna::Push(E->L, bg->GetMaxPlayers());
        return 1;
    }

    /**
     * Returns the minimum allowed [Player] count of the specific [Battleground].
     *
     * @return uint32 minPlayerCount
     */
    int GetMinPlayers(Eluna* E, BattleGround* bg)
    {
        Eluna::Push(E->L, bg->GetMinPlayers());
        return 1;
    }

    /**
     * Returns the maximum allowed [Player] count per team of the specific [Battleground].
     *
     * @return uint32 maxTeamPlayerCount
     */
    int GetMaxPlayersPerTeam(Eluna* E, BattleGround* bg)
    {
        Eluna::Push(E->L, bg->GetMaxPlayersPerTeam());
        return 1;
    }

    /**
     * Returns the minimum allowed [Player] count per team of the specific [Battleground].
     *
     * @return uint32 minTeamPlayerCount
     */
    int GetMinPlayersPerTeam(Eluna* E, BattleGround* bg)
    {
        Eluna::Push(E->L, bg->GetMinPlayersPerTeam());
        return 1;
    }

    /**
     * Returns the winning team of the specific [Battleground].
     *
     * @return Team team
     */
    int GetWinner(Eluna* E, BattleGround* bg)
    {
        Eluna::Push(E->L, bg->GetWinner());
        return 1;
    }

    /**
     * Returns the status of the specific [Battleground].
     *
     * @return BattleGroundStatus status
     */
    int GetStatus(Eluna* E, BattleGround* bg)
    {
        Eluna::Push(E->L, bg->GetStatus());
        return 1;
    }
};
#endif