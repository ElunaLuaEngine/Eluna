/*
* Copyright (C) 2010 - 2014 Eluna Lua Engine <http://emudevs.com/>
* This program is free software licensed under GPL version 3
* Please see the included DOCS/LICENSE.md for more information
*/

#ifndef OBJECTMETHODS_H
#define OBJECTMETHODS_H

namespace LuaObject
{
    /* BOOLEAN */
    int HasFlag(Eluna* /*E*/, lua_State* L, Object* obj)
    {
        uint16 index = Eluna::CHECKVAL<uint16>(L, 2);
        uint32 flag = Eluna::CHECKVAL<uint32>(L, 3);

        Eluna::Push(L, obj->HasFlag(index, flag));
        return 1;
    }

    int IsInWorld(Eluna* /*E*/, lua_State* L, Object* obj)
    {
        Eluna::Push(L, obj->IsInWorld());
        return 1;
    }

    /* GETTERS */
    int GetInt32Value(Eluna* /*E*/, lua_State* L, Object* obj)
    {
        uint16 index = Eluna::CHECKVAL<uint16>(L, 2);
        Eluna::Push(L, obj->GetInt32Value(index));
        return 1;
    }

    int GetUInt32Value(Eluna* /*E*/, lua_State* L, Object* obj)
    {
        uint16 index = Eluna::CHECKVAL<uint16>(L, 2);
        Eluna::Push(L, obj->GetUInt32Value(index));
        return 1;
    }

    int GetFloatValue(Eluna* /*E*/, lua_State* L, Object* obj)
    {
        uint16 index = Eluna::CHECKVAL<uint16>(L, 2);
        Eluna::Push(L, obj->GetFloatValue(index));
        return 1;
    }

    int GetByteValue(Eluna* /*E*/, lua_State* L, Object* obj)
    {
        uint16 index = Eluna::CHECKVAL<uint16>(L, 2);
        uint8 offset = Eluna::CHECKVAL<uint8>(L, 3);
        Eluna::Push(L, obj->GetByteValue(index, offset));
        return 1;
    }

    int GetUInt16Value(Eluna* /*E*/, lua_State* L, Object* obj)
    {
        uint16 index = Eluna::CHECKVAL<uint16>(L, 2);
        uint8 offset = Eluna::CHECKVAL<uint8>(L, 3);
        Eluna::Push(L, obj->GetUInt16Value(index, offset));
        return 1;
    }

    int GetScale(Eluna* /*E*/, lua_State* L, Object* obj)
    {
        Eluna::Push(L, obj->GetObjectScale());
        return 1;
    }

    int GetEntry(Eluna* /*E*/, lua_State* L, Object* obj)
    {
        Eluna::Push(L, obj->GetEntry());
        return 1;
    }

    int GetGUID(Eluna* /*E*/, lua_State* L, Object* obj)
    {
        Eluna::Push(L, obj->GET_GUID());
        return 1;
    }

    int GetGUIDLow(Eluna* /*E*/, lua_State* L, Object* obj)
    {
        Eluna::Push(L, obj->GetGUIDLow());
        return 1;
    }

    int GetTypeId(Eluna* /*E*/, lua_State* L, Object* obj)
    {
        Eluna::Push(L, obj->GetTypeId());
        return 1;
    }

    int GetUInt64Value(Eluna* /*E*/, lua_State* L, Object* obj)
    {
        uint16 index = Eluna::CHECKVAL<uint16>(L, 2);
        obj->GetUInt64Value(index);
        return 0;
    }

    /* SETTERS */
    int SetFlag(Eluna* /*E*/, lua_State* L, Object* obj)
    {
        uint16 index = Eluna::CHECKVAL<uint16>(L, 2);
        uint32 flag = Eluna::CHECKVAL<uint32>(L, 3);

        obj->SetFlag(index, flag);
        return 0;
    }

    int SetInt32Value(Eluna* /*E*/, lua_State* L, Object* obj)
    {
        uint16 index = Eluna::CHECKVAL<uint16>(L, 2);
        int32 value = Eluna::CHECKVAL<int32>(L, 3);
        obj->SetInt32Value(index, value);
        return 0;
    }

    int SetUInt32Value(Eluna* /*E*/, lua_State* L, Object* obj)
    {
        uint16 index = Eluna::CHECKVAL<uint16>(L, 2);
        uint32 value = Eluna::CHECKVAL<uint32>(L, 3);
        obj->SetUInt32Value(index, value);
        return 0;
    }

    int SetFloatValue(Eluna* /*E*/, lua_State* L, Object* obj)
    {
        uint16 index = Eluna::CHECKVAL<uint16>(L, 2);
        float value = Eluna::CHECKVAL<float>(L, 3);

        obj->SetFloatValue(index, value);
        return 0;
    }

    int SetByteValue(Eluna* /*E*/, lua_State* L, Object* obj)
    {
        uint16 index = Eluna::CHECKVAL<uint16>(L, 2);
        uint8 offset = Eluna::CHECKVAL<uint8>(L, 3);
        uint8 value = Eluna::CHECKVAL<uint8>(L, 4);
        obj->SetByteValue(index, offset, value);
        return 0;
    }

    int SetUInt16Value(Eluna* /*E*/, lua_State* L, Object* obj)
    {
        uint16 index = Eluna::CHECKVAL<uint16>(L, 2);
        uint8 offset = Eluna::CHECKVAL<uint8>(L, 3);
        uint16 value = Eluna::CHECKVAL<uint16>(L, 4);
        obj->SetUInt16Value(index, offset, value);
        return 0;
    }

    int SetInt16Value(Eluna* /*E*/, lua_State* L, Object* obj)
    {
        uint16 index = Eluna::CHECKVAL<uint16>(L, 2);
        uint8 offset = Eluna::CHECKVAL<uint8>(L, 3);
        int16 value = Eluna::CHECKVAL<int16>(L, 4);
        obj->SetInt16Value(index, offset, value);
        return 0;
    }

    int SetScale(Eluna* /*E*/, lua_State* L, Object* obj)
    {
        float size = Eluna::CHECKVAL<float>(L, 2);

        obj->SetObjectScale(size);
        return 0;
    }

    int SetUInt64Value(Eluna* /*E*/, lua_State* L, Object* obj)
    {
        uint16 index = Eluna::CHECKVAL<uint16>(L, 2);
        uint64 value = Eluna::CHECKVAL<uint64>(L, 3);
        obj->SetUInt64Value(index, value);
        return 0;
    }

    /* OTHER */
    int RemoveFlag(Eluna* /*E*/, lua_State* L, Object* obj)
    {
        uint16 index = Eluna::CHECKVAL<uint16>(L, 2);
        uint32 flag = Eluna::CHECKVAL<uint32>(L, 3);

        obj->RemoveFlag(index, flag);
        return 0;
    }

    int UpdateUInt32Value(Eluna* /*E*/, lua_State* L, Object* obj)
    {
        uint16 index = Eluna::CHECKVAL<uint16>(L, 2);
        uint32 value = Eluna::CHECKVAL<uint32>(L, 3);
        obj->UpdateUInt32Value(index, value);
        return 0;
    }

    int ToCorpse(Eluna* /*E*/, lua_State* L, Object* obj)
    {
        Eluna::Push(L, obj->ToCorpse());
        return 1;
    }

    int ToGameObject(Eluna* /*E*/, lua_State* L, Object* obj)
    {
        Eluna::Push(L, obj->ToGameObject());
        return 1;
    }

    int ToUnit(Eluna* /*E*/, lua_State* L, Object* obj)
    {
        Eluna::Push(L, obj->ToUnit());
        return 1;
    }

    int ToCreature(Eluna* /*E*/, lua_State* L, Object* obj)
    {
        Eluna::Push(L, obj->ToCreature());
        return 1;
    }

    int ToPlayer(Eluna* /*E*/, lua_State* L, Object* obj)
    {
        Eluna::Push(L, obj->ToPlayer());
        return 1;
    }
};
#endif
