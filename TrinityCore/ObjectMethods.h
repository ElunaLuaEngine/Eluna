/*
* Copyright (C) 2010 - 2024 Eluna Lua Engine <https://elunaluaengine.github.io/>
* This program is free software licensed under GPL version 3
* Please see the included DOCS/LICENSE.md for more information
*/

#ifndef OBJECTMETHODS_H
#define OBJECTMETHODS_H

/***
 * A basic game object (either an [Item] or a [WorldObject]).
 *
 * Objects in MaNGOS/Trinity are stored an a giant block of "values".
 * Subclasses of Object, like [WorldObject], extend the block with more data specific to that subclass.
 * Further subclasses, like [Player], extend it even further.
 *
 * A detailed map of all the fields in this data block can be found in the UpdateFields.h file of your emulator
 *   (it varies depending on the expansion supported).
 *
 * The GetValue methods in this class (e.g. [Object:GetInt32Value]) provide low-level access to the data block.
 * Other methods, like [Object:HasFlag] and [Object:GetScale], merely wrap the GetValue methods and provide a simpler interface.
 *
 * Inherits all methods from: none
 */
namespace LuaObject
{
    /**
     * Returns `true` if the specified flag is set, otherwise `false`.
     *
     * @param uint16 index : the index of the flags data in the [Object]
     * @param uint32 flag : the flag to check for in the flags data
     * @return bool hasFlag
     */
    int HasFlag(Eluna* E, Object* obj)
    {
        uint16 index = E->CHECKVAL<uint16>(2);
        uint32 flag = E->CHECKVAL<uint32>(3);

        E->Push(obj->HasFlag(index, flag));
        return 1;
    }

    /**
     * Returns `true` if the [Object] has been added to its [Map], otherwise `false`.
     *
     * @return bool inWorld
     */
    int IsInWorld(Eluna* E, Object* obj)
    {
        E->Push(obj->IsInWorld());
        return 1;
    }

    /**
     * Returns the data at the specified index, casted to a signed 32-bit integer.
     *
     * @param uint16 index
     * @return int32 value
     */
    int GetInt32Value(Eluna* E, Object* obj)
    {
        uint16 index = E->CHECKVAL<uint16>(2);
        E->Push(obj->GetInt32Value(index));
        return 1;
    }

    /**
     * Returns the data at the specified index, casted to a unsigned 32-bit integer.
     *
     * @param uint16 index
     * @return uint32 value
     */
    int GetUInt32Value(Eluna* E, Object* obj)
    {
        uint16 index = E->CHECKVAL<uint16>(2);
        E->Push(obj->GetUInt32Value(index));
        return 1;
    }

    /**
     * Returns the data at the specified index, casted to a single-precision floating point value.
     *
     * @param uint16 index
     * @return float value
     */
    int GetFloatValue(Eluna* E, Object* obj)
    {
        uint16 index = E->CHECKVAL<uint16>(2);
        E->Push(obj->GetFloatValue(index));
        return 1;
    }

    /**
     * Returns the data at the specified index and offset, casted to an unsigned 8-bit integer.
     *
     * E.g. if you want the second byte at index 10, you would pass in 1 as the offset.
     *
     * @param uint16 index
     * @param uint8 offset : should be 0, 1, 2, or 3
     * @return uint8 value
     */
    int GetByteValue(Eluna* E, Object* obj)
    {
        uint16 index = E->CHECKVAL<uint16>(2);
        uint8 offset = E->CHECKVAL<uint8>(3);
        E->Push(obj->GetByteValue(index, offset));
        return 1;
    }

    /**
     * Returns the data at the specified index and offset, casted to a signed 16-bit integer.
     *
     * E.g. if you want the second half-word at index 10, you would pass in 1 as the offset.
     *
     * @param uint16 index
     * @param uint8 offset : should be 0 or 1
     * @return uint16 value
     */
    int GetUInt16Value(Eluna* E, Object* obj)
    {
        uint16 index = E->CHECKVAL<uint16>(2);
        uint8 offset = E->CHECKVAL<uint8>(3);
        E->Push(obj->GetUInt16Value(index, offset));
        return 1;
    }

    /**
     * Returns the scale/size of the [Object].
     *
     * This affects the size of a [WorldObject] in-game, but [Item]s don't have a "scale".
     *
     * @return float scale
     */
    int GetScale(Eluna* E, Object* obj)
    {
        E->Push(obj->GetObjectScale());
        return 1;
    }

    /**
     * Returns the entry of the [Object].
     *
     * [Player]s do not have an "entry".
     *
     * @return uint32 entry
     */
    int GetEntry(Eluna* E, Object* obj)
    {
        E->Push(obj->GetEntry());
        return 1;
    }

    /**
     * Returns the GUID of the [Object].
     * 
     * GUID is an unique identifier for the object.
     * 
     * However on MaNGOS and cMangos creatures and gameobjects inside different maps can share
     * the same GUID but not on the same map.
     * 
     * On TrinityCore this value is unique across all maps
     * 
     * @return ObjectGuid guid
     */
    int GetGUID(Eluna* E, Object* obj)
    {
        E->Push(obj->GET_GUID());
        return 1;
    }

    /**
     * Returns the low-part of the [Object]'s GUID.
     * 
     * On TrinityCore all low GUIDs are different for all objects of the same type.
     * For example creatures in instances are assigned new GUIDs when the Map is created.
     * 
     * On MaNGOS and cMaNGOS low GUIDs are unique only on the same map.
     * For example creatures in instances use the same low GUID assigned for that spawn in the database.
     * This is why to identify a creature you have to know the instanceId and low GUID. See [Map:GetIntstanceId]
     *
     * @return uint32 guidLow
     */
    int GetGUIDLow(Eluna* E, Object* obj)
    {
        E->Push(obj->GetGUID().GetCounter());
        return 1;
    }

    /**
     * Returns the TypeId of the [Object].
     *
     *     enum TypeID
     *     {
     *         TYPEID_OBJECT        = 0,
     *         TYPEID_ITEM          = 1,
     *         TYPEID_CONTAINER     = 2,
     *         TYPEID_UNIT          = 3,
     *         TYPEID_PLAYER        = 4,
     *         TYPEID_GAMEOBJECT    = 5,
     *         TYPEID_DYNAMICOBJECT = 6,
     *         TYPEID_CORPSE        = 7
     *     };
     *
     * @return uint8 typeID
     */
    int GetTypeId(Eluna* E, Object* obj)
    {
        E->Push(obj->GetTypeId());
        return 1;
    }

    /**
     * Returns the data at the specified index, casted to an unsigned 64-bit integer.
     *
     * @param uint16 index
     * @return uint64 value
     */
    int GetUInt64Value(Eluna* E, Object* obj)
    {
        uint16 index = E->CHECKVAL<uint16>(2);
        E->Push(obj->GetUInt64Value(index));
        return 1;
    }

    /**
     * Sets the specified flag in the data value at the specified index.
     *
     * If the flag was already set, it remains set.
     *
     * To remove a flag, use [Object:RemoveFlag].
     *
     * @param uint16 index
     * @param uint32 value
     */
    int SetFlag(Eluna* E, Object* obj)
    {
        uint16 index = E->CHECKVAL<uint16>(2);
        uint32 flag = E->CHECKVAL<uint32>(3);

        obj->SetFlag(index, flag);
        return 0;
    }

    /**
     * Sets the data at the specified index to the given value, converted to a signed 32-bit integer.
     *
     * @param uint16 index
     * @param int32 value
     */
    int SetInt32Value(Eluna* E, Object* obj)
    {
        uint16 index = E->CHECKVAL<uint16>(2);
        int32 value = E->CHECKVAL<int32>(3);
        obj->SetInt32Value(index, value);
        return 0;
    }

    /**
     * Sets the data at the specified index to the given value, converted to an unsigned 32-bit integer.
     *
     * @param uint16 index
     * @param uint32 value
     */
    int SetUInt32Value(Eluna* E, Object* obj)
    {
        uint16 index = E->CHECKVAL<uint16>(2);
        uint32 value = E->CHECKVAL<uint32>(3);
        obj->SetUInt32Value(index, value);
        return 0;
    }

    /**
     * Sets the data at the specified index to the given value, converted to an unsigned 32-bit integer.
     *
     * @param uint16 index
     * @param uint32 value
     */
    int UpdateUInt32Value(Eluna* E, Object* obj)
    {
        uint16 index = E->CHECKVAL<uint16>(2);
        uint32 value = E->CHECKVAL<uint32>(3);
        obj->UpdateUInt32Value(index, value);
        return 0;
    }

    /**
     * Sets the data at the specified index to the given value, converted to a single-precision floating point value.
     *
     * @param uint16 index
     * @param float value
     */
    int SetFloatValue(Eluna* E, Object* obj)
    {
        uint16 index = E->CHECKVAL<uint16>(2);
        float value = E->CHECKVAL<float>(3);

        obj->SetFloatValue(index, value);
        return 0;
    }

    /**
     * Sets the data at the specified index and offset to the given value, converted to an unsigned 8-bit integer.
     *
     * @param uint16 index
     * @param uint8 offset : should be 0, 1, 2, or 3
     * @param uint8 value
     */
    int SetByteValue(Eluna* E, Object* obj)
    {
        uint16 index = E->CHECKVAL<uint16>(2);
        uint8 offset = E->CHECKVAL<uint8>(3);
        uint8 value = E->CHECKVAL<uint8>(4);
        obj->SetByteValue(index, offset, value);
        return 0;
    }

    /**
     * Sets the data at the specified index to the given value, converted to an unsigned 16-bit integer.
     *
     * @param uint16 index
     * @param uint8 offset : should be 0 or 1
     * @param uint16 value
     */
    int SetUInt16Value(Eluna* E, Object* obj)
    {
        uint16 index = E->CHECKVAL<uint16>(2);
        uint8 offset = E->CHECKVAL<uint8>(3);
        uint16 value = E->CHECKVAL<uint16>(4);
        obj->SetUInt16Value(index, offset, value);
        return 0;
    }

    /**
     * Sets the data at the specified index to the given value, converted to a signed 16-bit integer.
     *
     * @param uint16 index
     * @param uint8 offset : should be 0 or 1
     * @param int16 value
     */
    int SetInt16Value(Eluna* E, Object* obj)
    {
        uint16 index = E->CHECKVAL<uint16>(2);
        uint8 offset = E->CHECKVAL<uint8>(3);
        int16 value = E->CHECKVAL<int16>(4);
        obj->SetInt16Value(index, offset, value);
        return 0;
    }

    /**
     * Sets the [Object]'s scale/size to the given value.
     *
     * @param float scale
     */
    int SetScale(Eluna* E, Object* obj)
    {
        float size = E->CHECKVAL<float>(2);

        obj->SetObjectScale(size);
        return 0;
    }

    /**
     * Sets the data at the specified index to the given value, converted to an unsigned 64-bit integer.
     *
     * @param uint16 index
     * @param uint64 value
     */
    int SetUInt64Value(Eluna* E, Object* obj)
    {
        uint16 index = E->CHECKVAL<uint16>(2);
        uint64 value = E->CHECKVAL<uint64>(3);
        obj->SetUInt64Value(index, value);
        return 0;
    }

    /**
     * Removes a flag from the value at the specified index.
     *
     * @param uint16 index
     * @param uint32 flag
     */
    int RemoveFlag(Eluna* E, Object* obj)
    {
        uint16 index = E->CHECKVAL<uint16>(2);
        uint32 flag = E->CHECKVAL<uint32>(3);

        obj->RemoveFlag(index, flag);
        return 0;
    }

    /**
     * Attempts to convert the [Object] to a [Corpse].
     *
     * If the [Object] is not a [Corpse], returns `nil`.
     *
     * @return [Corpse] corpse : the [Object] as a [Corpse], or `nil`
     */
    int ToCorpse(Eluna* E, Object* obj)
    {
        E->Push(obj->ToCorpse());
        return 1;
    }

    /**
     * Attempts to convert the [Object] to a [GameObject].
     *
     * If the [Object] is not a [GameObject], returns `nil`.
     *
     * @return [GameObject] gameObject : the [Object] as a [GameObject], or `nil`
     */
    int ToGameObject(Eluna* E, Object* obj)
    {
        E->Push(obj->ToGameObject());
        return 1;
    }

    /**
     * Attempts to convert the [Object] to a [Unit].
     *
     * If the [Object] is not a [Unit], returns `nil`.
     *
     * @return [Unit] unit : the [Object] as a [Unit], or `nil`
     */
    int ToUnit(Eluna* E, Object* obj)
    {
        E->Push(obj->ToUnit());
        return 1;
    }

    /**
     * Attempts to convert the [Object] to a [Creature].
     *
     * If the [Object] is not a [Creature], returns `nil`.
     *
     * @return [Creature] creature : the [Object] as a [Creature], or `nil`
     */
    int ToCreature(Eluna* E, Object* obj)
    {
        E->Push(obj->ToCreature());
        return 1;
    }

    /**
     * Attempts to convert the [Object] to a [Player].
     *
     * If the [Object] is not a [Player], returns `nil`.
     *
     * @return [Player] player : the [Object] as a [Player], or `nil`
     */
    int ToPlayer(Eluna* E, Object* obj)
    {
        E->Push(obj->ToPlayer());
        return 1;
    }
    
    ElunaRegister<Object> ObjectMethods[] =
    {
        // Getters
        { "GetEntry", &LuaObject::GetEntry },
        { "GetGUID", &LuaObject::GetGUID },
        { "GetGUIDLow", &LuaObject::GetGUIDLow },
        { "GetInt32Value", &LuaObject::GetInt32Value },
        { "GetUInt32Value", &LuaObject::GetUInt32Value },
        { "GetFloatValue", &LuaObject::GetFloatValue },
        { "GetByteValue", &LuaObject::GetByteValue },
        { "GetUInt16Value", &LuaObject::GetUInt16Value },
        { "GetUInt64Value", &LuaObject::GetUInt64Value },
        { "GetScale", &LuaObject::GetScale },
        { "GetTypeId", &LuaObject::GetTypeId },

        // Setters
        { "SetInt32Value", &LuaObject::SetInt32Value },
        { "SetUInt32Value", &LuaObject::SetUInt32Value },
        { "UpdateUInt32Value", &LuaObject::UpdateUInt32Value },
        { "SetFloatValue", &LuaObject::SetFloatValue },
        { "SetByteValue", &LuaObject::SetByteValue },
        { "SetUInt16Value", &LuaObject::SetUInt16Value },
        { "SetInt16Value", &LuaObject::SetInt16Value },
        { "SetUInt64Value", &LuaObject::SetUInt64Value },
        { "SetScale", &LuaObject::SetScale },
        { "SetFlag", &LuaObject::SetFlag },

        // Boolean
        { "IsInWorld", &LuaObject::IsInWorld },
        { "HasFlag", &LuaObject::HasFlag },

        // Other
        { "ToGameObject", &LuaObject::ToGameObject },
        { "ToUnit", &LuaObject::ToUnit },
        { "ToCreature", &LuaObject::ToCreature },
        { "ToPlayer", &LuaObject::ToPlayer },
        { "ToCorpse", &LuaObject::ToCorpse },
        { "RemoveFlag", &LuaObject::RemoveFlag },

        { NULL, NULL, METHOD_REG_NONE }
    };
};
#endif
