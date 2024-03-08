**This directory is used for custom C modules.**

*Thanks to [@anzz1](https://github.com/anzz1) for the original work!*

**Quick guide below:**
- Create a subdirectory with your module name.
- Add your module files (.c, .h etc).
- Run cmake, this will automatically add a new project which compiles the appropriate .dll or .so file.
- Place the .dll or .so file inside your lua_scripts directory.
- Use "require modulename" in whichever script you use the module.


**Below is an example module:**

example_module.c
```C
#include <lua.h>
#include <lauxlib.h>

#if defined(WIN32)
#define MODULEAPI __declspec(dllexport) int
#else
#define MODULEAPI int
#endif

/*
 * example_module.say_hello() will return the below defined message.
 */
const char MESSAGE[] = "hello world!";
int say_hello(lua_State *L) {
    lua_pushstring(L, MESSAGE);
    return 1;
}

/*
 * the unload function will run on the Lua state close.
 * this can then be used to save, exit cleanly, etc.
 */
int Unload(lua_State* L) {
    luaL_dostring(L, "print('goodbye world!');");
    return 0;
}

/*
 * functions is a list of C functions and their bound function name in the Lua namespace
 */
static const struct luaL_Reg functions [] = {
    {"say_hello", say_hello},
    {"unload", Unload},
    {NULL, NULL}
};

/*
 * all modules need a luaopen_xxxx function, where xxxx is the name of the module.
 * this is automatically executed on require.
 */
MODULEAPI luaopen_example_module(lua_State* L) {
    // register the example module and its function list in the global namespace
    luaL_register(L, "example_module", functions);

    // run the Unload function on ELUNA_EVENT_ON_LUA_STATE_CLOSE
    if (luaL_loadstring(L, "RegisterServerEvent(16, example_module.unload)") != 0)
        return lua_error(L);
    lua_call(L, 0, 0);
    return 1;
}
```
This would generate into example_module.dll/.so, and you could call this as shown below:

```Lua
require "example_module"

print("Testing say_hello()")
print(example_module.say_hello())
```
