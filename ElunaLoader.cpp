/*
* Copyright (C) 2010 - 2024 Eluna Lua Engine <https://elunaluaengine.github.io/>
* Copyright (C) 2022 - 2022 Hour of Twilight <https://www.houroftwilight.net/>
* This program is free software licensed under GPL version 3
* Please see the included DOCS/LICENSE.md for more information
*/

#include "LuaEngine.h"
#include "ElunaCompat.h"
#include "ElunaConfig.h"
#include "ElunaLoader.h"
#include "ElunaUtility.h"
#include "ElunaIncludes.h"
#include <fstream>
#include <sstream>

#ifdef USING_BOOST
#include <boost/filesystem.hpp>
namespace fs = boost::filesystem;
#else
#include <filesystem>
namespace fs = std::filesystem;
#endif

#ifdef ELUNA_WINDOWS
#include <Windows.h>
#endif

#ifdef TRINITY
#include "MapManager.h"
#endif

extern "C" {
#include <lua.h>
#include <lualib.h>
#include <lauxlib.h>
}

ElunaLoader::ElunaLoader()
{
}

ElunaLoader* ElunaLoader::instance()
{
    static ElunaLoader instance;
    return &instance;
}

ElunaLoader::~ElunaLoader()
{
}

void ElunaLoader::LoadScripts()
{
    lua_folderpath = sElunaConfig->GetConfig(CONFIG_ELUNA_SCRIPT_PATH);
    const std::string& lua_path_extra = sElunaConfig->GetConfig(CONFIG_ELUNA_REQUIRE_PATH_EXTRA);
    const std::string& lua_cpath_extra = sElunaConfig->GetConfig(CONFIG_ELUNA_REQUIRE_CPATH_EXTRA);

    uint32 oldMSTime = ElunaUtil::GetCurrTime();
    lua_scripts.clear();
    lua_extensions.clear();
    combined_scripts.clear();
#ifndef ELUNA_WINDOWS
    if (lua_folderpath[0] == '~')
        if (const char* home = getenv("HOME"))
            lua_folderpath.replace(0, 1, home);
#endif
    ELUNA_LOG_INFO("[Eluna]: Searching for scripts in `%s`", lua_folderpath.c_str());
    lua_requirepath.clear();
    lua_requirecpath.clear();

    // open a new temporary Lua state to compile bytecode in
    lua_State* L = luaL_newstate();
    luaL_openlibs(L);

    // read and compile all scripts
    ReadFiles(L, lua_folderpath);

    // close temporary Lua state
    lua_close(L);

    // combine lists of Lua scripts and extensions
    CombineLists();

    // append our custom require paths and cpaths if the config variables are not empty
    if (!lua_path_extra.empty())
        lua_requirepath += lua_path_extra;

    if (!lua_cpath_extra.empty())
        lua_requirecpath += lua_cpath_extra;

    // Erase last ;
    if (!lua_requirepath.empty())
        lua_requirepath.erase(lua_requirepath.end() - 1);

    if (!lua_requirecpath.empty())
        lua_requirecpath.erase(lua_requirecpath.end() - 1);

    ELUNA_LOG_INFO("[Eluna]: Loaded and precompiled %u scripts in %u ms", uint32(combined_scripts.size()), ElunaUtil::GetTimeDiff(oldMSTime));
    requiredMaps.clear();
    std::istringstream maps(sElunaConfig->GetConfig(CONFIG_ELUNA_ONLY_ON_MAPS));
    while (maps.good())
    {
        std::string mapIdStr;
        std::getline(maps, mapIdStr, ',');
        if (maps.fail() || maps.bad())
            break;
        try {
            uint32 mapId = std::stoul(mapIdStr);
            requiredMaps.emplace_back(mapId);
        }
        catch (std::exception&) {
            ELUNA_LOG_ERROR("[Eluna]: Error tokenizing Eluna.OnlyOnMaps, invalid config value '%s'", mapIdStr.c_str());
        }
    }
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
    ELUNA_LOG_DEBUG("[Eluna]: ReadFiles from path `%s`", path.c_str());

    fs::path someDir(path);
    fs::directory_iterator end_iter;

    if (fs::exists(someDir) && fs::is_directory(someDir) && !fs::is_empty(someDir))
    {
        lua_requirepath +=
            path + "/?.lua;" +
            path + "/?.ext;" +
            path + "/?.moon;";

        lua_requirecpath +=
            path + "/?.dll;" +
            path + "/?.so;";

        for (fs::directory_iterator dir_iter(someDir); dir_iter != end_iter; ++dir_iter)
        {
            std::string fullpath = dir_iter->path().generic_string();
            // Check if file is hidden
#ifdef ELUNA_WINDOWS
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
                int32 mapId;

                // strip base folder path and trailing slash from fullpath
                std::string subfolder = dir_iter->path().generic_string();
                subfolder = subfolder.erase(0, lua_folderpath.size() + 1);

                // stringstream used for conversion
                std::stringstream ss;

                // push subfolder int to subMapId
                ss << subfolder;
                ss >> mapId;

                // if this failed, then we load the script for all maps
                if (ss.fail())
                    mapId = -1;

                // just in case we have a subfolder named an int less than all..
                if (mapId < -1)
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
        lua_extensions.push_back(script);
    else
        lua_scripts.push_back(script);
    ELUNA_LOG_DEBUG("[Eluna]: ProcessScript processed `%s` successfully", fullpath.c_str());
}

static bool ScriptPathComparator(const LuaScript& first, const LuaScript& second)
{
    return first.filepath < second.filepath;
}

void ElunaLoader::CombineLists()
{
    lua_extensions.sort(ScriptPathComparator);
    lua_scripts.sort(ScriptPathComparator);
    combined_scripts.insert(combined_scripts.end(), lua_extensions.begin(), lua_extensions.end());
    combined_scripts.insert(combined_scripts.end(), lua_scripts.begin(), lua_scripts.end());
}

bool ElunaLoader::ShouldMapLoadEluna(uint32 id)
{
    if (!requiredMaps.size())
        return true;

    return (std::find(requiredMaps.begin(), requiredMaps.end(), id) != requiredMaps.end());
}
