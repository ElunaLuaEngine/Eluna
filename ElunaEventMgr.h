/*
* Copyright (C) 2010 - 2024 Eluna Lua Engine <https://elunaluaengine.github.io/>
* This program is free software licensed under GPL version 3
* Please see the included DOCS/LICENSE.md for more information
*/

#ifndef _ELUNA_EVENT_MGR_H
#define _ELUNA_EVENT_MGR_H

#include "ElunaUtility.h"
#include "Common.h"
#if defined ELUNA_TRINITY
#include "Random.h"
#elif defined ELUNA_CMANGOS
#include "Util/Util.h"
#else
#include "Util.h"
#endif
#include <map>

#if defined ELUNA_TRINITY || defined ELUNA_AZEROTHCORE
#include "Define.h"
#else
#include "Platform/Define.h"
#endif

class Eluna;
class EventMgr;
class ElunaEventProcessor;
class WorldObject;

enum LuaEventState : uint8
{
    LUAEVENT_STATE_RUN,    // On next call run the function normally
    LUAEVENT_STATE_ABORT,  // On next call unregisters reffed function and erases the data
    LUAEVENT_STATE_ERASE,  // On next call just erases the data
};

enum DeferredOpType : uint8
{
    AddEvent,
    SetState,
    SetStates,
    ClearAll
};

enum GlobalEventSpace : uint8
{
    GLOBAL_EVENTS
};

struct LuaEvent
{
    LuaEvent(int _funcRef, uint32 _min, uint32 _max, uint32 _repeats) : min(_min), max(_max), delay(0), repeats(_repeats), funcRef(_funcRef), state(LUAEVENT_STATE_RUN) { }

    void SetState(LuaEventState _state)
    {
        if (state != LUAEVENT_STATE_ERASE)
            state = _state;
    }

    void GenerateDelay()
    {
        delay = urand(min, max);
    }

    uint32 min;   // Minimum delay between event calls
    uint32 max;   // Maximum delay between event calls
    uint32 delay; // The currently used waiting time
    uint32 repeats; // Amount of repeats to make, 0 for infinite
    int funcRef;    // Lua function reference ID, also used as event ID
    LuaEventState state;    // State for next call
};

class ElunaEventProcessor
{
    friend class EventMgr;

public:
    typedef std::multimap<uint64, LuaEvent*> EventList;
    typedef std::unordered_map<int, LuaEvent*> EventMap;

    ElunaEventProcessor(EventMgr* mgr, WorldObject* obj) : m_time(0), obj(obj), mgr(mgr) { }
    ~ElunaEventProcessor();

    void Update(uint32 diff);
    // removes all timed events on next tick or at tick end
    void SetStates(LuaEventState state);
    // set the event to be removed when executing
    void SetState(int eventId, LuaEventState state);
    void AddEvent(int funcRef, uint32 min, uint32 max, uint32 repeats);

private:
    struct DeferredOp
    {
        int eventId = 0;
        DeferredOpType type;
        LuaEventState state = LUAEVENT_STATE_RUN;
        LuaEvent* event = nullptr;
    };

    void ClearAllEvents();
    void AddEvent(LuaEvent* luaEvent);
    void RemoveEvent(LuaEvent* luaEvent);

    void QueueDeferredOp(DeferredOpType type, LuaEvent* event = nullptr, int eventId = 0, LuaEventState state = LUAEVENT_STATE_RUN);
    void ProcessDeferredOps();
    bool isUpdating = false;
    std::vector<DeferredOp> deferredOps;

    EventList eventList;
    EventMap eventMap;
    uint64 m_time;

    bool pendingDeletion = false;

    WorldObject* obj;
    EventMgr* mgr;
};

class ElunaProcessorInfo
{
public:
    ElunaProcessorInfo(EventMgr* mgr, uint64 processorId) : mgr(mgr), processorId(processorId) { }
    ~ElunaProcessorInfo();

    uint64 GetProcessorId() const { return processorId; }

private:
    EventMgr* mgr;
    uint64 processorId;
};

class EventMgr
{
public:
    EventMgr(Eluna* _E);
    ~EventMgr();

    void UpdateProcessors(uint32 diff);
    void SetAllEventStates(LuaEventState state);
    void SetEventState(int eventId, LuaEventState state);

    // Global (per state) processors
    ElunaEventProcessor* GetGlobalProcessor(GlobalEventSpace space);

    // Per-object processors
    uint64 CreateObjectProcessor(WorldObject* obj);
    ElunaEventProcessor* GetObjectProcessor(uint64 processorId);
    void FlagObjectProcessorForDeletion(uint64 processorId);

private:
    typedef std::unordered_set<ElunaEventProcessor*> ProcessorSet;
    typedef std::unordered_map<uint64, std::unique_ptr<ElunaEventProcessor>> ObjectProcessorMap;
    typedef std::unordered_map<GlobalEventSpace, std::unique_ptr<ElunaEventProcessor>> GlobalProcessorsMap;

    ProcessorSet processors; // tracks ALL processors (object + global)
    GlobalProcessorsMap globalProcessors;
    ObjectProcessorMap objectProcessors;
    std::unordered_set<uint64> objectProcessorsPendingDelete;

    Eluna* E;

    void CleanupObjectProcessors();

    friend class ElunaEventProcessor;
    friend class ElunaProcessorInfo;
};

#endif
