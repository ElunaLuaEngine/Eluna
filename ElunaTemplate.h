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
#include "ElunaConfig.h"
#include "ElunaSpellWrapper.h"
#if !defined ELUNA_CMANGOS
#include "SharedDefines.h"
#else
#include "Globals/SharedDefines.h"
#include "Util/UniqueTrackablePtr.h"
#endif

#if defined ELUNA_TRINITY
#include "UniqueTrackablePtr.h"
#endif

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
    virtual void* GetObjIfValid() const = 0;
    // Returns pointer to the wrapped object's type name
    const char* GetTypeName() const { return type_name; }
#if !defined TRACKABLE_PTR_NAMESPACE
    // Invalidates the pointer if it should be invalidated
    virtual void Invalidate() = 0;
#endif

protected:
    Eluna* E;
    const char* type_name;
};

#if defined TRACKABLE_PTR_NAMESPACE
template <typename T>
struct ElunaConstrainedObjectRef
{
    TRACKABLE_PTR_NAMESPACE unique_weak_ptr<T> Obj;
    Map const* BoundMap = nullptr;
};

ElunaConstrainedObjectRef<Aura> GetWeakPtrFor(Aura const* obj);
ElunaConstrainedObjectRef<AuraEffect> GetWeakPtrFor(AuraEffect const* obj);
ElunaConstrainedObjectRef<ElunaProcInfo> GetWeakPtrFor(ElunaProcInfo const* obj);
ElunaConstrainedObjectRef<BattleGround> GetWeakPtrFor(BattleGround const* obj);
ElunaConstrainedObjectRef<Group> GetWeakPtrFor(Group const* obj);
ElunaConstrainedObjectRef<Guild> GetWeakPtrFor(Guild const* obj);
ElunaConstrainedObjectRef<Map> GetWeakPtrFor(Map const* obj);
ElunaConstrainedObjectRef<Object> GetWeakPtrForObjectImpl(Object const* obj);
ElunaConstrainedObjectRef<Quest> GetWeakPtrFor(Quest const* obj);
ElunaConstrainedObjectRef<Spell> GetWeakPtrFor(Spell const* obj);
ElunaConstrainedObjectRef<ElunaSpellInfo> GetWeakPtrFor(ElunaSpellInfo const* obj);
#if ELUNA_EXPANSION >= EXP_WOTLK
ElunaConstrainedObjectRef<Vehicle> GetWeakPtrFor(Vehicle const* obj);
#endif

template <typename T>
ElunaConstrainedObjectRef<T> GetWeakPtrFor(T const* obj)
{
    ElunaConstrainedObjectRef<Object> ref = GetWeakPtrForObjectImpl(obj);
    return { TRACKABLE_PTR_NAMESPACE static_pointer_cast<T>(ref.Obj), ref.BoundMap };
}

#endif

template <typename T>
class ElunaObjectImpl : public ElunaObject
{
public:
#if defined TRACKABLE_PTR_NAMESPACE
    ElunaObjectImpl(Eluna* E, T const* obj, char const* tname) : ElunaObject(E, tname), _obj(GetWeakPtrFor(obj))
    {
    }

    void* GetObjIfValid() const override
    {
        if (TRACKABLE_PTR_NAMESPACE unique_strong_ref_ptr<T> obj = _obj.Obj.lock())
            if (!E->GetBoundMap() || !_obj.BoundMap || E->GetBoundMap() == _obj.BoundMap)
                return obj.get();

        return nullptr;
    }
#else
    ElunaObjectImpl(Eluna* E, T* obj, char const* tname) : ElunaObject(E, tname), _obj(obj), callstackid(E->GetCallstackId())
    {
    }

    void* GetObjIfValid() const override
    {
        if (callstackid == E->GetCallstackId())
            return _obj;

        return nullptr;
    }

    void Invalidate() override { callstackid = 1; }
#endif

private:
#if defined TRACKABLE_PTR_NAMESPACE
    ElunaConstrainedObjectRef<T> _obj;
#else
    void* _obj;
    uint64 callstackid;
#endif
};

template <typename T>
class ElunaObjectValueImpl : public ElunaObject
{
public:
    ElunaObjectValueImpl(Eluna* E, T const* obj, char const* tname) : ElunaObject(E, tname), _obj(*obj /*always a copy, what gets passed here might be pointing to something not owned by us*/)
    {
    }

    void* GetObjIfValid() const override { return const_cast<T*>(&_obj); }

#if !defined TRACKABLE_PTR_NAMESPACE
    void Invalidate() override { }
#endif

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

template<typename T = void>
struct ElunaRegister
{
    const char* name;
    typename std::conditional<std::is_same_v<T, void>, int(*)(Eluna*), int(*)(Eluna*, T*)>::type mfunc;
    MethodRegisterState regState;
    MethodFlags flags;

    // constructor for class methods
    ElunaRegister(const char* name, int(*func)(Eluna*, T*), MethodRegisterState state = METHOD_REG_ALL, uint32 flags = METHOD_FLAG_NONE)
        : name(name), mfunc(func), regState(state), flags(static_cast<MethodFlags>(flags)) {}

    // constructor for global methods
    ElunaRegister(const char* name, int(*func)(Eluna*), MethodRegisterState state = METHOD_REG_ALL, uint32 flags = METHOD_FLAG_NONE)
        : name(name), mfunc(func), regState(state), flags(static_cast<MethodFlags>(flags)) {}

    // constructor for unimplemented methods
    ElunaRegister(const char* name, MethodRegisterState state = METHOD_REG_NONE, uint32 flags = METHOD_FLAG_NONE)
        : name(name), mfunc(nullptr), regState(state), flags(static_cast<MethodFlags>(flags)) {}
};

template<typename T = void>
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

        lua_State* L = E->L;

        // check that metatable isn't already there
        lua_getglobal(L, name);
        ASSERT(lua_isnoneornil(L, -1));

        // pop nil
        lua_pop(L, 1);

        tname = name;

        // create metatable for userdata of this type
        luaL_newmetatable(L, tname);
        int metatable = lua_gettop(L);

        // push methodtable to stack to be accessed and modified by users
        lua_pushvalue(L, metatable);
        lua_setglobal(L, tname);

        // tostring
        lua_pushcfunction(L, ToString);
        lua_setfield(L, metatable, "__tostring");

        // garbage collecting
        lua_pushcfunction(L, CollectGarbage);
        lua_setfield(L, metatable, "__gc");

        // TODO: Safe to remove this?
        // make methods accessible through metatable
        lua_pushvalue(L, metatable);
        lua_setfield(L, metatable, "__index");

        // make new indexes saved to methods
        lua_pushcfunction(L, Add);
        lua_setfield(L, metatable, "__add");

        // make new indexes saved to methods
        lua_pushcfunction(L, Subtract);
        lua_setfield(L, metatable, "__sub");

        // make new indexes saved to methods
        lua_pushcfunction(L, Multiply);
        lua_setfield(L, metatable, "__mul");

        // make new indexes saved to methods
        lua_pushcfunction(L, Divide);
        lua_setfield(L, metatable, "__div");

        // make new indexes saved to methods
        lua_pushcfunction(L, Mod);
        lua_setfield(L, metatable, "__mod");

        // make new indexes saved to methods
        lua_pushcfunction(L, Pow);
        lua_setfield(L, metatable, "__pow");

        // make new indexes saved to methods
        lua_pushcfunction(L, UnaryMinus);
        lua_setfield(L, metatable, "__unm");

        // make new indexes saved to methods
        lua_pushcfunction(L, Concat);
        lua_setfield(L, metatable, "__concat");

        // make new indexes saved to methods
        lua_pushcfunction(L, Length);
        lua_setfield(L, metatable, "__len");

        // make new indexes saved to methods
        lua_pushcfunction(L, Equal);
        lua_setfield(L, metatable, "__eq");

        // make new indexes saved to methods
        lua_pushcfunction(L, Less);
        lua_setfield(L, metatable, "__lt");

        // make new indexes saved to methods
        lua_pushcfunction(L, LessOrEqual);
        lua_setfield(L, metatable, "__le");

        // make new indexes saved to methods
        lua_pushcfunction(L, Call);
        lua_setfield(L, metatable, "__call");

        // special method to get the object type
        lua_pushcfunction(L, GetType);
        lua_setfield(L, metatable, "GetObjectType");

        // pop metatable
        lua_pop(L, 1);
    }

    template<typename C, size_t N>
    static void SetMethods(Eluna* E, ElunaRegister<C> const (&methodTable)[N])
    {
        ASSERT(E);
        ASSERT(methodTable);

        lua_State* L = E->L;

        // determine if the method table functions are global or non-global
        constexpr bool isGlobal = std::is_same_v<C, void>;

        if constexpr (isGlobal)
        {
            lua_pushglobaltable(L);
        }
        else
        {
            ASSERT(tname);

            // get metatable
            lua_pushstring(L, tname);
            lua_rawget(L, LUA_REGISTRYINDEX);
            ASSERT(lua_istable(L, -1));
        }

        // load all core-specific methods
        for (std::size_t i = 0; i < N; i++)
        {
            const auto& method = methodTable + i;

            // push the method name to the Lua stack
            lua_pushstring(L, method->name);

            // if the method should not be registered, push a closure to error output function
            if (method->regState == METHOD_REG_NONE)
            {
                lua_pushstring(L, method->name);
                lua_pushcclosure(L, MethodUnimpl, 1);
                lua_rawset(L, -3);
                continue;
            }

            // if the method is considered unsafe, and unsafe methods have not been enabled, push a closure to error output function
            if (method->flags & METHOD_FLAG_UNSAFE && !sElunaConfig->UnsafeMethodsEnabled())
            {
                lua_pushstring(L, method->name);
                lua_pushcclosure(L, MethodUnsafe, 1);
                lua_rawset(L, -3);
                continue;
            }

            // if the method is considered deprecated, and deprecated methods have not been enabled, push a closure to error output function
            if (method->flags & METHOD_FLAG_DEPRECATED && !sElunaConfig->DeprecatedMethodsEnabled())
            {
                lua_pushstring(L, method->name);
                lua_pushcclosure(L, MethodDeprecated, 1);
                lua_rawset(L, -3);
                continue;
            }

            // if we're in multistate mode, we need to check whether a method is flagged as a world or a map specific method
            if (method->regState != METHOD_REG_ALL)
            {
                int32 mapId = E->GetBoundMapId();

                // if the method should not be registered, push a closure to error output function
                if ((mapId == -1 && method->regState == METHOD_REG_MAP) ||
                    (mapId != -1 && method->regState == METHOD_REG_WORLD))
                {
                    lua_pushstring(L, method->name);
                    lua_pushinteger(L, mapId);
                    lua_pushcclosure(L, MethodWrongState, 2);
                    lua_rawset(L, -3);
                    continue;
                }
            }

            // push a closure to the thunk with the method pointer as light user data
            lua_pushlightuserdata(L, (void*)method);
            lua_pushcclosure(L, thunk, 1);
            lua_rawset(L, -3);
        }

        lua_pop(L, 1);
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

        void* obj = elunaObj->GetObjIfValid();
        if (!obj)
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
        return static_cast<T*>(obj);
    }

    static int GetType(lua_State* L)
    {
        lua_pushstring(L, tname);
        return 1;
    }

    static int thunk(lua_State* L)
    {
        ElunaRegister<T>* l = static_cast<ElunaRegister<T>*>(lua_touserdata(L, lua_upvalueindex(1)));
        Eluna* E = Eluna::GetEluna(L);

        // determine if the method table functions are global or non-global
        constexpr bool isGlobal = std::is_same_v<T, void>;

        // we only check self if the method is not a global
        T* obj;
        if constexpr (!isGlobal)
        {
            obj = E->CHECKOBJ<T>(1);
            if (!obj)
                return 0;
        }

        int top = lua_gettop(L);

        int expected = 0;
        if constexpr (isGlobal)
            expected = l->mfunc(E);      // global method
        else
            expected = l->mfunc(E, obj); // non-global method

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
    static int Subtract(lua_State* L) { return ArithmeticError(L); }
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

    static int MethodWrongState(lua_State* L) { luaL_error(L, "attempt to call method '%s' that does not exist for state: %d", lua_tostring(L, lua_upvalueindex(1)), lua_tointeger(L, lua_upvalueindex(2))); return 0; }
    static int MethodUnimpl(lua_State* L) { luaL_error(L, "attempt to call method '%s' that is not implemented for this emulator", lua_tostring(L, lua_upvalueindex(1))); return 0; }
    static int MethodUnsafe(lua_State* L) { luaL_error(L, "attempt to call method '%s' that is flagged as unsafe! to use this method, enable unsafe methods in the config file", lua_tostring(L, lua_upvalueindex(1))); return 0; }
    static int MethodDeprecated(lua_State* L) { luaL_error(L, "attempt to call method '%s' that is flagged as deprecated! this method will be removed in the future. to use this method, enable deprecated methods in the config file", lua_tostring(L, lua_upvalueindex(1))); return 0; }
};

template<typename T> const char* ElunaTemplate<T>::tname = NULL;

#endif
