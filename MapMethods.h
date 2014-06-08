/*
* Copyright (C) 2010 - 2014 Eluna Lua Engine <http://emudevs.com/>
* This program is free software licensed under GPL version 3
* Please see the included DOCS/LICENSE.md for more information
*/

#ifndef MAPMETHODS_H
#define MAPMETHODS_H

namespace LuaMap
{
    /* BOOLEAN */
#ifndef CLASSIC
    int IsArena(lua_State* L, Map* map)
    {
        Eluna::Push(L, map->IsBattleArena());
        return 1;
    }
#endif

    int IsBattleground(lua_State* L, Map* map)
    {
#ifdef MANGOS
        Eluna::Push(L, map->IsBattleGround());
#else
        Eluna::Push(L, map->IsBattleground());
#endif
        return 1;
    }

    int IsDungeon(lua_State* L, Map* map)
    {
        Eluna::Push(L, map->IsDungeon());
        return 1;
    }

    int IsEmpty(lua_State* L, Map* map)
    {
        Eluna::Push(L, map->isEmpty());
        return 1;
    }

#ifndef CLASSIC
    int IsHeroic(lua_State* L, Map* map)
    {
        Eluna::Push(L, map->IsHeroic());
        return 1;
    }
#endif

    int IsRaid(lua_State* L, Map* map)
    {
        Eluna::Push(L, map->IsRaid());
        return 1;
    }

    /* GETTERS */
    int GetName(lua_State* L, Map* map)
    {
        Eluna::Push(L, map->GetMapName());
        return 1;
    }

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

    int GetDifficulty(lua_State* L, Map* map)
    {
#ifndef CLASSIC
        Eluna::Push(L, map->GetDifficulty());
#else
        Eluna::Push(L, (Difficulty)0);
#endif
        return 1;
    }

    int GetInstanceId(lua_State* L, Map* map)
    {
        Eluna::Push(L, map->GetInstanceId());
        return 1;
    }

    int GetPlayerCount(lua_State* L, Map* map)
    {
        Eluna::Push(L, map->GetPlayersCountExceptGMs());
        return 1;
    }

    int GetMapId(lua_State* L, Map* map)
    {
        Eluna::Push(L, map->GetId());
        return 1;
    }

    int GetAreaId(lua_State* L, Map* map)
    {
        float x = Eluna::CHECKVAL<float>(L, 2);
        float y = Eluna::CHECKVAL<float>(L, 3);
        float z = Eluna::CHECKVAL<float>(L, 4);

#ifdef MANGOS
        Eluna::Push(L, map->GetTerrain()->GetAreaId(x, y, z));
#else
        Eluna::Push(L, map->GetAreaId(x, y, z));
#endif
        return 1;
    }

    int GetWorldObject(lua_State* L, Map* map)
    {
        uint64 guid = Eluna::CHECKVAL<uint64>(L, 2);

#ifdef MANGOS
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
