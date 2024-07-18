/*
* Copyright (C) 2010 - 2022 Eluna Lua Engine <https://elunaluaengine.github.io/>
* Copyright (C) 2022 - 2022 Hour of Twilight <https://www.houroftwilight.net/>
* This program is free software licensed under GPL version 3
* Please see the included DOCS/LICENSE.md for more information
*/

#ifndef _ELUNALOADER_H
#define _ELUNALOADER_H

#include "ElunaUtility.h"

#ifdef TRINITY
#include <efsw/efsw.hpp>
#endif

extern "C"
{
#include "lua.h"
};

enum ElunaReloadActions
{
    RELOAD_CACHE_ONLY   = -3,
    RELOAD_ALL_STATES   = -2,
    RELOAD_GLOBAL_STATE = -1
};

enum ElunaScriptCacheState
{
    SCRIPT_CACHE_NONE = 0,
    SCRIPT_CACHE_REINIT = 1,
    SCRIPT_CACHE_LOADING = 2,
    SCRIPT_CACHE_READY = 3
};

struct LuaScript;

class ElunaLoader
{
private:
    ElunaLoader();
    ~ElunaLoader();

public:
    ElunaLoader(ElunaLoader const&) = delete;
    ElunaLoader(ElunaLoader&&) = delete;

    ElunaLoader& operator= (ElunaLoader const&) = delete;
    ElunaLoader& operator= (ElunaLoader&&) = delete;
    static ElunaLoader* instance();

    void LoadScripts();
    bool ShouldMapLoadEluna(uint32 mapId);
    void ReloadElunaForMap(int mapId);

    uint8 GetCacheState() const { return _cacheState.load(); }
    const std::vector<LuaScript>& GetLuaScripts() const { return lua_scripts; }
    const std::string& GetRequirePath() const { return lua_requirepath; }
    const std::string& GetRequireCPath() const { return lua_requirecpath; }

    typedef std::list<LuaScript> ScriptList;

#ifdef TRINITY
    // efsw file watcher
    void InitializeFileWatcher();
    efsw::FileWatcher lua_fileWatcher;
    efsw::WatchID lua_scriptWatcher;
#endif

private:
    void ReloadScriptCache();
    void ReadFiles(lua_State* L, std::string path);
    void CombineLists();
    void ProcessScript(lua_State* L, std::string filename, const std::string& fullpath, int32 mapId);
    bool CompileScript(lua_State* L, LuaScript& script);
    static int LoadBytecodeChunk(lua_State* L, uint8* bytes, size_t len, BytecodeBuffer* buffer);

protected:
    std::atomic<uint8> _cacheState;
    std::vector<LuaScript> lua_scripts;
    std::string lua_requirepath;
    std::string lua_requirecpath;
    ScriptList _scripts;
    ScriptList _extensions;
    std::list<uint32> requiredMaps;
    std::thread _reloadThread;
};

#ifdef TRINITY
/// File watcher responsible for watching lua scripts
class ElunaUpdateListener : public efsw::FileWatchListener
{
public:
    ElunaUpdateListener() { }
    virtual ~ElunaUpdateListener() { }

    void handleFileAction(efsw::WatchID /*watchid*/, std::string const& dir,
        std::string const& filename, efsw::Action /*action*/, std::string oldFilename = "") final override;
};

static ElunaUpdateListener elunaUpdateListener;
#endif

#define sElunaLoader ElunaLoader::instance()

#endif
