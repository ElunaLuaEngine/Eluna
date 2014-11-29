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
    void CheckFields(Eluna* E, ElunaQuery* result)
    {
        if (Eluna::CHECKVAL<uint32>(E->L, 2) >= RESULT->GetFieldCount())
            luaL_argerror(E->L, 2, "invalid field index");
    }

    /* BOOLEAN */
    int IsNull(Eluna* E, ElunaQuery* result)
    {
        uint32 col = Eluna::CHECKVAL<uint32>(E->L, 2);
        CheckFields(E, result);

#ifndef TRINITY
        Eluna::Push(E->L, RESULT->Fetch()[col].IsNULL());
#else
        Eluna::Push(E->L, RESULT->Fetch()[col].IsNull());
#endif
        return 1;
    }

    /* GETTERS */
    int GetColumnCount(Eluna* E, ElunaQuery* result)
    {
        Eluna::Push(E->L, RESULT->GetFieldCount());
        return 1;
    }

    int GetRowCount(Eluna* E, ElunaQuery* result)
    {
        if (RESULT->GetRowCount() > (uint32)-1)
            Eluna::Push(E->L, (uint32)-1);
        else
            Eluna::Push(E->L, RESULT->GetRowCount());
        return 1;
    }

    int GetBool(Eluna* E, ElunaQuery* result)
    {
        uint32 col = Eluna::CHECKVAL<uint32>(E->L, 2);
        CheckFields(E, result);
        Eluna::Push(E->L, RESULT->Fetch()[col].GetBool());
        return 1;
    }

    int GetUInt8(Eluna* E, ElunaQuery* result)
    {
        uint32 col = Eluna::CHECKVAL<uint32>(E->L, 2);
        CheckFields(E, result);
        Eluna::Push(E->L, RESULT->Fetch()[col].GetUInt8());
        return 1;
    }

    int GetUInt16(Eluna* E, ElunaQuery* result)
    {
        uint32 col = Eluna::CHECKVAL<uint32>(E->L, 2);
        CheckFields(E, result);
        Eluna::Push(E->L, RESULT->Fetch()[col].GetUInt16());
        return 1;
    }

    int GetUInt32(Eluna* E, ElunaQuery* result)
    {
        uint32 col = Eluna::CHECKVAL<uint32>(E->L, 2);
        CheckFields(E, result);
        Eluna::Push(E->L, RESULT->Fetch()[col].GetUInt32());
        return 1;
    }

    int GetUInt64(Eluna* E, ElunaQuery* result)
    {
        uint32 col = Eluna::CHECKVAL<uint32>(E->L, 2);
        CheckFields(E, result);
        Eluna::Push(E->L, RESULT->Fetch()[col].GetUInt64());
        return 1;
    }

    int GetInt8(Eluna* E, ElunaQuery* result)
    {
        uint32 col = Eluna::CHECKVAL<uint32>(E->L, 2);
        CheckFields(E, result);
        Eluna::Push(E->L, RESULT->Fetch()[col].GetInt8());
        return 1;
    }

    int GetInt16(Eluna* E, ElunaQuery* result)
    {
        uint32 col = Eluna::CHECKVAL<uint32>(E->L, 2);
        CheckFields(E, result);
        Eluna::Push(E->L, RESULT->Fetch()[col].GetInt16());
        return 1;
    }

    int GetInt32(Eluna* E, ElunaQuery* result)
    {
        uint32 col = Eluna::CHECKVAL<uint32>(E->L, 2);
        CheckFields(E, result);
        Eluna::Push(E->L, RESULT->Fetch()[col].GetInt32());
        return 1;
    }

    int GetInt64(Eluna* E, ElunaQuery* result)
    {
        uint32 col = Eluna::CHECKVAL<uint32>(E->L, 2);
        CheckFields(E, result);
        Eluna::Push(E->L, RESULT->Fetch()[col].GetInt64());
        return 1;
    }

    int GetFloat(Eluna* E, ElunaQuery* result)
    {
        uint32 col = Eluna::CHECKVAL<uint32>(E->L, 2);
        CheckFields(E, result);
        Eluna::Push(E->L, RESULT->Fetch()[col].GetFloat());
        return 1;
    }

    int GetDouble(Eluna* E, ElunaQuery* result)
    {
        uint32 col = Eluna::CHECKVAL<uint32>(E->L, 2);
        CheckFields(E, result);
        Eluna::Push(E->L, RESULT->Fetch()[col].GetDouble());
        return 1;
    }

    int GetString(Eluna* E, ElunaQuery* result)
    {
        uint32 col = Eluna::CHECKVAL<uint32>(E->L, 2);
        CheckFields(E, result);

#ifndef TRINITY
        Eluna::Push(E->L, RESULT->Fetch()[col].GetCppString());
#else
        Eluna::Push(E->L, RESULT->Fetch()[col].GetString());
#endif
        return 1;
    }

    int GetCString(Eluna* E, ElunaQuery* result)
    {
        uint32 col = Eluna::CHECKVAL<uint32>(E->L, 2);
        CheckFields(E, result);

#ifndef TRINITY
        Eluna::Push(E->L, RESULT->Fetch()[col].GetString());
#else
        Eluna::Push(E->L, RESULT->Fetch()[col].GetCString());
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
    int NextRow(Eluna* E, ElunaQuery* result)
    {
        Eluna::Push(E->L, RESULT->NextRow());
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
    int GetRow(Eluna* E, ElunaQuery* result)
    {
        lua_newtable(E->L);
        int tbl = lua_gettop(E->L);

        uint32 col = RESULT->GetFieldCount();
        Field* row = RESULT->Fetch();

#ifndef TRINITY
        const QueryFieldNames& names = RESULT->GetFieldNames();
#endif

        for (uint32 i = 0; i < col; ++i)
        {
#ifdef TRINITY
            Eluna::Push(E->L, RESULT->GetFieldName(i));

            const char* str = row[i].GetCString();
            if (row[i].IsNull() || !str)
                Eluna::Push(E->L);
#else
            Eluna::Push(E->L, names[i]);

            const char* str = row[i].GetString();
            if (row[i].IsNULL() || !str)
                Eluna::Push(E->L);
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
                        Eluna::Push(E->L, strtod(str, NULL));
                        break;
                    default:
                        Eluna::Push(E->L, str);
                        break;
                }
            }

            lua_settable(E->L, tbl);
        }

        lua_settop(E->L, tbl);
        return 1;
    }
};
#undef RESULT

#endif
