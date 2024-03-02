/*
 * Copyright (C) 2010 - 2024 Eluna Lua Engine <https://elunaluaengine.github.io/>
 * This program is free software licensed under GPL version 3
 * Please see the included DOCS/LICENSE.md for more information
 */

#include "ElunaInstanceAI.h"
#include "ElunaUtility.h"
#include "lmarshal.h"


#ifndef TRINITY
void ElunaInstanceAI::Initialize()
{
    ASSERT(!instance->GetEluna()->HasInstanceData(instance));

    // Create a new table for instance data.
    lua_State* L = instance->GetEluna()->L;
    lua_newtable(L);
    instance->GetEluna()->CreateInstanceData(instance);

    instance->GetEluna()->OnInitialize(this);
}
#endif

void ElunaInstanceAI::Load(const char* data)
{
    // If we get passed NULL (i.e. `Reload` was called) then use
    //   the last known save data (or maybe just an empty string).
    if (!data)
    {
        data = lastSaveData.c_str();
    }
    else // Otherwise, copy the new data into our buffer.
    {
        lastSaveData.assign(data);
    }

    if (data[0] == '\0')
    {
        ASSERT(!instance->GetEluna()->HasInstanceData(instance));

        // Create a new table for instance data.
        lua_State* L = instance->GetEluna()->L;
        lua_newtable(L);
        instance->GetEluna()->CreateInstanceData(instance);

        instance->GetEluna()->OnLoad(this);
        // Stack: (empty)
        return;
    }

    size_t decodedLength;
    const unsigned char* decodedData = ElunaUtil::DecodeData(data, &decodedLength);
    lua_State* L = instance->GetEluna()->L;

    if (decodedData)
    {
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
                instance->GetEluna()->CreateInstanceData(instance);
                // Stack: (empty)
                instance->GetEluna()->OnLoad(this);
                // WARNING! lastSaveData might be different after `OnLoad` if the Lua code saved data.
            }
            else
            {
                ELUNA_LOG_ERROR("Error while loading instance data: Expected data to be a table (type 5), got type %d instead", lua_type(L, -1));
                lua_pop(L, 1);
                // Stack: (empty)

#ifndef TRINITY
                Initialize();
#endif
            }
        }
        else
        {
            // Stack: error_message
            ELUNA_LOG_ERROR("Error while parsing instance data with lua-marshal: %s", lua_tostring(L, -1));
            lua_pop(L, 1);
            // Stack: (empty)

#ifndef TRINITY
            Initialize();
#endif
        }

        delete[] decodedData;
    }
    else
    {
        ELUNA_LOG_ERROR("Error while decoding instance data: Data is not valid base-64");

#ifndef TRINITY
        Initialize();
#endif
    }
}

const char* ElunaInstanceAI::Save() const
{
    lua_State* L = instance->GetEluna()->L;
    // Stack: (empty)

    /*
     * Need to cheat because this method actually does modify this instance,
     *   even though it's declared as `const`.
     *
     * Declaring virtual methods as `const` is BAD!
     * Don't dictate to children that their methods must be pure.
     */
    ElunaInstanceAI* self = const_cast<ElunaInstanceAI*>(this);

    lua_pushcfunction(L, mar_encode);
    instance->GetEluna()->PushInstanceData(self, false);
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
    ElunaUtil::EncodeData(data, dataLength, self->lastSaveData);

    lua_pop(L, 1);
    // Stack: (empty)

    return lastSaveData.c_str();
}

uint32 ElunaInstanceAI::GetData(uint32 key) const
{
    Eluna* E = instance->GetEluna();
    lua_State* L = E->L;
    // Stack: (empty)

    E->PushInstanceData(const_cast<ElunaInstanceAI*>(this), false);
    // Stack: instance_data

    E->Push(key);
    // Stack: instance_data, key

    lua_gettable(L, -2);
    // Stack: instance_data, value

    uint32 value = E->CHECKVAL<uint32>(-1, 0);
    lua_pop(L, 2);
    // Stack: (empty)

    return value;
}

void ElunaInstanceAI::SetData(uint32 key, uint32 value)
{
    Eluna* E = instance->GetEluna();
    lua_State* L = E->L;
    // Stack: (empty)

    E->PushInstanceData(this, false);
    // Stack: instance_data

    E->Push(key);
    E->Push(value);
    // Stack: instance_data, key, value

    lua_settable(L, -3);
    // Stack: instance_data

    lua_pop(L, 1);
    // Stack: (empty)
}

uint64 ElunaInstanceAI::GetData64(uint32 key) const
{
    Eluna* E = instance->GetEluna();
    lua_State* L = E->L;
    // Stack: (empty)

    E->PushInstanceData(const_cast<ElunaInstanceAI*>(this), false);
    // Stack: instance_data

    E->Push(key);
    // Stack: instance_data, key

    lua_gettable(L, -2);
    // Stack: instance_data, value

    uint64 value = E->CHECKVAL<uint64>(-1, 0);
    lua_pop(L, 2);
    // Stack: (empty)

    return value;
}

void ElunaInstanceAI::SetData64(uint32 key, uint64 value)
{
    Eluna* E = instance->GetEluna();
    lua_State* L = E->L;
    // Stack: (empty)

    E->PushInstanceData(this, false);
    // Stack: instance_data

    E->Push(key);
    E->Push(value);
    // Stack: instance_data, key, value

    lua_settable(L, -3);
    // Stack: instance_data

    lua_pop(L, 1);
    // Stack: (empty)
}
