/*
* Copyright (C) 2010 - 2024 Eluna Lua Engine <https://elunaluaengine.github.io/>
* This program is free software licensed under GPL version 3
* Please see the included DOCS/LICENSE.md for more information
*/

#ifndef AURAEFFECTMETHODS_H
#define AURAEFFECTMETHODS_H


namespace LuaAuraEffects
{
    /**
     * Returns the [Aura] that this [AuraEffect] belongs to.
     *
     * @return [Aura] base
     */
    int GetBase(Eluna* E, AuraEffect* aurEff)
    {
        E->Push(aurEff->GetBase());
        return 1;
    }

    /**
     * Returns the base amount of the [AuraEffect].
     *
     * @return int32 baseAmount
     */
    int GetBaseAmount(Eluna* E, AuraEffect* aurEff)
    {
        E->Push(aurEff->GetBaseAmount());
        return 1;
    }

    /**
     * Returns the amplitude in milliseconds of the [AuraEffect].
     *
     * @return uint32 amplitude
     */
    int GetAmplitude(Eluna* E, AuraEffect* aurEff)
    {
        E->Push(aurEff->GetAmplitude());
        return 1;
    }

    /**
     * Returns the current amount of the [AuraEffect].
     *
     * @return int32 amount
     */
    int GetAmount(Eluna* E, AuraEffect* aurEff)
    {
        E->Push(aurEff->GetAmount());
        return 1;
    }

    /**
     * Sets the amount of the [AuraEffect].
     *
     * @param int32 amount : the amount to set
     */
    int SetAmount(Eluna* E, AuraEffect* aurEff)
    {
        int32 amount = E->CHECKVAL<int32>(2);
        aurEff->SetAmount(amount);
        return 0;
    }

    /**
     * Returns the remaining time in milliseconds until the next tick of the [AuraEffect].
     *
     * @return int32 periodicTimer
     */
    int GetPeriodicTimer(Eluna* E, AuraEffect* aurEff)
    {
        E->Push(aurEff->GetPeriodicTimer());
        return 1;
    }

    /**
     * Sets the periodic timer of the [AuraEffect].
     *
     * @param int32 timer : the timer value in milliseconds to set
     */
    int SetPeriodicTimer(Eluna* E, AuraEffect* aurEff)
    {
        int32 timer = E->CHECKVAL<int32>(2);
        aurEff->SetPeriodicTimer(timer);
        return 0;
    }

    /**
     * Calculates and returns the amount of the [AuraEffect] for the given caster.
     *
     * @param [Unit] caster : the caster to calculate the amount for
     * @return int32 amount
     */
    int CalculateAmount(Eluna* E, AuraEffect* aurEff)
    {
        Unit* caster = E->CHECKOBJ<Unit>(2);
        E->Push(aurEff->CalculateAmount(caster));
        return 1;
    }

    /**
     * Calculates the periodic properties of the [AuraEffect] for the given caster.
     *
     * @param [Unit] caster : the caster to calculate for
     * @param bool resetPeriodicTimer = false : whether to reset the periodic timer
     * @param bool load = false : whether this is being loaded from the database
     */
    int CalculatePeriodic(Eluna* E, AuraEffect* aurEff)
    {
        Unit* caster = E->CHECKOBJ<Unit>(2);
        bool resetPeriodicTimer = E->CHECKVAL<bool>(3, false);
        bool load = E->CHECKVAL<bool>(4, false);
        aurEff->CalculatePeriodic(caster, resetPeriodicTimer, load);
        return 0;
    }

    /**
     * Changes the amount of the [AuraEffect].
     *
     * @param int32 newAmount : the new amount to set
     * @param bool mark = true : whether to mark the effect as changed
     * @param bool onStackOrReapply = false : whether this change is due to a stack or reapply
     */
    int ChangeAmount(Eluna* E, AuraEffect* aurEff)
    {
        int32 newAmount = E->CHECKVAL<int32>(2);
        bool mark = E->CHECKVAL<bool>(3, true);
        bool onStackOrReapply = E->CHECKVAL<bool>(4, false);
        aurEff->ChangeAmount(newAmount, mark, onStackOrReapply);
        return 0;
    }

    /**
     * Recalculates the amount of the [AuraEffect].
     */
    int RecalculateAmount(Eluna* /*E*/, AuraEffect* aurEff)
    {
        aurEff->RecalculateAmount();
        return 0;
    }

    /**
     * Returns `true` if the [AuraEffect] amount can be recalculated, `false` otherwise.
     *
     * @return bool canBeRecalculated
     */
    int CanBeRecalculated(Eluna* E, AuraEffect* aurEff)
    {
        E->Push(aurEff->CanBeRecalculated());
        return 1;
    }

    /**
     * Sets whether the [AuraEffect] amount can be recalculated.
     *
     * @param bool val = true : set to 'true' to allow recalculation
     */
    int SetCanBeRecalculated(Eluna* E, AuraEffect* aurEff)
    {
        bool val = E->CHECKVAL<bool>(2, true);
        aurEff->SetCanBeRecalculated(val);
        return 0;
    }

    /**
     * Returns the current tick number of the [AuraEffect].
     *
     * @return uint32 tickNumber
     */
    int GetTickNumber(Eluna* E, AuraEffect* aurEff)
    {
        E->Push(aurEff->GetTickNumber());
        return 1;
    }

    /**
     * Returns the total number of ticks of the [AuraEffect].
     *
     * @return uint32 totalTicks
     */
    int GetTotalTicks(Eluna* E, AuraEffect* aurEff)
    {
        E->Push(aurEff->GetTotalTicks());
        return 1;
    }

    /**
     * Returns a table of all [Unit]s currently affected by this [AuraEffect].
     *
     * @return table targets : a table of [Unit] objects
     */
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

    /**
     * Returns the spell ID of the [AuraEffect].
     *
     * @return uint32 id
     */
    int GetId(Eluna* E, AuraEffect* aurEff)
    {
        E->Push(aurEff->GetId());
        return 1;
    }

    /**
     * Returns the effect index of the [AuraEffect].
     *
     * @return uint8 effIndex
     */
    int GetEffIndex(Eluna* E, AuraEffect* aurEff)
    {
        E->Push(uint8(aurEff->GetEffIndex()));
        return 1;
    }

    /**
     * Returns the aura type of the [AuraEffect].
     *
     * @return uint16 auraType
     */
    int GetAuraType(Eluna* E, AuraEffect* aurEff)
    {
        E->Push(uint16(aurEff->GetAuraType()));
        return 1;
    }

    /**
     * Returns the [Unit] that cast the [AuraEffect].
     *
     * @return [Unit] caster
     */
    int GetCaster(Eluna* E, AuraEffect* aurEff)
    {
        E->Push(aurEff->GetCaster());
        return 1;
    }

    /**
     * Returns the GUID of the [Unit] that cast the [AuraEffect].
     *
     * @return ObjectGuid casterGUID
     */
    int GetCasterGUID(Eluna* E, AuraEffect* aurEff)
    {
        E->Push(aurEff->GetCasterGUID());
        return 1;
    }

    /**
     * Returns the [ElunaSpellInfo] of the spell that created this [AuraEffect].
     *
     * @return [ElunaSpellInfo] spellInfo
     */
    int GetSpellInfo(Eluna* E, AuraEffect* aurEff)
    {
        ElunaSpellInfo info(aurEff->GetId());
        E->Push(&info);
        return 1;
    }

    ElunaRegister<AuraEffect> AuraEffectMethods[] =
    {
        // Getters
        { "GetBase",               &LuaAuraEffects::GetBase },
        { "GetBaseAmount",         &LuaAuraEffects::GetBaseAmount },
        { "GetAmplitude",          &LuaAuraEffects::GetAmplitude },
        { "GetAmount",             &LuaAuraEffects::GetAmount },
        { "GetPeriodicTimer",      &LuaAuraEffects::GetPeriodicTimer },
        { "GetTickNumber",         &LuaAuraEffects::GetTickNumber },
        { "GetRemainingTicks",     METHOD_REG_NONE },
        { "GetTotalTicks",         &LuaAuraEffects::GetTotalTicks },
        { "GetTargetList",         &LuaAuraEffects::GetTargetList },
        { "GetId",                 &LuaAuraEffects::GetId },
        { "GetEffIndex",           &LuaAuraEffects::GetEffIndex },
        { "GetAuraType",           &LuaAuraEffects::GetAuraType },
        { "GetCaster",             &LuaAuraEffects::GetCaster },
        { "GetCasterGUID",         &LuaAuraEffects::GetCasterGUID },
        { "GetSpellInfo",          &LuaAuraEffects::GetSpellInfo },
        // Setters
        { "SetAmount",             &LuaAuraEffects::SetAmount },
        { "SetPeriodicTimer",      &LuaAuraEffects::SetPeriodicTimer },
        { "SetCanBeRecalculated",  &LuaAuraEffects::SetCanBeRecalculated },
        // Booleans
        { "CanBeRecalculated",     &LuaAuraEffects::CanBeRecalculated },
        // Other
        { "CalculateAmount",       &LuaAuraEffects::CalculateAmount },
        { "CalculatePeriodic",     &LuaAuraEffects::CalculatePeriodic },
        { "ChangeAmount",          &LuaAuraEffects::ChangeAmount },
        { "RecalculateAmount",     &LuaAuraEffects::RecalculateAmount },
    };
}

#endif

