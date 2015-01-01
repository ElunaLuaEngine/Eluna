/*
* Copyright (C) 2010 - 2015 Eluna Lua Engine <http://emudevs.com/>
* This program is free software licensed under GPL version 3
* Please see the included DOCS/LICENSE.md for more information
*/

#ifndef WORLDOBJECTMETHODS_H
#define WORLDOBJECTMETHODS_H

namespace LuaWorldObject
{
    /**
     * Returns the name of the [WorldObject]
     *
     * @return string name
     */
    int GetName(Eluna* /*E*/, lua_State* L, WorldObject* obj)
    {
        Eluna::Push(L, obj->GetName());
        return 1;
    }

    /**
     * Returns the current [Map] object of the [WorldObject]
     *
     * @return [Map] mapObject
     */
    int GetMap(Eluna* /*E*/, lua_State* L, WorldObject* obj)
    {
        Eluna::Push(L, obj->GetMap());
        return 1;
    }

#if (!defined(TBC) && !defined(CLASSIC))
    /**
     * Returns the current phase of the [WorldObject]
     *
     * @return uint32 phase
     */
    int GetPhaseMask(Eluna* /*E*/, lua_State* L, WorldObject* obj)
    {
        Eluna::Push(L, obj->GetPhaseMask());
        return 1;
    }
#endif

    /**
     * Returns the current instance ID of the [WorldObject]
     *
     * @return uint32 instanceId
     */
    int GetInstanceId(Eluna* /*E*/, lua_State* L, WorldObject* obj)
    {
        Eluna::Push(L, obj->GetInstanceId());
        return 1;
    }

    /**
     * Returns the current area ID of the [WorldObject]
     *
     * @return uint32 areaId
     */
    int GetAreaId(Eluna* /*E*/, lua_State* L, WorldObject* obj)
    {
        Eluna::Push(L, obj->GetAreaId());
        return 1;
    }

    /**
     * Returns the current zone ID of the [WorldObject]
     *
     * @return uint32 zoneId
     */
    int GetZoneId(Eluna* /*E*/, lua_State* L, WorldObject* obj)
    {
        Eluna::Push(L, obj->GetZoneId());
        return 1;
    }

    /**
     * Returns the current map ID of the [WorldObject]
     *
     * @return uint32 mapId
     */
    int GetMapId(Eluna* /*E*/, lua_State* L, WorldObject* obj)
    {
        Eluna::Push(L, obj->GetMapId());
        return 1;
    }

    /**
     * Returns the current X coordinate of the [WorldObject]
     *
     * @return float x
     */
    int GetX(Eluna* /*E*/, lua_State* L, WorldObject* obj)
    {
        Eluna::Push(L, obj->GetPositionX());
        return 1;
    }

    /**
     * Returns the current Y coordinate of the [WorldObject]
     *
     * @return float y
     */
    int GetY(Eluna* /*E*/, lua_State* L, WorldObject* obj)
    {
        Eluna::Push(L, obj->GetPositionY());
        return 1;
    }

    /**
     * Returns the current Z coordinate of the [WorldObject]
     *
     * @return float z
     */
    int GetZ(Eluna* /*E*/, lua_State* L, WorldObject* obj)
    {
        Eluna::Push(L, obj->GetPositionZ());
        return 1;
    }

    /**
     * Returns the current orientation of the [WorldObject]
     *
     * @return float orientation / facing
     */
    int GetO(Eluna* /*E*/, lua_State* L, WorldObject* obj)
    {
        Eluna::Push(L, obj->GetOrientation());
        return 1;
    }

    /**
     * Returns the coordinates and orientation of the [WorldObject]
     *
     * @return float x : x coordinate of the [WorldObject]
     * @return float y : y coordinate of the [WorldObject]
     * @return float z : z coordinate (height) of the [WorldObject]
     * @return float o : facing / orientation of  the [WorldObject]
     */
    int GetLocation(Eluna* /*E*/, lua_State* L, WorldObject* obj)
    {
        Eluna::Push(L, obj->GetPositionX());
        Eluna::Push(L, obj->GetPositionY());
        Eluna::Push(L, obj->GetPositionZ());
        Eluna::Push(L, obj->GetOrientation());
        return 4;
    }

    /**
     * Returns the nearest [Player] object in sight of the [WorldObject] or within the given range
     *
     * @param float range = 533.33333 : optionally set range. Default range is grid size
     *
     * @return [Player] nearestPlayer
     */
    int GetNearestPlayer(Eluna* /*E*/, lua_State* L, WorldObject* obj)
    {
        float range = Eluna::CHECKVAL<float>(L, 2, SIZE_OF_GRIDS);

        Unit* target = NULL;
        ElunaUtil::WorldObjectInRangeCheck checker(true, obj, range, TYPEMASK_PLAYER);
#ifndef TRINITY
        MaNGOS::UnitLastSearcher<ElunaUtil::WorldObjectInRangeCheck> searcher(target, checker);
        Cell::VisitWorldObjects(obj, searcher, range);
#else
        Trinity::UnitLastSearcher<ElunaUtil::WorldObjectInRangeCheck> searcher(obj, target, checker);
        obj->VisitNearbyObject(range, searcher);
#endif

        Eluna::Push(L, target);
        return 1;
    }

    /**
     * Returns the nearest [GameObject] object in sight of the [WorldObject] or within the given range and/or with a specific entry ID
     *
     * @param float range = 533.33333 : optionally set range. Default range is grid size
     * @param uint32 entryId = 0 : optionally set entry ID of game object to find
     *
     * @return [GameObject] nearestGameObject
     */
    int GetNearestGameObject(Eluna* /*E*/, lua_State* L, WorldObject* obj)
    {
        float range = Eluna::CHECKVAL<float>(L, 2, SIZE_OF_GRIDS);
        uint32 entry = Eluna::CHECKVAL<uint32>(L, 3, 0);

        GameObject* target = NULL;
        ElunaUtil::WorldObjectInRangeCheck checker(true, obj, range, TYPEMASK_GAMEOBJECT, entry);
#ifndef TRINITY
        MaNGOS::GameObjectLastSearcher<ElunaUtil::WorldObjectInRangeCheck> searcher(target, checker);
        Cell::VisitGridObjects(obj, searcher, range);
#else
        Trinity::GameObjectLastSearcher<ElunaUtil::WorldObjectInRangeCheck> searcher(obj, target, checker);
        obj->VisitNearbyObject(range, searcher);
#endif

        Eluna::Push(L, target);
        return 1;
    }

    /**
     * Returns the nearest [Creature] object in sight of the [WorldObject] or within the given range and/or with a specific entry ID
     *
     * @param float range = 533.33333 : optionally set range. Default range is grid size
     * @param uint32 entryId = 0 : optionally set entry ID of creature to find
     *
     * @return [Creature] nearestCreature
     */
    int GetNearestCreature(Eluna* /*E*/, lua_State* L, WorldObject* obj)
    {
        float range = Eluna::CHECKVAL<float>(L, 2, SIZE_OF_GRIDS);
        uint32 entry = Eluna::CHECKVAL<uint32>(L, 3, 0);

        Creature* target = NULL;
        ElunaUtil::WorldObjectInRangeCheck checker(true, obj, range, TYPEMASK_UNIT, entry);
#ifndef TRINITY
        MaNGOS::CreatureLastSearcher<ElunaUtil::WorldObjectInRangeCheck> searcher(target, checker);
        Cell::VisitGridObjects(obj, searcher, range);
#else
        Trinity::CreatureLastSearcher<ElunaUtil::WorldObjectInRangeCheck> searcher(obj, target, checker);
        obj->VisitNearbyObject(range, searcher);
#endif

        Eluna::Push(L, target);
        return 1;
    }

    /**
     * Returns a table of [Player] objects in sight of the [WorldObject] or within the given range
     *
     * @param float range = 533.33333 : optionally set range. Default range is grid size
     *
     * @return table playersInRange : table of [Player]s
     */
    int GetPlayersInRange(Eluna* /*E*/, lua_State* L, WorldObject* obj)
    {
        float range = Eluna::CHECKVAL<float>(L, 2, SIZE_OF_GRIDS);

        std::list<Player*> list;
        ElunaUtil::WorldObjectInRangeCheck checker(false, obj, range, TYPEMASK_PLAYER);
#ifndef TRINITY
        MaNGOS::PlayerListSearcher<ElunaUtil::WorldObjectInRangeCheck> searcher(list, checker);
        Cell::VisitWorldObjects(obj, searcher, range);
#else
        Trinity::PlayerListSearcher<ElunaUtil::WorldObjectInRangeCheck> searcher(obj, list, checker);
        obj->VisitNearbyObject(range, searcher);
#endif

        lua_newtable(L);
        int tbl = lua_gettop(L);
        uint32 i = 0;

        for (std::list<Player*>::const_iterator it = list.begin(); it != list.end(); ++it)
        {
            Eluna::Push(L, ++i);
            Eluna::Push(L, *it);
            lua_settable(L, tbl);
        }

        lua_settop(L, tbl);
        return 1;
    }

    /**
     * Returns a table of [Creature] objects in sight of the [WorldObject] or within the given range and/or with a specific entry ID
     *
     * @param float range = 533.33333 : optionally set range. Default range is grid size
     * @param uint32 entryId = 0 : optionally set entry ID of creatures to find
     *
     * @return table creaturesInRange : table of [Creature]s
     */
    int GetCreaturesInRange(Eluna* /*E*/, lua_State* L, WorldObject* obj)
    {
        float range = Eluna::CHECKVAL<float>(L, 2, SIZE_OF_GRIDS);
        uint32 entry = Eluna::CHECKVAL<uint32>(L, 3, 0);

        std::list<Creature*> list;
        ElunaUtil::WorldObjectInRangeCheck checker(false, obj, range, TYPEMASK_UNIT, entry);
#ifndef TRINITY
        MaNGOS::CreatureListSearcher<ElunaUtil::WorldObjectInRangeCheck> searcher(list, checker);
        Cell::VisitGridObjects(obj, searcher, range);
#else
        Trinity::CreatureListSearcher<ElunaUtil::WorldObjectInRangeCheck> searcher(obj, list, checker);
        obj->VisitNearbyObject(range, searcher);
#endif

        lua_newtable(L);
        int tbl = lua_gettop(L);
        uint32 i = 0;

        for (std::list<Creature*>::const_iterator it = list.begin(); it != list.end(); ++it)
        {
            Eluna::Push(L, ++i);
            Eluna::Push(L, *it);
            lua_settable(L, tbl);
        }

        lua_settop(L, tbl);
        return 1;
    }

    /**
     * Returns a table of [GameObject] objects in sight of the [WorldObject] or within the given range and/or with a specific entry ID
     *
     * @param float range = 533.33333 : optionally set range. Default range is grid size
     * @param uint32 entryId = 0 : optionally set entry ID of game objects to find
     *
     * @return table gameObjectsInRange : table of [GameObject]s
     */
    int GetGameObjectsInRange(Eluna* /*E*/, lua_State* L, WorldObject* obj)
    {
        float range = Eluna::CHECKVAL<float>(L, 2, SIZE_OF_GRIDS);
        uint32 entry = Eluna::CHECKVAL<uint32>(L, 3, 0);

        std::list<GameObject*> list;
        ElunaUtil::WorldObjectInRangeCheck checker(false, obj, range, TYPEMASK_GAMEOBJECT, entry);
#ifndef TRINITY
        MaNGOS::GameObjectListSearcher<ElunaUtil::WorldObjectInRangeCheck> searcher(list, checker);
        Cell::VisitGridObjects(obj, searcher, range);
#else
        Trinity::GameObjectListSearcher<ElunaUtil::WorldObjectInRangeCheck> searcher(obj, list, checker);
        obj->VisitNearbyObject(range, searcher);
#endif

        lua_newtable(L);
        int tbl = lua_gettop(L);
        uint32 i = 0;

        for (std::list<GameObject*>::const_iterator it = list.begin(); it != list.end(); ++it)
        {
            Eluna::Push(L, ++i);
            Eluna::Push(L, *it);
            lua_settable(L, tbl);
        }

        lua_settop(L, tbl);
        return 1;
    }

    /**
     * Returns nearest [WorldObject] in sight of the [WorldObject].
     * The distance, type, entry and hostility requirements the [WorldObject] must match can be passed.
     *
     * @param float range = 533.33333 : optionally set range. Default range is grid size
     * @param [TypeMask] type = 0 : the [TypeMask] that the [WorldObject] must be. This can contain multiple types. 0 will be ingored
     * @param uint32 entry = 0 : the entry of the [WorldObject], 0 will be ingored
     * @param uint32 hostile = 0 : specifies whether the [WorldObject] needs to be 1 hostile, 2 friendly or 0 either
     *
     * @return [WorldObject] worldObject
     */
    int GetNearObject(Eluna* /*E*/, lua_State* L, WorldObject* obj)
    {
        float range = Eluna::CHECKVAL<float>(L, 2, SIZE_OF_GRIDS);
        uint16 type = Eluna::CHECKVAL<uint16>(L, 3, 0); // TypeMask
        uint32 entry = Eluna::CHECKVAL<uint32>(L, 4, 0);
        uint32 hostile = Eluna::CHECKVAL<uint32>(L, 5, 0); // 0 none, 1 hostile, 2 friendly

        float x, y, z;
        obj->GetPosition(x, y, z);
        ElunaUtil::WorldObjectInRangeCheck checker(true, obj, range, type, entry, hostile);

        WorldObject* target = NULL;
#ifndef TRINITY
        MaNGOS::WorldObjectLastSearcher<ElunaUtil::WorldObjectInRangeCheck> searcher(target, checker);
        Cell::VisitAllObjects(obj, searcher, range);
#else
        Trinity::WorldObjectLastSearcher<ElunaUtil::WorldObjectInRangeCheck> searcher(obj, target, checker);
        obj->VisitNearbyObject(range, searcher);
#endif

        Eluna::Push(L, target);
        return 1;
    }

    /**
     * Returns a table of [WorldObject]s in sight of the [WorldObject].
     * The distance, type, entry and hostility requirements the [WorldObject] must match can be passed.
     *
     * @param float range = 533.33333 : optionally set range. Default range is grid size
     * @param [TypeMask] type = 0 : the [TypeMask] that the [WorldObject] must be. This can contain multiple types. 0 will be ingored
     * @param uint32 entry = 0 : the entry of the [WorldObject], 0 will be ingored
     * @param uint32 hostile = 0 : specifies whether the [WorldObject] needs to be 1 hostile, 2 friendly or 0 either
     *
     * @return table worldObjectList : table of [WorldObject]s
     */
    int GetNearObjects(Eluna* /*E*/, lua_State* L, WorldObject* obj)
    {
        float range = Eluna::CHECKVAL<float>(L, 2, SIZE_OF_GRIDS);
        uint16 type = Eluna::CHECKVAL<uint16>(L, 3, 0); // TypeMask
        uint32 entry = Eluna::CHECKVAL<uint32>(L, 4, 0);
        uint32 hostile = Eluna::CHECKVAL<uint32>(L, 5, 0); // 0 none, 1 hostile, 2 friendly

        float x, y, z;
        obj->GetPosition(x, y, z);
        ElunaUtil::WorldObjectInRangeCheck checker(false, obj, range, type, entry, hostile);

        std::list<WorldObject*> list;
#ifndef TRINITY
        MaNGOS::WorldObjectListSearcher<ElunaUtil::WorldObjectInRangeCheck> searcher(list, checker);
        Cell::VisitAllObjects(obj, searcher, range);
#else
        Trinity::WorldObjectListSearcher<ElunaUtil::WorldObjectInRangeCheck> searcher(obj, list, checker);
        obj->VisitNearbyObject(range, searcher);
#endif

        lua_newtable(L);
        int tbl = lua_gettop(L);
        uint32 i = 0;

        for (std::list<WorldObject*>::const_iterator it = list.begin(); it != list.end(); ++it)
        {
            Eluna::Push(L, ++i);
            Eluna::Push(L, *it);
            lua_settable(L, tbl);
        }

        lua_settop(L, tbl);
        return 1;
    }

    /**
     * Returns the distance from this [WorldObject] to another [WorldObject], or from this [WorldObject] to a point.
     *
     * @proto dist = (obj)
     * @proto dist = (x, y, z)
     *
     * @param [WorldObject] obj
     * @param float x : the X-coordinate of the point
     * @param float y : the Y-coordinate of the point
     * @param float z : the Z-coordinate of the point
     *
     * @return float dist : the distance in yards
     */
    int GetDistance(Eluna* /*E*/, lua_State* L, WorldObject* obj)
    {
        WorldObject* target = Eluna::CHECKOBJ<WorldObject>(L, 2, false);
        if (target && target->IsInWorld())
            Eluna::Push(L, obj->GetDistance(target));
        else
        {
            float X = Eluna::CHECKVAL<float>(L, 2);
            float Y = Eluna::CHECKVAL<float>(L, 3);
            float Z = Eluna::CHECKVAL<float>(L, 4);
            Eluna::Push(L, obj->GetDistance(X, Y, Z));
        }
        return 1;
    }

    /**
     * Returns the x, y and z of a point dist away from the [WorldObject].
     *
     * @param float distance : specifies the distance of the point from the [WorldObject] in yards
     * @param float angle : specifies the angle of the point relative to the orientation / facing of the [WorldObject] in radians
     *
     * @return float x
     * @return float y
     * @return float z
     */
    int GetRelativePoint(Eluna* /*E*/, lua_State* L, WorldObject* obj)
    {
        float dist = Eluna::CHECKVAL<float>(L, 2);
        float rad = Eluna::CHECKVAL<float>(L, 3);

        float x, y, z;
        obj->GetClosePoint(x, y, z, 0.0f, dist, rad);

        Eluna::Push(L, x);
        Eluna::Push(L, y);
        Eluna::Push(L, z);
        return 3;
    }

    /**
     * Returns the angle between this [WorldObject] and another [WorldObject] or a point.
     * The angle is the angle between two points and orientation will be ignored.
     *
     * @proto dist = (obj)
     * @proto dist = (x, y)
     *
     * @param [WorldObject] object
     * @param float x
     * @param float y
     *
     * @return float angle : angle in radians in range 0..2*pi
     */
    int GetAngle(Eluna* /*E*/, lua_State* L, WorldObject* obj)
    {
        WorldObject* target = Eluna::CHECKOBJ<WorldObject>(L, 2, false);

        if (target && target->IsInWorld())
            Eluna::Push(L, obj->GetAngle(target));
        else
        {
            float x = Eluna::CHECKVAL<float>(L, 2);
            float y = Eluna::CHECKVAL<float>(L, 3);
            Eluna::Push(L, obj->GetAngle(x, y));
        }
        return 1;
    }

    /**
     * Sends a [WorldPacket] to [Player]s in sight of the [WorldObject].
     *
     * @param [WorldPacket] packet
     */
    int SendPacket(Eluna* /*E*/, lua_State* L, WorldObject* obj)
    {
        WorldPacket* data = Eluna::CHECKOBJ<WorldPacket>(L, 2);
        obj->SendMessageToSet(data, true);
        return 0;
    }

    /**
     * Spawns a [GameObject] at specified location.
     *
     * @param uint32 entry : [GameObject] entry ID
     * @param float x
     * @param float y
     * @param float z
     * @param float o
     * @param uint32 respawnDelay = 30 : respawn time in seconds
     * @return [GameObject] gameObject
     */
    int SummonGameObject(Eluna* /*E*/, lua_State* L, WorldObject* obj)
    {
        uint32 entry = Eluna::CHECKVAL<uint32>(L, 2);
        float x = Eluna::CHECKVAL<float>(L, 3);
        float y = Eluna::CHECKVAL<float>(L, 4);
        float z = Eluna::CHECKVAL<float>(L, 5);
        float o = Eluna::CHECKVAL<float>(L, 6);
        uint32 respawnDelay = Eluna::CHECKVAL<uint32>(L, 7, 30);
#ifndef TRINITY
        Eluna::Push(L, obj->SummonGameObject(entry, x, y, z, o, respawnDelay));
#else
        Eluna::Push(L, obj->SummonGameObject(entry, x, y, z, o, 0, 0, 0, 0, respawnDelay));
#endif
        return 1;
    }

    /**
     * Spawns the creature at specified location.
     *
     * @param uint32 entry : [Creature]'s entry ID
     * @param float x
     * @param float y
     * @param float z
     * @param float o
     * @param TempSummonType spawnType : defines how and when the creature despawns
     * @param uint32 despawnTimer : despawn time in seconds
     * @return [Creature] spawnedCreature
     */
    int SpawnCreature(Eluna* /*E*/, lua_State* L, WorldObject* obj)
    {
        uint32 entry = Eluna::CHECKVAL<uint32>(L, 2);
        float x = Eluna::CHECKVAL<float>(L, 3);
        float y = Eluna::CHECKVAL<float>(L, 4);
        float z = Eluna::CHECKVAL<float>(L, 5);
        float o = Eluna::CHECKVAL<float>(L, 6);
        uint32 spawnType = Eluna::CHECKVAL<uint32>(L, 7, 8);
        uint32 despawnTimer = Eluna::CHECKVAL<uint32>(L, 8, 0);

        TempSummonType type;
        switch (spawnType)
        {
            case 1:
                type = TEMPSUMMON_TIMED_OR_DEAD_DESPAWN;
                break;
            case 2:
                type = TEMPSUMMON_TIMED_OR_CORPSE_DESPAWN;
                break;
            case 3:
                type = TEMPSUMMON_TIMED_DESPAWN;
                break;
            case 4:
#ifdef TRINITY
                type = TEMPSUMMON_TIMED_DESPAWN_OUT_OF_COMBAT;
#else
                type = TEMPSUMMON_TIMED_OOC_DESPAWN;
#endif
                break;
            case 5:
                type = TEMPSUMMON_CORPSE_DESPAWN;
                break;
            case 6:
                type = TEMPSUMMON_CORPSE_TIMED_DESPAWN;
                break;
            case 7:
                type = TEMPSUMMON_DEAD_DESPAWN;
                break;
            case 8:
                type = TEMPSUMMON_MANUAL_DESPAWN;
                break;
#ifndef TRINITY
            case 9:
                type = TEMPSUMMON_TIMED_OOC_OR_CORPSE_DESPAWN;
                break;
            case 10:
                type = TEMPSUMMON_TIMED_OOC_OR_DEAD_DESPAWN;
                break;
#endif
            default:
                return luaL_argerror(L, 7, "valid SpawnType expected");
        }
        Eluna::Push(L, obj->SummonCreature(entry, x, y, z, o, type, despawnTimer));
        return 1;
    }

    /**
     * Registers a timed event to the [WorldObject]
     * When the passed function is called, the parameters `(eventId, delay, repeats, worldobject)` are passed to it.
     * Repeats will decrease on each call if the event does not repeat indefinitely
     *
     * Note that for [Creature] and [GameObject] the timed event timer ticks only if the creature is in sight of someone
     * For all [WorldObject]s the timed events are removed when the object is destoryed. This means that for example a [Player]'s events are removed on logout.
     *
     * @param function function : function to trigger when the time has passed
     * @param uint32 delay : set time in milliseconds for the event to trigger
     * @param uint32 repeats : how many times for the event to repeat, 0 is infinite
     * @return int eventId : unique ID for the timed event used to cancel it or nil
     */
    int RegisterEvent(Eluna* /*E*/, lua_State* L, WorldObject* obj)
    {
        luaL_checktype(L, 2, LUA_TFUNCTION);
        uint32 delay = Eluna::CHECKVAL<uint32>(L, 3);
        uint32 repeats = Eluna::CHECKVAL<uint32>(L, 4);

        lua_pushvalue(L, 2);
        int functionRef = luaL_ref(L, LUA_REGISTRYINDEX);
        if (functionRef != LUA_REFNIL && functionRef != LUA_NOREF)
        {
            obj->elunaEvents->AddEvent(functionRef, delay, repeats);
            Eluna::Push(L, functionRef);
        }
        return 1;
    }

    /**
     * Removes the timed event from a [WorldObject] by the specified event ID
     *
     * @param int eventId : event Id to remove
     */
    int RemoveEventById(Eluna* /*E*/, lua_State* L, WorldObject* obj)
    {
        int eventId = Eluna::CHECKVAL<int>(L, 2);
        obj->elunaEvents->RemoveEvent(eventId);
        return 0;
    }

    /**
     * Removes all timed events from a [WorldObject]
     *
     */
    int RemoveEvents(Eluna* /*E*/, lua_State* /*L*/, WorldObject* obj)
    {
        obj->elunaEvents->RemoveEvents();
        return 0;
    }

    /**
     * Returns true if the given [WorldObject] or coordinates are in the [WorldObject]'s line of sight
     *
     * @proto isInLoS = (worldobject)
     * @proto isInLoS = (x, y, z)
     *
     * @param [WorldObject] worldobject
     * @param float x
     * @param float y
     * @param float z
     * @return bool isInLoS
     */
    int IsWithinLoS(Eluna* /*E*/, lua_State* L, WorldObject* obj)
    {
        WorldObject* target = Eluna::CHECKOBJ<WorldObject>(L, 2, false);

        if (target)
            Eluna::Push(L, obj->IsWithinLOSInMap(target));
        else
        {
            float x = Eluna::CHECKVAL<float>(L, 2);
            float y = Eluna::CHECKVAL<float>(L, 3);
            float z = Eluna::CHECKVAL<float>(L, 4);
            Eluna::Push(L, obj->IsWithinLOS(x, y, z));
        }

        return 1;
    }
};
#endif
