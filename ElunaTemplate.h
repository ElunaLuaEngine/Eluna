/*
* Copyright (C) 2010 - 2024 Eluna Lua Engine <https://elunaluaengine.github.io/>
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
#include "ElunaCompat.h"
#ifndef CMANGOS
#include "SharedDefines.h"
#else
#include "Globals/SharedDefines.h"
#endif

class ElunaGlobal
{
public:
    struct ElunaRegister
    {
        const char* name;
        int(*func)(Eluna*);
        MethodRegisterState regState = METHOD_REG_ALL;
    };

    static int thunk(lua_State* L)
    {
        ElunaRegister* l = static_cast<ElunaRegister*>(lua_touserdata(L, lua_upvalueindex(1)));
        Eluna* E = static_cast<Eluna*>(lua_touserdata(L, lua_upvalueindex(2)));
        int top = lua_gettop(L);
        int expected = l->func(E);
        int args = lua_gettop(L) - top;
        if (args < 0 || args > expected)
        {
            ELUNA_LOG_ERROR("[Eluna]: %s returned unexpected amount of arguments %i out of %i. Report to devs", l->name, args, expected);
            ASSERT(false);
        }
        lua_settop(L, top + expected);
        return expected;
    }

    static void SetMethods(Eluna* E, ElunaRegister* methodTable)
    {
        ASSERT(E);
        ASSERT(methodTable);

        lua_pushglobaltable(E->L);

        for (; methodTable && methodTable->name; ++methodTable)
        {
            lua_pushstring(E->L, methodTable->name);

            // if the method should not be registered, push a closure to error output function
            if (methodTable->regState == METHOD_REG_NONE)
            {
                lua_pushcclosure(E->L, MethodUnimpl, 0);
                lua_rawset(E->L, -3);
                continue;
            }

            // if we're in multistate mode, we need to check whether a method is flagged as a world or a map specific method
            if (!E->GetCompatibilityMode() && methodTable->regState != METHOD_REG_ALL)
            {
                // if the method should not be registered, push a closure to error output function
                if ((E->GetBoundMapId() == -1 && methodTable->regState == METHOD_REG_MAP) ||
                    (E->GetBoundMapId() != -1 && methodTable->regState == METHOD_REG_WORLD))
                {
                    lua_pushcclosure(E->L, MethodWrongState, 0);
                    lua_rawset(E->L, -3);
                    continue;
                }
            }

            // push method table and Eluna object pointers as light user data
            lua_pushlightuserdata(E->L, (void*)methodTable);
            lua_pushlightuserdata(E->L, (void*)E);

            // push a closure to the thunk function with 2 upvalues (method table and Eluna object)
            lua_pushcclosure(E->L, thunk, 2);
            lua_rawset(E->L, -3);
        }

        lua_remove(E->L, -1);
    }

    static int MethodWrongState(lua_State* L) { luaL_error(L, "attempt to call a method that does not exist for state: %d", Eluna::GetEluna(L)->GetBoundMapId()); return 0; }
    static int MethodUnimpl(lua_State* L) { luaL_error(L, "attempt to call a method that is not implemented for this emulator"); return 0; }
};

class ElunaObject
{
public:
    ElunaObject(Eluna* E, char const* tname) : E(E), type_name(tname)
    {
    }

    virtual ~ElunaObject()
    {
    }

    // Get wrapped object pointer
    virtual void* GetObj() const = 0;
    // Returns whether the object is valid or not
    virtual bool IsValid() const = 0;
    // Returns pointer to the wrapped object's type name
    const char* GetTypeName() const { return type_name; }
    // Invalidates the pointer if it should be invalidated
    virtual void Invalidate() = 0;

protected:
    Eluna* E;
    const char* type_name;
};

template <typename T>
class ElunaObjectImpl : public ElunaObject
{
public:
    ElunaObjectImpl(Eluna* E, T* obj, char const* tname) : ElunaObject(E, tname), _obj(obj), callstackid(E->GetCallstackId())
    {
    }

    void* GetObj() const override { return _obj; }
    bool IsValid() const override { return callstackid == E->GetCallstackId(); }
    void Invalidate() override { callstackid = 1; }

private:
    void* _obj;
    uint64 callstackid;
};

template <typename T>
class ElunaObjectValueImpl : public ElunaObject
{
public:
    ElunaObjectValueImpl(Eluna* E, T* obj, char const* tname) : ElunaObject(E, tname), _obj(*obj /*always a copy, what gets passed here might be pointing to something not owned by us*/)
    {
    }

    void* GetObj() const override { return const_cast<T*>(&_obj); }
    bool IsValid() const override { return true; }
    void Invalidate() override { }

private:
    T _obj;
};

#define MAKE_ELUNA_OBJECT_VALUE_IMPL(type) \
template <> \
class ElunaObjectImpl<type> : public ElunaObjectValueImpl<type> \
{ \
public: \
    using ElunaObjectValueImpl::ElunaObjectValueImpl; \
}

MAKE_ELUNA_OBJECT_VALUE_IMPL(long long);
MAKE_ELUNA_OBJECT_VALUE_IMPL(unsigned long long);
MAKE_ELUNA_OBJECT_VALUE_IMPL(ObjectGuid);
MAKE_ELUNA_OBJECT_VALUE_IMPL(WorldPacket);
MAKE_ELUNA_OBJECT_VALUE_IMPL(ElunaQuery);

template<typename T>
struct ElunaRegister
{
    const char* name;
    int(*mfunc)(Eluna*, T*);
    MethodRegisterState regState = METHOD_REG_ALL;
};

template<typename T>
class ElunaTemplate
{
public:
    static const char* tname;

    // name will be used as type name
    // If gc is true, lua will handle the memory management for object pushed
    // gc should be used if pushing for example WorldPacket,
    // that will only be needed on lua side and will not be managed by TC/mangos/<core>
    static void Register(Eluna* E, const char* name)
    {
        ASSERT(E);
        ASSERT(name);

        // check that metatable isn't already there
        lua_getglobal(E->L, name);
        ASSERT(lua_isnoneornil(E->L, -1));

        // pop nil
        lua_pop(E->L, 1);

        tname = name;

        // create metatable for userdata of this type
        luaL_newmetatable(E->L, tname);
        int metatable  = lua_gettop(E->L);

        // push methodtable to stack to be accessed and modified by users
        lua_pushvalue(E->L, metatable);
        lua_setglobal(E->L, tname);

        // tostring
        lua_pushcfunction(E->L, ToString);
        lua_setfield(E->L, metatable, "__tostring");

        // garbage collecting
        lua_pushcfunction(E->L, CollectGarbage);
        lua_setfield(E->L, metatable, "__gc");

        // TODO: Safe to remove this?
        // make methods accessible through metatable
        lua_pushvalue(E->L, metatable);
        lua_setfield(E->L, metatable, "__index");

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
        lua_setfield(E->L, metatable, "GetObjectType");

        // pop metatable
        lua_pop(E->L, 1);
    }

    template<typename C>
    static void SetMethods(Eluna* E, ElunaRegister<C>* methodTable)
    {
        ASSERT(E);
        ASSERT(tname);
        ASSERT(methodTable);

        // get metatable
        lua_pushstring(E->L, tname);
        lua_rawget(E->L, LUA_REGISTRYINDEX);
        ASSERT(lua_istable(E->L, -1));

        // load all core-specific methods
        for (; methodTable && methodTable->name; ++methodTable)
        {
            // push the method name to the Lua stack
            lua_pushstring(E->L, methodTable->name);

            // if the method should not be registered, push a closure to error output function
            if (methodTable->regState == METHOD_REG_NONE)
            {
                lua_pushcclosure(E->L, MethodUnimpl, 0);
                lua_rawset(E->L, -3);
                continue;
            }

            // if we're in multistate mode, we need to check whether a method is flagged as a world or a map specific method
            if (!E->GetCompatibilityMode() && methodTable->regState != METHOD_REG_ALL)
            {
                // if the method should not be registered, push a closure to error output function
                if ((E->GetBoundMapId() == -1 && methodTable->regState == METHOD_REG_MAP) ||
                    (E->GetBoundMapId() != -1 && methodTable->regState == METHOD_REG_WORLD))
                {
                    lua_pushcclosure(E->L, MethodWrongState, 0);
                    lua_rawset(E->L, -3);
                    continue;
                }
            }

            // push method table and Eluna object pointers as light user data
            lua_pushlightuserdata(E->L, (void*)methodTable);
            lua_pushlightuserdata(E->L, (void*)E);

            // push a closure to the thunk function with 2 upvalues (method table and Eluna object)
            lua_pushcclosure(E->L, thunk, 2);
            lua_rawset(E->L, -3);
        }

        lua_pop(E->L, 1);
    }

    static int Push(Eluna* E, T const* obj)
    {
        lua_State* L = E->L;
        if (!obj)
        {
            lua_pushnil(L);
            return 1;
        }

        typedef ElunaObjectImpl<T> ElunaObjectType;

        // Create new userdata
        ElunaObjectType* elunaObject = static_cast<ElunaObjectType*>(lua_newuserdata(L, sizeof(ElunaObjectType)));
        if (!elunaObject)
        {
            ELUNA_LOG_ERROR("%s could not create new userdata", tname);
            lua_pushnil(L);
            return 1;
        }
        new (elunaObject) ElunaObjectType(E, const_cast<T*>(obj), tname);

        // Set metatable for it
        lua_pushstring(L, tname);
        lua_rawget(L, LUA_REGISTRYINDEX);
        if (!lua_istable(L, -1))
        {
            ELUNA_LOG_ERROR("%s missing metatable", tname);
            lua_pop(L, 2);
            lua_pushnil(L);
            return 1;
        }
        lua_setmetatable(L, -2);
        return 1;
    }

    static T* Check(Eluna* E, int narg, bool error = true)
    {
        lua_State* L = E->L;

        ElunaObject* elunaObj = E->CHECKTYPE(narg, tname, error);
        if (!elunaObj)
            return NULL;

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

    static int thunk(lua_State* L)
    {
        ElunaRegister<T>* l = static_cast<ElunaRegister<T>*>(lua_touserdata(L, lua_upvalueindex(1)));
        Eluna* E = static_cast<Eluna*>(lua_touserdata(L, lua_upvalueindex(2)));

        T* obj = E->CHECKOBJ<T>(1); // get self
        if (!obj)
            return 0;

        int top = lua_gettop(L);
        int expected = l->mfunc(E, obj);
        int args = lua_gettop(L) - top;
        if (args < 0 || args > expected)
        {
            ELUNA_LOG_ERROR("[Eluna]: %s returned unexpected amount of arguments %i out of %i. Report to devs", l->name, args, expected);
            ASSERT(false);
        }
        lua_settop(L, top + expected);
        return expected;
    }

    // Metamethods ("virtual")

    // Remember special cases like ElunaTemplate<Vehicle>::CollectGarbage
    static int CollectGarbage(lua_State* L)
    {
        Eluna* E = Eluna::GetEluna(L);

        // Get object pointer (and check type, no error)
        ElunaObject* obj = E->CHECKOBJ<ElunaObject>(1, false);
        obj->~ElunaObject();
        return 0;
    }

    static int ToString(lua_State* L)
    {
        Eluna* E = Eluna::GetEluna(L);

        T* obj = E->CHECKOBJ<T>(1, true); // get self
        lua_pushfstring(L, "%s: %p", tname, obj);
        return 1;
    }

    static int ArithmeticError(lua_State* L) { return luaL_error(L, "attempt to perform arithmetic on a %s value", tname); }
    static int CompareError(lua_State* L) { return luaL_error(L, "attempt to compare %s", tname); }
    static int Add(lua_State* L) { return ArithmeticError(L); }
    static int Substract(lua_State* L) { return ArithmeticError(L); }
    static int Multiply(lua_State* L) { return ArithmeticError(L); }
    static int Divide(lua_State* L) { return ArithmeticError(L); }
    static int Mod(lua_State* L) { return ArithmeticError(L); }
    static int Pow(lua_State* L) { return ArithmeticError(L); }
    static int UnaryMinus(lua_State* L) { return ArithmeticError(L); }
    static int Concat(lua_State* L) { return luaL_error(L, "attempt to concatenate a %s value", tname); }
    static int Length(lua_State* L) { return luaL_error(L, "attempt to get length of a %s value", tname); }
    static int Equal(lua_State* L) { Eluna* E = Eluna::GetEluna(L); E->Push(E->CHECKOBJ<T>(1) == E->CHECKOBJ<T>(2)); return 1; }
    static int Less(lua_State* L) { return CompareError(L); }
    static int LessOrEqual(lua_State* L) { return CompareError(L); }
    static int Call(lua_State* L) { return luaL_error(L, "attempt to call a %s value", tname); }

    static int MethodWrongState(lua_State* L) { luaL_error(L, "attempt to call a method that does not exist for state: %d", Eluna::GetEluna(L)->GetBoundMapId()); return 0; }
    static int MethodUnimpl(lua_State* L) { luaL_error(L, "attempt to call a method that is not implemented for this emulator"); return 0; }
};

template<typename T> const char* ElunaTemplate<T>::tname = NULL;

#endif
