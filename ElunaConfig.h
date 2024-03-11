/*
* Copyright (C) 2010 - 2024 Eluna Lua Engine <https://elunaluaengine.github.io/>
* This program is free software licensed under GPL version 3
* Please see the included DOCS/LICENSE.md for more information
*/

#ifndef _ELUNACONFIG_H
#define _ELUNACONFIG_H

#include "ElunaUtility.h"

enum ElunaConfigBoolValues
{
    CONFIG_ELUNA_ENABLED,
    CONFIG_ELUNA_COMPATIBILITY_MODE,
    CONFIG_ELUNA_TRACEBACK,
    CONFIG_ELUNA_BOOL_COUNT
};

enum ElunaConfigStringValues
{
    CONFIG_ELUNA_SCRIPT_PATH,
    CONFIG_ELUNA_ONLY_ON_MAPS,
    CONFIG_ELUNA_REQUIRE_PATH_EXTRA,
    CONFIG_ELUNA_REQUIRE_CPATH_EXTRA,
    CONFIG_ELUNA_STRING_COUNT
};

class ElunaConfig
{
private:
    ElunaConfig();
    ~ElunaConfig();
    ElunaConfig(ElunaConfig const&) = delete;
    ElunaConfig& operator=(ElunaConfig const&) = delete;

public:
    static ElunaConfig* instance();

    void Initialize();

    bool GetConfig(ElunaConfigBoolValues index) const { return _configBoolValues[index]; }
    const std::string& GetConfig(ElunaConfigStringValues index) const { return _configStringValues[index]; }
    void SetConfig(ElunaConfigBoolValues index, bool value) { _configBoolValues[index] = value; }
    void SetConfig(ElunaConfigStringValues index, std::string value) { _configStringValues[index] = value; }

    bool IsElunaEnabled();
    bool IsElunaCompatibilityMode();

private:
    bool _configBoolValues[CONFIG_ELUNA_BOOL_COUNT];
    std::string _configStringValues[CONFIG_ELUNA_STRING_COUNT];

    void SetConfig(ElunaConfigBoolValues index, char const* fieldname, bool defvalue);
    void SetConfig(ElunaConfigStringValues index, char const* fieldname, std::string defvalue);
};

#define sElunaConfig ElunaConfig::instance()

#endif //_ELUNACONFIG_H
