/*
* Copyright (C) 2010 - 2014 Eluna Lua Engine <http://emudevs.com/>
* This program is free software licensed under GPL version 3
* Please see the included DOCS/LICENSE.md for more information
*/

#ifndef _ELUNA_UTIL_H
#define _ELUNA_UTIL_H

#include "Common.h"
#include "SharedDefines.h"
#ifdef TRINITY
#ifdef CATA
#include "Object.h"
#endif
#else
#include "ObjectGuid.h"
#endif

#ifdef TRINITY
#ifndef CATA
typedef uint64 ObjectGuid;
#endif
#define ELUNA_LOG_INFO(...)     TC_LOG_INFO("eluna", __VA_ARGS__);
#define ELUNA_LOG_ERROR(...)    TC_LOG_ERROR("eluna", __VA_ARGS__);
#define ELUNA_LOG_DEBUG(...)    TC_LOG_DEBUG("eluna", __VA_ARGS__);
#define GET_GUID                GetGUID
#else
#define MAKE_NEW_GUID(l, e, h)  ObjectGuid(h, e, l)
#define GUID_ENPART(guid)       ObjectGuid(guid).GetEntry()
#define GUID_LOPART(guid)       ObjectGuid(guid).GetCounter()
#define GUID_HIPART(guid)       ObjectGuid(guid).GetHigh()
#define ASSERT                  MANGOS_ASSERT
#define ELUNA_LOG_INFO(...)     sLog.outString(__VA_ARGS__);
#define ELUNA_LOG_ERROR(...)    sLog.outErrorEluna(__VA_ARGS__);
#define ELUNA_LOG_DEBUG(...)    sLog.outDebug(__VA_ARGS__);
#define GET_GUID                GetObjectGuid
#define GetGameObjectTemplate   GetGameObjectInfo
#define GetItemTemplate         GetItemPrototype
#define GetTemplate             GetProto
#endif

#ifndef UNORDERED_MAP
#define UNORDERED_MAP std::unordered_map
#endif

class Unit;
class WorldObject;

namespace ElunaUtil
{
    uint32 GetCurrTime();

    uint32 GetTimeDiff(uint32 oldMSTime);

    class ObjectGUIDCheck
    {
    public:
        ObjectGUIDCheck(ObjectGuid guid);
        bool operator()(WorldObject* object);

        ObjectGuid _guid;
    };

    // Binary predicate to sort WorldObjects based on the distance to a reference WorldObject
    class ObjectDistanceOrderPred
    {
    public:
        ObjectDistanceOrderPred(WorldObject const* pRefObj, bool ascending = true);
        bool operator()(WorldObject const* pLeft, WorldObject const* pRight) const;

        WorldObject const* m_refObj;
        const bool m_ascending;
    };

    // Doesn't get self
    class WorldObjectInRangeCheck
    {
    public:
        WorldObjectInRangeCheck(bool nearest, WorldObject const* obj, float range,
            uint16 typeMask = 0, uint32 entry = 0, uint32 hostile = 0);
        WorldObject const& GetFocusObject() const;
        bool operator()(WorldObject* u);

        bool i_nearest;
        WorldObject const* i_obj;
        float i_range;
        uint16 i_typeMask;
        uint32 i_entry;
        uint32 i_hostile;

        WorldObjectInRangeCheck(WorldObjectInRangeCheck const&);
    };
};

#endif
