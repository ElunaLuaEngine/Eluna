#pragma once
#include <unordered_map>
#include <string>
#include <functional>
#include "lua.hpp"

class ElunaStateCommunication
{
public:
    static void Register(lua_State* L);

    static int RegisterStateEvent(lua_State* L);
    static int NotifyStateEvent(lua_State* L);

private:
    static std::unordered_map<int, std::unordered_map<std::string, std::function<void(std::string)>>> events; // Evénements par mapId
};
