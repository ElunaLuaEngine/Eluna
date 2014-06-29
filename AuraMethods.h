/*
* Copyright (C) 2010 - 2014 Eluna Lua Engine <http://emudevs.com/>
* This program is free software licensed under GPL version 3
* Please see the included DOCS/LICENSE.md for more information
*/

#ifndef AURAMETHODS_H
#define AURAMETHODS_H

namespace LuaAura
{
    int GetCaster(lua_State* L, Aura* aura)
    {
        Eluna::Push(L, aura->GetCaster());
        return 1;
    }

    int GetCasterGUID(lua_State* L, Aura* aura)
    {
#ifndef TRINITY
        Eluna::Push(L, aura->GetCasterGuid());
#else
        Eluna::Push(L, aura->GetCasterGUID());
#endif
        return 1;
    }

    int GetCasterLevel(lua_State* L, Aura* aura)
    {
        Eluna::Push(L, aura->GetCaster()->getLevel());
        return 1;
    }

    int GetDuration(lua_State* L, Aura* aura)
    {
#ifndef TRINITY
        Eluna::Push(L, aura->GetAuraDuration());
#else
        Eluna::Push(L, aura->GetDuration());
#endif
        return 1;
    }

    int GetCharges(lua_State* L, Aura* aura)
    {
        Eluna::Push(L, aura->GetStackAmount());
        return 1;
    }

    int GetAuraId(lua_State* L, Aura* aura)
    {
        Eluna::Push(L, aura->GetId());
        return 1;
    }

    int GetMaxDuration(lua_State* L, Aura* aura)
    {
#ifndef TRINITY
        Eluna::Push(L, aura->GetAuraMaxDuration());
#else
        Eluna::Push(L, aura->GetMaxDuration());
#endif
        return 1;
    }

    int GetStackAmount(lua_State* L, Aura* aura)
    {
        Eluna::Push(L, aura->GetStackAmount());
        return 1;
    }

    int GetOwner(lua_State* L, Aura* aura)
    {
#ifndef TRINITY
        Eluna::Push(L, aura->GetTarget());
#else
        Eluna::Push(L, aura->GetOwner());
#endif
        return 1;
    }

    int SetDuration(lua_State* L, Aura* aura)
    {
        int duration = Eluna::CHECKVAL<int>(L, 2);
#ifndef TRINITY
        aura->GetHolder()->SetAuraDuration(duration);
#else
        aura->SetDuration(duration);
#endif
        return 0;
    }

    int SetMaxDuration(lua_State* L, Aura* aura)
    {
        int duration = Eluna::CHECKVAL<int>(L, 2);
#ifndef TRINITY
        aura->GetHolder()->SetAuraMaxDuration(duration);
#else
        aura->SetMaxDuration(duration);
#endif
        return 0;
    }

    int SetStackAmount(lua_State* L, Aura* aura)
    {
        int amount = Eluna::CHECKVAL<int>(L, 2);
#ifndef TRINITY
        aura->GetHolder()->SetStackAmount(amount);
#else
        aura->SetStackAmount(amount);
#endif
        return 0;
    }

    int Remove(lua_State* /*L*/, Aura* aura)
    {
#ifndef TRINITY
        aura->GetHolder()->RemoveAura(aura->GetEffIndex());
#else
        aura->Remove();
#endif
        return 0;
    }
};
#endif
