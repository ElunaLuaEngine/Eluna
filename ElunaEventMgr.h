/*
* Copyright (C) 2010 - 2014 Eluna Lua Engine <http://emudevs.com/>
* This program is free software licensed under GPL version 3
* Please see the included DOCS/LICENSE.md for more information
*/

#ifndef _ELUNA_EVENT_MGR_H
#define _ELUNA_EVENT_MGR_H

#include "Common.h"
#ifdef TRINITY
#include "EventProcessor.h"
#else
#include "Utilities/EventProcessor.h"
#endif

class Eluna;
class EventMgr;
class EventProcessor;
class Object;

class LuaEvent : public BasicEvent
{
    friend class EventMgr;

public:
    LuaEvent(Eluna& _E, EventProcessor* _events, int _funcRef, uint32 _delay, uint32 _calls, Object* _obj);
    ~LuaEvent();

    // Should never execute on dead events
    bool Execute(uint64 time, uint32 diff);

private:
    Eluna& E;
    EventProcessor* events; // Pointer to events (holds the timed event)
    int funcRef;    // Lua function reference ID, also used as event ID
    uint32 delay;   // Delay between event calls
    uint32 calls;   // Amount of calls to make, 0 for infinite
    Object* obj;    // Object to push
};

class EventMgr
{
public:
    typedef std::set<LuaEvent*> EventSet;
    typedef std::map<EventProcessor*, EventSet> EventMap;
    Eluna& E;

    EventMap LuaEvents; // LuaEvents[processor] = {LuaEvent, LuaEvent...}
    EventProcessor GlobalEvents;

    EventMgr(Eluna& _E);
    ~EventMgr();

    // Should be run on world tick
    void Update(uint32 diff);

    // Aborts all lua events
    // void KillAllEvents(EventProcessor* events);

    // Remove all timed events
    void RemoveEvents();

    // Remove timed events from processor
    void RemoveEvents(EventProcessor* events);

    // Adds a new event to the processor and returns the eventID or 0 (Never negative)
    int AddEvent(EventProcessor* events, int funcRef, uint32 delay, uint32 calls, Object* obj = NULL);

    // Finds the event that has the ID from events
    LuaEvent* GetEvent(EventProcessor* events, int eventId);

    // Remove the event with the eventId from processor
    // Returns true if event is removed
    // EventId is func ref
    bool RemoveEvent(EventProcessor* events, int eventId);

    // Removes the eventId from all events
    void RemoveEvent(int eventId);
};

#endif
