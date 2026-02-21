/*
* Copyright (C) 2010 - 2024 Eluna Lua Engine <https://elunaluaengine.github.io/>
* This program is free software licensed under GPL version 3
* Please see the included DOCS/LICENSE.md for more information
*/
#ifndef SPELLINFO_METHODS
#define SPELLINFO_METHODS
namespace LuaSpellInfo
{
    int GetId(Eluna* E, ElunaSpellInfo* spellInfo)
    {
        E->Push(spellInfo->GetSpellInfo()->Id);
        return 1;
    }

    int GetDispel(Eluna* E, ElunaSpellInfo* spellInfo)
    {
        E->Push(spellInfo->GetSpellInfo()->Dispel);
        return 1;
    }

    int GetMechanic(Eluna* E, ElunaSpellInfo* spellInfo)
    {
        E->Push(spellInfo->GetSpellInfo()->Mechanic);
        return 1;
    }

    int GetAttributes(Eluna* E, ElunaSpellInfo* spellInfo)
    {
        E->Push(spellInfo->GetSpellInfo()->Attributes);
        return 1;
    }

    int GetAttributesEx(Eluna* E, ElunaSpellInfo* spellInfo)
    {
        E->Push(spellInfo->GetSpellInfo()->AttributesEx);
        return 1;
    }

    int GetAttributesEx2(Eluna* E, ElunaSpellInfo* spellInfo)
    {
        E->Push(spellInfo->GetSpellInfo()->AttributesEx2);
        return 1;
    }

    int GetAttributesEx3(Eluna* E, ElunaSpellInfo* spellInfo)
    {
        E->Push(spellInfo->GetSpellInfo()->AttributesEx3);
        return 1;
    }

    int GetAttributesEx4(Eluna* E, ElunaSpellInfo* spellInfo)
    {
        E->Push(spellInfo->GetSpellInfo()->AttributesEx4);
        return 1;
    }

    int GetAttributesEx5(Eluna* E, ElunaSpellInfo* spellInfo)
    {
        E->Push(spellInfo->GetSpellInfo()->AttributesEx5);
        return 1;
    }

    int GetAttributesEx6(Eluna* E, ElunaSpellInfo* spellInfo)
    {
        E->Push(spellInfo->GetSpellInfo()->AttributesEx6);
        return 1;
    }

    int GetAttributesEx7(Eluna* E, ElunaSpellInfo* spellInfo)
    {
        E->Push(spellInfo->GetSpellInfo()->AttributesEx7);
        return 1;
    }

    int GetAttributesCu(Eluna* E, ElunaSpellInfo* spellInfo)
    {
        E->Push(spellInfo->GetSpellInfo()->AttributesCu);
        return 1;
    }

    int GetStances(Eluna* E, ElunaSpellInfo* spellInfo)
    {
        E->Push(static_cast<uint32>(spellInfo->GetSpellInfo()->Stances));
        return 1;
    }

    int GetStancesNot(Eluna* E, ElunaSpellInfo* spellInfo)
    {
        E->Push(static_cast<uint32>(spellInfo->GetSpellInfo()->StancesNot));
        return 1;
    }

    int GetTargets(Eluna* E, ElunaSpellInfo* spellInfo)
    {
        E->Push(spellInfo->GetSpellInfo()->Targets);
        return 1;
    }

    int GetTargetCreatureType(Eluna* E, ElunaSpellInfo* spellInfo)
    {
        E->Push(spellInfo->GetSpellInfo()->TargetCreatureType);
        return 1;
    }

    int GetRequiresSpellFocus(Eluna* E, ElunaSpellInfo* spellInfo)
    {
        E->Push(spellInfo->GetSpellInfo()->RequiresSpellFocus);
        return 1;
    }

    int GetFacingCasterFlags(Eluna* E, ElunaSpellInfo* spellInfo)
    {
        E->Push(spellInfo->GetSpellInfo()->FacingCasterFlags);
        return 1;
    }

    int GetCasterAuraState(Eluna* E, ElunaSpellInfo* spellInfo)
    {
        E->Push(spellInfo->GetSpellInfo()->CasterAuraState);
        return 1;
    }

    int GetTargetAuraState(Eluna* E, ElunaSpellInfo* spellInfo)
    {
        E->Push(spellInfo->GetSpellInfo()->TargetAuraState);
        return 1;
    }

    int GetCasterAuraStateNot(Eluna* E, ElunaSpellInfo* spellInfo)
    {
        E->Push(spellInfo->GetSpellInfo()->CasterAuraStateNot);
        return 1;
    }

    int GetTargetAuraStateNot(Eluna* E, ElunaSpellInfo* spellInfo)
    {
        E->Push(spellInfo->GetSpellInfo()->TargetAuraStateNot);
        return 1;
    }

    int GetCasterAuraSpell(Eluna* E, ElunaSpellInfo* spellInfo)
    {
        E->Push(spellInfo->GetSpellInfo()->CasterAuraSpell);
        return 1;
    }

    int GetTargetAuraSpell(Eluna* E, ElunaSpellInfo* spellInfo)
    {
        E->Push(spellInfo->GetSpellInfo()->TargetAuraSpell);
        return 1;
    }

    int GetExcludeCasterAuraSpell(Eluna* E, ElunaSpellInfo* spellInfo)
    {
        E->Push(spellInfo->GetSpellInfo()->ExcludeCasterAuraSpell);
        return 1;
    }

    int GetExcludeTargetAuraSpell(Eluna* E, ElunaSpellInfo* spellInfo)
    {
        E->Push(spellInfo->GetSpellInfo()->ExcludeTargetAuraSpell);
        return 1;
    }

    int GetRecoveryTime(Eluna* E, ElunaSpellInfo* spellInfo)
    {
        E->Push(spellInfo->GetSpellInfo()->RecoveryTime);
        return 1;
    }

    int GetCategoryRecoveryTime(Eluna* E, ElunaSpellInfo* spellInfo)
    {
        E->Push(spellInfo->GetSpellInfo()->CategoryRecoveryTime);
        return 1;
    }

    int GetStartRecoveryCategory(Eluna* E, ElunaSpellInfo* spellInfo)
    {
        E->Push(spellInfo->GetSpellInfo()->StartRecoveryCategory);
        return 1;
    }

    int GetStartRecoveryTime(Eluna* E, ElunaSpellInfo* spellInfo)
    {
        E->Push(spellInfo->GetSpellInfo()->StartRecoveryTime);
        return 1;
    }

    int GetInterruptFlags(Eluna* E, ElunaSpellInfo* spellInfo)
    {
        E->Push(spellInfo->GetSpellInfo()->InterruptFlags);
        return 1;
    }

    int GetAuraInterruptFlags(Eluna* E, ElunaSpellInfo* spellInfo)
    {
        E->Push(spellInfo->GetSpellInfo()->AuraInterruptFlags);
        return 1;
    }

    int GetChannelInterruptFlags(Eluna* E, ElunaSpellInfo* spellInfo)
    {
        E->Push(spellInfo->GetSpellInfo()->ChannelInterruptFlags);
        return 1;
    }

    int GetProcFlags(Eluna* E, ElunaSpellInfo* spellInfo)
    {
        E->Push(spellInfo->GetSpellInfo()->ProcFlags);
        return 1;
    }

    int GetProcChance(Eluna* E, ElunaSpellInfo* spellInfo)
    {
        E->Push(spellInfo->GetSpellInfo()->ProcChance);
        return 1;
    }

    int GetProcCharges(Eluna* E, ElunaSpellInfo* spellInfo)
    {
        E->Push(spellInfo->GetSpellInfo()->ProcCharges);
        return 1;
    }

    int GetMaxLevel(Eluna* E, ElunaSpellInfo* spellInfo)
    {
        E->Push(spellInfo->GetSpellInfo()->MaxLevel);
        return 1;
    }

    int GetBaseLevel(Eluna* E, ElunaSpellInfo* spellInfo)
    {
        E->Push(spellInfo->GetSpellInfo()->BaseLevel);
        return 1;
    }

    int GetSpellLevel(Eluna* E, ElunaSpellInfo* spellInfo)
    {
        E->Push(spellInfo->GetSpellInfo()->SpellLevel);
        return 1;
    }

    int GetPowerType(Eluna* E, ElunaSpellInfo* spellInfo)
    {
        E->Push(spellInfo->GetSpellInfo()->PowerType);
        return 1;
    }

    int GetManaCost(Eluna* E, ElunaSpellInfo* spellInfo)
    {
        E->Push(spellInfo->GetSpellInfo()->ManaCost);
        return 1;
    }

    int GetManaCostPerlevel(Eluna* E, ElunaSpellInfo* spellInfo)
    {
        E->Push(spellInfo->GetSpellInfo()->ManaCostPerlevel);
        return 1;
    }

    int GetManaPerSecond(Eluna* E, ElunaSpellInfo* spellInfo)
    {
        E->Push(spellInfo->GetSpellInfo()->ManaPerSecond);
        return 1;
    }

    int GetManaPerSecondPerLevel(Eluna* E, ElunaSpellInfo* spellInfo)
    {
        E->Push(spellInfo->GetSpellInfo()->ManaPerSecondPerLevel);
        return 1;
    }

    int GetManaCostPercentage(Eluna* E, ElunaSpellInfo* spellInfo)
    {
        E->Push(spellInfo->GetSpellInfo()->ManaCostPercentage);
        return 1;
    }

    int GetRuneCostID(Eluna* E, ElunaSpellInfo* spellInfo)
    {
        E->Push(spellInfo->GetSpellInfo()->RuneCostID);
        return 1;
    }

    int GetSpeed(Eluna* E, ElunaSpellInfo* spellInfo)
    {
        E->Push(spellInfo->GetSpellInfo()->Speed);
        return 1;
    }

    int GetStackAmount(Eluna* E, ElunaSpellInfo* spellInfo)
    {
        E->Push(spellInfo->GetSpellInfo()->StackAmount);
        return 1;
    }

    int GetTotem(Eluna* E, ElunaSpellInfo* spellInfo)
    {
        uint32 index = E->CHECKVAL<uint32>(2);
        if (index >= 2)
            return luaL_argerror(E->L, 2, "index out of range (0-1)");
        E->Push(spellInfo->GetSpellInfo()->Totem[index]);
        return 1;
    }

    int GetReagent(Eluna* E, ElunaSpellInfo* spellInfo)
    {
        uint32 index = E->CHECKVAL<uint32>(2);
        if (index >= MAX_SPELL_REAGENTS)
            return luaL_argerror(E->L, 2, "index out of range (0-MAX_SPELL_REAGENTS-1)");
        E->Push(spellInfo->GetSpellInfo()->Reagent[index]);
        return 1;
    }

    int GetReagentCount(Eluna* E, ElunaSpellInfo* spellInfo)
    {
        uint32 index = E->CHECKVAL<uint32>(2);
        if (index >= MAX_SPELL_REAGENTS)
            return luaL_argerror(E->L, 2, "index out of range (0-MAX_SPELL_REAGENTS-1)");
        E->Push(spellInfo->GetSpellInfo()->ReagentCount[index]);
        return 1;
    }

    int GetEquippedItemClass(Eluna* E, ElunaSpellInfo* spellInfo)
    {
        E->Push(spellInfo->GetSpellInfo()->EquippedItemClass);
        return 1;
    }

    int GetEquippedItemSubClassMask(Eluna* E, ElunaSpellInfo* spellInfo)
    {
        E->Push(spellInfo->GetSpellInfo()->EquippedItemSubClassMask);
        return 1;
    }

    int GetEquippedItemInventoryTypeMask(Eluna* E, ElunaSpellInfo* spellInfo)
    {
        E->Push(spellInfo->GetSpellInfo()->EquippedItemInventoryTypeMask);
        return 1;
    }

    int GetTotemCategory(Eluna* E, ElunaSpellInfo* spellInfo)
    {
        uint32 index = E->CHECKVAL<uint32>(2);
        if (index >= 2)
            return luaL_argerror(E->L, 2, "index out of range (0-1)");
        E->Push(spellInfo->GetSpellInfo()->TotemCategory[index]);
        return 1;
    }

    int GetSpellVisual(Eluna* E, ElunaSpellInfo* spellInfo)
    {
        uint32 index = E->CHECKVAL<uint32>(2);
        if (index >= 2)
            return luaL_argerror(E->L, 2, "index out of range (0-1)");
        E->Push(spellInfo->GetSpellInfo()->SpellVisual[index]);
        return 1;
    }

    int GetSpellIconID(Eluna* E, ElunaSpellInfo* spellInfo)
    {
        E->Push(spellInfo->GetSpellInfo()->SpellIconID);
        return 1;
    }

    int GetActiveIconID(Eluna* E, ElunaSpellInfo* spellInfo)
    {
        E->Push(spellInfo->GetSpellInfo()->ActiveIconID);
        return 1;
    }

    int GetPriority(Eluna* E, ElunaSpellInfo* spellInfo)
    {
        E->Push(spellInfo->GetSpellInfo()->Priority);
        return 1;
    }

    int GetMaxTargetLevel(Eluna* E, ElunaSpellInfo* spellInfo)
    {
        E->Push(spellInfo->GetSpellInfo()->MaxTargetLevel);
        return 1;
    }

    int GetMaxAffectedTargets(Eluna* E, ElunaSpellInfo* spellInfo)
    {
        E->Push(spellInfo->GetSpellInfo()->MaxAffectedTargets);
        return 1;
    }

    int GetSpellFamilyName(Eluna* E, ElunaSpellInfo* spellInfo)
    {
        E->Push(spellInfo->GetSpellInfo()->SpellFamilyName);
        return 1;
    }

    int GetSpellFamilyFlags(Eluna* E, ElunaSpellInfo* spellInfo)
    {
        uint32 index = E->CHECKVAL<uint32>(2);
        if (index >= 3)
            return luaL_argerror(E->L, 2, "index out of range (0-2)");
        E->Push(spellInfo->GetSpellInfo()->SpellFamilyFlags[index]);
        return 1;
    }

    int GetDmgClass(Eluna* E, ElunaSpellInfo* spellInfo)
    {
        E->Push(spellInfo->GetSpellInfo()->DmgClass);
        return 1;
    }

    int GetPreventionType(Eluna* E, ElunaSpellInfo* spellInfo)
    {
        E->Push(spellInfo->GetSpellInfo()->PreventionType);
        return 1;
    }

    int GetAreaGroupId(Eluna* E, ElunaSpellInfo* spellInfo)
    {
        E->Push(spellInfo->GetSpellInfo()->AreaGroupId);
        return 1;
    }

    int GetSchoolMask(Eluna* E, ElunaSpellInfo* spellInfo)
    {
        E->Push(spellInfo->GetSpellInfo()->SchoolMask);
        return 1;
    }

    int GetDuration(Eluna* E, ElunaSpellInfo* spellInfo)
    {
        E->Push(spellInfo->GetSpellInfo()->GetDuration());
        return 1;
    }

    int GetMaxDuration(Eluna* E, ElunaSpellInfo* spellInfo)
    {
        E->Push(spellInfo->GetSpellInfo()->GetMaxDuration());
        return 1;
    }

    int GetMaxRange(Eluna* E, ElunaSpellInfo* spellInfo)
    {
        E->Push(spellInfo->GetSpellInfo()->GetMaxRange());
        return 1;
    }

    int GetMinRange(Eluna* E, ElunaSpellInfo* spellInfo)
    {
        E->Push(spellInfo->GetSpellInfo()->GetMinRange());
        return 1;
    }

    int GetMaxTicks(Eluna* E, ElunaSpellInfo* spellInfo)
    {
        E->Push(spellInfo->GetSpellInfo()->GetMaxTicks());
        return 1;
    }

    int GetCategory(Eluna* E, ElunaSpellInfo* spellInfo)
    {
        E->Push(spellInfo->GetSpellInfo()->GetCategory());
        return 1;
    }

    int GetRank(Eluna* E, ElunaSpellInfo* spellInfo)
    {
        E->Push(spellInfo->GetSpellInfo()->GetRank());
        return 1;
    }

    int GetAllEffectsMechanicMask(Eluna* E, ElunaSpellInfo* spellInfo)
    {
        E->Push(spellInfo->GetSpellInfo()->GetAllEffectsMechanicMask());
        return 1;
    }

    int GetAllowedMechanicMask(Eluna* E, ElunaSpellInfo* spellInfo)
    {
        E->Push(spellInfo->GetSpellInfo()->GetAllowedMechanicMask());
        return 1;
    }

    int GetExplicitTargetMask(Eluna* E, ElunaSpellInfo* spellInfo)
    {
        E->Push(spellInfo->GetSpellInfo()->GetExplicitTargetMask());
        return 1;
    }

    int GetAuraState(Eluna* E, ElunaSpellInfo* spellInfo)
    {
        E->Push(spellInfo->GetSpellInfo()->GetAuraState());
        return 1;
    }

    int GetSpellSpecific(Eluna* E, ElunaSpellInfo* spellInfo)
    {
        E->Push(spellInfo->GetSpellInfo()->GetSpellSpecific());
        return 1;
    }

    int GetAttackType(Eluna* E, ElunaSpellInfo* spellInfo)
    {
        E->Push(spellInfo->GetSpellInfo()->GetAttackType());
        return 1;
    }

    int GetEffectMechanicMask(Eluna* E, ElunaSpellInfo* spellInfo)
    {
        uint32 effIndex = E->CHECKVAL<uint32>(2);
        if (effIndex >= MAX_SPELL_EFFECTS)
            return luaL_argerror(E->L, 2, "effect index out of range");
        E->Push(spellInfo->GetSpellInfo()->GetEffectMechanicMask(static_cast<SpellEffIndex>(effIndex)));
        return 1;
    }

    int GetEffectMechanic(Eluna* E, ElunaSpellInfo* spellInfo)
    {
        uint32 effIndex = E->CHECKVAL<uint32>(2);
        if (effIndex >= MAX_SPELL_EFFECTS)
            return luaL_argerror(E->L, 2, "effect index out of range");
        E->Push(spellInfo->GetSpellInfo()->GetEffectMechanic(static_cast<SpellEffIndex>(effIndex)));
        return 1;
    }

    int GetDiminishingReturnsGroupForSpell(Eluna* E, ElunaSpellInfo* spellInfo)
    {
        bool triggered = E->CHECKVAL<bool>(2);
        E->Push(spellInfo->GetSpellInfo()->GetDiminishingReturnsGroupForSpell(triggered));
        return 1;
    }

    int GetDiminishingReturnsGroupType(Eluna* E, ElunaSpellInfo* spellInfo)
    {
        bool triggered = E->CHECKVAL<bool>(2);
        E->Push(spellInfo->GetSpellInfo()->GetDiminishingReturnsGroupType(triggered));
        return 1;
    }

    int GetDiminishingReturnsMaxLevel(Eluna* E, ElunaSpellInfo* spellInfo)
    {
        bool triggered = E->CHECKVAL<bool>(2);
        E->Push(spellInfo->GetSpellInfo()->GetDiminishingReturnsMaxLevel(triggered));
        return 1;
    }

    int GetDiminishingReturnsLimitDuration(Eluna* E, ElunaSpellInfo* spellInfo)
    {
        bool triggered = E->CHECKVAL<bool>(2);
        E->Push(spellInfo->GetSpellInfo()->GetDiminishingReturnsLimitDuration(triggered));
        return 1;
    }

    int CalcCastTime(Eluna* E, ElunaSpellInfo* spellInfo)
    {
        E->Push(spellInfo->GetSpellInfo()->CalcCastTime());
        return 1;
    }

    int IsPassive(Eluna* E, ElunaSpellInfo* spellInfo)
    {
        E->Push(spellInfo->GetSpellInfo()->IsPassive());
        return 1;
    }

    int IsAutocastable(Eluna* E, ElunaSpellInfo* spellInfo)
    {
        E->Push(spellInfo->GetSpellInfo()->IsAutocastable());
        return 1;
    }

    int IsStackableWithRanks(Eluna* E, ElunaSpellInfo* spellInfo)
    {
        E->Push(spellInfo->GetSpellInfo()->IsStackableWithRanks());
        return 1;
    }

    int IsPassiveStackableWithRanks(Eluna* E, ElunaSpellInfo* spellInfo)
    {
        E->Push(spellInfo->GetSpellInfo()->IsPassiveStackableWithRanks());
        return 1;
    }

    int IsMultiSlotAura(Eluna* E, ElunaSpellInfo* spellInfo)
    {
        E->Push(spellInfo->GetSpellInfo()->IsMultiSlotAura());
        return 1;
    }

    int IsStackableOnOneSlotWithDifferentCasters(Eluna* E, ElunaSpellInfo* spellInfo)
    {
        E->Push(spellInfo->GetSpellInfo()->IsStackableOnOneSlotWithDifferentCasters());
        return 1;
    }

    int IsCooldownStartedOnEvent(Eluna* E, ElunaSpellInfo* spellInfo)
    {
        E->Push(spellInfo->GetSpellInfo()->IsCooldownStartedOnEvent());
        return 1;
    }

    int IsDeathPersistent(Eluna* E, ElunaSpellInfo* spellInfo)
    {
        E->Push(spellInfo->GetSpellInfo()->IsDeathPersistent());
        return 1;
    }

    int IsRequiringDeadTarget(Eluna* E, ElunaSpellInfo* spellInfo)
    {
        E->Push(spellInfo->GetSpellInfo()->IsRequiringDeadTarget());
        return 1;
    }

    int IsAllowingDeadTarget(Eluna* E, ElunaSpellInfo* spellInfo)
    {
        E->Push(spellInfo->GetSpellInfo()->IsAllowingDeadTarget());
        return 1;
    }

    int IsGroupBuff(Eluna* E, ElunaSpellInfo* spellInfo)
    {
        E->Push(spellInfo->GetSpellInfo()->IsGroupBuff());
        return 1;
    }

    int CanBeUsedInCombat(Eluna* E, ElunaSpellInfo* spellInfo)
    {
        E->Push(spellInfo->GetSpellInfo()->CanBeUsedInCombat());
        return 1;
    }

    int IsPositive(Eluna* E, ElunaSpellInfo* spellInfo)
    {
        E->Push(spellInfo->GetSpellInfo()->IsPositive());
        return 1;
    }

    int IsPositiveEffect(Eluna* E, ElunaSpellInfo* spellInfo)
    {
        uint8 effIndex = E->CHECKVAL<uint8>(2);
        if (effIndex >= MAX_SPELL_EFFECTS)
            return luaL_argerror(E->L, 2, "effect index out of range");
        E->Push(spellInfo->GetSpellInfo()->IsPositiveEffect(effIndex));
        return 1;
    }

    int IsChanneled(Eluna* E, ElunaSpellInfo* spellInfo)
    {
        E->Push(spellInfo->GetSpellInfo()->IsChanneled());
        return 1;
    }

    int IsMoveAllowedChannel(Eluna* E, ElunaSpellInfo* spellInfo)
    {
        E->Push(spellInfo->GetSpellInfo()->IsMoveAllowedChannel());
        return 1;
    }

    int NeedsComboPoints(Eluna* E, ElunaSpellInfo* spellInfo)
    {
        E->Push(spellInfo->GetSpellInfo()->NeedsComboPoints());
        return 1;
    }

    int IsNextMeleeSwingSpell(Eluna* E, ElunaSpellInfo* spellInfo)
    {
        E->Push(spellInfo->GetSpellInfo()->IsNextMeleeSwingSpell());
        return 1;
    }

    int IsBreakingStealth(Eluna* E, ElunaSpellInfo* spellInfo)
    {
        E->Push(spellInfo->GetSpellInfo()->IsBreakingStealth());
        return 1;
    }

    int IsRangedWeaponSpell(Eluna* E, ElunaSpellInfo* spellInfo)
    {
        E->Push(spellInfo->GetSpellInfo()->IsRangedWeaponSpell());
        return 1;
    }

    int IsAutoRepeatRangedSpell(Eluna* E, ElunaSpellInfo* spellInfo)
    {
        E->Push(spellInfo->GetSpellInfo()->IsAutoRepeatRangedSpell());
        return 1;
    }

    int HasInitialAggro(Eluna* E, ElunaSpellInfo* spellInfo)
    {
        E->Push(spellInfo->GetSpellInfo()->HasInitialAggro());
        return 1;
    }

    int IsRanked(Eluna* E, ElunaSpellInfo* spellInfo)
    {
        E->Push(spellInfo->GetSpellInfo()->IsRanked());
        return 1;
    }

    int IsAffectingArea(Eluna* E, ElunaSpellInfo* spellInfo)
    {
        E->Push(spellInfo->GetSpellInfo()->IsAffectingArea());
        return 1;
    }

    int IsTargetingArea(Eluna* E, ElunaSpellInfo* spellInfo)
    {
        E->Push(spellInfo->GetSpellInfo()->IsTargetingArea());
        return 1;
    }

    int NeedsExplicitUnitTarget(Eluna* E, ElunaSpellInfo* spellInfo)
    {
        E->Push(spellInfo->GetSpellInfo()->NeedsExplicitUnitTarget());
        return 1;
    }

    int IsSelfCast(Eluna* E, ElunaSpellInfo* spellInfo)
    {
        E->Push(spellInfo->GetSpellInfo()->IsSelfCast());
        return 1;
    }

    int IsSingleTarget(Eluna* E, ElunaSpellInfo* spellInfo)
    {
        E->Push(spellInfo->GetSpellInfo()->IsSingleTarget());
        return 1;
    }

    int IsExplicitDiscovery(Eluna* E, ElunaSpellInfo* spellInfo)
    {
        E->Push(spellInfo->GetSpellInfo()->IsExplicitDiscovery());
        return 1;
    }

    int IsLootCrafting(Eluna* E, ElunaSpellInfo* spellInfo)
    {
        E->Push(spellInfo->GetSpellInfo()->IsLootCrafting());
        return 1;
    }

    int IsProfessionOrRiding(Eluna* E, ElunaSpellInfo* spellInfo)
    {
        E->Push(spellInfo->GetSpellInfo()->IsProfessionOrRiding());
        return 1;
    }

    int IsProfession(Eluna* E, ElunaSpellInfo* spellInfo)
    {
        E->Push(spellInfo->GetSpellInfo()->IsProfession());
        return 1;
    }

    int IsPrimaryProfession(Eluna* E, ElunaSpellInfo* spellInfo)
    {
        E->Push(spellInfo->GetSpellInfo()->IsPrimaryProfession());
        return 1;
    }

    int IsPrimaryProfessionFirstRank(Eluna* E, ElunaSpellInfo* spellInfo)
    {
        E->Push(spellInfo->GetSpellInfo()->IsPrimaryProfessionFirstRank());
        return 1;
    }

    int IsAbilityLearnedWithProfession(Eluna* E, ElunaSpellInfo* spellInfo)
    {
        E->Push(spellInfo->GetSpellInfo()->IsAbilityLearnedWithProfession());
        return 1;
    }

    int IsAffectedBySpellMods(Eluna* E, ElunaSpellInfo* spellInfo)
    {
        E->Push(spellInfo->GetSpellInfo()->IsAffectedBySpellMods());
        return 1;
    }

    int HasEffect(Eluna* E, ElunaSpellInfo* spellInfo)
    {
        SpellEffects effect = static_cast<SpellEffects>(E->CHECKVAL<uint32>(2));
        E->Push(spellInfo->GetSpellInfo()->HasEffect(effect));
        return 1;
    }

    int HasAura(Eluna* E, ElunaSpellInfo* spellInfo)
    {
        AuraType aura = static_cast<AuraType>(E->CHECKVAL<uint32>(2));
        E->Push(spellInfo->GetSpellInfo()->HasAura(aura));
        return 1;
    }

    int HasAreaAuraEffect(Eluna* E, ElunaSpellInfo* spellInfo)
    {
        E->Push(spellInfo->GetSpellInfo()->HasAreaAuraEffect());
        return 1;
    }

    int HasOnlyDamageEffects(Eluna* E, ElunaSpellInfo* spellInfo)
    {
        E->Push(spellInfo->GetSpellInfo()->HasOnlyDamageEffects());
        return 1;
    }

    int IsAffected(Eluna* E, ElunaSpellInfo* spellInfo)
    {
        uint32 familyName = E->CHECKVAL<uint32>(2);
        uint32 f0 = E->CHECKVAL<uint32>(3);
        uint32 f1 = E->CHECKVAL<uint32>(4);
        uint32 f2 = E->CHECKVAL<uint32>(5);
        E->Push(spellInfo->GetSpellInfo()->IsAffected(familyName, flag96(f0, f1, f2)));
        return 1;
    }

    int IsAffectedBySpellMod(Eluna* E, ElunaSpellInfo* spellInfo)
    {
        SpellModifier* mod = E->CHECKOBJ<SpellModifier>(2);
        E->Push(spellInfo->GetSpellInfo()->IsAffectedBySpellMod(mod));
        return 1;
    }

    int IsRankOf(Eluna* E, ElunaSpellInfo* spellInfo)
    {
        ElunaSpellInfo* other = E->CHECKOBJ<ElunaSpellInfo>(2);
        E->Push(spellInfo->GetSpellInfo()->IsRankOf(other->GetSpellInfo()));
        return 1;
    }

    int IsDifferentRankOf(Eluna* E, ElunaSpellInfo* spellInfo)
    {
        ElunaSpellInfo* other = E->CHECKOBJ<ElunaSpellInfo>(2);
        E->Push(spellInfo->GetSpellInfo()->IsDifferentRankOf(other->GetSpellInfo()));
        return 1;
    }

    int IsHighRankOf(Eluna* E, ElunaSpellInfo* spellInfo)
    {
        ElunaSpellInfo* other = E->CHECKOBJ<ElunaSpellInfo>(2);
        E->Push(spellInfo->GetSpellInfo()->IsHighRankOf(other->GetSpellInfo()));
        return 1;
    }

    int CanPierceImmuneAura(Eluna* E, ElunaSpellInfo* spellInfo)
    {
        ElunaSpellInfo* other = E->CHECKOBJ<ElunaSpellInfo>(2);
        E->Push(spellInfo->GetSpellInfo()->CanPierceImmuneAura(other->GetSpellInfo()));
        return 1;
    }

    int CanDispelAura(Eluna* E, ElunaSpellInfo* spellInfo)
    {
        ElunaSpellInfo* other = E->CHECKOBJ<ElunaSpellInfo>(2);
        E->Push(spellInfo->GetSpellInfo()->CanDispelAura(other->GetSpellInfo()));
        return 1;
    }

    int IsAuraExclusiveBySpecificWith(Eluna* E, ElunaSpellInfo* spellInfo)
    {
        ElunaSpellInfo* other = E->CHECKOBJ<ElunaSpellInfo>(2);
        E->Push(spellInfo->GetSpellInfo()->IsAuraExclusiveBySpecificWith(other->GetSpellInfo()));
        return 1;
    }

    int IsAuraExclusiveBySpecificPerCasterWith(Eluna* E, ElunaSpellInfo* spellInfo)
    {
        ElunaSpellInfo* other = E->CHECKOBJ<ElunaSpellInfo>(2);
        E->Push(spellInfo->GetSpellInfo()->IsAuraExclusiveBySpecificPerCasterWith(other->GetSpellInfo()));
        return 1;
    }

    int IsItemFitToSpellRequirements(Eluna* E, ElunaSpellInfo* spellInfo)
    {
        Item* item = E->CHECKOBJ<Item>(2);
        E->Push(spellInfo->GetSpellInfo()->IsItemFitToSpellRequirements(item));
        return 1;
    }

    int CheckTarget(Eluna* E, ElunaSpellInfo* spellInfo)
    {
        WorldObject* caster = E->CHECKOBJ<WorldObject>(2);
        WorldObject* target = E->CHECKOBJ<WorldObject>(3);
        E->Push(spellInfo->GetSpellInfo()->CheckTarget(caster, target));
        return 1;
    }

    int CheckTargetCreatureType(Eluna* E, ElunaSpellInfo* spellInfo)
    {
        Unit* target = E->CHECKOBJ<Unit>(2);
        E->Push(spellInfo->GetSpellInfo()->CheckTargetCreatureType(target));
        return 1;
    }

    int SpellCancelsAuraEffect(Eluna* E, ElunaSpellInfo* spellInfo)
    {
        AuraEffect* aurEff = E->CHECKOBJ<AuraEffect>(2);
        E->Push(spellInfo->GetSpellInfo()->SpellCancelsAuraEffect(aurEff));
        return 1;
    }

    int CanSpellProvideImmunityAgainstAura(Eluna* E, ElunaSpellInfo* spellInfo)
    {
        ElunaSpellInfo* other = E->CHECKOBJ<ElunaSpellInfo>(2);
        E->Push(spellInfo->GetSpellInfo()->CanSpellProvideImmunityAgainstAura(other->GetSpellInfo()));
        return 1;
    }

    int IsAbilityOfSkillType(Eluna* E, ElunaSpellInfo* spellInfo)
    {
        uint32 skillType = E->CHECKVAL<uint32>(2);
        E->Push(spellInfo->GetSpellInfo()->IsAbilityOfSkillType(skillType));
        return 1;
    }

    int NeedsToBeTriggeredByCaster(Eluna* E, ElunaSpellInfo* spellInfo)
    {
        ElunaSpellInfo* triggeringSpell = E->CHECKOBJ<ElunaSpellInfo>(2);
        E->Push(spellInfo->GetSpellInfo()->NeedsToBeTriggeredByCaster(triggeringSpell->GetSpellInfo()));
        return 1;
    }

    int GetSpellMechanicMaskByEffectMask(Eluna* E, ElunaSpellInfo* spellInfo)
    {
        uint32 effectMask = E->CHECKVAL<uint32>(2);
        E->Push(spellInfo->GetSpellInfo()->GetSpellMechanicMaskByEffectMask(effectMask));
        return 1;
    }

    int GetEffectIndex(Eluna* E, ElunaSpellInfo* spellInfo)
    {
        uint32 effIndex = E->CHECKVAL<uint32>(2);
        if (effIndex >= MAX_SPELL_EFFECTS)
            return luaL_argerror(E->L, 2, "effect index out of range");
        E->Push(static_cast<uint32>(spellInfo->GetSpellInfo()->GetEffect(static_cast<SpellEffIndex>(effIndex)).EffectIndex));
        return 1;
    }

    int GetEffectType(Eluna* E, ElunaSpellInfo* spellInfo)
    {
        uint32 effIndex = E->CHECKVAL<uint32>(2);
        if (effIndex >= MAX_SPELL_EFFECTS)
            return luaL_argerror(E->L, 2, "effect index out of range");
        E->Push(static_cast<uint32>(spellInfo->GetSpellInfo()->GetEffect(static_cast<SpellEffIndex>(effIndex)).Effect));
        return 1;
    }

    int GetEffectApplyAuraName(Eluna* E, ElunaSpellInfo* spellInfo)
    {
        uint32 effIndex = E->CHECKVAL<uint32>(2);
        if (effIndex >= MAX_SPELL_EFFECTS)
            return luaL_argerror(E->L, 2, "effect index out of range");
        E->Push(static_cast<uint32>(spellInfo->GetSpellInfo()->GetEffect(static_cast<SpellEffIndex>(effIndex)).ApplyAuraName));
        return 1;
    }

    int GetEffectAmplitude(Eluna* E, ElunaSpellInfo* spellInfo)
    {
        uint32 effIndex = E->CHECKVAL<uint32>(2);
        if (effIndex >= MAX_SPELL_EFFECTS)
            return luaL_argerror(E->L, 2, "effect index out of range");
        E->Push(spellInfo->GetSpellInfo()->GetEffect(static_cast<SpellEffIndex>(effIndex)).Amplitude);
        return 1;
    }

    int GetEffectDieSides(Eluna* E, ElunaSpellInfo* spellInfo)
    {
        uint32 effIndex = E->CHECKVAL<uint32>(2);
        if (effIndex >= MAX_SPELL_EFFECTS)
            return luaL_argerror(E->L, 2, "effect index out of range");
        E->Push(spellInfo->GetSpellInfo()->GetEffect(static_cast<SpellEffIndex>(effIndex)).DieSides);
        return 1;
    }

    int GetEffectRealPointsPerLevel(Eluna* E, ElunaSpellInfo* spellInfo)
    {
        uint32 effIndex = E->CHECKVAL<uint32>(2);
        if (effIndex >= MAX_SPELL_EFFECTS)
            return luaL_argerror(E->L, 2, "effect index out of range");
        E->Push(spellInfo->GetSpellInfo()->GetEffect(static_cast<SpellEffIndex>(effIndex)).RealPointsPerLevel);
        return 1;
    }

    int GetEffectBasePoints(Eluna* E, ElunaSpellInfo* spellInfo)
    {
        uint32 effIndex = E->CHECKVAL<uint32>(2);
        if (effIndex >= MAX_SPELL_EFFECTS)
            return luaL_argerror(E->L, 2, "effect index out of range");
        E->Push(spellInfo->GetSpellInfo()->GetEffect(static_cast<SpellEffIndex>(effIndex)).BasePoints);
        return 1;
    }

    int GetEffectPointsPerComboPoint(Eluna* E, ElunaSpellInfo* spellInfo)
    {
        uint32 effIndex = E->CHECKVAL<uint32>(2);
        if (effIndex >= MAX_SPELL_EFFECTS)
            return luaL_argerror(E->L, 2, "effect index out of range");
        E->Push(spellInfo->GetSpellInfo()->GetEffect(static_cast<SpellEffIndex>(effIndex)).PointsPerComboPoint);
        return 1;
    }

    int GetEffectValueMultiplier(Eluna* E, ElunaSpellInfo* spellInfo)
    {
        uint32 effIndex = E->CHECKVAL<uint32>(2);
        if (effIndex >= MAX_SPELL_EFFECTS)
            return luaL_argerror(E->L, 2, "effect index out of range");
        E->Push(spellInfo->GetSpellInfo()->GetEffect(static_cast<SpellEffIndex>(effIndex)).ValueMultiplier);
        return 1;
    }

    int GetEffectDamageMultiplier(Eluna* E, ElunaSpellInfo* spellInfo)
    {
        uint32 effIndex = E->CHECKVAL<uint32>(2);
        if (effIndex >= MAX_SPELL_EFFECTS)
            return luaL_argerror(E->L, 2, "effect index out of range");
        E->Push(spellInfo->GetSpellInfo()->GetEffect(static_cast<SpellEffIndex>(effIndex)).DamageMultiplier);
        return 1;
    }

    int GetEffectBonusMultiplier(Eluna* E, ElunaSpellInfo* spellInfo)
    {
        uint32 effIndex = E->CHECKVAL<uint32>(2);
        if (effIndex >= MAX_SPELL_EFFECTS)
            return luaL_argerror(E->L, 2, "effect index out of range");
        E->Push(spellInfo->GetSpellInfo()->GetEffect(static_cast<SpellEffIndex>(effIndex)).BonusMultiplier);
        return 1;
    }

    int GetEffectMiscValue(Eluna* E, ElunaSpellInfo* spellInfo)
    {
        uint32 effIndex = E->CHECKVAL<uint32>(2);
        if (effIndex >= MAX_SPELL_EFFECTS)
            return luaL_argerror(E->L, 2, "effect index out of range");
        E->Push(spellInfo->GetSpellInfo()->GetEffect(static_cast<SpellEffIndex>(effIndex)).MiscValue);
        return 1;
    }

    int GetEffectMiscValueB(Eluna* E, ElunaSpellInfo* spellInfo)
    {
        uint32 effIndex = E->CHECKVAL<uint32>(2);
        if (effIndex >= MAX_SPELL_EFFECTS)
            return luaL_argerror(E->L, 2, "effect index out of range");
        E->Push(spellInfo->GetSpellInfo()->GetEffect(static_cast<SpellEffIndex>(effIndex)).MiscValueB);
        return 1;
    }

    int GetEffectChainTarget(Eluna* E, ElunaSpellInfo* spellInfo)
    {
        uint32 effIndex = E->CHECKVAL<uint32>(2);
        if (effIndex >= MAX_SPELL_EFFECTS)
            return luaL_argerror(E->L, 2, "effect index out of range");
        E->Push(spellInfo->GetSpellInfo()->GetEffect(static_cast<SpellEffIndex>(effIndex)).ChainTarget);
        return 1;
    }

    int GetEffectItemType(Eluna* E, ElunaSpellInfo* spellInfo)
    {
        uint32 effIndex = E->CHECKVAL<uint32>(2);
        if (effIndex >= MAX_SPELL_EFFECTS)
            return luaL_argerror(E->L, 2, "effect index out of range");
        E->Push(spellInfo->GetSpellInfo()->GetEffect(static_cast<SpellEffIndex>(effIndex)).ItemType);
        return 1;
    }

    int GetEffectTriggerSpell(Eluna* E, ElunaSpellInfo* spellInfo)
    {
        uint32 effIndex = E->CHECKVAL<uint32>(2);
        if (effIndex >= MAX_SPELL_EFFECTS)
            return luaL_argerror(E->L, 2, "effect index out of range");
        E->Push(spellInfo->GetSpellInfo()->GetEffect(static_cast<SpellEffIndex>(effIndex)).TriggerSpell);
        return 1;
    }

    // SpellClassMask is flag96, exposed as index 0-2
    int GetEffectSpellClassMask(Eluna* E, ElunaSpellInfo* spellInfo)
    {
        uint32 effIndex = E->CHECKVAL<uint32>(2);
        if (effIndex >= MAX_SPELL_EFFECTS)
            return luaL_argerror(E->L, 2, "effect index out of range");
        uint32 maskIndex = E->CHECKVAL<uint32>(3);
        if (maskIndex >= 3)
            return luaL_argerror(E->L, 3, "mask index out of range (0-2)");
        E->Push(spellInfo->GetSpellInfo()->GetEffect(static_cast<SpellEffIndex>(effIndex)).SpellClassMask[maskIndex]);
        return 1;
    }

    int GetEffectCalcValue(Eluna* E, ElunaSpellInfo* spellInfo)
    {
        uint32 effIndex = E->CHECKVAL<uint32>(2);
        if (effIndex >= MAX_SPELL_EFFECTS)
            return luaL_argerror(E->L, 2, "effect index out of range");
        E->Push(spellInfo->GetSpellInfo()->GetEffect(static_cast<SpellEffIndex>(effIndex)).CalcValue());
        return 1;
    }

    int GetEffectCalcRadius(Eluna* E, ElunaSpellInfo* spellInfo)
    {
        uint32 effIndex = E->CHECKVAL<uint32>(2);
        if (effIndex >= MAX_SPELL_EFFECTS)
            return luaL_argerror(E->L, 2, "effect index out of range");
        E->Push(spellInfo->GetSpellInfo()->GetEffect(static_cast<SpellEffIndex>(effIndex)).CalcRadius());
        return 1;
    }

    int GetEffectHasRadius(Eluna* E, ElunaSpellInfo* spellInfo)
    {
        uint32 effIndex = E->CHECKVAL<uint32>(2);
        if (effIndex >= MAX_SPELL_EFFECTS)
            return luaL_argerror(E->L, 2, "effect index out of range");
        E->Push(spellInfo->GetSpellInfo()->GetEffect(static_cast<SpellEffIndex>(effIndex)).HasRadius());
        return 1;
    }

    int GetEffectProvidedTargetMask(Eluna* E, ElunaSpellInfo* spellInfo)
    {
        uint32 effIndex = E->CHECKVAL<uint32>(2);
        if (effIndex >= MAX_SPELL_EFFECTS)
            return luaL_argerror(E->L, 2, "effect index out of range");
        E->Push(spellInfo->GetSpellInfo()->GetEffect(static_cast<SpellEffIndex>(effIndex)).GetProvidedTargetMask());
        return 1;
    }

    int GetEffectImplicitTargetType(Eluna* E, ElunaSpellInfo* spellInfo)
    {
        uint32 effIndex = E->CHECKVAL<uint32>(2);
        if (effIndex >= MAX_SPELL_EFFECTS)
            return luaL_argerror(E->L, 2, "effect index out of range");
        E->Push(static_cast<uint32>(spellInfo->GetSpellInfo()->GetEffect(static_cast<SpellEffIndex>(effIndex)).GetImplicitTargetType()));
        return 1;
    }

    int GetEffectUsedTargetObjectType(Eluna* E, ElunaSpellInfo* spellInfo)
    {
        uint32 effIndex = E->CHECKVAL<uint32>(2);
        if (effIndex >= MAX_SPELL_EFFECTS)
            return luaL_argerror(E->L, 2, "effect index out of range");
        E->Push(static_cast<uint32>(spellInfo->GetSpellInfo()->GetEffect(static_cast<SpellEffIndex>(effIndex)).GetUsedTargetObjectType()));
        return 1;
    }

    int EffectIsEffect(Eluna* E, ElunaSpellInfo* spellInfo)
    {
        uint32 effIndex = E->CHECKVAL<uint32>(2);
        if (effIndex >= MAX_SPELL_EFFECTS)
            return luaL_argerror(E->L, 2, "effect index out of range");
        E->Push(spellInfo->GetSpellInfo()->GetEffect(static_cast<SpellEffIndex>(effIndex)).IsEffect());
        return 1;
    }

    int EffectIsEffectType(Eluna* E, ElunaSpellInfo* spellInfo)
    {
        uint32 effIndex = E->CHECKVAL<uint32>(2);
        if (effIndex >= MAX_SPELL_EFFECTS)
            return luaL_argerror(E->L, 2, "effect index out of range");
        SpellEffects effect = static_cast<SpellEffects>(E->CHECKVAL<uint32>(3));
        E->Push(spellInfo->GetSpellInfo()->GetEffect(static_cast<SpellEffIndex>(effIndex)).IsEffect(effect));
        return 1;
    }

    int EffectIsAura(Eluna* E, ElunaSpellInfo* spellInfo)
    {
        uint32 effIndex = E->CHECKVAL<uint32>(2);
        if (effIndex >= MAX_SPELL_EFFECTS)
            return luaL_argerror(E->L, 2, "effect index out of range");
        E->Push(spellInfo->GetSpellInfo()->GetEffect(static_cast<SpellEffIndex>(effIndex)).IsAura());
        return 1;
    }

    int EffectIsAuraType(Eluna* E, ElunaSpellInfo* spellInfo)
    {
        uint32 effIndex = E->CHECKVAL<uint32>(2);
        if (effIndex >= MAX_SPELL_EFFECTS)
            return luaL_argerror(E->L, 2, "effect index out of range");
        AuraType aura = static_cast<AuraType>(E->CHECKVAL<uint32>(3));
        E->Push(spellInfo->GetSpellInfo()->GetEffect(static_cast<SpellEffIndex>(effIndex)).IsAura(aura));
        return 1;
    }

    int EffectIsTargetingArea(Eluna* E, ElunaSpellInfo* spellInfo)
    {
        uint32 effIndex = E->CHECKVAL<uint32>(2);
        if (effIndex >= MAX_SPELL_EFFECTS)
            return luaL_argerror(E->L, 2, "effect index out of range");
        E->Push(spellInfo->GetSpellInfo()->GetEffect(static_cast<SpellEffIndex>(effIndex)).IsTargetingArea());
        return 1;
    }

    int EffectIsAreaAuraEffect(Eluna* E, ElunaSpellInfo* spellInfo)
    {
        uint32 effIndex = E->CHECKVAL<uint32>(2);
        if (effIndex >= MAX_SPELL_EFFECTS)
            return luaL_argerror(E->L, 2, "effect index out of range");
        E->Push(spellInfo->GetSpellInfo()->GetEffect(static_cast<SpellEffIndex>(effIndex)).IsAreaAuraEffect());
        return 1;
    }

    int EffectIsUnitOwnedAuraEffect(Eluna* E, ElunaSpellInfo* spellInfo)
    {
        uint32 effIndex = E->CHECKVAL<uint32>(2);
        if (effIndex >= MAX_SPELL_EFFECTS)
            return luaL_argerror(E->L, 2, "effect index out of range");
        E->Push(spellInfo->GetSpellInfo()->GetEffect(static_cast<SpellEffIndex>(effIndex)).IsUnitOwnedAuraEffect());
        return 1;
    }

    // SpellImplicitTargetInfo - TargetA
    int GetEffectTargetATarget(Eluna* E, ElunaSpellInfo* spellInfo)
    {
        uint32 effIndex = E->CHECKVAL<uint32>(2);
        if (effIndex >= MAX_SPELL_EFFECTS)
            return luaL_argerror(E->L, 2, "effect index out of range");
        E->Push(static_cast<uint32>(spellInfo->GetSpellInfo()->GetEffect(static_cast<SpellEffIndex>(effIndex)).TargetA.GetTarget()));
        return 1;
    }

    int GetEffectTargetASelectionCategory(Eluna* E, ElunaSpellInfo* spellInfo)
    {
        uint32 effIndex = E->CHECKVAL<uint32>(2);
        if (effIndex >= MAX_SPELL_EFFECTS)
            return luaL_argerror(E->L, 2, "effect index out of range");
        E->Push(static_cast<uint32>(spellInfo->GetSpellInfo()->GetEffect(static_cast<SpellEffIndex>(effIndex)).TargetA.GetSelectionCategory()));
        return 1;
    }

    int GetEffectTargetAReferenceType(Eluna* E, ElunaSpellInfo* spellInfo)
    {
        uint32 effIndex = E->CHECKVAL<uint32>(2);
        if (effIndex >= MAX_SPELL_EFFECTS)
            return luaL_argerror(E->L, 2, "effect index out of range");
        E->Push(static_cast<uint32>(spellInfo->GetSpellInfo()->GetEffect(static_cast<SpellEffIndex>(effIndex)).TargetA.GetReferenceType()));
        return 1;
    }

    int GetEffectTargetAObjectType(Eluna* E, ElunaSpellInfo* spellInfo)
    {
        uint32 effIndex = E->CHECKVAL<uint32>(2);
        if (effIndex >= MAX_SPELL_EFFECTS)
            return luaL_argerror(E->L, 2, "effect index out of range");
        E->Push(static_cast<uint32>(spellInfo->GetSpellInfo()->GetEffect(static_cast<SpellEffIndex>(effIndex)).TargetA.GetObjectType()));
        return 1;
    }

    int GetEffectTargetACheckType(Eluna* E, ElunaSpellInfo* spellInfo)
    {
        uint32 effIndex = E->CHECKVAL<uint32>(2);
        if (effIndex >= MAX_SPELL_EFFECTS)
            return luaL_argerror(E->L, 2, "effect index out of range");
        E->Push(static_cast<uint32>(spellInfo->GetSpellInfo()->GetEffect(static_cast<SpellEffIndex>(effIndex)).TargetA.GetCheckType()));
        return 1;
    }

    int GetEffectTargetADirectionType(Eluna* E, ElunaSpellInfo* spellInfo)
    {
        uint32 effIndex = E->CHECKVAL<uint32>(2);
        if (effIndex >= MAX_SPELL_EFFECTS)
            return luaL_argerror(E->L, 2, "effect index out of range");
        E->Push(static_cast<uint32>(spellInfo->GetSpellInfo()->GetEffect(static_cast<SpellEffIndex>(effIndex)).TargetA.GetDirectionType()));
        return 1;
    }

    int GetEffectTargetAIsArea(Eluna* E, ElunaSpellInfo* spellInfo)
    {
        uint32 effIndex = E->CHECKVAL<uint32>(2);
        if (effIndex >= MAX_SPELL_EFFECTS)
            return luaL_argerror(E->L, 2, "effect index out of range");
        E->Push(spellInfo->GetSpellInfo()->GetEffect(static_cast<SpellEffIndex>(effIndex)).TargetA.IsArea());
        return 1;
    }

    int GetEffectTargetADirectionAngle(Eluna* E, ElunaSpellInfo* spellInfo)
    {
        uint32 effIndex = E->CHECKVAL<uint32>(2);
        if (effIndex >= MAX_SPELL_EFFECTS)
            return luaL_argerror(E->L, 2, "effect index out of range");
        E->Push(spellInfo->GetSpellInfo()->GetEffect(static_cast<SpellEffIndex>(effIndex)).TargetA.CalcDirectionAngle());
        return 1;
    }

    // SpellImplicitTargetInfo - TargetB
    int GetEffectTargetBTarget(Eluna* E, ElunaSpellInfo* spellInfo)
    {
        uint32 effIndex = E->CHECKVAL<uint32>(2);
        if (effIndex >= MAX_SPELL_EFFECTS)
            return luaL_argerror(E->L, 2, "effect index out of range");
        E->Push(static_cast<uint32>(spellInfo->GetSpellInfo()->GetEffect(static_cast<SpellEffIndex>(effIndex)).TargetB.GetTarget()));
        return 1;
    }

    int GetEffectTargetBSelectionCategory(Eluna* E, ElunaSpellInfo* spellInfo)
    {
        uint32 effIndex = E->CHECKVAL<uint32>(2);
        if (effIndex >= MAX_SPELL_EFFECTS)
            return luaL_argerror(E->L, 2, "effect index out of range");
        E->Push(static_cast<uint32>(spellInfo->GetSpellInfo()->GetEffect(static_cast<SpellEffIndex>(effIndex)).TargetB.GetSelectionCategory()));
        return 1;
    }

    int GetEffectTargetBReferenceType(Eluna* E, ElunaSpellInfo* spellInfo)
    {
        uint32 effIndex = E->CHECKVAL<uint32>(2);
        if (effIndex >= MAX_SPELL_EFFECTS)
            return luaL_argerror(E->L, 2, "effect index out of range");
        E->Push(static_cast<uint32>(spellInfo->GetSpellInfo()->GetEffect(static_cast<SpellEffIndex>(effIndex)).TargetB.GetReferenceType()));
        return 1;
    }

    int GetEffectTargetBObjectType(Eluna* E, ElunaSpellInfo* spellInfo)
    {
        uint32 effIndex = E->CHECKVAL<uint32>(2);
        if (effIndex >= MAX_SPELL_EFFECTS)
            return luaL_argerror(E->L, 2, "effect index out of range");
        E->Push(static_cast<uint32>(spellInfo->GetSpellInfo()->GetEffect(static_cast<SpellEffIndex>(effIndex)).TargetB.GetObjectType()));
        return 1;
    }

    int GetEffectTargetBCheckType(Eluna* E, ElunaSpellInfo* spellInfo)
    {
        uint32 effIndex = E->CHECKVAL<uint32>(2);
        if (effIndex >= MAX_SPELL_EFFECTS)
            return luaL_argerror(E->L, 2, "effect index out of range");
        E->Push(static_cast<uint32>(spellInfo->GetSpellInfo()->GetEffect(static_cast<SpellEffIndex>(effIndex)).TargetB.GetCheckType()));
        return 1;
    }

    int GetEffectTargetBDirectionType(Eluna* E, ElunaSpellInfo* spellInfo)
    {
        uint32 effIndex = E->CHECKVAL<uint32>(2);
        if (effIndex >= MAX_SPELL_EFFECTS)
            return luaL_argerror(E->L, 2, "effect index out of range");
        E->Push(static_cast<uint32>(spellInfo->GetSpellInfo()->GetEffect(static_cast<SpellEffIndex>(effIndex)).TargetB.GetDirectionType()));
        return 1;
    }

    int GetEffectTargetBIsArea(Eluna* E, ElunaSpellInfo* spellInfo)
    {
        uint32 effIndex = E->CHECKVAL<uint32>(2);
        if (effIndex >= MAX_SPELL_EFFECTS)
            return luaL_argerror(E->L, 2, "effect index out of range");
        E->Push(spellInfo->GetSpellInfo()->GetEffect(static_cast<SpellEffIndex>(effIndex)).TargetB.IsArea());
        return 1;
    }

    int GetEffectTargetBDirectionAngle(Eluna* E, ElunaSpellInfo* spellInfo)
    {
        uint32 effIndex = E->CHECKVAL<uint32>(2);
        if (effIndex >= MAX_SPELL_EFFECTS)
            return luaL_argerror(E->L, 2, "effect index out of range");
        E->Push(spellInfo->GetSpellInfo()->GetEffect(static_cast<SpellEffIndex>(effIndex)).TargetB.CalcDirectionAngle());
        return 1;
    }


    ElunaRegister<ElunaSpellInfo> SpellInfoMethods[] =
    {
        { "GetId",                                      &LuaSpellInfo::GetId },
        { "GetDispel",                                  &LuaSpellInfo::GetDispel },
        { "GetMechanic",                                &LuaSpellInfo::GetMechanic },
        { "GetAttributes",                              &LuaSpellInfo::GetAttributes },
        { "GetAttributesEx",                            &LuaSpellInfo::GetAttributesEx },
        { "GetAttributesEx2",                           &LuaSpellInfo::GetAttributesEx2 },
        { "GetAttributesEx3",                           &LuaSpellInfo::GetAttributesEx3 },
        { "GetAttributesEx4",                           &LuaSpellInfo::GetAttributesEx4 },
        { "GetAttributesEx5",                           &LuaSpellInfo::GetAttributesEx5 },
        { "GetAttributesEx6",                           &LuaSpellInfo::GetAttributesEx6 },
        { "GetAttributesEx7",                           &LuaSpellInfo::GetAttributesEx7 },
        { "GetAttributesCu",                            &LuaSpellInfo::GetAttributesCu },
        { "GetStances",                                 &LuaSpellInfo::GetStances },
        { "GetStancesNot",                              &LuaSpellInfo::GetStancesNot },
        { "GetTargets",                                 &LuaSpellInfo::GetTargets },
        { "GetTargetCreatureType",                      &LuaSpellInfo::GetTargetCreatureType },
        { "GetRequiresSpellFocus",                      &LuaSpellInfo::GetRequiresSpellFocus },
        { "GetFacingCasterFlags",                       &LuaSpellInfo::GetFacingCasterFlags },
        { "GetCasterAuraState",                         &LuaSpellInfo::GetCasterAuraState },
        { "GetTargetAuraState",                         &LuaSpellInfo::GetTargetAuraState },
        { "GetCasterAuraStateNot",                      &LuaSpellInfo::GetCasterAuraStateNot },
        { "GetTargetAuraStateNot",                      &LuaSpellInfo::GetTargetAuraStateNot },
        { "GetCasterAuraSpell",                         &LuaSpellInfo::GetCasterAuraSpell },
        { "GetTargetAuraSpell",                         &LuaSpellInfo::GetTargetAuraSpell },
        { "GetExcludeCasterAuraSpell",                  &LuaSpellInfo::GetExcludeCasterAuraSpell },
        { "GetExcludeTargetAuraSpell",                  &LuaSpellInfo::GetExcludeTargetAuraSpell },
        { "GetRecoveryTime",                            &LuaSpellInfo::GetRecoveryTime },
        { "GetCategoryRecoveryTime",                    &LuaSpellInfo::GetCategoryRecoveryTime },
        { "GetStartRecoveryCategory",                   &LuaSpellInfo::GetStartRecoveryCategory },
        { "GetStartRecoveryTime",                       &LuaSpellInfo::GetStartRecoveryTime },
        { "GetInterruptFlags",                          &LuaSpellInfo::GetInterruptFlags },
        { "GetAuraInterruptFlags",                      &LuaSpellInfo::GetAuraInterruptFlags },
        { "GetChannelInterruptFlags",                   &LuaSpellInfo::GetChannelInterruptFlags },
        { "GetProcFlags",                               &LuaSpellInfo::GetProcFlags },
        { "GetProcChance",                              &LuaSpellInfo::GetProcChance },
        { "GetProcCharges",                             &LuaSpellInfo::GetProcCharges },
        { "GetMaxLevel",                                &LuaSpellInfo::GetMaxLevel },
        { "GetBaseLevel",                               &LuaSpellInfo::GetBaseLevel },
        { "GetSpellLevel",                              &LuaSpellInfo::GetSpellLevel },
        { "GetPowerType",                               &LuaSpellInfo::GetPowerType },
        { "GetManaCost",                                &LuaSpellInfo::GetManaCost },
        { "GetManaCostPerlevel",                        &LuaSpellInfo::GetManaCostPerlevel },
        { "GetManaPerSecond",                           &LuaSpellInfo::GetManaPerSecond },
        { "GetManaPerSecondPerLevel",                   &LuaSpellInfo::GetManaPerSecondPerLevel },
        { "GetManaCostPercentage",                      &LuaSpellInfo::GetManaCostPercentage },
        { "GetRuneCostID",                              &LuaSpellInfo::GetRuneCostID },
        { "GetSpeed",                                   &LuaSpellInfo::GetSpeed },
        { "GetStackAmount",                             &LuaSpellInfo::GetStackAmount },
        { "GetTotem",                                   &LuaSpellInfo::GetTotem },
        { "GetReagent",                                 &LuaSpellInfo::GetReagent },
        { "GetReagentCount",                            &LuaSpellInfo::GetReagentCount },
        { "GetEquippedItemClass",                       &LuaSpellInfo::GetEquippedItemClass },
        { "GetEquippedItemSubClassMask",                &LuaSpellInfo::GetEquippedItemSubClassMask },
        { "GetEquippedItemInventoryTypeMask",           &LuaSpellInfo::GetEquippedItemInventoryTypeMask },
        { "GetTotemCategory",                           &LuaSpellInfo::GetTotemCategory },
        { "GetSpellVisual",                             &LuaSpellInfo::GetSpellVisual },
        { "GetSpellIconID",                             &LuaSpellInfo::GetSpellIconID },
        { "GetActiveIconID",                            &LuaSpellInfo::GetActiveIconID },
        { "GetPriority",                                &LuaSpellInfo::GetPriority },
        { "GetMaxTargetLevel",                          &LuaSpellInfo::GetMaxTargetLevel },
        { "GetMaxAffectedTargets",                      &LuaSpellInfo::GetMaxAffectedTargets },
        { "GetSpellFamilyName",                         &LuaSpellInfo::GetSpellFamilyName },
        { "GetSpellFamilyFlags",                        &LuaSpellInfo::GetSpellFamilyFlags },
        { "GetDmgClass",                                &LuaSpellInfo::GetDmgClass },
        { "GetPreventionType",                          &LuaSpellInfo::GetPreventionType },
        { "GetAreaGroupId",                             &LuaSpellInfo::GetAreaGroupId },
        { "GetSchoolMask",                              &LuaSpellInfo::GetSchoolMask },
        { "GetDuration",                                &LuaSpellInfo::GetDuration },
        { "GetMaxDuration",                             &LuaSpellInfo::GetMaxDuration },
        { "GetMaxRange",                                &LuaSpellInfo::GetMaxRange },
        { "GetMinRange",                                &LuaSpellInfo::GetMinRange },
        { "GetMaxTicks",                                &LuaSpellInfo::GetMaxTicks },
        { "GetCategory",                                &LuaSpellInfo::GetCategory },
        { "GetRank",                                    &LuaSpellInfo::GetRank },
        { "GetAllEffectsMechanicMask",                  &LuaSpellInfo::GetAllEffectsMechanicMask },
        { "GetAllowedMechanicMask",                     &LuaSpellInfo::GetAllowedMechanicMask },
        { "GetExplicitTargetMask",                      &LuaSpellInfo::GetExplicitTargetMask },
        { "GetAuraState",                               &LuaSpellInfo::GetAuraState },
        { "GetSpellSpecific",                           &LuaSpellInfo::GetSpellSpecific },
        { "GetAttackType",                              &LuaSpellInfo::GetAttackType },
        { "GetEffectMechanicMask",                      &LuaSpellInfo::GetEffectMechanicMask },
        { "GetEffectMechanic",                          &LuaSpellInfo::GetEffectMechanic },
        { "GetSpellMechanicMaskByEffectMask",           &LuaSpellInfo::GetSpellMechanicMaskByEffectMask },
        { "GetDiminishingReturnsGroupForSpell",         &LuaSpellInfo::GetDiminishingReturnsGroupForSpell },
        { "GetDiminishingReturnsGroupType",             &LuaSpellInfo::GetDiminishingReturnsGroupType },
        { "GetDiminishingReturnsMaxLevel",              &LuaSpellInfo::GetDiminishingReturnsMaxLevel },
        { "GetDiminishingReturnsLimitDuration",         &LuaSpellInfo::GetDiminishingReturnsLimitDuration },
        { "CalcCastTime",                               &LuaSpellInfo::CalcCastTime },
        { "IsPassive",                                  &LuaSpellInfo::IsPassive },
        { "IsAutocastable",                             &LuaSpellInfo::IsAutocastable },
        { "IsStackableWithRanks",                       &LuaSpellInfo::IsStackableWithRanks },
        { "IsPassiveStackableWithRanks",                &LuaSpellInfo::IsPassiveStackableWithRanks },
        { "IsMultiSlotAura",                            &LuaSpellInfo::IsMultiSlotAura },
        { "IsStackableOnOneSlotWithDifferentCasters",   &LuaSpellInfo::IsStackableOnOneSlotWithDifferentCasters },
        { "IsCooldownStartedOnEvent",                   &LuaSpellInfo::IsCooldownStartedOnEvent },
        { "IsDeathPersistent",                          &LuaSpellInfo::IsDeathPersistent },
        { "IsRequiringDeadTarget",                      &LuaSpellInfo::IsRequiringDeadTarget },
        { "IsAllowingDeadTarget",                       &LuaSpellInfo::IsAllowingDeadTarget },
        { "IsGroupBuff",                                &LuaSpellInfo::IsGroupBuff },
        { "CanBeUsedInCombat",                          &LuaSpellInfo::CanBeUsedInCombat },
        { "IsPositive",                                 &LuaSpellInfo::IsPositive },
        { "IsChanneled",                                &LuaSpellInfo::IsChanneled },
        { "IsMoveAllowedChannel",                       &LuaSpellInfo::IsMoveAllowedChannel },
        { "NeedsComboPoints",                           &LuaSpellInfo::NeedsComboPoints },
        { "IsNextMeleeSwingSpell",                      &LuaSpellInfo::IsNextMeleeSwingSpell },
        { "IsBreakingStealth",                          &LuaSpellInfo::IsBreakingStealth },
        { "IsRangedWeaponSpell",                        &LuaSpellInfo::IsRangedWeaponSpell },
        { "IsAutoRepeatRangedSpell",                    &LuaSpellInfo::IsAutoRepeatRangedSpell },
        { "HasInitialAggro",                            &LuaSpellInfo::HasInitialAggro },
        { "IsRanked",                                   &LuaSpellInfo::IsRanked },
        { "IsAffectingArea",                            &LuaSpellInfo::IsAffectingArea },
        { "IsTargetingArea",                            &LuaSpellInfo::IsTargetingArea },
        { "NeedsExplicitUnitTarget",                    &LuaSpellInfo::NeedsExplicitUnitTarget },
        { "IsSelfCast",                                 &LuaSpellInfo::IsSelfCast },
        { "IsSingleTarget",                             &LuaSpellInfo::IsSingleTarget },
        { "IsExplicitDiscovery",                        &LuaSpellInfo::IsExplicitDiscovery },
        { "IsLootCrafting",                             &LuaSpellInfo::IsLootCrafting },
        { "IsProfessionOrRiding",                       &LuaSpellInfo::IsProfessionOrRiding },
        { "IsProfession",                               &LuaSpellInfo::IsProfession },
        { "IsPrimaryProfession",                        &LuaSpellInfo::IsPrimaryProfession },
        { "IsPrimaryProfessionFirstRank",               &LuaSpellInfo::IsPrimaryProfessionFirstRank },
        { "IsAbilityLearnedWithProfession",             &LuaSpellInfo::IsAbilityLearnedWithProfession },
        { "IsAffectedBySpellMods",                      &LuaSpellInfo::IsAffectedBySpellMods },
        { "HasAreaAuraEffect",                          &LuaSpellInfo::HasAreaAuraEffect },
        { "HasOnlyDamageEffects",                       &LuaSpellInfo::HasOnlyDamageEffects },
        { "IsPositiveEffect",                           &LuaSpellInfo::IsPositiveEffect },
        { "HasEffect",                                  &LuaSpellInfo::HasEffect },
        { "HasAura",                                    &LuaSpellInfo::HasAura },
        { "IsAffected",                                 &LuaSpellInfo::IsAffected },
        { "IsAffectedBySpellMod",                       &LuaSpellInfo::IsAffectedBySpellMod },
        { "IsRankOf",                                   &LuaSpellInfo::IsRankOf },
        { "IsDifferentRankOf",                          &LuaSpellInfo::IsDifferentRankOf },
        { "IsHighRankOf",                               &LuaSpellInfo::IsHighRankOf },
        { "CanPierceImmuneAura",                        &LuaSpellInfo::CanPierceImmuneAura },
        { "CanDispelAura",                              &LuaSpellInfo::CanDispelAura },
        { "CanSpellProvideImmunityAgainstAura",         &LuaSpellInfo::CanSpellProvideImmunityAgainstAura },
        { "IsAuraExclusiveBySpecificWith",              &LuaSpellInfo::IsAuraExclusiveBySpecificWith },
        { "IsAuraExclusiveBySpecificPerCasterWith",     &LuaSpellInfo::IsAuraExclusiveBySpecificPerCasterWith },
        { "IsItemFitToSpellRequirements",               &LuaSpellInfo::IsItemFitToSpellRequirements },
        { "IsAbilityOfSkillType",                       &LuaSpellInfo::IsAbilityOfSkillType },
        { "NeedsToBeTriggeredByCaster",                 &LuaSpellInfo::NeedsToBeTriggeredByCaster },
        { "CheckTarget",                                &LuaSpellInfo::CheckTarget },
        { "CheckTargetCreatureType",                    &LuaSpellInfo::CheckTargetCreatureType },
        { "SpellCancelsAuraEffect",                     &LuaSpellInfo::SpellCancelsAuraEffect },
        { "GetEffectIndex",                             &LuaSpellInfo::GetEffectIndex },
        { "GetEffectType",                              &LuaSpellInfo::GetEffectType },
        { "GetEffectApplyAuraName",                     &LuaSpellInfo::GetEffectApplyAuraName },
        { "GetEffectAmplitude",                         &LuaSpellInfo::GetEffectAmplitude },
        { "GetEffectDieSides",                          &LuaSpellInfo::GetEffectDieSides },
        { "GetEffectRealPointsPerLevel",                &LuaSpellInfo::GetEffectRealPointsPerLevel },
        { "GetEffectBasePoints",                        &LuaSpellInfo::GetEffectBasePoints },
        { "GetEffectPointsPerComboPoint",               &LuaSpellInfo::GetEffectPointsPerComboPoint },
        { "GetEffectValueMultiplier",                   &LuaSpellInfo::GetEffectValueMultiplier },
        { "GetEffectDamageMultiplier",                  &LuaSpellInfo::GetEffectDamageMultiplier },
        { "GetEffectBonusMultiplier",                   &LuaSpellInfo::GetEffectBonusMultiplier },
        { "GetEffectMiscValue",                         &LuaSpellInfo::GetEffectMiscValue },
        { "GetEffectMiscValueB",                        &LuaSpellInfo::GetEffectMiscValueB },
        { "GetEffectChainTarget",                       &LuaSpellInfo::GetEffectChainTarget },
        { "GetEffectItemType",                          &LuaSpellInfo::GetEffectItemType },
        { "GetEffectTriggerSpell",                      &LuaSpellInfo::GetEffectTriggerSpell },
        { "GetEffectSpellClassMask",                    &LuaSpellInfo::GetEffectSpellClassMask },
        { "GetEffectCalcValue",                         &LuaSpellInfo::GetEffectCalcValue },
        { "GetEffectCalcRadius",                        &LuaSpellInfo::GetEffectCalcRadius },
        { "GetEffectHasRadius",                         &LuaSpellInfo::GetEffectHasRadius },
        { "GetEffectProvidedTargetMask",                &LuaSpellInfo::GetEffectProvidedTargetMask },
        { "GetEffectImplicitTargetType",                &LuaSpellInfo::GetEffectImplicitTargetType },
        { "GetEffectUsedTargetObjectType",              &LuaSpellInfo::GetEffectUsedTargetObjectType },
        { "EffectIsEffect",                             &LuaSpellInfo::EffectIsEffect },
        { "EffectIsEffectType",                         &LuaSpellInfo::EffectIsEffectType },
        { "EffectIsAura",                               &LuaSpellInfo::EffectIsAura },
        { "EffectIsAuraType",                           &LuaSpellInfo::EffectIsAuraType },
        { "EffectIsTargetingArea",                      &LuaSpellInfo::EffectIsTargetingArea },
        { "EffectIsAreaAuraEffect",                     &LuaSpellInfo::EffectIsAreaAuraEffect },
        { "EffectIsUnitOwnedAuraEffect",                &LuaSpellInfo::EffectIsUnitOwnedAuraEffect },
        { "GetEffectTargetATarget",                     &LuaSpellInfo::GetEffectTargetATarget },
        { "GetEffectTargetASelectionCategory",          &LuaSpellInfo::GetEffectTargetASelectionCategory },
        { "GetEffectTargetAReferenceType",              &LuaSpellInfo::GetEffectTargetAReferenceType },
        { "GetEffectTargetAObjectType",                 &LuaSpellInfo::GetEffectTargetAObjectType },
        { "GetEffectTargetACheckType",                  &LuaSpellInfo::GetEffectTargetACheckType },
        { "GetEffectTargetADirectionType",              &LuaSpellInfo::GetEffectTargetADirectionType },
        { "GetEffectTargetAIsArea",                     &LuaSpellInfo::GetEffectTargetAIsArea },
        { "GetEffectTargetADirectionAngle",             &LuaSpellInfo::GetEffectTargetADirectionAngle },
        { "GetEffectTargetBTarget",                     &LuaSpellInfo::GetEffectTargetBTarget },
        { "GetEffectTargetBSelectionCategory",          &LuaSpellInfo::GetEffectTargetBSelectionCategory },
        { "GetEffectTargetBReferenceType",              &LuaSpellInfo::GetEffectTargetBReferenceType },
        { "GetEffectTargetBObjectType",                 &LuaSpellInfo::GetEffectTargetBObjectType },
        { "GetEffectTargetBCheckType",                  &LuaSpellInfo::GetEffectTargetBCheckType },
        { "GetEffectTargetBDirectionType",              &LuaSpellInfo::GetEffectTargetBDirectionType },
        { "GetEffectTargetBIsArea",                     &LuaSpellInfo::GetEffectTargetBIsArea },
        { "GetEffectTargetBDirectionAngle",             &LuaSpellInfo::GetEffectTargetBDirectionAngle }
    };
}
#endif
