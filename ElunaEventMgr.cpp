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

LuaEvent::LuaEvent(ElunaEventProcessor* _events, int _funcRef, uint32 _delay, uint32 _calls) :
to_Abort(false), events(_events), funcRef(_funcRef), delay(_delay), calls(_calls)
{
}

LuaEvent::~LuaEvent()
{
    luaL_unref((*events->E)->L, LUA_REGISTRYINDEX, funcRef); // Free lua function ref
}

void LuaEvent::Execute()
{
    LOCK_ELUNA;
    // In multithread get map from object and the map's lua state
    lua_rawgeti((*events->E)->L, LUA_REGISTRYINDEX, funcRef);
    Eluna::Push((*events->E)->L, funcRef);
    Eluna::Push((*events->E)->L, delay);
    Eluna::Push((*events->E)->L, calls);
    if (calls) // Must be before calling
        --calls;
    Eluna::Push((*events->E)->L, events->obj);
    (*events->E)->ExecuteCall(4, 0);

    ASSERT(!(*events->E)->event_level);
    (*events->E)->InvalidateObjects();
}

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

    if (obj && Eluna::initialized)
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
        LuaEvent* event = it->second;
        eventList.erase(it);
        eventMap.erase(event->funcRef);

        if (event->to_Abort)
        {
            delete event;
            continue;
        }

        bool remove = event->calls == 1;
        if (!remove)
            AddEvent(event); // Reschedule before calling incase RemoveEvents used

        event->Execute();

        if (remove)
            delete event;
    }
}

void ElunaEventProcessor::RemoveEvents()
{
    for (EventList::iterator it = eventList.begin(); it != eventList.end(); ++it)
        it->second->to_Abort = true;
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
        delete it->second;

    eventList.clear();
    eventMap.clear();
}

void ElunaEventProcessor::RemoveEvent(int eventId)
{
    if (eventMap.find(eventId) != eventMap.end())
        eventMap[eventId]->to_Abort = true;
}

void ElunaEventProcessor::AddEvent(LuaEvent* event)
{
    eventList.insert(std::pair<uint64, LuaEvent*>(m_time + event->delay, event));
    eventMap[event->funcRef] = event;
}

void ElunaEventProcessor::AddEvent(int funcRef, uint32 delay, uint32 repeats)
{
    AddEvent(new LuaEvent(this, funcRef, delay, repeats));
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
