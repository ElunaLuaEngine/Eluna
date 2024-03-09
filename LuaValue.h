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

#pragma once

#include <unordered_map> // std::unordered_map
#include <string> // std::to_string, std::string
#include <variant> // std::monostate, std::variant, std::visit
#include <memory> // std::unique_ptr, std::shared_ptr
#include <type_traits> // std::decay_t, std::is_same_v, std::false_type
#include <initializer_list> // std::initializer_list
#include <utility> // std::pair, std::make_pair, std::move

constexpr const char* LUAVAL_MT_NAME = "LuaVal";
class LuaVal;
struct lua_State;

size_t LuaValHash(LuaVal const& k);

namespace std {

    template <>
    struct hash<LuaVal>
    {
        std::size_t operator()(const LuaVal& k) const
        {
            return LuaValHash(k);
        }
    };
}

class LuaVal
{
public:
    typedef std::unordered_map<LuaVal, LuaVal> MapType;
    typedef std::monostate NIL;
    template<class T> struct always_false : std::false_type {};
    typedef std::shared_ptr<MapType> WrappedMap;
    typedef std::variant<NIL, std::string, WrappedMap, bool, double> LuaValVariant;

    static int lua_get(lua_State* L);
    static int lua_set(lua_State* L);

    static std::string to_string_map(MapType const* ptr);
    int asObject(lua_State* L) const;
    int asLua(lua_State* L, unsigned int depth) const;
    static LuaVal AsLuaVal(lua_State* L, int index);
    static LuaVal FromTable(lua_State* L, int index);
    static int lua_asLua(lua_State* L);
    static int lua_AsLuaVal(lua_State* L);
    static int lua_gc(lua_State* L);
    static int lua_to_string(lua_State* L);

    static LuaVal* GetLuaVal(lua_State* L, int index);
    static LuaVal* GetCheckLuaVal(lua_State* L, int index);
    static int PushLuaVal(lua_State* L, LuaVal const& lv);
    static void Register(lua_State* L);

    bool operator<(LuaVal const& b) const
    {
        return v < b.v;
    }

    bool operator==(LuaVal const& b) const
    {
        return v == b.v;
    }

    std::string to_string() const
    {
        return std::visit([](auto&& arg) -> std::string {
            using T = std::decay_t<decltype(arg)>;
            if constexpr (std::is_same_v<T, NIL>)
                return "nil";
            else if constexpr (std::is_same_v<T, std::string>)
                return arg;
            else if constexpr (std::is_same_v<T, WrappedMap>)
                return LuaVal::to_string_map(arg.get());
            else if constexpr (std::is_same_v<T, bool>)
                return arg ? "true" : "false";
            else if constexpr (std::is_same_v<T, double>)
                return std::to_string(arg);
            else
                static_assert(always_false<T>::value, "non-exhaustive visitor!");
            }, v);
    }

    LuaVal() : v() {}
    LuaVal(std::string const& s) : v(s) {}
    LuaVal(bool b) : v(b) {}
    LuaVal(double d) : v(d) {}
    LuaVal(MapType const& t) : v(std::make_shared<MapType>(t)) {}
    LuaVal(std::initializer_list<std::pair<const LuaVal, LuaVal> /* MapType::value_type */> const& l) : v(std::make_shared<MapType>(l)) {}

    LuaVal(LuaVal&& b) noexcept : v(std::move(b.v)) {
    }
    LuaVal(const LuaVal& b) : v(b.v) {
    }
    ~LuaVal() {
    }
    LuaVal& operator=(LuaVal&& b) noexcept
    {
        v = std::move(b.v);
        return *this;
    }
    LuaVal& operator=(const LuaVal& b) {
        v = b.v;
        return *this;
    }
    LuaVal clone() const {
        LuaVal lv;
        lv.v = std::visit([&](auto&& arg) -> LuaValVariant
        {
            using T = std::decay_t<decltype(arg)>;
            if constexpr (std::is_same_v<T, WrappedMap>)
                return std::make_shared<MapType>(*arg);
            else
                return arg;
        }, v);
        return lv;
    }
    LuaVal reference() const {
        return *this;
    }

    LuaValVariant v;
};
