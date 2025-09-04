/*
* Copyright (C) 2010 - 2025 Eluna Lua Engine <https://elunaluaengine.github.io/>
* This program is free software licensed under GPL version 3
* Please see the included DOCS/LICENSE.md for more information
*/

#ifndef _ELUNAMGR_H
#define _ELUNAMGR_H

#include "LuaEngine.h"

#include <unordered_map>
#include <memory>

struct ElunaInfo
{
    uint32_t mapId;
    uint32_t instanceId;
    uint64_t key;

    ElunaInfo(uint32_t map, uint32_t instance)
        : mapId(map), instanceId(instance)
    {
        key = (static_cast<uint64_t>(mapId) << 32) | instanceId;
    }

    // Getter to fetch Eluna object
    Eluna* GetEluna() const;
};

class ElunaMgr
{
private:
    ElunaMgr();
    ~ElunaMgr();
    ElunaMgr(ElunaMgr const&) = delete;
    ElunaMgr& operator=(ElunaMgr const&) = delete;

public:
    static ElunaMgr* instance();

    void Create(Map* map, ElunaInfo const& info);

    Eluna* Get(uint64_t key) const;
    Eluna* Get(ElunaInfo const& info) const;

    void Destroy(uint64_t key);
    void Destroy(ElunaInfo const& info);

private:
    std::unordered_map<uint64_t, std::unique_ptr<Eluna>> _elunaMap;
};

#define sElunaMgr ElunaMgr::instance()

#endif //_ELUNAMGR_H
