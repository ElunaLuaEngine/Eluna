/*
* Copyright (C) 2010 - 2025 Eluna Lua Engine <https://elunaluaengine.github.io/>
* This program is free software licensed under GPL version 3
* Please see the included DOCS/LICENSE.md for more information
*/

#ifndef _ELUNAMGR_H
#define _ELUNAMGR_H

#include <limits>
#include <memory>
#include <unordered_map>

class Eluna;

struct ElunaInfo
{
public:
    ElunaInfo(uint32 mapId, uint32 instanceId);
    ~ElunaInfo();

public:
    static constexpr uint32 MakeKey(uint32 mapId, uint32 instanceId);
    static constexpr uint32 MakeGlobalKey(uint32 instanceId);

    bool IsValid() const;
    bool IsGlobal() const;

    uint32 GetMapId() const;
    uint32 GetInstanceId() const;

    // Getter to fetch Eluna object
    Eluna* GetEluna() const;

public:
    static uint64 const INVALID_KEY_ID = std::numeric_limits<uint64>().max();
    static uint32 const GLOBAL_MAP_ID = std::numeric_limits<uint32>().max();

    uint64 key = INVALID_KEY_ID;
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
