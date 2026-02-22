/*
* Copyright (C) 2010 - 2024 Eluna Lua Engine <https://elunaluaengine.github.io/>
* This program is free software licensed under GPL version 3
* Please see the included DOCS/LICENSE.md for more information
*/

#ifndef AURAMETHODS_H
#define AURAMETHODS_H

/***
 * The persistent effect of a [Spell] that remains on a [Unit] after the [Spell]
 *   has been cast.
 *
 * As an example, if you cast a damage-over-time spell on a target, an [Aura] is
 *   put on the target that deals damage continuously.
 *
 * [Aura]s on your player are displayed in-game as a series of icons to the left
 *   of the mini-map.
 *
 * Inherits all methods from: none
 */
namespace LuaAura
{
    /**
     * Returns the [Unit] that casted the [Spell] that caused this [Aura] to be applied.
     *
     * @return [Unit] caster
     */
    int GetCaster(Eluna* E, Aura* aura)
    {
        E->Push(aura->GetCaster());
        return 1;
    }

    /**
     * Returns the GUID of the [Unit] that casted the [Spell] that caused this [Aura] to be applied.
     *
     * @return string caster_guid : the GUID of the Unit as a decimal string
     */
    int GetCasterGUID(Eluna* E, Aura* aura)
    {
        E->Push(aura->GetCasterGUID());
        return 1;
    }

    /**
     * Returns the level of the [Unit] that casted the [Spell] that caused this [Aura] to be applied.
     *
     * @return uint32 caster_level
     */
    int GetCasterLevel(Eluna* E, Aura* aura)
    {
        E->Push(aura->GetCaster()->GetLevel());
        return 1;
    }

    /**
     * Returns the amount of time left until the [Aura] expires.
     *
     * @return int32 duration : amount of time left in milliseconds
     */
    int GetDuration(Eluna* E, Aura* aura)
    {
        E->Push(aura->GetDuration());
        return 1;
    }

    /**
     * Returns the ID of the [Spell] that caused this [Aura] to be applied.
     *
     * @return uint32 aura_id
     */
    int GetAuraId(Eluna* E, Aura* aura)
    {
        E->Push(aura->GetId());
        return 1;
    }

    /**
     * Returns the amount of time this [Aura] lasts when applied.
     *
     * To determine how much time has passed since this Aura was applied,
     *   subtract the result of [Aura]:GetDuration from the result of this method.
     *
     * @return int32 max_duration : the maximum duration of the Aura, in milliseconds
     */
    int GetMaxDuration(Eluna* E, Aura* aura)
    {
        E->Push(aura->GetMaxDuration());
        return 1;
    }

    /**
     * Returns the number of times the [Aura] has "stacked".
     *
     * This is the same as the number displayed on the [Aura]'s icon in-game.
     *
     * @return uint32 stack_amount
     */
    int GetStackAmount(Eluna* E, Aura* aura)
    {
        E->Push(aura->GetStackAmount());
        return 1;
    }

    /**
     * Returns the [Unit] that the [Aura] has been applied to.
     *
     * @return [Unit] owner
     */
    int GetOwner(Eluna* E, Aura* aura)
    {
        E->Push(aura->GetOwner());
        return 1;
    }

    /**
     * Change the amount of time before the [Aura] expires.
     *
     * @param int32 duration : the new duration of the Aura, in milliseconds
     */
    int SetDuration(Eluna* E, Aura* aura)
    {
        int32 duration = E->CHECKVAL<int32>(2);

        aura->SetDuration(duration);
        return 0;
    }

    /**
     * Change the maximum amount of time before the [Aura] expires.
     *
     * This does not affect the current duration of the [Aura], but if the [Aura]
     *   is reset to the maximum duration, it will instead change to `duration`.
     *
     * @param int32 duration : the new maximum duration of the Aura, in milliseconds
     */
    int SetMaxDuration(Eluna* E, Aura* aura)
    {
        int32 duration = E->CHECKVAL<int32>(2);

        aura->SetMaxDuration(duration);
        return 0;
    }

    /**
     * Change the amount of times the [Aura] has "stacked" on the [Unit].
     *
     * If `amount` is greater than or equal to the current number of stacks,
     *   then the [Aura] has its duration reset to the maximum duration.
     *
     * @param uint8 amount
     */
    int SetStackAmount(Eluna* E, Aura* aura)
    {
        uint8 amount = E->CHECKVAL<uint8>(2);

        aura->SetStackAmount(amount);
        return 0;
    }

    /**
     * Remove this [Aura] from the [Unit] it is applied to.
     */
    int Remove(Eluna* /*E*/, Aura* aura)
    {
        aura->Remove();
        return 0;
    }

    /**
     * Returns the [ElunaSpellInfo] of the spell that created this [Aura].
     *
     * @return [ElunaSpellInfo] spellInfo
     */
    int GetSpellInfo(Eluna* E, Aura* aura)
    {
        ElunaSpellInfo info(aura->GetId());
        E->Push(&info);
        return 1;
    }

    ElunaRegister<Aura> AuraMethods[] =
    {
        // Getters
        { "GetCaster", &LuaAura::GetCaster },
        { "GetCasterGUID", &LuaAura::GetCasterGUID },
        { "GetCasterLevel", &LuaAura::GetCasterLevel },
        { "GetDuration", &LuaAura::GetDuration },
        { "GetMaxDuration", &LuaAura::GetMaxDuration },
        { "GetAuraId", &LuaAura::GetAuraId },
        { "GetStackAmount", &LuaAura::GetStackAmount },
        { "GetOwner", &LuaAura::GetOwner },
        { "GetSpellInfo", &LuaAura::GetSpellInfo },

        // Setters
        { "SetDuration", &LuaAura::SetDuration },
        { "SetMaxDuration", &LuaAura::SetMaxDuration },
        { "SetStackAmount", &LuaAura::SetStackAmount },

        // Other
        { "Remove", &LuaAura::Remove }
    };
};
#endif
