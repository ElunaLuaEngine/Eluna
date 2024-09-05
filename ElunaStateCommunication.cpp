#include "ElunaStateCommunication.h"
#include <iostream>

std::unordered_map<int, std::unordered_map<std::string, std::function<void(std::string)>>> ElunaStateCommunication::events;

void ElunaStateCommunication::Register(lua_State* L)
{
    lua_register(L, "RegisterStateEvent", ElunaStateCommunication::RegisterStateEvent);
    lua_register(L, "NotifyStateEvent", ElunaStateCommunication::NotifyStateEvent);
}

int ElunaStateCommunication::RegisterStateEvent(lua_State* L)
{
    int mapId = luaL_checkint(L, 1);
    const char* eventName = luaL_checkstring(L, 2);
    
    if (!lua_isfunction(L, 3)) {
        luaL_error(L, "Expected a function as the third argument");
        return 0;
    }

    lua_pushvalue(L, 3);
    int callbackRef = luaL_ref(L, LUA_REGISTRYINDEX);

    events[mapId][eventName] = [L, callbackRef](std::string data) {
        lua_rawgeti(L, LUA_REGISTRYINDEX, callbackRef);
        lua_pushstring(L, data.c_str());
        lua_call(L, 1, 0);
    };

    return 0;
}

int ElunaStateCommunication::NotifyStateEvent(lua_State* L)
{
    int mapId = luaL_checkint(L, 1);
    const char* eventName = luaL_checkstring(L, 2);
    const char* data = luaL_checkstring(L, 3);

    if (events.find(mapId) != events.end() && events[mapId].find(eventName) != events[mapId].end()) {
        events[mapId][eventName](data);
    }

    return 0;
}