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
    CONFIG_ELUNA_TRACEBACK,
    CONFIG_ELUNA_SCRIPT_RELOADER,
    CONFIG_ELUNA_ENABLE_UNSAFE,
    CONFIG_ELUNA_ENABLE_DEPRECATED,
    CONFIG_ELUNA_ENABLE_RELOAD_COMMAND,
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

enum ElunaConfigUInt32Values
{
    CONFIG_ELUNA_RELOAD_SECURITY_LEVEL,
    CONFIG_ELUNA_INT_COUNT
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
    const uint32& GetConfig(ElunaConfigUInt32Values index) const { return _configUInt32Values[index]; }

    bool IsElunaEnabled() { return GetConfig(CONFIG_ELUNA_ENABLED); }
    bool UnsafeMethodsEnabled() { return GetConfig(CONFIG_ELUNA_ENABLE_UNSAFE); }
    bool DeprecatedMethodsEnabled() { return GetConfig(CONFIG_ELUNA_ENABLE_DEPRECATED); }
    bool IsReloadCommandEnabled() { return GetConfig(CONFIG_ELUNA_ENABLE_RELOAD_COMMAND); }
    AccountTypes GetReloadSecurityLevel() { return static_cast<AccountTypes>(GetConfig(CONFIG_ELUNA_RELOAD_SECURITY_LEVEL)); }
    bool ShouldMapLoadEluna(uint32 mapId);

private:
    bool _configBoolValues[CONFIG_ELUNA_BOOL_COUNT];
    std::string _configStringValues[CONFIG_ELUNA_STRING_COUNT];
    uint32 _configUInt32Values[CONFIG_ELUNA_INT_COUNT];

    void SetConfig(ElunaConfigBoolValues index, bool value) { _configBoolValues[index] = value; }
    void SetConfig(ElunaConfigStringValues index, std::string value) { _configStringValues[index] = value; }
    void SetConfig(ElunaConfigUInt32Values index, uint32 value) { _configUInt32Values[index] = value; }

    void SetConfig(ElunaConfigBoolValues index, char const* fieldname, bool defvalue);
    void SetConfig(ElunaConfigStringValues index, char const* fieldname, std::string defvalue);
    void SetConfig(ElunaConfigUInt32Values index, char const* fieldname, uint32 defvalue);

    void TokenizeAllowedMaps();

    std::unordered_set<uint32> m_allowedMaps;
};

#define sElunaConfig ElunaConfig::instance()

#endif //_ELUNACONFIG_H
