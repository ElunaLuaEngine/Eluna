/*
* Copyright (C) 2010 - 2014 Eluna Lua Engine <http://emudevs.com/>
* This program is free software licensed under GPL version 3
* Please see the included DOCS/LICENSE.md for more information
*/

#ifndef QUERYMETHODS_H
#define QUERYMETHODS_H

#ifndef TRINITY
#define RESULT  result
#else
#define RESULT  (*result)
#endif
namespace LuaQuery
{
    void CheckFields(lua_State* L, ElunaQuery* result)
    {
        if (Eluna::CHECKVAL<uint32>(L, 2) >= RESULT->GetFieldCount())
            luaL_argerror(L, 2, "invalid field index");
    }

    /* BOOLEAN */
    int IsNull(lua_State* L, ElunaQuery* result)
    {
        uint32 col = Eluna::CHECKVAL<uint32>(L, 2);
        CheckFields(L, result);

#ifndef TRINITY
        Eluna::Push(L, RESULT->Fetch()[col].IsNULL());
#else
        Eluna::Push(L, RESULT->Fetch()[col].IsNull());
#endif
        return 1;
    }

    /* GETTERS */
    int GetColumnCount(lua_State* L, ElunaQuery* result)
    {
        Eluna::Push(L, RESULT->GetFieldCount());
        return 1;
    }

    int GetRowCount(lua_State* L, ElunaQuery* result)
    {
        if (RESULT->GetRowCount() > (uint32)-1)
            Eluna::Push(L, (uint32)-1);
        else
            Eluna::Push(L, RESULT->GetRowCount());
        return 1;
    }

    int GetBool(lua_State* L, ElunaQuery* result)
    {
        uint32 col = Eluna::CHECKVAL<uint32>(L, 2);
        CheckFields(L, result);
        Eluna::Push(L, RESULT->Fetch()[col].GetBool());
        return 1;
    }

    int GetUInt8(lua_State* L, ElunaQuery* result)
    {
        uint32 col = Eluna::CHECKVAL<uint32>(L, 2);
        CheckFields(L, result);
        Eluna::Push(L, RESULT->Fetch()[col].GetUInt8());
        return 1;
    }

    int GetUInt16(lua_State* L, ElunaQuery* result)
    {
        uint32 col = Eluna::CHECKVAL<uint32>(L, 2);
        CheckFields(L, result);
        Eluna::Push(L, RESULT->Fetch()[col].GetUInt16());
        return 1;
    }

    int GetUInt32(lua_State* L, ElunaQuery* result)
    {
        uint32 col = Eluna::CHECKVAL<uint32>(L, 2);
        CheckFields(L, result);
        Eluna::Push(L, RESULT->Fetch()[col].GetUInt32());
        return 1;
    }

    int GetUInt64(lua_State* L, ElunaQuery* result)
    {
        uint32 col = Eluna::CHECKVAL<uint32>(L, 2);
        CheckFields(L, result);
        Eluna::Push(L, RESULT->Fetch()[col].GetUInt64());
        return 1;
    }

    int GetInt8(lua_State* L, ElunaQuery* result)
    {
        uint32 col = Eluna::CHECKVAL<uint32>(L, 2);
        CheckFields(L, result);
        Eluna::Push(L, RESULT->Fetch()[col].GetInt8());
        return 1;
    }

    int GetInt16(lua_State* L, ElunaQuery* result)
    {
        uint32 col = Eluna::CHECKVAL<uint32>(L, 2);
        CheckFields(L, result);
        Eluna::Push(L, RESULT->Fetch()[col].GetInt16());
        return 1;
    }

    int GetInt32(lua_State* L, ElunaQuery* result)
    {
        uint32 col = Eluna::CHECKVAL<uint32>(L, 2);
        CheckFields(L, result);
        Eluna::Push(L, RESULT->Fetch()[col].GetInt32());
        return 1;
    }

    int GetInt64(lua_State* L, ElunaQuery* result)
    {
        uint32 col = Eluna::CHECKVAL<uint32>(L, 2);
        CheckFields(L, result);
        Eluna::Push(L, RESULT->Fetch()[col].GetInt64());
        return 1;
    }

    int GetFloat(lua_State* L, ElunaQuery* result)
    {
        uint32 col = Eluna::CHECKVAL<uint32>(L, 2);
        CheckFields(L, result);
        Eluna::Push(L, RESULT->Fetch()[col].GetFloat());
        return 1;
    }

    int GetDouble(lua_State* L, ElunaQuery* result)
    {
        uint32 col = Eluna::CHECKVAL<uint32>(L, 2);
        CheckFields(L, result);
        Eluna::Push(L, RESULT->Fetch()[col].GetDouble());
        return 1;
    }

    int GetString(lua_State* L, ElunaQuery* result)
    {
        uint32 col = Eluna::CHECKVAL<uint32>(L, 2);
        CheckFields(L, result);

#ifndef TRINITY
        Eluna::Push(L, RESULT->Fetch()[col].GetCppString());
#else
        Eluna::Push(L, RESULT->Fetch()[col].GetString());
#endif
        return 1;
    }

    int GetCString(lua_State* L, ElunaQuery* result)
    {
        uint32 col = Eluna::CHECKVAL<uint32>(L, 2);
        CheckFields(L, result);

#ifndef TRINITY
        Eluna::Push(L, RESULT->Fetch()[col].GetString());
#else
        Eluna::Push(L, RESULT->Fetch()[col].GetCString());
#endif
        return 1;
    }

    /* OTHER */

    /**
     * Advances the ElunaQuery to the next row in the result returned.
     * Returns false if there was no new row, otherwise true.
     *
     * @return bool hadNextRow
     */
    int NextRow(lua_State* L, ElunaQuery* result)
    {
        Eluna::Push(L, RESULT->NextRow());
        return 1;
    }

    /**
     * Returns a table from the current row where keys are field names and values are the row's values.
     * All numerical values will be numbers and everything else is returned as a string.
     * For example `SELECT entry, name FROM creature_template` would result in a table of `{ entry = 123, name = "some creature name" }`
     * To move to next row see [ElunaQuery:NextRow]
     *
     * @return table rowData : table filled with row columns and data where `T[column] = data`
     */
    int GetRow(lua_State* L, ElunaQuery* result)
    {
        lua_newtable(L);
        int tbl = lua_gettop(L);

        uint32 col = RESULT->GetFieldCount();
        Field* row = RESULT->Fetch();

#ifndef TRINITY
        const QueryFieldNames& names = RESULT->GetFieldNames();
#endif

        for (uint32 i = 0; i < col; ++i)
        {
#ifdef TRINITY
            Eluna::Push(L, RESULT->GetFieldName(i));

            const char* str = row[i].GetCString();
            if (row[i].IsNull() || !str)
                Eluna::Push(L);
#else
            Eluna::Push(L, names[i]);

            const char* str = row[i].GetString();
            if (row[i].IsNULL() || !str)
                Eluna::Push(L);
#endif
            else
            {
                // MYSQL_TYPE_LONGLONG Interpreted as string for lua
                switch (row[i].GetType())
                {
                    case MYSQL_TYPE_TINY:
                    case MYSQL_TYPE_SHORT:
                    case MYSQL_TYPE_INT24:
                    case MYSQL_TYPE_LONG:
                    case MYSQL_TYPE_FLOAT:
                    case MYSQL_TYPE_DOUBLE:
                        Eluna::Push(L, strtod(str, NULL));
                        break;
                    default:
                        Eluna::Push(L, str);
                        break;
                }
            }

            lua_settable(L, tbl);
        }

        lua_settop(L, tbl);
        return 1;
    }
};
#undef RESULT

#endif
