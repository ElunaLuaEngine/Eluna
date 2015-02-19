/*
 * Copyright (C) 2010 - 2015 Eluna Lua Engine <http://emudevs.com/>
 * This program is free software licensed under GPL version 3
 * Please see the included DOCS/LICENSE.md for more information
 */


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

    if (!data)
        data = lastSaveData;
    else
        strcpy(lastSaveData, data);

    if (strlen(data) > 0)
    {
        size_t decodedLength;
        const unsigned char* decodedData = ElunaUtil::DecodeData(data, &decodedLength);

        if (decodedData)
        {
            lua_State* L = sEluna->L;
            lua_pushcfunction(L, mar_decode);
            lua_pushlstring(L, (const char*)decodedData, decodedLength);

            // Call `mar_decode` and check for success.
            if (lua_pcall(L, 1, 1, 0) == 0)
            {
                // Only use the data if it's a table.
                if (lua_istable(L, -1))
                {
                    sEluna->CreateInstanceData(instance);
                    sEluna->OnLoad(this);
                }
                else
                    lua_pop(L, 1);
            }
            else
                lua_pop(L, 1);

            free((void*)decodedData);
        }
    }

    Initialize();
}

const char* ElunaInstanceAI::Save() const
{
    LOCK_ELUNA;
    lua_State* L = sEluna->L;
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

    if (lua_pcall(L, 1, 1, 0) != 0)
    {
        sLog.outBasic("Error while saving: %s", lua_tostring(L, -1));
        lua_pop(L, 1);
        return NULL;
    }

    size_t dataLength;
    const unsigned char* data = (const unsigned char*)lua_tolstring(L, -1, &dataLength);
    ElunaUtil::EncodeData(data, dataLength, self->lastSaveData, MAX_SAVE_DATA);

    lua_pop(L, 1);
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
