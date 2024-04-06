/*
* Copyright (C) 2010 - 2022 Eluna Lua Engine <https://elunaluaengine.github.io/>
* Copyright (C) 2022 - 2022 Hour of Twilight <https://www.houroftwilight.net/>
* This program is free software licensed under GPL version 3
* Please see the included DOCS/LICENSE.md for more information
*/

#ifndef _ELUNALOADER_H
#define _ELUNALOADER_H

#include "ElunaUtility.h"

extern "C"
{
#include "lua.h"
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
    void ReadFiles(lua_State* L, std::string path);
    void CombineLists();
    void ProcessScript(lua_State* L, std::string filename, const std::string& fullpath, int32 mapId);
    bool ShouldMapLoadEluna(uint32 mapId);
    bool CompileScript(lua_State* L, LuaScript& script);
    static int LoadBytecodeChunk(lua_State* L, uint8* bytes, size_t len, BytecodeBuffer* buffer);

    // Lua script folder path
    std::string lua_folderpath;
    // lua path variable for require() function
    std::string lua_requirepath;
    std::string lua_requirecpath;

    typedef std::list<LuaScript> ScriptList;
    ScriptList lua_scripts;
    ScriptList lua_extensions;
    std::vector<LuaScript> combined_scripts;
    std::list<uint32> requiredMaps;
};

#define sElunaLoader ElunaLoader::instance()

#endif
