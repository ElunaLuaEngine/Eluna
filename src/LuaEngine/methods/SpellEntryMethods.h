/*
* Copyright (C) 2010 - 2016 Eluna Lua Engine <http://emudevs.com/>
* This program is free software licensed under GPL version 3
* Please see the included DOCS/LICENSE.md for more information
*/

#ifndef SPELLENTRYMETHODS_H
#define SPELLENTRYMETHODS_H

namespace LuaSpellEntry
{
    int GetId(lua_State* L, SpellEntry* entry)
    {
        Eluna::Push(L, entry->Id);
        return 1;
    }

    int GetCategory(lua_State* L, SpellEntry* entry)
    {
        Eluna::Push(L, entry->Category);
        return 1;
    }

    int GetDispel(lua_State* L, SpellEntry* entry)
    {
        Eluna::Push(L, entry->Dispel);
        return 1;
    }

    int GetMechanic(lua_State* L, SpellEntry* entry)
    {
        Eluna::Push(L, entry->Mechanic);
        return 1;
    }

    int GetAttributes(lua_State* L, SpellEntry* entry)
    {
        Eluna::Push(L, entry->Attributes);
        return 1;
    }

    int GetAttributesEx(lua_State* L, SpellEntry* entry)
    {
        Eluna::Push(L, entry->AttributesEx);
        return 1;
    }

    int GetAttributesEx2(lua_State* L, SpellEntry* entry)
    {
        Eluna::Push(L, entry->AttributesEx2);
        return 1;
    }

    int GetAttributesEx3(lua_State* L, SpellEntry* entry)
    {
        Eluna::Push(L, entry->AttributesEx3);
        return 1;
    }

    int GetAttributesEx4(lua_State* L, SpellEntry* entry)
    {
        Eluna::Push(L, entry->AttributesEx4);
        return 1;
    }

    int GetAttributesEx5(lua_State* L, SpellEntry* entry)
    {
        Eluna::Push(L, entry->AttributesEx5);
        return 1;
    }

    int GetAttributesEx6(lua_State* L, SpellEntry* entry)
    {
        Eluna::Push(L, entry->AttributesEx6);
        return 1;
    }

    int GetAttributesEx7(lua_State* L, SpellEntry* entry)
    {
        Eluna::Push(L, entry->AttributesEx7);
        return 1;
    }

    int GetStances(lua_State* L, SpellEntry* entry)
    {
        Eluna::Push(L, entry->Stances);
        return 1;
    }

    int GetStancesNot(lua_State* L, SpellEntry* entry)
    {
        Eluna::Push(L, entry->StancesNot);
        return 1;
    }

    int GetTargets(lua_State* L, SpellEntry* entry)
    {
        Eluna::Push(L, entry->Targets);
        return 1;
    }

    int GetTargetCreatureType(lua_State* L, SpellEntry* entry)
    {
        Eluna::Push(L, entry->TargetCreatureType);
        return 1;
    }

    int GetRequiresSpellFocus(lua_State* L, SpellEntry* entry)
    {
        Eluna::Push(L, entry->RequiresSpellFocus);
        return 1;
    }

    int GetFacingCasterFlags(lua_State* L, SpellEntry* entry)
    {
        Eluna::Push(L, entry->FacingCasterFlags);
        return 1;
    }

    int GetCasterAuraState(lua_State* L, SpellEntry* entry)
    {
        Eluna::Push(L, entry->CasterAuraState);
        return 1;
    }

    int GetTargetAuraState(lua_State* L, SpellEntry* entry)
    {
        Eluna::Push(L, entry->TargetAuraState);
        return 1;
    }

    int GetCasterAuraStateNot(lua_State* L, SpellEntry* entry)
    {
        Eluna::Push(L, entry->CasterAuraStateNot);
        return 1;
    }

    int GetTargetAuraStateNot(lua_State* L, SpellEntry* entry)
    {
        Eluna::Push(L, entry->TargetAuraStateNot);
        return 1;
    }

    int GetCasterAuraSpell(lua_State* L, SpellEntry* entry)
    {
        Eluna::Push(L, entry->CasterAuraSpell);
        return 1;
    }

    int GetTargetAuraSpell(lua_State* L, SpellEntry* entry)
    {
        Eluna::Push(L, entry->TargetAuraSpell);
        return 1;
    }

    int GetExcludeCasterAuraSpell(lua_State* L, SpellEntry* entry)
    {
        Eluna::Push(L, entry->ExcludeCasterAuraSpell);
        return 1;
    }

    int GetExcludeTargetAuraSpell(lua_State* L, SpellEntry* entry)
    {
        Eluna::Push(L, entry->ExcludeTargetAuraSpell);
        return 1;
    }

    int GetCastingTimeIndex(lua_State* L, SpellEntry* entry)
    {
        Eluna::Push(L, entry->CastingTimeIndex);
        return 1;
    }

    int GetRecoveryTime(lua_State* L, SpellEntry* entry)
    {
        Eluna::Push(L, entry->RecoveryTime);
        return 1;
    }

    int GetCategoryRecoveryTime(lua_State* L, SpellEntry* entry)
    {
        Eluna::Push(L, entry->CategoryRecoveryTime);
        return 1;
    }

    int GetInterruptFlags(lua_State* L, SpellEntry* entry)
    {
        Eluna::Push(L, entry->InterruptFlags);
        return 1;
    }

    int GetAuraInterruptFlags(lua_State* L, SpellEntry* entry)
    {
        Eluna::Push(L, entry->AuraInterruptFlags);
        return 1;
    }

    int GetChannelInterruptFlags(lua_State* L, SpellEntry* entry)
    {
        Eluna::Push(L, entry->ChannelInterruptFlags);
        return 1;
    }

    int GetProcFlags(lua_State* L, SpellEntry* entry)
    {
        Eluna::Push(L, entry->ProcFlags);
        return 1;
    }

    int GetProcChance(lua_State* L, SpellEntry* entry)
    {
        Eluna::Push(L, entry->ProcChance);
        return 1;
    }

    int GetProcCharges(lua_State* L, SpellEntry* entry)
    {
        Eluna::Push(L, entry->ProcCharges);
        return 1;
    }

    int GetMaxLevel(lua_State* L, SpellEntry* entry)
    {
        Eluna::Push(L, entry->MaxLevel);
        return 1;
    }

    int GetBaseLevel(lua_State* L, SpellEntry* entry)
    {
        Eluna::Push(L, entry->BaseLevel);
        return 1;
    }

    int GetSpellLevel(lua_State* L, SpellEntry* entry)
    {
        Eluna::Push(L, entry->SpellLevel);
        return 1;
    }

    int GetDurationIndex(lua_State* L, SpellEntry* entry)
    {
        Eluna::Push(L, entry->DurationIndex);
        return 1;
    }

    int GetPowerType(lua_State* L, SpellEntry* entry)
    {
        Eluna::Push(L, entry->PowerType);
        return 1;
    }

    int GetManaCost(lua_State* L, SpellEntry* entry)
    {
        Eluna::Push(L, entry->ManaCost);
        return 1;
    }

    int GetManaCostPerlevel(lua_State* L, SpellEntry* entry)
    {
        Eluna::Push(L, entry->ManaCostPerlevel);
        return 1;
    }

    int GetManaPerSecond(lua_State* L, SpellEntry* entry)
    {
        Eluna::Push(L, entry->ManaPerSecond);
        return 1;
    }

    int GetManaPerSecondPerLevel(lua_State* L, SpellEntry* entry)
    {
        Eluna::Push(L, entry->ManaPerSecondPerLevel);
        return 1;
    }

    int GetRangeIndex(lua_State* L, SpellEntry* entry)
    {
        Eluna::Push(L, entry->RangeIndex);
        return 1;
    }

    int GetSpeed(lua_State* L, SpellEntry* entry)
    {
        Eluna::Push(L, entry->Speed);
        return 1;
    }

    int GetStackAmount(lua_State* L, SpellEntry* entry)
    {
        Eluna::Push(L, entry->StackAmount);
        return 1;
    }

    int GetTotem(lua_State* L, SpellEntry* entry)
    {
        lua_newtable(L);
        int tbl = lua_gettop(L);
        uint32 i = 0;

        for (size_t index = 0; index < entry->Totem.size(); ++index)
        {
            Eluna::Push(L, entry->Totem[index]);
            lua_rawseti(L, tbl, ++i);
        }
        
        lua_settop(L, tbl); // push table to top of stack
        return 1;
    }

    int GetReagent(lua_State* L, SpellEntry* entry)
    {
        lua_newtable(L);
        int tbl = lua_gettop(L);
        uint32 i = 0;

        for (size_t index = 0; index < entry->Reagent.size(); ++index)
        {
            Eluna::Push(L, entry->Reagent[index]);
            lua_rawseti(L, tbl, ++i);
        }
        
        lua_settop(L, tbl); // push table to top of stack
        return 1;
    }

    int GetReagentCount(lua_State* L, SpellEntry* entry)
    {
        lua_newtable(L);
        int tbl = lua_gettop(L);
        uint32 i = 0;

        for (size_t index = 0; index < entry->ReagentCount.size(); ++index)
        {
            Eluna::Push(L, entry->ReagentCount[index]);
            lua_rawseti(L, tbl, ++i);
        }
        
        lua_settop(L, tbl); // push table to top of stack
        return 1;
    }

    int GetEquippedItemClass(lua_State* L, SpellEntry* entry)
    {
        Eluna::Push(L, entry->EquippedItemClass);
        return 1;
    }

    int GetEquippedItemSubClassMask(lua_State* L, SpellEntry* entry)
    {
        Eluna::Push(L, entry->EquippedItemSubClassMask);
        return 1;
    }

    int GetEquippedItemInventoryTypeMask(lua_State* L, SpellEntry* entry)
    {
        Eluna::Push(L, entry->EquippedItemInventoryTypeMask);
        return 1;
    }

    int GetEffect(lua_State* L, SpellEntry* entry)
    {
        lua_newtable(L);
        int tbl = lua_gettop(L);
        uint32 i = 0;

        for (size_t index = 0; index < entry->Effect.size(); ++index)
        {
            Eluna::Push(L, entry->Effect[index]);
            lua_rawseti(L, tbl, ++i);
        }
        
        lua_settop(L, tbl); // push table to top of stack
        return 1;
    }

    int GetEffectDieSides(lua_State* L, SpellEntry* entry)
    {
        lua_newtable(L);
        int tbl = lua_gettop(L);
        uint32 i = 0;

        for (size_t index = 0; index < entry->EffectDieSides.size(); ++index)
        {
            Eluna::Push(L, entry->EffectDieSides[index]);
            lua_rawseti(L, tbl, ++i);
        }
        
        lua_settop(L, tbl); // push table to top of stack
        return 1;
    }

    int GetEffectRealPointsPerLevel(lua_State* L, SpellEntry* entry)
    {
        lua_newtable(L);
        int tbl = lua_gettop(L);
        uint32 i = 0;

        for (size_t index = 0; index < entry->EffectRealPointsPerLevel.size(); ++index)
        {
            Eluna::Push(L, entry->EffectRealPointsPerLevel[index]);
            lua_rawseti(L, tbl, ++i);
        }
        
        lua_settop(L, tbl); // push table to top of stack
        return 1;
    }

    int GetEffectBasePoints(lua_State* L, SpellEntry* entry)
    {
        lua_newtable(L);
        int tbl = lua_gettop(L);
        uint32 i = 0;

        for (size_t index = 0; index < entry->EffectBasePoints.size(); ++index)
        {
            Eluna::Push(L, entry->EffectBasePoints[index]);
            lua_rawseti(L, tbl, ++i);
        }
        
        lua_settop(L, tbl); // push table to top of stack
        return 1;
    }

    int GetEffectMechanic(lua_State* L, SpellEntry* entry)
    {
        lua_newtable(L);
        int tbl = lua_gettop(L);
        uint32 i = 0;

        for (size_t index = 0; index < entry->EffectMechanic.size(); ++index)
        {
            Eluna::Push(L, entry->EffectMechanic[index]);
            lua_rawseti(L, tbl, ++i);
        }
        
        lua_settop(L, tbl); // push table to top of stack
        return 1;
    }

    int GetEffectImplicitTargetA(lua_State* L, SpellEntry* entry)
    {
        lua_newtable(L);
        int tbl = lua_gettop(L);
        uint32 i = 0;

        for (size_t index = 0; index < entry->EffectImplicitTargetA.size(); ++index)
        {
            Eluna::Push(L, entry->EffectImplicitTargetA[index]);
            lua_rawseti(L, tbl, ++i);
        }
        
        lua_settop(L, tbl); // push table to top of stack
        return 1;
    }

    int GetEffectImplicitTargetB(lua_State* L, SpellEntry* entry)
    {
        lua_newtable(L);
        int tbl = lua_gettop(L);
        uint32 i = 0;

        for (size_t index = 0; index < entry->EffectImplicitTargetB.size(); ++index)
        {
            Eluna::Push(L, entry->EffectImplicitTargetB[index]);
            lua_rawseti(L, tbl, ++i);
        }
        
        lua_settop(L, tbl); // push table to top of stack
        return 1;
    }

    int GetEffectRadiusIndex(lua_State* L, SpellEntry* entry)
    {
        lua_newtable(L);
        int tbl = lua_gettop(L);
        uint32 i = 0;

        for (size_t index = 0; index < entry->EffectRadiusIndex.size(); ++index)
        {
            Eluna::Push(L, entry->EffectRadiusIndex[index]);
            lua_rawseti(L, tbl, ++i);
        }
        
        lua_settop(L, tbl); // push table to top of stack
        return 1;
    }

    int GetEffectApplyAuraName(lua_State* L, SpellEntry* entry)
    {
        lua_newtable(L);
        int tbl = lua_gettop(L);
        uint32 i = 0;

        for (size_t index = 0; index < entry->EffectApplyAuraName.size(); ++index)
        {
            Eluna::Push(L, entry->EffectApplyAuraName[index]);
            lua_rawseti(L, tbl, ++i);
        }
        
        lua_settop(L, tbl); // push table to top of stack
        return 1;
    }

    int GetEffectAmplitude(lua_State* L, SpellEntry* entry)
    {
        lua_newtable(L);
        int tbl = lua_gettop(L);
        uint32 i = 0;

        for (size_t index = 0; index < entry->EffectAmplitude.size(); ++index)
        {
            Eluna::Push(L, entry->EffectAmplitude[index]);
            lua_rawseti(L, tbl, ++i);
        }
        
        lua_settop(L, tbl); // push table to top of stack
        return 1;
    }

    int GetEffectValueMultiplier(lua_State* L, SpellEntry* entry)
    {
        lua_newtable(L);
        int tbl = lua_gettop(L);
        uint32 i = 0;

        for (size_t index = 0; index < entry->EffectValueMultiplier.size(); ++index)
        {
            Eluna::Push(L, entry->EffectValueMultiplier[index]);
            lua_rawseti(L, tbl, ++i);
        }
        
        lua_settop(L, tbl); // push table to top of stack
        return 1;
    }

    int GetEffectChainTarget(lua_State* L, SpellEntry* entry)
    {
        lua_newtable(L);
        int tbl = lua_gettop(L);
        uint32 i = 0;

        for (size_t index = 0; index < entry->EffectChainTarget.size(); ++index)
        {
            Eluna::Push(L, entry->EffectChainTarget[index]);
            lua_rawseti(L, tbl, ++i);
        }
        
        lua_settop(L, tbl); // push table to top of stack
        return 1;
    }

    int GetEffectItemType(lua_State* L, SpellEntry* entry)
    {
        lua_newtable(L);
        int tbl = lua_gettop(L);
        uint32 i = 0;

        for (size_t index = 0; index < entry->EffectItemType.size(); ++index)
        {
            Eluna::Push(L, entry->EffectItemType[index]);
            lua_rawseti(L, tbl, ++i);
        }
        
        lua_settop(L, tbl); // push table to top of stack
        return 1;
    }

    int GetEffectMiscValue(lua_State* L, SpellEntry* entry)
    {
        lua_newtable(L);
        int tbl = lua_gettop(L);
        uint32 i = 0;

        for (size_t index = 0; index < entry->EffectMiscValue.size(); ++index)
        {
            Eluna::Push(L, entry->EffectMiscValue[index]);
            lua_rawseti(L, tbl, ++i);
        }
        
        lua_settop(L, tbl); // push table to top of stack
        return 1;
    }

    int GetEffectMiscValueB(lua_State* L, SpellEntry* entry)
    {
        lua_newtable(L);
        int tbl = lua_gettop(L);
        uint32 i = 0;

        for (size_t index = 0; index < entry->EffectMiscValueB.size(); ++index)
        {
            Eluna::Push(L, entry->EffectMiscValueB[index]);
            lua_rawseti(L, tbl, ++i);
        }
        
        lua_settop(L, tbl); // push table to top of stack
        return 1;
    }

    int GetEffectTriggerSpell(lua_State* L, SpellEntry* entry)
    {
        lua_newtable(L);
        int tbl = lua_gettop(L);
        uint32 i = 0;

        for (size_t index = 0; index < entry->EffectTriggerSpell.size(); ++index)
        {
            Eluna::Push(L, entry->EffectTriggerSpell[index]);
            lua_rawseti(L, tbl, ++i);
        }
        
        lua_settop(L, tbl); // push table to top of stack
        return 1;
    }

    int GetEffectPointsPerComboPoint(lua_State* L, SpellEntry* entry)
    {
        lua_newtable(L);
        int tbl = lua_gettop(L);
        uint32 i = 0;

        for (size_t index = 0; index < entry->EffectPointsPerComboPoint.size(); ++index)
        {
            Eluna::Push(L, entry->EffectPointsPerComboPoint[index]);
            lua_rawseti(L, tbl, ++i);
        }
        
        lua_settop(L, tbl); // push table to top of stack
        return 1;
    }

    int GetEffectSpellClassMask(lua_State* L, SpellEntry* entry)
    {
        lua_newtable(L);
        int tbl = lua_gettop(L);
        uint32 i = 0;

        for (size_t index = 0; index < entry->EffectSpellClassMask.size(); ++index)
        {
            Eluna::Push(L, entry->EffectSpellClassMask[index]);
            lua_rawseti(L, tbl, ++i);
        }
        
        lua_settop(L, tbl); // push table to top of stack
        return 1;
    }

    int GetSpellVisual(lua_State* L, SpellEntry* entry)
    {
        lua_newtable(L);
        int tbl = lua_gettop(L);
        uint32 i = 0;

        for (size_t index = 0; index < entry->SpellVisual.size(); ++index)
        {
            Eluna::Push(L, entry->SpellVisual[index]);
            lua_rawseti(L, tbl, ++i);
        }
        
        lua_settop(L, tbl); // push table to top of stack
        return 1;
    }

    int GetSpellIconID(lua_State* L, SpellEntry* entry)
    {
        Eluna::Push(L, entry->SpellIconID);
        return 1;
    }

    int GetActiveIconID(lua_State* L, SpellEntry* entry)
    {
        Eluna::Push(L, entry->ActiveIconID);
        return 1;
    }

    int GetSpellPriority(lua_State* L, SpellEntry* entry)
    {
        Eluna::Push(L, entry->SpellPriority);
        return 1;
    }

    int GetSpellName(lua_State* L, SpellEntry* entry)
    {
        lua_newtable(L);
        int tbl = lua_gettop(L);
        uint32 i = 0;

        for (size_t index = 0; index < entry->SpellName.size(); ++index)
        {
            Eluna::Push(L, entry->SpellName[index]);
            lua_rawseti(L, tbl, ++i);
        }
        
        lua_settop(L, tbl); // push table to top of stack
        return 1;
    }

    int GetRank(lua_State* L, SpellEntry* entry)
    {
        lua_newtable(L);
        int tbl = lua_gettop(L);
        uint32 i = 0;

        for (size_t index = 0; index < entry->Rank.size(); ++index)
        {
            Eluna::Push(L, entry->Rank[index]);
            lua_rawseti(L, tbl, ++i);
        }
        
        lua_settop(L, tbl); // push table to top of stack
        return 1;
    }

    int GetManaCostPercentage(lua_State* L, SpellEntry* entry)
    {
        Eluna::Push(L, entry->ManaCostPercentage);
        return 1;
    }

    int GetStartRecoveryCategory(lua_State* L, SpellEntry* entry)
    {
        Eluna::Push(L, entry->StartRecoveryCategory);
        return 1;
    }

    int GetStartRecoveryTime(lua_State* L, SpellEntry* entry)
    {
        Eluna::Push(L, entry->StartRecoveryTime);
        return 1;
    }

    int GetMaxTargetLevel(lua_State* L, SpellEntry* entry)
    {
        Eluna::Push(L, entry->MaxTargetLevel);
        return 1;
    }

    int GetSpellFamilyName(lua_State* L, SpellEntry* entry)
    {
        Eluna::Push(L, entry->SpellFamilyName);
        return 1;
    }

    int GetSpellFamilyFlags(lua_State* L, SpellEntry* entry)
    {
        Eluna::Push(L, entry->SpellFamilyFlags);
        return 1;
    }

    int GetMaxAffectedTargets(lua_State* L, SpellEntry* entry)
    {
        Eluna::Push(L, entry->MaxAffectedTargets);
        return 1;
    }

    int GetDmgClass(lua_State* L, SpellEntry* entry)
    {
        Eluna::Push(L, entry->DmgClass);
        return 1;
    }

    int GetPreventionType(lua_State* L, SpellEntry* entry)
    {
        Eluna::Push(L, entry->PreventionType);
        return 1;
    }

    int GetEffectDamageMultiplier(lua_State* L, SpellEntry* entry)
    {
        lua_newtable(L);
        int tbl = lua_gettop(L);
        uint32 i = 0;

        for (size_t index = 0; index < entry->EffectDamageMultiplier.size(); ++index)
        {
            Eluna::Push(L, entry->EffectDamageMultiplier[index]);
            lua_rawseti(L, tbl, ++i);
        }
        
        lua_settop(L, tbl); // push table to top of stack
        return 1;
    }

    int GetTotemCategory(lua_State* L, SpellEntry* entry)
    {
        lua_newtable(L);
        int tbl = lua_gettop(L);
        uint32 i = 0;

        for (size_t index = 0; index < entry->TotemCategory.size(); ++index)
        {
            Eluna::Push(L, entry->TotemCategory[index]);
            lua_rawseti(L, tbl, ++i);
        }
        
        lua_settop(L, tbl); // push table to top of stack
        return 1;
    }

    int GetAreaGroupId(lua_State* L, SpellEntry* entry)
    {
        Eluna::Push(L, entry->AreaGroupId);
        return 1;
    }

    int GetSchoolMask(lua_State* L, SpellEntry* entry)
    {
        Eluna::Push(L, entry->SchoolMask);
        return 1;
    }

    int GetRuneCostID(lua_State* L, SpellEntry* entry)
    {
        Eluna::Push(L, entry->RuneCostID);
        return 1;
    }

    int GetEffectBonusMultiplier(lua_State* L, SpellEntry* entry)
    {
        lua_newtable(L);
        int tbl = lua_gettop(L);
        uint32 i = 0;

        for (size_t index = 0; index < entry->EffectBonusMultiplier.size(); ++index)
        {
            Eluna::Push(L, entry->EffectBonusMultiplier[index]);
            lua_rawseti(L, tbl, ++i);
        }
        
        lua_settop(L, tbl); // push table to top of stack
        return 1;
    }
}

#endif

