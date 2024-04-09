// BSD-3-Clause
// Copyright (c) 2022, Rochet2 <rochet2@post.com>
// All rights reserved.
//
// Redistribution and use in source and binary forms, with or without
// modification, are permitted provided that the following conditions are met:
//
// * Redistributions of source code must retain the above copyright notice, this
//   list of conditions and the following disclaimer.
//
// * Redistributions in binary form must reproduce the above copyright notice,
//   this list of conditions and the following disclaimer in the documentation
//   and/or other materials provided with the distribution.
//
// * Neither the name of the copyright holder nor the names of its
//   contributors may be used to endorse or promote products derived from
//   this software without specific prior written permission.
//
// THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS"
// AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
// IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE
// DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE LIABLE
// FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL
// DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR
// SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER
// CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY,
// OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE
// OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.

#include "ElunaCompat.h"
#include "LuaValue.h"
#include <stdio.h> // snprintf

extern "C"
{
#include "lua.h"
#include "lualib.h"
#include "lauxlib.h"
}

LuaVal* LuaVal::GetLuaVal(lua_State* L, int index) {
    return static_cast<LuaVal*>(luaL_testudata(L, index, LUAVAL_MT_NAME));
}

LuaVal* LuaVal::GetCheckLuaVal(lua_State* L, int index) {
    return static_cast<LuaVal*>(luaL_checkudata(L, index, LUAVAL_MT_NAME));
}

int LuaVal::PushLuaVal(lua_State* L, LuaVal const& lv) {
    LuaVal* ud = static_cast<LuaVal*>(lua_newuserdata(L, sizeof(LuaVal)));
    new (ud) LuaVal(lv.reference());
    luaL_setmetatable(L, LUAVAL_MT_NAME);
    return 1;
}

void LuaVal::Register(lua_State* L) {
    luaL_newmetatable(L, LUAVAL_MT_NAME);
    // mt

    lua_pushvalue(L, -1);
    lua_setfield(L, -2, "__index");
    lua_pushcfunction(L, &LuaVal::lua_to_string);
    lua_setfield(L, -2, "__tostring");
    lua_pushcfunction(L, &LuaVal::lua_gc);
    lua_setfield(L, -2, "__gc");

    lua_pushcfunction(L, &LuaVal::lua_get);
    lua_setfield(L, -2, "Get");
    lua_pushcfunction(L, &LuaVal::lua_set);
    lua_setfield(L, -2, "Set");
    lua_pushcfunction(L, &LuaVal::lua_AsLuaVal);
    lua_setfield(L, -2, "New");
    lua_pushcfunction(L, &LuaVal::lua_asLua);
    lua_setfield(L, -2, "AsTable");

    lua_setglobal(L, "LuaVal");
}

int LuaVal::lua_get(lua_State* L) {
    LuaVal* self = GetCheckLuaVal(L, 1);
    int arguments = std::max(2, lua_gettop(L));
    WrappedMap const* p = std::get_if<WrappedMap>(&self->v);
    if (!p)
        luaL_argerror(L, 1, "trying to index a non-table LuaVal");
    for (int i = 2; i <= arguments; ++i) {
        auto& map = (*p);
        auto klv = AsLuaVal(L, i);
        if (std::holds_alternative<NIL>(klv.v))
            luaL_argerror(L, i, "trying to use nil as key");
        auto it = map->find(klv);
        if (it == map->end()) {
            if (i < arguments) {
                luaL_argerror(L, i, "trying to index a nil value within a LuaVal");
            }
            break;
        }
        else if (i == arguments) {
            auto& val = it->second;
            return val.asObject(L);
        }
        p = std::get_if<WrappedMap>(&it->second.v);
        if (!p)
            luaL_argerror(L, i, "trying to index a non-table LuaVal");
    }
    lua_pushnil(L);
    return 1;
}

int LuaVal::lua_set(lua_State* L) {
    LuaVal* self = GetCheckLuaVal(L, 1);
    int arguments = std::max(3, lua_gettop(L));
    WrappedMap const* p = std::get_if<WrappedMap>(&self->v);
    if (!p)
        luaL_argerror(L, 1, "trying to index a non-table LuaVal");
    for (int i = 2; i <= arguments - 2; ++i) {
        auto& map = (*p);
        auto klv = AsLuaVal(L, i);
        if (std::holds_alternative<NIL>(klv.v))
            luaL_argerror(L, i, "trying to use nil as key");
        auto it = map->find(klv);
        if (it == map->end()) {
            if (i < arguments) {
                luaL_argerror(L, i, "trying to index a nil value within a LuaVal");
            }
            break;
        }
        p = std::get_if<WrappedMap>(&it->second.v);
        if (!p)
            luaL_argerror(L, i, "trying to index a non-table LuaVal");
    }
    auto kk = AsLuaVal(L, arguments - 1);
    auto vv = AsLuaVal(L, arguments);
    if (std::holds_alternative<NIL>(kk.v))
        luaL_argerror(L, arguments - 1, "trying to use nil as key");
    if (std::holds_alternative<NIL>(vv.v)) {
        (**p).erase(kk);
    }
    else {
        auto const& [it, _] = (**p).insert_or_assign(std::move(kk), std::move(vv));
        return it->second.asObject(L);
    }
    return 0;
}

std::string LuaVal::to_string_map(MapType const* ptr)
{
    std::string out = "[\n";
    for (std::pair<const LuaVal, LuaVal> const& pair : *ptr)
        out += "  { key: " + pair.first.to_string() + ", value: " + pair.second.to_string() + " },\n";
    out += ']';
    return out;
}

int LuaVal::lua_to_string(lua_State* L)
{
    LuaVal* self = GetCheckLuaVal(L, 1);
    std::string str = self->to_string();
    lua_pushlstring(L, str.c_str(), str.size());
    return 1;
}

int LuaVal::lua_gc(lua_State* L)
{
    LuaVal* self = GetCheckLuaVal(L, 1);
    self->~LuaVal();
    return 0;
}

int LuaVal::asObject(lua_State* L) const
{
    return std::visit([&](auto&& arg) {
        using T = std::decay_t<decltype(arg)>;
        if constexpr (std::is_same_v<T, NIL>) {
            lua_pushnil(L);
            return 1;
        }
        else if constexpr (std::is_same_v<T, std::string>) {
            lua_pushlstring(L, arg.c_str(), arg.size());
            return 1;
        }
        else if constexpr (std::is_same_v<T, WrappedMap>) {
            return PushLuaVal(L, *this);
        }
        else if constexpr (std::is_same_v<T, bool>) {
            lua_pushboolean(L, arg);
            return 1;
        }
        else if constexpr (std::is_same_v<T, double>) {
            lua_pushnumber(L, arg);
            return 1;
        }
        else {
            static_assert(always_false<T>::value, "non-exhaustive visitor!");
        }
        }, v);
}

int LuaVal::asLua(lua_State* L, unsigned int depth) const
{
    WrappedMap const* p = std::get_if<WrappedMap>(&v);
    if (p)
    {
        lua_newtable(L);
        for (auto& it : **p) {
            if (depth == 1) {
                it.first.asObject(L);
                it.second.asObject(L);
                lua_rawset(L, -3);
            }
            else if (depth == 0) {
                it.first.asLua(L, depth);
                it.second.asLua(L, depth);
                lua_rawset(L, -3);
            }
            else {
                it.first.asLua(L, depth - 1);
                it.second.asLua(L, depth - 1);
                lua_rawset(L, -3);
            }
        }
        return 1;
    }
    return asObject(L);
}

int LuaVal::lua_asLua(lua_State* L)
{
    LuaVal* self = GetCheckLuaVal(L, 1);
    int depth = luaL_optinteger(L, 2, 0);
    return self->asLua(L, static_cast<unsigned int>(depth));
}

LuaVal LuaVal::AsLuaVal(lua_State* L, int index)
{
    auto t = lua_type(L, index);
    switch (t)
    {
    case LUA_TBOOLEAN:
        return LuaVal(static_cast<bool>(lua_toboolean(L, index)));
    case LUA_TNIL:
        return LuaVal();
    case LUA_TNUMBER:
        return LuaVal(lua_tonumber(L, index));
    case LUA_TSTRING: {
        size_t len;
        const char* str = lua_tolstring(L, index, &len);
        return LuaVal(std::string(str, len));
    }
    case LUA_TTABLE:
        return FromTable(L, index);
    case LUA_TUSERDATA:
        if (LuaVal* ptr = GetLuaVal(L, index))
            return ptr->reference();
        break;
    }
    luaL_argerror(L, index, "Trying to use unsupported type");
    return LuaVal();
}

int LuaVal::lua_AsLuaVal(lua_State* L)
{
    return PushLuaVal(L, AsLuaVal(L, 1));
}

LuaVal LuaVal::FromTable(lua_State* L, int index)
{
    // Assumed we know index is a table already
    LuaVal m({});
    auto& t = std::get<WrappedMap>(m.v);
    int top = lua_gettop(L);
    lua_pushnil(L);
    while (lua_next(L, index) != 0) {
        t->emplace(AsLuaVal(L, top + 1), AsLuaVal(L, top + 2));
        lua_pop(L, 1);
    }
    return m;
}

size_t LuaValHash(LuaVal const& k)
{
    return std::hash<LuaVal::LuaValVariant>{}(k.v);
}
