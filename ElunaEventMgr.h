/*
* Copyright (C) 2010 - 2015 Eluna Lua Engine <http://emudevs.com/>
* This program is free software licensed under GPL version 3
* Please see the included DOCS/LICENSE.md for more information
*/

#ifndef _ELUNA_EVENT_MGR_H
#define _ELUNA_EVENT_MGR_H

#include "ElunaUtility.h"
#include "Common.h"
#include <map>

#ifdef TRINITY
#include "Define.h"
#else
#include "Platform/Define.h"
#endif

class Eluna;
class EventMgr;
class ElunaEventProcessor;
class WorldObject;

class LuaEvent
{
    friend class EventMgr;
    friend class ElunaEventProcessor;

public:
    // Should never execute on dead events
    void Execute();
    bool to_Abort;

private:
    LuaEvent(ElunaEventProcessor* _events, int _funcRef, uint32 _delay, uint32 _calls);
    ~LuaEvent();

    ElunaEventProcessor* events; // Pointer to events (holds the timed event)
    int funcRef;    // Lua function reference ID, also used as event ID
    uint32 delay;   // Delay between event calls
    uint32 calls;   // Amount of calls to make, 0 for infinite
};

class ElunaEventProcessor
{
    friend class LuaEvent;
    friend class EventMgr;

public:
    typedef std::multimap<uint64, LuaEvent*> EventList;
    typedef UNORDERED_MAP<int, LuaEvent*> EventMap;

    ElunaEventProcessor(Eluna** _E, WorldObject* _obj);
    ~ElunaEventProcessor();

    void Update(uint32 diff);
    // removes all timed events on next tick or at tick end
    void RemoveEvents();
    // set the event to be removed when executing
    void RemoveEvent(int eventId);
    void AddEvent(int funcRef, uint32 delay, uint32 repeats);
    EventMap eventMap;

private:
    void RemoveEvents_internal();
    void AddEvent(LuaEvent* Event);
    EventList eventList;
    uint64 m_time;
    WorldObject* obj;
    Eluna** E;
};

class EventMgr : public ElunaUtil::RWLockable
{
public:
    typedef UNORDERED_SET<ElunaEventProcessor*> ProcessorSet;
    ProcessorSet processors;
    ElunaEventProcessor* globalProcessor;
    Eluna** E;

    EventMgr(Eluna** _E);
    ~EventMgr();

    // Remove all timed events
    // Execute only in safe env
    void RemoveEvents();

    // Removes the eventId from all events
    // Execute only in safe env
    void RemoveEvent(int eventId);
};

#endif
