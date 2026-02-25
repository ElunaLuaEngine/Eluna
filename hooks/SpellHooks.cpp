/*
 * Copyright (C) 2010 - 2024 Eluna Lua Engine <https://elunaluaengine.github.io/>
 * This program is free software licensed under GPL version 3
 * Please see the included DOCS/LICENSE.md for more information
 */

#include "Hooks.h"
#include "HookHelpers.h"
#include "LuaEngine.h"
#include "BindingMap.h"
#include "ElunaIncludes.h"
#include "ElunaTemplate.h"

using namespace Hooks;

#define START_HOOK(EVENT, SPELL) \
    auto binding = GetBinding<EntryKey<SpellEvents>>(REGTYPE_SPELL);\
    auto key = EntryKey<SpellEvents>(EVENT, SPELL->GetSpellInfo()->Id);\
    if (!binding->HasBindingsFor(key))\
        return;

#define START_HOOK_WITH_RETVAL(EVENT, SPELL, RETVAL) \
    auto binding = GetBinding<EntryKey<SpellEvents>>(REGTYPE_SPELL);\
    auto key = EntryKey<SpellEvents>(EVENT, SPELL->GetSpellInfo()->Id);\
    if (!binding->HasBindingsFor(key))\
        return RETVAL;

void Eluna::OnSpellCast(Spell* pSpell, bool skipCheck)
{
    START_HOOK(SPELL_EVENT_ON_CAST, pSpell);
    HookPush(pSpell);
    HookPush(skipCheck);
    CallAllFunctions(binding, key);
}

bool Eluna::OnAuraApplication(Aura* aura, AuraEffect const* auraEff, Unit* target, uint8 mode, bool apply)
{
    START_HOOK_WITH_RETVAL(SPELL_EVENT_ON_AURA_APPLICATION, aura, false);
    HookPush(aura);
    HookPush(auraEff);
    HookPush(target);
    HookPush(mode);
    HookPush(apply);
    return CallAllFunctionsBool(binding, key, false);
}

void Eluna::OnAuraDispel(Aura* aura, DispelInfo* dispelInfo)
{
    START_HOOK(SPELL_EVENT_ON_DISPEL, aura);
    HookPush(aura);
    HookPush(dispelInfo->GetDispeller());
    HookPush(dispelInfo->GetDispellerSpellId());
    HookPush(dispelInfo->GetRemovedCharges());
    CallAllFunctions(binding, key);
}

bool Eluna::OnPeriodicTick(Aura* aura, AuraEffect const* auraEff, Unit* target)
{
    START_HOOK_WITH_RETVAL(SPELL_EVENT_ON_PERIODIC_TICK, aura, false);
    HookPush(aura);
    HookPush(auraEff);
    HookPush(target);
    return CallAllFunctionsBool(binding, key, false);
}

void Eluna::OnPeriodicUpdate(Aura* aura, AuraEffect const* auraEff)
{
    START_HOOK(SPELL_EVENT_ON_PERIODIC_UPDATE, aura);
    HookPush(aura);
    HookPush(auraEff);
    CallAllFunctions(binding, key);
}

void Eluna::OnAuraCalcAmount(Aura* aura, AuraEffect const* auraEff, int32& amount, bool& canBeRecalculated)
{
    START_HOOK(SPELL_EVENT_ON_AURA_CALC_AMOUNT, aura);

    HookPush(aura);
    HookPush(auraEff);

    HookPush(amount);
    int amountIndex = lua_gettop(L);

    HookPush(canBeRecalculated);
    int canBeRecalculatedIndex = lua_gettop(L);

    CallAllFunctionsMultiReturn(
        binding,
        key,
        std::tie(amount, canBeRecalculated),
        std::array<int, 2>{ amountIndex, canBeRecalculatedIndex }
    );
}

void Eluna::OnCalcPeriodic(Aura* aura, AuraEffect const* auraEff, bool& isPeriodic, int32& amplitude)
{
    START_HOOK(SPELL_EVENT_ON_AURA_CALC_AMOUNT, aura);

    HookPush(aura);
    HookPush(auraEff);

    HookPush(isPeriodic);
    int isPeriodicIndex = lua_gettop(L);

    HookPush(amplitude);
    int amplitudeIndex = lua_gettop(L);

    CallAllFunctionsMultiReturn(
        binding,
        key,
        std::tie(isPeriodic, amplitude),
        std::array<int, 2>{ isPeriodicIndex, amplitudeIndex }
    );
}

bool Eluna::OnAuraCanProc(Aura* aura, ProcEventInfo& procInfo)
{
    START_HOOK_WITH_RETVAL(SPELL_EVENT_ON_CHECK_PROC, aura, true);
    ElunaProcInfo luaProcInfo(procInfo, aura->GetCaster()->GetMap());
    HookPush(aura);
    HookPush(&luaProcInfo);
    bool retVal = CallAllFunctionsBool(binding, key, true);
    luaProcInfo.ApplyToProcEventInfo(procInfo);
    return retVal;
}

bool Eluna::OnAuraProc(Aura* aura, ProcEventInfo& procInfo)
{
    START_HOOK_WITH_RETVAL(SPELL_EVENT_ON_CHECK_PROC, aura, false);
    ElunaProcInfo luaProcInfo(procInfo, aura->GetCaster()->GetMap());
    HookPush(aura);
    HookPush(&luaProcInfo);
    bool defaultPrevented = CallAllFunctionsBool(binding, key, false);
    luaProcInfo.ApplyToProcEventInfo(procInfo);
    return defaultPrevented;
}

uint32 Eluna::OnCheckCast(Spell* pSpell)
{
    START_HOOK_WITH_RETVAL(SPELL_EVENT_ON_CHECK_CAST, pSpell, SPELL_FAILED_SUCCESS);
    HookPush(pSpell);
    return static_cast<uint32>(CallAllFunctionsInt(binding, key, int32(SPELL_FAILED_SUCCESS)));
}

void Eluna::OnBeforeCast(Spell* pSpell)
{
    START_HOOK(SPELL_EVENT_ON_BEFORE_CAST, pSpell);
    HookPush(pSpell);
    CallAllFunctions(binding, key);
}

void Eluna::OnAfterCast(Spell* pSpell)
{
    START_HOOK(SPELL_EVENT_ON_AFTER_CAST, pSpell);
    HookPush(pSpell);
    CallAllFunctions(binding, key);
}

void Eluna::OnObjectAreaTargetSelect(Spell* pSpell, uint8 effIndex, std::list<WorldObject*>& targets)
{
    START_HOOK(SPELL_EVENT_ON_OBJECT_AREA_TARGET, pSpell);
    HookPush(pSpell);
    HookPush(effIndex);
    CallAllFunctionsTable(binding, key, targets);
}

void Eluna::OnObjectTargetSelect(Spell* pSpell, uint8 effIndex, WorldObject*& target)
{
    START_HOOK(SPELL_EVENT_ON_OBJECT_TARGET, pSpell);
    HookPush(pSpell);
    HookPush(effIndex);
    HookPush(target);
    CallAllFunctions(binding, key);
}

void Eluna::OnDestinationTargetSelect(Spell* pSpell, uint8 effIndex, SpellDestination& target)
{
    START_HOOK(SPELL_EVENT_ON_DEST_TARGET, pSpell);
    HookPush(pSpell);
    HookPush(effIndex);
    HookPush(target._position.m_mapId);
    int mapIdIndex = lua_gettop(L);
    HookPush(target._position.m_positionX);
    int posXIndex = lua_gettop(L);
    HookPush(target._position.m_positionY);
    int posYIndex = lua_gettop(L);
    HookPush(target._position.m_positionZ);
    int posZIndex = lua_gettop(L);
    HookPush(target._position.GetOrientation());
    int orientationIndex = lua_gettop(L);

    uint32 mapId = target._position.m_mapId;
    float posX = target._position.m_positionX;
    float posY = target._position.m_positionY;
    float posZ = target._position.m_positionZ;
    float orientation = target._position.GetOrientation();

    CallAllFunctionsMultiReturn(
        binding,
        key,
        std::tie(mapId, posX, posY, posZ, orientation),
        std::array<int, 5>{ mapIdIndex, posXIndex, posYIndex, posZIndex, orientationIndex }
    );

    target._position.m_mapId = mapId;
    target._position.m_positionX = posX;
    target._position.m_positionY = posY;
    target._position.m_positionZ = posZ;
    target._position.SetOrientation(orientation);
}

bool Eluna::OnEffectLaunch(Spell* pSpell, uint8 effIndex, uint8 mode, bool preventDefault)
{
    START_HOOK_WITH_RETVAL(SPELL_EVENT_ON_EFFECT_LAUNCH, pSpell, preventDefault);
    HookPush(pSpell);
    HookPush(effIndex);
    HookPush(mode);
    return CallAllFunctionsBool(binding, key, preventDefault);
}

bool Eluna::OnEffectLaunchTarget(Spell* pSpell, uint8 effIndex, uint8 mode, bool preventDefault)
{
    START_HOOK_WITH_RETVAL(SPELL_EVENT_ON_EFFECT_LAUNCH_TARGET, pSpell, preventDefault);
    HookPush(pSpell);
    HookPush(effIndex);
    HookPush(mode);
    preventDefault = CallAllFunctionsBool(binding, key, preventDefault);
    return preventDefault;
}

bool Eluna::OnEffectHit(Spell* pSpell, uint8 effIndex, uint8 mode, bool preventDefault)
{
    START_HOOK_WITH_RETVAL(SPELL_EVENT_ON_EFFECT_HIT, pSpell, preventDefault);
    HookPush(pSpell);
    HookPush(effIndex);
    HookPush(mode);
    preventDefault = CallAllFunctionsBool(binding, key, preventDefault);
    return preventDefault;
}

bool Eluna::OnEffectHitTarget(Spell* pSpell, uint8 effIndex, uint8 mode, bool preventDefault)
{
    START_HOOK_WITH_RETVAL(SPELL_EVENT_ON_EFFECT_HIT_TARGET, pSpell, preventDefault);
    HookPush(pSpell);
    HookPush(effIndex);
    HookPush(mode);
    preventDefault = CallAllFunctionsBool(binding, key, preventDefault);
    return preventDefault;
}

void Eluna::OnBeforeSpellHit(Spell* pSpell, uint8 missInfo)
{
    START_HOOK(SPELL_EVENT_ON_BEFORE_HIT, pSpell);
    HookPush(pSpell);
    HookPush(missInfo);
    CallAllFunctions(binding, key);
}

void Eluna::OnSpellHit(Spell* pSpell)
{
    START_HOOK(SPELL_EVENT_ON_HIT, pSpell);
    HookPush(pSpell);
    CallAllFunctions(binding, key);
}

void Eluna::OnAfterSpellHit(Spell* pSpell)
{
    START_HOOK(SPELL_EVENT_ON_AFTER_HIT, pSpell);
    HookPush(pSpell);
    CallAllFunctions(binding, key);
}

void Eluna::OnEffectCalcAbsorb(Spell* pSpell, DamageInfo const& damageInfo, uint32& resistAmount, int32& absorbAmount)
{
    START_HOOK(SPELL_EVENT_ON_EFFECT_CALC_ABSORB, pSpell);
    HookPush(pSpell);
    HookPush(damageInfo.GetAttacker());
    HookPush(damageInfo.GetVictim());
    HookPush(damageInfo.GetDamage());
    HookPush(damageInfo.GetAbsorb());
    HookPush(damageInfo.GetResist());
    HookPush(damageInfo.GetBlock());
    HookPush(static_cast<uint32>(damageInfo.GetSchoolMask()));
    HookPush(static_cast<uint32>(damageInfo.GetDamageType()));
    HookPush(static_cast<uint32>(damageInfo.GetAttackType()));
    HookPush(damageInfo.GetHitMask());
    HookPush(resistAmount);
    int resistIndex = lua_gettop(L);
    HookPush(absorbAmount);
    int absorbIndex = lua_gettop(L);
    CallAllFunctionsMultiReturn(
        binding,
        key,
        std::tie(resistAmount, absorbAmount),
        std::array<int, 2>{ resistIndex, absorbIndex }
    );
}
