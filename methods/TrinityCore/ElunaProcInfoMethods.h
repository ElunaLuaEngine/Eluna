#ifndef ELUNAPROCINFOMETHODS_H
#define ELUNAPROCINFOMETHODS_H

namespace LuaElunaProcInfo
{
    /**
     * Returns the [Unit] that triggered the proc event.
     *
     * @return [Unit] actor
     */
    int GetActor(Eluna* E, ElunaProcInfo* procInfo)
    {
        E->Push(procInfo->GetActor());
        return 1;
    }

    /**
     * Returns the target [Unit] of the proc event action.
     *
     * @return [Unit] actionTarget
     */
    int GetActionTarget(Eluna* E, ElunaProcInfo* procInfo)
    {
        E->Push(procInfo->GetActionTarget());
        return 1;
    }

    /**
     * Returns the type mask of the proc event.
     *
     * @return uint32 typeMask
     */
    int GetTypeMask(Eluna* E, ElunaProcInfo* procInfo)
    {
        E->Push(procInfo->GetTypeMask());
        return 1;
    }

    /**
     * Returns the spell type mask of the proc event.
     *
     * @return uint32 spellTypeMask
     */
    int GetSpellTypeMask(Eluna* E, ElunaProcInfo* procInfo)
    {
        E->Push(procInfo->GetSpellTypeMask());
        return 1;
    }

    /**
     * Returns the spell phase mask of the proc event.
     *
     * @return uint32 spellPhaseMask
     */
    int GetSpellPhaseMask(Eluna* E, ElunaProcInfo* procInfo)
    {
        E->Push(procInfo->GetSpellPhaseMask());
        return 1;
    }

    /**
     * Returns the hit mask of the proc event.
     *
     * @return uint32 hitMask
     */
    int GetHitMask(Eluna* E, ElunaProcInfo* procInfo)
    {
        E->Push(procInfo->GetHitMask());
        return 1;
    }

    /**
     * Returns the [Spell] that triggered the proc event, or nil if the proc was not triggered by a spell.
     *
     * @return [Spell] procSpell
     */
    int GetProcSpell(Eluna* E, ElunaProcInfo* procInfo)
    {
        E->Push(procInfo->GetProcSpell());
        return 1;
    }

    /**
     * Returns the [SpellInfo] of the spell that triggered the proc event.
     *
     * @return [SpellInfo] spellInfo
     */
    int GetSpellInfo(Eluna* E, ElunaProcInfo* procInfo)
    {
        if (!procInfo->GetSpellInfo())
        {
            E->Push();
            return 1;
        }

        ElunaSpellInfo info(procInfo->GetSpellInfo()->Id);
        E->Push(&info);
        return 1;
    }

    /**
     * Returns the school mask of the proc event.
     *
     * @return uint32 schoolMask
     */
    int GetSchoolMask(Eluna* E, ElunaProcInfo* procInfo)
    {
        E->Push(procInfo->GetSchoolMask());
        return 1;
    }

    /**
     * Returns the damage dealt in the proc event.
     *
     * @return uint32 damage
     */
    int GetDamage(Eluna* E, ElunaProcInfo* procInfo)
    {
        E->Push(procInfo->GetDamage());
        return 1;
    }

    /**
     * Returns the damage effect type of the proc event.
     *
     * @return uint32 damageType
     */
    int GetDamageType(Eluna* E, ElunaProcInfo* procInfo)
    {
        E->Push(procInfo->GetDamageType());
        return 1;
    }

    /**
     * Returns the weapon attack type of the proc event.
     *
     * @return uint32 attackType
     */
    int GetAttackType(Eluna* E, ElunaProcInfo* procInfo)
    {
        E->Push(procInfo->GetAttackType());
        return 1;
    }

    /**
     * Returns the amount of damage absorbed in the proc event.
     *
     * @return uint32 damageAbsorb
     */
    int GetDamageAbsorb(Eluna* E, ElunaProcInfo* procInfo)
    {
        E->Push(procInfo->GetDamageAbsorb());
        return 1;
    }

    /**
     * Returns the amount of damage resisted in the proc event.
     *
     * @return uint32 resist
     */
    int GetResist(Eluna* E, ElunaProcInfo* procInfo)
    {
        E->Push(procInfo->GetResist());
        return 1;
    }

    /**
     * Returns the amount of damage blocked in the proc event.
     *
     * @return uint32 block
     */
    int GetBlock(Eluna* E, ElunaProcInfo* procInfo)
    {
        E->Push(procInfo->GetBlock());
        return 1;
    }

    /**
     * Returns the amount of healing done in the proc event.
     *
     * @return uint32 heal
     */
    int GetHeal(Eluna* E, ElunaProcInfo* procInfo)
    {
        E->Push(procInfo->GetHeal());
        return 1;
    }

    /**
     * Returns the effective healing done in the proc event, after overhealing is subtracted.
     *
     * @return uint32 effectiveHeal
     */
    int GetEffectiveHeal(Eluna* E, ElunaProcInfo* procInfo)
    {
        E->Push(procInfo->GetEffectiveHeal());
        return 1;
    }

    /**
     * Returns the amount of healing absorbed in the proc event.
     *
     * @return uint32 healAbsorb
     */
    int GetHealAbsorb(Eluna* E, ElunaProcInfo* procInfo)
    {
        E->Push(procInfo->GetHealAbsorb());
        return 1;
    }

    /**
     * Returns `true` if the proc event involved damage, `false` otherwise.
     *
     * @return bool hasDamage
     */
    int HasDamage(Eluna* E, ElunaProcInfo* procInfo)
    {
        E->Push(procInfo->HasDamage());
        return 1;
    }

    /**
     * Returns `true` if the proc event involved healing, `false` otherwise.
     *
     * @return bool hasHeal
     */
    int HasHeal(Eluna* E, ElunaProcInfo* procInfo)
    {
        E->Push(procInfo->HasHeal());
        return 1;
    }

    /**
     * Sets the damage of the proc event.
     *
     * @param int32 damage : the damage value to set
     */
    int SetDamage(Eluna* E, ElunaProcInfo* procInfo)
    {
        int32 damage = E->CHECKVAL<int32>(2);
        procInfo->SetDamage(damage);
        return 0;
    }

    /**
     * Sets the absorbed damage of the proc event.
     *
     * @param uint32 absorb : the absorb value to set
     */
    int SetAbsorbDamage(Eluna* E, ElunaProcInfo* procInfo)
    {
        uint32 absorb = E->CHECKVAL<uint32>(2);
        procInfo->SetAbsorbDamage(absorb);
        return 0;
    }

    /**
     * Sets the resisted damage of the proc event.
     *
     * @param uint32 resist : the resist value to set
     */
    int SetResistDamage(Eluna* E, ElunaProcInfo* procInfo)
    {
        uint32 resist = E->CHECKVAL<uint32>(2);
        procInfo->SetResistDamage(resist);
        return 0;
    }

    /**
     * Sets the blocked damage of the proc event.
     *
     * @param uint32 block : the block value to set
     */
    int SetBlockDamage(Eluna* E, ElunaProcInfo* procInfo)
    {
        uint32 block = E->CHECKVAL<uint32>(2);
        procInfo->SetBlockDamage(block);
        return 0;
    }

    /**
     * Sets the healing of the proc event.
     *
     * @param int32 heal : the heal value to set
     */
    int SetHeal(Eluna* E, ElunaProcInfo* procInfo)
    {
        int32 heal = E->CHECKVAL<int32>(2);
        procInfo->SetHeal(heal);
        return 0;
    }

    /**
     * Sets the absorbed healing of the proc event.
     *
     * @param uint32 absorb : the absorb value to set
     */
    int SetAbsorbHeal(Eluna* E, ElunaProcInfo* procInfo)
    {
        uint32 absorb = E->CHECKVAL<uint32>(2);
        procInfo->SetAbsorbHeal(absorb);
        return 0;
    }

    /**
     * Sets the effective healing of the proc event.
     *
     * @param uint32 effectiveHeal : the effective heal value to set
     */
    int SetEffectiveHeal(Eluna* E, ElunaProcInfo* procInfo)
    {
        uint32 effectiveHeal = E->CHECKVAL<uint32>(2);
        procInfo->SetEffectiveHeal(effectiveHeal);
        return 0;
    }

    /**
     * Returns the [Map] the proc event occurred on.
     *
     * @return [Map] map
     */
    int GetMap(Eluna* E, ElunaProcInfo* procInfo)
    {
        E->Push(procInfo->GetMap());
        return 1;
    }

    ElunaRegister<ElunaProcInfo> ElunaProcInfoMethods[] =
    {
        // Getters
        { "GetActor",          &LuaElunaProcInfo::GetActor },
        { "GetActionTarget",   &LuaElunaProcInfo::GetActionTarget },
        { "GetTypeMask",       &LuaElunaProcInfo::GetTypeMask },
        { "GetSpellTypeMask",  &LuaElunaProcInfo::GetSpellTypeMask },
        { "GetSpellPhaseMask", &LuaElunaProcInfo::GetSpellPhaseMask },
        { "GetHitMask",        &LuaElunaProcInfo::GetHitMask },
        { "GetProcSpell",      &LuaElunaProcInfo::GetProcSpell },
        { "GetSpellInfo",      &LuaElunaProcInfo::GetSpellInfo },
        { "GetSchoolMask",     &LuaElunaProcInfo::GetSchoolMask },
        { "GetDamage",         &LuaElunaProcInfo::GetDamage },
        { "GetDamageType",     &LuaElunaProcInfo::GetDamageType },
        { "GetAttackType",     &LuaElunaProcInfo::GetAttackType },
        { "GetDamageAbsorb",   &LuaElunaProcInfo::GetDamageAbsorb },
        { "GetResist",         &LuaElunaProcInfo::GetResist },
        { "GetBlock",          &LuaElunaProcInfo::GetBlock },
        { "GetHeal",           &LuaElunaProcInfo::GetHeal },
        { "GetEffectiveHeal",  &LuaElunaProcInfo::GetEffectiveHeal },
        { "GetHealAbsorb",     &LuaElunaProcInfo::GetHealAbsorb },
        { "GetMap",            &LuaElunaProcInfo::GetMap },
        // Setters
        { "SetDamage",         &LuaElunaProcInfo::SetDamage },
        { "SetAbsorbDamage",   &LuaElunaProcInfo::SetAbsorbDamage },
        { "SetResistDamage",   &LuaElunaProcInfo::SetResistDamage },
        { "SetBlockDamage",    &LuaElunaProcInfo::SetBlockDamage },
        { "SetHeal",           &LuaElunaProcInfo::SetHeal },
        { "SetAbsorbHeal",     &LuaElunaProcInfo::SetAbsorbHeal },
        { "SetEffectiveHeal",  &LuaElunaProcInfo::SetEffectiveHeal },
        // Booleans
        { "HasDamage",         &LuaElunaProcInfo::HasDamage },
        { "HasHeal",           &LuaElunaProcInfo::HasHeal },
    };
}

#endif
