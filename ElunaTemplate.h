/*
* Copyright (C) 2010 - 2014 Eluna Lua Engine <http://emudevs.com/>
* This program is free software licensed under GPL version 3
* Please see the included DOCS/LICENSE.md for more information
*/

#ifndef _ELUNA_TEMPLATE_H
#define _ELUNA_TEMPLATE_H

extern "C"
{
#include "lua.h"
#include "lualib.h"
#include "lauxlib.h"
};
#include "LuaEngine.h"
#include "ElunaUtility.h"

template<typename T>
struct ElunaRegister
{
    const char* name;
    int(*mfunc)(lua_State*, T*);
};

template<typename T>
class ElunaTemplate
{
public:
    static const char* tname;
    static bool manageMemory;

    static int typeT(lua_State* L)
    {
        lua_pushstring(L, tname);
        return 1;
    }

    // name will be used as type name
    // If gc is true, lua will handle the memory management for object pushed
    // gc should be used if pushing for example WorldPacket,
    // that will only be needed on lua side and will not be managed by TC/mangos/<core>
    static void Register(lua_State* L, const char* name, bool gc = false)
    {
        tname = name;
        manageMemory = gc;

        lua_newtable(L);
        int methods = lua_gettop(L);

        // store method table in globals so that
        // scripts can add functions in Lua
        lua_pushvalue(L, methods);
        lua_setglobal(L, tname);

        luaL_newmetatable(L, tname);
        int metatable = lua_gettop(L);

        // tostring
        lua_pushcfunction(L, tostringT);
        lua_setfield(L, metatable, "__tostring");

        // garbage collecting
        if (manageMemory)
        {
            lua_pushcfunction(L, gcT);
            lua_setfield(L, metatable, "__gc");
        }

        // make methods accessible through metatable
        lua_pushvalue(L, methods);
        lua_setfield(L, metatable, "__index");

        // make new indexes saved to methods
        lua_pushvalue(L, methods);
        lua_setfield(L, metatable, "__newindex");

        // special method to get the object type
        lua_pushcfunction(L, typeT);
        lua_setfield(L, methods, "GetObjectType");

        // pop methods and metatable
        lua_pop(L, 2);
    }

    template<typename C>
    static void SetMethods(lua_State* L, ElunaRegister<C>* methodTable)
    {
        if (!methodTable)
            return;

        luaL_getmetatable(L, tname);
        if (!lua_istable(L, -1))
        {
            lua_remove(L, -1);
            ELUNA_LOG_ERROR("%s missing metatable", tname);
            return;
        }

        lua_getfield(L, -1, "__index");
        lua_remove(L, -2);
        if (!lua_istable(L, -1))
        {
            lua_remove(L, -1);
            ELUNA_LOG_ERROR("%s missing method table from metatable", tname);
            return;
        }

        for (; methodTable && methodTable->name && methodTable->mfunc; ++methodTable)
        {
            lua_pushstring(L, methodTable->name);
            lua_pushlightuserdata(L, (void*)methodTable);
            lua_pushcclosure(L, thunk, 1);
            lua_settable(L, -3);
        }

        lua_remove(L, -1);
    }

    // Remember special case ElunaTemplate<Vehicle>::gcT
    static int gcT(lua_State* L)
    {
        if (!manageMemory)
            return 0;

        // Get object pointer (and check type, no error)
        T** ptrHold = static_cast<T**>(luaL_testudata(L, -1, tname));
        if (ptrHold)
            delete *ptrHold;
        return 0;
    }

    static int push(lua_State* L, T const* obj)
    {
        if (!obj)
        {
            lua_pushnil(L);
            return 1;
        }

        if (!manageMemory)
        {
            lua_rawgeti(L, LUA_REGISTRYINDEX, sEluna->userdata_table);
            lua_pushfstring(L, "%p", obj);
            lua_gettable(L, -2);
            if (!lua_isnoneornil(L, -1) && luaL_checkudata(L, -1, tname))
            {
                lua_remove(L, -2);
                return 1;
            }
            lua_remove(L, -1);
            // left userdata_table in stack
        }

        // Create new userdata
        T const** ptrHold = static_cast<T const**>(lua_newuserdata(L, sizeof(T const*)));
        if (!ptrHold)
        {
            ELUNA_LOG_ERROR("%s could not create new userdata", tname);
            lua_pop(L, manageMemory ? 1 : 2);
            lua_pushnil(L);
            return 1;
        }
        *ptrHold = obj;

        // Set metatable for it
        luaL_getmetatable(L, tname);
        if (!lua_istable(L, -1))
        {
            ELUNA_LOG_ERROR("%s missing metatable", tname);
            lua_pop(L, manageMemory ? 2 : 3);
            lua_pushnil(L);
            return 1;
        }
        lua_setmetatable(L, -2);

        if (!manageMemory)
        {
            lua_pushfstring(L, "%p", obj);
            lua_pushvalue(L, -2);
            lua_settable(L, -4);
            lua_remove(L, -2);
        }
        return 1;
    }

    static T* check(lua_State* L, int narg, bool error = true)
    {
        T** ptrHold = static_cast<T**>(lua_touserdata(L, narg));
        if (!ptrHold)
        {
            if (error)
            {
                char buff[256];
                snprintf(buff, 256, "%s expected, got %s", tname, luaL_typename(L, narg));
                luaL_argerror(L, narg, buff);
            }
            return NULL;
        }

        if (!manageMemory)
        {
            // Check pointer validity
            lua_rawgeti(L, LUA_REGISTRYINDEX, sEluna->userdata_table);
            lua_pushfstring(L, "%p", *ptrHold);
            lua_gettable(L, -2);
            lua_remove(L, -2);
            bool valid = lua_isuserdata(L, -1);
            lua_remove(L, -1);
            if (!valid)
            {
                char buff[256];
                snprintf(buff, 256, "%s expected, got pointer to nonexisting object (%s). This should never happen", tname, luaL_typename(L, narg));
                if (error)
                {
                    luaL_argerror(L, narg, buff);
                }
                else
                {
                    ELUNA_LOG_ERROR("%s", buff);
                }
                return NULL;
            }
        }
        return *ptrHold;
    }

    static int thunk(lua_State* L)
    {
        T* obj = Eluna::CHECKOBJ<T>(L, 1); // get self
        if (!obj)
            return 0;
        ElunaRegister<T>* l = static_cast<ElunaRegister<T>*>(lua_touserdata(L, lua_upvalueindex(1)));
        int args = lua_gettop(L);
        int expected = l->mfunc(L, obj);
        args = lua_gettop(L) - args;
        if (args < 0 || args > expected) // Assert instead?
        {
            ELUNA_LOG_ERROR("[Eluna]: %s returned unexpected amount of arguments %i out of %i. Report to devs", l->name, args, expected);
        }
        for (; args < expected; ++args)
            lua_pushnil(L);
        return expected;
    }

    static int tostringT(lua_State* L)
    {
        T* obj = Eluna::CHECKOBJ<T>(L, 1); // get self
        if (obj)
            lua_pushfstring(L, "%s: (%p)", tname, obj);
        else
            lua_pushstring(L, "nil");
        return 1;
    }
};

#endif
