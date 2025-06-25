/*
* Copyright (C) 2010 - 2025 Eluna Lua Engine <https://elunaluaengine.github.io/>
* This program is free software licensed under GPL version 3
* Please see the included DOCS/LICENSE.md for more information
*/

#ifndef CUSTOMMETHODSINT_H
#define CUSTOMMETHODSINT_H

#ifdef ELUNA_USE_CUSTOM_METHODS
    #include "CustomMethods.h"
#else
namespace LuaCustom
{
    inline void RegisterCustomMethods([[maybe_unused]] Eluna* E) {}
}
#endif

#endif
