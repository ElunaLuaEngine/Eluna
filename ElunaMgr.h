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

struct ElunaInfoKey
{
public:
    ElunaInfoKey() : value(INVALID_KEY_VALUE) {}
    ElunaInfoKey(uint64 key) : value(key) {}
    ElunaInfoKey(uint32 mapId, uint32 instanceId);
    ~ElunaInfoKey() {}

    bool operator==(const ElunaInfoKey& other) const;

public:
    static constexpr ElunaInfoKey MakeKey(uint32 mapId, uint32 instanceId);
    static constexpr ElunaInfoKey MakeGlobalKey(uint32 instanceId);

    bool IsValid() const;
    bool IsGlobal() const;

    uint32 GetMapId() const;
    uint32 GetInstanceId() const;
    
public:
    static uint64 const INVALID_KEY_VALUE = std::numeric_limits<uint64>().max();
    static uint32 const GLOBAL_MAP_ID = std::numeric_limits<uint32>().max();

    uint64 value;
};

// Specialize ElunaInfoKey for use in unordered_map
namespace std
{
    template <>
    struct hash<ElunaInfoKey>
    {
        size_t operator()(const ElunaInfoKey& key) const
        {
            return key.value;
        }
    };
}

struct ElunaInfo
{
public:
    ElunaInfo() : key() {}
    ElunaInfo(ElunaInfoKey key) : key(key) {}
    ElunaInfo(uint32 mapId, uint32 instanceId);
    ~ElunaInfo();

public:
    bool IsValid() const;
    bool IsGlobal() const;

    uint32 GetMapId() const;
    uint32 GetInstanceId() const;

    // Getter to fetch Eluna object
    Eluna* GetEluna() const;

public:
    ElunaInfoKey key;
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

    Eluna* Get(ElunaInfoKey key) const;
    Eluna* Get(ElunaInfo const& info) const;

    void Destroy(ElunaInfoKey key);
    void Destroy(ElunaInfo const& info);

private:
    std::unordered_map<ElunaInfoKey, std::unique_ptr<Eluna>> _elunaMap;
};

#define sElunaMgr ElunaMgr::instance()

#endif //_ELUNAMGR_H
