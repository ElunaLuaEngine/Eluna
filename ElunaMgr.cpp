/*
* Copyright (C) 2010 - 2025 Eluna Lua Engine <https://elunaluaengine.github.io/>
* This program is free software licensed under GPL version 3
* Please see the included DOCS/LICENSE.md for more information
*/

#include "ElunaMgr.h"
#include "LuaEngine.h"

ElunaMgr::ElunaMgr()
{
}

ElunaMgr* ElunaMgr::instance()
{
    static ElunaMgr instance;
    return &instance;
}

ElunaMgr::~ElunaMgr()
{
}

void ElunaMgr::Create(Map* map, ElunaInfo const& info)
{
    // If already exists, do nothing
    bool keyExists = info.IsValid() && (_elunaMap.find(info.key) != _elunaMap.end());
    if (keyExists)
        return;

    _elunaMap.emplace(info.key, std::make_unique<Eluna>(map));
}

Eluna* ElunaMgr::Get(ElunaInfoKey key) const
{
    auto it = _elunaMap.find(key);
    if (it != _elunaMap.end())
        return it->second.get();

    return nullptr;
}

Eluna* ElunaMgr::Get(ElunaInfo const& info) const
{
    return Get(info.key);
}

void ElunaMgr::Destroy(ElunaInfoKey key)
{
    _elunaMap.erase(key);
}

void ElunaMgr::Destroy(ElunaInfo const& info)
{
    Destroy(info.key);
}

ElunaInfoKey::ElunaInfoKey(uint32 mapId, uint32 instanceId)
{
    value = MakeKey(mapId, instanceId);
}

bool ElunaInfoKey::operator==(const ElunaInfoKey& other) const
{
    return value == other.value;
}

constexpr ElunaInfoKey ElunaInfoKey::MakeKey(uint32 mapId, uint32 instanceId)
{
    return ElunaInfoKey(instanceId | (static_cast<uint64>(mapId) << 32));
}

constexpr ElunaInfoKey ElunaInfoKey::MakeGlobalKey(uint32 instanceId)
{
    return MakeKey(GLOBAL_MAP_ID, instanceId);
}

bool ElunaInfoKey::IsValid() const
{
    return value != INVALID_KEY_VALUE;
}

bool ElunaInfoKey::IsGlobal() const
{
    return IsValid() && GetMapId() == GLOBAL_MAP_ID;
}

uint32 ElunaInfoKey::GetMapId() const
{
    return value >> 32;
}

uint32 ElunaInfoKey::GetInstanceId() const
{
    return value & 0xFFFFFFFF;
}

ElunaInfo::ElunaInfo(uint32 mapId, uint32 instanceId)
{
    key = ElunaInfoKey::MakeKey(mapId, instanceId);
}

ElunaInfo::~ElunaInfo()
{
    if (IsValid() && sElunaMgr)
        sElunaMgr->Destroy(key);
}

bool ElunaInfo::IsValid() const
{
    return key.IsValid();
}

bool ElunaInfo::IsGlobal() const
{
    return key.IsGlobal();
}

uint32 ElunaInfo::GetMapId() const
{
    return key.GetMapId();
}

uint32 ElunaInfo::GetInstanceId() const
{
    return key.GetInstanceId();
}

Eluna* ElunaInfo::GetEluna() const
{
    if (IsValid() && sElunaMgr)
        return sElunaMgr->Get(key);

    return nullptr;
}
