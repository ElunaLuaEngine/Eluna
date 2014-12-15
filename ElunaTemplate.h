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

class ElunaGlobal
{
public:
    struct ElunaRegister
    {
        const char* name;
        int(*mfunc)(Eluna*, lua_State*);
    };

    static int thunk(lua_State* L)
    {
        ElunaRegister* l = static_cast<ElunaRegister*>(lua_touserdata(L, lua_upvalueindex(1)));
        Eluna* E = static_cast<Eluna*>(lua_touserdata(L, lua_upvalueindex(2)));
        int args = lua_gettop(L);
        int expected = l->mfunc(E, L);
        args = lua_gettop(L) - args;
        if (args < 0 || args > expected) // Assert instead?
        {
            ELUNA_LOG_ERROR("[Eluna]: %s returned unexpected amount of arguments %i out of %i. Report to devs", l->name, args, expected);
        }
        for (; args < expected; ++args)
            lua_pushnil(L);
        return expected;
    }

    static void SetMethods(Eluna* E, ElunaRegister* methodTable)
    {
        if (!methodTable)
            return;

        lua_pushglobaltable(E->L);

        for (; methodTable && methodTable->name && methodTable->mfunc; ++methodTable)
        {
            lua_pushstring(E->L, methodTable->name);
            lua_pushlightuserdata(E->L, (void*)methodTable);
            lua_pushlightuserdata(E->L, (void*)E);
            lua_pushcclosure(E->L, thunk, 2);
            lua_settable(E->L, -3);
        }

        lua_remove(E->L, -1);
    }
};

class ElunaObject
{
public:
    ElunaObject(void* obj, bool manageMemory) : _isvalid(false), _invalidate(!manageMemory), object(obj)
    {
        SetValid(true);
    }

    ~ElunaObject()
    {
    }

    void* GetObj() const { return object; }
    bool IsValid() const { return _isvalid; }
    bool CanInvalidate() const { return _invalidate; }

    void SetObj(void* obj)
    {
        object = obj;
    }
    void SetValid(bool valid)
    {
        _isvalid = object && valid;
    }
    void SetValidation(bool invalidate)
    {
        _invalidate = invalidate;
    }
    void Invalidate()
    {
        if (CanInvalidate())
            _isvalid = false;
    }

private:
    bool _isvalid;
    bool _invalidate;
    void* object;
};

template<typename T>
struct ElunaRegister
{
    const char* name;
    int(*mfunc)(Eluna*, lua_State*, T*);
};

template<typename T>
class ElunaTemplate
{
public:
    static const char* tname;
    static bool manageMemory;

    // name will be used as type name
    // If gc is true, lua will handle the memory management for object pushed
    // gc should be used if pushing for example WorldPacket,
    // that will only be needed on lua side and will not be managed by TC/mangos/<core>
    static void Register(Eluna* E, const char* name, bool gc = false)
    {
        ASSERT(!tname || name);

        tname = name;
        manageMemory = gc;

        lua_newtable(E->L);
        int methods = lua_gettop(E->L);

        // store method table in globals so that
        // scripts can add functions in Lua
        lua_pushvalue(E->L, methods);
        lua_setglobal(E->L, tname);

        luaL_newmetatable(E->L, tname);
        int metatable = lua_gettop(E->L);

        // tostring
        lua_pushcfunction(E->L, tostringT);
        lua_setfield(E->L, metatable, "__tostring");

        // garbage collecting
        if (manageMemory)
        {
            lua_pushcfunction(E->L, gcT);
            lua_setfield(E->L, metatable, "__gc");
        }

        // make methods accessible through metatable
        lua_pushvalue(E->L, methods);
        lua_setfield(E->L, metatable, "__index");

        // make new indexes saved to methods
        lua_pushvalue(E->L, methods);
        lua_setfield(E->L, metatable, "__newindex");

        // special method to get the object type
        lua_pushcfunction(E->L, typeT);
        lua_setfield(E->L, methods, "GetObjectType");

        // pop methods and metatable
        lua_pop(E->L, 2);
    }

    template<typename C>
    static void SetMethods(Eluna* E, ElunaRegister<C>* methodTable)
    {
        if (!methodTable)
            return;

        luaL_getmetatable(E->L, tname);
        if (!lua_istable(E->L, -1))
        {
            lua_remove(E->L, -1);
            ELUNA_LOG_ERROR("%s missing metatable", tname);
            return;
        }

        lua_getfield(E->L, -1, "__index");
        lua_remove(E->L, -2);
        if (!lua_istable(E->L, -1))
        {
            lua_remove(E->L, -1);
            ELUNA_LOG_ERROR("%s missing method table from metatable", tname);
            return;
        }

        for (; methodTable && methodTable->name && methodTable->mfunc; ++methodTable)
        {
            lua_pushstring(E->L, methodTable->name);
            lua_pushlightuserdata(E->L, (void*)methodTable);
            lua_pushlightuserdata(E->L, (void*)E);
            lua_pushcclosure(E->L, thunk, 2);
            lua_settable(E->L, -3);
        }

        lua_remove(E->L, -1);
    }

    static int push(lua_State* L, T const* obj)
    {
        if (!obj)
        {
            lua_pushnil(L);
            return 1;
        }

        //if (!manageMemory)
        //{
            lua_getglobal(L, ELUNA_OBJECT_STORE);
            ASSERT(lua_istable(L, -1));
            lua_pushfstring(L, "%p", obj);
            lua_gettable(L, -2);
            if (!lua_isnoneornil(L, -1) && luaL_checkudata(L, -1, tname))
            {
                // remove userdata_table, leave userdata
                lua_remove(L, -2);

                // set userdata valid
                if (ElunaObject* elunaObj = Eluna::CHECKOBJ<ElunaObject>(L, -1, false))
                    elunaObj->SetValid(true);
                return 1;
            }
            lua_remove(L, -1);
            // left userdata_table in stack
        //}

        // Create new userdata
        ElunaObject** ptrHold = static_cast<ElunaObject**>(lua_newuserdata(L, sizeof(ElunaObject*)));
        if (!ptrHold)
        {
            ELUNA_LOG_ERROR("%s could not create new userdata", tname);
            lua_pop(L, 2 /*manageMemory ? 1 : 2*/);
            lua_pushnil(L);
            return 1;
        }
        *ptrHold = new ElunaObject((void*)(obj), manageMemory);

        // Set metatable for it
        luaL_getmetatable(L, tname);
        if (!lua_istable(L, -1))
        {
            ELUNA_LOG_ERROR("%s missing metatable", tname);
            lua_pop(L, 3 /*manageMemory ? 2 : 3*/);
            lua_pushnil(L);
            return 1;
        }
        lua_setmetatable(L, -2);

        //if (!manageMemory)
        //{
            lua_pushfstring(L, "%p", obj);
            lua_pushvalue(L, -2);
            lua_settable(L, -4);
            lua_remove(L, -2);
        //}
        return 1;
    }

    static T* check(lua_State* L, int narg, bool error = true)
    {
        ElunaObject* elunaObj = Eluna::CHECKOBJ<ElunaObject>(L, narg, error);

        if (!elunaObj)
            return NULL;

        //if (!manageMemory)
        //{
        //    // Check pointer validity
        //    lua_rawgeti(L, LUA_REGISTRYINDEX, sEluna->userdata_table);
        //    lua_pushfstring(L, "%p", (*ptrHold)->GetObj());
        //    lua_gettable(L, -2);
        //    lua_remove(L, -2);
        //    bool valid = lua_isuserdata(L, -1) != 0;
        //    lua_remove(L, -1);
        //    if (!valid)
        //    {
        //        char buff[256];
        //        snprintf(buff, 256, "%s expected, got pointer to nonexisting object (%s). This should never happen", tname, luaL_typename(L, narg));
        //        if (error)
        //        {
        //            luaL_argerror(L, narg, buff);
        //        }
        //        else
        //        {
        //            ELUNA_LOG_ERROR("%s", buff);
        //        }
        //        return NULL;
        //    }
        //}

        if (!elunaObj->IsValid())
        {
            char buff[256];
            snprintf(buff, 256, "%s expected, got pointer to nonexisting (invalidated) object (%s). Check your code.", tname, luaL_typename(L, narg));
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
        return static_cast<T*>(elunaObj->GetObj());
    }

    static int typeT(lua_State* L)
    {
        lua_pushstring(L, tname);
        return 1;
    }

    // Remember special case ElunaTemplate<Vehicle>::gcT
    static int gcT(lua_State* L)
    {
        // Get object pointer (and check type, no error)
        ElunaObject** ptrHold = static_cast<ElunaObject**>(luaL_testudata(L, -1, tname));
        if (ptrHold)
        {
            if (manageMemory)
                delete static_cast<T*>((*ptrHold)->GetObj());
            delete *ptrHold;
        }
        return 0;
    }

    static int thunk(lua_State* L)
    {
        T* obj = Eluna::CHECKOBJ<T>(L, 1); // get self
        if (!obj)
            return 0;
        ElunaRegister<T>* l = static_cast<ElunaRegister<T>*>(lua_touserdata(L, lua_upvalueindex(1)));
        Eluna* E = static_cast<Eluna*>(lua_touserdata(L, lua_upvalueindex(2)));
        int top = lua_gettop(L);
        int expected = l->mfunc(E, L, obj);
        int args = lua_gettop(L) - top;
        if (args < 0 || args > expected) // Assert instead?
        {
            ELUNA_LOG_ERROR("[Eluna]: %s returned unexpected amount of arguments %i out of %i. Report to devs", l->name, args, expected);
        }
        if (args == expected)
            return expected;
        lua_settop(L, top);
        return 0;
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
