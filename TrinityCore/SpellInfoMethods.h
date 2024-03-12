/*
* Copyright (C) 2010 - 2024 Eluna Lua Engine <https://elunaluaengine.github.io/>
* This program is free software licensed under GPL version 3
* Please see the included DOCS/LICENSE.md for more information
*/

#ifndef SPELLINFOMETHODS_H
#define SPELLINFOMETHODS_H

namespace LuaSpellInfo
{

    /**
     * Returns the name of the [SpellInfo]
     *
     * <pre>
     * enum LocaleConstant
     * {
     *     LOCALE_enUS = 0,
     *     LOCALE_koKR = 1,
     *     LOCALE_frFR = 2,
     *     LOCALE_deDE = 3,
     *     LOCALE_zhCN = 4,
     *     LOCALE_zhTW = 5,
     *     LOCALE_esES = 6,
     *     LOCALE_esMX = 7,
     *     LOCALE_ruRU = 8
     * };
     * </pre>
     *
     * @param [LocaleConstant] locale = DEFAULT_LOCALE : locale to return the [SpellInfo]'s name
     * @return string name
     */
    int GetName(Eluna* E, SpellInfo* spell_info)
    {
        uint8 locale = E->CHECKVAL<uint8>(2, DEFAULT_LOCALE);
        E->Push(spell_info->SpellName[static_cast<LocaleConstant>(locale)]);
        return 1;
    }

    ElunaRegister<SpellInfo> SpellInfoMethods[] =
    {
        // Getters
        { "GetName", &LuaSpellInfo::GetName },
        
        // Setters

        // Boolean

        // Other

        { NULL, NULL, METHOD_REG_NONE }
    };

}
#endif
