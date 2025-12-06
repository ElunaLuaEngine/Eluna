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

ElunaEventProcessor::~ElunaEventProcessor()
{
    ClearAllEvents();
}

void ElunaEventProcessor::Update(uint32 diff)
{
    isUpdating = true;

    m_time += diff;
    while (!eventList.empty() && eventList.begin()->first <= m_time)
    {
        auto it = eventList.begin();
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

            // Call the timed event
            if (!obj || (obj && obj->IsInWorld()))
                mgr->E->OnTimedEvent(luaEvent->funcRef, delay, luaEvent->repeats ? luaEvent->repeats-- : luaEvent->repeats, obj);

            if (!remove)
                continue;
        }

        // Event should be deleted (executed last time or set to be aborted)
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

    for (auto& [time, event] : eventList)
        event->SetState(state);

    if (state == LUAEVENT_STATE_ERASE)
        eventMap.clear();
}

void ElunaEventProcessor::ClearAllEvents()
{
    if (isUpdating)
    {
        QueueDeferredOp(DeferredOpType::ClearAll);
        return;
    }

    for (auto& [time, event] : eventList)
        RemoveEvent(event);

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
    eventList.emplace(m_time + luaEvent->delay, luaEvent);
    eventMap[luaEvent->funcRef] = luaEvent;
}

void ElunaEventProcessor::AddEvent(int funcRef, uint32 min, uint32 max, uint32 repeats)
{
    AddEvent(new LuaEvent(funcRef, min, max, repeats));
}

void ElunaEventProcessor::RemoveEvent(LuaEvent* luaEvent)
{
    // Unreference if should and if Eluna was not yet uninitialized and if the lua state still exists
    if (luaEvent->state != LUAEVENT_STATE_ERASE && mgr->E->HasLuaState())
    {
        // Free lua function ref
        luaL_unref(mgr->E->L, LUA_REGISTRYINDEX, luaEvent->funcRef);
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

    using Handler = void(*)(ElunaEventProcessor*, DeferredOp&);
    static constexpr Handler handlers[] =
    {
        [](ElunaEventProcessor* self, DeferredOp& op)     { self->AddEvent(op.event); },
        [](ElunaEventProcessor* self, DeferredOp& op)     { self->SetState(op.eventId, op.state); },
        [](ElunaEventProcessor* self, DeferredOp& op)     { self->SetStates(op.state); },
        [](ElunaEventProcessor* self, DeferredOp& /*op*/) { self->ClearAllEvents(); }
    };

    for (DeferredOp& op : ops)
    {
        handlers[op.type](this, op);
    }
}

ElunaProcessorInfo::~ElunaProcessorInfo()
{
    if (mgr)
        mgr->FlagObjectProcessorForDeletion(processorId);
}

EventMgr::EventMgr(Eluna* _E) : E(_E)
{
    auto gp = std::make_unique<ElunaEventProcessor>(this, nullptr);
    processors.insert(gp.get());
    globalProcessors.emplace(GLOBAL_EVENTS, std::move(gp));
}

EventMgr::~EventMgr()
{
    globalProcessors.clear();
    objectProcessors.clear();
    processors.clear();
    objectProcessorsPendingDelete.clear();
}

void EventMgr::UpdateProcessors(uint32 diff)
{
    // iterate a copy because processors may be destroyed during update (creature removed by a script, etc)
    ProcessorSet copy = processors;

    for (auto* processor : copy)
    {
        if (processors.find(processor) != processors.end())
            if (!processor->pendingDeletion)
                processor->Update(diff);
    }

    CleanupObjectProcessors();
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

uint64 EventMgr::CreateObjectProcessor(WorldObject* obj)
{
#if !ELUNA_CMANGOS && !ELUNA_VMANGOS
    uint64 id = obj->GetGUID().GetRawValue();
#else
    uint64 id = obj->GetObjectGuid().GetRawValue();
#endif
    auto proc = std::make_unique<ElunaEventProcessor>(this, obj);
    ElunaEventProcessor* raw = proc.get();

    processors.insert(raw);
    objectProcessors.emplace(id, std::move(proc));

    return id;
}

ElunaEventProcessor* EventMgr::GetObjectProcessor(uint64 processorId)
{
    auto it = objectProcessors.find(processorId);
    return (it != objectProcessors.end()) ? it->second.get() : nullptr;
}

void EventMgr::FlagObjectProcessorForDeletion(uint64 processorId)
{
    auto it = objectProcessors.find(processorId);
    if (it == objectProcessors.end())
        return;

    ElunaEventProcessor* p = it->second.get();
    if (!p->pendingDeletion)
    {
        p->pendingDeletion = true;
        p->obj = nullptr;
        objectProcessorsPendingDelete.insert(processorId);
    }
}

void EventMgr::CleanupObjectProcessors()
{
    for (uint64 processorId : objectProcessorsPendingDelete)
    {
        auto it = objectProcessors.find(processorId);
        if (it == objectProcessors.end())
            continue;

        ElunaEventProcessor* p = it->second.get();
        p->SetStates(LUAEVENT_STATE_ERASE);

        processors.erase(p);
        objectProcessors.erase(it);
    }

    objectProcessorsPendingDelete.clear();
}
