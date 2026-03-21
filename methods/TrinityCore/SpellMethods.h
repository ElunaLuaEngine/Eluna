/*
* Copyright (C) 2010 - 2024 Eluna Lua Engine <https://elunaluaengine.github.io/>
* This program is free software licensed under GPL version 3
* Please see the included DOCS/LICENSE.md for more information
*/

#ifndef SPELLMETHODS_H
#define SPELLMETHODS_H

/***
 * An instance of a spell, created when the spell is cast by a [Unit].
 *
 * Inherits all methods from: none
 */
namespace LuaSpell
{
    /**
     * Returns `true` if the [Spell] is automatically repeating, `false` otherwise.
     *
     * @return bool isAutoRepeating
     */
    int IsAutoRepeat(Eluna* E, Spell* spell)
    {
        E->Push(spell->IsAutoRepeat());
        return 1;
    }

    /**
     * Returns the [Unit] that casted the [Spell].
     *
     * @return [Unit] caster
     */
    int GetCaster(Eluna* E, Spell* spell)
    {
        E->Push(spell->GetCaster());
        return 1;
    }

    /**
     * Returns the cast time of the [Spell].
     *
     * @return int32 castTime
     */
    int GetCastTime(Eluna* E, Spell* spell)
    {
        E->Push(spell->GetCastTime());
        return 1;
    }

    /**
     * Returns the entry ID of the [Spell].
     *
     * @return uint32 entryId
     */
    int GetEntry(Eluna* E, Spell* spell)
    {
        E->Push(spell->m_spellInfo->Id);
        return 1;
    }

    /**
     * Returns the power cost of the [Spell].
     *
     * @return uint32 powerCost
     */
    int GetPowerCost(Eluna* E, Spell* spell)
    {
        E->Push(spell->GetPowerCost());
        return 1;
    }

    /**
     * Returns the spell duration of the [Spell].
     *
     * @return int32 duration
     */
    int GetDuration(Eluna* E, Spell* spell)
    {
        E->Push(spell->GetSpellInfo()->GetDuration());
        return 1;
    }

    /**
     * Returns the target destination coordinates of the [Spell].
     *
     * @return float x : x coordinate of the [Spell]
     * @return float y : y coordinate of the [Spell]
     * @return float z : z coordinate of the [Spell]
     */
    int GetTargetDest(Eluna* E, Spell* spell)
    {
        if (!spell->m_targets.HasDst())
            return 3;

        float x, y, z;
        spell->m_targets.GetDstPos()->GetPosition(x, y, z);

        E->Push(x);
        E->Push(y);
        E->Push(z);
        return 3;
    }

    /**
     * Returns the target [Object] of the [Spell].
     *
     * The target can be any of the following [Object] types:
     * - [Player]
     * - [Creature]
     * - [GameObject]
     * - [Item]
     * - [Corpse]
     *
     * @return [Object] target
     */
    int GetTarget(Eluna* E, Spell* spell)
    {
        if (GameObject* target = spell->m_targets.GetGOTarget())
            E->Push(target);
        else if (Item* target = spell->m_targets.GetItemTarget())
            E->Push(target);
        else if (Corpse* target = spell->m_targets.GetCorpseTarget())
            E->Push(target);
        else if (Unit* target = spell->m_targets.GetUnitTarget())
            E->Push(target);
        else if (WorldObject* target = spell->m_targets.GetObjectTarget())
            E->Push(target);
        return 1;
    }

    /**
     * Sets the [Spell] to automatically repeat.
     *
     * @param bool repeat : set variable to 'true' for spell to automatically repeat
     */
    int SetAutoRepeat(Eluna* E, Spell* spell)
    {
        bool repeat = E->CHECKVAL<bool>(2);
        spell->SetAutoRepeat(repeat);
        return 0;
    }

    /**
     * Casts the [Spell].
     *
     * @param bool skipCheck = false : skips initial checks to see if the [Spell] can be casted or not, this is optional
     */
    int Cast(Eluna* E, Spell* spell)
    {
        bool skipCheck = E->CHECKVAL<bool>(2, false);
        spell->cast(skipCheck);
        return 0;
    }

    /**
     * Cancels the [Spell].
     */
    int Cancel(Eluna* /*E*/, Spell* spell)
    {
        spell->cancel();
        return 0;
    }

    /**
     * Finishes the [Spell].
     */
    int Finish(Eluna* /*E*/, Spell* spell)
    {
        spell->finish();
        return 0;
    }

    /**
     * Returns the [SpellInfo] of the spell that created this [Spell].
     *
     * @return [SpellInfo] spellInfo
     */
    int GetSpellInfo(Eluna* E, Spell* spell)
    {
        ElunaSpellInfo info(spell->GetSpellInfo()->Id);
        E->Push(&info);
        return 1;
    }

    /**
     * Returns `true` if the [Spell] is triggered, `false` otherwise.
     *
     * @return bool isTriggered
     */
    int IsTriggered(Eluna* E, Spell* spell)
    {
        E->Push(spell->IsTriggered());
        return 1;
    }

    /**
     * Returns `true` if the [Spell] is ignoring cooldowns, `false` otherwise.
     *
     * @return bool isIgnoringCooldowns
     */
    int IsIgnoringCooldowns(Eluna* E, Spell* spell)
    {
        E->Push(spell->IsIgnoringCooldowns());
        return 1;
    }

    /**
     * Returns `true` if the [Spell] proc is disabled, `false` otherwise.
     *
     * @return bool isProcDisabled
     */
    int IsProcDisabled(Eluna* E, Spell* spell)
    {
        E->Push(spell->IsProcDisabled());
        return 1;
    }

    /**
     * Returns `true` if the [Spell] channel is active, `false` otherwise.
     *
     * @return bool isChannelActive
     */
    int IsChannelActive(Eluna* E, Spell* spell)
    {
        E->Push(spell->IsChannelActive());
        return 1;
    }

    /**
     * Returns `true` if the [Spell] is an auto action reset spell, `false` otherwise.
     *
     * @return bool isAutoActionResetSpell
     */
    int IsAutoActionResetSpell(Eluna* E, Spell* spell)
    {
        E->Push(spell->IsAutoActionResetSpell());
        return 1;
    }

    /**
     * Returns `true` if the [Spell] is positive, `false` otherwise.
     *
     * @return bool isPositive
     */
    int IsPositive(Eluna* E, Spell* spell)
    {
        E->Push(spell->IsPositive());
        return 1;
    }

    /**
     * Returns `true` if the [Spell] is deletable, `false` otherwise.
     *
     * @return bool isDeletable
     */
    int IsDeletable(Eluna* E, Spell* spell)
    {
        E->Push(spell->IsDeletable());
        return 1;
    }

    /**
     * Returns `true` if the [Spell] is interruptable, `false` otherwise.
     *
     * @return bool isInterruptable
     */
    int IsInterruptable(Eluna* E, Spell* spell)
    {
        E->Push(spell->IsInterruptable());
        return 1;
    }

    /**
     * Returns `true` if the [Spell] needs to be sent to the client, `false` otherwise.
     *
     * @return bool isNeedSendToClient
     */
    int IsNeedSendToClient(Eluna* E, Spell* spell)
    {
        E->Push(spell->IsNeedSendToClient());
        return 1;
    }

    /**
     * Returns `true` if the [Spell] was triggered by the given [SpellInfo], `false` otherwise.
     *
     * @param [SpellInfo] spellInfo : the aura spell info to check against
     * @return bool isTriggeredByAura
     */
    int IsTriggeredByAura(Eluna* E, Spell* spell)
    {
        ElunaSpellInfo* info = E->CHECKOBJ<ElunaSpellInfo>(2);
        E->Push(spell->IsTriggeredByAura(info->GetSpellInfo()));
        return 1;
    }

    /**
     * Returns the original caster [Unit] of the [Spell].
     *
     * @return [Unit] originalCaster
     */
    int GetOriginalCaster(Eluna* E, Spell* spell)
    {
        E->Push(spell->GetOriginalCaster());
        return 1;
    }

    /**
     * Returns the current state of the [Spell].
     *
     * @return uint32 state
     */
    int GetState(Eluna* E, Spell* spell)
    {
        E->Push(spell->getState());
        return 1;
    }

    /**
     * Returns the delay start time of the [Spell].
     *
     * @return uint64 delayStart
     */
    int GetDelayStart(Eluna* E, Spell* spell)
    {
        E->Push(spell->GetDelayStart());
        return 1;
    }

    /**
     * Returns the delay moment of the [Spell].
     *
     * @return uint64 delayMoment
     */
    int GetDelayMoment(Eluna* E, Spell* spell)
    {
        E->Push(spell->GetDelayMoment());
        return 1;
    }

    /**
     * Returns the rune state of the [Spell].
     *
     * @return uint8 runeState
     */
    int GetRuneState(Eluna* E, Spell* spell)
    {
        E->Push(spell->GetRuneState());
        return 1;
    }

    /**
     * Returns the number of unit targets for the given effect index of the [Spell].
     *
     * @param uint8 effIndex : the effect index to check
     * @return int32 count
     */
    int GetUnitTargetCountForEffect(Eluna* E, Spell* spell)
    {
        uint8 effIndex = E->CHECKVAL<uint8>(2);
        E->Push(static_cast<int32>(spell->GetUnitTargetCountForEffect(static_cast<SpellEffIndex>(effIndex))));
        return 1;
    }

    /**
     * Returns the number of GameObject targets for the given effect index of the [Spell].
     *
     * @param uint8 effIndex : the effect index to check
     * @return int32 count
     */
    int GetGameObjectTargetCountForEffect(Eluna* E, Spell* spell)
    {
        uint8 effIndex = E->CHECKVAL<uint8>(2);
        E->Push(static_cast<int32>(spell->GetGameObjectTargetCountForEffect(static_cast<SpellEffIndex>(effIndex))));
        return 1;
    }

    /**
     * Returns the number of item targets for the given effect index of the [Spell].
     *
     * @param uint8 effIndex : the effect index to check
     * @return int32 count
     */
    int GetItemTargetCountForEffect(Eluna* E, Spell* spell)
    {
        uint8 effIndex = E->CHECKVAL<uint8>(2);
        E->Push(static_cast<int32>(spell->GetItemTargetCountForEffect(static_cast<SpellEffIndex>(effIndex))));
        return 1;
    }

    /**
     * Calculates the damage for the given effect index of the [Spell].
     *
     * @param uint8 effIndex : the effect index to calculate damage for
     * @return int32 damage
     */
    int CalculateDamage(Eluna* E, Spell* spell)
    {
        uint8 effIndex = E->CHECKVAL<uint8>(2);
        E->Push(spell->CalculateDamage(spell->GetSpellInfo()->GetEffect(static_cast<SpellEffIndex>(effIndex))));
        return 1;
    }

    /**
     * Sets the state of the [Spell].
     *
     * @param uint32 state : the state to set
     */
    int SetState(Eluna* E, Spell* spell)
    {
        uint32 state = E->CHECKVAL<uint32>(2);
        spell->setState(state);
        return 0;
    }

    /**
     * Sets the delay start time of the [Spell].
     *
     * @param uint64 time : the delay start time to set
     */
    int SetDelayStart(Eluna* E, Spell* spell)
    {
        uint64 time = E->CHECKVAL<uint64>(2);
        spell->SetDelayStart(time);
        return 0;
    }

    /**
     * Sets the rune state of the [Spell].
     *
     * @param uint8 value : the rune state to set
     */
    int SetRuneState(Eluna* E, Spell* spell)
    {
        uint8 value = E->CHECKVAL<uint8>(2);
        spell->SetRuneState(value);
        return 0;
    }

    /**
     * Sets whether the [Spell] is currently being executed.
     *
     * @param bool yes : set to 'true' if the spell is currently being executed
     */
    int SetExecutedCurrently(Eluna* E, Spell* spell)
    {
        bool yes = E->CHECKVAL<bool>(2);
        spell->SetExecutedCurrently(yes);
        return 0;
    }

    /**
     * Sets whether the [Spell] is referenced from the current spell.
     *
     * @param bool yes : set to 'true' if the spell is referenced from the current spell
     */
    int SetReferencedFromCurrent(Eluna* E, Spell* spell)
    {
        bool yes = E->CHECKVAL<bool>(2);
        spell->SetReferencedFromCurrent(yes);
        return 0;
    }

    /**
     * Sets a spell value modifier on the [Spell].
     *
     * @param uint8 mod : the [SpellValueMod] to set
     * @param int32 value : the value to set
     */
    int SetSpellValue(Eluna* E, Spell* spell)
    {
        uint8 mod = E->CHECKVAL<uint8>(2);
        int32 value = E->CHECKVAL<int32>(3);
        spell->SetSpellValue(static_cast<SpellValueMod>(mod), value);
        return 0;
    }

    /**
     * Updates the [Spell]'s pointers. Must be used after time delays on non-triggered spell casts.
     *
     * @return bool success
     */
    int UpdatePointers(Eluna* E, Spell* spell)
    {
        E->Push(spell->UpdatePointers());
        return 1;
    }

    /**
     * Cleans up the target list of the [Spell].
     */
    int CleanupTargetList(Eluna* /*E*/, Spell* spell)
    {
        spell->CleanupTargetList();
        return 0;
    }

    ElunaRegister<Spell> SpellMethods[] =
    {
        // Getters
        { "GetCaster",                          &LuaSpell::GetCaster },
        { "GetOriginalCaster",                  &LuaSpell::GetOriginalCaster },
        { "GetCastTime",                        &LuaSpell::GetCastTime },
        { "GetEntry",                           &LuaSpell::GetEntry },
        { "GetDuration",                        &LuaSpell::GetDuration },
        { "GetPowerCost",                       &LuaSpell::GetPowerCost },
        { "GetTargetDest",                      &LuaSpell::GetTargetDest },
        { "GetTarget",                          &LuaSpell::GetTarget },
        { "GetState",                           &LuaSpell::GetState },
        { "GetDelayStart",                      &LuaSpell::GetDelayStart },
        { "GetDelayMoment",                     &LuaSpell::GetDelayMoment },
        { "GetRuneState",                       &LuaSpell::GetRuneState },
        { "GetUnitTargetCountForEffect",        &LuaSpell::GetUnitTargetCountForEffect },
        { "GetGameObjectTargetCountForEffect",  &LuaSpell::GetGameObjectTargetCountForEffect },
        { "GetItemTargetCountForEffect",        &LuaSpell::GetItemTargetCountForEffect },
        { "GetSpellInfo",                       &LuaSpell::GetSpellInfo },
        { "CalculateDamage",                    &LuaSpell::CalculateDamage },
        // Setters
        { "SetAutoRepeat",                      &LuaSpell::SetAutoRepeat },
        { "SetSpellValue",                      &LuaSpell::SetSpellValue },
        { "SetState",                           &LuaSpell::SetState },
        { "SetDelayStart",                      &LuaSpell::SetDelayStart },
        { "SetRuneState",                       &LuaSpell::SetRuneState },
        { "SetExecutedCurrently",               &LuaSpell::SetExecutedCurrently },
        { "SetReferencedFromCurrent",           &LuaSpell::SetReferencedFromCurrent },
        // Booleans
        { "IsAutoRepeat",                       &LuaSpell::IsAutoRepeat },
        { "IsTriggered",                        &LuaSpell::IsTriggered },
        { "IsIgnoringCooldowns",                &LuaSpell::IsIgnoringCooldowns },
        { "IsProcDisabled",                     &LuaSpell::IsProcDisabled },
        { "IsChannelActive",                    &LuaSpell::IsChannelActive },
        { "IsAutoActionResetSpell",             &LuaSpell::IsAutoActionResetSpell },
        { "IsPositive",                         &LuaSpell::IsPositive },
        { "IsDeletable",                        &LuaSpell::IsDeletable },
        { "IsInterruptable",                    &LuaSpell::IsInterruptable },
        { "IsNeedSendToClient",                 &LuaSpell::IsNeedSendToClient },
        { "IsTriggeredByAura",                  &LuaSpell::IsTriggeredByAura },
        { "UpdatePointers",                     &LuaSpell::UpdatePointers },
        // Other
        { "Cancel",                             &LuaSpell::Cancel },
        { "Cast",                               &LuaSpell::Cast },
        { "Finish",                             &LuaSpell::Finish },
        { "CleanupTargetList",                  &LuaSpell::CleanupTargetList },
    };
};
#endif
