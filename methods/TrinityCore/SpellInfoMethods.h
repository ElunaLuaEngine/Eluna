/*
* Copyright (C) 2010 - 2024 Eluna Lua Engine <https://elunaluaengine.github.io/>
* This program is free software licensed under GPL version 3
* Please see the included DOCS/LICENSE.md for more information
*/
#ifndef SPELLINFO_METHODS
#define SPELLINFO_METHODS
namespace LuaSpellInfo
{
    /**
     * Returns the ID of the [ElunaSpellInfo].
     *
     * @return uint32 id
     */
    int GetId(Eluna* E, ElunaSpellInfo* spellInfo)
    {
        E->Push(spellInfo->GetSpellInfo()->Id);
        return 1;
    }

    /**
     * Returns the dispel type of the [ElunaSpellInfo].
     *
     * @return uint32 dispel
     */
    int GetDispel(Eluna* E, ElunaSpellInfo* spellInfo)
    {
        E->Push(spellInfo->GetSpellInfo()->Dispel);
        return 1;
    }

    /**
     * Returns the mechanic of the [ElunaSpellInfo].
     *
     * @return uint32 mechanic
     */
    int GetMechanic(Eluna* E, ElunaSpellInfo* spellInfo)
    {
        E->Push(spellInfo->GetSpellInfo()->Mechanic);
        return 1;
    }

    /**
     * Returns the attributes of the [ElunaSpellInfo].
     *
     * @return uint32 attributes
     */
    int GetAttributes(Eluna* E, ElunaSpellInfo* spellInfo)
    {
        E->Push(spellInfo->GetSpellInfo()->Attributes);
        return 1;
    }

    /**
     * Returns the first extended attributes of the [ElunaSpellInfo].
     *
     * @return uint32 attributesEx
     */
    int GetAttributesEx(Eluna* E, ElunaSpellInfo* spellInfo)
    {
        E->Push(spellInfo->GetSpellInfo()->AttributesEx);
        return 1;
    }

    /**
     * Returns the second extended attributes of the [ElunaSpellInfo].
     *
     * @return uint32 attributesEx2
     */
    int GetAttributesEx2(Eluna* E, ElunaSpellInfo* spellInfo)
    {
        E->Push(spellInfo->GetSpellInfo()->AttributesEx2);
        return 1;
    }

    /**
     * Returns the third extended attributes of the [ElunaSpellInfo].
     *
     * @return uint32 attributesEx3
     */
    int GetAttributesEx3(Eluna* E, ElunaSpellInfo* spellInfo)
    {
        E->Push(spellInfo->GetSpellInfo()->AttributesEx3);
        return 1;
    }

    /**
     * Returns the fourth extended attributes of the [ElunaSpellInfo].
     *
     * @return uint32 attributesEx4
     */
    int GetAttributesEx4(Eluna* E, ElunaSpellInfo* spellInfo)
    {
        E->Push(spellInfo->GetSpellInfo()->AttributesEx4);
        return 1;
    }

    /**
     * Returns the fifth extended attributes of the [ElunaSpellInfo].
     *
     * @return uint32 attributesEx5
     */
    int GetAttributesEx5(Eluna* E, ElunaSpellInfo* spellInfo)
    {
        E->Push(spellInfo->GetSpellInfo()->AttributesEx5);
        return 1;
    }

    /**
     * Returns the sixth extended attributes of the [ElunaSpellInfo].
     *
     * @return uint32 attributesEx6
     */
    int GetAttributesEx6(Eluna* E, ElunaSpellInfo* spellInfo)
    {
        E->Push(spellInfo->GetSpellInfo()->AttributesEx6);
        return 1;
    }

    /**
     * Returns the seventh extended attributes of the [ElunaSpellInfo].
     *
     * @return uint32 attributesEx7
     */
    int GetAttributesEx7(Eluna* E, ElunaSpellInfo* spellInfo)
    {
        E->Push(spellInfo->GetSpellInfo()->AttributesEx7);
        return 1;
    }

    /**
     * Returns the custom attributes of the [ElunaSpellInfo].
     *
     * @return uint32 attributesCu
     */
    int GetAttributesCu(Eluna* E, ElunaSpellInfo* spellInfo)
    {
        E->Push(spellInfo->GetSpellInfo()->AttributesCu);
        return 1;
    }

    /**
     * Returns the stances bitmask of the [ElunaSpellInfo] as uint32.
     *
     * @return uint32 stances
     */
    int GetStances(Eluna* E, ElunaSpellInfo* spellInfo)
    {
        E->Push(static_cast<uint32>(spellInfo->GetSpellInfo()->Stances));
        return 1;
    }

    /**
     * Returns the stances not bitmask of the [ElunaSpellInfo] as uint32.
     *
     * @return uint32 stancesNot
     */
    int GetStancesNot(Eluna* E, ElunaSpellInfo* spellInfo)
    {
        E->Push(static_cast<uint32>(spellInfo->GetSpellInfo()->StancesNot));
        return 1;
    }

    /**
     * Returns the targets bitmask of the [ElunaSpellInfo].
     *
     * @return uint32 targets
     */
    int GetTargets(Eluna* E, ElunaSpellInfo* spellInfo)
    {
        E->Push(spellInfo->GetSpellInfo()->Targets);
        return 1;
    }

    /**
     * Returns the target creature type of the [ElunaSpellInfo].
     *
     * @return uint32 targetCreatureType
     */
    int GetTargetCreatureType(Eluna* E, ElunaSpellInfo* spellInfo)
    {
        E->Push(spellInfo->GetSpellInfo()->TargetCreatureType);
        return 1;
    }

    /**
     * Returns the requires spell focus entry of the [ElunaSpellInfo].
     *
     * @return uint32 requiresSpellFocus
     */
    int GetRequiresSpellFocus(Eluna* E, ElunaSpellInfo* spellInfo)
    {
        E->Push(spellInfo->GetSpellInfo()->RequiresSpellFocus);
        return 1;
    }

    /**
     * Returns the facing caster flags of the [ElunaSpellInfo].
     *
     * @return uint32 facingCasterFlags
     */
    int GetFacingCasterFlags(Eluna* E, ElunaSpellInfo* spellInfo)
    {
        E->Push(spellInfo->GetSpellInfo()->FacingCasterFlags);
        return 1;
    }

    /**
     * Returns the caster aura state required to cast the [ElunaSpellInfo].
     *
     * @return uint32 casterAuraState
     */
    int GetCasterAuraState(Eluna* E, ElunaSpellInfo* spellInfo)
    {
        E->Push(spellInfo->GetSpellInfo()->CasterAuraState);
        return 1;
    }

    /**
     * Returns the target aura state required to cast the [ElunaSpellInfo].
     *
     * @return uint32 targetAuraState
     */
    int GetTargetAuraState(Eluna* E, ElunaSpellInfo* spellInfo)
    {
        E->Push(spellInfo->GetSpellInfo()->TargetAuraState);
        return 1;
    }

    /**
     * Returns the caster aura state that prevents casting the [ElunaSpellInfo].
     *
     * @return uint32 casterAuraStateNot
     */
    int GetCasterAuraStateNot(Eluna* E, ElunaSpellInfo* spellInfo)
    {
        E->Push(spellInfo->GetSpellInfo()->CasterAuraStateNot);
        return 1;
    }

    /**
     * Returns the target aura state that prevents casting the [ElunaSpellInfo].
     *
     * @return uint32 targetAuraStateNot
     */
    int GetTargetAuraStateNot(Eluna* E, ElunaSpellInfo* spellInfo)
    {
        E->Push(spellInfo->GetSpellInfo()->TargetAuraStateNot);
        return 1;
    }

    /**
     * Returns the spell ID that must be active on the caster to cast the [ElunaSpellInfo].
     *
     * @return uint32 casterAuraSpell
     */
    int GetCasterAuraSpell(Eluna* E, ElunaSpellInfo* spellInfo)
    {
        E->Push(spellInfo->GetSpellInfo()->CasterAuraSpell);
        return 1;
    }

    /**
     * Returns the spell ID that must be active on the target to cast the [ElunaSpellInfo].
     *
     * @return uint32 targetAuraSpell
     */
    int GetTargetAuraSpell(Eluna* E, ElunaSpellInfo* spellInfo)
    {
        E->Push(spellInfo->GetSpellInfo()->TargetAuraSpell);
        return 1;
    }

    /**
     * Returns the spell ID that must not be active on the caster to cast the [ElunaSpellInfo].
     *
     * @return uint32 excludeCasterAuraSpell
     */
    int GetExcludeCasterAuraSpell(Eluna* E, ElunaSpellInfo* spellInfo)
    {
        E->Push(spellInfo->GetSpellInfo()->ExcludeCasterAuraSpell);
        return 1;
    }

    /**
     * Returns the spell ID that must not be active on the target to cast the [ElunaSpellInfo].
     *
     * @return uint32 excludeTargetAuraSpell
     */
    int GetExcludeTargetAuraSpell(Eluna* E, ElunaSpellInfo* spellInfo)
    {
        E->Push(spellInfo->GetSpellInfo()->ExcludeTargetAuraSpell);
        return 1;
    }

    /**
     * Returns the recovery time in milliseconds of the [ElunaSpellInfo].
     *
     * @return uint32 recoveryTime
     */
    int GetRecoveryTime(Eluna* E, ElunaSpellInfo* spellInfo)
    {
        E->Push(spellInfo->GetSpellInfo()->RecoveryTime);
        return 1;
    }

    /**
     * Returns the category recovery time in milliseconds of the [ElunaSpellInfo].
     *
     * @return uint32 categoryRecoveryTime
     */
    int GetCategoryRecoveryTime(Eluna* E, ElunaSpellInfo* spellInfo)
    {
        E->Push(spellInfo->GetSpellInfo()->CategoryRecoveryTime);
        return 1;
    }

    /**
     * Returns the start recovery category of the [ElunaSpellInfo].
     *
     * @return uint32 startRecoveryCategory
     */
    int GetStartRecoveryCategory(Eluna* E, ElunaSpellInfo* spellInfo)
    {
        E->Push(spellInfo->GetSpellInfo()->StartRecoveryCategory);
        return 1;
    }

    /**
     * Returns the start recovery time in milliseconds of the [ElunaSpellInfo].
     *
     * @return uint32 startRecoveryTime
     */
    int GetStartRecoveryTime(Eluna* E, ElunaSpellInfo* spellInfo)
    {
        E->Push(spellInfo->GetSpellInfo()->StartRecoveryTime);
        return 1;
    }

    /**
     * Returns the interrupt flags of the [ElunaSpellInfo].
     *
     * @return uint32 interruptFlags
     */
    int GetInterruptFlags(Eluna* E, ElunaSpellInfo* spellInfo)
    {
        E->Push(spellInfo->GetSpellInfo()->InterruptFlags);
        return 1;
    }

    /**
     * Returns the aura interrupt flags of the [ElunaSpellInfo].
     *
     * @return uint32 auraInterruptFlags
     */
    int GetAuraInterruptFlags(Eluna* E, ElunaSpellInfo* spellInfo)
    {
        E->Push(spellInfo->GetSpellInfo()->AuraInterruptFlags);
        return 1;
    }

    /**
     * Returns the channel interrupt flags of the [ElunaSpellInfo].
     *
     * @return uint32 channelInterruptFlags
     */
    int GetChannelInterruptFlags(Eluna* E, ElunaSpellInfo* spellInfo)
    {
        E->Push(spellInfo->GetSpellInfo()->ChannelInterruptFlags);
        return 1;
    }

    /**
     * Returns the proc flags of the [ElunaSpellInfo].
     *
     * @return uint32 procFlags
     */
    int GetProcFlags(Eluna* E, ElunaSpellInfo* spellInfo)
    {
        E->Push(spellInfo->GetSpellInfo()->ProcFlags);
        return 1;
    }

    /**
     * Returns the proc chance of the [ElunaSpellInfo].
     *
     * @return uint32 procChance
     */
    int GetProcChance(Eluna* E, ElunaSpellInfo* spellInfo)
    {
        E->Push(spellInfo->GetSpellInfo()->ProcChance);
        return 1;
    }

    /**
     * Returns the proc charges of the [ElunaSpellInfo].
     *
     * @return uint32 procCharges
     */
    int GetProcCharges(Eluna* E, ElunaSpellInfo* spellInfo)
    {
        E->Push(spellInfo->GetSpellInfo()->ProcCharges);
        return 1;
    }

    /**
     * Returns the maximum level of the [ElunaSpellInfo].
     *
     * @return uint32 maxLevel
     */
    int GetMaxLevel(Eluna* E, ElunaSpellInfo* spellInfo)
    {
        E->Push(spellInfo->GetSpellInfo()->MaxLevel);
        return 1;
    }

    /**
     * Returns the base level required to cast the [ElunaSpellInfo].
     *
     * @return uint32 baseLevel
     */
    int GetBaseLevel(Eluna* E, ElunaSpellInfo* spellInfo)
    {
        E->Push(spellInfo->GetSpellInfo()->BaseLevel);
        return 1;
    }

    /**
     * Returns the spell level of the [ElunaSpellInfo].
     *
     * @return uint32 spellLevel
     */
    int GetSpellLevel(Eluna* E, ElunaSpellInfo* spellInfo)
    {
        E->Push(spellInfo->GetSpellInfo()->SpellLevel);
        return 1;
    }

    /**
     * Returns the power type of the [ElunaSpellInfo].
     *
     * @return uint32 powerType
     */
    int GetPowerType(Eluna* E, ElunaSpellInfo* spellInfo)
    {
        E->Push(spellInfo->GetSpellInfo()->PowerType);
        return 1;
    }

    /**
     * Returns the mana cost of the [ElunaSpellInfo].
     *
     * @return uint32 manaCost
     */
    int GetManaCost(Eluna* E, ElunaSpellInfo* spellInfo)
    {
        E->Push(spellInfo->GetSpellInfo()->ManaCost);
        return 1;
    }

    /**
     * Returns the mana cost per level of the [ElunaSpellInfo].
     *
     * @return uint32 manaCostPerlevel
     */
    int GetManaCostPerlevel(Eluna* E, ElunaSpellInfo* spellInfo)
    {
        E->Push(spellInfo->GetSpellInfo()->ManaCostPerlevel);
        return 1;
    }

    /**
     * Returns the mana per second drain of the [ElunaSpellInfo].
     *
     * @return uint32 manaPerSecond
     */
    int GetManaPerSecond(Eluna* E, ElunaSpellInfo* spellInfo)
    {
        E->Push(spellInfo->GetSpellInfo()->ManaPerSecond);
        return 1;
    }

    /**
     * Returns the mana per second per level drain of the [ElunaSpellInfo].
     *
     * @return uint32 manaPerSecondPerLevel
     */
    int GetManaPerSecondPerLevel(Eluna* E, ElunaSpellInfo* spellInfo)
    {
        E->Push(spellInfo->GetSpellInfo()->ManaPerSecondPerLevel);
        return 1;
    }

    /**
     * Returns the mana cost percentage of the [ElunaSpellInfo].
     *
     * @return uint32 manaCostPercentage
     */
    int GetManaCostPercentage(Eluna* E, ElunaSpellInfo* spellInfo)
    {
        E->Push(spellInfo->GetSpellInfo()->ManaCostPercentage);
        return 1;
    }

    /**
     * Returns the rune cost ID of the [ElunaSpellInfo].
     *
     * @return uint32 runeCostID
     */
    int GetRuneCostID(Eluna* E, ElunaSpellInfo* spellInfo)
    {
        E->Push(spellInfo->GetSpellInfo()->RuneCostID);
        return 1;
    }

    /**
     * Returns the projectile speed of the [ElunaSpellInfo].
     *
     * @return float speed
     */
    int GetSpeed(Eluna* E, ElunaSpellInfo* spellInfo)
    {
        E->Push(spellInfo->GetSpellInfo()->Speed);
        return 1;
    }

    /**
     * Returns the stack amount of the [ElunaSpellInfo].
     *
     * @return uint32 stackAmount
     */
    int GetStackAmount(Eluna* E, ElunaSpellInfo* spellInfo)
    {
        E->Push(spellInfo->GetSpellInfo()->StackAmount);
        return 1;
    }

    /**
     * Returns the totem entry at the given index for the [ElunaSpellInfo].
     *
     * @param uint32 index : the totem index (0-1)
     * @return uint32 totem
     */
    int GetTotem(Eluna* E, ElunaSpellInfo* spellInfo)
    {
        uint32 index = E->CHECKVAL<uint32>(2);
        if (index >= 2)
            return luaL_argerror(E->L, 2, "index out of range (0-1)");
        E->Push(spellInfo->GetSpellInfo()->Totem[index]);
        return 1;
    }

    /**
     * Returns the reagent entry at the given index for the [ElunaSpellInfo].
     *
     * @param uint32 index : the reagent index (0-MAX_SPELL_REAGENTS-1)
     * @return int32 reagent
     */
    int GetReagent(Eluna* E, ElunaSpellInfo* spellInfo)
    {
        uint32 index = E->CHECKVAL<uint32>(2);
        if (index >= MAX_SPELL_REAGENTS)
            return luaL_argerror(E->L, 2, "index out of range (0-MAX_SPELL_REAGENTS-1)");
        E->Push(spellInfo->GetSpellInfo()->Reagent[index]);
        return 1;
    }

    /**
     * Returns the reagent count at the given index for the [ElunaSpellInfo].
     *
     * @param uint32 index : the reagent index (0-MAX_SPELL_REAGENTS-1)
     * @return uint32 reagentCount
     */
    int GetReagentCount(Eluna* E, ElunaSpellInfo* spellInfo)
    {
        uint32 index = E->CHECKVAL<uint32>(2);
        if (index >= MAX_SPELL_REAGENTS)
            return luaL_argerror(E->L, 2, "index out of range (0-MAX_SPELL_REAGENTS-1)");
        E->Push(spellInfo->GetSpellInfo()->ReagentCount[index]);
        return 1;
    }

    /**
     * Returns the required equipped item class of the [ElunaSpellInfo].
     *
     * @return int32 equippedItemClass
     */
    int GetEquippedItemClass(Eluna* E, ElunaSpellInfo* spellInfo)
    {
        E->Push(spellInfo->GetSpellInfo()->EquippedItemClass);
        return 1;
    }

    /**
     * Returns the required equipped item subclass mask of the [ElunaSpellInfo].
     *
     * @return int32 equippedItemSubClassMask
     */
    int GetEquippedItemSubClassMask(Eluna* E, ElunaSpellInfo* spellInfo)
    {
        E->Push(spellInfo->GetSpellInfo()->EquippedItemSubClassMask);
        return 1;
    }

    /**
     * Returns the required equipped item inventory type mask of the [ElunaSpellInfo].
     *
     * @return int32 equippedItemInventoryTypeMask
     */
    int GetEquippedItemInventoryTypeMask(Eluna* E, ElunaSpellInfo* spellInfo)
    {
        E->Push(spellInfo->GetSpellInfo()->EquippedItemInventoryTypeMask);
        return 1;
    }

    /**
     * Returns the totem category entry at the given index for the [ElunaSpellInfo].
     *
     * @param uint32 index : the totem category index (0-1)
     * @return uint32 totemCategory
     */
    int GetTotemCategory(Eluna* E, ElunaSpellInfo* spellInfo)
    {
        uint32 index = E->CHECKVAL<uint32>(2);
        if (index >= 2)
            return luaL_argerror(E->L, 2, "index out of range (0-1)");
        E->Push(spellInfo->GetSpellInfo()->TotemCategory[index]);
        return 1;
    }

    /**
     * Returns the spell visual ID at the given index for the [ElunaSpellInfo].
     *
     * @param uint32 index : the visual index (0-1)
     * @return uint32 spellVisual
     */
    int GetSpellVisual(Eluna* E, ElunaSpellInfo* spellInfo)
    {
        uint32 index = E->CHECKVAL<uint32>(2);
        if (index >= 2)
            return luaL_argerror(E->L, 2, "index out of range (0-1)");
        E->Push(spellInfo->GetSpellInfo()->SpellVisual[index]);
        return 1;
    }

    /**
     * Returns the spell icon ID of the [ElunaSpellInfo].
     *
     * @return uint32 spellIconID
     */
    int GetSpellIconID(Eluna* E, ElunaSpellInfo* spellInfo)
    {
        E->Push(spellInfo->GetSpellInfo()->SpellIconID);
        return 1;
    }

    /**
     * Returns the active icon ID of the [ElunaSpellInfo].
     *
     * @return uint32 activeIconID
     */
    int GetActiveIconID(Eluna* E, ElunaSpellInfo* spellInfo)
    {
        E->Push(spellInfo->GetSpellInfo()->ActiveIconID);
        return 1;
    }

    /**
     * Returns the priority of the [ElunaSpellInfo].
     *
     * @return uint32 priority
     */
    int GetPriority(Eluna* E, ElunaSpellInfo* spellInfo)
    {
        E->Push(spellInfo->GetSpellInfo()->Priority);
        return 1;
    }

    /**
     * Returns the maximum target level of the [ElunaSpellInfo].
     *
     * @return uint32 maxTargetLevel
     */
    int GetMaxTargetLevel(Eluna* E, ElunaSpellInfo* spellInfo)
    {
        E->Push(spellInfo->GetSpellInfo()->MaxTargetLevel);
        return 1;
    }

    /**
     * Returns the maximum number of affected targets of the [ElunaSpellInfo].
     *
     * @return uint32 maxAffectedTargets
     */
    int GetMaxAffectedTargets(Eluna* E, ElunaSpellInfo* spellInfo)
    {
        E->Push(spellInfo->GetSpellInfo()->MaxAffectedTargets);
        return 1;
    }

    /**
     * Returns the spell family name of the [ElunaSpellInfo].
     *
     * @return uint32 spellFamilyName
     */
    int GetSpellFamilyName(Eluna* E, ElunaSpellInfo* spellInfo)
    {
        E->Push(spellInfo->GetSpellInfo()->SpellFamilyName);
        return 1;
    }

    /**
     * Returns the spell family flags of the [ElunaSpellInfo] at the given index.
     * The flags are a 96-bit value split into three uint32 components (index 0-2).
     *
     * @param uint32 index : the flag index (0-2)
     * @return uint32 spellFamilyFlags
     */
    int GetSpellFamilyFlags(Eluna* E, ElunaSpellInfo* spellInfo)
    {
        uint32 index = E->CHECKVAL<uint32>(2);
        if (index >= 3)
            return luaL_argerror(E->L, 2, "index out of range (0-2)");
        E->Push(spellInfo->GetSpellInfo()->SpellFamilyFlags[index]);
        return 1;
    }

    /**
     * Returns the damage class of the [ElunaSpellInfo].
     *
     * @return uint32 dmgClass
     */
    int GetDmgClass(Eluna* E, ElunaSpellInfo* spellInfo)
    {
        E->Push(spellInfo->GetSpellInfo()->DmgClass);
        return 1;
    }

    /**
     * Returns the prevention type of the [ElunaSpellInfo].
     *
     * @return uint32 preventionType
     */
    int GetPreventionType(Eluna* E, ElunaSpellInfo* spellInfo)
    {
        E->Push(spellInfo->GetSpellInfo()->PreventionType);
        return 1;
    }

    /**
     * Returns the area group ID of the [ElunaSpellInfo].
     *
     * @return int32 areaGroupId
     */
    int GetAreaGroupId(Eluna* E, ElunaSpellInfo* spellInfo)
    {
        E->Push(spellInfo->GetSpellInfo()->AreaGroupId);
        return 1;
    }

    /**
     * Returns the school mask of the [ElunaSpellInfo].
     *
     * @return uint32 schoolMask
     */
    int GetSchoolMask(Eluna* E, ElunaSpellInfo* spellInfo)
    {
        E->Push(spellInfo->GetSpellInfo()->SchoolMask);
        return 1;
    }

    /**
     * Returns the duration in milliseconds of the [ElunaSpellInfo].
     *
     * @return int32 duration
     */
    int GetDuration(Eluna* E, ElunaSpellInfo* spellInfo)
    {
        E->Push(spellInfo->GetSpellInfo()->GetDuration());
        return 1;
    }

    /**
     * Returns the maximum duration in milliseconds of the [ElunaSpellInfo].
     *
     * @return int32 maxDuration
     */
    int GetMaxDuration(Eluna* E, ElunaSpellInfo* spellInfo)
    {
        E->Push(spellInfo->GetSpellInfo()->GetMaxDuration());
        return 1;
    }

    /**
     * Returns the maximum range of the [ElunaSpellInfo].
     *
     * @return float maxRange
     */
    int GetMaxRange(Eluna* E, ElunaSpellInfo* spellInfo)
    {
        E->Push(spellInfo->GetSpellInfo()->GetMaxRange());
        return 1;
    }

    /**
     * Returns the minimum range of the [ElunaSpellInfo].
     *
     * @return float minRange
     */
    int GetMinRange(Eluna* E, ElunaSpellInfo* spellInfo)
    {
        E->Push(spellInfo->GetSpellInfo()->GetMinRange());
        return 1;
    }

    /**
     * Returns the maximum number of ticks of the [ElunaSpellInfo].
     *
     * @return uint32 maxTicks
     */
    int GetMaxTicks(Eluna* E, ElunaSpellInfo* spellInfo)
    {
        E->Push(spellInfo->GetSpellInfo()->GetMaxTicks());
        return 1;
    }

    /**
     * Returns the category of the [ElunaSpellInfo].
     *
     * @return uint32 category
     */
    int GetCategory(Eluna* E, ElunaSpellInfo* spellInfo)
    {
        E->Push(spellInfo->GetSpellInfo()->GetCategory());
        return 1;
    }

    /**
     * Returns the rank of the [ElunaSpellInfo].
     *
     * @return uint8 rank
     */
    int GetRank(Eluna* E, ElunaSpellInfo* spellInfo)
    {
        E->Push(spellInfo->GetSpellInfo()->GetRank());
        return 1;
    }

    /**
     * Returns a bitmask of all mechanics used across all effects of the [ElunaSpellInfo].
     *
     * @return uint32 mechanicMask
     */
    int GetAllEffectsMechanicMask(Eluna* E, ElunaSpellInfo* spellInfo)
    {
        E->Push(spellInfo->GetSpellInfo()->GetAllEffectsMechanicMask());
        return 1;
    }

    /**
     * Returns the allowed mechanic mask of the [ElunaSpellInfo].
     *
     * @return uint32 allowedMechanicMask
     */
    int GetAllowedMechanicMask(Eluna* E, ElunaSpellInfo* spellInfo)
    {
        E->Push(spellInfo->GetSpellInfo()->GetAllowedMechanicMask());
        return 1;
    }

    /**
     * Returns the explicit target mask of the [ElunaSpellInfo].
     *
     * @return uint32 explicitTargetMask
     */
    int GetExplicitTargetMask(Eluna* E, ElunaSpellInfo* spellInfo)
    {
        E->Push(spellInfo->GetSpellInfo()->GetExplicitTargetMask());
        return 1;
    }

    /**
     * Returns the aura state of the [ElunaSpellInfo].
     *
     * @return uint32 auraState
     */
    int GetAuraState(Eluna* E, ElunaSpellInfo* spellInfo)
    {
        E->Push(spellInfo->GetSpellInfo()->GetAuraState());
        return 1;
    }

    /**
     * Returns the spell specific type of the [ElunaSpellInfo].
     *
     * @return uint32 spellSpecific
     */
    int GetSpellSpecific(Eluna* E, ElunaSpellInfo* spellInfo)
    {
        E->Push(spellInfo->GetSpellInfo()->GetSpellSpecific());
        return 1;
    }

    /**
     * Returns the weapon attack type of the [ElunaSpellInfo].
     *
     * @return uint32 attackType
     */
    int GetAttackType(Eluna* E, ElunaSpellInfo* spellInfo)
    {
        E->Push(spellInfo->GetSpellInfo()->GetAttackType());
        return 1;
    }

    /**
     * Returns the mechanic mask for the given effect mask of the [ElunaSpellInfo].
     *
     * @param uint32 effectMask : bitmask of effect indices to check
     * @return uint32 mechanicMask
     */
    int GetSpellMechanicMaskByEffectMask(Eluna* E, ElunaSpellInfo* spellInfo)
    {
        uint32 effectMask = E->CHECKVAL<uint32>(2);
        E->Push(spellInfo->GetSpellInfo()->GetSpellMechanicMaskByEffectMask(effectMask));
        return 1;
    }

    /**
     * Returns the mechanic mask for the given effect index of the [ElunaSpellInfo].
     *
     * @param uint32 effIndex : the effect index (0-MAX_SPELL_EFFECTS-1)
     * @return uint32 mechanicMask
     */
    int GetEffectMechanicMask(Eluna* E, ElunaSpellInfo* spellInfo)
    {
        uint32 effIndex = E->CHECKVAL<uint32>(2);
        if (effIndex >= MAX_SPELL_EFFECTS)
            return luaL_argerror(E->L, 2, "effect index out of range");
        E->Push(spellInfo->GetSpellInfo()->GetEffectMechanicMask(static_cast<SpellEffIndex>(effIndex)));
        return 1;
    }

    /**
     * Returns the mechanic for the given effect index of the [ElunaSpellInfo].
     *
     * @param uint32 effIndex : the effect index (0-MAX_SPELL_EFFECTS-1)
     * @return uint32 mechanic
     */
    int GetEffectMechanic(Eluna* E, ElunaSpellInfo* spellInfo)
    {
        uint32 effIndex = E->CHECKVAL<uint32>(2);
        if (effIndex >= MAX_SPELL_EFFECTS)
            return luaL_argerror(E->L, 2, "effect index out of range");
        E->Push(spellInfo->GetSpellInfo()->GetEffectMechanic(static_cast<SpellEffIndex>(effIndex)));
        return 1;
    }

    /**
     * Returns the diminishing returns group for the [ElunaSpellInfo].
     *
     * @param bool triggered : whether the spell is triggered
     * @return uint32 diminishingGroup
     */
    int GetDiminishingReturnsGroupForSpell(Eluna* E, ElunaSpellInfo* spellInfo)
    {
        bool triggered = E->CHECKVAL<bool>(2);
        E->Push(spellInfo->GetSpellInfo()->GetDiminishingReturnsGroupForSpell(triggered));
        return 1;
    }

    /**
     * Returns the diminishing returns group type for the [ElunaSpellInfo].
     *
     * @param bool triggered : whether the spell is triggered
     * @return uint32 diminishingGroupType
     */
    int GetDiminishingReturnsGroupType(Eluna* E, ElunaSpellInfo* spellInfo)
    {
        bool triggered = E->CHECKVAL<bool>(2);
        E->Push(spellInfo->GetSpellInfo()->GetDiminishingReturnsGroupType(triggered));
        return 1;
    }

    /**
     * Returns the diminishing returns max level for the [ElunaSpellInfo].
     *
     * @param bool triggered : whether the spell is triggered
     * @return uint32 diminishingMaxLevel
     */
    int GetDiminishingReturnsMaxLevel(Eluna* E, ElunaSpellInfo* spellInfo)
    {
        bool triggered = E->CHECKVAL<bool>(2);
        E->Push(spellInfo->GetSpellInfo()->GetDiminishingReturnsMaxLevel(triggered));
        return 1;
    }

    /**
     * Returns the diminishing returns limit duration in milliseconds for the [ElunaSpellInfo].
     *
     * @param bool triggered : whether the spell is triggered
     * @return int32 diminishingLimitDuration
     */
    int GetDiminishingReturnsLimitDuration(Eluna* E, ElunaSpellInfo* spellInfo)
    {
        bool triggered = E->CHECKVAL<bool>(2);
        E->Push(spellInfo->GetSpellInfo()->GetDiminishingReturnsLimitDuration(triggered));
        return 1;
    }

    /**
     * Returns the calculated cast time in milliseconds of the [ElunaSpellInfo].
     *
     * @return uint32 castTime
     */
    int CalcCastTime(Eluna* E, ElunaSpellInfo* spellInfo)
    {
        E->Push(spellInfo->GetSpellInfo()->CalcCastTime());
        return 1;
    }

    /**
     * Returns `true` if the [ElunaSpellInfo] is a passive spell, `false` otherwise.
     *
     * @return bool isPassive
     */
    int IsPassive(Eluna* E, ElunaSpellInfo* spellInfo)
    {
        E->Push(spellInfo->GetSpellInfo()->IsPassive());
        return 1;
    }

    /**
     * Returns `true` if the [ElunaSpellInfo] is autocastable, `false` otherwise.
     *
     * @return bool isAutocastable
     */
    int IsAutocastable(Eluna* E, ElunaSpellInfo* spellInfo)
    {
        E->Push(spellInfo->GetSpellInfo()->IsAutocastable());
        return 1;
    }

    /**
     * Returns `true` if the [ElunaSpellInfo] is stackable with ranks, `false` otherwise.
     *
     * @return bool isStackableWithRanks
     */
    int IsStackableWithRanks(Eluna* E, ElunaSpellInfo* spellInfo)
    {
        E->Push(spellInfo->GetSpellInfo()->IsStackableWithRanks());
        return 1;
    }

    /**
     * Returns `true` if the [ElunaSpellInfo] is a passive spell stackable with ranks, `false` otherwise.
     *
     * @return bool isPassiveStackableWithRanks
     */
    int IsPassiveStackableWithRanks(Eluna* E, ElunaSpellInfo* spellInfo)
    {
        E->Push(spellInfo->GetSpellInfo()->IsPassiveStackableWithRanks());
        return 1;
    }

    /**
     * Returns `true` if the [ElunaSpellInfo] occupies multiple aura slots, `false` otherwise.
     *
     * @return bool isMultiSlotAura
     */
    int IsMultiSlotAura(Eluna* E, ElunaSpellInfo* spellInfo)
    {
        E->Push(spellInfo->GetSpellInfo()->IsMultiSlotAura());
        return 1;
    }

    /**
     * Returns `true` if the [ElunaSpellInfo] can stack on one slot from different casters, `false` otherwise.
     *
     * @return bool isStackableOnOneSlotWithDifferentCasters
     */
    int IsStackableOnOneSlotWithDifferentCasters(Eluna* E, ElunaSpellInfo* spellInfo)
    {
        E->Push(spellInfo->GetSpellInfo()->IsStackableOnOneSlotWithDifferentCasters());
        return 1;
    }

    /**
     * Returns `true` if the [ElunaSpellInfo] cooldown is started on event, `false` otherwise.
     *
     * @return bool isCooldownStartedOnEvent
     */
    int IsCooldownStartedOnEvent(Eluna* E, ElunaSpellInfo* spellInfo)
    {
        E->Push(spellInfo->GetSpellInfo()->IsCooldownStartedOnEvent());
        return 1;
    }

    /**
     * Returns `true` if the [ElunaSpellInfo] persists through death, `false` otherwise.
     *
     * @return bool isDeathPersistent
     */
    int IsDeathPersistent(Eluna* E, ElunaSpellInfo* spellInfo)
    {
        E->Push(spellInfo->GetSpellInfo()->IsDeathPersistent());
        return 1;
    }

    /**
     * Returns `true` if the [ElunaSpellInfo] requires the target to be dead, `false` otherwise.
     *
     * @return bool isRequiringDeadTarget
     */
    int IsRequiringDeadTarget(Eluna* E, ElunaSpellInfo* spellInfo)
    {
        E->Push(spellInfo->GetSpellInfo()->IsRequiringDeadTarget());
        return 1;
    }

    /**
     * Returns `true` if the [ElunaSpellInfo] allows targeting dead units, `false` otherwise.
     *
     * @return bool isAllowingDeadTarget
     */
    int IsAllowingDeadTarget(Eluna* E, ElunaSpellInfo* spellInfo)
    {
        E->Push(spellInfo->GetSpellInfo()->IsAllowingDeadTarget());
        return 1;
    }

    /**
     * Returns `true` if the [ElunaSpellInfo] is a group buff, `false` otherwise.
     *
     * @return bool isGroupBuff
     */
    int IsGroupBuff(Eluna* E, ElunaSpellInfo* spellInfo)
    {
        E->Push(spellInfo->GetSpellInfo()->IsGroupBuff());
        return 1;
    }

    /**
     * Returns `true` if the [ElunaSpellInfo] can be used in combat, `false` otherwise.
     *
     * @return bool canBeUsedInCombat
     */
    int CanBeUsedInCombat(Eluna* E, ElunaSpellInfo* spellInfo)
    {
        E->Push(spellInfo->GetSpellInfo()->CanBeUsedInCombat());
        return 1;
    }

    /**
     * Returns `true` if the [ElunaSpellInfo] is a positive spell, `false` otherwise.
     *
     * @return bool isPositive
     */
    int IsPositive(Eluna* E, ElunaSpellInfo* spellInfo)
    {
        E->Push(spellInfo->GetSpellInfo()->IsPositive());
        return 1;
    }

    /**
     * Returns `true` if the effect at the given index of the [ElunaSpellInfo] is positive, `false` otherwise.
     *
     * @param uint8 effIndex : the effect index (0-MAX_SPELL_EFFECTS-1)
     * @return bool isPositiveEffect
     */
    int IsPositiveEffect(Eluna* E, ElunaSpellInfo* spellInfo)
    {
        uint8 effIndex = E->CHECKVAL<uint8>(2);
        if (effIndex >= MAX_SPELL_EFFECTS)
            return luaL_argerror(E->L, 2, "effect index out of range");
        E->Push(spellInfo->GetSpellInfo()->IsPositiveEffect(effIndex));
        return 1;
    }

    /**
     * Returns `true` if the [ElunaSpellInfo] is a channeled spell, `false` otherwise.
     *
     * @return bool isChanneled
     */
    int IsChanneled(Eluna* E, ElunaSpellInfo* spellInfo)
    {
        E->Push(spellInfo->GetSpellInfo()->IsChanneled());
        return 1;
    }

    /**
     * Returns `true` if the [ElunaSpellInfo] allows movement while channeling, `false` otherwise.
     *
     * @return bool isMoveAllowedChannel
     */
    int IsMoveAllowedChannel(Eluna* E, ElunaSpellInfo* spellInfo)
    {
        E->Push(spellInfo->GetSpellInfo()->IsMoveAllowedChannel());
        return 1;
    }

    /**
     * Returns `true` if the [ElunaSpellInfo] requires combo points, `false` otherwise.
     *
     * @return bool needsComboPoints
     */
    int NeedsComboPoints(Eluna* E, ElunaSpellInfo* spellInfo)
    {
        E->Push(spellInfo->GetSpellInfo()->NeedsComboPoints());
        return 1;
    }

    /**
     * Returns `true` if the [ElunaSpellInfo] is a next melee swing spell, `false` otherwise.
     *
     * @return bool isNextMeleeSwingSpell
     */
    int IsNextMeleeSwingSpell(Eluna* E, ElunaSpellInfo* spellInfo)
    {
        E->Push(spellInfo->GetSpellInfo()->IsNextMeleeSwingSpell());
        return 1;
    }

    /**
     * Returns `true` if the [ElunaSpellInfo] breaks stealth, `false` otherwise.
     *
     * @return bool isBreakingStealth
     */
    int IsBreakingStealth(Eluna* E, ElunaSpellInfo* spellInfo)
    {
        E->Push(spellInfo->GetSpellInfo()->IsBreakingStealth());
        return 1;
    }

    /**
     * Returns `true` if the [ElunaSpellInfo] is a ranged weapon spell, `false` otherwise.
     *
     * @return bool isRangedWeaponSpell
     */
    int IsRangedWeaponSpell(Eluna* E, ElunaSpellInfo* spellInfo)
    {
        E->Push(spellInfo->GetSpellInfo()->IsRangedWeaponSpell());
        return 1;
    }

    /**
     * Returns `true` if the [ElunaSpellInfo] is an auto repeat ranged spell, `false` otherwise.
     *
     * @return bool isAutoRepeatRangedSpell
     */
    int IsAutoRepeatRangedSpell(Eluna* E, ElunaSpellInfo* spellInfo)
    {
        E->Push(spellInfo->GetSpellInfo()->IsAutoRepeatRangedSpell());
        return 1;
    }

    /**
     * Returns `true` if the [ElunaSpellInfo] has initial aggro, `false` otherwise.
     *
     * @return bool hasInitialAggro
     */
    int HasInitialAggro(Eluna* E, ElunaSpellInfo* spellInfo)
    {
        E->Push(spellInfo->GetSpellInfo()->HasInitialAggro());
        return 1;
    }

    /**
     * Returns `true` if the [ElunaSpellInfo] is ranked, `false` otherwise.
     *
     * @return bool isRanked
     */
    int IsRanked(Eluna* E, ElunaSpellInfo* spellInfo)
    {
        E->Push(spellInfo->GetSpellInfo()->IsRanked());
        return 1;
    }

    /**
     * Returns `true` if the [ElunaSpellInfo] affects an area, `false` otherwise.
     *
     * @return bool isAffectingArea
     */
    int IsAffectingArea(Eluna* E, ElunaSpellInfo* spellInfo)
    {
        E->Push(spellInfo->GetSpellInfo()->IsAffectingArea());
        return 1;
    }

    /**
     * Returns `true` if the [ElunaSpellInfo] targets an area, `false` otherwise.
     *
     * @return bool isTargetingArea
     */
    int IsTargetingArea(Eluna* E, ElunaSpellInfo* spellInfo)
    {
        E->Push(spellInfo->GetSpellInfo()->IsTargetingArea());
        return 1;
    }

    /**
     * Returns `true` if the [ElunaSpellInfo] needs an explicit unit target, `false` otherwise.
     *
     * @return bool needsExplicitUnitTarget
     */
    int NeedsExplicitUnitTarget(Eluna* E, ElunaSpellInfo* spellInfo)
    {
        E->Push(spellInfo->GetSpellInfo()->NeedsExplicitUnitTarget());
        return 1;
    }

    /**
     * Returns `true` if the [ElunaSpellInfo] is a self cast spell, `false` otherwise.
     *
     * @return bool isSelfCast
     */
    int IsSelfCast(Eluna* E, ElunaSpellInfo* spellInfo)
    {
        E->Push(spellInfo->GetSpellInfo()->IsSelfCast());
        return 1;
    }

    /**
     * Returns `true` if the [ElunaSpellInfo] can only have a single target active at a time, `false` otherwise.
     *
     * @return bool isSingleTarget
     */
    int IsSingleTarget(Eluna* E, ElunaSpellInfo* spellInfo)
    {
        E->Push(spellInfo->GetSpellInfo()->IsSingleTarget());
        return 1;
    }

    /**
     * Returns `true` if the [ElunaSpellInfo] is an explicit discovery spell, `false` otherwise.
     *
     * @return bool isExplicitDiscovery
     */
    int IsExplicitDiscovery(Eluna* E, ElunaSpellInfo* spellInfo)
    {
        E->Push(spellInfo->GetSpellInfo()->IsExplicitDiscovery());
        return 1;
    }

    /**
     * Returns `true` if the [ElunaSpellInfo] is a loot crafting spell, `false` otherwise.
     *
     * @return bool isLootCrafting
     */
    int IsLootCrafting(Eluna* E, ElunaSpellInfo* spellInfo)
    {
        E->Push(spellInfo->GetSpellInfo()->IsLootCrafting());
        return 1;
    }

    /**
     * Returns `true` if the [ElunaSpellInfo] is a profession or riding spell, `false` otherwise.
     *
     * @return bool isProfessionOrRiding
     */
    int IsProfessionOrRiding(Eluna* E, ElunaSpellInfo* spellInfo)
    {
        E->Push(spellInfo->GetSpellInfo()->IsProfessionOrRiding());
        return 1;
    }

    /**
     * Returns `true` if the [ElunaSpellInfo] is a profession spell, `false` otherwise.
     *
     * @return bool isProfession
     */
    int IsProfession(Eluna* E, ElunaSpellInfo* spellInfo)
    {
        E->Push(spellInfo->GetSpellInfo()->IsProfession());
        return 1;
    }

    /**
     * Returns `true` if the [ElunaSpellInfo] is a primary profession spell, `false` otherwise.
     *
     * @return bool isPrimaryProfession
     */
    int IsPrimaryProfession(Eluna* E, ElunaSpellInfo* spellInfo)
    {
        E->Push(spellInfo->GetSpellInfo()->IsPrimaryProfession());
        return 1;
    }

    /**
     * Returns `true` if the [ElunaSpellInfo] is the first rank of a primary profession spell, `false` otherwise.
     *
     * @return bool isPrimaryProfessionFirstRank
     */
    int IsPrimaryProfessionFirstRank(Eluna* E, ElunaSpellInfo* spellInfo)
    {
        E->Push(spellInfo->GetSpellInfo()->IsPrimaryProfessionFirstRank());
        return 1;
    }

    /**
     * Returns `true` if the [ElunaSpellInfo] is an ability learned with a profession, `false` otherwise.
     *
     * @return bool isAbilityLearnedWithProfession
     */
    int IsAbilityLearnedWithProfession(Eluna* E, ElunaSpellInfo* spellInfo)
    {
        E->Push(spellInfo->GetSpellInfo()->IsAbilityLearnedWithProfession());
        return 1;
    }

    /**
     * Returns `true` if the [ElunaSpellInfo] is affected by spell mods, `false` otherwise.
     *
     * @return bool isAffectedBySpellMods
     */
    int IsAffectedBySpellMods(Eluna* E, ElunaSpellInfo* spellInfo)
    {
        E->Push(spellInfo->GetSpellInfo()->IsAffectedBySpellMods());
        return 1;
    }

    /**
     * Returns `true` if the [ElunaSpellInfo] has the given spell effect, `false` otherwise.
     *
     * @param uint32 effect : the [SpellEffects] to check for
     * @return bool hasEffect
     */
    int HasEffect(Eluna* E, ElunaSpellInfo* spellInfo)
    {
        SpellEffects effect = static_cast<SpellEffects>(E->CHECKVAL<uint32>(2));
        E->Push(spellInfo->GetSpellInfo()->HasEffect(effect));
        return 1;
    }

    /**
     * Returns `true` if the [ElunaSpellInfo] has the given aura type, `false` otherwise.
     *
     * @param uint32 aura : the [AuraType] to check for
     * @return bool hasAura
     */
    int HasAura(Eluna* E, ElunaSpellInfo* spellInfo)
    {
        AuraType aura = static_cast<AuraType>(E->CHECKVAL<uint32>(2));
        E->Push(spellInfo->GetSpellInfo()->HasAura(aura));
        return 1;
    }

    /**
     * Returns `true` if the [ElunaSpellInfo] has an area aura effect, `false` otherwise.
     *
     * @return bool hasAreaAuraEffect
     */
    int HasAreaAuraEffect(Eluna* E, ElunaSpellInfo* spellInfo)
    {
        E->Push(spellInfo->GetSpellInfo()->HasAreaAuraEffect());
        return 1;
    }

    /**
     * Returns `true` if the [ElunaSpellInfo] only has damage effects, `false` otherwise.
     *
     * @return bool hasOnlyDamageEffects
     */
    int HasOnlyDamageEffects(Eluna* E, ElunaSpellInfo* spellInfo)
    {
        E->Push(spellInfo->GetSpellInfo()->HasOnlyDamageEffects());
        return 1;
    }

    /**
     * Returns `true` if the [ElunaSpellInfo] is affected by the given spell family and flags, `false` otherwise.
     * The flags are a 96-bit value split into three uint32 components.
     *
     * @param uint32 familyName : the spell family name to check
     * @param uint32 flag0 : the first 32 bits of the spell family flags
     * @param uint32 flag1 : the second 32 bits of the spell family flags
     * @param uint32 flag2 : the third 32 bits of the spell family flags
     * @return bool isAffected
     */
    int IsAffected(Eluna* E, ElunaSpellInfo* spellInfo)
    {
        uint32 familyName = E->CHECKVAL<uint32>(2);
        uint32 f0 = E->CHECKVAL<uint32>(3);
        uint32 f1 = E->CHECKVAL<uint32>(4);
        uint32 f2 = E->CHECKVAL<uint32>(5);
        E->Push(spellInfo->GetSpellInfo()->IsAffected(familyName, flag96(f0, f1, f2)));
        return 1;
    }

    /**
     * Returns `true` if the [ElunaSpellInfo] is affected by the given [SpellModifier], `false` otherwise.
     *
     * @param [SpellModifier] mod : the spell modifier to check
     * @return bool isAffectedBySpellMod
     */
    int IsAffectedBySpellMod(Eluna* E, ElunaSpellInfo* spellInfo)
    {
        SpellModifier* mod = E->CHECKOBJ<SpellModifier>(2);
        E->Push(spellInfo->GetSpellInfo()->IsAffectedBySpellMod(mod));
        return 1;
    }

    /**
     * Returns `true` if the [ElunaSpellInfo] is the same rank as the given [ElunaSpellInfo], `false` otherwise.
     *
     * @param [ElunaSpellInfo] spellInfo : the spell info to compare against
     * @return bool isRankOf
     */
    int IsRankOf(Eluna* E, ElunaSpellInfo* spellInfo)
    {
        ElunaSpellInfo* other = E->CHECKOBJ<ElunaSpellInfo>(2);
        E->Push(spellInfo->GetSpellInfo()->IsRankOf(other->GetSpellInfo()));
        return 1;
    }

    /**
     * Returns `true` if the [ElunaSpellInfo] is a different rank of the given [ElunaSpellInfo], `false` otherwise.
     *
     * @param [ElunaSpellInfo] spellInfo : the spell info to compare against
     * @return bool isDifferentRankOf
     */
    int IsDifferentRankOf(Eluna* E, ElunaSpellInfo* spellInfo)
    {
        ElunaSpellInfo* other = E->CHECKOBJ<ElunaSpellInfo>(2);
        E->Push(spellInfo->GetSpellInfo()->IsDifferentRankOf(other->GetSpellInfo()));
        return 1;
    }

    /**
     * Returns `true` if the [ElunaSpellInfo] is a higher rank than the given [ElunaSpellInfo], `false` otherwise.
     *
     * @param [ElunaSpellInfo] spellInfo : the spell info to compare against
     * @return bool isHighRankOf
     */
    int IsHighRankOf(Eluna* E, ElunaSpellInfo* spellInfo)
    {
        ElunaSpellInfo* other = E->CHECKOBJ<ElunaSpellInfo>(2);
        E->Push(spellInfo->GetSpellInfo()->IsHighRankOf(other->GetSpellInfo()));
        return 1;
    }

    /**
     * Returns `true` if the [ElunaSpellInfo] can pierce the immunity provided by the given [ElunaSpellInfo], `false` otherwise.
     *
     * @param [ElunaSpellInfo] auraSpellInfo : the aura spell info to check against
     * @return bool canPierceImmuneAura
     */
    int CanPierceImmuneAura(Eluna* E, ElunaSpellInfo* spellInfo)
    {
        ElunaSpellInfo* other = E->CHECKOBJ<ElunaSpellInfo>(2);
        E->Push(spellInfo->GetSpellInfo()->CanPierceImmuneAura(other->GetSpellInfo()));
        return 1;
    }

    /**
     * Returns `true` if the [ElunaSpellInfo] can dispel the given [ElunaSpellInfo], `false` otherwise.
     *
     * @param [ElunaSpellInfo] auraSpellInfo : the aura spell info to check against
     * @return bool canDispelAura
     */
    int CanDispelAura(Eluna* E, ElunaSpellInfo* spellInfo)
    {
        ElunaSpellInfo* other = E->CHECKOBJ<ElunaSpellInfo>(2);
        E->Push(spellInfo->GetSpellInfo()->CanDispelAura(other->GetSpellInfo()));
        return 1;
    }

    /**
     * Returns `true` if the [ElunaSpellInfo] can provide immunity against the given [ElunaSpellInfo], `false` otherwise.
     *
     * @param [ElunaSpellInfo] auraSpellInfo : the aura spell info to check against
     * @return bool canSpellProvideImmunityAgainstAura
     */
    int CanSpellProvideImmunityAgainstAura(Eluna* E, ElunaSpellInfo* spellInfo)
    {
        ElunaSpellInfo* other = E->CHECKOBJ<ElunaSpellInfo>(2);
        E->Push(spellInfo->GetSpellInfo()->CanSpellProvideImmunityAgainstAura(other->GetSpellInfo()));
        return 1;
    }

    /**
     * Returns `true` if the [ElunaSpellInfo] is exclusively stacking with the given [ElunaSpellInfo] by specific aura, `false` otherwise.
     *
     * @param [ElunaSpellInfo] spellInfo : the spell info to compare against
     * @return bool isAuraExclusiveBySpecificWith
     */
    int IsAuraExclusiveBySpecificWith(Eluna* E, ElunaSpellInfo* spellInfo)
    {
        ElunaSpellInfo* other = E->CHECKOBJ<ElunaSpellInfo>(2);
        E->Push(spellInfo->GetSpellInfo()->IsAuraExclusiveBySpecificWith(other->GetSpellInfo()));
        return 1;
    }

    /**
     * Returns `true` if the [ElunaSpellInfo] is exclusively stacking per caster with the given [ElunaSpellInfo] by specific aura, `false` otherwise.
     *
     * @param [ElunaSpellInfo] spellInfo : the spell info to compare against
     * @return bool isAuraExclusiveBySpecificPerCasterWith
     */
    int IsAuraExclusiveBySpecificPerCasterWith(Eluna* E, ElunaSpellInfo* spellInfo)
    {
        ElunaSpellInfo* other = E->CHECKOBJ<ElunaSpellInfo>(2);
        E->Push(spellInfo->GetSpellInfo()->IsAuraExclusiveBySpecificPerCasterWith(other->GetSpellInfo()));
        return 1;
    }

    /**
     * Returns `true` if the given [Item] fits the requirements of the [ElunaSpellInfo], `false` otherwise.
     *
     * @param [Item] item : the item to check
     * @return bool isItemFitToSpellRequirements
     */
    int IsItemFitToSpellRequirements(Eluna* E, ElunaSpellInfo* spellInfo)
    {
        Item* item = E->CHECKOBJ<Item>(2);
        E->Push(spellInfo->GetSpellInfo()->IsItemFitToSpellRequirements(item));
        return 1;
    }

    /**
     * Returns `true` if the [ElunaSpellInfo] is an ability of the given skill type, `false` otherwise.
     *
     * @param uint32 skillType : the skill type to check
     * @return bool isAbilityOfSkillType
     */
    int IsAbilityOfSkillType(Eluna* E, ElunaSpellInfo* spellInfo)
    {
        uint32 skillType = E->CHECKVAL<uint32>(2);
        E->Push(spellInfo->GetSpellInfo()->IsAbilityOfSkillType(skillType));
        return 1;
    }

    /**
     * Returns `true` if the [ElunaSpellInfo] needs to be triggered by the given triggering [ElunaSpellInfo], `false` otherwise.
     *
     * @param [ElunaSpellInfo] triggeringSpell : the triggering spell info to check against
     * @return bool needsToBeTriggeredByCaster
     */
    int NeedsToBeTriggeredByCaster(Eluna* E, ElunaSpellInfo* spellInfo)
    {
        ElunaSpellInfo* triggeringSpell = E->CHECKOBJ<ElunaSpellInfo>(2);
        E->Push(spellInfo->GetSpellInfo()->NeedsToBeTriggeredByCaster(triggeringSpell->GetSpellInfo()));
        return 1;
    }

    /**
     * Checks whether the [ElunaSpellInfo] can be cast on the given target by the given caster.
     * Returns the [SpellCastResult] of the check.
     *
     * @param [WorldObject] caster : the caster to check from
     * @param [WorldObject] target : the target to check against
     * @return uint32 spellCastResult
     */
    int CheckTarget(Eluna* E, ElunaSpellInfo* spellInfo)
    {
        WorldObject* caster = E->CHECKOBJ<WorldObject>(2);
        WorldObject* target = E->CHECKOBJ<WorldObject>(3);
        E->Push(spellInfo->GetSpellInfo()->CheckTarget(caster, target));
        return 1;
    }

    /**
     * Returns `true` if the given [Unit] matches the required creature type for the [ElunaSpellInfo], `false` otherwise.
     *
     * @param [Unit] target : the unit to check
     * @return bool checkTargetCreatureType
     */
    int CheckTargetCreatureType(Eluna* E, ElunaSpellInfo* spellInfo)
    {
        Unit* target = E->CHECKOBJ<Unit>(2);
        E->Push(spellInfo->GetSpellInfo()->CheckTargetCreatureType(target));
        return 1;
    }

    /**
     * Returns `true` if the [ElunaSpellInfo] cancels the given [AuraEffect], `false` otherwise.
     *
     * @param [AuraEffect] aurEff : the aura effect to check against
     * @return bool spellCancelsAuraEffect
     */
    int SpellCancelsAuraEffect(Eluna* E, ElunaSpellInfo* spellInfo)
    {
        AuraEffect* aurEff = E->CHECKOBJ<AuraEffect>(2);
        E->Push(spellInfo->GetSpellInfo()->SpellCancelsAuraEffect(aurEff));
        return 1;
    }

    /**
     * Returns the effect index of the given effect slot of the [ElunaSpellInfo].
     *
     * @param uint32 effIndex : the effect slot (0-MAX_SPELL_EFFECTS-1)
     * @return uint32 effectIndex
     */
    int GetEffectIndex(Eluna* E, ElunaSpellInfo* spellInfo)
    {
        uint32 effIndex = E->CHECKVAL<uint32>(2);
        if (effIndex >= MAX_SPELL_EFFECTS)
            return luaL_argerror(E->L, 2, "effect index out of range");
        E->Push(static_cast<uint32>(spellInfo->GetSpellInfo()->GetEffect(static_cast<SpellEffIndex>(effIndex)).EffectIndex));
        return 1;
    }

    /**
     * Returns the effect type of the given effect slot of the [ElunaSpellInfo].
     *
     * @param uint32 effIndex : the effect slot (0-MAX_SPELL_EFFECTS-1)
     * @return uint32 effectType
     */
    int GetEffectType(Eluna* E, ElunaSpellInfo* spellInfo)
    {
        uint32 effIndex = E->CHECKVAL<uint32>(2);
        if (effIndex >= MAX_SPELL_EFFECTS)
            return luaL_argerror(E->L, 2, "effect index out of range");
        E->Push(static_cast<uint32>(spellInfo->GetSpellInfo()->GetEffect(static_cast<SpellEffIndex>(effIndex)).Effect));
        return 1;
    }

    /**
     * Returns the aura type applied by the given effect slot of the [ElunaSpellInfo].
     *
     * @param uint32 effIndex : the effect slot (0-MAX_SPELL_EFFECTS-1)
     * @return uint32 applyAuraName
     */
    int GetEffectApplyAuraName(Eluna* E, ElunaSpellInfo* spellInfo)
    {
        uint32 effIndex = E->CHECKVAL<uint32>(2);
        if (effIndex >= MAX_SPELL_EFFECTS)
            return luaL_argerror(E->L, 2, "effect index out of range");
        E->Push(static_cast<uint32>(spellInfo->GetSpellInfo()->GetEffect(static_cast<SpellEffIndex>(effIndex)).ApplyAuraName));
        return 1;
    }

    /**
     * Returns the amplitude in milliseconds of the given effect slot of the [ElunaSpellInfo].
     *
     * @param uint32 effIndex : the effect slot (0-MAX_SPELL_EFFECTS-1)
     * @return uint32 amplitude
     */
    int GetEffectAmplitude(Eluna* E, ElunaSpellInfo* spellInfo)
    {
        uint32 effIndex = E->CHECKVAL<uint32>(2);
        if (effIndex >= MAX_SPELL_EFFECTS)
            return luaL_argerror(E->L, 2, "effect index out of range");
        E->Push(spellInfo->GetSpellInfo()->GetEffect(static_cast<SpellEffIndex>(effIndex)).Amplitude);
        return 1;
    }

    /**
     * Returns the die sides of the given effect slot of the [ElunaSpellInfo].
     *
     * @param uint32 effIndex : the effect slot (0-MAX_SPELL_EFFECTS-1)
     * @return int32 dieSides
     */
    int GetEffectDieSides(Eluna* E, ElunaSpellInfo* spellInfo)
    {
        uint32 effIndex = E->CHECKVAL<uint32>(2);
        if (effIndex >= MAX_SPELL_EFFECTS)
            return luaL_argerror(E->L, 2, "effect index out of range");
        E->Push(spellInfo->GetSpellInfo()->GetEffect(static_cast<SpellEffIndex>(effIndex)).DieSides);
        return 1;
    }

    /**
     * Returns the real points per level of the given effect slot of the [ElunaSpellInfo].
     *
     * @param uint32 effIndex : the effect slot (0-MAX_SPELL_EFFECTS-1)
     * @return float realPointsPerLevel
     */
    int GetEffectRealPointsPerLevel(Eluna* E, ElunaSpellInfo* spellInfo)
    {
        uint32 effIndex = E->CHECKVAL<uint32>(2);
        if (effIndex >= MAX_SPELL_EFFECTS)
            return luaL_argerror(E->L, 2, "effect index out of range");
        E->Push(spellInfo->GetSpellInfo()->GetEffect(static_cast<SpellEffIndex>(effIndex)).RealPointsPerLevel);
        return 1;
    }

    /**
     * Returns the base points of the given effect slot of the [ElunaSpellInfo].
     *
     * @param uint32 effIndex : the effect slot (0-MAX_SPELL_EFFECTS-1)
     * @return int32 basePoints
     */
    int GetEffectBasePoints(Eluna* E, ElunaSpellInfo* spellInfo)
    {
        uint32 effIndex = E->CHECKVAL<uint32>(2);
        if (effIndex >= MAX_SPELL_EFFECTS)
            return luaL_argerror(E->L, 2, "effect index out of range");
        E->Push(spellInfo->GetSpellInfo()->GetEffect(static_cast<SpellEffIndex>(effIndex)).BasePoints);
        return 1;
    }

    /**
     * Returns the points per combo point of the given effect slot of the [ElunaSpellInfo].
     *
     * @param uint32 effIndex : the effect slot (0-MAX_SPELL_EFFECTS-1)
     * @return float pointsPerComboPoint
     */
    int GetEffectPointsPerComboPoint(Eluna* E, ElunaSpellInfo* spellInfo)
    {
        uint32 effIndex = E->CHECKVAL<uint32>(2);
        if (effIndex >= MAX_SPELL_EFFECTS)
            return luaL_argerror(E->L, 2, "effect index out of range");
        E->Push(spellInfo->GetSpellInfo()->GetEffect(static_cast<SpellEffIndex>(effIndex)).PointsPerComboPoint);
        return 1;
    }

    /**
     * Returns the value multiplier of the given effect slot of the [ElunaSpellInfo].
     *
     * @param uint32 effIndex : the effect slot (0-MAX_SPELL_EFFECTS-1)
     * @return float valueMultiplier
     */
    int GetEffectValueMultiplier(Eluna* E, ElunaSpellInfo* spellInfo)
    {
        uint32 effIndex = E->CHECKVAL<uint32>(2);
        if (effIndex >= MAX_SPELL_EFFECTS)
            return luaL_argerror(E->L, 2, "effect index out of range");
        E->Push(spellInfo->GetSpellInfo()->GetEffect(static_cast<SpellEffIndex>(effIndex)).ValueMultiplier);
        return 1;
    }

    /**
     * Returns the damage multiplier of the given effect slot of the [ElunaSpellInfo].
     *
     * @param uint32 effIndex : the effect slot (0-MAX_SPELL_EFFECTS-1)
     * @return float damageMultiplier
     */
    int GetEffectDamageMultiplier(Eluna* E, ElunaSpellInfo* spellInfo)
    {
        uint32 effIndex = E->CHECKVAL<uint32>(2);
        if (effIndex >= MAX_SPELL_EFFECTS)
            return luaL_argerror(E->L, 2, "effect index out of range");
        E->Push(spellInfo->GetSpellInfo()->GetEffect(static_cast<SpellEffIndex>(effIndex)).DamageMultiplier);
        return 1;
    }

    /**
     * Returns the bonus multiplier of the given effect slot of the [ElunaSpellInfo].
     *
     * @param uint32 effIndex : the effect slot (0-MAX_SPELL_EFFECTS-1)
     * @return float bonusMultiplier
     */
    int GetEffectBonusMultiplier(Eluna* E, ElunaSpellInfo* spellInfo)
    {
        uint32 effIndex = E->CHECKVAL<uint32>(2);
        if (effIndex >= MAX_SPELL_EFFECTS)
            return luaL_argerror(E->L, 2, "effect index out of range");
        E->Push(spellInfo->GetSpellInfo()->GetEffect(static_cast<SpellEffIndex>(effIndex)).BonusMultiplier);
        return 1;
    }

    /**
     * Returns the misc value of the given effect slot of the [ElunaSpellInfo].
     *
     * @param uint32 effIndex : the effect slot (0-MAX_SPELL_EFFECTS-1)
     * @return int32 miscValue
     */
    int GetEffectMiscValue(Eluna* E, ElunaSpellInfo* spellInfo)
    {
        uint32 effIndex = E->CHECKVAL<uint32>(2);
        if (effIndex >= MAX_SPELL_EFFECTS)
            return luaL_argerror(E->L, 2, "effect index out of range");
        E->Push(spellInfo->GetSpellInfo()->GetEffect(static_cast<SpellEffIndex>(effIndex)).MiscValue);
        return 1;
    }

    /**
     * Returns the secondary misc value of the given effect slot of the [ElunaSpellInfo].
     *
     * @param uint32 effIndex : the effect slot (0-MAX_SPELL_EFFECTS-1)
     * @return int32 miscValueB
     */
    int GetEffectMiscValueB(Eluna* E, ElunaSpellInfo* spellInfo)
    {
        uint32 effIndex = E->CHECKVAL<uint32>(2);
        if (effIndex >= MAX_SPELL_EFFECTS)
            return luaL_argerror(E->L, 2, "effect index out of range");
        E->Push(spellInfo->GetSpellInfo()->GetEffect(static_cast<SpellEffIndex>(effIndex)).MiscValueB);
        return 1;
    }

    /**
     * Returns the chain target count of the given effect slot of the [ElunaSpellInfo].
     *
     * @param uint32 effIndex : the effect slot (0-MAX_SPELL_EFFECTS-1)
     * @return uint32 chainTarget
     */
    int GetEffectChainTarget(Eluna* E, ElunaSpellInfo* spellInfo)
    {
        uint32 effIndex = E->CHECKVAL<uint32>(2);
        if (effIndex >= MAX_SPELL_EFFECTS)
            return luaL_argerror(E->L, 2, "effect index out of range");
        E->Push(spellInfo->GetSpellInfo()->GetEffect(static_cast<SpellEffIndex>(effIndex)).ChainTarget);
        return 1;
    }

    /**
     * Returns the item type entry of the given effect slot of the [ElunaSpellInfo].
     *
     * @param uint32 effIndex : the effect slot (0-MAX_SPELL_EFFECTS-1)
     * @return uint32 itemType
     */
    int GetEffectItemType(Eluna* E, ElunaSpellInfo* spellInfo)
    {
        uint32 effIndex = E->CHECKVAL<uint32>(2);
        if (effIndex >= MAX_SPELL_EFFECTS)
            return luaL_argerror(E->L, 2, "effect index out of range");
        E->Push(spellInfo->GetSpellInfo()->GetEffect(static_cast<SpellEffIndex>(effIndex)).ItemType);
        return 1;
    }

    /**
     * Returns the trigger spell ID of the given effect slot of the [ElunaSpellInfo].
     *
     * @param uint32 effIndex : the effect slot (0-MAX_SPELL_EFFECTS-1)
     * @return uint32 triggerSpell
     */
    int GetEffectTriggerSpell(Eluna* E, ElunaSpellInfo* spellInfo)
    {
        uint32 effIndex = E->CHECKVAL<uint32>(2);
        if (effIndex >= MAX_SPELL_EFFECTS)
            return luaL_argerror(E->L, 2, "effect index out of range");
        E->Push(spellInfo->GetSpellInfo()->GetEffect(static_cast<SpellEffIndex>(effIndex)).TriggerSpell);
        return 1;
    }

    /**
     * Returns the spell class mask component at the given mask index for the given effect slot of the [ElunaSpellInfo].
     * The mask is a 96-bit value split into three uint32 components (index 0-2).
     *
     * @param uint32 effIndex : the effect slot (0-MAX_SPELL_EFFECTS-1)
     * @param uint32 maskIndex : the mask component index (0-2)
     * @return uint32 spellClassMask
     */
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

    /**
     * Returns the calculated value for the given effect slot of the [ElunaSpellInfo].
     *
     * @param uint32 effIndex : the effect slot (0-MAX_SPELL_EFFECTS-1)
     * @return int32 calcValue
     */
    int GetEffectCalcValue(Eluna* E, ElunaSpellInfo* spellInfo)
    {
        uint32 effIndex = E->CHECKVAL<uint32>(2);
        if (effIndex >= MAX_SPELL_EFFECTS)
            return luaL_argerror(E->L, 2, "effect index out of range");
        E->Push(spellInfo->GetSpellInfo()->GetEffect(static_cast<SpellEffIndex>(effIndex)).CalcValue());
        return 1;
    }

    /**
     * Returns the calculated radius for the given effect slot of the [ElunaSpellInfo].
     *
     * @param uint32 effIndex : the effect slot (0-MAX_SPELL_EFFECTS-1)
     * @return float calcRadius
     */
    int GetEffectCalcRadius(Eluna* E, ElunaSpellInfo* spellInfo)
    {
        uint32 effIndex = E->CHECKVAL<uint32>(2);
        if (effIndex >= MAX_SPELL_EFFECTS)
            return luaL_argerror(E->L, 2, "effect index out of range");
        E->Push(spellInfo->GetSpellInfo()->GetEffect(static_cast<SpellEffIndex>(effIndex)).CalcRadius());
        return 1;
    }

    /**
     * Returns `true` if the given effect slot of the [ElunaSpellInfo] has a radius, `false` otherwise.
     *
     * @param uint32 effIndex : the effect slot (0-MAX_SPELL_EFFECTS-1)
     * @return bool hasRadius
     */
    int GetEffectHasRadius(Eluna* E, ElunaSpellInfo* spellInfo)
    {
        uint32 effIndex = E->CHECKVAL<uint32>(2);
        if (effIndex >= MAX_SPELL_EFFECTS)
            return luaL_argerror(E->L, 2, "effect index out of range");
        E->Push(spellInfo->GetSpellInfo()->GetEffect(static_cast<SpellEffIndex>(effIndex)).HasRadius());
        return 1;
    }

    /**
     * Returns the provided target mask for the given effect slot of the [ElunaSpellInfo].
     *
     * @param uint32 effIndex : the effect slot (0-MAX_SPELL_EFFECTS-1)
     * @return uint32 providedTargetMask
     */
    int GetEffectProvidedTargetMask(Eluna* E, ElunaSpellInfo* spellInfo)
    {
        uint32 effIndex = E->CHECKVAL<uint32>(2);
        if (effIndex >= MAX_SPELL_EFFECTS)
            return luaL_argerror(E->L, 2, "effect index out of range");
        E->Push(spellInfo->GetSpellInfo()->GetEffect(static_cast<SpellEffIndex>(effIndex)).GetProvidedTargetMask());
        return 1;
    }

    /**
     * Returns the implicit target type for the given effect slot of the [ElunaSpellInfo].
     *
     * @param uint32 effIndex : the effect slot (0-MAX_SPELL_EFFECTS-1)
     * @return uint32 implicitTargetType
     */
    int GetEffectImplicitTargetType(Eluna* E, ElunaSpellInfo* spellInfo)
    {
        uint32 effIndex = E->CHECKVAL<uint32>(2);
        if (effIndex >= MAX_SPELL_EFFECTS)
            return luaL_argerror(E->L, 2, "effect index out of range");
        E->Push(static_cast<uint32>(spellInfo->GetSpellInfo()->GetEffect(static_cast<SpellEffIndex>(effIndex)).GetImplicitTargetType()));
        return 1;
    }

    /**
     * Returns the used target object type for the given effect slot of the [ElunaSpellInfo].
     *
     * @param uint32 effIndex : the effect slot (0-MAX_SPELL_EFFECTS-1)
     * @return uint32 usedTargetObjectType
     */
    int GetEffectUsedTargetObjectType(Eluna* E, ElunaSpellInfo* spellInfo)
    {
        uint32 effIndex = E->CHECKVAL<uint32>(2);
        if (effIndex >= MAX_SPELL_EFFECTS)
            return luaL_argerror(E->L, 2, "effect index out of range");
        E->Push(static_cast<uint32>(spellInfo->GetSpellInfo()->GetEffect(static_cast<SpellEffIndex>(effIndex)).GetUsedTargetObjectType()));
        return 1;
    }

    /**
     * Returns `true` if the given effect slot of the [ElunaSpellInfo] is an effect, `false` otherwise.
     *
     * @param uint32 effIndex : the effect slot (0-MAX_SPELL_EFFECTS-1)
     * @return bool isEffect
     */
    int EffectIsEffect(Eluna* E, ElunaSpellInfo* spellInfo)
    {
        uint32 effIndex = E->CHECKVAL<uint32>(2);
        if (effIndex >= MAX_SPELL_EFFECTS)
            return luaL_argerror(E->L, 2, "effect index out of range");
        E->Push(spellInfo->GetSpellInfo()->GetEffect(static_cast<SpellEffIndex>(effIndex)).IsEffect());
        return 1;
    }

    /**
     * Returns `true` if the given effect slot of the [ElunaSpellInfo] is the given effect type, `false` otherwise.
     *
     * @param uint32 effIndex : the effect slot (0-MAX_SPELL_EFFECTS-1)
     * @param uint32 effect : the [SpellEffects] to check for
     * @return bool isEffectType
     */
    int EffectIsEffectType(Eluna* E, ElunaSpellInfo* spellInfo)
    {
        uint32 effIndex = E->CHECKVAL<uint32>(2);
        if (effIndex >= MAX_SPELL_EFFECTS)
            return luaL_argerror(E->L, 2, "effect index out of range");
        SpellEffects effect = static_cast<SpellEffects>(E->CHECKVAL<uint32>(3));
        E->Push(spellInfo->GetSpellInfo()->GetEffect(static_cast<SpellEffIndex>(effIndex)).IsEffect(effect));
        return 1;
    }

    /**
     * Returns `true` if the given effect slot of the [ElunaSpellInfo] applies an aura, `false` otherwise.
     *
     * @param uint32 effIndex : the effect slot (0-MAX_SPELL_EFFECTS-1)
     * @return bool isAura
     */
    int EffectIsAura(Eluna* E, ElunaSpellInfo* spellInfo)
    {
        uint32 effIndex = E->CHECKVAL<uint32>(2);
        if (effIndex >= MAX_SPELL_EFFECTS)
            return luaL_argerror(E->L, 2, "effect index out of range");
        E->Push(spellInfo->GetSpellInfo()->GetEffect(static_cast<SpellEffIndex>(effIndex)).IsAura());
        return 1;
    }

    /**
     * Returns `true` if the given effect slot of the [ElunaSpellInfo] applies the given aura type, `false` otherwise.
     *
     * @param uint32 effIndex : the effect slot (0-MAX_SPELL_EFFECTS-1)
     * @param uint32 aura : the [AuraType] to check for
     * @return bool isAuraType
     */
    int EffectIsAuraType(Eluna* E, ElunaSpellInfo* spellInfo)
    {
        uint32 effIndex = E->CHECKVAL<uint32>(2);
        if (effIndex >= MAX_SPELL_EFFECTS)
            return luaL_argerror(E->L, 2, "effect index out of range");
        AuraType aura = static_cast<AuraType>(E->CHECKVAL<uint32>(3));
        E->Push(spellInfo->GetSpellInfo()->GetEffect(static_cast<SpellEffIndex>(effIndex)).IsAura(aura));
        return 1;
    }

    /**
     * Returns `true` if the given effect slot of the [ElunaSpellInfo] is targeting an area, `false` otherwise.
     *
     * @param uint32 effIndex : the effect slot (0-MAX_SPELL_EFFECTS-1)
     * @return bool isTargetingArea
     */
    int EffectIsTargetingArea(Eluna* E, ElunaSpellInfo* spellInfo)
    {
        uint32 effIndex = E->CHECKVAL<uint32>(2);
        if (effIndex >= MAX_SPELL_EFFECTS)
            return luaL_argerror(E->L, 2, "effect index out of range");
        E->Push(spellInfo->GetSpellInfo()->GetEffect(static_cast<SpellEffIndex>(effIndex)).IsTargetingArea());
        return 1;
    }

    /**
     * Returns `true` if the given effect slot of the [ElunaSpellInfo] is an area aura effect, `false` otherwise.
     *
     * @param uint32 effIndex : the effect slot (0-MAX_SPELL_EFFECTS-1)
     * @return bool isAreaAuraEffect
     */
    int EffectIsAreaAuraEffect(Eluna* E, ElunaSpellInfo* spellInfo)
    {
        uint32 effIndex = E->CHECKVAL<uint32>(2);
        if (effIndex >= MAX_SPELL_EFFECTS)
            return luaL_argerror(E->L, 2, "effect index out of range");
        E->Push(spellInfo->GetSpellInfo()->GetEffect(static_cast<SpellEffIndex>(effIndex)).IsAreaAuraEffect());
        return 1;
    }

    /**
     * Returns `true` if the given effect slot of the [ElunaSpellInfo] is a unit owned aura effect, `false` otherwise.
     *
     * @param uint32 effIndex : the effect slot (0-MAX_SPELL_EFFECTS-1)
     * @return bool isUnitOwnedAuraEffect
     */
    int EffectIsUnitOwnedAuraEffect(Eluna* E, ElunaSpellInfo* spellInfo)
    {
        uint32 effIndex = E->CHECKVAL<uint32>(2);
        if (effIndex >= MAX_SPELL_EFFECTS)
            return luaL_argerror(E->L, 2, "effect index out of range");
        E->Push(spellInfo->GetSpellInfo()->GetEffect(static_cast<SpellEffIndex>(effIndex)).IsUnitOwnedAuraEffect());
        return 1;
    }

    /**
     * Returns the target A type of the given effect slot of the [ElunaSpellInfo].
     *
     * @param uint32 effIndex : the effect slot (0-MAX_SPELL_EFFECTS-1)
     * @return uint32 targetA
     */
    int GetEffectTargetATarget(Eluna* E, ElunaSpellInfo* spellInfo)
    {
        uint32 effIndex = E->CHECKVAL<uint32>(2);
        if (effIndex >= MAX_SPELL_EFFECTS)
            return luaL_argerror(E->L, 2, "effect index out of range");
        E->Push(static_cast<uint32>(spellInfo->GetSpellInfo()->GetEffect(static_cast<SpellEffIndex>(effIndex)).TargetA.GetTarget()));
        return 1;
    }

    /**
     * Returns the target A selection category of the given effect slot of the [ElunaSpellInfo].
     *
     * @param uint32 effIndex : the effect slot (0-MAX_SPELL_EFFECTS-1)
     * @return uint32 selectionCategory
     */
    int GetEffectTargetASelectionCategory(Eluna* E, ElunaSpellInfo* spellInfo)
    {
        uint32 effIndex = E->CHECKVAL<uint32>(2);
        if (effIndex >= MAX_SPELL_EFFECTS)
            return luaL_argerror(E->L, 2, "effect index out of range");
        E->Push(static_cast<uint32>(spellInfo->GetSpellInfo()->GetEffect(static_cast<SpellEffIndex>(effIndex)).TargetA.GetSelectionCategory()));
        return 1;
    }

    /**
     * Returns the target A reference type of the given effect slot of the [ElunaSpellInfo].
     *
     * @param uint32 effIndex : the effect slot (0-MAX_SPELL_EFFECTS-1)
     * @return uint32 referenceType
     */
    int GetEffectTargetAReferenceType(Eluna* E, ElunaSpellInfo* spellInfo)
    {
        uint32 effIndex = E->CHECKVAL<uint32>(2);
        if (effIndex >= MAX_SPELL_EFFECTS)
            return luaL_argerror(E->L, 2, "effect index out of range");
        E->Push(static_cast<uint32>(spellInfo->GetSpellInfo()->GetEffect(static_cast<SpellEffIndex>(effIndex)).TargetA.GetReferenceType()));
        return 1;
    }

    /**
     * Returns the target A object type of the given effect slot of the [ElunaSpellInfo].
     *
     * @param uint32 effIndex : the effect slot (0-MAX_SPELL_EFFECTS-1)
     * @return uint32 objectType
     */
    int GetEffectTargetAObjectType(Eluna* E, ElunaSpellInfo* spellInfo)
    {
        uint32 effIndex = E->CHECKVAL<uint32>(2);
        if (effIndex >= MAX_SPELL_EFFECTS)
            return luaL_argerror(E->L, 2, "effect index out of range");
        E->Push(static_cast<uint32>(spellInfo->GetSpellInfo()->GetEffect(static_cast<SpellEffIndex>(effIndex)).TargetA.GetObjectType()));
        return 1;
    }

    /**
     * Returns the target A check type of the given effect slot of the [ElunaSpellInfo].
     *
     * @param uint32 effIndex : the effect slot (0-MAX_SPELL_EFFECTS-1)
     * @return uint32 checkType
     */
    int GetEffectTargetACheckType(Eluna* E, ElunaSpellInfo* spellInfo)
    {
        uint32 effIndex = E->CHECKVAL<uint32>(2);
        if (effIndex >= MAX_SPELL_EFFECTS)
            return luaL_argerror(E->L, 2, "effect index out of range");
        E->Push(static_cast<uint32>(spellInfo->GetSpellInfo()->GetEffect(static_cast<SpellEffIndex>(effIndex)).TargetA.GetCheckType()));
        return 1;
    }

    /**
     * Returns the target A direction type of the given effect slot of the [ElunaSpellInfo].
     *
     * @param uint32 effIndex : the effect slot (0-MAX_SPELL_EFFECTS-1)
     * @return uint32 directionType
     */
    int GetEffectTargetADirectionType(Eluna* E, ElunaSpellInfo* spellInfo)
    {
        uint32 effIndex = E->CHECKVAL<uint32>(2);
        if (effIndex >= MAX_SPELL_EFFECTS)
            return luaL_argerror(E->L, 2, "effect index out of range");
        E->Push(static_cast<uint32>(spellInfo->GetSpellInfo()->GetEffect(static_cast<SpellEffIndex>(effIndex)).TargetA.GetDirectionType()));
        return 1;
    }

    /**
     * Returns `true` if target A of the given effect slot of the [ElunaSpellInfo] is an area target, `false` otherwise.
     *
     * @param uint32 effIndex : the effect slot (0-MAX_SPELL_EFFECTS-1)
     * @return bool isArea
     */
    int GetEffectTargetAIsArea(Eluna* E, ElunaSpellInfo* spellInfo)
    {
        uint32 effIndex = E->CHECKVAL<uint32>(2);
        if (effIndex >= MAX_SPELL_EFFECTS)
            return luaL_argerror(E->L, 2, "effect index out of range");
        E->Push(spellInfo->GetSpellInfo()->GetEffect(static_cast<SpellEffIndex>(effIndex)).TargetA.IsArea());
        return 1;
    }

    /**
     * Returns the calculated direction angle for target A of the given effect slot of the [ElunaSpellInfo].
     *
     * @param uint32 effIndex : the effect slot (0-MAX_SPELL_EFFECTS-1)
     * @return float directionAngle
     */
    int GetEffectTargetADirectionAngle(Eluna* E, ElunaSpellInfo* spellInfo)
    {
        uint32 effIndex = E->CHECKVAL<uint32>(2);
        if (effIndex >= MAX_SPELL_EFFECTS)
            return luaL_argerror(E->L, 2, "effect index out of range");
        E->Push(spellInfo->GetSpellInfo()->GetEffect(static_cast<SpellEffIndex>(effIndex)).TargetA.CalcDirectionAngle());
        return 1;
    }

    /**
     * Returns the target B type of the given effect slot of the [ElunaSpellInfo].
     *
     * @param uint32 effIndex : the effect slot (0-MAX_SPELL_EFFECTS-1)
     * @return uint32 targetB
     */
    int GetEffectTargetBTarget(Eluna* E, ElunaSpellInfo* spellInfo)
    {
        uint32 effIndex = E->CHECKVAL<uint32>(2);
        if (effIndex >= MAX_SPELL_EFFECTS)
            return luaL_argerror(E->L, 2, "effect index out of range");
        E->Push(static_cast<uint32>(spellInfo->GetSpellInfo()->GetEffect(static_cast<SpellEffIndex>(effIndex)).TargetB.GetTarget()));
        return 1;
    }

    /**
     * Returns the target B selection category of the given effect slot of the [ElunaSpellInfo].
     *
     * @param uint32 effIndex : the effect slot (0-MAX_SPELL_EFFECTS-1)
     * @return uint32 selectionCategory
     */
    int GetEffectTargetBSelectionCategory(Eluna* E, ElunaSpellInfo* spellInfo)
    {
        uint32 effIndex = E->CHECKVAL<uint32>(2);
        if (effIndex >= MAX_SPELL_EFFECTS)
            return luaL_argerror(E->L, 2, "effect index out of range");
        E->Push(static_cast<uint32>(spellInfo->GetSpellInfo()->GetEffect(static_cast<SpellEffIndex>(effIndex)).TargetB.GetSelectionCategory()));
        return 1;
    }

    /**
     * Returns the target B reference type of the given effect slot of the [ElunaSpellInfo].
     *
     * @param uint32 effIndex : the effect slot (0-MAX_SPELL_EFFECTS-1)
     * @return uint32 referenceType
     */
    int GetEffectTargetBReferenceType(Eluna* E, ElunaSpellInfo* spellInfo)
    {
        uint32 effIndex = E->CHECKVAL<uint32>(2);
        if (effIndex >= MAX_SPELL_EFFECTS)
            return luaL_argerror(E->L, 2, "effect index out of range");
        E->Push(static_cast<uint32>(spellInfo->GetSpellInfo()->GetEffect(static_cast<SpellEffIndex>(effIndex)).TargetB.GetReferenceType()));
        return 1;
    }

    /**
     * Returns the target B object type of the given effect slot of the [ElunaSpellInfo].
     *
     * @param uint32 effIndex : the effect slot (0-MAX_SPELL_EFFECTS-1)
     * @return uint32 objectType
     */
    int GetEffectTargetBObjectType(Eluna* E, ElunaSpellInfo* spellInfo)
    {
        uint32 effIndex = E->CHECKVAL<uint32>(2);
        if (effIndex >= MAX_SPELL_EFFECTS)
            return luaL_argerror(E->L, 2, "effect index out of range");
        E->Push(static_cast<uint32>(spellInfo->GetSpellInfo()->GetEffect(static_cast<SpellEffIndex>(effIndex)).TargetB.GetObjectType()));
        return 1;
    }

    /**
     * Returns the target B check type of the given effect slot of the [ElunaSpellInfo].
     *
     * @param uint32 effIndex : the effect slot (0-MAX_SPELL_EFFECTS-1)
     * @return uint32 checkType
     */
    int GetEffectTargetBCheckType(Eluna* E, ElunaSpellInfo* spellInfo)
    {
        uint32 effIndex = E->CHECKVAL<uint32>(2);
        if (effIndex >= MAX_SPELL_EFFECTS)
            return luaL_argerror(E->L, 2, "effect index out of range");
        E->Push(static_cast<uint32>(spellInfo->GetSpellInfo()->GetEffect(static_cast<SpellEffIndex>(effIndex)).TargetB.GetCheckType()));
        return 1;
    }

    /**
     * Returns the target B direction type of the given effect slot of the [ElunaSpellInfo].
     *
     * @param uint32 effIndex : the effect slot (0-MAX_SPELL_EFFECTS-1)
     * @return uint32 directionType
     */
    int GetEffectTargetBDirectionType(Eluna* E, ElunaSpellInfo* spellInfo)
    {
        uint32 effIndex = E->CHECKVAL<uint32>(2);
        if (effIndex >= MAX_SPELL_EFFECTS)
            return luaL_argerror(E->L, 2, "effect index out of range");
        E->Push(static_cast<uint32>(spellInfo->GetSpellInfo()->GetEffect(static_cast<SpellEffIndex>(effIndex)).TargetB.GetDirectionType()));
        return 1;
    }

    /**
     * Returns `true` if target B of the given effect slot of the [ElunaSpellInfo] is an area target, `false` otherwise.
     *
     * @param uint32 effIndex : the effect slot (0-MAX_SPELL_EFFECTS-1)
     * @return bool isArea
     */
    int GetEffectTargetBIsArea(Eluna* E, ElunaSpellInfo* spellInfo)
    {
        uint32 effIndex = E->CHECKVAL<uint32>(2);
        if (effIndex >= MAX_SPELL_EFFECTS)
            return luaL_argerror(E->L, 2, "effect index out of range");
        E->Push(spellInfo->GetSpellInfo()->GetEffect(static_cast<SpellEffIndex>(effIndex)).TargetB.IsArea());
        return 1;
    }

    /**
     * Returns the calculated direction angle for target B of the given effect slot of the [ElunaSpellInfo].
     *
     * @param uint32 effIndex : the effect slot (0-MAX_SPELL_EFFECTS-1)
     * @return float directionAngle
     */
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
