/*
 * Copyright (C) 2010 - 2015 Eluna Lua Engine <http://emudevs.com/>
 * This program is free software licensed under GPL version 3
 * Please see the included DOCS/LICENSE.md for more information
 */

// TRINITY USERS: Do not compile this file!

#include "ElunaInstanceAI.h"
#include "ElunaUtility.h"
#include "lmarshal.h"


void ElunaInstanceAI::Initialize()
{
    LOCK_ELUNA;

    // We might have instance data if this method was called from `Load`.
    if (!sEluna->HasInstanceData(instance))
    {
        // Create a new table for instance data.
        lua_State* L = sEluna->L;
        lua_newtable(L);
        sEluna->CreateInstanceData(instance);
    }

    sEluna->OnInitialize(this);
}

void ElunaInstanceAI::Load(const char* data)
{
    LOCK_ELUNA;

#ifndef TRINITY
    // Trinity and MaNGOS based call the Initialize differently.
    // On MaNGOS based Initialize is called when loading is not called
    // On Trinity Initialize is called when the instance script is generated no matter if loading happens
    // Calling initialize before loading on mangos makes initialize called in any case on both cores.
    Initialize();
#endif

    // If we get passed NULL (i.e. `Reload` was called) then use
    //   the last known save data (or maybe just an empty string).
    if (!data)
    {
        data = lastSaveData;
    }
    else // Otherwise, copy the new data into our buffer.
    {
        strcpy(lastSaveData, data);
    }

    // Don't bother trying to decode an empty string.
    if (data[0] != '\0')
    {
        size_t decodedLength;
        const unsigned char* decodedData = ElunaUtil::DecodeData(data, &decodedLength);

        if (decodedData)
        {
            lua_State* L = sEluna->L;
            // Stack: (empty)

            lua_pushcfunction(L, mar_decode);
            lua_pushlstring(L, (const char*)decodedData, decodedLength);
            // Stack: mar_decode, decoded_data

            // Call `mar_decode` and check for success.
            if (lua_pcall(L, 1, 1, 0) == 0)
            {
                // Stack: data
                // Only use the data if it's a table.
                if (lua_istable(L, -1))
                {
                    sEluna->CreateInstanceData(instance);
                    // Stack: (empty)
                    sEluna->OnLoad(this);
                }
                else
                {
                    lua_pop(L, 1);
                    // Stack: (empty)
                }
            }
            else
            {
                // Stack: error_message
                ELUNA_LOG_ERROR("Error while loading: %s", lua_tostring(L, -1));
                lua_pop(L, 1);
                // Stack: (empty)
            }

            free((void*)decodedData);
        }
    }
}

const char* ElunaInstanceAI::Save() const
{
    LOCK_ELUNA;
    lua_State* L = sEluna->L;
    // Stack: (empty)

    /*
     * Need to cheat because this method actually does modify this instance,
     *   even though it's declared as `const`.
     *
     * Declaring virtual methods as `const` is BAD!
     * Don't dictate to children that their method must be pure.
     */
    ElunaInstanceAI* self = const_cast<ElunaInstanceAI*>(this);

    lua_pushcfunction(L, mar_encode);
    sEluna->PushInstanceData(self, false);
    // Stack: mar_encode, instance_data

    if (lua_pcall(L, 1, 1, 0) != 0)
    {
        // Stack: error_message
        ELUNA_LOG_ERROR("Error while saving: %s", lua_tostring(L, -1));
        lua_pop(L, 1);
        return NULL;
    }

    // Stack: data
    size_t dataLength;
    const unsigned char* data = (const unsigned char*)lua_tolstring(L, -1, &dataLength);
    ElunaUtil::EncodeData(data, dataLength, self->lastSaveData, MAX_SAVE_DATA);

    lua_pop(L, 1);
    // Stack: (empty)

    return lastSaveData;
}

uint32 ElunaInstanceAI::GetData(uint32 key) const
{
    LOCK_ELUNA;
    lua_State* L = sEluna->L;
    // Stack: (empty)

    sEluna->PushInstanceData(const_cast<ElunaInstanceAI*>(this), false);
    // Stack: instance_data

    Eluna::Push(L, key);
    // Stack: instance_data, key

    lua_gettable(L, -2);
    // Stack: instance_data, value

    uint32 value = Eluna::CHECKVAL<uint32>(L, -1, 0);
    lua_pop(L, 2);
    // Stack: (empty)

    return value;
}

void ElunaInstanceAI::SetData(uint32 key, uint32 value)
{
    LOCK_ELUNA;
    lua_State* L = sEluna->L;
    // Stack: (empty)

    sEluna->PushInstanceData(this, false);
    // Stack: instance_data

    Eluna::Push(L, key);
    Eluna::Push(L, value);
    // Stack: instance_data, key, value

    lua_settable(L, -3);
    // Stack: instance_data

    lua_pop(L, 1);
    // Stack: (empty)
}

uint64 ElunaInstanceAI::GetData64(uint32 key) const
{
    LOCK_ELUNA;
    lua_State* L = sEluna->L;
    // Stack: (empty)

    sEluna->PushInstanceData(const_cast<ElunaInstanceAI*>(this), false);
    // Stack: instance_data

    Eluna::Push(L, key);
    // Stack: instance_data, key

    lua_gettable(L, -2);
    // Stack: instance_data, value

    uint64 value = Eluna::CHECKVAL<uint64>(L, -1, 0);
    lua_pop(L, 2);
    // Stack: (empty)

    return value;
}

void ElunaInstanceAI::SetData64(uint32 key, uint64 value)
{
    LOCK_ELUNA;
    lua_State* L = sEluna->L;
    // Stack: (empty)

    sEluna->PushInstanceData(this, false);
    // Stack: instance_data

    Eluna::Push(L, key);
    Eluna::Push(L, value);
    // Stack: instance_data, key, value

    lua_settable(L, -3);
    // Stack: instance_data

    lua_pop(L, 1);
    // Stack: (empty)
}
