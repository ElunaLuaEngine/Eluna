/*
* Copyright (C) 2010 - 2024 Eluna Lua Engine <https://elunaluaengine.github.io/>
* This program is free software licensed under GPL version 3
* Please see the included DOCS/LICENSE.md for more information
*/

#include "ElunaEventMgr.h"
#include "LuaEngine.h"
#if !defined ELUNA_CMANGOS
#include "Object.h"
#else
#include "Entities/Object.h"
#endif

extern "C"
{
#include "lua.h"
#include "lauxlib.h"
};

ElunaEventProcessor::ElunaEventProcessor(Eluna* _E, WorldObject* _obj) : m_time(0), obj(_obj), E(_E)
{
    if (obj)
        E->eventMgr->processors.insert(this);
}

ElunaEventProcessor::~ElunaEventProcessor()
{
    {
        RemoveEvents_internal();
    }

    if (obj)
        E->eventMgr->processors.erase(this);
}

void ElunaEventProcessor::Update(uint32 diff)
{
    m_time += diff;
    for (EventList::iterator it = eventList.begin(); it != eventList.end() && it->first <= m_time; it = eventList.begin())
    {
        LuaEvent* luaEvent = it->second;
        eventList.erase(it);

        if (luaEvent->state != LUAEVENT_STATE_ERASE)
            eventMap.erase(luaEvent->funcRef);

        if (luaEvent->state == LUAEVENT_STATE_RUN)
        {
            uint32 delay = luaEvent->delay;
            bool remove = luaEvent->repeats == 1;
            if (!remove)
                AddEvent(luaEvent); // Reschedule before calling incase RemoveEvents used

            // Call the timed event
            E->OnTimedEvent(luaEvent->funcRef, delay, luaEvent->repeats ? luaEvent->repeats-- : luaEvent->repeats, obj);

            if (!remove)
                continue;
        }

        // Event should be deleted (executed last time or set to be aborted)
        RemoveEvent(luaEvent);
    }
}

void ElunaEventProcessor::SetStates(LuaEventState state)
{
    for (EventList::iterator it = eventList.begin(); it != eventList.end(); ++it)
        it->second->SetState(state);
    if (state == LUAEVENT_STATE_ERASE)
        eventMap.clear();
}

void ElunaEventProcessor::RemoveEvents_internal()
{
    for (EventList::iterator it = eventList.begin(); it != eventList.end(); ++it)
        RemoveEvent(it->second);

    eventList.clear();
    eventMap.clear();
}

void ElunaEventProcessor::SetState(int eventId, LuaEventState state)
{
    if (eventMap.find(eventId) != eventMap.end())
        eventMap[eventId]->SetState(state);
    if (state == LUAEVENT_STATE_ERASE)
        eventMap.erase(eventId);
}

void ElunaEventProcessor::AddEvent(LuaEvent* luaEvent)
{
    luaEvent->GenerateDelay();
    eventList.insert(std::pair<uint64, LuaEvent*>(m_time + luaEvent->delay, luaEvent));
    eventMap[luaEvent->funcRef] = luaEvent;
}

void ElunaEventProcessor::AddEvent(int funcRef, uint32 min, uint32 max, uint32 repeats)
{
    AddEvent(new LuaEvent(funcRef, min, max, repeats));
}

void ElunaEventProcessor::RemoveEvent(LuaEvent* luaEvent)
{
    // Unreference if should and if Eluna was not yet uninitialized and if the lua state still exists
    if (luaEvent->state != LUAEVENT_STATE_ERASE && E->HasLuaState())
    {
        // Free lua function ref
        luaL_unref(E->L, LUA_REGISTRYINDEX, luaEvent->funcRef);
    }
    delete luaEvent;
}

EventMgr::EventMgr(Eluna* _E) : globalProcessor(new ElunaEventProcessor(_E, NULL)), E(_E)
{
}

EventMgr::~EventMgr()
{
    {
        if (!processors.empty())
            for (ProcessorSet::const_iterator it = processors.begin(); it != processors.end(); ++it) // loop processors
                (*it)->RemoveEvents_internal();
        globalProcessor->RemoveEvents_internal();
    }
    delete globalProcessor;
    globalProcessor = NULL;
}

void EventMgr::SetStates(LuaEventState state)
{
    if (!processors.empty())
        for (ProcessorSet::const_iterator it = processors.begin(); it != processors.end(); ++it) // loop processors
            (*it)->SetStates(state);
    globalProcessor->SetStates(state);
}

void EventMgr::SetState(int eventId, LuaEventState state)
{
    if (!processors.empty())
        for (ProcessorSet::const_iterator it = processors.begin(); it != processors.end(); ++it) // loop processors
            (*it)->SetState(eventId, state);
    globalProcessor->SetState(eventId, state);
}
