/*
* Copyright (C) 2010 - 2015 Eluna Lua Engine <http://emudevs.com/>
* This program is free software licensed under GPL version 3
* Please see the included DOCS/LICENSE.md for more information
*/

#ifndef _ELUNA_UTIL_H
#define _ELUNA_UTIL_H

#include "Common.h"
#include "SharedDefines.h"
#include "ObjectGuid.h"
#ifdef TRINITY
#include "QueryResult.h"
#ifdef CATA
#include "Object.h"
#endif
#else
#include "Database/QueryResult.h"
#endif

// Some dummy includes containing BOOST_VERSION:
// ObjectAccessor.h Config.h Log.h
#ifdef BOOST_VERSION
#define USING_BOOST
#endif

#ifdef USING_BOOST
#include <boost/thread/locks.hpp>
#include <boost/thread/shared_mutex.hpp>
#endif

#ifdef TRINITY
typedef QueryResult ElunaQuery;
#define ELUNA_LOG_INFO(...)     TC_LOG_INFO("eluna", __VA_ARGS__);
#define ELUNA_LOG_ERROR(...)    TC_LOG_ERROR("eluna", __VA_ARGS__);
#define ELUNA_LOG_DEBUG(...)    TC_LOG_DEBUG("eluna", __VA_ARGS__);
#define GET_GUID                GetGUID
#else
typedef QueryNamedResult ElunaQuery;
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
#include <unordered_map>
#define UNORDERED_MAP std::unordered_map
#endif
#ifndef UNORDERED_SET
#include <unordered_set>
#define UNORDERED_SET std::unordered_set
#endif

#ifndef MAKE_NEW_GUID
#define MAKE_NEW_GUID(l, e, h)  ObjectGuid(h, e, l)
#endif
#ifndef GUID_ENPART
#define GUID_ENPART(guid)       ObjectGuid(guid).GetEntry()
#endif
#ifndef GUID_LOPART
#define GUID_LOPART(guid)       ObjectGuid(guid).GetCounter()
#endif
#ifndef GUID_HIPART
#define GUID_HIPART(guid)       ObjectGuid(guid).GetHigh()
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

        WorldObject const* i_obj;
        uint32 i_hostile;
        uint32 i_entry;
        float i_range;
        uint16 i_typeMask;
        bool i_nearest;
    };

    /*
     * Usage:
     * Inherit this class, then when needing lock, use
     * ReadGuard guard(GetLock());
     * or
     * WriteGuard guard(GetLock());
     *
     * The lock is automatically released at end of scope
     */
    class RWLockable
    {
    public:

#ifdef USING_BOOST
        typedef boost::shared_mutex LockType;
        typedef boost::shared_lock<boost::shared_mutex> ReadGuard;
        typedef boost::unique_lock<boost::shared_mutex> WriteGuard;
#else
        typedef ACE_RW_Thread_Mutex LockType;
        typedef ACE_Read_Guard<LockType> ReadGuard;
        typedef ACE_Write_Guard<LockType> WriteGuard;
#endif

        LockType& GetLock() { return _lock; }

    private:
        LockType _lock;
    };

    /*
     * Encodes `data` in Base-64 and store the result in `buffer`.
     *
     * If the resulting string's length would be > `max_length`,
     *   encoding is aborted and `buffer` is left unmodified.
     */
    void EncodeData(const unsigned char* data, size_t input_length, char* buffer, size_t max_length);

    /*
     * Decodes `data` from Base-64 and returns a pointer to the result, or `NULL` on error.
     *
     * The returned result buffer must be `free`d by the caller.
     */
    unsigned char* DecodeData(const char* data, size_t *output_length);
};

#endif
