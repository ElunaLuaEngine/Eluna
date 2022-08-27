/*
* Copyright (C) 2010 - 2016 Eluna Lua Engine <http://emudevs.com/>
* This program is free software licensed under GPL version 3
* Please see the included DOCS/LICENSE.md for more information
*/

#ifndef WORLDOBJECTMETHODS_H
#define WORLDOBJECTMETHODS_H

/***
 * Inherits all methods from: [Object]
 */
namespace LuaWorldObject
{
    /**
     * Returns the name of the [WorldObject]
     *
     * @return string name
     */
    int GetName(Eluna* E, WorldObject* obj)
    {
        E->Push(E->L, obj->GetName());
        return 1;
    }

    /**
     * Returns the current [Map] object of the [WorldObject]
     *
     * @return [Map] mapObject
     */
    int GetMap(Eluna* E, WorldObject* obj)
    {
        E->Push(E->L, obj->GetMap());
        return 1;
    }

#if (!defined(TBC) && !defined(CLASSIC))
    /**
     * Returns the current phase of the [WorldObject]
     *
     * @return uint32 phase
     */
    int GetPhaseMask(Eluna* E, WorldObject* obj)
    {
        E->Push(E->L, obj->GetPhaseMask());
        return 1;
    }

    /**
    * Sets the [WorldObject]'s phase mask.
    *
    * @param uint32 phaseMask
    * @param bool update = true : update visibility to nearby objects
    */
    int SetPhaseMask(Eluna* E, WorldObject* obj)
    {
        uint32 phaseMask = Eluna::CHECKVAL<uint32>(E->L, 2);
        bool update = Eluna::CHECKVAL<bool>(E->L, 3, true);
        obj->SetPhaseMask(phaseMask, update);
        return 0;
    }
#endif

    /**
     * Returns the current instance ID of the [WorldObject]
     *
     * @return uint32 instanceId
     */
    int GetInstanceId(Eluna* E, WorldObject* obj)
    {
        E->Push(E->L, obj->GetInstanceId());
        return 1;
    }

    /**
     * Returns the current area ID of the [WorldObject]
     *
     * @return uint32 areaId
     */
    int GetAreaId(Eluna* E, WorldObject* obj)
    {
        E->Push(E->L, obj->GetAreaId());
        return 1;
    }

    /**
     * Returns the current zone ID of the [WorldObject]
     *
     * @return uint32 zoneId
     */
    int GetZoneId(Eluna* E, WorldObject* obj)
    {
        E->Push(E->L, obj->GetZoneId());
        return 1;
    }

    /**
     * Returns the current map ID of the [WorldObject]
     *
     * @return uint32 mapId
     */
    int GetMapId(Eluna* E, WorldObject* obj)
    {
        E->Push(E->L, obj->GetMapId());
        return 1;
    }

    /**
     * Returns the current X coordinate of the [WorldObject]
     *
     * @return float x
     */
    int GetX(Eluna* E, WorldObject* obj)
    {
        E->Push(E->L, obj->GetPositionX());
        return 1;
    }

    /**
     * Returns the current Y coordinate of the [WorldObject]
     *
     * @return float y
     */
    int GetY(Eluna* E, WorldObject* obj)
    {
        E->Push(E->L, obj->GetPositionY());
        return 1;
    }

    /**
     * Returns the current Z coordinate of the [WorldObject]
     *
     * @return float z
     */
    int GetZ(Eluna* E, WorldObject* obj)
    {
        E->Push(E->L, obj->GetPositionZ());
        return 1;
    }

    /**
     * Returns the current orientation of the [WorldObject]
     *
     * @return float orientation / facing
     */
    int GetO(Eluna* E, WorldObject* obj)
    {
        E->Push(E->L, obj->GetOrientation());
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
    int GetLocation(Eluna* E, WorldObject* obj)
    {
        E->Push(E->L, obj->GetPositionX());
        E->Push(E->L, obj->GetPositionY());
        E->Push(E->L, obj->GetPositionZ());
        E->Push(E->L, obj->GetOrientation());
        return 4;
    }

    /**
     * Returns the nearest [Player] object in sight of the [WorldObject] or within the given range
     *
     * @param float range = 533.33333 : optionally set range. Default range is grid size
     * @param uint32 hostile = 0 : 0 both, 1 hostile, 2 friendly
     * @param uint32 dead = 1 : 0 both, 1 alive, 2 dead
     *
     * @return [Player] nearestPlayer
     */
    int GetNearestPlayer(Eluna* E, WorldObject* obj)
    {
        float range = Eluna::CHECKVAL<float>(E->L, 2, SIZE_OF_GRIDS);
        uint32 hostile = Eluna::CHECKVAL<uint32>(E->L, 3, 0);
        uint32 dead = Eluna::CHECKVAL<uint32>(E->L, 4, 1);

        Unit* target = NULL;
        ElunaUtil::WorldObjectInRangeCheck checker(true, obj, range, TYPEMASK_PLAYER, 0, hostile, dead);
#ifdef TRINITY
        Trinity::UnitLastSearcher<ElunaUtil::WorldObjectInRangeCheck> searcher(obj, target, checker);
        Cell::VisitAllObjects(obj, searcher, range);

#elif AZEROTHCORE
        Acore::UnitLastSearcher<ElunaUtil::WorldObjectInRangeCheck> searcher(obj, target, checker);
        Cell::VisitAllObjects(obj, searcher, range);
#else
        MaNGOS::UnitLastSearcher<ElunaUtil::WorldObjectInRangeCheck> searcher(target, checker);
        Cell::VisitWorldObjects(obj, searcher, range);
#endif

        E->Push(E->L, target);
        return 1;
    }

    /**
     * Returns the nearest [GameObject] object in sight of the [WorldObject] or within the given range and/or with a specific entry ID
     *
     * @param float range = 533.33333 : optionally set range. Default range is grid size
     * @param uint32 entryId = 0 : optionally set entry ID of game object to find
     * @param uint32 hostile = 0 : 0 both, 1 hostile, 2 friendly
     *
     * @return [GameObject] nearestGameObject
     */
    int GetNearestGameObject(Eluna* E, WorldObject* obj)
    {
        float range = Eluna::CHECKVAL<float>(E->L, 2, SIZE_OF_GRIDS);
        uint32 entry = Eluna::CHECKVAL<uint32>(E->L, 3, 0);
        uint32 hostile = Eluna::CHECKVAL<uint32>(E->L, 4, 0);

        GameObject* target = NULL;
        ElunaUtil::WorldObjectInRangeCheck checker(true, obj, range, TYPEMASK_GAMEOBJECT, entry, hostile);
#ifdef TRINITY
        Trinity::GameObjectLastSearcher<ElunaUtil::WorldObjectInRangeCheck> searcher(obj, target, checker);
        Cell::VisitAllObjects(obj, searcher, range);
#elif AZEROTHCORE
        Acore::GameObjectLastSearcher<ElunaUtil::WorldObjectInRangeCheck> searcher(obj, target, checker);
        Cell::VisitAllObjects(obj, searcher, range);
#else
        MaNGOS::GameObjectLastSearcher<ElunaUtil::WorldObjectInRangeCheck> searcher(target, checker);
        Cell::VisitGridObjects(obj, searcher, range);
#endif

        E->Push(E->L, target);
        return 1;
    }

    /**
     * Returns the nearest [Creature] object in sight of the [WorldObject] or within the given range and/or with a specific entry ID
     *
     * @param float range = 533.33333 : optionally set range. Default range is grid size
     * @param uint32 entryId = 0 : optionally set entry ID of creature to find
     * @param uint32 hostile = 0 : 0 both, 1 hostile, 2 friendly
     * @param uint32 dead = 1 : 0 both, 1 alive, 2 dead
     *
     * @return [Creature] nearestCreature
     */
    int GetNearestCreature(Eluna* E, WorldObject* obj)
    {
        float range = Eluna::CHECKVAL<float>(E->L, 2, SIZE_OF_GRIDS);
        uint32 entry = Eluna::CHECKVAL<uint32>(E->L, 3, 0);
        uint32 hostile = Eluna::CHECKVAL<uint32>(E->L, 4, 0);
        uint32 dead = Eluna::CHECKVAL<uint32>(E->L, 5, 1);

        Creature* target = NULL;
        ElunaUtil::WorldObjectInRangeCheck checker(true, obj, range, TYPEMASK_UNIT, entry, hostile, dead);
#ifdef TRINITY
        Trinity::CreatureLastSearcher<ElunaUtil::WorldObjectInRangeCheck> searcher(obj, target, checker);
        Cell::VisitAllObjects(obj, searcher, range);
#elif AZEROTHCORE
        Acore::CreatureLastSearcher<ElunaUtil::WorldObjectInRangeCheck> searcher(obj, target, checker);
        Cell::VisitAllObjects(obj, searcher, range);
#else
        MaNGOS::CreatureLastSearcher<ElunaUtil::WorldObjectInRangeCheck> searcher(target, checker);
        Cell::VisitGridObjects(obj, searcher, range);

#endif

        E->Push(E->L, target);
        return 1;
    }

    /**
     * Returns a table of [Player] objects in sight of the [WorldObject] or within the given range
     *
     * @param float range = 533.33333 : optionally set range. Default range is grid size
     * @param uint32 hostile = 0 : 0 both, 1 hostile, 2 friendly
     * @param uint32 dead = 1 : 0 both, 1 alive, 2 dead
     *
     * @return table playersInRange : table of [Player]s
     */
    int GetPlayersInRange(Eluna* E, WorldObject* obj)
    {
        float range = Eluna::CHECKVAL<float>(E->L, 2, SIZE_OF_GRIDS);
        uint32 hostile = Eluna::CHECKVAL<uint32>(E->L, 3, 0);
        uint32 dead = Eluna::CHECKVAL<uint32>(E->L, 4, 1);

        std::list<Player*> list;
        ElunaUtil::WorldObjectInRangeCheck checker(false, obj, range, TYPEMASK_PLAYER, 0, hostile, dead);
#ifdef TRINITY
        Trinity::PlayerListSearcher<ElunaUtil::WorldObjectInRangeCheck> searcher(obj, list, checker);
        Cell::VisitAllObjects(obj, searcher, range);
#elif AZEROTHCORE
        Acore::PlayerListSearcher<ElunaUtil::WorldObjectInRangeCheck> searcher(obj, list, checker);
        Cell::VisitAllObjects(obj, searcher, range);
#else
        MaNGOS::PlayerListSearcher<ElunaUtil::WorldObjectInRangeCheck> searcher(list, checker);
        Cell::VisitWorldObjects(obj, searcher, range);
#endif

        lua_createtable(E->L, list.size(), 0);
        int tbl = lua_gettop(E->L);
        uint32 i = 0;

        for (std::list<Player*>::const_iterator it = list.begin(); it != list.end(); ++it)
        {
            E->Push(E->L, *it);
            lua_rawseti(E->L, tbl, ++i);
        }

        lua_settop(E->L, tbl);
        return 1;
    }

    /**
     * Returns a table of [Creature] objects in sight of the [WorldObject] or within the given range and/or with a specific entry ID
     *
     * @param float range = 533.33333 : optionally set range. Default range is grid size
     * @param uint32 entryId = 0 : optionally set entry ID of creatures to find
     * @param uint32 hostile = 0 : 0 both, 1 hostile, 2 friendly
     * @param uint32 dead = 1 : 0 both, 1 alive, 2 dead
     *
     * @return table creaturesInRange : table of [Creature]s
     */
    int GetCreaturesInRange(Eluna* E, WorldObject* obj)
    {
        float range = Eluna::CHECKVAL<float>(E->L, 2, SIZE_OF_GRIDS);
        uint32 entry = Eluna::CHECKVAL<uint32>(E->L, 3, 0);
        uint32 hostile = Eluna::CHECKVAL<uint32>(E->L, 4, 0);
        uint32 dead = Eluna::CHECKVAL<uint32>(E->L, 5, 1);

        std::list<Creature*> list;
        ElunaUtil::WorldObjectInRangeCheck checker(false, obj, range, TYPEMASK_UNIT, entry, hostile, dead);
#ifdef TRINITY
        Trinity::CreatureListSearcher<ElunaUtil::WorldObjectInRangeCheck> searcher(obj, list, checker);
        Cell::VisitAllObjects(obj, searcher, range);
#elif defined AZEROTHCORE
        Acore::CreatureListSearcher<ElunaUtil::WorldObjectInRangeCheck> searcher(obj, list, checker);
        Cell::VisitAllObjects(obj, searcher, range);
#else
        MaNGOS::CreatureListSearcher<ElunaUtil::WorldObjectInRangeCheck> searcher(list, checker);
        Cell::VisitGridObjects(obj, searcher, range);
#endif

        lua_createtable(E->L, list.size(), 0);
        int tbl = lua_gettop(E->L);
        uint32 i = 0;

        for (std::list<Creature*>::const_iterator it = list.begin(); it != list.end(); ++it)
        {
            E->Push(E->L, *it);
            lua_rawseti(E->L, tbl, ++i);
        }

        lua_settop(E->L, tbl);
        return 1;
    }

    /**
     * Returns a table of [GameObject] objects in sight of the [WorldObject] or within the given range and/or with a specific entry ID
     *
     * @param float range = 533.33333 : optionally set range. Default range is grid size
     * @param uint32 entryId = 0 : optionally set entry ID of game objects to find
     * @param uint32 hostile = 0 : 0 both, 1 hostile, 2 friendly
     *
     * @return table gameObjectsInRange : table of [GameObject]s
     */
    int GetGameObjectsInRange(Eluna* E, WorldObject* obj)
    {
        float range = Eluna::CHECKVAL<float>(E->L, 2, SIZE_OF_GRIDS);
        uint32 entry = Eluna::CHECKVAL<uint32>(E->L, 3, 0);
        uint32 hostile = Eluna::CHECKVAL<uint32>(E->L, 4, 0);

        std::list<GameObject*> list;
        ElunaUtil::WorldObjectInRangeCheck checker(false, obj, range, TYPEMASK_GAMEOBJECT, entry, hostile);
#ifdef TRINITY
        Trinity::GameObjectListSearcher<ElunaUtil::WorldObjectInRangeCheck> searcher(obj, list, checker);
        Cell::VisitAllObjects(obj, searcher, range);
#elif AZEROTHCORE
        Acore::GameObjectListSearcher<ElunaUtil::WorldObjectInRangeCheck> searcher(obj, list, checker);
        Cell::VisitAllObjects(obj, searcher, range);
#else
        MaNGOS::GameObjectListSearcher<ElunaUtil::WorldObjectInRangeCheck> searcher(list, checker);
        Cell::VisitGridObjects(obj, searcher, range);
#endif

        lua_createtable(E->L, list.size(), 0);
        int tbl = lua_gettop(E->L);
        uint32 i = 0;

        for (std::list<GameObject*>::const_iterator it = list.begin(); it != list.end(); ++it)
        {
            E->Push(E->L, *it);
            lua_rawseti(E->L, tbl, ++i);
        }

        lua_settop(E->L, tbl);
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
     * @param uint32 dead = 1 : 0 both, 1 alive, 2 dead
     *
     * @return [WorldObject] worldObject
     */
    int GetNearObject(Eluna* E, WorldObject* obj)
    {
        float range = Eluna::CHECKVAL<float>(E->L, 2, SIZE_OF_GRIDS);
        uint16 type = Eluna::CHECKVAL<uint16>(E->L, 3, 0); // TypeMask
        uint32 entry = Eluna::CHECKVAL<uint32>(E->L, 4, 0);
        uint32 hostile = Eluna::CHECKVAL<uint32>(E->L, 5, 0); // 0 none, 1 hostile, 2 friendly
        uint32 dead = Eluna::CHECKVAL<uint32>(E->L, 6, 1); // 0 both, 1 alive, 2 dead

        float x, y, z;
        obj->GetPosition(x, y, z);
        ElunaUtil::WorldObjectInRangeCheck checker(true, obj, range, type, entry, hostile, dead);

        WorldObject* target = NULL;
#ifdef TRINITY
        Trinity::WorldObjectLastSearcher<ElunaUtil::WorldObjectInRangeCheck> searcher(obj, target, checker);
        Cell::VisitAllObjects(obj, searcher, range);
#elif AZEROTHCORE
        Acore::WorldObjectLastSearcher<ElunaUtil::WorldObjectInRangeCheck> searcher(obj, target, checker);
        Cell::VisitAllObjects(obj, searcher, range);
#else
        MaNGOS::WorldObjectLastSearcher<ElunaUtil::WorldObjectInRangeCheck> searcher(target, checker);
        Cell::VisitAllObjects(obj, searcher, range);
#endif

        E->Push(E->L, target);
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
     * @param uint32 dead = 1 : 0 both, 1 alive, 2 dead
     *
     * @return table worldObjectList : table of [WorldObject]s
     */
    int GetNearObjects(Eluna* E, WorldObject* obj)
    {
        float range = Eluna::CHECKVAL<float>(E->L, 2, SIZE_OF_GRIDS);
        uint16 type = Eluna::CHECKVAL<uint16>(E->L, 3, 0); // TypeMask
        uint32 entry = Eluna::CHECKVAL<uint32>(E->L, 4, 0);
        uint32 hostile = Eluna::CHECKVAL<uint32>(E->L, 5, 0); // 0 none, 1 hostile, 2 friendly
        uint32 dead = Eluna::CHECKVAL<uint32>(E->L, 6, 1); // 0 both, 1 alive, 2 dead

        float x, y, z;
        obj->GetPosition(x, y, z);
        ElunaUtil::WorldObjectInRangeCheck checker(false, obj, range, type, entry, hostile, dead);

        std::list<WorldObject*> list;
#ifdef TRINITY
        Trinity::WorldObjectListSearcher<ElunaUtil::WorldObjectInRangeCheck> searcher(obj, list, checker);
        Cell::VisitAllObjects(obj, searcher, range);
#elif AZEROTHCORE
        Acore::WorldObjectListSearcher<ElunaUtil::WorldObjectInRangeCheck> searcher(obj, list, checker);
        Cell::VisitAllObjects(obj, searcher, range);
#else
        MaNGOS::WorldObjectListSearcher<ElunaUtil::WorldObjectInRangeCheck> searcher(list, checker);
        Cell::VisitAllObjects(obj, searcher, range);
#endif

        lua_createtable(E->L, list.size(), 0);
        int tbl = lua_gettop(E->L);
        uint32 i = 0;

        for (std::list<WorldObject*>::const_iterator it = list.begin(); it != list.end(); ++it)
        {
            E->Push(E->L, *it);
            lua_rawseti(E->L, tbl, ++i);
        }

        lua_settop(E->L, tbl);
        return 1;
    }

    /**
     * Returns the distance from this [WorldObject] to another [WorldObject], or from this [WorldObject] to a point in 3d space.
     *
     * The function takes into account the given object sizes. See also [WorldObject:GetExactDistance], [WorldObject:GetDistance2d]
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
    int GetDistance(Eluna* E, WorldObject* obj)
    {
        WorldObject* target = Eluna::CHECKOBJ<WorldObject>(E->L, 2, false);
        if (target)
            E->Push(E->L, obj->GetDistance(target));
        else
        {
            float X = Eluna::CHECKVAL<float>(E->L, 2);
            float Y = Eluna::CHECKVAL<float>(E->L, 3);
            float Z = Eluna::CHECKVAL<float>(E->L, 4);
            E->Push(E->L, obj->GetDistance(X, Y, Z));
        }
        return 1;
    }

    /**
     * Returns the distance from this [WorldObject] to another [WorldObject], or from this [WorldObject] to a point in 3d space.
     *
     * The function does not take into account the given object sizes, which means only the object coordinates are compared. See also [WorldObject:GetDistance], [WorldObject:GetDistance2d]
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
    int GetExactDistance(Eluna* E, WorldObject* obj)
    {
        float x, y, z;
        obj->GetPosition(x, y, z);
        WorldObject* target = Eluna::CHECKOBJ<WorldObject>(E->L, 2, false);
        if (target)
        {
            float x2, y2, z2;
            target->GetPosition(x2, y2, z2);
            x -= x2;
            y -= y2;
            z -= z2;
        }
        else
        {
            x -= Eluna::CHECKVAL<float>(E->L, 2);
            y -= Eluna::CHECKVAL<float>(E->L, 3);
            z -= Eluna::CHECKVAL<float>(E->L, 4);
        }

        E->Push(E->L, std::sqrt(x*x + y*y + z*z));
        return 1;
    }

    /**
     * Returns the distance from this [WorldObject] to another [WorldObject], or from this [WorldObject] to a point in 2d space.
     *
     * The function takes into account the given object sizes. See also [WorldObject:GetDistance], [WorldObject:GetExactDistance2d]
     *
     * @proto dist = (obj)
     * @proto dist = (x, y)
     *
     * @param [WorldObject] obj
     * @param float x : the X-coordinate of the point
     * @param float y : the Y-coordinate of the point
     *
     * @return float dist : the distance in yards
     */
    int GetDistance2d(Eluna* E, WorldObject* obj)
    {
        WorldObject* target = Eluna::CHECKOBJ<WorldObject>(E->L, 2, false);
        if (target)
            E->Push(E->L, obj->GetDistance2d(target));
        else
        {
            float X = Eluna::CHECKVAL<float>(E->L, 2);
            float Y = Eluna::CHECKVAL<float>(E->L, 3);
            E->Push(E->L, obj->GetDistance2d(X, Y));
        }
        return 1;
    }

    /**
     * Returns the distance from this [WorldObject] to another [WorldObject], or from this [WorldObject] to a point in 2d space.
     *
     * The function does not take into account the given object sizes, which means only the object coordinates are compared. See also [WorldObject:GetDistance], [WorldObject:GetDistance2d]
     *
     * @proto dist = (obj)
     * @proto dist = (x, y)
     *
     * @param [WorldObject] obj
     * @param float x : the X-coordinate of the point
     * @param float y : the Y-coordinate of the point
     *
     * @return float dist : the distance in yards
     */
    int GetExactDistance2d(Eluna* E, WorldObject* obj)
    {
        float x, y, z;
        obj->GetPosition(x, y, z);
        WorldObject* target = Eluna::CHECKOBJ<WorldObject>(E->L, 2, false);
        if (target)
        {
            float x2, y2, z2;
            target->GetPosition(x2, y2, z2);
            x -= x2;
            y -= y2;
        }
        else
        {
            x -= Eluna::CHECKVAL<float>(E->L, 2);
            y -= Eluna::CHECKVAL<float>(E->L, 3);
        }

        E->Push(E->L, std::sqrt(x*x + y*y));
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
    int GetRelativePoint(Eluna* E, WorldObject* obj)
    {
        float dist = Eluna::CHECKVAL<float>(E->L, 2);
        float rad = Eluna::CHECKVAL<float>(E->L, 3);

        float x, y, z;
        obj->GetClosePoint(x, y, z, 0.0f, dist, rad);

        E->Push(E->L, x);
        E->Push(E->L, y);
        E->Push(E->L, z);
        return 3;
    }

    /**
     * Returns the angle between this [WorldObject] and another [WorldObject] or a point.
     *
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
    int GetAngle(Eluna* E, WorldObject* obj)
    {
        WorldObject* target = Eluna::CHECKOBJ<WorldObject>(E->L, 2, false);
#if defined TRINITY && !AZEROTHCORE
        if (target)
            E->Push(E->L, obj->GetAbsoluteAngle(target));
        else
        {
            float x = Eluna::CHECKVAL<float>(E->L, 2);
            float y = Eluna::CHECKVAL<float>(E->L, 3);
            E->Push(E->L, obj->GetAbsoluteAngle(x, y));
        }
#else
        if (target)
            E->Push(E->L, obj->GetAngle(target));
        else
        {
            float x = Eluna::CHECKVAL<float>(E->L, 2);
            float y = Eluna::CHECKVAL<float>(E->L, 3);
            E->Push(E->L, obj->GetAngle(x, y));
        }
#endif
        return 1;
    }

    /**
     * Sends a [WorldPacket] to [Player]s in sight of the [WorldObject].
     *
     * @param [WorldPacket] packet
     */
    int SendPacket(Eluna* E, WorldObject* obj)
    {
        WorldPacket* data = Eluna::CHECKOBJ<WorldPacket>(E->L, 2);
#ifdef CMANGOS
        obj->SendMessageToSet(*data, true);
#else
        obj->SendMessageToSet(data, true);
#endif
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
    int SummonGameObject(Eluna* E, WorldObject* obj)
    {
        uint32 entry = Eluna::CHECKVAL<uint32>(E->L, 2);
        float x = Eluna::CHECKVAL<float>(E->L, 3);
        float y = Eluna::CHECKVAL<float>(E->L, 4);
        float z = Eluna::CHECKVAL<float>(E->L, 5);
        float o = Eluna::CHECKVAL<float>(E->L, 6);
        uint32 respawnDelay = Eluna::CHECKVAL<uint32>(E->L, 7, 30);
#ifdef TRINITY
        QuaternionData rot = QuaternionData::fromEulerAnglesZYX(o, 0.f, 0.f);
        E->Push(E->L, obj->SummonGameObject(entry, Position(x, y, z, o), rot, Seconds(respawnDelay)));
#elif AZEROTHCORE
        E->Push(E->L, obj->SummonGameObject(entry, x, y, z, o, 0, 0, 0, 0, respawnDelay));
#else
        E->Push(E->L, obj->SummonGameObject(entry, x, y, z, o, respawnDelay));
#endif
        return 1;
    }

    /**
     * Spawns the creature at specified location.
     *
     *     enum TempSummonType
     *     {
     *         TEMPSUMMON_TIMED_OR_DEAD_DESPAWN       = 1, // despawns after a specified time OR when the creature disappears
     *         TEMPSUMMON_TIMED_OR_CORPSE_DESPAWN     = 2, // despawns after a specified time OR when the creature dies
     *         TEMPSUMMON_TIMED_DESPAWN               = 3, // despawns after a specified time
     *         TEMPSUMMON_TIMED_DESPAWN_OUT_OF_COMBAT = 4, // despawns after a specified time after the creature is out of combat
     *         TEMPSUMMON_CORPSE_DESPAWN              = 5, // despawns instantly after death
     *         TEMPSUMMON_CORPSE_TIMED_DESPAWN        = 6, // despawns after a specified time after death
     *         TEMPSUMMON_DEAD_DESPAWN                = 7, // despawns when the creature disappears
     *         TEMPSUMMON_MANUAL_DESPAWN              = 8, // despawns when UnSummon() is called
     *         TEMPSUMMON_TIMED_OOC_OR_CORPSE_DESPAWN = 9, // despawns after a specified time (OOC) OR when the creature dies
     *         TEMPSUMMON_TIMED_OOC_OR_DEAD_DESPAWN   = 10 // despawns after a specified time (OOC) OR when the creature disappears
     *     };
     *
     * @param uint32 entry : [Creature]'s entry ID
     * @param float x
     * @param float y
     * @param float z
     * @param float o
     * @param [TempSummonType] spawnType = MANUAL_DESPAWN : defines how and when the creature despawns
     * @param uint32 despawnTimer = 0 : despawn time in milliseconds
     * @return [Creature] spawnedCreature
     */
    int SpawnCreature(Eluna* E, WorldObject* obj)
    {
        uint32 entry = Eluna::CHECKVAL<uint32>(E->L, 2);
        float x = Eluna::CHECKVAL<float>(E->L, 3);
        float y = Eluna::CHECKVAL<float>(E->L, 4);
        float z = Eluna::CHECKVAL<float>(E->L, 5);
        float o = Eluna::CHECKVAL<float>(E->L, 6);
        uint32 spawnType = Eluna::CHECKVAL<uint32>(E->L, 7, 8);
        uint32 despawnTimer = Eluna::CHECKVAL<uint32>(E->L, 8, 0);

#if defined TRINITY || AZEROTHCORE
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
                type = TEMPSUMMON_TIMED_DESPAWN_OUT_OF_COMBAT;
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
            default:
                return luaL_argerror(E->L, 7, "valid SpawnType expected");
        }
#else
        TempSpawnType type;
        switch (spawnType)
        {
            case 1:
                type = TEMPSPAWN_TIMED_OR_DEAD_DESPAWN;
                break;
            case 2:
                type = TEMPSPAWN_TIMED_OR_CORPSE_DESPAWN;
                break;
            case 3:
                type = TEMPSPAWN_TIMED_DESPAWN;
                break;
            case 4:
                type = TEMPSPAWN_TIMED_OOC_DESPAWN;
                break;
            case 5:
                type = TEMPSPAWN_CORPSE_DESPAWN;
                break;
            case 6:
                type = TEMPSPAWN_CORPSE_TIMED_DESPAWN;
                break;
            case 7:
                type = TEMPSPAWN_DEAD_DESPAWN;
                break;
            case 8:
                type = TEMPSPAWN_MANUAL_DESPAWN;
                break;
            case 9:
                type = TEMPSPAWN_TIMED_OOC_OR_CORPSE_DESPAWN;
                break;
            case 10:
                type = TEMPSPAWN_TIMED_OOC_OR_DEAD_DESPAWN;
                break;
            default:
                return luaL_argerror(E->L, 7, "valid SpawnType expected");
        }
#endif
#ifdef TRINITY
        E->Push(E->L, obj->SummonCreature(entry, x, y, z, o, type, Milliseconds(despawnTimer)));
#else
        E->Push(E->L, obj->SummonCreature(entry, x, y, z, o, type, despawnTimer));
#endif
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
     *     local function Timed(eventid, delay, repeats, worldobject)
     *         print(worldobject:GetName())
     *     end
     *     worldobject:RegisterEvent(Timed, 1000, 5) -- do it after 1 second 5 times
     *     worldobject:RegisterEvent(Timed, {1000, 10000}, 0) -- do it after 1 to 10 seconds forever
     *
     * @proto eventId = (function, delay)
     * @proto eventId = (function, delaytable)
     * @proto eventId = (function, delay, repeats)
     * @proto eventId = (function, delaytable, repeats)
     *
     * @param function function : function to trigger when the time has passed
     * @param uint32 delay : set time in milliseconds for the event to trigger
     * @param table delaytable : a table `{min, max}` containing the minimum and maximum delay time
     * @param uint32 repeats = 1 : how many times for the event to repeat, 0 is infinite
     * @return int eventId : unique ID for the timed event used to cancel it or nil
     */
    int RegisterEvent(Eluna* E, WorldObject* obj)
    {
        luaL_checktype(E->L, 2, LUA_TFUNCTION);
        uint32 min, max;
        if (lua_istable(E->L, 3))
        {
            E->Push(E->L, 1);
            lua_gettable(E->L, 3);
            min = Eluna::CHECKVAL<uint32>(E->L, -1);
            E->Push(E->L, 2);
            lua_gettable(E->L, 3);
            max = Eluna::CHECKVAL<uint32>(E->L, -1);
            lua_pop(E->L, 2);
        }
        else
            min = max = Eluna::CHECKVAL<uint32>(E->L, 3);
        uint32 repeats = Eluna::CHECKVAL<uint32>(E->L, 4, 1);

        if (min > max)
            return luaL_argerror(E->L, 3, "min is bigger than max delay");

        lua_pushvalue(E->L, 2);
        int functionRef = luaL_ref(E->L, LUA_REGISTRYINDEX);
        if (functionRef != LUA_REFNIL && functionRef != LUA_NOREF)
        {
            obj->elunaEvents->AddEvent(functionRef, min, max, repeats);
            E->Push(E->L, functionRef);
        }
        return 1;
    }

    /**
     * Removes the timed event from a [WorldObject] by the specified event ID
     *
     * @param int eventId : event Id to remove
     */
    int RemoveEventById(Eluna* E, WorldObject* obj)
    {
        int eventId = Eluna::CHECKVAL<int>(E->L, 2);
        obj->elunaEvents->SetState(eventId, LUAEVENT_STATE_ABORT);
        return 0;
    }

    /**
     * Removes all timed events from a [WorldObject]
     *
     */
    int RemoveEvents(Eluna* /*E*/, WorldObject* obj)
    {
        obj->elunaEvents->SetStates(LUAEVENT_STATE_ABORT);
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
    int IsWithinLoS(Eluna* E, WorldObject* obj)
    {
        WorldObject* target = Eluna::CHECKOBJ<WorldObject>(E->L, 2, false);

        if (target)
            E->Push(E->L, obj->IsWithinLOSInMap(target));
        else
        {
            float x = Eluna::CHECKVAL<float>(E->L, 2);
            float y = Eluna::CHECKVAL<float>(E->L, 3);
            float z = Eluna::CHECKVAL<float>(E->L, 4);
            E->Push(E->L, obj->IsWithinLOS(x, y, z));
        }

        return 1;
    }

    /**
     * Returns true if the [WorldObject]s are on the same map
     *
     * @param [WorldObject] worldobject
     * @return bool isInMap
     */
    int IsInMap(Eluna* E, WorldObject* obj)
    {
        WorldObject* target = Eluna::CHECKOBJ<WorldObject>(E->L, 2, true);
        E->Push(E->L, obj->IsInMap(target));
        return 1;
    }

    /**
     * Returns true if the point is in the given distance of the [WorldObject]
     *
     * Notice that the distance is measured from the edge of the [WorldObject].
     *
     * @param float x
     * @param float y
     * @param float z
     * @param float distance
     * @return bool isInDistance
     */
    int IsWithinDist3d(Eluna* E, WorldObject* obj)
    {
        float x = Eluna::CHECKVAL<float>(E->L, 2);
        float y = Eluna::CHECKVAL<float>(E->L, 3);
        float z = Eluna::CHECKVAL<float>(E->L, 4);
        float dist = Eluna::CHECKVAL<float>(E->L, 5);
        E->Push(E->L, obj->IsWithinDist3d(x, y, z, dist));
        return 1;
    }

    /**
     * Returns true if the point is in the given distance of the [WorldObject]
     *
     * The distance is measured only in x,y coordinates.
     * Notice that the distance is measured from the edge of the [WorldObject].
     *
     * @param float x
     * @param float y
     * @param float distance
     * @return bool isInDistance
     */
    int IsWithinDist2d(Eluna* E, WorldObject* obj)
    {
        float x = Eluna::CHECKVAL<float>(E->L, 2);
        float y = Eluna::CHECKVAL<float>(E->L, 3);
        float dist = Eluna::CHECKVAL<float>(E->L, 4);
        E->Push(E->L, obj->IsWithinDist2d(x, y, dist));
        return 1;
    }

    /**
     * Returns true if the target is in the given distance of the [WorldObject]
     *
     * Notice that the distance is measured from the edge of the [WorldObject]s.
     *
     * @param [WorldObject] target
     * @param float distance
     * @param bool is3D = true : if false, only x,y coordinates used for checking
     * @return bool isInDistance
     */
    int IsWithinDist(Eluna* E, WorldObject* obj)
    {
        WorldObject* target = Eluna::CHECKOBJ<WorldObject>(E->L, 2, true);
        float distance = Eluna::CHECKVAL<float>(E->L, 3);
        bool is3D = Eluna::CHECKVAL<bool>(E->L, 4, true);
        E->Push(E->L, obj->IsWithinDist(target, distance, is3D));
        return 1;
    }

    /**
     * Returns true if the [WorldObject] is on the same map and within given distance
     *
     * Notice that the distance is measured from the edge of the [WorldObject]s.
     *
     * @param [WorldObject] target
     * @param float distance
     * @param bool is3D = true : if false, only x,y coordinates used for checking
     * @return bool isInDistance
     */
    int IsWithinDistInMap(Eluna* E, WorldObject* obj)
    {
        WorldObject* target = Eluna::CHECKOBJ<WorldObject>(E->L, 2);
        float distance = Eluna::CHECKVAL<float>(E->L, 3);
        bool is3D = Eluna::CHECKVAL<bool>(E->L, 4, true);

        E->Push(E->L, obj->IsWithinDistInMap(target, distance, is3D));
        return 1;
    }

    /**
     * Returns true if the target is within given range
     *
     * Notice that the distance is measured from the edge of the [WorldObject]s.
     *
     * @param [WorldObject] target
     * @param float minrange
     * @param float maxrange
     * @param bool is3D = true : if false, only x,y coordinates used for checking
     * @return bool isInDistance
     */
    int IsInRange(Eluna* E, WorldObject* obj)
    {
        WorldObject* target = Eluna::CHECKOBJ<WorldObject>(E->L, 2);
        float minrange = Eluna::CHECKVAL<float>(E->L, 3);
        float maxrange = Eluna::CHECKVAL<float>(E->L, 4);
        bool is3D = Eluna::CHECKVAL<bool>(E->L, 5, true);

        E->Push(E->L, obj->IsInRange(target, minrange, maxrange, is3D));
        return 1;
    }

    /**
     * Returns true if the point is within given range
     *
     * Notice that the distance is measured from the edge of the [WorldObject].
     *
     * @param float x
     * @param float y
     * @param float minrange
     * @param float maxrange
     * @return bool isInDistance
     */
    int IsInRange2d(Eluna* E, WorldObject* obj)
    {
        float x = Eluna::CHECKVAL<float>(E->L, 2);
        float y = Eluna::CHECKVAL<float>(E->L, 3);
        float minrange = Eluna::CHECKVAL<float>(E->L, 4);
        float maxrange = Eluna::CHECKVAL<float>(E->L, 5);

        E->Push(E->L, obj->IsInRange2d(x, y, minrange, maxrange));
        return 1;
    }

    /**
     * Returns true if the point is within given range
     *
     * Notice that the distance is measured from the edge of the [WorldObject].
     *
     * @param float x
     * @param float y
     * @param float z
     * @param float minrange
     * @param float maxrange
     * @return bool isInDistance
     */
    int IsInRange3d(Eluna* E, WorldObject* obj)
    {
        float x = Eluna::CHECKVAL<float>(E->L, 2);
        float y = Eluna::CHECKVAL<float>(E->L, 3);
        float z = Eluna::CHECKVAL<float>(E->L, 4);
        float minrange = Eluna::CHECKVAL<float>(E->L, 5);
        float maxrange = Eluna::CHECKVAL<float>(E->L, 6);

        E->Push(E->L, obj->IsInRange3d(x, y, z, minrange, maxrange));
        return 1;
    }

    /**
     * Returns true if the target is in the given arc in front of the [WorldObject]
     *
     * @param [WorldObject] target
     * @param float arc = pi
     * @return bool isInFront
     */
    int IsInFront(Eluna* E, WorldObject* obj)
    {
        WorldObject* target = Eluna::CHECKOBJ<WorldObject>(E->L, 2);
        float arc = Eluna::CHECKVAL<float>(E->L, 3, static_cast<float>(M_PI));

#ifdef MANGOS
        E->Push(E->L, obj->IsInFront(target, arc));
#else
        E->Push(E->L, obj->isInFront(target, arc));
#endif
        return 1;
    }

    /**
     * Returns true if the target is in the given arc behind the [WorldObject]
     *
     * @param [WorldObject] target
     * @param float arc = pi
     * @return bool isInBack
     */
    int IsInBack(Eluna* E, WorldObject* obj)
    {
        WorldObject* target = Eluna::CHECKOBJ<WorldObject>(E->L, 2);
        float arc = Eluna::CHECKVAL<float>(E->L, 3, static_cast<float>(M_PI));

#ifdef MANGOS
        E->Push(E->L, obj->IsInBack(target, arc));
#else
        E->Push(E->L, obj->isInBack(target, arc));
#endif
        return 1;
    }

    /**
     * The [WorldObject] plays music to a [Player]
     *
     * If no [Player] provided it will play the music to everyone near.
     * This method does not interrupt previously played music.
     *
     * See also [WorldObject:PlayDistanceSound], [WorldObject:PlayDirectSound]
     *
     * @param uint32 music : entry of a music
     * @param [Player] player = nil : [Player] to play the music to
     */
    int PlayMusic(Eluna* E, WorldObject* obj)
    {
        uint32 musicid = Eluna::CHECKVAL<uint32>(E->L, 2);
        Player* player = Eluna::CHECKOBJ<Player>(E->L, 3, false);

        WorldPacket data(SMSG_PLAY_MUSIC, 4);
        data << uint32(musicid);
#ifdef CMANGOS
        if (player)
            player->SendDirectMessage(data);
        else
            obj->SendMessageToSet(data, true);
#else
        if (player)
            player->SendDirectMessage(&data);
        else
            obj->SendMessageToSet(&data, true);
#endif
        return 0;
    }

    /**
     * The [WorldObject] plays a sound to a [Player]
     *
     * If no [Player] provided it will play the sound to everyone near.
     * This method will play sound and does not interrupt prvious sound.
     *
     * See also [WorldObject:PlayDistanceSound], [WorldObject:PlayMusic]
     *
     * @param uint32 sound : entry of a sound
     * @param [Player] player = nil : [Player] to play the sound to
     */
    int PlayDirectSound(Eluna* E, WorldObject* obj)
    {
        uint32 soundId = Eluna::CHECKVAL<uint32>(E->L, 2);
        Player* player = Eluna::CHECKOBJ<Player>(E->L, 3, false);
        if (!sSoundEntriesStore.LookupEntry(soundId))
            return 0;

        if (player)
#ifndef CMANGOS
            obj->PlayDirectSound(soundId, player);
#else
            obj->PlayDirectSound(soundId, PlayPacketParameters(PLAY_TARGET, (Player const*)player));
#endif
        else
            obj->PlayDirectSound(soundId);
        return 0;
    }

    /**
     * The [WorldObject] plays a sound to a [Player]
     *
     * If no [Player] it will play the sound to everyone near.
     * Sound will fade the further you are from the [WorldObject].
     * This method interrupts previously playing sound.
     *
     * See also [WorldObject:PlayDirectSound], [WorldObject:PlayMusic]
     *
     * @param uint32 sound : entry of a sound
     * @param [Player] player = nil : [Player] to play the sound to
     */
    int PlayDistanceSound(Eluna* E, WorldObject* obj)
    {
        uint32 soundId = Eluna::CHECKVAL<uint32>(E->L, 2);
        Player* player = Eluna::CHECKOBJ<Player>(E->L, 3, false);
        if (!sSoundEntriesStore.LookupEntry(soundId))
            return 0;

        if (player)
#ifndef CMANGOS
            obj->PlayDistanceSound(soundId, player);
#else
            obj->PlayDistanceSound(soundId, PlayPacketParameters(PLAY_TARGET, (Player const*)player));
#endif
        else
            obj->PlayDistanceSound(soundId);
        return 0;
    }
};
#endif
