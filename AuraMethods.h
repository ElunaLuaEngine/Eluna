/*
* Copyright (C) 2010 - 2014 Eluna Lua Engine <http://emudevs.com/>
* This program is free software licensed under GPL version 3
* Please see the included DOCS/LICENSE.md for more information
*/

#ifndef AURAMETHODS_H
#define AURAMETHODS_H

namespace LuaAura
{
    /**
     * Returns the `Unit` that casted the `Spell` that caused this Aura to be applied.
     *
     * @return :Unit the `Unit` that casted this Aura
     */
    int GetCaster(lua_State* L, Aura* aura)
    {
        Eluna::Push(L, aura->GetCaster());
        return 1;
    }

    /**
     * Returns the GUID of the `Unit` that casted the `Spell` that caused this Aura to be applied.
     *
     * @return :string the GUID of the `Unit` as a decimal string
     */
    int GetCasterGUID(lua_State* L, Aura* aura)
    {
#ifndef TRINITY
        Eluna::Push(L, aura->GetCasterGuid());
#else
        Eluna::Push(L, aura->GetCasterGUID());
#endif
        return 1;
    }

    /**
     * Returns the level of the `Unit` that casted the `Spell` that caused this Aura to be applied.
     *
     * @return :number the level of the `Unit`
     */
    int GetCasterLevel(lua_State* L, Aura* aura)
    {
        Eluna::Push(L, aura->GetCaster()->getLevel());
        return 1;
    }

    /**
     * Returns the amount of time left until the Aura expires.
     *
     * @return :number amount of time left in milliseconds
     */
    int GetDuration(lua_State* L, Aura* aura)
    {
#ifndef TRINITY
        Eluna::Push(L, aura->GetAuraDuration());
#else
        Eluna::Push(L, aura->GetDuration());
#endif
        return 1;
    }

    /**
     * Returns the ID of the `Spell` that caused this Aura to be applied.
     *
     * @return :number the `Spell` ID
     */
    int GetAuraId(lua_State* L, Aura* aura)
    {
        Eluna::Push(L, aura->GetId());
        return 1;
    }

    /**
     * Returns the amount of time this Aura lasts when applied.
     *
     * To determine how much time has passed since this Aura was applied,
     *   subtract the result of `GetDuration` from the result of this method.
     *
     * @return :number the maximum duration of the Aura, in milliseconds
     */
    int GetMaxDuration(lua_State* L, Aura* aura)
    {
#ifndef TRINITY
        Eluna::Push(L, aura->GetAuraMaxDuration());
#else
        Eluna::Push(L, aura->GetMaxDuration());
#endif
        return 1;
    }

    /**
     * Returns the number of times the Aura has "stacked".
     *
     * This is the same as the number displayed on the Aura's icon in-game.
     *
     * @return :number how many times the Aura has stacked
     */
    int GetStackAmount(lua_State* L, Aura* aura)
    {
        Eluna::Push(L, aura->GetStackAmount());
        return 1;
    }

    /**
     * Returns the `Unit` that the Aura has been applied to.
     *
     * @return :Unit who the Aura has been applied to
     */
    int GetOwner(lua_State* L, Aura* aura)
    {
#ifndef TRINITY
        Eluna::Push(L, aura->GetTarget());
#else
        Eluna::Push(L, aura->GetOwner());
#endif
        return 1;
    }

    /**
     * Change the amount of time before the Aura expires.
     *
     * @param duration :number the new duration of the Aura, in milliseconds
     */
    int SetDuration(lua_State* L, Aura* aura)
    {
        int duration = Eluna::CHECKVAL<int>(L, 2);
#ifndef TRINITY
        aura->GetHolder()->SetAuraDuration(duration);
#else
        aura->SetDuration(duration);
#endif
        return 0;
    }

    /**
     * Change the maximum amount of time before the Aura expires.
     *
     * This does not affect the current duration of the Aura, but if the Aura
     *   is reset to the maximum duration, it will instead change to `duration`.
     *
     * @param duration :number the new maximum duration of the Aura, in milliseconds
     */
    int SetMaxDuration(lua_State* L, Aura* aura)
    {
        int duration = Eluna::CHECKVAL<int>(L, 2);
#ifndef TRINITY
        aura->GetHolder()->SetAuraMaxDuration(duration);
#else
        aura->SetMaxDuration(duration);
#endif
        return 0;
    }

    /**
     * Change the amount of times the Aura has "stacked" on the `Unit`.
     *
     * If `amount` is greater than or equal to the current number of stacks,
     *   then the Aura has its duration reset to the maximum duration.
     *
     * @param amount :number the new stack amount for the Aura
     */
    int SetStackAmount(lua_State* L, Aura* aura)
    {
        int amount = Eluna::CHECKVAL<int>(L, 2);
#ifndef TRINITY
        aura->GetHolder()->SetStackAmount(amount);
#else
        aura->SetStackAmount(amount);
#endif
        return 0;
    }

    /**
     * Remove this Aura from the `Unit` it is applied to.
     */
    int Remove(lua_State* /*L*/, Aura* aura)
    {
#ifndef TRINITY
        aura->GetHolder()->RemoveAura(aura->GetEffIndex());
#else
        aura->Remove();
#endif
        return 0;
    }
};
#endif
