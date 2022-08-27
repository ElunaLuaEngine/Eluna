/*
* Copyright (C) 2010 - 2022 Eluna Lua Engine <https://elunaluaengine.github.io/>
* Copyright (C) 2022 - 2022 Hour of Twilight <https://www.houroftwilight.net/>
* This program is free software licensed under GPL version 3
* Please see the included DOCS/LICENSE.md for more information
*/

#include "LuaEngine.h"
#include "ElunaLoader.h"
#include "ElunaUtility.h"
#include "ElunaIncludes.h"
#include <filesystem>
#include <fstream>
#include <boost/filesystem.hpp>

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
    lua_folderpath = eConfigMgr->GetStringDefault("Eluna.ScriptPath", "lua_scripts");

    uint32 oldMSTime = ElunaUtil::GetCurrTime();
    lua_scripts.clear();
    lua_extensions.clear();
    combined_scripts.clear();
#ifndef ELUNA_WINDOWS
    if (lua_folderpath[0] == '~')
        if (const char* home = getenv("HOME"))
            lua_folderpath.replace(0, 1, home);
#endif
    ELUNA_LOG_INFO("[Eluna]: Searching scripts from `%s`", lua_folderpath.c_str());
    lua_requirepath.clear();
    ReadFiles(lua_folderpath);

    // Combine extensions and lua scripts into one list for proper loading order.
    CombineLists();

    // Erase last ;
    if (!lua_requirepath.empty())
        lua_requirepath.erase(lua_requirepath.end() - 1);

    ELUNA_LOG_INFO("[Eluna]: Loaded %u scripts in %u ms", uint32(combined_scripts.size()), ElunaUtil::GetTimeDiff(oldMSTime));

    requiredMaps.clear();
    
    std::string maps = sConfigMgr->GetStringDefault("Eluna.OnlyOnMaps", "");
    for (std::string_view mapIdStr : Trinity::Tokenize(maps, ',', false))
    {
        int32 mapId = Trinity::StringTo<int32>(mapIdStr).value_or(-1);
        if(mapId >= 0)
            requiredMaps.emplace_back(mapId);
        //@todo: error message for being unable to read correctly
    }
}

// Finds lua script files from given path (including subdirectories) and pushes them to scripts
void ElunaLoader::ReadFiles(std::string path)
{
    ELUNA_LOG_DEBUG("[Eluna]: GetScripts from path `%s`", path.c_str());

    boost::filesystem::path someDir(path);
    boost::filesystem::directory_iterator end_iter;

    if (boost::filesystem::exists(someDir) && boost::filesystem::is_directory(someDir))
    {
        lua_requirepath +=
            path + "/?.lua;" +
            path + "/?.ext;" +
            path + "/?.dll;" +
            path + "/?.so;";

        for (boost::filesystem::directory_iterator dir_iter(someDir); dir_iter != end_iter; ++dir_iter)
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
            if (boost::filesystem::is_directory(dir_iter->status()))
            {
                ReadFiles(fullpath);
                continue;
            }

            if (boost::filesystem::is_regular_file(dir_iter->status()))
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
                AddScriptPath(filename, fullpath, mapId);
            }
        }
    }
}

void ElunaLoader::AddScriptPath(std::string filename, const std::string& fullpath, int32 mapId)
{
    ELUNA_LOG_DEBUG("[Eluna]: AddScriptPath Checking file `%s`", fullpath.c_str());

    // split file name
    std::size_t extDot = filename.find_last_of('.');
    if (extDot == std::string::npos)
        return;
    std::string ext = filename.substr(extDot);
    filename = filename.substr(0, extDot);

    // check extension and add path to scripts to load
    if (ext != ".lua" && ext != ".dll" && ext != ".so" && ext != ".ext")
        return;
    bool extension = ext == ".ext";

    // open file
    std::ifstream file(fullpath, std::ios::in | std::ios::binary);
    if (!file.is_open())
        return;

    // read contents
    std::string content{ std::istreambuf_iterator<char>(file), std::istreambuf_iterator<char>() };

    // close file
    file.close();

    LuaScript script;
    script.fileext = ext;
    script.filename = filename;
    script.filepath = fullpath;
    script.modulepath = fullpath.substr(0, fullpath.length() - filename.length() - ext.length());
    script.filedata = content;
    script.mapId = mapId;

    if (extension)
        lua_extensions.push_back(script);
    else
        lua_scripts.push_back(script);
    ELUNA_LOG_DEBUG("[Eluna]: AddScriptPath add path `%s`", fullpath.c_str());
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
