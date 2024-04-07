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
    auto key = EntryKey<SpellEvents>(EVENT, SPELL->m_spellInfo->Id);\
    if (!SpellEventBindings->HasBindingsFor(key))\
        return;

#define START_HOOK_WITH_RETVAL(EVENT, SPELL, RETVAL) \
    auto key = EntryKey<SpellEvents>(EVENT, SPELL->m_spellInfo->Id);\
    if (!SpellEventBindings->HasBindingsFor(key))\
        return RETVAL;

void Eluna::OnSpellCast(Spell* pSpell, bool skipCheck)
{
    START_HOOK(SPELL_EVENT_ON_CAST, pSpell);
    HookPush(pSpell);
    HookPush(skipCheck);
    CallAllFunctions(SpellEventBindings, key);
}
