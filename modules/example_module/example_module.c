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

/*
 * _Unload() is a magic function name which is called(if found) on every module
 * when Eluna uninitializes(on server exit)
 * 
 * You do not need this, but you can use it to save files, cleanly exit threads, etc.
 * 
 */
int _Unload(lua_State* L) {
    return 0;
}

static const struct luaL_Reg functions [] = {
    {"say_hello", say_hello},
    {"_Unload", _Unload},
    {NULL, NULL}
};

MODULEAPI luaopen_example_module(lua_State *L) {
    luaL_register(L, "example_module", functions);
    return 1;
}
