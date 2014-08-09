/*
* Copyright (C) 2010 - 2014 Eluna Lua Engine <http://emudevs.com/>
* This program is free software licensed under GPL version 3
* Please see the included DOCS/LICENSE.md for more information
*/

#ifndef WORLDPACKETMETHODS_H
#define WORLDPACKETMETHODS_H

namespace LuaPacket
{
    /**
     * Returns the opcode of the &WorldPacket.
     *
     * @return uint16 opcode
     */
    int GetOpcode(lua_State* L, WorldPacket* packet)
    {
        Eluna::Push(L, packet->GetOpcode());
        return 1;
    }

    /**
     * Returns the size of the &WorldPacket.
     *
     * @return uint32 : size of &WorldPacket
     */
    int GetSize(lua_State* L, WorldPacket* packet)
    {
        Eluna::Push(L, packet->size());
        return 1;
    }

    /**
     * Sets the opcode of the &WorldPacket by specifying an opcode.
     *
     * @param uint32 packet : the packet specified to be set for the &WorldPacket
     */
    int SetOpcode(lua_State* L, WorldPacket* packet)
    {
        uint32 opcode = Eluna::CHECKVAL<uint32>(L, 2);
        if (opcode >= NUM_MSG_TYPES)
            return luaL_argerror(L, 2, "valid opcode expected");
        packet->SetOpcode((OpcodesList)opcode);
        return 0;
    }

    /**
     * Reads an int8 value of the &WorldPacket specified.
     *
     * @return int8
     */
    int ReadByte(lua_State* L, WorldPacket* packet)
    {
        int8 byte;
        (*packet) >> byte;
        Eluna::Push(L, byte);
        return 1;
    }

    /**
     * Reads a uint8 value of the &WorldPacket specified.
     *
     * @return uint8
     */
    int ReadUByte(lua_State* L, WorldPacket* packet)
    {
        uint8 byte;
        (*packet) >> byte;
        Eluna::Push(L, byte);
        return 1;
    }

    /**
     * Reads an int16 value of the &WorldPacket specified.
     *
     * @return int16
     */
    int ReadShort(lua_State* L, WorldPacket* packet)
    {
        int16 _short;
        (*packet) >> _short;
        Eluna::Push(L, _short);
        return 1;
    }

    /**
     * Reads a uint16 value of the &WorldPacket specified.
     *
     * @return uint16
     */
    int ReadUShort(lua_State* L, WorldPacket* packet)
    {
        uint16 _ushort;
        (*packet) >> _ushort;
        Eluna::Push(L, _ushort);
        return 1;
    }

    /**
     * Reads an int32 value of the &WorldPacket specified.
     *
     * @return int32
     */
    int ReadLong(lua_State* L, WorldPacket* packet)
    {
        int32 _long;
        (*packet) >> _long;
        Eluna::Push(L, _long);
        return 1;
    }

    /**
     * Reads a uint32 value of the &WorldPacket specified.
     *
     * @return uint32
     */
    int ReadULong(lua_State* L, WorldPacket* packet)
    {
        uint32 _ulong;
        (*packet) >> _ulong;
        Eluna::Push(L, _ulong);
        return 1;
    }

    /**
     * Reads a float value of the &WorldPacket specified.
     *
     * @return float
     */
    int ReadFloat(lua_State* L, WorldPacket* packet)
    {
        float _val;
        (*packet) >> _val;
        Eluna::Push(L, _val);
        return 1;
    }

    /**
     * Reads a double value of the &WorldPacket specified.
     *
     * @return double
     */
    int ReadDouble(lua_State* L, WorldPacket* packet)
    {
        double _val;
        (*packet) >> _val;
        Eluna::Push(L, _val);
        return 1;
    }

    /**
     * Reads a uint64 GUID value of the &WorldPacket specified.
     *
     * @return uint64 : GUID returned as uint64
     */
    int ReadGUID(lua_State* L, WorldPacket* packet)
    {
        uint64 guid;
        (*packet) >> guid;
        Eluna::Push(L, guid);
        return 1;
    }

    /**
     * Reads a string value of the &WorldPacket specified.
     *
     * @return string
     */
    int ReadString(lua_State* L, WorldPacket* packet)
    {
        std::string _val;
        (*packet) >> _val;
        Eluna::Push(L, _val);
        return 1;
    }

    /**
     * Writes a uint64 GUID to the &WorldPacket.
     *
     * @param uint64 GUID : the GUID to be written to the &WorldPacket
     */
    int WriteGUID(lua_State* L, WorldPacket* packet)
    {
        uint64 guid = Eluna::CHECKVAL<uint64>(L, 2);
        (*packet) << guid;
        return 0;
    }

    /**
     * Writes a string to the &WorldPacket.
     *
     * @param string : the string to be written to the &WorldPacket
     */
    int WriteString(lua_State* L, WorldPacket* packet)
    {
        std::string _val = Eluna::CHECKVAL<std::string>(L, 2);
        (*packet) << _val;
        return 0;
    }

    /**
     * Writes an int8 value to the &WorldPacket.
     *
     * @param int8 value : the int8 value to be written to the &WorldPacket
     */
    int WriteByte(lua_State* L, WorldPacket* packet)
    {
        int8 byte = Eluna::CHECKVAL<int8>(L, 2);
        (*packet) << byte;
        return 0;
    }

    /**
     * Writes a uint8 value to the &WorldPacket.
     *
     * @param uint8 value : the uint8 value to be written to the &WorldPacket
     */
    int WriteUByte(lua_State* L, WorldPacket* packet)
    {
        uint8 byte = Eluna::CHECKVAL<uint8>(L, 2);
        (*packet) << byte;
        return 0;
    }

    /**
     * Writes an int16 value to the &WorldPacket.
     *
     * @param int16 value : the int16 value to be written to the &WorldPacket
     */
    int WriteShort(lua_State* L, WorldPacket* packet)
    {
        int16 _short = Eluna::CHECKVAL<int16>(L, 2);
        (*packet) << _short;
        return 0;
    }

    /**
     * Writes a uint16 value to the &WorldPacket.
     *
     * @param uint16 value : the uint16 value to be written to the &WorldPacket
     */
    int WriteUShort(lua_State* L, WorldPacket* packet)
    {
        uint16 _ushort = Eluna::CHECKVAL<uint16>(L, 2);
        (*packet) << _ushort;
        return 0;
    }

    /**
     * Writes an int32 value to the &WorldPacket.
     *
     * @param int32 value : the int32 value to be written to the &WorldPacket
     */
    int WriteLong(lua_State* L, WorldPacket* packet)
    {
        int32 _long = Eluna::CHECKVAL<int32>(L, 2);
        (*packet) << _long;
        return 0;
    }

    /**
     * Writes a uint32 value to the &WorldPacket.
     *
     * @param uint32 value : the uint32 value to be written to the &WorldPacket
     */
    int WriteULong(lua_State* L, WorldPacket* packet)
    {
        uint32 _ulong = Eluna::CHECKVAL<uint32>(L, 2);
        (*packet) << _ulong;
        return 0;
    }

    /**
     * Writes a float value to the &WorldPacket.
     *
     * @param float value : the float value to be written to the &WorldPacket
     */
    int WriteFloat(lua_State* L, WorldPacket* packet)
    {
        float _val = Eluna::CHECKVAL<float>(L, 2);
        (*packet) << _val;
        return 0;
    }

    /**
     * Writes a double value to the &WorldPacket.
     *
     * @param double value : the double value to be written to the &WorldPacket
     */
    int WriteDouble(lua_State* L, WorldPacket* packet)
    {
        double _val = Eluna::CHECKVAL<double>(L, 2);
        (*packet) << _val;
        return 0;
    }
};

#endif
