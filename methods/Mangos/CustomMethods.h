/*
* Copyright (C) 2010 - 2024 Eluna Lua Engine <https://elunaluaengine.github.io/>
* This program is free software licensed under GPL version 3
* Please see the included DOCS/LICENSE.md for more information
*/

// This file is used for custom Lua methods, without needing to edit the existing method header files.
// This can also be used to override default methods without needing to edit existing methods.
// It follows the same structure as any other method header, except you can use RegisterCustomFunction
// to register multiple method tables in a single file.

#include "ElunaTemplate.h"
#include "ElunaIncludes.h"

#ifndef CUSTOMMETHODS_H
#define CUSTOMMETHODS_H

namespace LuaCustom
{
    // See the CustomMethods header file in the TC method directory for an example.
    inline void RegisterCustomMethods([[maybe_unused]] Eluna* E)
    {

    };
};

#endif
