/*
 * Copyright (C) 2010 - 2024 Eluna Lua Engine <https://elunaluaengine.github.io/>
 * This program is free software licensed under GPL version 3
 * Please see the included DOCS/LICENSE.md for more information
 */

#ifndef _HOOK_HELPERS_H
#define _HOOK_HELPERS_H

#include "LuaEngine.h"
#include "ElunaUtility.h"

template<typename T>
struct LuaRet;

template<>
struct LuaRet<bool>
{
    static bool Is(lua_State* L, int idx) { return lua_isboolean(L, idx); }
    static bool Get(Eluna* /*E*/, lua_State* L, int idx) { return lua_toboolean(L, idx) != 0; }
};

template<>
struct LuaRet<int32>
{
    static bool Is(lua_State* L, int idx) { return lua_isnumber(L, idx); }
    static int32 Get(Eluna* E, lua_State* /*L*/, int idx) { return E->CHECKVAL<int32>(idx); }
};

template<>
struct LuaRet<uint32>
{
    static bool Is(lua_State* L, int idx) { return lua_isnumber(L, idx); }
    static uint32 Get(Eluna* E, lua_State* /*L*/, int idx) { return E->CHECKVAL<uint32>(idx); }
};

template<>
struct LuaRet<float>
{
    static bool Is(lua_State* L, int idx) { return lua_isnumber(L, idx); }
    static float Get(Eluna* /*E*/, lua_State* L, int idx) { return static_cast<float>(lua_tonumber(L, idx)); }
};

template<>
struct LuaRet<double>
{
    static bool Is(lua_State* L, int idx) { return lua_isnumber(L, idx); }
    static double Get(Eluna* /*E*/, lua_State* L, int idx) { return lua_tonumber(L, idx); }
};

template<>
struct LuaRet<std::string>
{
    static bool Is(lua_State* L, int idx) { return lua_isstring(L, idx); }
    static std::string Get(Eluna* /*E*/, lua_State* L, int idx)
    {
        const char* s = lua_tostring(L, idx);
        return s ? std::string(s) : std::string();
    }
};

/*
 * Sets up the stack so that event handlers can be called.
 *
 * Returns the number of functions that were pushed onto the stack.
 */
template<typename K1, typename K2>
int Eluna::SetupStack(BindingMap<K1>* bindings1, BindingMap<K2>* bindings2, const K1& key1, const K2& key2, int number_of_arguments)
{
    ASSERT(number_of_arguments == this->push_counter);
    ASSERT(key1.event_id == key2.event_id);
    // Stack: [arguments]

    HookPush(key1.event_id);
    this->push_counter = 0;
    ++number_of_arguments;
    // Stack: [arguments], event_id

    int arguments_top = lua_gettop(L);
    int first_argument_index = arguments_top - number_of_arguments + 1;
    ASSERT(arguments_top >= number_of_arguments);

    lua_insert(L, first_argument_index);
    // Stack: event_id, [arguments]

    bindings1->PushRefsFor(key1);
    if (bindings2)
        bindings2->PushRefsFor(key2);
    // Stack: event_id, [arguments], [functions]

    int number_of_functions = lua_gettop(L) - arguments_top;
    return number_of_functions;
}

/*
 * Replace one of the arguments pushed before `SetupStack` with a new value.
 */
template<typename T>
void Eluna::ReplaceArgument(T value, int index)
{
    ASSERT(index > 0 && index <= lua_gettop(L));
    // Stack: event_id, [arguments], [functions], [results]

    Push(value);
    // Stack: event_id, [arguments], [functions], [results], value

    lua_replace(L, index + 1);
    // Stack: event_id, [arguments and value], [functions], [results]
}

/*
 * indices[i] = stack index captured BEFORE SetupStack() inserts event_id.
 * If indices[i] == 0, we won't ReplaceArgument for that output.
 */
template<typename... Outs, size_t... Is>
void Eluna::ApplyMultiReturnsImpl(int r, std::tuple<Outs&...>& outs, const std::array<int, sizeof...(Outs)>& indices, std::index_sequence<Is...>)
{
    ((
        [&] {
            using T = std::remove_reference_t<std::tuple_element_t<Is, std::tuple<Outs&...>>>;
            const int idx = r + static_cast<int>(Is);

            if (LuaRet<T>::Is(L, idx))
            {
                std::get<Is>(outs) = LuaRet<T>::Get(this, L, idx);

                if (indices[Is] != 0)
                    ReplaceArgument(std::get<Is>(outs), indices[Is]);
            }
        }(),
            0
            ), ...);
}

/*
 * Call all event handlers registered to the event ID/entry combination and ignore any results.
 */
template<typename K1, typename K2>
void Eluna::CallAllFunctions(BindingMap<K1>* bindings1, BindingMap<K2>* bindings2, const K1& key1, const K2& key2)
{
    int number_of_arguments = this->push_counter;
    // Stack: [arguments]

    int number_of_functions = SetupStack(bindings1, bindings2, key1, key2, number_of_arguments);
    // Stack: event_id, [arguments], [functions]

    while (number_of_functions > 0)
    {
        CallOneFunction(number_of_functions, number_of_arguments, 0);
        --number_of_functions;
        // Stack: event_id, [arguments], [functions - 1]
    }
    // Stack: event_id, [arguments]

    CleanUpStack(number_of_arguments);
    // Stack: (empty)
}

/*
 * Call all event handlers registered to the event ID/entry combination,
 *   and returns `default_value` if ALL event handlers returned `default_value`,
 *   otherwise returns the opposite of `default_value`.
 */
template<typename K1, typename K2>
bool Eluna::CallAllFunctionsBool(BindingMap<K1>* bindings1, BindingMap<K2>* bindings2, const K1& key1, const K2& key2, bool default_value/* = false*/)
{
    bool result = default_value;
    // Note: number_of_arguments here does not count in eventID, which is pushed in SetupStack
    int number_of_arguments = this->push_counter;
    // Stack: [arguments]

    int number_of_functions = SetupStack(bindings1, bindings2, key1, key2, number_of_arguments);
    // Stack: event_id, [arguments], [functions]

    while (number_of_functions > 0)
    {
        int r = CallOneFunction(number_of_functions, number_of_arguments, 1);
        --number_of_functions;
        // Stack: event_id, [arguments], [functions - 1], result

        if (lua_isboolean(L, r) && (lua_toboolean(L, r) == 1) != default_value)
            result = !default_value;

        lua_pop(L, 1);
        // Stack: event_id, [arguments], [functions - 1]
    }
    // Stack: event_id, [arguments]

    CleanUpStack(number_of_arguments);
    // Stack: (empty)
    return result;
}

/*
 * Call all event handlers registered to the event ID/entry combination,
 * requesting N returns (N = sizeof...(Outs)), and decoding each return into
 * the corresponding out reference if the Lua type matches.
 *
 * If `out_arg_indices[i]` is non-zero, the corresponding argument slot is
 * replaced in-place so subsequent handlers receive the updated value.
 */
template<typename K1, typename K2, typename... Outs>
void Eluna::CallAllFunctionsMultiReturn(BindingMap<K1>* bindings1, BindingMap<K2>* bindings2, const K1& key1, const K2& key2, std::tuple<Outs&...> outs, const std::array<int, sizeof...(Outs)>& out_arg_indices)
{
    constexpr int number_of_returns = static_cast<int>(sizeof...(Outs));
    const int number_of_arguments = this->push_counter;

    int number_of_functions = SetupStack(bindings1, bindings2, key1, key2, number_of_arguments);
    // Stack: event_id, [arguments], [functions]

    while (number_of_functions > 0)
    {
        int r = CallOneFunction(number_of_functions, number_of_arguments, number_of_returns);
        --number_of_functions;
        // Stack: event_id, [arguments], [functions - 1], [ret0..retN-1]

        ApplyMultiReturnsImpl(r, outs, out_arg_indices, std::index_sequence_for<Outs...>{});

        lua_pop(L, number_of_returns);
        // Stack: event_id, [arguments], [functions - 1]
    }

    CleanUpStack(number_of_arguments);
}

/*
 * Call all event handlers registered to the event ID/entry combination,
 *   and returns `default_value` if ALL event handlers returned `default_value`,
 *   otherwise returns the most recent non-`default_value` return value.
 */
template<typename K1, typename K2>
int Eluna::CallAllFunctionsInt(BindingMap<K1>* bindings1, BindingMap<K2>* bindings2, const K1& key1, const K2& key2, int32 default_value/* = 0*/)
{
    int result = default_value;
    int number_of_arguments = this->push_counter;
    // Stack: [arguments]
    int number_of_functions = SetupStack(bindings1, bindings2, key1, key2, number_of_arguments);
    // Stack: event_id, [arguments], [functions]
    while (number_of_functions > 0)
    {
        int r = CallOneFunction(number_of_functions, number_of_arguments, 1);
        --number_of_functions;
        // Stack: event_id, [arguments], [functions - 1], result
        if (lua_isnumber(L, r))
        {
            int32 ret = static_cast<int32>(lua_tointeger(L, r));
            if (ret != default_value)
                result = ret;
        }
        lua_pop(L, 1);
        // Stack: event_id, [arguments], [functions - 1]
    }
    // Stack: event_id, [arguments]
    CleanUpStack(number_of_arguments);
    // Stack: (empty)
    return result;
}

template<typename K1, typename K2, typename T>
void Eluna::CallAllFunctionsTable(BindingMap<K1>* bindings1, BindingMap<K2>* bindings2, const K1& key1, const K2& key2, std::list<T*>& list)
{
    const int number_of_arguments = this->push_counter;
    int number_of_functions = SetupStack(bindings1, bindings2, key1, key2, number_of_arguments);
    // Stack: event_id, [arguments], [functions]

    // Build table from list at a known stack position
    lua_newtable(L);
    int tableIndex = lua_gettop(L);
    int i = 1;
    for (T* entry : list)
    {
        Push(entry);
        lua_rawseti(L, tableIndex, i++);
    }

    while (number_of_functions > 0)
    {
        lua_pushvalue(L, tableIndex);
        CallOneFunction(number_of_functions, number_of_arguments + 1, 0);
        --number_of_functions;
    }

    // Read modified table back into list
    list.clear();
    lua_pushnil(L);
    while (lua_next(L, tableIndex) != 0)
    {
        if (T* obj = CHECKOBJ<T>(lua_gettop(L), false))
            list.push_back(obj);
        lua_pop(L, 1);
    }

    lua_pop(L, 1); // pop table
    CleanUpStack(number_of_arguments);
}

#endif // _HOOK_HELPERS_H
