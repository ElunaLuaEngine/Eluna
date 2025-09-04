/*
* Copyright (C) 2010 - 2025 Eluna Lua Engine <https://elunaluaengine.github.io/>
* This program is free software licensed under GPL version 3
* Please see the included DOCS/LICENSE.md for more information
*/

#ifndef _ELUNAMGR_H
#define _ELUNAMGR_H

#include <unordered_map>
#include <memory>

class Eluna;

struct ElunaInfo
{
    uint32 mapId;
    uint32 instanceId;
    uint64 key;

    ElunaInfo(uint32 map, uint32 instance)
        : mapId(map), instanceId(instance)
    {
        key = (static_cast<uint64>(mapId) << 32) | instanceId;
    }

    ~ElunaInfo();

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

    Eluna* Get(uint64 key) const;
    Eluna* Get(ElunaInfo const& info) const;

    void Destroy(uint64 key);
    void Destroy(ElunaInfo const& info);

private:
    std::unordered_map<uint64, std::unique_ptr<Eluna>> _elunaMap;
};

#define sElunaMgr ElunaMgr::instance()

#endif //_ELUNAMGR_H
