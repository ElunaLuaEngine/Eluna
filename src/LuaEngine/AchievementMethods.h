/*
* Copyright (C) 2010 - 2016 Eluna Lua Engine <http://emudevs.com/>
* This program is free software licensed under GPL version 3
* Please see the included DOCS/LICENSE.md for more information
*/

#ifndef ACHIEVEMENTMETHODS_H
#define ACHIEVEMENTMETHODS_H

namespace LuaAchievement
{
    /**
     * Returns the [Achievement]s ID
     *
     * @return uint32 id
     */
    int GetId(lua_State* L, AchievementEntry* const achievement)
    {
        Eluna::Push(L, achievement->ID);
        return 1;
    }
};
#endif
