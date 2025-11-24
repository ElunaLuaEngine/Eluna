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
    if (E && E->eventMgr)
        E->eventMgr->processors.insert(this);
}

ElunaEventProcessor::~ElunaEventProcessor()
{
    RemoveEvents_internal();

    if (E && E->eventMgr)
        E->eventMgr->processors.erase(this);
}

void ElunaEventProcessor::Update(uint32 diff)
{
    isUpdating = true;

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
                AddEvent(luaEvent); // may be deferred if we recurse into Update

            if (!obj || (obj && obj->IsInWorld()))
                E->OnTimedEvent(luaEvent->funcRef, delay, luaEvent->repeats ? luaEvent->repeats-- : luaEvent->repeats, obj);

            if (!remove)
                continue;
        }

        RemoveEvent(luaEvent);
    }

    isUpdating = false;
    ProcessDeferredOps();
}

void ElunaEventProcessor::SetStates(LuaEventState state)
{
    if (isUpdating)
    {
        QueueDeferredOp(DeferredOpType::SetStates, nullptr, 0, state);
        return;
    }

    for (EventList::iterator it = eventList.begin(); it != eventList.end(); ++it)
        it->second->SetState(state);

    if (state == LUAEVENT_STATE_ERASE)
        eventMap.clear();
}

void ElunaEventProcessor::RemoveEvents_internal()
{
    if (isUpdating)
    {
        QueueDeferredOp(DeferredOpType::ClearAll);
        return;
    }

    for (EventList::iterator it = eventList.begin(); it != eventList.end(); ++it)
        RemoveEvent(it->second);

    deferredOps.clear();
    eventList.clear();
    eventMap.clear();
}

void ElunaEventProcessor::SetState(int eventId, LuaEventState state)
{
    if (isUpdating)
    {
        QueueDeferredOp(DeferredOpType::SetState, nullptr, eventId, state);
        return;
    }

    auto itr = eventMap.find(eventId);
    if (itr != eventMap.end())
        itr->second->SetState(state);

    if (state == LUAEVENT_STATE_ERASE)
        eventMap.erase(eventId);
}

void ElunaEventProcessor::AddEvent(LuaEvent* luaEvent)
{
    if (isUpdating)
    {
        QueueDeferredOp(DeferredOpType::AddEvent, luaEvent);
        return;
    }

    luaEvent->GenerateDelay();
    eventList.insert(std::make_pair(m_time + luaEvent->delay, luaEvent));
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

void ElunaEventProcessor::QueueDeferredOp(DeferredOpType type, LuaEvent* event, int eventId, LuaEventState state)
{
    DeferredOp op;
    op.type = type;
    op.event = event;
    op.eventId = eventId;
    op.state = state;
    deferredOps.push_back(op);
}

void ElunaEventProcessor::ProcessDeferredOps()
{
    if (deferredOps.empty())
        return;

    std::vector<DeferredOp> ops;
    ops.swap(deferredOps);

    for (DeferredOp& op : ops)
    {
        switch (op.type)
        {
        case DeferredOpType::AddEvent:
            AddEvent(op.event);
            break;

        case DeferredOpType::SetState:
            SetState(op.eventId, op.state);
            break;

        case DeferredOpType::SetStates:
            SetStates(op.state);
            break;

        case DeferredOpType::ClearAll:
            RemoveEvents_internal();
            break;
        }
    }
}

EventMgr::EventMgr(Eluna* _E) : E(_E)
{
    auto gp = std::make_unique<ElunaEventProcessor>(E, nullptr);
    processors.insert(gp.get());
    globalProcessors.emplace(GLOBAL_EVENTS, std::move(gp));
}

EventMgr::~EventMgr()
{
    globalProcessors.clear();
    processors.clear();
}

void EventMgr::UpdateProcessors(uint32 diff)
{
    // iterate a copy because processors may be destroyed during update (creature removed by a script, etc)
    ProcessorSet copy = processors;

    for (auto* processor : copy)
    {
        if (processors.find(processor) != processors.end())
            processor->Update(diff);
    }
}

void EventMgr::SetAllEventStates(LuaEventState state)
{
    for (auto* processor : processors)
        processor->SetStates(state);
}

void EventMgr::SetEventState(int eventId, LuaEventState state)
{
    for (auto* processor : processors)
        processor->SetState(eventId, state);
}

ElunaEventProcessor* EventMgr::GetGlobalProcessor(GlobalEventSpace space)
{
    auto it = globalProcessors.find(space);
    return (it != globalProcessors.end()) ? it->second.get() : nullptr;
}
