/*
* Copyright (C) 2010 - 2014 Eluna Lua Engine <http://emudevs.com/>
* This program is free software licensed under GPL version 3
* Please see the included DOCS/LICENSE.md for more information
*/

#ifndef QUESTMETHODS_H
#define QUESTMETHODS_H

namespace LuaQuest
{
    /* BOOLEAN */
    int HasFlag(lua_State* L, Quest* quest)
    {
        uint32 flag = Eluna::CHECKVAL<uint32>(L, 2);
#ifndef TRINITY
        Eluna::Push(L, quest->HasQuestFlag((QuestFlags)flag));
#else
        Eluna::Push(L, quest->HasFlag(flag));
#endif
        return 1;
    }

#ifndef CLASSIC
    int IsDaily(lua_State* L, Quest* quest)
    {
        Eluna::Push(L, quest->IsDaily());
        return 1;
    }
#endif

    int IsRepeatable(lua_State* L, Quest* quest)
    {
        Eluna::Push(L, quest->IsRepeatable());
        return 1;
    }

    /* GETTERS */
    int GetId(lua_State* L, Quest* quest)
    {
        Eluna::Push(L, quest->GetQuestId());
        return 1;
    }

    int GetLevel(lua_State* L, Quest* quest)
    {
        Eluna::Push(L, quest->GetQuestLevel());
        return 1;
    }

    int GetMinLevel(lua_State* L, Quest* quest)
    {
        Eluna::Push(L, quest->GetMinLevel());
        return 1;
    }

    int GetNextQuestId(lua_State* L, Quest* quest)
    {
        Eluna::Push(L, quest->GetNextQuestId());
        return 1;
    }

    int GetPrevQuestId(lua_State* L, Quest* quest)
    {
        Eluna::Push(L, quest->GetPrevQuestId());
        return 1;
    }

    int GetNextQuestInChain(lua_State* L, Quest* quest)
    {
        Eluna::Push(L, quest->GetNextQuestInChain());
        return 1;
    }

    int GetFlags(lua_State* L, Quest* quest)
    {
#ifndef TRINITY
        Eluna::Push(L, quest->GetQuestFlags());
#else
        Eluna::Push(L, quest->GetFlags());
#endif
        return 1;
    }

    int GetType(lua_State* L, Quest* quest)
    {
        Eluna::Push(L, quest->GetType());
        return 1;
    }

    /*int GetMaxLevel(lua_State* L, Quest* quest)
    {
    Eluna::Push(L, quest->GetMaxLevel());
    return 1;
    }*/
};
#endif
