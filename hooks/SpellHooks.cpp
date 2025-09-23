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

bool Eluna::OnPerodicTick(Aura* aura, AuraEffect const* auraEff)
{
    START_HOOK_WITH_RETVAL(SPELL_EVENT_ON_PERODIC_TICK, aura, false);
    HookPush(aura);
    HookPush(auraEff);
    return CallAllFunctionsBool(binding, key, false);
}

void Eluna::OnPerodicUpdate(Aura* aura, AuraEffect const* auraEff)
{
    START_HOOK(SPELL_EVENT_ON_PERODIC_UPDATE, aura);
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
    int n = SetupStack(binding, key, 4);

    while (n > 0)
    {
        int r = CallOneFunction(n--, 4, 2);

        if (lua_isnumber(L, r + 0))
        {
            amount = CHECKVAL<uint32>(r + 0);
            // Update the stack for subsequent calls.
            ReplaceArgument(amount, amountIndex);
        }


        if (lua_isboolean(L, r + 1))
        {
            canBeRecalculated = lua_toboolean(L, r + 1);
            // Update the stack for subsequent calls.
            ReplaceArgument(amount, canBeRecalculatedIndex);
        }

        lua_pop(L, 2);
    }

    CleanUpStack(2);
}

void Eluna::OnCalcPerodic(Aura* aura, AuraEffect const* auraEff, bool& isPeriodic, int32& amplitude)
{
    START_HOOK(SPELL_EVENT_ON_AURA_CALC_AMOUNT, aura);
    HookPush(aura);
    HookPush(auraEff);
    HookPush(isPeriodic);
    int isPeriodicIndex = lua_gettop(L);
    HookPush(amplitude);
    int amplitudeIndex = lua_gettop(L);
    int n = SetupStack(binding, key, 4);

    while (n > 0)
    {
        int r = CallOneFunction(n--, 4, 2);

        if (lua_isboolean(L, r + 0))
        {
            isPeriodic = lua_toboolean(L, r + 0);
            // Update the stack for subsequent calls.
            ReplaceArgument(isPeriodic, isPeriodicIndex);
        }

        if (lua_isnumber(L, r + 1))
        {
            amplitude = CHECKVAL<int32>(r + 1);
            // Update the stack for subsequent calls.
            ReplaceArgument(amplitude, amplitudeIndex);
        }

        lua_pop(L, 2);
    }

    CleanUpStack(2);
}
