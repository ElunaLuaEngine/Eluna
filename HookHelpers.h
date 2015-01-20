/*
 * Copyright (C) 2010 - 2015 Eluna Lua Engine <http://emudevs.com/>
 * This program is free software licensed under GPL version 3
 * Please see the included DOCS/LICENSE.md for more information
 */

#ifndef _HOOK_HELPERS_H
#define _HOOK_HELPERS_H

#include "LuaEngine.h"
#include "ElunaUtility.h"

/*
 * Sets up the stack so that event handlers can be called.
 *
 * Returns the number of functions that were pushed onto the stack.
 *
 * Use the simpler overloads for just EventBind or EntryBind instead of this overload in hooks.
 */
template<typename T>
int Eluna::SetupStack(EventBind<T>* event_bindings, EntryBind<T>* entry_bindings, UniqueBind<T>* guid_bindings, T event_id, uint32 entry, uint64 guid, uint32 instanceId, int number_of_arguments)
{
    // Ensure that if `entry_bindings` is not NULL, a valid entry is supplied.
    ASSERT(!entry_bindings || (entry_bindings && entry > 0));
    ASSERT(number_of_arguments == this->push_counter);
    // Stack: [arguments]

    Push(event_id);
    this->push_counter = 0;
    ++number_of_arguments;
    // Stack: [arguments], event_id

    int arguments_top = lua_gettop(L);
    int first_argument_index = arguments_top - number_of_arguments + 1;
    ASSERT(arguments_top >= number_of_arguments);

    lua_insert(L, first_argument_index);
    // Stack: event_id, [arguments]

    if (event_bindings)
        event_bindings->PushFuncRefs(L, (int)event_id);

    if (entry_bindings)
        entry_bindings->PushFuncRefs(L, (int)event_id, entry);

    if (guid_bindings)
        guid_bindings->PushFuncRefs(L, (int)event_id, guid, instanceId);
    // Stack: event_id, [arguments], [functions]

    int number_of_functions = lua_gettop(L) - arguments_top;
    return number_of_functions;
}

/*
 * Replace one of the arguments pushed before `SetupStack` with a new value.
 */
template<typename T>
void Eluna::ReplaceArgument(T value, uint8 index)
{
    ASSERT(index < lua_gettop(L) && index > 0);
    // Stack: event_id, [arguments], [functions], [results]

    Eluna::Push(L, value);
    // Stack: event_id, [arguments], [functions], [results], value

    lua_replace(L, index + 1);
    // Stack: event_id, [arguments and value], [functions], [results]
}

/*
 * Call all event handlers registered to the event ID/entry combination and ignore any results.
 */
template<typename T>
void Eluna::CallAllFunctions(EventBind<T>* event_bindings, EntryBind<T>* entry_bindings, UniqueBind<T>* guid_bindings, T event_id, uint32 entry, uint64 guid, uint32 instanceId)
{
    int number_of_arguments = this->push_counter;
    // Stack: [arguments]

    int number_of_functions = SetupStack(event_bindings, entry_bindings, guid_bindings, event_id, entry, guid, instanceId, number_of_arguments);
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
template<typename T>
bool Eluna::CallAllFunctionsBool(EventBind<T>* event_bindings, EntryBind<T>* entry_bindings, UniqueBind<T>* guid_bindings, T event_id, uint32 entry, uint64 guid, uint32 instanceId, bool default_value)
{
    bool result = default_value;
    // Note: number_of_arguments here does not count in eventID, which is pushed in SetupStack
    int number_of_arguments = this->push_counter;
    // Stack: [arguments]

    int number_of_functions = SetupStack(event_bindings, entry_bindings, guid_bindings, event_id, entry, guid, instanceId, number_of_arguments);
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

#endif // _HOOK_HELPERS_H
