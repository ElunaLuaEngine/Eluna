/*
* Copyright (C) 2010 - 2024 Eluna Lua Engine <https://elunaluaengine.github.io/>
* This program is free software licensed under GPL version 3
* Please see the included DOCS/LICENSE.md for more information
*/

#if defined ELUNA_TRINITY
#include "Config.h"
#else
#include "Config/Config.h"
#endif
#include "ElunaConfig.h"

ElunaConfig::ElunaConfig()
{
}

ElunaConfig* ElunaConfig::instance()
{
    static ElunaConfig instance;
    return &instance;
}

ElunaConfig::~ElunaConfig()
{
}

void ElunaConfig::Initialize()
{
    // Load bools
    SetConfig(CONFIG_ELUNA_ENABLED, "Eluna.Enabled", true);
    SetConfig(CONFIG_ELUNA_TRACEBACK, "Eluna.TraceBack", false);
    SetConfig(CONFIG_ELUNA_SCRIPT_RELOADER, "Eluna.ScriptReloader", false);
    SetConfig(CONFIG_ELUNA_ENABLE_UNSAFE, "Eluna.UseUnsafeMethods", true);
    SetConfig(CONFIG_ELUNA_ENABLE_DEPRECATED, "Eluna.UseDeprecatedMethods", true);
    SetConfig(CONFIG_ELUNA_ENABLE_RELOAD_COMMAND, "Eluna.ReloadCommand", true);

    // Load strings
    SetConfig(CONFIG_ELUNA_SCRIPT_PATH, "Eluna.ScriptPath", "lua_scripts");
    SetConfig(CONFIG_ELUNA_ONLY_ON_MAPS, "Eluna.OnlyOnMaps", "");
    SetConfig(CONFIG_ELUNA_REQUIRE_PATH_EXTRA, "Eluna.RequirePaths", "");
    SetConfig(CONFIG_ELUNA_REQUIRE_CPATH_EXTRA, "Eluna.RequireCPaths", "");

    // Load ints
    SetConfig(CONFIG_ELUNA_RELOAD_SECURITY_LEVEL, "Eluna.ReloadSecurityLevel", 3);

    // Call extra functions
    TokenizeAllowedMaps();
}

void ElunaConfig::SetConfig(ElunaConfigBoolValues index, char const* fieldname, bool defvalue)
{
#if defined ELUNA_TRINITY
    SetConfig(index, sConfigMgr->GetBoolDefault(fieldname, defvalue));
#else
    SetConfig(index, sConfig.GetBoolDefault(fieldname, defvalue));
#endif
}

void ElunaConfig::SetConfig(ElunaConfigStringValues index, char const* fieldname, std::string defvalue)
{
#if defined ELUNA_TRINITY
    SetConfig(index, sConfigMgr->GetStringDefault(fieldname, defvalue));
#elif defined ELUNA_CMANGOS
    SetConfig(index, sConfig.GetStringDefault(fieldname, defvalue));
#else
    SetConfig(index, sConfig.GetStringDefault(fieldname, defvalue.c_str()));
#endif
}

void ElunaConfig::SetConfig(ElunaConfigUInt32Values index, char const* fieldname, uint32 defvalue)
{
#if defined ELUNA_TRINITY
    SetConfig(index, sConfigMgr->GetIntDefault(fieldname, defvalue));
#else
    SetConfig(index, sConfig.GetIntDefault(fieldname, defvalue));
#endif
}

bool ElunaConfig::ShouldMapLoadEluna(uint32 id)
{
    // if the set is empty (all maps), return true
    if (m_allowedMaps.empty())
        return true;

    // Check if the map ID is in the set
    return (m_allowedMaps.find(id) != m_allowedMaps.end());
}

void ElunaConfig::TokenizeAllowedMaps()
{
    // clear allowed maps
    m_allowedMaps.clear();

    // read the configuration value into stringstream
    std::istringstream maps(GetConfig(CONFIG_ELUNA_ONLY_ON_MAPS));

    // tokenize maps and add to allowed maps
    std::string mapIdStr;
    while (std::getline(maps, mapIdStr, ','))
    {
        // remove spaces
        mapIdStr.erase(std::remove_if(mapIdStr.begin(), mapIdStr.end(), [](char c) {
            return std::isspace(static_cast<unsigned char>(c));
            }), mapIdStr.end());

        try {
            uint32 mapId = std::stoul(mapIdStr);
            m_allowedMaps.emplace(mapId);
        }
        catch (std::exception&) {
            ELUNA_LOG_ERROR("[Eluna]: Error tokenizing Eluna.OnlyOnMaps, invalid config value '%s'", mapIdStr.c_str());
        }
    }
}
