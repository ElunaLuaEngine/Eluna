/*
* Copyright (C) 2010 - 2015 Eluna Lua Engine <http://emudevs.com/>
* This program is free software licensed under GPL version 3
* Please see the included DOCS/LICENSE.md for more information
*/

#include "ElunaEventMgr.h"
#include "LuaEngine.h"
#include "Object.h"

extern "C"
{
#include "lua.h"
#include "lauxlib.h"
};

ElunaEventProcessor::ElunaEventProcessor(Eluna** _E, WorldObject* _obj) : m_time(0), obj(_obj), E(_E)
{
    if (obj)
    {
        EventMgr::WriteGuard guard((*E)->eventMgr->GetLock());
        (*E)->eventMgr->processors.insert(this);
    }
}

ElunaEventProcessor::~ElunaEventProcessor()
{
    RemoveEvents_internal();

    if (obj && Eluna::IsInitialized())
    {
        EventMgr::WriteGuard guard((*E)->eventMgr->GetLock());
        (*E)->eventMgr->processors.erase(this);
    }
}

void ElunaEventProcessor::Update(uint32 diff)
{
    m_time += diff;
    for (EventList::iterator it = eventList.begin(); it != eventList.end() && it->first <= m_time; it = eventList.begin())
    {
        LuaEvent* luaEvent = it->second;
        eventList.erase(it);
        eventMap.erase(luaEvent->funcRef);

        if (!luaEvent->abort)
        {
            bool remove = luaEvent->repeats == 1;
            if (!remove)
                AddEvent(luaEvent); // Reschedule before calling incase RemoveEvents used

            // Call the timed event
            (*E)->OnTimedEvent(luaEvent->funcRef, luaEvent->delay, luaEvent->repeats ? luaEvent->repeats-- : luaEvent->repeats, obj);

            if (!remove)
                continue;
        }

        // Event should be deleted (executed last time or set to be aborted)
        RemoveEvent(luaEvent);
    }
}

void ElunaEventProcessor::RemoveEvents()
{
    for (EventList::iterator it = eventList.begin(); it != eventList.end(); ++it)
        it->second->abort = true;
}

void ElunaEventProcessor::RemoveEvents_internal()
{
    //if (!final)
    //{
    //    for (EventList::iterator it = eventList.begin(); it != eventList.end(); ++it)
    //        it->second->to_Abort = true;
    //    return;
    //}

    for (EventList::iterator it = eventList.begin(); it != eventList.end(); ++it)
        RemoveEvent(it->second);

    eventList.clear();
    eventMap.clear();
}

void ElunaEventProcessor::RemoveEvent(int eventId)
{
    if (eventMap.find(eventId) != eventMap.end())
        eventMap[eventId]->abort = true;
}

void ElunaEventProcessor::AddEvent(LuaEvent* luaEvent)
{
    eventList.insert(std::pair<uint64, LuaEvent*>(m_time + luaEvent->delay, luaEvent));
    eventMap[luaEvent->funcRef] = luaEvent;
}

void ElunaEventProcessor::AddEvent(int funcRef, uint32 delay, uint32 repeats)
{
    AddEvent(new LuaEvent(funcRef, delay, repeats));
}

void ElunaEventProcessor::RemoveEvent(LuaEvent* luaEvent)
{
    // Free lua function ref
    luaL_unref((*E)->L, LUA_REGISTRYINDEX, luaEvent->funcRef);
    delete luaEvent;
}

EventMgr::EventMgr(Eluna** _E) : globalProcessor(new ElunaEventProcessor(_E, NULL)), E(_E)
{
}

EventMgr::~EventMgr()
{
    {
        ReadGuard guard(GetLock());
        if (!processors.empty())
            for (ProcessorSet::const_iterator it = processors.begin(); it != processors.end(); ++it) // loop processors
                (*it)->RemoveEvents_internal();
        globalProcessor->RemoveEvents_internal();
    }
    delete globalProcessor;
    globalProcessor = NULL;
}

void EventMgr::RemoveEvents()
{
    ReadGuard guard(GetLock());
    if (!processors.empty())
        for (ProcessorSet::const_iterator it = processors.begin(); it != processors.end(); ++it) // loop processors
            (*it)->RemoveEvents();
    globalProcessor->RemoveEvents();
}

void EventMgr::RemoveEvent(int eventId)
{
    ReadGuard guard(GetLock());
    if (!processors.empty())
        for (ProcessorSet::const_iterator it = processors.begin(); it != processors.end(); ++it) // loop processors
            (*it)->RemoveEvent(eventId);
    globalProcessor->RemoveEvent(eventId);
}
