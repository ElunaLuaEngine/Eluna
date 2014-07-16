/*
* Copyright (C) 2010 - 2014 Eluna Lua Engine <http://emudevs.com/>
* This program is free software licensed under GPL version 3
* Please see the included DOCS/LICENSE.md for more information
*/

#include "ElunaEventMgr.h"
#include "LuaEngine.h"

extern "C"
{
#include "lua.h"
#include "lauxlib.h"
};

LuaEvent::LuaEvent(Eluna& _E, EventProcessor* _events, int _funcRef, uint32 _delay, uint32 _calls, Object* _obj):
E(_E), events(_events), funcRef(_funcRef), delay(_delay), calls(_calls), obj(_obj)
{
    if (_events)
        E.m_EventMgr->LuaEvents[_events].insert(this); // Able to access the event if we have the processor
}

LuaEvent::~LuaEvent()
{
    if (events)
    {
        // Attempt to remove the pointer from LuaEvents
        EventMgr::EventMap::const_iterator it = E.m_EventMgr->LuaEvents.find(events); // Get event set
        if (it != E.m_EventMgr->LuaEvents.end())
            E.m_EventMgr->LuaEvents[events].erase(this);// Remove pointer
    }
    luaL_unref(E.L, LUA_REGISTRYINDEX, funcRef); // Free lua function ref
}

bool LuaEvent::Execute(uint64 /*time*/, uint32 /*diff*/)
{
    bool remove = (calls == 1);
    if (!remove)
        events->AddEvent(this, events->CalculateTime(delay)); // Reschedule before calling incase RemoveEvents used
    lua_rawgeti(E.L, LUA_REGISTRYINDEX, funcRef);
    Eluna::Push(E.L, funcRef);
    Eluna::Push(E.L, delay);
    Eluna::Push(E.L, calls);
    if (!remove && calls)
        --calls;
    Eluna::Push(E.L, obj);
    Eluna::ExecuteCall(E.L, 4, 0);
    return remove; // Destory (true) event if not run
}

EventMgr::EventMgr(Eluna& _E): E(_E)
{
}

EventMgr::~EventMgr()
{
    RemoveEvents();
}

void EventMgr::Update(uint32 diff)
{
    GlobalEvents.Update(diff);
}

/*
void EventMgr::KillAllEvents(EventProcessor* events)
{
    if (!events)
        return;
    if (LuaEvents.empty())
        return;
    EventMap::const_iterator it = LuaEvents.find(events); // Get event set
    if (it == LuaEvents.end())
        return;
    if (it->second.empty())
        return;
    for (EventSet::const_iterator itr = it->second.begin(); itr != it->second.end();) // Loop events
        (*(itr++))->to_Abort = true; // Abort event
}
*/

void EventMgr::RemoveEvents()
{
    if (!LuaEvents.empty())
        for (EventMap::const_iterator it = LuaEvents.begin(); it != LuaEvents.end();) // loop processors
            (it++)->first->KillAllEvents(false); // KillAllEvents((it++)->first);
    LuaEvents.clear(); // remove pointers
    // This is handled automatically on delete
    // for (ProcessorMap::iterator it = Processors.begin(); it != Processors.end();)
    //    (it++)->second.KillAllEvents(true);
    // Processors.clear(); // remove guid saved processors
    GlobalEvents.KillAllEvents(true);
}

void EventMgr::RemoveEvents(EventProcessor* events)
{
    if (!events)
        return;
    // KillAllEvents(events);
    events->KillAllEvents(false);
    LuaEvents.erase(events); // remove pointer set
}

int EventMgr::AddEvent(EventProcessor* events, int funcRef, uint32 delay, uint32 calls, Object* obj)
{
    if (!events || funcRef <= 0) // If funcRef <= 0, function reference failed
        return 0; // on fail always return 0. funcRef can be negative.
    events->AddEvent(new LuaEvent(E, events, funcRef, delay, calls, obj), events->CalculateTime(delay));
    return funcRef; // return the event ID
}

LuaEvent* EventMgr::GetEvent(EventProcessor* events, int eventId)
{
    if (!events || !eventId)
        return NULL;
    if (LuaEvents.empty())
        return NULL;
    EventMap::const_iterator it = LuaEvents.find(events); // Get event set
    if (it == LuaEvents.end())
        return NULL;
    if (it->second.empty())
        return NULL;
    for (EventSet::const_iterator itr = it->second.begin(); itr != it->second.end(); ++itr) // Loop events
        if ((*itr) && (*itr)->funcRef == eventId) // Check if the event has our ID
            return *itr; // Return the event if found
    return NULL;
}

bool EventMgr::RemoveEvent(EventProcessor* events, int eventId)
{
    // eventId = funcRef
    if (!events || !eventId)
        return false;
    LuaEvent* luaEvent = GetEvent(events, eventId);
    if (!luaEvent)
        return false;
    luaEvent->to_Abort = true; // Set to remove on next call
    LuaEvents[events].erase(luaEvent); // Remove pointer
    return true;
}

void EventMgr::RemoveEvent(int eventId)
{
    if (!eventId)
        return;
    if (LuaEvents.empty())
        return;
    for (EventMap::const_iterator it = LuaEvents.begin(); it != LuaEvents.end();) // loop processors
        if (RemoveEvent((it++)->first, eventId))
            break; // succesfully remove the event, stop loop.
}
