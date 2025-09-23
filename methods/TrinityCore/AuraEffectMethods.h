/*
* Copyright (C) 2010 - 2024 Eluna Lua Engine <https://elunaluaengine.github.io/>
* This program is free software licensed under GPL version 3
* Please see the included DOCS/LICENSE.md for more information
*/

#ifndef AURAEFFECTMETHODS_H
#define AURAEFFECTMETHODS_H


namespace LuaAuraEffects
{
    int GetBase(Eluna* E, AuraEffect* aurEff)
    {
        E->Push(aurEff->GetBase());
        return 1;
    }

    int GetBaseAmount(Eluna* E, AuraEffect* aurEff)
    {
        E->Push(aurEff->GetBaseAmount());
        return 1;
    }

    int GetAmplitude(Eluna* E, AuraEffect* aurEff)
    {
        E->Push(aurEff->GetAmplitude());
        return 1;
    }

    int GetAmount(Eluna* E, AuraEffect* aurEff)
    {
        E->Push(aurEff->GetAmount());
        return 1;
    }

    int SetAmount(Eluna* E, AuraEffect* aurEff)
    {
        int32 amount = E->CHECKVAL<int32>(2);
        aurEff->SetAmount(amount);
        return 0;
    }

    int GetPeriodicTimer(Eluna* E, AuraEffect* aurEff)
    {
        E->Push(aurEff->GetPeriodicTimer());
        return 1;
    }

    int SetPeriodicTimer(Eluna* E, AuraEffect* aurEff)
    {
        int32 timer = E->CHECKVAL<int32>(2);
        aurEff->SetPeriodicTimer(timer);
        return 0;
    }

    int CalculateAmount(Eluna* E, AuraEffect* aurEff)
    {
        Unit* caster = E->CHECKOBJ<Unit>(2);
        E->Push(aurEff->CalculateAmount(caster));
        return 1;
    }

    int CalculatePeriodic(Eluna* E, AuraEffect* aurEff)
    {
        Unit* caster = E->CHECKOBJ<Unit>(2);
        bool resetPeriodicTimer = E->CHECKVAL<bool>(3, false);
        bool load = E->CHECKVAL<bool>(4, false);
        aurEff->CalculatePeriodic(caster, resetPeriodicTimer, load);
        return 0;
    }

    int ChangeAmount(Eluna* E, AuraEffect* aurEff)
    {
        int32 newAmount = E->CHECKVAL<int32>(2);
        bool mark = E->CHECKVAL<bool>(3, true);
        bool onStackOrReapply = E->CHECKVAL<bool>(4, false);
        aurEff->ChangeAmount(newAmount, mark, onStackOrReapply);
        return 0;
    }

    int RecalculateAmount(Eluna* /*E*/, AuraEffect* aurEff)
    {
        aurEff->RecalculateAmount();
        return 0;
    }

    int CanBeRecalculated(Eluna* E, AuraEffect* aurEff)
    {
        E->Push(aurEff->CanBeRecalculated());
        return 1;
    }

    int SetCanBeRecalculated(Eluna* E, AuraEffect* aurEff)
    {
        bool val = E->CHECKVAL<bool>(2, true);
        aurEff->SetCanBeRecalculated(val);
        return 0;
    }

    int GetTickNumber(Eluna* E, AuraEffect* aurEff)
    {
        E->Push(aurEff->GetTickNumber());
        return 1;
    }

    int GetRemainingTicks(Eluna* E, AuraEffect* aurEff)
    {
        E->Push(aurEff->GetRemainingTicks());
        return 1;
    }

    int GetTotalTicks(Eluna* E, AuraEffect* aurEff)
    {
        E->Push(aurEff->GetTotalTicks());
        return 1;
    }

    int GetTargetList(Eluna* E, AuraEffect* aurEff)
    {
        std::list<Unit*> list;
        aurEff->GetTargetList(list);
        lua_createtable(E->L, list.size(), 0);
        int tbl = lua_gettop(E->L);
        uint32 i = 0;

        for (std::list<Unit*>::const_iterator it = list.begin(); it != list.end(); ++it)
        {
            E->Push(*it);
            lua_rawseti(E->L, tbl, ++i);
        }

        lua_settop(E->L, tbl);
        return 1;
    }

    ElunaRegister<AuraEffect> AuraEffectMethods[] =
    {
        {"GetBase", &LuaAuraEffects::GetBase},
        {"GetBaseAmount", &LuaAuraEffects::GetBaseAmount},
        {"GetAmplitude", &LuaAuraEffects::GetAmplitude},
        {"GetAmount", &LuaAuraEffects::GetAmount},
        {"SetAmount", &LuaAuraEffects::SetAmount},
        {"GetPeriodicTimer", &LuaAuraEffects::GetPeriodicTimer},
        {"SetPeriodicTimer", &LuaAuraEffects::SetPeriodicTimer},
        {"CalculateAmount", &LuaAuraEffects::CalculateAmount},
        {"CalculatePeriodic", &LuaAuraEffects::CalculatePeriodic},
        {"ChangeAmount", &LuaAuraEffects::ChangeAmount},
        {"RecalculateAmount", &LuaAuraEffects::RecalculateAmount},
        {"CanBeRecalculated", &LuaAuraEffects::CanBeRecalculated},
        {"SetCanBeRecalculated", &LuaAuraEffects::SetCanBeRecalculated},
        {"GetTickNumber", &LuaAuraEffects::GetTickNumber},
        {"GetRemainingTicks", &LuaAuraEffects::GetRemainingTicks},
        {"GetTotalTicks", &LuaAuraEffects::GetTotalTicks},
        {"GetTargetList", &LuaAuraEffects::GetTargetList}
    };
};
#endif

