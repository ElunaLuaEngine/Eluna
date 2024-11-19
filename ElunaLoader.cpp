/*
* Copyright (C) 2010 - 2024 Eluna Lua Engine <https://elunaluaengine.github.io/>
* Copyright (C) 2022 - 2022 Hour of Twilight <https://www.houroftwilight.net/>
* This program is free software licensed under GPL version 3
* Please see the included DOCS/LICENSE.md for more information
*/

#include "ElunaCompat.h"
#include "ElunaConfig.h"
#include "ElunaLoader.h"
#include "ElunaUtility.h"
#include <fstream>
#include <sstream>
#include <thread>
#include <charconv>

#if defined USING_BOOST
#include <boost/filesystem.hpp>
namespace fs = boost::filesystem;
#else
#include <filesystem>
namespace fs = std::filesystem;
#endif

#if defined ELUNA_WINDOWS
#include <Windows.h>
#endif

#if defined ELUNA_TRINITY || ELUNA_MANGOS
#include "MapManager.h"
#elif defined ELUNA_CMANGOS
#include "Maps/MapManager.h"
#endif

extern "C" {
#include <lua.h>
#include <lualib.h>
#include <lauxlib.h>
}

#if defined ELUNA_TRINITY
void ElunaUpdateListener::handleFileAction(efsw::WatchID /*watchid*/, std::string const& dir, std::string const& filename, efsw::Action /*action*/, std::string /*oldFilename*/)
{
    auto const path = fs::absolute(filename, dir);
    if (!path.has_extension())
        return;

    std::string ext = path.extension().string();
    std::transform(ext.begin(), ext.end(), ext.begin(), [](unsigned char c) { return std::tolower(c); });

    if (ext != ".lua" && ext != ".ext")
        return;

    sElunaLoader->ReloadElunaForMap(RELOAD_ALL_STATES);
}
#endif

ElunaLoader::ElunaLoader() : m_cacheState(SCRIPT_CACHE_NONE)
{
#if defined ELUNA_TRINITY
    lua_scriptWatcher = -1;
#endif
}

ElunaLoader* ElunaLoader::instance()
{
    static ElunaLoader instance;
    return &instance;
}

ElunaLoader::~ElunaLoader()
{
    // join any previously created reload thread so it can exit cleanly
    if (m_reloadThread.joinable())
        m_reloadThread.join();

#if defined ELUNA_TRINITY
    if (lua_scriptWatcher >= 0)
    {
        lua_fileWatcher.removeWatch(lua_scriptWatcher);
        lua_scriptWatcher = -1;
    }
#endif
}

void ElunaLoader::ReloadScriptCache()
{
    // if the internal cache state is anything other than ready, we return
    if (m_cacheState != SCRIPT_CACHE_READY)
    {
        ELUNA_LOG_DEBUG("[Eluna]: Script cache not ready, skipping reload");
        return;
    }

    // try to join any previous thread before starting a new one, just in case
    if (m_reloadThread.joinable())
        m_reloadThread.join();

    // set the internal cache state to reinit
    m_cacheState = SCRIPT_CACHE_REINIT;

    // create new thread to load scripts asynchronously
    m_reloadThread = std::thread(&ElunaLoader::LoadScripts, this);
    ELUNA_LOG_DEBUG("[Eluna]: Script cache reload thread started");
}

void ElunaLoader::LoadScripts()
{
    // only reload the cache if it is either in a reinit state or not loaded at all
    if (m_cacheState != SCRIPT_CACHE_REINIT && m_cacheState != SCRIPT_CACHE_NONE)
        return;

    // set the cache state to loading
    m_cacheState = SCRIPT_CACHE_LOADING;

    uint32 oldMSTime = ElunaUtil::GetCurrTime();

    std::string lua_folderpath = sElunaConfig->GetConfig(CONFIG_ELUNA_SCRIPT_PATH);
    const std::string& lua_path_extra = sElunaConfig->GetConfig(CONFIG_ELUNA_REQUIRE_PATH_EXTRA);
    const std::string& lua_cpath_extra = sElunaConfig->GetConfig(CONFIG_ELUNA_REQUIRE_CPATH_EXTRA);
    
#if !defined ELUNA_WINDOWS
    if (lua_folderpath[0] == '~')
        if (const char* home = getenv("HOME"))
            lua_folderpath.replace(0, 1, home);
#endif

    ELUNA_LOG_INFO("[Eluna]: Searching for scripts in `%s`", lua_folderpath.c_str());

    // open a new temporary Lua state to compile bytecode in
    lua_State* L = luaL_newstate();
    luaL_openlibs(L);

    // clear all cache variables
    m_requirePath.clear();
    m_requirecPath.clear();

    // read and compile all scripts
    ReadFiles(L, lua_folderpath);

    // close temporary Lua state
    lua_close(L);

    // combine lists of Lua scripts and extensions
    CombineLists();

    // append our custom require paths and cpaths if the config variables are not empty
    if (!lua_path_extra.empty())
        m_requirePath += lua_path_extra;

    if (!lua_cpath_extra.empty())
        m_requirecPath += lua_cpath_extra;

    // Erase last ;
    if (!m_requirePath.empty())
        m_requirePath.erase(m_requirePath.end() - 1);

    if (!m_requirecPath.empty())
        m_requirecPath.erase(m_requirecPath.end() - 1);

    ELUNA_LOG_INFO("[Eluna]: Loaded and precompiled %u scripts in %u ms", uint32(m_scriptCache.size()), ElunaUtil::GetTimeDiff(oldMSTime));

    // set the cache state to ready
    m_cacheState = SCRIPT_CACHE_READY;
}

int ElunaLoader::LoadBytecodeChunk(lua_State* /*L*/, uint8* bytes, size_t len, BytecodeBuffer* buffer)
{
    for (size_t i = 0; i < len; i++)
        buffer->push_back(bytes[i]);

    return 0;
}

// Finds lua script files from given path (including subdirectories) and pushes them to scripts
void ElunaLoader::ReadFiles(lua_State* L, std::string path)
{
    std::string lua_folderpath = sElunaConfig->GetConfig(CONFIG_ELUNA_SCRIPT_PATH);

    ELUNA_LOG_DEBUG("[Eluna]: ReadFiles from path `%s`", path.c_str());

    fs::path someDir(path);
    fs::directory_iterator end_iter;

    if (fs::exists(someDir) && fs::is_directory(someDir) && !fs::is_empty(someDir))
    {
        m_requirePath +=
            path + "/?.lua;" +
            path + "/?.ext;" +
            path + "/?.moon;";

        m_requirecPath +=
            path + "/?.dll;" +
            path + "/?.so;";

        for (fs::directory_iterator dir_iter(someDir); dir_iter != end_iter; ++dir_iter)
        {
            std::string fullpath = dir_iter->path().generic_string();
            // Check if file is hidden
#if defined ELUNA_WINDOWS
            DWORD dwAttrib = GetFileAttributes(fullpath.c_str());
            if (dwAttrib != INVALID_FILE_ATTRIBUTES && (dwAttrib & FILE_ATTRIBUTE_HIDDEN))
                continue;
#else
            std::string name = dir_iter->path().filename().generic_string().c_str();
            if (name[0] == '.')
                continue;
#endif

            // load subfolder
            if (fs::is_directory(dir_iter->status()))
            {
                ReadFiles(L, fullpath);
                continue;
            }

            if (fs::is_regular_file(dir_iter->status()))
            {
                // default to all maps
                int32 mapId = -1;

                // strip base folder path and trailing slash from fullpath
                std::string subfolder = dir_iter->path().generic_string();
                subfolder = subfolder.erase(0, lua_folderpath.size() + 1);

                // convert subfolder name to an integer
                auto [ptr, ec] = std::from_chars(subfolder.data(), subfolder.data() + subfolder.size(), mapId);

                // default to all maps on invalid map id or map id less than -1
                if (ec == std::errc::invalid_argument || ec == std::errc::result_out_of_range || mapId < -1)
                    mapId = -1;

                // was file, try add
                std::string filename = dir_iter->path().filename().generic_string();
                ProcessScript(L, filename, fullpath, mapId);
            }
        }
    }
}

bool ElunaLoader::CompileScript(lua_State* L, LuaScript& script)
{
    // Attempt to load the file
    int err = 0;
    if (script.fileext == ".moon")
    {
        std::string str = "return require('moonscript').loadfile([[" + script.filepath+ "]])";
        err = luaL_dostring(L, str.c_str());
    } else
        err = luaL_loadfile(L, script.filepath.c_str());

    // If something bad happened, try to find an error.
    if (err != 0)
    {
        ELUNA_LOG_ERROR("[Eluna]: CompileScript failed to load the Lua script `%s`.", script.filename.c_str());
        Eluna::Report(L);
        return false;
    }
    ELUNA_LOG_DEBUG("[Eluna]: CompileScript loaded Lua script `%s`", script.filename.c_str());

    // Everything's OK so far, the script has been loaded, now we need to start dumping it to bytecode.
    err = lua_dump(L, (lua_Writer)LoadBytecodeChunk, &script.bytecode);
    if (err || script.bytecode.empty())
    {
        ELUNA_LOG_ERROR("[Eluna]: CompileScript failed to dump the Lua script `%s` to bytecode.", script.filename.c_str());
        Eluna::Report(L);
        return false;
    }
    ELUNA_LOG_DEBUG("[Eluna]: CompileScript dumped Lua script `%s` to bytecode.", script.filename.c_str());

    // pop the loaded function from the stack
    lua_pop(L, 1);
    return true;
}

void ElunaLoader::ProcessScript(lua_State* L, std::string filename, const std::string& fullpath, int32 mapId)
{
    ELUNA_LOG_DEBUG("[Eluna]: ProcessScript checking file `%s`", fullpath.c_str());

    // split file name
    std::size_t extDot = filename.find_last_of('.');
    if (extDot == std::string::npos)
        return;
    std::string ext = filename.substr(extDot);
    filename = filename.substr(0, extDot);

    // check extension and add path to scripts to load
    if (ext != ".lua" && ext != ".ext" && ext != ".moon")
        return;
    bool extension = ext == ".ext";

    LuaScript script;
    script.fileext = ext;
    script.filename = filename;
    script.filepath = fullpath;
    script.modulepath = fullpath.substr(0, fullpath.length() - filename.length() - ext.length());
    script.mapId = mapId;

    // if compilation fails, we don't add the script 
    if (!CompileScript(L, script))
        return;

    if (extension)
        m_extensions.push_back(script);
    else
        m_scripts.push_back(script);

    ELUNA_LOG_DEBUG("[Eluna]: ProcessScript processed `%s` successfully", fullpath.c_str());
}

#if defined ELUNA_TRINITY
void ElunaLoader::InitializeFileWatcher()
{
    std::string lua_folderpath = sElunaConfig->GetConfig(CONFIG_ELUNA_SCRIPT_PATH);

    lua_scriptWatcher = lua_fileWatcher.addWatch(lua_folderpath, &elunaUpdateListener, true);
    if (lua_scriptWatcher >= 0)
    {
        ELUNA_LOG_INFO("[Eluna]: Script reloader is listening on `%s`.", lua_folderpath.c_str());
    }
    else
    {
        ELUNA_LOG_INFO("[Eluna]: Failed to initialize the script reloader on `%s`.", lua_folderpath.c_str());
    }

    lua_fileWatcher.watch();
}
#endif

static bool ScriptPathComparator(const LuaScript& first, const LuaScript& second)
{
    return first.filepath < second.filepath;
}

void ElunaLoader::CombineLists()
{
    m_extensions.sort(ScriptPathComparator);
    m_scripts.sort(ScriptPathComparator);

    m_scriptCache.clear();
    m_scriptCache.insert(m_scriptCache.end(), m_extensions.begin(), m_extensions.end());
    m_scriptCache.insert(m_scriptCache.end(), m_scripts.begin(), m_scripts.end());

    m_extensions.clear();
    m_scripts.clear();
}

void ElunaLoader::ReloadElunaForMap(int mapId)
{
    // reload the script cache asynchronously
    ReloadScriptCache();

    // If a mapid is provided but does not match any map or reserved id then only script storage is loaded
    if (mapId != RELOAD_CACHE_ONLY)
    {
        if (mapId == RELOAD_GLOBAL_STATE || mapId == RELOAD_ALL_STATES)
#if defined ELUNA_TRINITY
            if (Eluna* e = sWorld->GetEluna())
#else
            if (Eluna* e = sWorld.GetEluna())
#endif
                e->ReloadEluna();

#if defined ELUNA_TRINITY
        sMapMgr->DoForAllMaps([&](Map* map)
#else
        sMapMgr.DoForAllMaps([&](Map* map)
#endif
            {
                if (mapId == RELOAD_ALL_STATES || mapId == static_cast<int>(map->GetId()))
                    if (Eluna* e = map->GetEluna())
                        e->ReloadEluna();
            }
        );
    }
}
