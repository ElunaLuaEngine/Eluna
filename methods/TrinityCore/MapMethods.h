/*
* Copyright (C) 2010 - 2024 Eluna Lua Engine <https://elunaluaengine.github.io/>
* This program is free software licensed under GPL version 3
* Please see the included DOCS/LICENSE.md for more information
*/

#ifndef MAPMETHODS_H
#define MAPMETHODS_H

#include "ElunaInstanceAI.h"
#include "LuaValue.h"

/***
 * A game map, e.g. Azeroth, Eastern Kingdoms, the Molten Core, etc.
 *
 * Inherits all methods from: none
 */
namespace LuaMap
{

    /**
     * Returns `true` if the [Map] is an arena [BattleGround], `false` otherwise.
     *
     * @return bool isArena
     */
    int IsArena(Eluna* E, Map* map)
    {
        E->Push(map->IsBattleArena());
        return 1;
    }

    /**
     * Returns `true` if the [Map] is a non-arena [BattleGround], `false` otherwise.
     *
     * @return bool isBattleGround
     */
    int IsBattleground(Eluna* E, Map* map)
    {
        E->Push(map->IsBattleground());
        return 1;
    }

    /**
     * Returns `true` if the [Map] is a dungeon, `false` otherwise.
     *
     * @return bool isDungeon
     */
    int IsDungeon(Eluna* E, Map* map)
    {
        E->Push(map->IsDungeon());
        return 1;
    }

    /**
     * Returns `true` if the [Map] has no [Player]s, `false` otherwise.
     *
     * @return bool isEmpty
     */
    int IsEmpty(Eluna* E, Map* map)
    {
        E->Push(map->isEmpty());
        return 1;
    }

    /**
     * Returns `true` if the [Map] is a heroic, `false` otherwise.
     *
     * @return bool isHeroic
     */
    int IsHeroic(Eluna* E, Map* map)
    {
        E->Push(map->IsHeroic());
        return 1;
    }

    /**
     * Returns `true` if the [Map] is a raid, `false` otherwise.
     *
     * @return bool isRaid
     */
    int IsRaid(Eluna* E, Map* map)
    {
        E->Push(map->IsRaid());
        return 1;
    }

    /**
     * Returns the name of the [Map].
     *
     * @return string mapName
     */
    int GetName(Eluna* E, Map* map)
    {
        E->Push(map->GetMapName());
        return 1;
    }

    /**
     * Returns the height of the [Map] at the given X and Y coordinates.
     *
     * In case of no height found nil is returned
     *
     * @param float x
     * @param float y
     * @return float z
     */
    int GetHeight(Eluna* E, Map* map)
    {
        float x = E->CHECKVAL<float>(2);
        float y = E->CHECKVAL<float>(3);
        uint32 phasemask = E->CHECKVAL<uint32>(4, 1);

#if ELUNA_EXPANSION < EXP_RETAIL
        float z = map->GetHeight(phasemask, x, y, MAX_HEIGHT);
#else
        PhaseShift phaseShift;
        float z = map->GetHeight(phaseShift, x, y, MAX_HEIGHT);
#endif
        if (z != INVALID_HEIGHT)
            E->Push(z);
        return 1;
    }

    /**
     * Returns the difficulty of the [Map].
     *
     * Always returns 0 if the expansion is pre-TBC.
     *
     * @return int32 difficulty
     */
    int GetDifficulty(Eluna* E, Map* map)
    {
#if ELUNA_EXPANSION < EXP_RETAIL
        E->Push(map->GetDifficulty());
#else
        E->Push(map->GetMapDifficulty());
#endif
        return 1;
    }

    /**
     * Returns the instance ID of the [Map].
     *
     * @return uint32 instanceId
     */
    int GetInstanceId(Eluna* E, Map* map)
    {
        E->Push(map->GetInstanceId());
        return 1;
    }

    /**
     * Returns the player count currently on the [Map] (excluding GMs).
     *
     * @return uint32 playerCount
     */
    int GetPlayerCount(Eluna* E, Map* map)
    {
        E->Push(map->GetPlayersCountExceptGMs());
        return 1;
    }

    /**
     * Returns the ID of the [Map].
     *
     * @return uint32 mapId
     */
    int GetMapId(Eluna* E, Map* map)
    {
        E->Push(map->GetId());
        return 1;
    }

    /**
     * Returns the area ID of the [Map] at the specified X, Y, and Z coordinates.
     *
     * @param float x
     * @param float y
     * @param float z
     * @param uint32 phasemask = PHASEMASK_NORMAL
     * @return uint32 areaId
     */
    int GetAreaId(Eluna* E, Map* map)
    {
        float x = E->CHECKVAL<float>(2);
        float y = E->CHECKVAL<float>(3);
        float z = E->CHECKVAL<float>(4);
#if ELUNA_EXPANSION < EXP_RETAIL
        float phasemask = E->CHECKVAL<uint32>(5, PHASEMASK_NORMAL);
        E->Push(map->GetAreaId(phasemask, x, y, z));
#else
        PhaseShift phaseShift;
        E->Push(map->GetAreaId(phaseShift, x, y, z));
#endif
        return 1;
    }

    /**
     * Returns a [WorldObject] by its GUID from the map if it is spawned.
     *
     * @param ObjectGuid guid
     * @return [WorldObject] object
     */
    int GetWorldObject(Eluna* E, Map* map)
    {
        ObjectGuid guid = E->CHECKVAL<ObjectGuid>(2);

        switch (guid.GetHigh())
        {
            case HIGHGUID_PLAYER:
                E->Push(eObjectAccessor()GetPlayer(map, guid));
                break;
            case HIGHGUID_TRANSPORT:
#if ELUNA_EXPANSION < EXP_RETAIL
            case HIGHGUID_MO_TRANSPORT:
#endif
            case HIGHGUID_GAMEOBJECT:
                E->Push(map->GetGameObject(guid));
                break;
            case HIGHGUID_VEHICLE:
            case HIGHGUID_UNIT:
                E->Push(map->GetCreature(guid));
                break;
            case HIGHGUID_PET:
                E->Push(map->GetPet(guid));
                break;
            case HIGHGUID_DYNAMICOBJECT:
                E->Push(map->GetDynamicObject(guid));
                break;
            case HIGHGUID_CORPSE:
                E->Push(map->GetCorpse(guid));
                break;
            default:
                break;
        }

        return 1;
    }

    /**
     * Sets the [Weather] type based on [WeatherType] and grade supplied.
     *
     * @table
     * @columns [WeatherType, ID]
     * @values [WEATHER_TYPE_FINE, 0]
     * @values [WEATHER_TYPE_RAIN, 1]
     * @values [WEATHER_TYPE_SNOW, 2]
     * @values [WEATHER_TYPE_STORM, 3]
     * @values [WEATHER_TYPE_THUNDERS, 86]
     * @values [WEATHER_TYPE_BLACKRAIN, 90]
     *
     * @param uint32 zone : id of the zone to set the weather for
     * @param [WeatherType] type : the [WeatherType], see above available weather types
     * @param float grade : the intensity/grade of the [Weather], ranges from 0 to 1
     */
    int SetWeather(Eluna* E, Map* map)
    {
        (void)map; // ensure that the variable is referenced in order to pass compiler checks
        uint32 zoneId = E->CHECKVAL<uint32>(2);
        uint32 weatherType = E->CHECKVAL<uint32>(3);
        float grade = E->CHECKVAL<float>(4);

        if (Weather * weather = map->GetOrGenerateZoneDefaultWeather(zoneId))
            weather->SetWeather((WeatherType)weatherType, grade);
        return 0;
    }

    /**
     * Gets the instance data table for the [Map], if it exists.
     *
     * The instance must be scripted using Eluna for this to succeed.
     * If the instance is scripted in C++ this will return `nil`.
     *
     * @return table instance_data : instance data table, or `nil`
     */
    int GetInstanceData(Eluna* E, Map* map)
    {
        ElunaInstanceAI* iAI = NULL;
        if (InstanceMap* inst = map->ToInstanceMap())
            iAI = dynamic_cast<ElunaInstanceAI*>(inst->GetInstanceScript());

        if (iAI)
            E->PushInstanceData(iAI, false);
        else
            E->Push(); // nil

        return 1;
    }

#if ELUNA_EXPANSION < EXP_RETAIL
    /**
     * Saves the [Map]'s instance data to the database.
     */
    int SaveInstanceData(Eluna* /*E*/, Map* map)
    {
        ElunaInstanceAI* iAI = NULL;
        if (InstanceMap* inst = map->ToInstanceMap())
            iAI = dynamic_cast<ElunaInstanceAI*>(inst->GetInstanceScript());

        if (iAI)
            iAI->SaveToDB();

        return 0;
    }
#endif

    /**
    * Returns a table with all the current [Player]s in the map
    *
    * @table
    * @columns [Team, ID]
    * @values [ALLIANCE, 0]
    * @values [HORDE, 1]
    * @values [NEUTRAL, 2]
    *
    * @param [TeamId] team : optional check team of the [Player], Alliance, Horde or Neutral (All)
    * @return table mapPlayers
    */
    int GetPlayers(Eluna* E, Map* map)
    {
        uint32 team = E->CHECKVAL<uint32>(2, TEAM_NEUTRAL);

        lua_newtable(E->L);
        int tbl = lua_gettop(E->L);
        uint32 i = 0;

        Map::PlayerList const& players = map->GetPlayers();
        for (Map::PlayerList::const_iterator itr = players.begin(); itr != players.end(); ++itr)
        {
            Player* player = itr->GetSource();
            if (!player)
                continue;

            if (player->GetSession() && (team >= TEAM_NEUTRAL || uint32(player->GetTeamId()) == team))
            {
                E->Push(player);
                lua_rawseti(E->L, tbl, ++i);
            }
        }

        lua_settop(E->L, tbl);
        return 1;
    }

    /**
     * Returns a runtime-persistent cache tied to the [Map].
     * This data will remain for as long as the [Map] exists, or until a server restart.
     *
     * A reload of the Lua state will NOT clear this cache.
     *
     * This cache can be added to and read from with the following sub-methods.
     * <pre>
     * -- Sets the key-value pair in the cache
     * Map:Data():Set("key", val)
     *
     * -- Returns the value from the cache using the key
     * local val = Map:Data():Get("key")
     *
     * -- Removes the key-value pair from the cache
     * Map:Data():Set("key", nil)
     *
     * -- Returns all the key-value pairs as a Lua table indexed by the keys
     * local table = Map:Data():AsTable()
     * </pre>
     */
    int Data(Eluna* E, Map* map)
    {
        return LuaVal::PushLuaVal(E->L, map->lua_data);
    }
    
    ElunaRegister<Map> MapMethods[] =
    {
        // Getters
        { "GetName", &LuaMap::GetName },
        { "GetDifficulty", &LuaMap::GetDifficulty },
        { "GetInstanceId", &LuaMap::GetInstanceId },
        { "GetInstanceData", &LuaMap::GetInstanceData },
        { "GetPlayerCount", &LuaMap::GetPlayerCount },
        { "GetPlayers", &LuaMap::GetPlayers },
        { "GetMapId", &LuaMap::GetMapId },
        { "GetAreaId", &LuaMap::GetAreaId },
        { "GetHeight", &LuaMap::GetHeight },
        { "GetWorldObject", &LuaMap::GetWorldObject },

        // Setters
        { "SetWeather", &LuaMap::SetWeather },

        // Boolean
        { "IsArena", &LuaMap::IsArena },
        { "IsBattleground", &LuaMap::IsBattleground },
        { "IsDungeon", &LuaMap::IsDungeon },
        { "IsEmpty", &LuaMap::IsEmpty },
        { "IsHeroic", &LuaMap::IsHeroic },
        { "IsRaid", &LuaMap::IsRaid },

        // Other
#if ELUNA_EXPANSION < EXP_RETAIL
        { "SaveInstanceData", &LuaMap::SaveInstanceData },
#else
        { "SaveInstanceData", METHOD_REG_NONE },
#endif
        { "Data", &LuaMap::Data }
    };
};
#endif
