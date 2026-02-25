/*
* Copyright (C) 2010 - 2024 Eluna Lua Engine <https://elunaluaengine.github.io/>
* This program is free software licensed under GPL version 3
* Please see the included DOCS/LICENSE.md for more information
*/

#ifndef UNITMETHODS_H
#define UNITMETHODS_H

/***
 * Inherits all methods from: [Object], [WorldObject]
 */
namespace LuaUnit
{
    /**
    * Sets a mechanic immunity for the [Unit].
    *
    * @table
    * @columns [Mechanic, ID, Comment]
    * @values [MECHANIC_NONE, 0,  ""]
    * @values [MECHANIC_CHARM, 1,  ""]
    * @values [MECHANIC_DISORIENTED, 2,  ""]
    * @values [MECHANIC_DISARM, 3,  ""]
    * @values [MECHANIC_DISTRACT, 4,  ""]
    * @values [MECHANIC_FEAR, 5,  ""]
    * @values [MECHANIC_GRIP, 6,  ""]
    * @values [MECHANIC_ROOT, 7,  ""]
    * @values [MECHANIC_SLOW_ATTACK, 8,  ""]
    * @values [MECHANIC_SILENCE, 9,  ""]
    * @values [MECHANIC_SLEEP, 10, ""]
    * @values [MECHANIC_SNARE, 11, ""]
    * @values [MECHANIC_STUN, 12, ""]
    * @values [MECHANIC_FREEZE, 13, ""]
    * @values [MECHANIC_KNOCKOUT, 14, ""]
    * @values [MECHANIC_BLEED, 15, ""]
    * @values [MECHANIC_BANDAGE, 16, ""]
    * @values [MECHANIC_POLYMORPH, 17, ""]
    * @values [MECHANIC_BANISH, 18, ""]
    * @values [MECHANIC_SHIELD, 19, ""]
    * @values [MECHANIC_SHACKLE, 20, ""]
    * @values [MECHANIC_MOUNT, 21, ""]
    * @values [MECHANIC_INFECTED, 22, ""]
    * @values [MECHANIC_TURN, 23, ""]
    * @values [MECHANIC_HORROR, 24, ""]
    * @values [MECHANIC_INVULNERABILITY, 25, ""]
    * @values [MECHANIC_INTERRUPT, 26, ""]
    * @values [MECHANIC_DAZE, 27, ""]
    * @values [MECHANIC_DISCOVERY, 28, ""]
    * @values [MECHANIC_IMMUNE_SHIELD, 29, "Divine (Blessing) Shield/Protection and Ice Block"]
    * @values [MECHANIC_SAPPED, 30, ""]
    * @values [MECHANIC_ENRAGED, 31, ""]
    *
    * @param int32 immunity : new value for the immunity mask
    * @param bool apply = true : if true, the immunity is applied, otherwise it is removed
    */
    int SetImmuneTo(Eluna* E, Unit* unit)
    {
        int32 immunity = E->CHECKVAL<int32>(2);
        bool apply = E->CHECKVAL<bool>(3, true);

        unit->ApplySpellImmune(0, 5, immunity, apply);
        return 0;
    }
    /**
     * The [Unit] tries to attack a given target
     *
     * @param [Unit] who : [Unit] to attack
     * @param bool meleeAttack = false: attack with melee or not
     * @return didAttack : if the [Unit] did not attack
     */
    int Attack(Eluna* E, Unit* unit)
    {
        Unit* who = E->CHECKOBJ<Unit>(2);
        bool meleeAttack = E->CHECKVAL<bool>(3, false);

        E->Push(unit->Attack(who, meleeAttack));
        return 1;
    }

    /**
     * The [Unit] stops attacking its target
     *
     * @return bool isAttacking : if the [Unit] wasn't attacking already
     */
    int AttackStop(Eluna* E, Unit* unit)
    {
        E->Push(unit->AttackStop());
        return 1;
    }

    /**
     * Returns true if the [Unit] is standing.
     *
     * @return bool isStanding
     */
    int IsStandState(Eluna* E, Unit* unit)
    {
        E->Push(unit->IsStandState());
        return 1;
    }

    /**
     * Returns true if the [Unit] is mounted.
     *
     * @return bool isMounted
     */
    int IsMounted(Eluna* E, Unit* unit)
    {
        E->Push(unit->IsMounted());
        return 1;
    }

    /**
     * Returns true if the [Unit] is rooted.
     *
     * @return bool isRooted
     */
    int IsRooted(Eluna* E, Unit* unit)
    {
        E->Push(unit->IsRooted() || unit->HasUnitMovementFlag(MOVEMENTFLAG_ROOT));
        return 1;
    }

    /**
     * Returns true if the [Unit] has full health.
     *
     * @return bool hasFullHealth
     */
    int IsFullHealth(Eluna* E, Unit* unit)
    {
        E->Push(unit->IsFullHealth());
        return 1;
    }

    /**
     * Returns true if the [Unit] is in an accessible place for the given [Creature].
     *
     * @param [WorldObject] obj
     * @param float radius
     * @return bool isAccessible
     */
    int IsInAccessiblePlaceFor(Eluna* E, Unit* unit)
    {
        Creature* creature = E->CHECKOBJ<Creature>(2);

        E->Push(unit->isInAccessiblePlaceFor(creature));
        return 1;
    }

    /**
     * Returns true if the [Unit] an auctioneer.
     *
     * @return bool isAuctioneer
     */
    int IsAuctioneer(Eluna* E, Unit* unit)
    {
        E->Push(unit->IsAuctioner());
        return 1;
    }

    /**
     * Returns true if the [Unit] a guild master.
     *
     * @return bool isGuildMaster
     */
    int IsGuildMaster(Eluna* E, Unit* unit)
    {
        E->Push(unit->IsGuildMaster());
        return 1;
    }

    /**
     * Returns true if the [Unit] an innkeeper.
     *
     * @return bool isInnkeeper
     */
    int IsInnkeeper(Eluna* E, Unit* unit)
    {
        E->Push(unit->IsInnkeeper());
        return 1;
    }

    /**
     * Returns true if the [Unit] a trainer.
     *
     * @return bool isTrainer
     */
    int IsTrainer(Eluna* E, Unit* unit)
    {
        E->Push(unit->IsTrainer());
        return 1;
    }

    /**
     * Returns true if the [Unit] is able to show a gossip window.
     *
     * @return bool hasGossip
     */
    int IsGossip(Eluna* E, Unit* unit)
    {
        E->Push(unit->IsGossip());
        return 1;
    }

    /**
     * Returns true if the [Unit] is a taxi master.
     *
     * @return bool isTaxi
     */
    int IsTaxi(Eluna* E, Unit* unit)
    {
        E->Push(unit->IsTaxi());
        return 1;
    }

    /**
     * Returns true if the [Unit] is a spirit healer.
     *
     * @return bool isSpiritHealer
     */
    int IsSpiritHealer(Eluna* E, Unit* unit)
    {
        E->Push(unit->IsSpiritHealer());
        return 1;
    }

    /**
     * Returns true if the [Unit] is a spirit guide.
     *
     * @return bool isSpiritGuide
     */
    int IsSpiritGuide(Eluna* E, Unit* unit)
    {
        E->Push(unit->IsSpiritGuide());
        return 1;
    }

    /**
     * Returns true if the [Unit] is a tabard designer.
     *
     * @return bool isTabardDesigner
     */
    int IsTabardDesigner(Eluna* E, Unit* unit)
    {
        E->Push(unit->IsTabardDesigner());
        return 1;
    }

    /**
     * Returns true if the [Unit] provides services like vendor, training and auction.
     *
     * @return bool isTabardDesigner
     */
    int IsServiceProvider(Eluna* E, Unit* unit)
    {
        E->Push(unit->IsServiceProvider());
        return 1;
    }

    /**
     * Returns true if the [Unit] is a spirit guide or spirit healer.
     *
     * @return bool isSpiritService
     */
    int IsSpiritService(Eluna* E, Unit* unit)
    {
        E->Push(unit->IsSpiritService());
        return 1;
    }

    /**
     * Returns true if the [Unit] is alive.
     *
     * @return bool isAlive
     */
    int IsAlive(Eluna* E, Unit* unit)
    {
        E->Push(unit->IsAlive());
        return 1;
    }

    /**
     * Returns true if the [Unit] is dead.
     *
     * @return bool isDead
     */
    int IsDead(Eluna* E, Unit* unit)
    {
        E->Push(unit->isDead());
        return 1;
    }

    /**
     * Returns true if the [Unit] is dying.
     *
     * @return bool isDying
     */
    int IsDying(Eluna* E, Unit* unit)
    {
        E->Push(unit->isDying());
        return 1;
    }

    /**
     * Returns true if the [Unit] is a banker.
     *
     * @return bool isBanker
     */
    int IsBanker(Eluna* E, Unit* unit)
    {
        E->Push(unit->IsBanker());
        return 1;
    }

    /**
     * Returns true if the [Unit] is a vendor.
     *
     * @return bool isVendor
     */
    int IsVendor(Eluna* E, Unit* unit)
    {
        E->Push(unit->IsVendor());
        return 1;
    }

    /**
     * Returns true if the [Unit] is a battle master.
     *
     * @return bool isBattleMaster
     */
    int IsBattleMaster(Eluna* E, Unit* unit)
    {
        E->Push(unit->IsBattleMaster());
        return 1;
    }

    /**
     * Returns true if the [Unit] is a charmed.
     *
     * @return bool isCharmed
     */
    int IsCharmed(Eluna* E, Unit* unit)
    {
        E->Push(unit->IsCharmed());
        return 1;
    }

    /**
     * Returns true if the [Unit] is an armorer and can repair equipment.
     *
     * @return bool isArmorer
     */
    int IsArmorer(Eluna* E, Unit* unit)
    {
        E->Push(unit->IsArmorer());
        return 1;
    }

    /**
     * Returns true if the [Unit] is attacking a player.
     *
     * @return bool isAttackingPlayer
     */
    int IsAttackingPlayer(Eluna* E, Unit* unit)
    {
        E->Push(unit->isAttackingPlayer());
        return 1;
    }

    /**
     * Returns true if the [Unit] flagged for PvP.
     *
     * @return bool isPvP
     */
    int IsPvPFlagged(Eluna* E, Unit* unit)
    {
        E->Push(unit->IsPvP());
        return 1;
    }

    /**
     * Returns true if the [Unit] is on a [Vehicle].
     *
     * @return bool isOnVehicle
     */
    int IsOnVehicle(Eluna* E, Unit* unit)
    {
        E->Push(unit->GetVehicle());
        return 1;
    }

    /**
     * Returns true if the [Unit] is in combat.
     *
     * @return bool inCombat
     */
    int IsInCombat(Eluna* E, Unit* unit)
    {
        E->Push(unit->IsInCombat());
        return 1;
    }

    /**
     * Returns true if the [Unit] is under water.
     *
     * @return bool underWater
     */
    int IsUnderWater(Eluna* E, Unit* unit)
    {
        E->Push(unit->IsUnderWater());
        return 1;
    }

    /**
     * Returns true if the [Unit] is in water.
     *
     * @return bool inWater
     */
    int IsInWater(Eluna* E, Unit* unit)
    {
        E->Push(unit->IsInWater());
        return 1;
    }

    /**
     * Returns true if the [Unit] is not moving.
     *
     * @return bool notMoving
     */
    int IsStopped(Eluna* E, Unit* unit)
    {
        E->Push(unit->IsStopped());
        return 1;
    }

    /**
     * Returns true if the [Unit] is a quest giver.
     *
     * @return bool questGiver
     */
    int IsQuestGiver(Eluna* E, Unit* unit)
    {
        E->Push(unit->IsQuestGiver());
        return 1;
    }

    /**
     * Returns true if the [Unit]'s health is below the given percentage.
     *
     * @param int32 healthpct : percentage in integer from
     * @return bool isBelow
     */
    int HealthBelowPct(Eluna* E, Unit* unit)
    {
        E->Push(unit->HealthBelowPct(E->CHECKVAL<int32>(2)));
        return 1;
    }

    /**
     * Returns true if the [Unit]'s health is above the given percentage.
     *
     * @param int32 healthpct : percentage in integer from
     * @return bool isAbove
     */
    int HealthAbovePct(Eluna* E, Unit* unit)
    {
        E->Push(unit->HealthAbovePct(E->CHECKVAL<int32>(2)));
        return 1;
    }

    /**
     * Returns true if the [Unit] has an aura from the given spell entry.
     *
     * @param uint32 spell : entry of the aura spell
     * @return bool hasAura
     */
    int HasAura(Eluna* E, Unit* unit)
    {
        uint32 spell = E->CHECKVAL<uint32>(2);

        E->Push(unit->HasAura(spell));
        return 1;
    }

    /**
     * Returns true if the [Unit] is casting a spell
     *
     * @return bool isCasting
     */
    int IsCasting(Eluna* E, Unit* unit)
    {
        E->Push(unit->HasUnitState(UNIT_STATE_CASTING));
        return 1;
    }

    /**
     * Returns true if the [Unit] has the given unit state.
     *
     * @param [UnitState] state : an unit state
     * @return bool hasState
     */
    int HasUnitState(Eluna* E, Unit* unit)
    {
        uint32 state = E->CHECKVAL<uint32>(2);

        E->Push(unit->HasUnitState(state));
        return 1;
    }

    /**
     * Returns true if the [Unit] is visible, false otherwise.
     *
     * @return bool isVisible
     */
    int IsVisible(Eluna* E, Unit* unit)
    {
        E->Push(unit->IsVisible());
        return 1;
    }

    /**
     * Returns true if the [Unit] is moving, false otherwise.
     *
     * @return bool isMoving
     */
    int IsMoving(Eluna* E, Unit* unit)
    {
        E->Push(unit->isMoving());
        return 1;
    }

    /**
     * Returns true if the [Unit] is flying, false otherwise.
     *
     * @return bool isFlying
     */
    int IsFlying(Eluna* E, Unit* unit)
    {
        E->Push(unit->IsFlying());
        return 1;
    }

    /**
     * Returns the [Unit]'s owner.
     *
     * @return [Unit] owner
     */
    int GetOwner(Eluna* E, Unit* unit)
    {
        E->Push(unit->GetOwner());
        return 1;
    }

    /**
     * Returns the [Unit]'s owner's GUID.
     *
     * @return ObjectGuid ownerGUID
     */
    int GetOwnerGUID(Eluna* E, Unit* unit)
    {
        E->Push(unit->GetOwnerGUID());
        return 1;
    }

    /**
     * Returns the [Unit]'s mount's modelID.
     *
     * @return uint32 mountId : displayId of the mount
     */
    int GetMountId(Eluna* E, Unit* unit)
    {
        E->Push(unit->GetMountDisplayId());
        return 1;
    }

    /**
     * Returns the [Unit]'s creator's GUID.
     *
     * @return ObjectGuid creatorGUID
     */
    int GetCreatorGUID(Eluna* E, Unit* unit)
    {
        E->Push(unit->GetCreatorGUID());
        return 1;
    }

    /**
     * Returns the [Unit]'s charmer's GUID.
     *
     * @return ObjectGuid charmerGUID
     */
    int GetCharmerGUID(Eluna* E, Unit* unit)
    {
        E->Push(unit->GetCharmerGUID());
        return 1;
    }

    /**
     * Returns the GUID of the [Unit]'s charmed entity.
     *
     * @return ObjectGuid charmedGUID
     */
    int GetCharmGUID(Eluna* E, Unit* unit)
    {
        E->Push(unit->GetCharmedGUID());
        return 1;
    }

    /**
     * Returns the GUID of the [Unit]'s pet.
     *
     * @return ObjectGuid petGUID
     */
    int GetPetGUID(Eluna* E, Unit* unit)
    {
        E->Push(unit->GetPetGUID());
        return 1;
    }

    /**
     * Returns the GUID of the [Unit]'s charmer or owner.
     *
     * @return ObjectGuid controllerGUID
     */
    int GetControllerGUID(Eluna* E, Unit* unit)
    {
        E->Push(unit->GetCharmerOrOwnerGUID());
        return 1;
    }

    /**
     * Returns the GUID of the [Unit]'s charmer or owner or its own GUID.
     *
     * @return ObjectGuid controllerGUID
     */
    int GetControllerGUIDS(Eluna* E, Unit* unit)
    {
        E->Push(unit->GetCharmerOrOwnerOrOwnGUID());
        return 1;
    }

    /**
     * Returns [Unit]'s specified stat
     *
     * @param uint32 statType
     * @return float stat
     */
    int GetStat(Eluna* E, Unit* unit)
    {
        uint32 stat = E->CHECKVAL<uint32>(2);

        if (stat >= MAX_STATS)
            return 1;

        E->Push(unit->GetStat((Stats)stat));
        return 1;
    }

    /**
     * Returns the [Unit]'s base spell power
     *
     * @param uint32 spellSchool
     * @return uint32 spellPower
     */
    int GetBaseSpellPower(Eluna* E, Unit* unit)
    {
        uint32 spellschool = E->CHECKVAL<uint32>(2);

        if (spellschool >= MAX_SPELL_SCHOOL)
            return 1;

        E->Push(unit->GetUInt32Value(PLAYER_FIELD_MOD_DAMAGE_DONE_POS + spellschool));
        return 1;
    }

    /**
     * Returns the [Unit]'s current victim target or nil.
     *
     * @return [Unit] victim
     */
    int GetVictim(Eluna* E, Unit* unit)
    {
        E->Push(unit->GetVictim());
        return 1;
    }

    /**
     * Returns the currently casted [Spell] of given type or nil.
     *
     * @table
     * @columns [CurrentSpellTypes, ID]
     * @values [CURRENT_MELEE_SPELL, 0]
     * @values [CURRENT_GENERIC_SPELL, 1]
     * @values [CURRENT_CHANNELED_SPELL, 2]
     * @values [CURRENT_AUTOREPEAT_SPELL, 3]
     *
     * @param [CurrentSpellTypes] spellType
     * @return [Spell] castedSpell
     */
    int GetCurrentSpell(Eluna* E, Unit* unit)
    {
        uint32 type = E->CHECKVAL<uint32>(2);
        if (type >= CURRENT_MAX_SPELL)
            return luaL_argerror(E->L, 2, "valid CurrentSpellTypes expected");

        E->Push(unit->GetCurrentSpell(type));
        return 1;
    }

    /**
     * Returns the [Unit]'s current stand state.
     *
     * @return uint8 standState
     */
    int GetStandState(Eluna* E, Unit* unit)
    {
        E->Push(unit->GetStandState());
        return 1;
    }

    /**
     * Returns the [Unit]'s current display ID.
     *
     * @return uint32 displayId
     */
    int GetDisplayId(Eluna* E, Unit* unit)
    {
        E->Push(unit->GetDisplayId());
        return 1;
    }

    /**
     * Returns the [Unit]'s native/original display ID.
     *
     * @return uint32 displayId
     */
    int GetNativeDisplayId(Eluna* E, Unit* unit)
    {
        E->Push(unit->GetNativeDisplayId());
        return 1;
    }

    /**
     * Returns the [Unit]'s level.
     *
     * @return uint8 level
     */
    int GetLevel(Eluna* E, Unit* unit)
    {
        E->Push(unit->GetLevel());
        return 1;
    }

    /**
     * Returns the [Unit]'s health amount.
     *
     * @return uint32 healthAmount
     */
    int GetHealth(Eluna* E, Unit* unit)
    {
        E->Push(unit->GetHealth());
        return 1;
    }

    Powers PowerSelectorHelper(Eluna* E, Unit* unit, int powerType = -1)
    {
        if (powerType == -1)
            return unit->GetPowerType();

        if (powerType < 0 || powerType >= int(MAX_POWERS))
            luaL_argerror(E->L, 2, "valid Powers expected");

        return (Powers)powerType;
    }

    /**
     * Returns the [Unit]'s power amount for given power type.
     *
     * @table
     * @columns [Powers, ID, Comment]
     * @values [POWER_MANA, 0, ""]
     * @values [POWER_RAGE, 1, ""]
     * @values [POWER_FOCUS, 2, ""]
     * @values [POWER_ENERGY, 3, ""]
     * @values [POWER_HAPPINESS, 4, ""]
     * @values [POWER_RUNE, 5, ""]
     * @values [POWER_RUNIC_POWER, 6, ""]
     * @values [MAX_POWERS, 7, ""]
     * @values [POWER_ALL, 127, "default for class?"]
     * @values [POWER_HEALTH, 0xFFFFFFFE, "-2 as signed value"]
     *
     * @param int type = -1 : a valid power type from [Powers] or -1 for the [Unit]'s current power type
     * @return uint32 powerAmount
     */
    int GetPower(Eluna* E, Unit* unit)
    {
        int type = E->CHECKVAL<int>(2, -1);
        Powers power = PowerSelectorHelper(E, unit, type);

        E->Push(unit->GetPower(power));
        return 1;
    }

    /**
     * Returns the [Unit]'s max power amount for given power type.
     *
     * @table
     * @columns [Powers, ID, Comment]
     * @values [POWER_MANA, 0, ""]
     * @values [POWER_RAGE, 1, ""]
     * @values [POWER_FOCUS, 2, ""]
     * @values [POWER_ENERGY, 3, ""]
     * @values [POWER_HAPPINESS, 4, ""]
     * @values [POWER_RUNE, 5, ""]
     * @values [POWER_RUNIC_POWER, 6, ""]
     * @values [MAX_POWERS, 7, ""]
     * @values [POWER_ALL, 127, "default for class?"]
     * @values [POWER_HEALTH, 0xFFFFFFFE, "-2 as signed value"]
     *
     * @param int type = -1 : a valid power type from [Powers] or -1 for the [Unit]'s current power type
     * @return uint32 maxPowerAmount
     */
    int GetMaxPower(Eluna* E, Unit* unit)
    {
        int type = E->CHECKVAL<int>(2, -1);
        Powers power = PowerSelectorHelper(E, unit, type);

        E->Push(unit->GetMaxPower(power));
        return 1;
    }

    /**
     * Returns the [Unit]'s power percent for given power type.
     *
     * @table
     * @columns [Powers, ID, Comment]
     * @values [POWER_MANA, 0, ""]
     * @values [POWER_RAGE, 1, ""]
     * @values [POWER_FOCUS, 2, ""]
     * @values [POWER_ENERGY, 3, ""]
     * @values [POWER_HAPPINESS, 4, ""]
     * @values [POWER_RUNE, 5, ""]
     * @values [POWER_RUNIC_POWER, 6, ""]
     * @values [MAX_POWERS, 7, ""]
     * @values [POWER_ALL, 127, "default for class?"]
     * @values [POWER_HEALTH, 0xFFFFFFFE, "-2 as signed value"]
     *
     * @param int type = -1 : a valid power type from [Powers] or -1 for the [Unit]'s current power type
     * @return float powerPct
     */
    int GetPowerPct(Eluna* E, Unit* unit)
    {
        int type = E->CHECKVAL<int>(2, -1);
        Powers power = PowerSelectorHelper(E, unit, type);

        float percent = ((float)unit->GetPower(power) / (float)unit->GetMaxPower(power)) * 100.0f;

        E->Push(percent);
        return 1;
    }

    /**
     * Returns the [Unit]'s current power type.
     *
     * @table
     * @columns [Powers, ID, Comment]
     * @values [POWER_MANA, 0, ""]
     * @values [POWER_RAGE, 1, ""]
     * @values [POWER_FOCUS, 2, ""]
     * @values [POWER_ENERGY, 3, ""]
     * @values [POWER_HAPPINESS, 4, ""]
     * @values [POWER_RUNE, 5, ""]
     * @values [POWER_RUNIC_POWER, 6, ""]
     * @values [MAX_POWERS, 7, ""]
     * @values [POWER_ALL, 127, "default for class?"]
     * @values [POWER_HEALTH, 0xFFFFFFFE, "-2 as signed value"]
     *
     * @return [Powers] powerType
     */
    int GetPowerType(Eluna* E, Unit* unit)
    {
        E->Push(unit->GetPowerType());
        return 1;
    }

    /**
     * Returns the [Unit]'s max health.
     *
     * @return uint32 maxHealth
     */
    int GetMaxHealth(Eluna* E, Unit* unit)
    {
        E->Push(unit->GetMaxHealth());
        return 1;
    }

    /**
     * Returns the [Unit]'s health percent.
     *
     * @return float healthPct
     */
    int GetHealthPct(Eluna* E, Unit* unit)
    {
        E->Push(unit->GetHealthPct());
        return 1;
    }

    /**
     * Returns the [Unit]'s gender.
     *
     * @return uint8 gender : 0 for male, 1 for female and 2 for none
     */
    int GetGender(Eluna* E, Unit* unit)
    {
        E->Push(unit->GetGender());
        return 1;
    }

    /**
     * Returns the [Unit]'s race ID.
     *
     * @return [Races] race
     */
    int GetRace(Eluna* E, Unit* unit)
    {
        E->Push(unit->GetRace());
        return 1;
    }

    /**
     * Returns the [Unit]'s class ID.
     *
     * @return [Classes] class
     */
    int GetClass(Eluna* E, Unit* unit)
    {
        E->Push(unit->GetClass());
        return 1;
    }

    /**
    * Returns the race mask
    *
    * @return uint32 racemask
    */
    int GetRaceMask(Eluna* E, Unit* unit)
    {
        E->Push(unit->GetRaceMask());
        return 1;
    }

    /**
    * Returns the class mask
    *
    * @return uint32 classmask
    */
    int GetClassMask(Eluna* E, Unit* unit)
    {
        E->Push(unit->GetClassMask());
        return 1;
    }

    /**
     * Returns the [Unit]'s creature type ID (enumerated in CreatureType.dbc).
     *
     * @table
     * @columns [CreatureType, ID]
     * @values [CREATURE_TYPE_BEAST, 1]
     * @values [CREATURE_TYPE_DRAGONKIN, 2]
     * @values [CREATURE_TYPE_DEMON, 3]
     * @values [CREATURE_TYPE_ELEMENTAL, 4]
     * @values [CREATURE_TYPE_GIANT, 5]
     * @values [CREATURE_TYPE_UNDEAD, 6]
     * @values [CREATURE_TYPE_HUMANOID, 7]
     * @values [CREATURE_TYPE_CRITTER, 8]
     * @values [CREATURE_TYPE_MECHANICAL, 9]
     * @values [CREATURE_TYPE_NOT_SPECIFIED, 10]
     * @values [CREATURE_TYPE_TOTEM, 11]
     * @values [CREATURE_TYPE_NON_COMBAT_PET, 12]
     * @values [CREATURE_TYPE_GAS_CLOUD, 13]
     *
     * @return [CreatureType] creatureType
     */
    int GetCreatureType(Eluna* E, Unit* unit)
    {
        E->Push(unit->GetCreatureType());
        return 1;
    }

    /**
     * Returns the [Unit]'s class' name in given or default locale or nil.
     *
     * @table
     * @columns [Locale, ID]
     * @values [LOCALE_enUS, 0]
     * @values [LOCALE_koKR, 1]
     * @values [LOCALE_frFR, 2]
     * @values [LOCALE_deDE, 3]
     * @values [LOCALE_zhCN, 4]
     * @values [LOCALE_zhTW, 5]
     * @values [LOCALE_esES, 6]
     * @values [LOCALE_esMX, 7]
     * @values [LOCALE_ruRU, 8]
     *
     * @param [LocaleConstant] locale = DEFAULT_LOCALE
     * @return string className : class name or nil
     */
    int GetClassAsString(Eluna* E, Unit* unit)
    {
        uint8 locale = E->CHECKVAL<uint8>(2, DEFAULT_LOCALE);
        if (locale >= TOTAL_LOCALES)
            return luaL_argerror(E->L, 2, "valid LocaleConstant expected");

        const ChrClassesEntry* entry = sChrClassesStore.LookupEntry(unit->GetClass());
        if (!entry)
            return 1;

        E->Push(entry->Name[locale]);
        return 1;
    }

    /**
     * Returns the [Unit]'s race's name in given or default locale or nil.
     *
     * @table
     * @columns [Locale, ID]
     * @values [LOCALE_enUS, 0]
     * @values [LOCALE_koKR, 1]
     * @values [LOCALE_frFR, 2]
     * @values [LOCALE_deDE, 3]
     * @values [LOCALE_zhCN, 4]
     * @values [LOCALE_zhTW, 5]
     * @values [LOCALE_esES, 6]
     * @values [LOCALE_esMX, 7]
     * @values [LOCALE_ruRU, 8]
     *
     * @param [LocaleConstant] locale = DEFAULT_LOCALE : locale to return the race name in
     * @return string raceName : race name or nil
     */
    int GetRaceAsString(Eluna* E, Unit* unit)
    {
        uint8 locale = E->CHECKVAL<uint8>(2, DEFAULT_LOCALE);
        if (locale >= TOTAL_LOCALES)
            return luaL_argerror(E->L, 2, "valid LocaleConstant expected");

        const ChrRacesEntry* entry = sChrRacesStore.LookupEntry(unit->GetRace());
        if (!entry)
            return 1;

        E->Push(entry->Name[locale]);
        return 1;
    }

    /**
     * Returns the [Unit]'s faction ID.
     *
     * @return uint32 faction
     */
    int GetFaction(Eluna* E, Unit* unit)
    {
        E->Push(unit->GetFaction());
        return 1;
    }

    /**
     * Returns the [Aura] of the given spell on the [Unit], or nil if not found.
     * Optionally filters by caster, item caster, and required effect mask.
     *
     * @param uint32 spellId : the spell ID to look up
     * @param ObjectGuid caster = ObjectGuid::Empty : the GUID of the caster to filter by, or empty for any caster
     * @param ObjectGuid itemCaster = ObjectGuid::Empty : the GUID of the item caster to filter by, or empty for any
     * @param uint8 reqEffMask = 0 : bitmask of effects that must be present, or 0 for any
     * @return [Aura] aura : the aura object or nil
     */
    int GetAura(Eluna* E, Unit* unit)
    {
        uint32 spellId = E->CHECKVAL<uint32>(2);
        ObjectGuid caster = E->CHECKVAL<ObjectGuid>(3, ObjectGuid::Empty);
        ObjectGuid itemCaster = E->CHECKVAL<ObjectGuid>(4, ObjectGuid::Empty);
        uint8 reqEffMask = E->CHECKVAL<uint8>(5, 0);
        E->Push(unit->GetAura(spellId, caster, itemCaster, reqEffMask));
        return 1;
    }

    /**
     * Returns the owned [Aura] of the given spell on the [Unit], or nil if not found.
     * Similar to GetAura but searches owned auras and optionally excludes a specific [Aura].
     *
     * @param uint32 spellId : the spell ID to look up
     * @param ObjectGuid caster = ObjectGuid::Empty : the GUID of the caster to filter by, or empty for any caster
     * @param ObjectGuid itemCaster = ObjectGuid::Empty : the GUID of the item caster to filter by, or empty for any
     * @param uint8 reqEffMask = 0 : bitmask of effects that must be present, or 0 for any
     * @param [Aura] exceptAura = nil : an [Aura] to exclude from the search, or nil for none
     * @return [Aura] aura : the aura object or nil
     */
    int GetOwnedAura(Eluna* E, Unit* unit)
    {
        uint32 spellId = E->CHECKVAL<uint32>(2);
        ObjectGuid caster = E->CHECKVAL<ObjectGuid>(3, ObjectGuid::Empty);
        ObjectGuid itemCaster = E->CHECKVAL<ObjectGuid>(4, ObjectGuid::Empty);
        uint8 reqEffMask = E->CHECKVAL<uint8>(5, 0);
        Aura* exceptAura = E->CHECKOBJ<Aura>(6, false);
        E->Push(unit->GetOwnedAura(spellId, caster, itemCaster, reqEffMask, exceptAura));
        return 1;
    }

    /**
     * Returns a table containing friendly [Unit]'s within given range of the [Unit].
     *
     * @param float range = 533.333 : search radius
     * @return table friendyUnits : table filled with friendly units
     */
    int GetFriendlyUnitsInRange(Eluna* E, Unit* unit)
    {
        float range = E->CHECKVAL<float>(2, SIZE_OF_GRIDS);

        std::list<Unit*> list;
        Trinity::AnyFriendlyUnitInObjectRangeCheck checker(unit, unit, range);
        Trinity::UnitListSearcher<Trinity::AnyFriendlyUnitInObjectRangeCheck> searcher(unit, list, checker);
        Cell::VisitAllObjects(unit, searcher, range);

        ElunaUtil::ObjectGUIDCheck guidCheck(unit->GET_GUID());
        list.remove_if(guidCheck);

        lua_createtable(E->L, list.size(), 0);
        int tbl = lua_gettop(E->L);
        uint32 i = 0;

        for (std::list<Unit*>::const_iterator it = list.begin(); it != list.end(); ++it)
        {
            E->Push(*it);
            lua_rawseti(E->L, tbl, ++i);
        }

        lua_settop(E->L, tbl);
        return 1;
    }

    /**
     * Returns a table containing unfriendly [Unit]'s within given range of the [Unit].
     *
     * @param float range = 533.333 : search radius
     * @return table unfriendyUnits : table filled with unfriendly units
     */
    int GetUnfriendlyUnitsInRange(Eluna* E, Unit* unit)
    {
        float range = E->CHECKVAL<float>(2, SIZE_OF_GRIDS);

        std::list<Unit*> list;
        Trinity::AnyUnfriendlyUnitInObjectRangeCheck checker(unit, unit, range);
        Trinity::UnitListSearcher<Trinity::AnyUnfriendlyUnitInObjectRangeCheck> searcher(unit, list, checker);
        Cell::VisitAllObjects(unit, searcher, range);

        ElunaUtil::ObjectGUIDCheck guidCheck(unit->GET_GUID());
        list.remove_if(guidCheck);

        lua_createtable(E->L, list.size(), 0);
        int tbl = lua_gettop(E->L);
        uint32 i = 0;

        for (std::list<Unit*>::const_iterator it = list.begin(); it != list.end(); ++it)
        {
            E->Push(*it);
            lua_rawseti(E->L, tbl, ++i);
        }

        lua_settop(E->L, tbl);
        return 1;
    }

    /**
     * Returns [Unit]'s [Vehicle] methods
     *
     * @return [Vehicle] vehicle
     */
    int GetVehicleKit(Eluna* E, Unit* unit)
    {
        E->Push(unit->GetVehicleKit());
        return 1;
    }

    /**
     * Returns [Unit]'s [Vehicle] object
     *
     * @return [Vehicle] vehicle
     */
    int GetVehicle(Eluna* E, Unit* unit)
    {
        E->Push(unit->GetVehicle());
        return 1;
    }

    /**
     * Returns the Critter Guid
     *
     * @return ObjectGuid critterGuid
     */
    int GetCritterGUID(Eluna* E, Unit* unit)
    {
        E->Push(unit->GetCritterGUID());
        return 1;
    }

    /**
     * Returns the [Unit]'s speed of given [UnitMoveType].
     *
     * @table
     * @columns [UnitMoveType, ID]
     * @values [MOVE_WALK, 0]
     * @values [MOVE_RUN, 1]
     * @values [MOVE_RUN_BACK, 2]
     * @values [MOVE_SWIM, 3]
     * @values [MOVE_SWIM_BACK, 4]
     * @values [MOVE_TURN_RATE, 5]
     * @values [MOVE_FLIGHT, 6]
     * @values [MOVE_FLIGHT_BACK, 7]
     * @values [MOVE_PITCH_RATE, 8]
     *
     * @param [UnitMoveType] type
     * @return float speed
     */
    int GetSpeed(Eluna* E, Unit* unit)
    {
        uint32 type = E->CHECKVAL<uint32>(2);
        if (type >= MAX_MOVE_TYPE)
            return luaL_argerror(E->L, 2, "valid UnitMoveType expected");

        E->Push(unit->GetSpeed((UnitMoveType)type));
        return 1;
    }

    /**
     * Returns the current movement type for this [Unit].
     *
     * @table
     * @columns [MovementGeneratorType, ID, Comment]
     * @values [IDLE_MOTION_TYPE, 0,  ""]
     * @values [RANDOM_MOTION_TYPE, 1,  ""]
     * @values [WAYPOINT_MOTION_TYPE, 2,  ""]
     * @values [MAX_DB_MOTION_TYPE, 3,  ""]
     * @values [ANIMAL_RANDOM_MOTION_TYPE, 3,  "TC"]
     * @values [CONFUSED_MOTION_TYPE, 4,  ""]
     * @values [CHASE_MOTION_TYPE, 5,  ""]
     * @values [HOME_MOTION_TYPE, 6,  ""]
     * @values [FLIGHT_MOTION_TYPE, 7,  ""]
     * @values [POINT_MOTION_TYPE, 8,  ""]
     * @values [FLEEING_MOTION_TYPE, 9,  ""]
     * @values [DISTRACT_MOTION_TYPE, 10, ""]
     * @values [ASSISTANCE_MOTION_TYPE, 11, ""]
     * @values [ASSISTANCE_DISTRACT_MOTION_TYPE, 12, ""]
     * @values [TIMED_FLEEING_MOTION_TYPE, 13, ""]
     * @values [FOLLOW_MOTION_TYPE, 14, ""]
     * @values [EFFECT_MOTION_TYPE, 15, "mangos"]
     * @values [ROTATE_MOTION_TYPE, 15, "TC"]
     * @values [EFFECT_MOTION_TYPE, 16, "TC"]
     * @values [NULL_MOTION_TYPE, 17, "TC"]
     *
     * @return [MovementGeneratorType] movementType
     */
    int GetMovementType(Eluna* E, Unit* unit)
    {
        E->Push(unit->GetMotionMaster()->GetCurrentMovementGeneratorType());
        return 1;
    }

    /**
     * Sets the [Unit]'s owner GUID to given GUID.
     *
     * @param ObjectGuid guid : new owner guid
     */
    int SetOwnerGUID(Eluna* E, Unit* unit)
    {
        ObjectGuid guid = E->CHECKVAL<ObjectGuid>(2);

        unit->SetOwnerGUID(guid);
        return 0;
    }

    /**
     * Sets the [Unit]'s PvP on or off.
     *
     * @param bool apply = true : true if set on, false if off
     */
    int SetPvP(Eluna* E, Unit* unit)
    {
        bool apply = E->CHECKVAL<bool>(2, true);

        unit->SetPvP(apply);
        return 0;
    }

    /**
     * Sets the [Unit]'s sheath state.
     *
     * @table
     * @columns [SheathState, ID, Comment]
     * @values [SHEATH_STATE_UNARMED, 0, "non prepared weapon"]
     * @values [SHEATH_STATE_MELEE, 1, "prepared melee weapon"]
     * @values [SHEATH_STATE_RANGED, 2, "prepared ranged weapon"]
     *
     * @param [SheathState] sheathState : valid SheathState
     */
    int SetSheath(Eluna* E, Unit* unit)
    {
        uint32 sheathed = E->CHECKVAL<uint32>(2);
        if (sheathed >= MAX_SHEATH_STATE)
            return luaL_argerror(E->L, 2, "valid SheathState expected");

        unit->SetSheath((SheathState)sheathed);
        return 0;
    }

    /**
     * Sets the [Unit]'s name internally.
     *
     * @param string name : new name
     */
    int SetName(Eluna* E, Unit* unit)
    {
        const char* name = E->CHECKVAL<const char*>(2);
        if (std::string(name).length() > 0)
            unit->SetName(name);
        return 0;
    }

    /**
     * Sets the [Unit]'s speed of given [UnitMoveType] to given rate.
     * If forced, packets sent to clients forcing the visual change.
     *
     * @table
     * @columns [UnitMoveType, ID]
     * @values [MOVE_WALK, 0]
     * @values [MOVE_RUN, 1]
     * @values [MOVE_RUN_BACK, 2]
     * @values [MOVE_SWIM, 3]
     * @values [MOVE_SWIM_BACK, 4]
     * @values [MOVE_TURN_RATE, 5]
     * @values [MOVE_FLIGHT, 6]
     * @values [MOVE_FLIGHT_BACK, 7]
     * @values [MOVE_PITCH_RATE, 8]
     *
     * @param [UnitMoveType] type
     * @param float rate
     * @param bool forced = false
     */
    int SetSpeed(Eluna* E, Unit* unit)
    {
        uint32 type = E->CHECKVAL<uint32>(2);
        float rate = E->CHECKVAL<float>(3);
        bool forced = E->CHECKVAL<bool>(4, false);
        (void)forced; // ensure that the variable is referenced in order to pass compiler checks
        if (type >= MAX_MOVE_TYPE)
            return luaL_argerror(E->L, 2, "valid UnitMoveType expected");

        unit->SetSpeedRate((UnitMoveType)type, rate);
        return 0;
    }

    /**
     * Sets the [Unit]'s faction.
     *
     * @param uint32 faction : new faction ID
     */
    int SetFaction(Eluna* E, Unit* unit)
    {
        uint32 factionId = E->CHECKVAL<uint32>(2);

        unit->SetFaction(factionId);
        return 0;
    }

    /**
     * Sets the [Unit]'s level.
     *
     * @param uint8 level : new level
     */
    int SetLevel(Eluna* E, Unit* unit)
    {
        uint8 newlevel = E->CHECKVAL<uint8>(2);

        if (newlevel < 1)
            return luaL_argerror(E->L, 2, "level cannot be below 1");

        if (Player* player = unit->ToPlayer())
        {
            player->GiveLevel(newlevel);
            player->InitTalentForLevel();
            player->SetUInt32Value(PLAYER_XP, 0);
        }
        else
            unit->SetLevel(newlevel);

        return 0;
    }

    /**
     * Sets the [Unit]'s health.
     *
     * @param uint32 health : new health
     */
    int SetHealth(Eluna* E, Unit* unit)
    {
        uint32 amt = E->CHECKVAL<uint32>(2);
        unit->SetHealth(amt);
        return 0;
    }

    /**
     * Sets the [Unit]'s max health.
     *
     * @param uint32 maxHealth : new max health
     */
    int SetMaxHealth(Eluna* E, Unit* unit)
    {
        uint32 amt = E->CHECKVAL<uint32>(2);
        unit->SetMaxHealth(amt);
        return 0;
    }

    /**
     * Sets the [Unit]'s power amount for the given power type.
     *
     * @table
     * @columns [Powers, ID, Comment]
     * @values [POWER_MANA, 0, ""]
     * @values [POWER_RAGE, 1, ""]
     * @values [POWER_FOCUS, 2, ""]
     * @values [POWER_ENERGY, 3, ""]
     * @values [POWER_HAPPINESS, 4, ""]
     * @values [POWER_RUNE, 5, ""]
     * @values [POWER_RUNIC_POWER, 6, ""]
     * @values [MAX_POWERS, 7, ""]
     * @values [POWER_ALL, 127, "default for class?"]
     * @values [POWER_HEALTH, 0xFFFFFFFE, "-2 as signed value"]
     *
     * @param uint32 amount : new power amount
     * @param int type = -1 : a valid power type from [Powers] or -1 for the [Unit]'s current power type
     */
    int SetPower(Eluna* E, Unit* unit)
    {
        uint32 amt = E->CHECKVAL<uint32>(2);
        int type = E->CHECKVAL<int>(3, -1);
        Powers power = PowerSelectorHelper(E, unit, type);

        unit->SetPower(power, amt);
        return 0;
    }

    /**
     * modifies the [Unit]'s power amount for the given power type.
     *
     * @table
     * @columns [Powers, ID, Comment]
     * @values [POWER_MANA, 0, ""]
     * @values [POWER_RAGE, 1, ""]
     * @values [POWER_FOCUS, 2, ""]
     * @values [POWER_ENERGY, 3, ""]
     * @values [POWER_HAPPINESS, 4, ""]
     * @values [POWER_RUNE, 5, ""]
     * @values [POWER_RUNIC_POWER, 6, ""]
     * @values [MAX_POWERS, 7, ""]
     * @values [POWER_ALL, 127, "default for class?"]
     * @values [POWER_HEALTH, 0xFFFFFFFE, "-2 as signed value"]
     *
     * @param int32 amount : amount to modify
     * @param int type = -1 : a valid power type from [Powers] or -1 for the [Unit]'s current power type
     */
    int ModifyPower(Eluna* E, Unit* unit)
    {
        int32 amt = E->CHECKVAL<int32>(2);
        int type = E->CHECKVAL<int>(3, -1);
        Powers power = PowerSelectorHelper(E, unit, type);

        unit->ModifyPower(power, amt);
        return 0;
    }

    /**
     * Sets the [Unit]'s max power amount for the given power type.
     *
     * @table
     * @columns [Powers, ID, Comment]
     * @values [POWER_MANA, 0, ""]
     * @values [POWER_RAGE, 1, ""]
     * @values [POWER_FOCUS, 2, ""]
     * @values [POWER_ENERGY, 3, ""]
     * @values [POWER_HAPPINESS, 4, ""]
     * @values [POWER_RUNE, 5, ""]
     * @values [POWER_RUNIC_POWER, 6, ""]
     * @values [MAX_POWERS, 7, ""]
     * @values [POWER_ALL, 127, "default for class?"]
     * @values [POWER_HEALTH, 0xFFFFFFFE, "-2 as signed value"]
     *
     * @param int type = -1 : a valid power type from [Powers] or -1 for the [Unit]'s current power type
     * @param uint32 maxPower : new max power amount
     */
    int SetMaxPower(Eluna* E, Unit* unit)
    {
        int type = E->CHECKVAL<int>(2, -1);
        uint32 amt = E->CHECKVAL<uint32>(3);
        Powers power = PowerSelectorHelper(E, unit, type);

        unit->SetMaxPower(power, amt);
        return 0;
    }

    /**
     * Sets the [Unit]'s power type.
     *
     * @table
     * @columns [Powers, ID, Comment]
     * @values [POWER_MANA, 0, ""]
     * @values [POWER_RAGE, 1, ""]
     * @values [POWER_FOCUS, 2, ""]
     * @values [POWER_ENERGY, 3, ""]
     * @values [POWER_HAPPINESS, 4, ""]
     * @values [POWER_RUNE, 5, ""]
     * @values [POWER_RUNIC_POWER, 6, ""]
     * @values [MAX_POWERS, 7, ""]
     * @values [POWER_ALL, 127, "default for class?"]
     * @values [POWER_HEALTH, 0xFFFFFFFE, "-2 as signed value"]
     *
     * @param [Powers] type : a valid power type
     */
    int SetPowerType(Eluna* E, Unit* unit)
    {
        uint32 type = E->CHECKVAL<uint32>(2);
        if (type >= int(MAX_POWERS))
            return luaL_argerror(E->L, 2, "valid Powers expected");

        unit->SetPowerType((Powers)type);
        return 0;
    }

    /**
     * Sets the [Unit]'s modelID.
     *
     * @param uint32 displayId
     */
    int SetDisplayId(Eluna* E, Unit* unit)
    {
        uint32 model = E->CHECKVAL<uint32>(2);
        unit->SetDisplayId(model);
        return 0;
    }

    /**
     * Sets the [Unit]'s native/default modelID.
     *
     * @param uint32 displayId
     */
    int SetNativeDisplayId(Eluna* E, Unit* unit)
    {
        uint32 model = E->CHECKVAL<uint32>(2);
        unit->SetNativeDisplayId(model);
        return 0;
    }

    /**
     * Sets the [Unit]'s facing/orientation.
     *
     * @param uint32 orientation
     */
    int SetFacing(Eluna* E, Unit* unit)
    {
        float o = E->CHECKVAL<float>(2);
        unit->SetFacingTo(o);
        return 0;
    }

    /**
     * Sets the [Unit] to face the given [WorldObject]'s direction.
     *
     * @param [WorldObject] target
     */
    int SetFacingToObject(Eluna* E, Unit* unit)
    {
        WorldObject* obj = E->CHECKOBJ<WorldObject>(2);
        unit->SetFacingToObject(obj);
        return 0;
    }

    /**
     * Sets creator GUID
     *
     * @param ObjectGuid guid
     */
    int SetCreatorGUID(Eluna* E, Unit* unit)
    {
        ObjectGuid guid = E->CHECKVAL<ObjectGuid>(2);

        unit->SetCreatorGUID(guid);
        return 0;
    }

    /**
     * Sets pet GUID
     *
     * @param ObjectGuid guid
     */
    int SetPetGUID(Eluna* E, Unit* unit)
    {
        ObjectGuid guid = E->CHECKVAL<ObjectGuid>(2);

        unit->SetPetGUID(guid);
        return 0;
    }

    /**
     * Toggles (Sets) [Unit]'s water walking
     *
     * @param bool enable = true
     */
    int SetWaterWalk(Eluna* E, Unit* unit)
    {
        bool enable = E->CHECKVAL<bool>(2, true);

        unit->SetWaterWalking(enable);
        return 0;
    }

    /**
     * Sets the [Unit]'s stand state
     *
     * @param uint8 state : stand state
     */
    int SetStandState(Eluna* E, Unit* unit)
    {
        uint8 state = E->CHECKVAL<uint8>(2);

        unit->SetStandState(UnitStandStateType(state));
        return 0;
    }

    /**
     * Sets the [Unit] in combat with the `enemy` [Unit].
     *
     * @param [Unit] enemy : the [Unit] to start combat with
     */
    int SetInCombatWith(Eluna* E, Unit* unit)
    {
        Unit* enemy = E->CHECKOBJ<Unit>(2);
        unit->SetInCombatWith(enemy);
        return 0;
    }

    /**
     * Sets the [Unit]'s FFA flag on or off.
     *
     * @param bool apply = true
     */
    int SetFFA(Eluna* E, Unit* unit)
    {
        bool apply = E->CHECKVAL<bool>(2, true);

        if (apply)
        {
            unit->SetByteFlag(UNIT_FIELD_BYTES_2, 1, UNIT_BYTE2_FLAG_FFA_PVP);
            for (Unit::ControlList::iterator itr = unit->m_Controlled.begin(); itr != unit->m_Controlled.end(); ++itr)
                (*itr)->SetByteValue(UNIT_FIELD_BYTES_2, 1, UNIT_BYTE2_FLAG_FFA_PVP);
        }
        else
        {
            unit->RemoveByteFlag(UNIT_FIELD_BYTES_2, 1, UNIT_BYTE2_FLAG_FFA_PVP);
            for (Unit::ControlList::iterator itr = unit->m_Controlled.begin(); itr != unit->m_Controlled.end(); ++itr)
                (*itr)->RemoveByteFlag(UNIT_FIELD_BYTES_2, 1, UNIT_BYTE2_FLAG_FFA_PVP);
        }

        return 0;
    }

    /**
     * Sets the [Unit]'s sanctuary flag on or off.
     *
     * @param bool apply = true
     */
    int SetSanctuary(Eluna* E, Unit* unit)
    {
        bool apply = E->CHECKVAL<bool>(2, true);

        if (apply)
        {
            unit->SetByteFlag(UNIT_FIELD_BYTES_2, 1, UNIT_BYTE2_FLAG_SANCTUARY);
            unit->CombatStop();
            unit->CombatStopWithPets();
        }
        else
            unit->RemoveByteFlag(UNIT_FIELD_BYTES_2, 1, UNIT_BYTE2_FLAG_SANCTUARY);

        return 0;
    }

    /**
     * Sets the [Unit]s critter GUID field.
     *
     * @param [ObjectGuid] guid
     */
    int SetCritterGUID(Eluna* E, Unit* unit)
    {
        ObjectGuid guid = E->CHECKVAL<ObjectGuid>(2);
        unit->SetCritterGUID(guid);
        return 0;
    }

    /**
     * Sets whether or not the [Unit] is stunned.
     *
     * @param bool stunned = true
     */
    int SetStunned(Eluna* E, Unit* unit)
    {
        bool apply = E->CHECKVAL<bool>(2, true);
        unit->SetControlled(apply, UNIT_STATE_STUNNED);
        return 0;
    }

    /**
     * Roots the [Unit] to the ground, if 'false' specified, unroots the [Unit].
     *
     * @param bool apply = true
     */
    int SetRooted(Eluna* E, Unit* unit)
    {
        bool apply = E->CHECKVAL<bool>(2, true);

        unit->SetControlled(apply, UNIT_STATE_ROOT);
        return 0;
    }

    /**
     * Confuses the [Unit], if 'false' specified, the [Unit] is no longer confused.
     *
     * @param bool apply = true
     */
    int SetConfused(Eluna* E, Unit* unit)
    {
        bool apply = E->CHECKVAL<bool>(2, true);

        unit->SetControlled(apply, UNIT_STATE_CONFUSED);
        return 0;
    }

    /**
     * Fears the [Unit], if 'false' specified, the [Unit] is no longer feared.
     *
     * @param bool apply = true
     */
    int SetFeared(Eluna* E, Unit* unit)
    {
        bool apply = E->CHECKVAL<bool>(2, true);

        unit->SetControlled(apply, UNIT_STATE_FLEEING);
        return 0;
    }

    /**
     * Sets whether or not the [Unit] can fly.
     *
     * @param bool canFly = true
     */
    int SetCanFly(Eluna* E, Unit* unit)
    {
        bool apply = E->CHECKVAL<bool>(2, true);

        unit->SetCanFly(apply);
        return 0;
    }

    /**
     * Sets whether or not the [Unit] is visible.
     *
     * @param bool visible = true
     */
    int SetVisible(Eluna* E, Unit* unit)
    {
        bool x = E->CHECKVAL<bool>(2, true);

        unit->SetVisible(x);
        return 0;
    }

    /**
     * Mounts the [Unit] on the given displayID/modelID.
     *
     * @param uint32 displayId
     */
    int Mount(Eluna* E, Unit* unit)
    {
        uint32 displayId = E->CHECKVAL<uint32>(2);

        unit->Mount(displayId);
        return 0;
    }

    /**
     * Dismounts the [Unit].
     */
    int Dismount(Eluna* /*E*/, Unit* unit)
    {
        if (unit->IsMounted())
        {
            unit->Dismount();
            unit->RemoveAurasByType(SPELL_AURA_MOUNTED);
        }

        return 0;
    }

    /**
     * Makes the [Unit] perform the given emote.
     *
     * @param uint32 emoteId
     */
    int PerformEmote(Eluna* E, Unit* unit)
    {
        Emote emote = static_cast<Emote>(E->CHECKVAL<uint32>(2));
        unit->HandleEmoteCommand(emote);
        return 0;
    }

    /**
     * Makes the [Unit] perform the given emote continuously.
     *
     * @param uint32 emoteId
     */
    int EmoteState(Eluna* E, Unit* unit)
    {
        uint32 emoteId = E->CHECKVAL<uint32>(2);

        unit->SetUInt32Value(UNIT_NPC_EMOTESTATE, emoteId);
        return 0;
    }

    /**
     * Returns calculated percentage from Health
     *
     * @return int32 percentage
     */
    int CountPctFromCurHealth(Eluna* E, Unit* unit)
    {
        E->Push(unit->CountPctFromCurHealth(E->CHECKVAL<int32>(2)));
        return 1;
    }

    /**
     * Returns calculated percentage from Max Health
     *
     * @return int32 percentage
     */
    int CountPctFromMaxHealth(Eluna* E, Unit* unit)
    {
        E->Push(unit->CountPctFromMaxHealth(E->CHECKVAL<int32>(2)));
        return 1;
    }

    /**
     * Sends chat message to [Player]
     *
     * @param uint8 type : chat, whisper, etc
     * @param uint32 lang : language to speak
     * @param string msg
     * @param [Player] target
     */
    int SendChatMessageToPlayer(Eluna* E, Unit* unit)
    {
        uint8 type = E->CHECKVAL<uint8>(2);
        uint32 lang = E->CHECKVAL<uint32>(3);
        std::string msg = E->CHECKVAL<std::string>(4);
        Player* target = E->CHECKOBJ<Player>(5);

        if (type >= MAX_CHAT_MSG_TYPE)
            return luaL_argerror(E->L, 2, "valid ChatMsg expected");
        if (lang >= LANGUAGES_COUNT)
            return luaL_argerror(E->L, 3, "valid Language expected");

        WorldPacket data;
        ChatHandler::BuildChatPacket(data, ChatMsg(type), Language(lang), unit, target, msg);

        target->GetSession()->SendPacket(&data);
        return 0;
    }

    /**
     * Stops the [Unit]'s movement
     */
    int MoveStop(Eluna* /*E*/, Unit* unit)
    {
        unit->StopMoving();
        return 0;
    }

    /**
     * The [Unit]'s movement expires and clears movement
     *
     * @param bool reset = true : cleans movement
     */
    int MoveExpire(Eluna* /*E*/, Unit* unit)
    {
        unit->GetMotionMaster()->Clear();
        return 0;
    }

    /**
     * Clears the [Unit]'s movement
     *
     * @param bool reset = true : clean movement
     */
    int MoveClear(Eluna* /*E*/, Unit* unit)
    {
        unit->GetMotionMaster()->Clear();
        return 0;
    }

    /**
     * The [Unit] will be idle
     */
    int MoveIdle(Eluna* /*E*/, Unit* unit)
    {
        unit->GetMotionMaster()->MoveIdle();
        return 0;
    }

    /**
     * The [Unit] will move at random
     *
     * @param float radius : limit on how far the [Unit] will move at random
     */
    int MoveRandom(Eluna* E, Unit* unit)
    {
        float radius = E->CHECKVAL<float>(2);
        float x, y, z;
        unit->GetPosition(x, y, z);
        unit->GetMotionMaster()->MoveRandom(radius);
        return 0;
    }

    /**
     * The [Unit] will move to its set home location
     */
    int MoveHome(Eluna* /*E*/, Unit* unit)
    {
        unit->GetMotionMaster()->MoveTargetedHome();
        return 0;
    }

    /**
     * The [Unit] will follow the target
     *
     * @param [Unit] target : target to follow
     * @param float dist = 0 : distance to start following
     * @param float angle = 0
     */
    int MoveFollow(Eluna* E, Unit* unit)
    {
        Unit* target = E->CHECKOBJ<Unit>(2);
        float dist = E->CHECKVAL<float>(3, 0.0f);
        float angle = E->CHECKVAL<float>(4, 0.0f);
        unit->GetMotionMaster()->MoveFollow(target, dist, angle);
        return 0;
    }

    /**
     * The [Unit] will chase the target
     *
     * @param [Unit] target : target to chase
     * @param float dist = 0 : distance start chasing
     * @param float angle = 0
     */
    int MoveChase(Eluna* E, Unit* unit)
    {
        Unit* target = E->CHECKOBJ<Unit>(2);
        float dist = E->CHECKVAL<float>(3, 0.0f);
        float angle = E->CHECKVAL<float>(4, 0.0f);
        unit->GetMotionMaster()->MoveChase(target, dist, angle);
        return 0;
    }

    /**
     * The [Unit] will move confused
     */
    int MoveConfused(Eluna* /*E*/, Unit* unit)
    {
        unit->GetMotionMaster()->MoveConfused();
        return 0;
    }

    /**
     * The [Unit] will flee
     *
     * @param [Unit] target
     * @param uint32 time = 0 : flee delay
     */
    int MoveFleeing(Eluna* E, Unit* unit)
    {
        Unit* target = E->CHECKOBJ<Unit>(2);
        uint32 time = E->CHECKVAL<uint32>(3, 0);
        unit->GetMotionMaster()->MoveFleeing(target, time);
        return 0;
    }

    /**
     * The [Unit] will move to the coordinates
     *
     * @param uint32 id : unique waypoint Id
     * @param float x
     * @param float y
     * @param float z
     * @param bool genPath = true : if true, generates path
     */
    int MoveTo(Eluna* E, Unit* unit)
    {
        uint32 id = E->CHECKVAL<uint32>(2);
        float x = E->CHECKVAL<float>(3);
        float y = E->CHECKVAL<float>(4);
        float z = E->CHECKVAL<float>(5);
        bool genPath = E->CHECKVAL<bool>(6, true);

        unit->GetMotionMaster()->MovePoint(id, x, y, z, genPath);
        return 0;
    }

    /**
     * Makes the [Unit] jump to the coordinates
     *
     * @param float x
     * @param float y
     * @param float z
     * @param float zSpeed : start velocity
     * @param float maxHeight : maximum height
     * @param uint32 id = 0 : unique movement Id
     */
    int MoveJump(Eluna* E, Unit* unit)
    {
        float x = E->CHECKVAL<float>(2);
        float y = E->CHECKVAL<float>(3);
        float z = E->CHECKVAL<float>(4);
        float zSpeed = E->CHECKVAL<float>(5);
        float maxHeight = E->CHECKVAL<float>(6);
        uint32 id = E->CHECKVAL<uint32>(7, 0);

        Position pos(x, y, z);

        unit->GetMotionMaster()->MoveJump(pos, zSpeed, maxHeight, id);
        return 0;
    }

    /**
     * The [Unit] will whisper the message to a [Player]
     *
     * @param string msg : message for the [Unit] to emote
     * @param uint32 lang : language for the [Unit] to speak
     * @param [Player] receiver : specific [Unit] to receive the message
     * @param bool bossWhisper = false : is a boss whisper
     */
    int SendUnitWhisper(Eluna* E, Unit* unit)
    {
        const char* msg = E->CHECKVAL<const char*>(2);
        uint32 lang = E->CHECKVAL<uint32>(3);
        (void)lang; // ensure that the variable is referenced in order to pass compiler checks
        Player* receiver = E->CHECKOBJ<Player>(4);
        bool bossWhisper = E->CHECKVAL<bool>(5, false);

        if (std::string(msg).length() > 0)
            unit->Whisper(msg, (Language)lang, receiver, bossWhisper);

        return 0;
    }

    /**
     * The [Unit] will emote the message
     *
     * @param string msg : message for the [Unit] to emote
     * @param [Unit] receiver = nil : specific [Unit] to receive the message
     * @param bool bossEmote = false : is a boss emote
     */
    int SendUnitEmote(Eluna* E, Unit* unit)
    {
        const char* msg = E->CHECKVAL<const char*>(2);
        Unit* receiver = E->CHECKOBJ<Unit>(3, false);
        bool bossEmote = E->CHECKVAL<bool>(4, false);

        if (std::string(msg).length() > 0)
            unit->TextEmote(msg, receiver, bossEmote);

        return 0;
    }

    /**
     * The [Unit] will say the message
     *
     * @param string msg : message for the [Unit] to say
     * @param uint32 language : language for the [Unit] to speak
     */
    int SendUnitSay(Eluna* E, Unit* unit)
    {
        const char* msg = E->CHECKVAL<const char*>(2);
        uint32 language = E->CHECKVAL<uint32>(3);

        if (std::string(msg).length() > 0)
            unit->Say(msg, (Language)language, unit);

        return 0;
    }

    /**
     * The [Unit] will yell the message
     *
     * @param string msg : message for the [Unit] to yell
     * @param uint32 language : language for the [Unit] to speak
     */
    int SendUnitYell(Eluna* E, Unit* unit)
    {
        const char* msg = E->CHECKVAL<const char*>(2);
        uint32 language = E->CHECKVAL<uint32>(3);

        if (std::string(msg).length() > 0)
            unit->Yell(msg, (Language)language, unit);

        return 0;
    }

    /**
     * Unmorphs the [Unit] setting it's display ID back to the native display ID.
     */
    int DeMorph(Eluna* /*E*/, Unit* unit)
    {
        unit->DeMorph();
        return 0;
    }

    /**
     * Makes the [Unit] cast the spell on the target.
     *
     * @param [Unit] target = nil : can be self or another unit
     * @param uint32 spell : entry of a spell
     * @param bool triggered = false : if true the spell is instant and has no cost
     */
    int CastSpell(Eluna* E, Unit* unit)
    {
        Unit* target = E->CHECKOBJ<Unit>(2, false);
        uint32 spell = E->CHECKVAL<uint32>(3);
        bool triggered = E->CHECKVAL<bool>(4, false);

        SpellInfo const* spellEntry = sSpellMgr->GetSpellInfo(spell);
        if (!spellEntry)
            return 0;

        unit->CastSpell(target, spell, triggered);
        return 0;
    }

    /**
     * Casts the [Spell] at target [Unit] with custom basepoints or casters.
     * See also [Unit:CastSpell].
     *
     * @param [Unit] target = nil
     * @param uint32 spell
     * @param bool triggered = false
     * @param int32 bp0 = nil : custom basepoints for [Spell] effect 1. If nil, no change is made
     * @param int32 bp1 = nil : custom basepoints for [Spell] effect 2. If nil, no change is made
     * @param int32 bp2 = nil : custom basepoints for [Spell] effect 3. If nil, no change is made
     * @param [Item] castItem = nil
     * @param ObjectGuid originalCaster = ObjectGuid()
     */
    int CastCustomSpell(Eluna* E, Unit* unit)
    {
        Unit* target = E->CHECKOBJ<Unit>(2, false);
        uint32 spell = E->CHECKVAL<uint32>(3);
        bool triggered = E->CHECKVAL<bool>(4, false);
        bool has_bp0 = !lua_isnoneornil(E->L, 5);
        int32 bp0 = E->CHECKVAL<int32>(5, 0);
        bool has_bp1 = !lua_isnoneornil(E->L, 6);
        int32 bp1 = E->CHECKVAL<int32>(6, 0);
        bool has_bp2 = !lua_isnoneornil(E->L, 7);
        int32 bp2 = E->CHECKVAL<int32>(7, 0);
        Item* castItem = E->CHECKOBJ<Item>(8, false);
        ObjectGuid originalCaster = E->CHECKVAL<ObjectGuid>(9, ObjectGuid());

        CastSpellExtraArgs args;
        if (has_bp0)
            args.AddSpellMod(SPELLVALUE_BASE_POINT0, bp0);
        if (has_bp1)
            args.AddSpellMod(SPELLVALUE_BASE_POINT1, bp1);
        if (has_bp2)
            args.AddSpellMod(SPELLVALUE_BASE_POINT2, bp2);
        if (triggered)
            args.TriggerFlags = TRIGGERED_FULL_MASK;
        if (castItem)
            args.SetCastItem(castItem);
        if (!originalCaster.IsEmpty())
            args.SetOriginalCaster(originalCaster);

        unit->CastSpell(target, spell, args);
        return 0;
    }

    /**
     * Makes the [Unit] cast the spell to the given coordinates, used for area effect spells.
     *
     * @param float x
     * @param float y
     * @param float z
     * @param uint32 spell : entry of a spell
     * @param bool triggered = true : if true the spell is instant and has no cost
     */
    int CastSpellAoF(Eluna* E, Unit* unit)
    {
        float _x = E->CHECKVAL<float>(2);
        float _y = E->CHECKVAL<float>(3);
        float _z = E->CHECKVAL<float>(4);
        uint32 spell = E->CHECKVAL<uint32>(5);
        bool triggered = E->CHECKVAL<bool>(6, true);

        CastSpellExtraArgs args;
        if (triggered)
            args.TriggerFlags = TRIGGERED_FULL_MASK;

        unit->CastSpell(Position(_x, _y, _z), spell, args);
        return 0;
    }

    /**
     * Clears the [Unit]'s combat
     */
    int ClearInCombat(Eluna* /*E*/, Unit* unit)
    {
        unit->ClearInCombat();
        return 0;
    }

    /**
     * Stops the [Unit]'s current spell cast
     *
     * @param uint32 spell = 0 : entry of a spell
     */
    int StopSpellCast(Eluna* E, Unit* unit)
    {
        uint32 spellId = E->CHECKVAL<uint32>(2, 0);
        unit->CastStop(spellId);
        return 0;
    }

    /**
     * Interrupts [Unit]'s spell state, casting, etc.
     *
     * if spell is not interruptible, it will return
     *
     * @param int32 spellType : type of spell to interrupt
     * @param bool delayed = true : skips if the spell is delayed
     */
    int InterruptSpell(Eluna* E, Unit* unit)
    {
        int spellType = E->CHECKVAL<int>(2);
        bool delayed = E->CHECKVAL<bool>(3, true);
        switch (spellType)
        {
            case 0:
                spellType = CURRENT_MELEE_SPELL;
                break;
            case 1:
                spellType = CURRENT_GENERIC_SPELL;
                break;
            case 2:
                spellType = CURRENT_CHANNELED_SPELL;
                break;
            case 3:
                spellType = CURRENT_AUTOREPEAT_SPELL;
                break;
            default:
                return luaL_argerror(E->L, 2, "valid CurrentSpellTypes expected");
        }

        unit->InterruptSpell((CurrentSpellTypes)spellType, delayed);
        return 0;
    }

    /**
     * Adds the [Aura] of the given spell entry on the given target from the [Unit].
     *
     * @param uint32 spell : entry of a spell
     * @param [Unit] target : aura will be applied on the target
     * @return [Aura] aura
     */
    int AddAura(Eluna* E, Unit* unit)
    {
        uint32 spell = E->CHECKVAL<uint32>(2);
        Unit* target = E->CHECKOBJ<Unit>(3);

        SpellInfo const* spellEntry = sSpellMgr->GetSpellInfo(spell);
        if (!spellEntry)
            return 1;

        E->Push(unit->AddAura(spell, target));
        return 1;
    }

    /**
     * Removes [Aura] of the given spell entry from the [Unit].
     *
     * @param uint32 spell : entry of a spell
     */
    int RemoveAura(Eluna* E, Unit* unit)
    {
        uint32 spellId = E->CHECKVAL<uint32>(2);
        unit->RemoveAurasDueToSpell(spellId);
        return 0;
    }

    /**
     * Removes all [Aura]'s from the [Unit].
     *
     *     Note: talents and racials are also auras, use with caution
     */
    int RemoveAllAuras(Eluna* /*E*/, Unit* unit)
    {
        unit->RemoveAllAuras();
        return 0;
    }

    /**
     * Removes all positive visible [Aura]'s from the [Unit].
     */
    int RemoveArenaAuras(Eluna* /*E*/, Unit* unit)
    {
        unit->RemoveArenaAuras();
        return 0;
    }

    /**
     * Adds the given unit state for the [Unit].
     *
     * @param [UnitState] state
     */
    int AddUnitState(Eluna* E, Unit* unit)
    {
        uint32 state = E->CHECKVAL<uint32>(2);

        unit->AddUnitState(state);
        return 0;
    }

    /**
     * Removes the given unit state from the [Unit].
     *
     * @param [UnitState] state
     */
    int ClearUnitState(Eluna* E, Unit* unit)
    {
        uint32 state = E->CHECKVAL<uint32>(2);

        unit->ClearUnitState(state);
        return 0;
    }

    /**
     * Makes the [Unit] teleport to given coordinates within same map.
     *
     * @param float x
     * @param float y
     * @param float z
     * @param float o : orientation
     */
    int NearTeleport(Eluna* E, Unit* unit)
    {
        float x = E->CHECKVAL<float>(2);
        float y = E->CHECKVAL<float>(3);
        float z = E->CHECKVAL<float>(4);
        float o = E->CHECKVAL<float>(5);

        unit->NearTeleportTo(x, y, z, o);
        return 0;
    }

    /**
     * Makes the [Unit] damage the target [Unit]
     *
     * @table
     * @columns [SpellSchools, ID]
     * @values [SPELL_SCHOOL_NORMAL, 0]
     * @values [SPELL_SCHOOL_HOLY, 1]
     * @values [SPELL_SCHOOL_FIRE, 2]
     * @values [SPELL_SCHOOL_NATURE, 3]
     * @values [SPELL_SCHOOL_FROST, 4]
     * @values [SPELL_SCHOOL_SHADOW, 5]
     * @values [SPELL_SCHOOL_ARCANE, 6]
     * @values [MAX_SPELL_SCHOOL, 7]
     *
     * @param [Unit] target : [Unit] to damage
     * @param uint32 damage : amount to damage
     * @param bool durabilityloss = true : if false, the damage does not do durability damage
     * @param [SpellSchools] school = MAX_SPELL_SCHOOL : school the damage is done in or MAX_SPELL_SCHOOL for direct damage
     * @param uint32 spell = 0 : spell that inflicts the damage
     */
    int DealDamage(Eluna* E, Unit* unit)
    {
        Unit* target = E->CHECKOBJ<Unit>(2);
        uint32 damage = E->CHECKVAL<uint32>(3);
        bool durabilityloss = E->CHECKVAL<bool>(4, true);
        uint32 school = E->CHECKVAL<uint32>(5, MAX_SPELL_SCHOOL);
        uint32 spell = E->CHECKVAL<uint32>(6, 0);
        if (school > MAX_SPELL_SCHOOL)
            return luaL_argerror(E->L, 6, "valid SpellSchool expected");

        // flat melee damage without resistence/etc reduction
        if (school == MAX_SPELL_SCHOOL)
        {
            Unit::DealDamage(unit, target, damage, NULL, DIRECT_DAMAGE, SPELL_SCHOOL_MASK_NORMAL, NULL, durabilityloss);
            unit->SendAttackStateUpdate(HITINFO_AFFECTS_VICTIM, target, 1, SPELL_SCHOOL_MASK_NORMAL, damage, 0, 0, VICTIMSTATE_HIT, 0);
            return 0;
        }

        SpellSchoolMask schoolmask = SpellSchoolMask(1 << school);

        if (Unit::IsDamageReducedByArmor(schoolmask))
            damage = Unit::CalcArmorReducedDamage(unit, target, damage, NULL, BASE_ATTACK);

        // melee damage by specific school
        if (!spell)
        {
            DamageInfo dmgInfo(unit, target, damage, nullptr, schoolmask, SPELL_DIRECT_DAMAGE, BASE_ATTACK);
            unit->CalcAbsorbResist(dmgInfo);

            if (!dmgInfo.GetDamage())
                damage = 0;
            else
                damage = dmgInfo.GetDamage();

            uint32 absorb = dmgInfo.GetAbsorb();
            uint32 resist = dmgInfo.GetResist();
            unit->DealDamageMods(target, damage, &absorb);

            Unit::DealDamage(unit, target, damage, NULL, DIRECT_DAMAGE, schoolmask, NULL, false);
            unit->SendAttackStateUpdate(HITINFO_AFFECTS_VICTIM, target, 0, schoolmask, damage, absorb, resist, VICTIMSTATE_HIT, 0);
            return 0;
        }

        if (!spell)
            return 0;

        SpellInfo const* spellInfo = sSpellMgr->GetSpellInfo(spell);
        if (!spellInfo)
            return 0;

        SpellNonMeleeDamage dmgInfo(unit, target, spell, spellInfo->GetSchoolMask());
        Unit::DealDamageMods(dmgInfo.target, dmgInfo.damage, &dmgInfo.absorb);

        unit->SendSpellNonMeleeDamageLog(&dmgInfo);
        unit->DealSpellDamage(&dmgInfo, true);
        return 0;
    }

    /**
     * Makes the [Unit] heal the target [Unit] with given spell
     *
     * @param [Unit] target : [Unit] to heal
     * @param uint32 spell : spell that causes the healing
     * @param uint32 amount : amount to heal
     * @param bool critical = false : if true, heal is logged as critical
     */
    int DealHeal(Eluna* E, Unit* unit)
    {
        Unit* target = E->CHECKOBJ<Unit>(2);
        uint32 spell = E->CHECKVAL<uint32>(3);
        uint32 amount = E->CHECKVAL<uint32>(4);
        bool critical = E->CHECKVAL<bool>(5, false);

        if (const SpellInfo* info = sSpellMgr->GetSpellInfo(spell))
        {
            HealInfo healInfo(unit, target, amount, info, info->GetSchoolMask());
            unit->HealBySpell(healInfo, critical);
        }

        return 0;
    }

    /**
     * Makes the [Unit] kill the target [Unit]
     *
     * @param [Unit] target : [Unit] to kill
     * @param bool durLoss = true : when true, the target's items suffer durability loss
     */
    int Kill(Eluna* E, Unit* unit)
    {
        Unit* target = E->CHECKOBJ<Unit>(2);
        bool durLoss = E->CHECKVAL<bool>(3, true);

        Unit::Kill(unit, target, durLoss);
        return 0;
    }

    /**
     * Restores the [Unit]s display ID to default
     */
    int RestoreDisplayId(Eluna* /*E*/, Unit* unit)
    {
        unit->RestoreDisplayId();
        return 0;
    }

    /**
     * Restores the [Unit]s faction to default
     */
    int RestoreFaction(Eluna* /*E*/, Unit* unit)
    {
        unit->RestoreFaction();
        return 0;
    }

    /**
     * Removes all bind sight auras from the [Unit].
     */
    int RemoveBindSightAuras(Eluna* /*E*/, Unit* unit)
    {
        unit->RemoveBindSightAuras();
        return 0;
    }

    /**
     * Removes all charm auras from the [Unit].
     */
    int RemoveCharmAuras(Eluna* /*E*/, Unit* unit)
    {
        unit->RemoveCharmAuras();
        return 0;
    }

    /**
     * Enables or disables whether or not the [Unit] can melee auto attack.
     *
     * @param bool disable = true : True to disable melee attack, false to enable
     */
    int DisableMelee(Eluna* E, Unit* unit)
    {
        bool apply = E->CHECKVAL<bool>(2, true);

        if (apply)
            unit->AddUnitState(UNIT_STATE_CANNOT_AUTOATTACK);
        else
            unit->ClearUnitState(UNIT_STATE_CANNOT_AUTOATTACK);

        return 0;
    }

    /**
     * Returns whether or not the [Unit] can have stat modifiers applied.
     *
     * @return bool canModifyStats
     */
    int CanModifyStats(Eluna* E, Unit* unit)
    {
        E->Push(unit->CanModifyStats());
        return 1;
    }

    /**
     * Modifies a flat amount of a specific stat of the [Unit]
     *
     * @table
     * @columns [UnitModifierFlatType, ID]
     * @values [BASE_VALUE, 0]
     * @values [TOTAL_VALUE, 1]
     *
     * @param uint32 statType : The stat to modify
     * @param [UnitModifierFlatType] modType : The type of modifier to apply
     * @param float value : The value to apply to the stat
     * @param bool apply = true : True applies a positive modifier, false applies a negative
     */
    int AddFlatStatModifier(Eluna* E, Unit* unit)
    {
        uint32 statType = E->CHECKVAL<uint32>(2);
        uint8 modType = E->CHECKVAL<uint8>(3);
        float value = E->CHECKVAL<float>(4);
        bool apply = E->CHECKVAL<bool>(5, true);

        unit->HandleStatFlatModifier(UnitMods(UNIT_MOD_STAT_START + statType), (UnitModifierFlatType)modType, value, apply);
        return 0;
    }

    /**
     * Modifies a percentage amount of a specific stat of the [Unit]
     *
     * @table
     * @columns [UnitModifierPctType, ID]
     * @values [BASE_PCT, 0]
     * @values [TOTAL_PCT, 1]
     *
     * @param uint32 statType : The stat to modify
     * @param [UnitModifierPctType] modType : The type of modifier to apply
     * @param float value : The value to apply to the stat
     */
    int AddPctStatModifier(Eluna* E, Unit* unit)
    {
        uint32 statType = E->CHECKVAL<uint32>(2);
        uint8 modType = E->CHECKVAL<uint8>(3);
        float value = E->CHECKVAL<float>(4);

        unit->ApplyStatPctModifier(UnitMods(UNIT_MOD_STAT_START + statType), (UnitModifierPctType)modType, value);
        return 0;
    }

    ElunaRegister<Unit> UnitMethods[] =
    {
        // Getters
        { "GetLevel", &LuaUnit::GetLevel },
        { "GetHealth", &LuaUnit::GetHealth },
        { "GetDisplayId", &LuaUnit::GetDisplayId },
        { "GetNativeDisplayId", &LuaUnit::GetNativeDisplayId },
        { "GetPower", &LuaUnit::GetPower },
        { "GetMaxPower", &LuaUnit::GetMaxPower },
        { "GetPowerType", &LuaUnit::GetPowerType },
        { "GetMaxHealth", &LuaUnit::GetMaxHealth },
        { "GetHealthPct", &LuaUnit::GetHealthPct },
        { "GetPowerPct", &LuaUnit::GetPowerPct },
        { "GetGender", &LuaUnit::GetGender },
        { "GetRace", &LuaUnit::GetRace },
        { "GetClass", &LuaUnit::GetClass },
        { "GetRaceMask", &LuaUnit::GetRaceMask },
        { "GetClassMask", &LuaUnit::GetClassMask },
        { "GetRaceAsString", &LuaUnit::GetRaceAsString },
        { "GetClassAsString", &LuaUnit::GetClassAsString },
        { "GetAura", &LuaUnit::GetAura },
        { "GetOwnedAura", &LuaUnit::GetOwnedAura },
        { "GetFaction", &LuaUnit::GetFaction },
        { "GetCurrentSpell", &LuaUnit::GetCurrentSpell },
        { "GetCreatureType", &LuaUnit::GetCreatureType },
        { "GetMountId", &LuaUnit::GetMountId },
        { "GetOwner", &LuaUnit::GetOwner },
        { "GetFriendlyUnitsInRange", &LuaUnit::GetFriendlyUnitsInRange },
        { "GetUnfriendlyUnitsInRange", &LuaUnit::GetUnfriendlyUnitsInRange },
        { "GetOwnerGUID", &LuaUnit::GetOwnerGUID },
        { "GetCreatorGUID", &LuaUnit::GetCreatorGUID },
        { "GetMinionGUID", &LuaUnit::GetPetGUID },
        { "GetCharmerGUID", &LuaUnit::GetCharmerGUID },
        { "GetCharmGUID", &LuaUnit::GetCharmGUID },
        { "GetPetGUID", &LuaUnit::GetPetGUID },
        { "GetCritterGUID", &LuaUnit::GetCritterGUID },
        { "GetControllerGUID", &LuaUnit::GetControllerGUID },
        { "GetControllerGUIDS", &LuaUnit::GetControllerGUIDS },
        { "GetStandState", &LuaUnit::GetStandState },
        { "GetVictim", &LuaUnit::GetVictim },
        { "GetSpeed", &LuaUnit::GetSpeed },
        { "GetStat", &LuaUnit::GetStat },
        { "GetBaseSpellPower", &LuaUnit::GetBaseSpellPower },
        { "GetVehicleKit", &LuaUnit::GetVehicleKit },
        { "GetVehicle", &LuaUnit::GetVehicle },
        { "GetMovementType", &LuaUnit::GetMovementType },

        // Setters
        { "SetFaction", &LuaUnit::SetFaction },
        { "SetLevel", &LuaUnit::SetLevel },
        { "SetHealth", &LuaUnit::SetHealth },
        { "SetMaxHealth", &LuaUnit::SetMaxHealth },
        { "SetPower", &LuaUnit::SetPower },
        { "SetMaxPower", &LuaUnit::SetMaxPower },
        { "SetPowerType", &LuaUnit::SetPowerType },
        { "SetDisplayId", &LuaUnit::SetDisplayId },
        { "SetNativeDisplayId", &LuaUnit::SetNativeDisplayId },
        { "SetFacing", &LuaUnit::SetFacing },
        { "SetFacingToObject", &LuaUnit::SetFacingToObject },
        { "SetSpeed", &LuaUnit::SetSpeed },
        { "SetStunned", &LuaUnit::SetStunned },
        { "SetRooted", &LuaUnit::SetRooted },
        { "SetConfused", &LuaUnit::SetConfused },
        { "SetFeared", &LuaUnit::SetFeared },
        { "SetPvP", &LuaUnit::SetPvP },
        { "SetFFA", &LuaUnit::SetFFA },
        { "SetSanctuary", &LuaUnit::SetSanctuary },
        { "SetCanFly", &LuaUnit::SetCanFly },
        { "SetVisible", &LuaUnit::SetVisible },
        { "SetOwnerGUID", &LuaUnit::SetOwnerGUID },
        { "SetName", &LuaUnit::SetName },
        { "SetSheath", &LuaUnit::SetSheath },
        { "SetCreatorGUID", &LuaUnit::SetCreatorGUID },
        { "SetMinionGUID", &LuaUnit::SetPetGUID },
        { "SetPetGUID", &LuaUnit::SetPetGUID },
        { "SetCritterGUID", &LuaUnit::SetCritterGUID },
        { "SetWaterWalk", &LuaUnit::SetWaterWalk },
        { "SetStandState", &LuaUnit::SetStandState },
        { "SetInCombatWith", &LuaUnit::SetInCombatWith },
        { "ModifyPower", &LuaUnit::ModifyPower },
        { "SetImmuneTo", &LuaUnit::SetImmuneTo },

        // Boolean
        { "IsAlive", &LuaUnit::IsAlive },
        { "IsDead", &LuaUnit::IsDead },
        { "IsDying", &LuaUnit::IsDying },
        { "IsPvPFlagged", &LuaUnit::IsPvPFlagged },
        { "IsInCombat", &LuaUnit::IsInCombat },
        { "IsBanker", &LuaUnit::IsBanker },
        { "IsBattleMaster", &LuaUnit::IsBattleMaster },
        { "IsCharmed", &LuaUnit::IsCharmed },
        { "IsArmorer", &LuaUnit::IsArmorer },
        { "IsAttackingPlayer", &LuaUnit::IsAttackingPlayer },
        { "IsInWater", &LuaUnit::IsInWater },
        { "IsUnderWater", &LuaUnit::IsUnderWater },
        { "IsAuctioneer", &LuaUnit::IsAuctioneer },
        { "IsGuildMaster", &LuaUnit::IsGuildMaster },
        { "IsInnkeeper", &LuaUnit::IsInnkeeper },
        { "IsTrainer", &LuaUnit::IsTrainer },
        { "IsGossip", &LuaUnit::IsGossip },
        { "IsTaxi", &LuaUnit::IsTaxi },
        { "IsSpiritHealer", &LuaUnit::IsSpiritHealer },
        { "IsSpiritGuide", &LuaUnit::IsSpiritGuide },
        { "IsTabardDesigner", &LuaUnit::IsTabardDesigner },
        { "IsServiceProvider", &LuaUnit::IsServiceProvider },
        { "IsSpiritService", &LuaUnit::IsSpiritService },
        { "HealthBelowPct", &LuaUnit::HealthBelowPct },
        { "HealthAbovePct", &LuaUnit::HealthAbovePct },
        { "IsMounted", &LuaUnit::IsMounted },
        { "AttackStop", &LuaUnit::AttackStop },
        { "Attack", &LuaUnit::Attack },
        { "IsVisible", &LuaUnit::IsVisible },
        { "IsMoving", &LuaUnit::IsMoving },
        { "IsFlying", &LuaUnit::IsFlying },
        { "IsStopped", &LuaUnit::IsStopped },
        { "HasUnitState", &LuaUnit::HasUnitState },
        { "IsQuestGiver", &LuaUnit::IsQuestGiver },
        { "IsInAccessiblePlaceFor", &LuaUnit::IsInAccessiblePlaceFor },
        { "IsVendor", &LuaUnit::IsVendor },
        { "IsRooted", &LuaUnit::IsRooted },
        { "IsFullHealth", &LuaUnit::IsFullHealth },
        { "HasAura", &LuaUnit::HasAura },
        { "IsCasting", &LuaUnit::IsCasting },
        { "IsStandState", &LuaUnit::IsStandState },
        { "IsOnVehicle", &LuaUnit::IsOnVehicle },
        { "CanModifyStats", &LuaUnit::CanModifyStats },

        // Other
        { "AddAura", &LuaUnit::AddAura },
        { "RemoveAura", &LuaUnit::RemoveAura },
        { "RemoveAllAuras", &LuaUnit::RemoveAllAuras },
        { "RemoveArenaAuras", &LuaUnit::RemoveArenaAuras },
        { "ClearInCombat", &LuaUnit::ClearInCombat },
        { "DeMorph", &LuaUnit::DeMorph },
        { "SendUnitWhisper", &LuaUnit::SendUnitWhisper },
        { "SendUnitEmote", &LuaUnit::SendUnitEmote },
        { "SendUnitSay", &LuaUnit::SendUnitSay },
        { "SendUnitYell", &LuaUnit::SendUnitYell },
        { "CastSpell", &LuaUnit::CastSpell },
        { "CastCustomSpell", &LuaUnit::CastCustomSpell },
        { "CastSpellAoF", &LuaUnit::CastSpellAoF },
        { "Kill", &LuaUnit::Kill },
        { "StopSpellCast", &LuaUnit::StopSpellCast },
        { "InterruptSpell", &LuaUnit::InterruptSpell },
        { "SendChatMessageToPlayer", &LuaUnit::SendChatMessageToPlayer },
        { "PerformEmote", &LuaUnit::PerformEmote },
        { "EmoteState", &LuaUnit::EmoteState },
        { "CountPctFromCurHealth", &LuaUnit::CountPctFromCurHealth },
        { "CountPctFromMaxHealth", &LuaUnit::CountPctFromMaxHealth },
        { "Dismount", &LuaUnit::Dismount },
        { "Mount", &LuaUnit::Mount },
        { "RestoreDisplayId", &LuaUnit::RestoreDisplayId },
        { "RestoreFaction", &LuaUnit::RestoreFaction },
        { "RemoveBindSightAuras", &LuaUnit::RemoveBindSightAuras },
        { "RemoveCharmAuras", &LuaUnit::RemoveCharmAuras },
        { "ClearUnitState", &LuaUnit::ClearUnitState },
        { "AddUnitState", &LuaUnit::AddUnitState },
        { "DisableMelee", &LuaUnit::DisableMelee },
        { "NearTeleport", &LuaUnit::NearTeleport },
        { "MoveIdle", &LuaUnit::MoveIdle },
        { "MoveRandom", &LuaUnit::MoveRandom },
        { "MoveHome", &LuaUnit::MoveHome },
        { "MoveFollow", &LuaUnit::MoveFollow },
        { "MoveChase", &LuaUnit::MoveChase },
        { "MoveConfused", &LuaUnit::MoveConfused },
        { "MoveFleeing", &LuaUnit::MoveFleeing },
        { "MoveTo", &LuaUnit::MoveTo },
        { "MoveJump", &LuaUnit::MoveJump },
        { "MoveStop", &LuaUnit::MoveStop },
        { "MoveExpire", &LuaUnit::MoveExpire },
        { "MoveClear", &LuaUnit::MoveClear },
        { "DealDamage", &LuaUnit::DealDamage },
        { "DealHeal", &LuaUnit::DealHeal },
        { "AddFlatStatModifier", &LuaUnit::AddFlatStatModifier },
        { "AddPctStatModifier", &LuaUnit::AddPctStatModifier },

        // Not implemented methods
        { "SummonGuardian", METHOD_REG_NONE } // not implemented
    };
};
#endif
