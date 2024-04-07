/*
* Copyright (C) 2010 - 2024 Eluna Lua Engine <https://elunaluaengine.github.io/>
* This program is free software licensed under GPL version 3
* Please see the included DOCS/LICENSE.md for more information
*/

#ifndef _ELUNA_UTIL_H
#define _ELUNA_UTIL_H

#include <unordered_map>
#include <unordered_set>
#include <mutex>
#include <memory>
#include "Common.h"
#ifndef CMANGOS
#include "SharedDefines.h"
#include "ObjectGuid.h"
#else
#include "Globals/SharedDefines.h"
#include "Entities/ObjectGuid.h"
#endif
#ifdef TRINITY
#include "QueryResult.h"
#include "Log.h"
#ifdef CATA
#include "Object.h"
#endif
#elif VMANGOS
#include "Database/QueryResult.h"
#include "Log.h"
#else
#include "Database/QueryResult.h"
#include "Log/Log.h"
#endif

#if !defined(MANGOS) && !defined(VMANGOS)
#define USING_BOOST
#endif

#if defined(TRINITY_PLATFORM) && defined(TRINITY_PLATFORM_WINDOWS)
#if TRINITY_PLATFORM == TRINITY_PLATFORM_WINDOWS
#define ELUNA_WINDOWS
#endif
#elif defined(AC_PLATFORM) && defined(AC_PLATFORM_WINDOWS)
#if AC_PLATFORM == AC_PLATFORM_WINDOWS
#define ELUNA_WINDOWS
#endif
#elif defined(PLATFORM) && defined(PLATFORM_WINDOWS)
#if PLATFORM == PLATFORM_WINDOWS
#define ELUNA_WINDOWS
#endif
#else
#error Eluna could not determine platform
#endif

#if defined(TRINITY) || defined(AZEROTHCORE)
typedef QueryResult ElunaQuery;
#define GET_GUID                GetGUID
#define HIGHGUID_PLAYER         HighGuid::Player
#define HIGHGUID_UNIT           HighGuid::Unit
#define HIGHGUID_ITEM           HighGuid::Item
#define HIGHGUID_GAMEOBJECT     HighGuid::GameObject
#define HIGHGUID_PET            HighGuid::Pet
#define HIGHGUID_TRANSPORT      HighGuid::Transport
#define HIGHGUID_VEHICLE        HighGuid::Vehicle
#define HIGHGUID_CONTAINER      HighGuid::Container
#define HIGHGUID_DYNAMICOBJECT  HighGuid::DynamicObject
#define HIGHGUID_CORPSE         HighGuid::Corpse
#define HIGHGUID_MO_TRANSPORT   HighGuid::Mo_Transport
#define HIGHGUID_INSTANCE       HighGuid::Instance
#define HIGHGUID_GROUP          HighGuid::Group
#endif

#ifdef TRINITY
#ifdef WOTLK
#include "fmt/printf.h"
#define ELUNA_LOG_TC_FMT(TC_LOG_MACRO, ...) \
    try { \
        std::string message = fmt::sprintf(__VA_ARGS__); \
        TC_LOG_MACRO("eluna", "{}", message); \
    } catch (const std::exception& e) { \
        TC_LOG_MACRO("eluna", "Failed to format log message: {}", e.what()); \
    }
#define ELUNA_LOG_INFO(...)     ELUNA_LOG_TC_FMT(TC_LOG_INFO, __VA_ARGS__);
#define ELUNA_LOG_ERROR(...)    ELUNA_LOG_TC_FMT(TC_LOG_ERROR, __VA_ARGS__);
#define ELUNA_LOG_DEBUG(...)    ELUNA_LOG_TC_FMT(TC_LOG_DEBUG, __VA_ARGS__);
#else
#define ELUNA_LOG_INFO(...)     TC_LOG_INFO("eluna", __VA_ARGS__);
#define ELUNA_LOG_ERROR(...)    TC_LOG_ERROR("eluna", __VA_ARGS__);
#define ELUNA_LOG_DEBUG(...)    TC_LOG_DEBUG("eluna", __VA_ARGS__);
#endif
#elif defined(AZEROTHCORE)
#define ELUNA_LOG_INFO(...)     LOG_INFO("eluna", __VA_ARGS__);
#define ELUNA_LOG_ERROR(...)    LOG_ERROR("eluna", __VA_ARGS__);
#define ELUNA_LOG_DEBUG(...)    LOG_DEBUG("eluna", __VA_ARGS__);
#elif VMANGOS
typedef std::shared_ptr<QueryNamedResult> ElunaQuery;
#define ASSERT                  MANGOS_ASSERT
#define ELUNA_LOG_INFO(...)     sLog.Out(LOG_ELUNA, LOG_LVL_BASIC,__VA_ARGS__);
#define ELUNA_LOG_ERROR(...)    sLog.Out(LOG_ELUNA, LOG_LVL_ERROR,__VA_ARGS__);
#define ELUNA_LOG_DEBUG(...)    sLog.Out(LOG_ELUNA, LOG_LVL_DEBUG,__VA_ARGS__);
#define GET_GUID                GetObjectGuid
#define GetGameObjectTemplate   GetGameObjectInfo
#define GetItemTemplate         GetItemPrototype
#define GetTemplate             GetProto
#else
typedef std::shared_ptr<QueryNamedResult> ElunaQuery;
#define ASSERT                  MANGOS_ASSERT
#define ELUNA_LOG_INFO(...)     sLog.outString(__VA_ARGS__);
#define ELUNA_LOG_ERROR(...)    sLog.outErrorEluna(__VA_ARGS__);
#define ELUNA_LOG_DEBUG(...)    sLog.outDebug(__VA_ARGS__);
#define GET_GUID                GetObjectGuid
#define GetGameObjectTemplate   GetGameObjectInfo
#define GetItemTemplate         GetItemPrototype
#define GetTemplate             GetProto
#endif

#if defined(TRINITY) || defined(AZEROTHCORE) || defined(MANGOS) || defined(CMANGOS) || defined(VMANGOS)
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
#endif

typedef std::vector<uint8> BytecodeBuffer;

class Unit;
class WorldObject;
struct FactionTemplateEntry;

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
            uint16 typeMask = 0, uint32 entry = 0, uint32 hostile = 0, uint32 dead = 0);
        WorldObject const& GetFocusObject() const;
        bool operator()(WorldObject* u);

        WorldObject const* const i_obj;
        Unit const* i_obj_unit;
        FactionTemplateEntry const* i_obj_fact;
        uint32 const i_hostile; // 0 both, 1 hostile, 2 friendly
        uint32 const i_entry;
        float i_range;
        uint16 const i_typeMask;
        uint32 const i_dead; // 0 both, 1 alive, 2 dead
        bool const i_nearest;
    };

    /*
     * Encodes `data` in Base-64 and store the result in `output`.
     */
    void EncodeData(const unsigned char* data, size_t input_length, std::string& output);

    /*
     * Decodes `data` from Base-64 and returns a pointer to the result, or `NULL` on error.
     *
     * The returned result buffer must be `delete[]`ed by the caller.
     */
    unsigned char* DecodeData(const char* data, size_t *output_length);
};

#endif
