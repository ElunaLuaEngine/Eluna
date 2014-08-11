/*
* Copyright (C) 2010 - 2014 Eluna Lua Engine <http://emudevs.com/>
* This program is free software licensed under GPL version 3
* Please see the included DOCS/LICENSE.md for more information
*/

#ifndef MAPMETHODS_H
#define MAPMETHODS_H

namespace LuaMap
{
    
#ifndef CLASSIC
    /**
     * Returns 'true' if the &Map is an arena, false otherwise
     *
     * @return bool isArena
     */
    int IsArena(lua_State* L, Map* map)
    {
        Eluna::Push(L, map->IsBattleArena());
        return 1;
    }
#endif

    /**
     * Returns 'true' if the &Map is a battleground, false otherwise
     *
     * @return bool isBattleGround
     */
    int IsBattleground(lua_State* L, Map* map)
    {
#ifndef TRINITY
        Eluna::Push(L, map->IsBattleGround());
#else
        Eluna::Push(L, map->IsBattleground());
#endif
        return 1;
    }

    /**
     * Returns 'true' if the &Map is a dungeon, false otherwise
     *
     * @return bool isDungeon
     */
    int IsDungeon(lua_State* L, Map* map)
    {
        Eluna::Push(L, map->IsDungeon());
        return 1;
    }

    /**
     * Returns 'true' if the &Map is empty, false otherwise
     *
     * @return bool isEmpty
     */
    int IsEmpty(lua_State* L, Map* map)
    {
        Eluna::Push(L, map->isEmpty());
        return 1;
    }

#ifndef CLASSIC
    /**
     * Returns 'true' if the &Map is a heroic, false otherwise
     *
     * @return bool isHeroic
     */
    int IsHeroic(lua_State* L, Map* map)
    {
        Eluna::Push(L, map->IsHeroic());
        return 1;
    }
#endif

    /**
     * Returns 'true' if the &Map is a raid, false otherwise
     *
     * @return bool isRaid
     */
    int IsRaid(lua_State* L, Map* map)
    {
        Eluna::Push(L, map->IsRaid());
        return 1;
    }

    /**
     * Returns the name of the &Map
     *
     * @return string mapName
     */
    int GetName(lua_State* L, Map* map)
    {
        Eluna::Push(L, map->GetMapName());
        return 1;
    }

    /**
     * Returns the height of the &Map at the given X and Y coordinates
     *
     * @param float x
     * @param float y
     * @return float z
     */
    int GetHeight(lua_State* L, Map* map)
    {
        float x = Eluna::CHECKVAL<float>(L, 2);
        float y = Eluna::CHECKVAL<float>(L, 3);
#if (defined(TBC) || defined(CLASSIC))
        float z = map->GetHeight(x, y, MAX_HEIGHT);
#else
        uint32 phasemask = Eluna::CHECKVAL<uint32>(L, 4, 1);
        float z = map->GetHeight(phasemask, x, y, MAX_HEIGHT);
#endif
        if (z != INVALID_HEIGHT)
            Eluna::Push(L, z);
        return 1;
    }

    /**
     * Returns the difficulty of the &Map
     *
     * @return int32 difficulty
     */
    int GetDifficulty(lua_State* L, Map* map)
    {
#ifndef CLASSIC
        Eluna::Push(L, map->GetDifficulty());
#else
        Eluna::Push(L, (Difficulty)0);
#endif
        return 1;
    }

    /**
     * Returns the instance id of the &Map
     *
     * @return uint32 instanceId
     */
    int GetInstanceId(lua_State* L, Map* map)
    {
        Eluna::Push(L, map->GetInstanceId());
        return 1;
    }

    /**
     * Returns the player count currently on the &Map
     * Does not include gamemasters
     *
     * @return uint32 playerCount
     */
    int GetPlayerCount(lua_State* L, Map* map)
    {
        Eluna::Push(L, map->GetPlayersCountExceptGMs());
        return 1;
    }

    /**
     * Returns the id of the &Map
     *
     * @return uint32 mapId
     */
    int GetMapId(lua_State* L, Map* map)
    {
        Eluna::Push(L, map->GetId());
        return 1;
    }

    /**
     * Returns the area id of the &Map at the specified X, Y and Z coordinates
     *
     * @param float x
     * @param float y
     * @param float z
     * @return uint32 areaId
     */
    int GetAreaId(lua_State* L, Map* map)
    {
        float x = Eluna::CHECKVAL<float>(L, 2);
        float y = Eluna::CHECKVAL<float>(L, 3);
        float z = Eluna::CHECKVAL<float>(L, 4);

#ifndef TRINITY
        Eluna::Push(L, map->GetTerrain()->GetAreaId(x, y, z));
#else
        Eluna::Push(L, map->GetAreaId(x, y, z));
#endif
        return 1;
    }

    int GetWorldObject(lua_State* L, Map* map)
    {
        uint64 guid = Eluna::CHECKVAL<uint64>(L, 2);

#ifndef TRINITY
        Eluna::Push(L, map->GetWorldObject(ObjectGuid(guid)));
#else
        switch (GUID_HIPART(guid))
        {
        case HIGHGUID_PLAYER:
            Eluna::Push(L, sObjectAccessor->GetObjectInMap(guid, map, (Player*)NULL));
            break;
        case HIGHGUID_TRANSPORT:
        case HIGHGUID_MO_TRANSPORT:
        case HIGHGUID_GAMEOBJECT:
            Eluna::Push(L, sObjectAccessor->GetObjectInMap(guid, map, (GameObject*)NULL));
            break;
        case HIGHGUID_VEHICLE:
        case HIGHGUID_UNIT:
            Eluna::Push(L, sObjectAccessor->GetObjectInMap(guid, map, (Creature*)NULL));
            break;
        case HIGHGUID_PET:
            Eluna::Push(L, sObjectAccessor->GetObjectInMap(guid, map, (Pet*)NULL));
            break;
        case HIGHGUID_DYNAMICOBJECT:
            Eluna::Push(L, sObjectAccessor->GetObjectInMap(guid, map, (DynamicObject*)NULL));
            break;
        case HIGHGUID_CORPSE:
            Eluna::Push(L, sObjectAccessor->GetObjectInMap(guid, map, (Corpse*)NULL));
            break;
        default:
            break;
        }
#endif
        return 1;
    }
};
#endif
