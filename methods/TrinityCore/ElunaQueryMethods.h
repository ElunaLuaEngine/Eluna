/*
* Copyright (C) 2010 - 2024 Eluna Lua Engine <https://elunaluaengine.github.io/>
* This program is free software licensed under GPL version 3
* Please see the included DOCS/LICENSE.md for more information
*/

#ifndef QUERYMETHODS_H
#define QUERYMETHODS_H

#define RESULT  (*result)

/***
 * The result of a database query.
 *
 * E.g. the return value of [Global:WorldDBQuery].
 *
 * Inherits all methods from: none
 */
namespace LuaQuery
{
    static void CheckFields(Eluna* E, ElunaQuery* result)
    {
        uint32 field = E->CHECKVAL<uint32>(2);
        uint32 count = RESULT->GetFieldCount();
        if (field >= count)
        {
            char arr[256];
            sprintf(arr, "trying to access invalid field index %u. There are %u fields available and the indexes start from 0", field, count);
            luaL_argerror(E->L, 2, arr);
        }
    }

    /**
     * Returns `true` if the specified column of the current row is `NULL`, otherwise `false`.
     *
     * @param uint32 column
     * @return bool isNull
     */
    int IsNull(Eluna* E, ElunaQuery* result)
    {
        uint32 col = E->CHECKVAL<uint32>(2);
        CheckFields(E, result);

        E->Push(RESULT->Fetch()[col].IsNull());
        return 1;
    }

    /**
     * Returns the number of columns in the result set.
     *
     * @return uint32 columnCount
     */
    int GetColumnCount(Eluna* E, ElunaQuery* result)
    {
        E->Push(RESULT->GetFieldCount());
        return 1;
    }

    /**
     * Returns the number of rows in the result set.
     *
     * @return uint32 rowCount
     */
    int GetRowCount(Eluna* E, ElunaQuery* result)
    {
        if (RESULT->GetRowCount() > (uint32)-1)
            E->Push((uint32)-1);
        else
            E->Push((uint32)(RESULT->GetRowCount()));
        return 1;
    }

    /**
     * Returns the data in the specified column of the current row, casted to a boolean.
     *
     * @param uint32 column
     * @return bool data
     */
    int GetBool(Eluna* E, ElunaQuery* result)
    {
        uint32 col = E->CHECKVAL<uint32>(2);
        CheckFields(E, result);
        E->Push(RESULT->Fetch()[col].GetBool());
        return 1;
    }

    /**
     * Returns the data in the specified column of the current row, casted to an unsigned 8-bit integer.
     *
     * @param uint32 column
     * @return uint8 data
     */
    int GetUInt8(Eluna* E, ElunaQuery* result)
    {
        uint32 col = E->CHECKVAL<uint32>(2);
        CheckFields(E, result);
        E->Push(RESULT->Fetch()[col].GetUInt8());
        return 1;
    }

    /**
     * Returns the data in the specified column of the current row, casted to an unsigned 16-bit integer.
     *
     * @param uint32 column
     * @return uint16 data
     */
    int GetUInt16(Eluna* E, ElunaQuery* result)
    {
        uint32 col = E->CHECKVAL<uint32>(2);
        CheckFields(E, result);
        E->Push(RESULT->Fetch()[col].GetUInt16());
        return 1;
    }

    /**
     * Returns the data in the specified column of the current row, casted to an unsigned 32-bit integer.
     *
     * @param uint32 column
     * @return uint32 data
     */
    int GetUInt32(Eluna* E, ElunaQuery* result)
    {
        uint32 col = E->CHECKVAL<uint32>(2);
        CheckFields(E, result);
        E->Push(RESULT->Fetch()[col].GetUInt32());
        return 1;
    }

    /**
     * Returns the data in the specified column of the current row, casted to an unsigned 64-bit integer.
     *
     * @param uint32 column
     * @return uint64 data
     */
    int GetUInt64(Eluna* E, ElunaQuery* result)
    {
        uint32 col = E->CHECKVAL<uint32>(2);
        CheckFields(E, result);
        E->Push(RESULT->Fetch()[col].GetUInt64());
        return 1;
    }

    /**
     * Returns the data in the specified column of the current row, casted to a signed 8-bit integer.
     *
     * @param uint32 column
     * @return int8 data
     */
    int GetInt8(Eluna* E, ElunaQuery* result)
    {
        uint32 col = E->CHECKVAL<uint32>(2);
        CheckFields(E, result);
        E->Push(RESULT->Fetch()[col].GetInt8());
        return 1;
    }

    /**
     * Returns the data in the specified column of the current row, casted to a signed 16-bit integer.
     *
     * @param uint32 column
     * @return int16 data
     */
    int GetInt16(Eluna* E, ElunaQuery* result)
    {
        uint32 col = E->CHECKVAL<uint32>(2);
        CheckFields(E, result);
        E->Push(RESULT->Fetch()[col].GetInt16());
        return 1;
    }

    /**
     * Returns the data in the specified column of the current row, casted to a signed 32-bit integer.
     *
     * @param uint32 column
     * @return int32 data
     */
    int GetInt32(Eluna* E, ElunaQuery* result)
    {
        uint32 col = E->CHECKVAL<uint32>(2);
        CheckFields(E, result);
        E->Push(RESULT->Fetch()[col].GetInt32());
        return 1;
    }

    /**
     * Returns the data in the specified column of the current row, casted to a signed 64-bit integer.
     *
     * @param uint32 column
     * @return int64 data
     */
    int GetInt64(Eluna* E, ElunaQuery* result)
    {
        uint32 col = E->CHECKVAL<uint32>(2);
        CheckFields(E, result);
        E->Push(RESULT->Fetch()[col].GetInt64());
        return 1;
    }

    /**
     * Returns the data in the specified column of the current row, casted to a 32-bit floating point value.
     *
     * @param uint32 column
     * @return float data
     */
    int GetFloat(Eluna* E, ElunaQuery* result)
    {
        uint32 col = E->CHECKVAL<uint32>(2);
        CheckFields(E, result);
        E->Push(RESULT->Fetch()[col].GetFloat());
        return 1;
    }

    /**
     * Returns the data in the specified column of the current row, casted to a 64-bit floating point value.
     *
     * @param uint32 column
     * @return double data
     */
    int GetDouble(Eluna* E, ElunaQuery* result)
    {
        uint32 col = E->CHECKVAL<uint32>(2);
        CheckFields(E, result);
        E->Push(RESULT->Fetch()[col].GetDouble());
        return 1;
    }

    /**
     * Returns the data in the specified column of the current row, casted to a string.
     *
     * @param uint32 column
     * @return string data
     */
    int GetString(Eluna* E, ElunaQuery* result)
    {
        uint32 col = E->CHECKVAL<uint32>(2);
        CheckFields(E, result);

        E->Push(RESULT->Fetch()[col].GetCString());
        return 1;
    }

    /**
     * Advances the [ElunaQuery] to the next row in the result set.
     *
     * *Do not* call this immediately after a query, or you'll skip the first row.
     *
     * Returns `false` if there was no new row, otherwise `true`.
     *
     * @return bool hadNextRow
     */
    int NextRow(Eluna* E, ElunaQuery* result)
    {
        E->Push(RESULT->NextRow());
        return 1;
    }

    /**
     * Returns a table from the current row where keys are field names and values are the row's values.
     *
     * All numerical values will be numbers and everything else is returned as a string.
     *
     * **For example,** the query:
     *
     *     SELECT entry, name FROM creature_template
     *
     * would result in a table like:
     *
     *     { entry = 123, name = "some creature name" }
     *
     * To move to next row use [ElunaQuery:NextRow].
     *
     * @return table rowData : table filled with row columns and data where `T[column] = data`
     */
    int GetRow(Eluna* E, ElunaQuery* result)
    {
        uint32 col = RESULT->GetFieldCount();
        Field* row = RESULT->Fetch();

        lua_createtable(E->L, 0, col);
        int tbl = lua_gettop(E->L);

        for (uint32 i = 0; i < col; ++i)
        {
            QueryResultFieldMetadata const& fieldMetadata = RESULT->GetFieldMetadata(i);

            E->Push(fieldMetadata.Alias);

            if (row[i].IsNull())
                E->Push();
            else
            {
                switch (fieldMetadata.Type)
                {
                    case DatabaseFieldTypes::UInt8:
                    case DatabaseFieldTypes::UInt16:
                    case DatabaseFieldTypes::UInt32:
                        E->Push(row[i].GetUInt32());
                        break;
                    case DatabaseFieldTypes::Int8:
                    case DatabaseFieldTypes::Int16:
                    case DatabaseFieldTypes::Int32:
                        E->Push(row[i].GetInt32());
                        break;
                    case DatabaseFieldTypes::UInt64:
                        E->Push(row[i].GetUInt64());
                        break;
                    case DatabaseFieldTypes::Int64:
                        E->Push(row[i].GetInt64());
                        break;
                    case DatabaseFieldTypes::Float:
                    case DatabaseFieldTypes::Double:
                    case DatabaseFieldTypes::Decimal:
                        E->Push(row[i].GetDouble());
                        break;
                    case DatabaseFieldTypes::Date:
                    case DatabaseFieldTypes::Time:
                    case DatabaseFieldTypes::Binary:
                        E->Push(row[i].GetCString());
                        break;
                    default:
                        E->Push();
                        break;
                }
            }
            lua_rawset(E->L, tbl);
        }

        lua_settop(E->L, tbl);
        return 1;
    }

    ElunaRegister<ElunaQuery> QueryMethods[] =
    {
        // Getters
        { "GetColumnCount", &LuaQuery::GetColumnCount },
        { "GetRowCount", &LuaQuery::GetRowCount },
        { "GetRow", &LuaQuery::GetRow },
        { "GetBool", &LuaQuery::GetBool },
        { "GetUInt8", &LuaQuery::GetUInt8 },
        { "GetUInt16", &LuaQuery::GetUInt16 },
        { "GetUInt32", &LuaQuery::GetUInt32 },
        { "GetUInt64", &LuaQuery::GetUInt64 },
        { "GetInt8", &LuaQuery::GetInt8 },
        { "GetInt16", &LuaQuery::GetInt16 },
        { "GetInt32", &LuaQuery::GetInt32 },
        { "GetInt64", &LuaQuery::GetInt64 },
        { "GetFloat", &LuaQuery::GetFloat },
        { "GetDouble", &LuaQuery::GetDouble },
        { "GetString", &LuaQuery::GetString },

        // Boolean
        { "NextRow", &LuaQuery::NextRow },
        { "IsNull", &LuaQuery::IsNull }
    };
};
#undef RESULT

#endif
