#ifndef ELUNAPROCINFOMETHODS_H
#define ELUNAPROCINFOMETHODS_H

namespace LuaElunaProcInfo
{
    int GetActor(Eluna* E, ElunaProcInfo* procInfo)
    {
        E->Push(procInfo->GetActor());
        return 1;
    }

    int GetActionTarget(Eluna* E, ElunaProcInfo* procInfo)
    {
        E->Push(procInfo->GetActionTarget());
        return 1;
    }

    int GetTypeMask(Eluna* E, ElunaProcInfo* procInfo)
    {
        E->Push(procInfo->GetTypeMask());
        return 1;
    }

    int GetSpellTypeMask(Eluna* E, ElunaProcInfo* procInfo)
    {
        E->Push(procInfo->GetSpellTypeMask());
        return 1;
    }

    int GetSpellPhaseMask(Eluna* E, ElunaProcInfo* procInfo)
    {
        E->Push(procInfo->GetSpellPhaseMask());
        return 1;
    }

    int GetHitMask(Eluna* E, ElunaProcInfo* procInfo)
    {
        E->Push(procInfo->GetHitMask());
        return 1;
    }

    int GetProcSpell(Eluna* E, ElunaProcInfo* procInfo)
    {
        E->Push(procInfo->GetProcSpell());
        return 1;
    }

    /*int GetSpellInfo(Eluna* E, ElunaProcInfo* procInfo)
    {
        E->Push(procInfo->GetSpellInfo());
        return 1;
    }*/

    int GetSchoolMask(Eluna* E, ElunaProcInfo* procInfo)
    {
        E->Push(procInfo->GetSchoolMask());
        return 1;
    }

    int GetDamage(Eluna* E, ElunaProcInfo* procInfo)
    {
        E->Push(procInfo->GetDamage());
        return 1;
    }

    int GetDamageType(Eluna* E, ElunaProcInfo* procInfo)
    {
        E->Push(procInfo->GetDamageType());
        return 1;
    }

    int GetAttackType(Eluna* E, ElunaProcInfo* procInfo)
    {
        E->Push(procInfo->GetAttackType());
        return 1;
    }

    int GetDamageAbsorb(Eluna* E, ElunaProcInfo* procInfo)
    {
        E->Push(procInfo->GetDamageAbsorb());
        return 1;
    }

    int GetResist(Eluna* E, ElunaProcInfo* procInfo)
    {
        E->Push(procInfo->GetResist());
        return 1;
    }

    int GetBlock(Eluna* E, ElunaProcInfo* procInfo)
    {
        E->Push(procInfo->GetBlock());
        return 1;
    }

    int GetHeal(Eluna* E, ElunaProcInfo* procInfo)
    {
        E->Push(procInfo->GetHeal());
        return 1;
    }

    int GetEffectiveHeal(Eluna* E, ElunaProcInfo* procInfo)
    {
        E->Push(procInfo->GetEffectiveHeal());
        return 1;
    }

    int GetHealAbsorb(Eluna* E, ElunaProcInfo* procInfo)
    {
        E->Push(procInfo->GetHealAbsorb());
        return 1;
    }

    int HasDamage(Eluna* E, ElunaProcInfo* procInfo)
    {
        E->Push(procInfo->HasDamage());
        return 1;
    }

    int HasHeal(Eluna* E, ElunaProcInfo* procInfo)
    {
        E->Push(procInfo->HasHeal());
        return 1;
    }

    int SetDamage(Eluna* E, ElunaProcInfo* procInfo)
    {
        int32 damage = E->CHECKVAL<int32>(2);
        procInfo->SetDamage(damage);
        return 0;
    }

    int SetAbsorbDamage(Eluna* E, ElunaProcInfo* procInfo)
    {
        uint32 absorb = E->CHECKVAL<uint32>(2);
        procInfo->SetAbsorbDamage(absorb);
        return 0;
    }

    int SetResistDamage(Eluna* E, ElunaProcInfo* procInfo)
    {
        uint32 resist = E->CHECKVAL<uint32>(2);
        procInfo->SetResistDamage(resist);
        return 0;
    }

    int SetBlockDamage(Eluna* E, ElunaProcInfo* procInfo)
    {
        uint32 block = E->CHECKVAL<uint32>(2);
        procInfo->SetBlockDamage(block);
        return 0;
    }

    int SetHeal(Eluna* E, ElunaProcInfo* procInfo)
    {
        int32 heal = E->CHECKVAL<int32>(2);
        procInfo->SetHeal(heal);
        return 0;
    }

    int SetAbsorbHeal(Eluna* E, ElunaProcInfo* procInfo)
    {
        uint32 absorb = E->CHECKVAL<uint32>(2);
        procInfo->SetAbsorbHeal(absorb);
        return 0;
    }

    int SetEffectiveHeal(Eluna* E, ElunaProcInfo* procInfo)
    {
        uint32 effectiveHeal = E->CHECKVAL<uint32>(2);
        procInfo->SetEffectiveHeal(effectiveHeal);
        return 0;
    }

    int GetMap(Eluna* E, ElunaProcInfo* procInfo)
    {
        E->Push(procInfo->GetMap());
        return 1;
    }

    ElunaRegister<ElunaProcInfo> ElunaProcInfoMethods[] =
    {
        { "GetActor", &LuaElunaProcInfo::GetActor },
        { "GetActionTarget", &LuaElunaProcInfo::GetActionTarget },
        { "GetTypeMask", &LuaElunaProcInfo::GetTypeMask },
        { "GetSpellTypeMask", &LuaElunaProcInfo::GetSpellTypeMask },
        { "GetSpellPhaseMask", &LuaElunaProcInfo::GetSpellPhaseMask },
        { "GetHitMask", &LuaElunaProcInfo::GetHitMask },
        { "GetProcSpell", &LuaElunaProcInfo::GetProcSpell },
        //{ "GetSpellInfo", &LuaElunaProcInfo::GetSpellInfo },
        { "GetSchoolMask", &LuaElunaProcInfo::GetSchoolMask },
        { "GetDamage", &LuaElunaProcInfo::GetDamage },
        { "GetDamageType", &LuaElunaProcInfo::GetDamageType },
        { "GetAttackType", &LuaElunaProcInfo::GetAttackType },
        { "GetDamageAbsorb", &LuaElunaProcInfo::GetDamageAbsorb },
        { "GetResist", &LuaElunaProcInfo::GetResist },
        { "GetBlock", &LuaElunaProcInfo::GetBlock },
        { "SetDamage", &LuaElunaProcInfo::SetDamage },
        { "SetAbsorbDamage", &LuaElunaProcInfo::SetAbsorbDamage },
        { "SetResistDamage", &LuaElunaProcInfo::SetResistDamage },
        { "SetBlockDamage", &LuaElunaProcInfo::SetBlockDamage },
        { "GetHeal", &LuaElunaProcInfo::GetHeal },
        { "GetEffectiveHeal", &LuaElunaProcInfo::GetEffectiveHeal },
        { "GetHealAbsorb", &LuaElunaProcInfo::GetHealAbsorb },
        { "SetHeal", &LuaElunaProcInfo::SetHeal },
        { "SetAbsorbHeal", &LuaElunaProcInfo::SetAbsorbHeal },
        { "SetEffectiveHeal", &LuaElunaProcInfo::SetEffectiveHeal },
        { "HasDamage", &LuaElunaProcInfo::HasDamage },
        { "HasHeal", &LuaElunaProcInfo::HasHeal },
    };
}

#endif
