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
#include "SharedDefines.h"

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

    // Get wrapped object pointer
    void* GetObj() const { return object; }
    // Returns whether the object is valid or not
    bool IsValid() const { return _isvalid; }
    // Returns whether the object can be invalidated or not
    bool CanInvalidate() const { return _invalidate; }

    // Sets the object pointer that is wrapped
    void SetObj(void* obj)
    {
        ASSERT(obj);
        object = obj;
        SetValid(true);
    }
    // Sets the object pointer to valid or invalid
    void SetValid(bool valid)
    {
        ASSERT(!valid || (valid && object));
        _isvalid = valid;
    }
    // Sets whether the pointer will be invalidated at end of calls
    void SetValidation(bool invalidate)
    {
        _invalidate = invalidate;
    }
    // Invalidates the pointer if it should be invalidated
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
        lua_pushcfunction(E->L, ToString);
        lua_setfield(E->L, metatable, "__tostring");

        // garbage collecting
        lua_pushcfunction(E->L, CollectGarbage);
        lua_setfield(E->L, metatable, "__gc");

        // make methods accessible through metatable
        lua_pushvalue(E->L, methods);
        lua_setfield(E->L, metatable, "__index");

        // make new indexes saved to methods
        lua_pushvalue(E->L, methods);
        lua_setfield(E->L, metatable, "__newindex");

        // make new indexes saved to methods
        lua_pushcfunction(E->L, Add);
        lua_setfield(E->L, metatable, "__add");

        // make new indexes saved to methods
        lua_pushcfunction(E->L, Substract);
        lua_setfield(E->L, metatable, "__sub");

        // make new indexes saved to methods
        lua_pushcfunction(E->L, Multiply);
        lua_setfield(E->L, metatable, "__mul");

        // make new indexes saved to methods
        lua_pushcfunction(E->L, Divide);
        lua_setfield(E->L, metatable, "__div");

        // make new indexes saved to methods
        lua_pushcfunction(E->L, Mod);
        lua_setfield(E->L, metatable, "__mod");

        // make new indexes saved to methods
        lua_pushcfunction(E->L, Pow);
        lua_setfield(E->L, metatable, "__pow");

        // make new indexes saved to methods
        lua_pushcfunction(E->L, UnaryMinus);
        lua_setfield(E->L, metatable, "__unm");

        // make new indexes saved to methods
        lua_pushcfunction(E->L, Concat);
        lua_setfield(E->L, metatable, "__concat");

        // make new indexes saved to methods
        lua_pushcfunction(E->L, Length);
        lua_setfield(E->L, metatable, "__len");

        // make new indexes saved to methods
        lua_pushcfunction(E->L, Equal);
        lua_setfield(E->L, metatable, "__eq");

        // make new indexes saved to methods
        lua_pushcfunction(E->L, Less);
        lua_setfield(E->L, metatable, "__lt");

        // make new indexes saved to methods
        lua_pushcfunction(E->L, LessOrEqual);
        lua_setfield(E->L, metatable, "__le");

        // make new indexes saved to methods
        lua_pushcfunction(E->L, Call);
        lua_setfield(E->L, metatable, "__call");

        // special method to get the object type
        lua_pushcfunction(E->L, GetType);
        lua_setfield(E->L, methods, "GetObjectType");

        // special method to decide object invalidation at end of call
        lua_pushcfunction(E->L, SetInvalidation);
        lua_setfield(E->L, methods, "SetInvalidation");

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
            lua_pushcclosure(E->L, CallMethod, 2);
            lua_settable(E->L, -3);
        }

        lua_remove(E->L, -1);
    }

    static int Push(lua_State* L, T const* obj)
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
            if (ElunaObject* elunaObj = Eluna::CHECKTYPE(L, -1, tname, false))
            {
                // set userdata valid
                elunaObj->SetValid(true);

                // remove userdata_table, leave userdata
                lua_remove(L, -2);
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

    static T* Check(lua_State* L, int narg, bool error = true)
    {
        ElunaObject* elunaObj = Eluna::CHECKTYPE(L, narg, tname, error);
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

    static int GetType(lua_State* L)
    {
        lua_pushstring(L, tname);
        return 1;
    }

    static int SetInvalidation(lua_State* L)
    {
        ElunaObject* elunaObj = Eluna::CHECKOBJ<ElunaObject>(L, 1);
        bool invalidate = Eluna::CHECKVAL<bool>(L, 2);

        elunaObj->SetValidation(invalidate);
        return 0;
    }

    static int CallMethod(lua_State* L)
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

    // Metamethods ("virtual")

    // Remember special cases like ElunaTemplate<Vehicle>::CollectGarbage
    static int CollectGarbage(lua_State* L)
    {
        // Get object pointer (and check type, no error)
        ElunaObject* obj = Eluna::CHECKOBJ<ElunaObject>(L, 1, false);
        if (obj && manageMemory)
            delete static_cast<T*>(obj->GetObj());
        delete obj;
        return 0;
    }

    static int ToString(lua_State* L)
    {
        T* obj = Eluna::CHECKOBJ<T>(L, 1, true); // get self
        lua_pushfstring(L, "%s: (%p)", tname, obj);
        return 1;
    }

    static int Add(lua_State* L) { return 0; }
    static int Substract(lua_State* L) { return 0; }
    static int Multiply(lua_State* L) { return 0; }
    static int Divide(lua_State* L) { return 0; }
    static int Mod(lua_State* L) { return 0; }
    static int Pow(lua_State* L) { return 0; }
    static int UnaryMinus(lua_State* L) { return 0; }
    static int Concat(lua_State* L) { return 0; }
    static int Length(lua_State* L) { return 0; }
    static int Equal(lua_State* L) { return 0; }
    static int Less(lua_State* L) { return 0; }
    static int LessOrEqual(lua_State* L) { return 0; }
    static int Call(lua_State* L) { return 0; }
};
//
//template<typename T> const char* ElunaTemplate<T>::tname;
//template<typename T> bool ElunaTemplate<T>::manageMemory;

#if (!defined(TBC) && !defined(CLASSIC))
template<> int ElunaTemplate<Vehicle>::CollectGarbage(lua_State* L);
#endif

template<> int ElunaTemplate<uint32>::Add(lua_State* L);
template<> int ElunaTemplate<uint32>::Substract(lua_State* L);
template<> int ElunaTemplate<uint32>::Multiply(lua_State* L);
template<> int ElunaTemplate<uint32>::Divide(lua_State* L);
template<> int ElunaTemplate<uint32>::Mod(lua_State* L);
template<> int ElunaTemplate<uint32>::Pow(lua_State* L);
// template<> int ElunaTemplate<uint32>::UnaryMinus(lua_State* L);
template<> int ElunaTemplate<uint32>::Concat(lua_State* L);
template<> int ElunaTemplate<uint32>::Length(lua_State* L);
template<> int ElunaTemplate<uint32>::Equal(lua_State* L);
template<> int ElunaTemplate<uint32>::Less(lua_State* L);
template<> int ElunaTemplate<uint32>::LessOrEqual(lua_State* L);
template<> int ElunaTemplate<uint32>::Call(lua_State* L);

template<> int ElunaTemplate<int32>::Add(lua_State* L);
template<> int ElunaTemplate<int32>::Substract(lua_State* L);
template<> int ElunaTemplate<int32>::Multiply(lua_State* L);
template<> int ElunaTemplate<int32>::Divide(lua_State* L);
template<> int ElunaTemplate<int32>::Mod(lua_State* L);
template<> int ElunaTemplate<int32>::Pow(lua_State* L);
template<> int ElunaTemplate<int32>::UnaryMinus(lua_State* L);
template<> int ElunaTemplate<int32>::Concat(lua_State* L);
template<> int ElunaTemplate<int32>::Length(lua_State* L);
template<> int ElunaTemplate<int32>::Equal(lua_State* L);
template<> int ElunaTemplate<int32>::Less(lua_State* L);
template<> int ElunaTemplate<int32>::LessOrEqual(lua_State* L);
template<> int ElunaTemplate<int32>::Call(lua_State* L);

#endif
