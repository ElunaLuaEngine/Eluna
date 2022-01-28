#include "lua.h"
#include "lauxlib.h"

#if defined(WIN32)
#define MODULEAPI __declspec(dllexport) int
#else
#define MODULEAPI int
#endif

const char MESSAGE[] = "hello world!";

int say_hello(lua_State *L) {
    lua_pushstring(L, MESSAGE);
    return 1;
}

static const struct luaL_Reg functions [] = {
    {"say_hello", say_hello},
    {NULL, NULL}
};

MODULEAPI luaopen_example_module(lua_State *L) {
    luaL_register(L, "example_module", functions);
    return 1;
}
