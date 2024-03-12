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
    
    /**
     * Checks if the [SpellInfo] has a specific attribute.
     *
     * Attributes are characteristics or properties that spells can possess.
     * Attributes are divided into different categories (from 0 to 8 in this context).
     *
     * Here is how each attribute is inspected:
     * 
     * <pre>
     * 0 : SpellAttr0
     * 1 : SpellAttr1
     * 2 : SpellAttr2
     * 3 : SpellAttr3
     * 4 : SpellAttr4
     * 5 : SpellAttr5
     * 6 : SpellAttr6
     * 7 : SpellAttr7
     * 8 : SpellCustomAttributes
     * </pre>
     *
     * @param attributeType : the type of the attribute.
     * @param attribute : the specific attribute to check.
     * @return boolean : returns true if [SpellInfo] has the attribute, else false
     */
    int HasAttribute(Eluna* E, SpellInfo* spell_info)
    {
        uint8 attributeType = E->CHECKVAL<uint8>(2);
        uint32 attribute    = E->CHECKVAL<uint32>(3);

        bool hasAttribute = false;
        switch(attributeType)
        {
            case 0:
                hasAttribute = spell_info->HasAttribute(static_cast<SpellAttr0>(attribute));
                break;
            case 1:
                hasAttribute = spell_info->HasAttribute(static_cast<SpellAttr1>(attribute));
                break;
            case 2:
                hasAttribute = spell_info->HasAttribute(static_cast<SpellAttr2>(attribute));
                break;
            case 3:
                hasAttribute = spell_info->HasAttribute(static_cast<SpellAttr3>(attribute));
                break;
            case 4:
                hasAttribute = spell_info->HasAttribute(static_cast<SpellAttr4>(attribute));
                break;
            case 5:
                hasAttribute = spell_info->HasAttribute(static_cast<SpellAttr5>(attribute));
                break;
            case 6:
                hasAttribute = spell_info->HasAttribute(static_cast<SpellAttr6>(attribute));
                break;
            case 7:
                hasAttribute = spell_info->HasAttribute(static_cast<SpellAttr7>(attribute));
                break;
            case 8:
                hasAttribute = spell_info->HasAttribute(static_cast<SpellCustomAttributes>(attribute));
                break;
        }

        E->Push(hasAttribute);
        return 1;
    }
    
    /**
     * Retrieves the attributes of the [SpellInfo] based on the attribute type.
     *
     * Attributes are properties or traits of a spell. There are different categories (0 to 8 in this case) of attributes.
     *
     * How each type of attribute is extracted:
     *
     * <pre>
     * 0 : Attributes
     * 1 : AttributesEx
     * 2 : AttributesEx2
     * 3 : AttributesEx3
     * 4 : AttributesEx4
     * 5 : AttributesEx5
     * 6 : AttributesEx6
     * 7 : AttributesEx7
     * 8 : AttributesCu
     * </pre>
     *
     * @param attributeType : The type of the attribute.
     * @return uint32 attributes : Returns the attributes of [SpellInfo] based on the attribute type.
     */
    int GetAttributes(Eluna* E, SpellInfo* spell_info)
    {
        uint8 attributeType = E->CHECKVAL<uint8>(2);
        uint32 attributes;

        switch(attributeType)
        {
            case 0:
                attributes = spell_info->Attributes;
                break;
            case 1:
                attributes = spell_info->AttributesEx;
                break;
            case 2:
                attributes = spell_info->AttributesEx2;
                break;
            case 3:
                attributes = spell_info->AttributesEx3;
                break;
            case 4:
                attributes = spell_info->AttributesEx4;
                break;
            case 5:
                attributes = spell_info->AttributesEx5;
                break;
            case 6:
                attributes = spell_info->AttributesEx6;
                break;
            case 7:
                attributes = spell_info->AttributesEx7;
                break;
            case 8:
                attributes = spell_info->AttributesCu;
                break;
        }

        E->Push(attributes);
        return 1;
    }
    
    /**
     * Determines whether the [SpellInfo] affects an area (AOE - Area of Effect)
     *
     * The affected area will depend upon the specifics of the spell.
     * A target can be an individual unit, player, or an area, and the spellInfo stores these details.
     * 
     * The function checks the spell's attributes to determine if the spell is designed to affect an area or not.
     * The outcome relies on spell's attributes field.
     * 
     * @return boolean : returns true if [SpellInfo] affects an area, else false
     */
    int IsAffectingArea(Eluna* E, SpellInfo* spell_info)
    {
        E->Push(spell_info->IsAffectingArea());
        return 1;
    }
    
    /**
     * Retrieves the category of the [SpellInfo].
     *
     * A spell's category is a way of grouping similar spells together.
     * It might define the spell's nature or its effect. 
     * For instance, damage spells, heal spells, and crowd-control spells might each have a different category.
     *
     * @return integer category : Returns the category of the [SpellInfo].
     */
    int GetCategory(Eluna* E, SpellInfo* spell_info)
    {
        E->Push(spell_info->GetCategory());
        return 1;
    }
    
    /**
     * Checks if the [SpellInfo] has a specific effect.
     *
     * A spell can have various effects such as damage, healing, or status changes.
     * These effects are identified by a predefined set of constants represented by the 'SpellEffects' enumeration.
     *
     * @param effect : The specific effect to check.
     * @return boolean : returns true if [SpellInfo] has the specific effect, else false
     */
    int HasEffect(Eluna* E, SpellInfo* spell_info)
    {
        uint8 effect = E->CHECKVAL<uint8>(2);
        E->Push(spell_info->HasEffect(static_cast<SpellEffects>(effect)));
        return 1;
    }
    
    /**
     * Checks if the [SpellInfo] has a specific aura.
     *
     * An aura represents a status change or modification due to a spell or ability. 
     * These auras are identified by a predefined set of constants represented by the 'AuraType' enumeration.
     *
     * @param aura : The specific aura to check.
     * @return boolean : Returns true if [SpellInfo] has the specific aura, else false
     */
    int HasAura(Eluna* E, SpellInfo* spell_info)
    {
        uint32 aura = E->CHECKVAL<uint32>(2);
        E->Push(spell_info->HasAura(static_cast<AuraType>(aura)));
        return 1;
    }
    
    /**
     * Checks if the [SpellInfo] has an area aura effect.
     *
     * Area aura is a type of spell effect that affects multiple targets within a certain area.
     * 
     * @return boolean : Returns true if [SpellInfo] has area aura effect, else false
     */
    int HasAreaAuraEffect(Eluna* E, SpellInfo* spell_info)
    {
        E->Push(spell_info->HasAreaAuraEffect());
        return 1;
    }
    
    /**
     * Checks if the [SpellInfo] contains only damage effects.
     *
     * Damage effects are spell effects that reduce the target's health points.
     *
     * @return boolean : Returns true if [SpellInfo] has only damage effects, else false.
     */
    int HasOnlyDamageEffects(Eluna* E, SpellInfo* spell_info)
    {
        E->Push(spell_info->HasOnlyDamageEffects());
        return 1;
    }

    ElunaRegister<SpellInfo> SpellInfoMethods[] =
    {
        // Getters
        { "GetName", &LuaSpellInfo::GetName },
        { "GetAttributes", &LuaSpellInfo::GetAttributes },
        { "GetCategory", &LuaSpellInfo::GetCategory },
        
        // Setters

        // Boolean
        { "HasAttribute", &LuaSpellInfo::HasAttribute },
        { "IsAffectingArea", &LuaSpellInfo::IsAffectingArea },
        { "HasEffect", &LuaSpellInfo::HasEffect },
        { "HasAura", &LuaSpellInfo::HasAura },
        { "HasAreaAuraEffect", &LuaSpellInfo::HasAreaAuraEffect },
        { "HasOnlyDamageEffects", &LuaSpellInfo::HasOnlyDamageEffects },
        
        // Other

        { NULL, NULL, METHOD_REG_NONE }
    };

}
#endif
