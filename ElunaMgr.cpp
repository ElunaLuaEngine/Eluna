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
    if (_elunaMap.find(info.key) != _elunaMap.end())
        return;

    _elunaMap.emplace(info.key, std::make_unique<Eluna>(map));
}

Eluna* ElunaMgr::Get(uint64 key) const
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

void ElunaMgr::Destroy(uint64 key)
{
    _elunaMap.erase(key);
}

void ElunaMgr::Destroy(ElunaInfo const& info)
{
    Destroy(info.key);
}

Eluna* ElunaInfo::GetEluna() const
{
    if (sElunaMgr)
        return sElunaMgr->Get(key);

    return nullptr;
}

ElunaInfo::~ElunaInfo()
{
    if (sElunaMgr)
        sElunaMgr->Destroy(key);
}
