/*
* Copyright (C) 2010 - 2024 Eluna Lua Engine <https://elunaluaengine.github.io/>
* This program is free software licensed under GPL version 3
* Please see the included DOCS/LICENSE.md for more information
*/

#if defined TRINITY || defined MANGOS
#include "Config.h"
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
    // Load eluna.conf configuration file
#ifdef TRINITY
    std::string configError;
    if (!sConfigMgr->LoadInitial(ELUNA_CONFIG, std::vector<std::string>(), configError))
    {
        printf("Error: %s. Eluna will be disabled.\n", configError.c_str());
        return;
    }
#elif CMANGOS
    if (!config.SetSource(ELUNA_CONFIG, "Eluna_"))
    {
        sLog.outString("Unable to open configuration file(%s). Eluna will be disabled.", ELUNA_CONFIG);
        return;
    }
#elif VMANGOS
    if (!config.SetSource(ELUNA_CONFIG))
    {
        sLog.Out(LOG_BASIC, LOG_LVL_ERROR, "Unable to open configuration file(%s). Eluna will be disabled.", ELUNA_CONFIG);
        return;
    }
#endif

    // Load bools
    SetConfig(CONFIG_ELUNA_ENABLED, "Eluna.Enabled", false);
    SetConfig(CONFIG_ELUNA_COMPATIBILITY_MODE, "Eluna.CompatibilityMode", true);
    SetConfig(CONFIG_ELUNA_TRACEBACK, "Eluna.TraceBack", false);

    // Load strings
    SetConfig(CONFIG_ELUNA_SCRIPT_PATH, "Eluna.ScriptPath", "lua_scripts");
    SetConfig(CONFIG_ELUNA_ONLY_ON_MAPS, "Eluna.OnlyOnMaps", "");
    SetConfig(CONFIG_ELUNA_REQUIRE_PATH_EXTRA, "Eluna.RequirePaths", "");
    SetConfig(CONFIG_ELUNA_REQUIRE_CPATH_EXTRA, "Eluna.RequireCPaths", "");
}

void ElunaConfig::SetConfig(ElunaConfigBoolValues index, char const* fieldname, bool defvalue)
{
#ifdef TRINITY
    SetConfig(index, sConfigMgr->GetBoolDefault(fieldname, defvalue));
#elif defined CMANGOS || defined VMANGOS
    SetConfig(index, config.GetBoolDefault(fieldname, defvalue));
#elif MANGOS
    SetConfig(index, sConfig.GetBoolDefault(fieldname, defvalue));
#endif
}

void ElunaConfig::SetConfig(ElunaConfigStringValues index, char const* fieldname, std::string defvalue)
{
#ifdef TRINITY
    SetConfig(index, sConfigMgr->GetStringDefault(fieldname, defvalue));
#elif CMANGOS
    SetConfig(index, config.GetStringDefault(fieldname, defvalue));
#elif VMANGOS
    SetConfig(index, config.GetStringDefault(fieldname, defvalue.c_str()));
#elif MANGOS
    SetConfig(index, sConfig.GetStringDefault(fieldname, defvalue.c_str()));
#endif
}

bool ElunaConfig::IsElunaEnabled()
{
    return GetConfig(CONFIG_ELUNA_ENABLED);
}

bool ElunaConfig::IsElunaCompatibilityMode()
{
    return GetConfig(CONFIG_ELUNA_COMPATIBILITY_MODE);
}
