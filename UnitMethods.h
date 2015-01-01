/*
* Copyright (C) 2010 - 2015 Eluna Lua Engine <http://emudevs.com/>
* This program is free software licensed under GPL version 3
* Please see the included DOCS/LICENSE.md for more information
*/

#ifndef UNITMETHODS_H
#define UNITMETHODS_H

namespace LuaUnit
{
    /* BOOLEAN */
    int Attack(Eluna* /*E*/, lua_State* L, Unit* unit)
    {
        Unit* who = Eluna::CHECKOBJ<Unit>(L, 2);
        bool meleeAttack = Eluna::CHECKVAL<bool>(L, 3, false);

        Eluna::Push(L, unit->Attack(who, meleeAttack));
        return 1;
    }

    int AttackStop(Eluna* /*E*/, lua_State* L, Unit* unit)
    {
        Eluna::Push(L, unit->AttackStop());
        return 1;
    }

    int IsStandState(Eluna* /*E*/, lua_State* L, Unit* unit)
    {
        Eluna::Push(L, unit->IsStandState());
        return 1;
    }

    int IsMounted(Eluna* /*E*/, lua_State* L, Unit* unit)
    {
        Eluna::Push(L, unit->IsMounted());
        return 1;
    }

    int IsRooted(Eluna* /*E*/, lua_State* L, Unit* unit)
    {
#ifdef TRINITY
        Eluna::Push(L, unit->isInRoots() || unit->HasUnitMovementFlag(MOVEMENTFLAG_ROOT));
#endif
#ifdef CMANGOS
        Eluna::Push(L, unit->isInRoots() || unit->IsRooted());
#endif
#ifdef MANGOS
        Eluna::Push(L, unit->IsInRoots() || unit->IsRooted());
#endif
        return 1;
    }

    int IsFullHealth(Eluna* /*E*/, lua_State* L, Unit* unit)
    {
        Eluna::Push(L, unit->IsFullHealth());
        return 1;
    }

    int IsWithinDistInMap(Eluna* /*E*/, lua_State* L, Unit* unit)
    {
        WorldObject* obj = Eluna::CHECKOBJ<WorldObject>(L, 2);
        float radius = Eluna::CHECKVAL<float>(L, 3);

        Eluna::Push(L, unit->IsWithinDistInMap(obj, radius));
        return 1;
    }

    int IsInAccessiblePlaceFor(Eluna* /*E*/, lua_State* L, Unit* unit)
    {
        Creature* creature = Eluna::CHECKOBJ<Creature>(L, 2);

#ifndef TRINITY
        Eluna::Push(L, unit->isInAccessablePlaceFor(creature));
#else
        Eluna::Push(L, unit->isInAccessiblePlaceFor(creature));
#endif
        return 1;
    }

    int IsAuctioneer(Eluna* /*E*/, lua_State* L, Unit* unit)
    {
#ifndef TRINITY
        Eluna::Push(L, unit->isAuctioner());
#else
        Eluna::Push(L, unit->IsAuctioner());
#endif
        return 1;
    }

    int IsGuildMaster(Eluna* /*E*/, lua_State* L, Unit* unit)
    {
#ifdef CMANGOS
        Eluna::Push(L, unit->isGuildMaster());
#else
        Eluna::Push(L, unit->IsGuildMaster());
#endif
        return 1;
    }

    int IsInnkeeper(Eluna* /*E*/, lua_State* L, Unit* unit)
    {
#ifdef CMANGOS
        Eluna::Push(L, unit->isInnkeeper());
#else
        Eluna::Push(L, unit->IsInnkeeper());
#endif
        return 1;
    }

    int IsTrainer(Eluna* /*E*/, lua_State* L, Unit* unit)
    {
#ifdef CMANGOS
        Eluna::Push(L, unit->isTrainer());
#else
        Eluna::Push(L, unit->IsTrainer());
#endif
        return 1;
    }

    int IsGossip(Eluna* /*E*/, lua_State* L, Unit* unit)
    {
#ifdef CMANGOS
        Eluna::Push(L, unit->isGossip());
#else
        Eluna::Push(L, unit->IsGossip());
#endif
        return 1;
    }

    int IsTaxi(Eluna* /*E*/, lua_State* L, Unit* unit)
    {
#ifdef CMANGOS
        Eluna::Push(L, unit->isTaxi());
#else
        Eluna::Push(L, unit->IsTaxi());
#endif
        return 1;
    }

    int IsSpiritHealer(Eluna* /*E*/, lua_State* L, Unit* unit)
    {
#ifdef CMANGOS
        Eluna::Push(L, unit->isSpiritHealer());
#else
        Eluna::Push(L, unit->IsSpiritHealer());
#endif
        return 1;
    }

    int IsSpiritGuide(Eluna* /*E*/, lua_State* L, Unit* unit)
    {
#ifdef CMANGOS
        Eluna::Push(L, unit->isSpiritGuide());
#else
        Eluna::Push(L, unit->IsSpiritGuide());
#endif
        return 1;
    }

    int IsTabardDesigner(Eluna* /*E*/, lua_State* L, Unit* unit)
    {
#ifdef CMANGOS
        Eluna::Push(L, unit->isTabardDesigner());
#else
        Eluna::Push(L, unit->IsTabardDesigner());
#endif
        return 1;
    }

    int IsServiceProvider(Eluna* /*E*/, lua_State* L, Unit* unit)
    {
#ifdef CMANGOS
        Eluna::Push(L, unit->isServiceProvider());
#else
        Eluna::Push(L, unit->IsServiceProvider());
#endif
        return 1;
    }

    int IsSpiritService(Eluna* /*E*/, lua_State* L, Unit* unit)
    {
#ifdef CMANGOS
        Eluna::Push(L, unit->isSpiritService());
#else
        Eluna::Push(L, unit->IsSpiritService());
#endif
        return 1;
    }

    int IsAlive(Eluna* /*E*/, lua_State* L, Unit* unit)
    {
#ifdef CMANGOS
        Eluna::Push(L, unit->isAlive());
#else
        Eluna::Push(L, unit->IsAlive());
#endif
        return 1;
    }

    int IsDead(Eluna* /*E*/, lua_State* L, Unit* unit)
    {
#ifdef MANGOS
        Eluna::Push(L, unit->IsDead());
#else
        Eluna::Push(L, unit->isDead());
#endif
        return 1;
    }

    int IsDying(Eluna* /*E*/, lua_State* L, Unit* unit)
    {
#ifdef MANGOS
        Eluna::Push(L, unit->IsDying());
#else
        Eluna::Push(L, unit->isDying());
#endif
        return 1;
    }

    int IsBanker(Eluna* /*E*/, lua_State* L, Unit* unit)
    {
#ifdef CMANGOS
        Eluna::Push(L, unit->isBanker());
#else
        Eluna::Push(L, unit->IsBanker());
#endif
        return 1;
    }

    int IsVendor(Eluna* /*E*/, lua_State* L, Unit* unit)
    {
#ifdef CMANGOS
        Eluna::Push(L, unit->isVendor());
#else
        Eluna::Push(L, unit->IsVendor());
#endif
        return 1;
    }

    int IsBattleMaster(Eluna* /*E*/, lua_State* L, Unit* unit)
    {
#ifdef CMANGOS
        Eluna::Push(L, unit->isBattleMaster());
#else
        Eluna::Push(L, unit->IsBattleMaster());
#endif
        return 1;
    }

    int IsCharmed(Eluna* /*E*/, lua_State* L, Unit* unit)
    {
#ifdef CMANGOS
        Eluna::Push(L, unit->isCharmed());
#else
        Eluna::Push(L, unit->IsCharmed());
#endif
        return 1;
    }

    int IsArmorer(Eluna* /*E*/, lua_State* L, Unit* unit)
    {
#ifdef CMANGOS
        Eluna::Push(L, unit->isArmorer());
#else
        Eluna::Push(L, unit->IsArmorer());
#endif
        return 1;
    }

    int IsAttackingPlayer(Eluna* /*E*/, lua_State* L, Unit* unit)
    {
        Eluna::Push(L, unit->isAttackingPlayer());
        return 1;
    }

    int IsPvPFlagged(Eluna* /*E*/, lua_State* L, Unit* unit)
    {
        Eluna::Push(L, unit->IsPvP());
        return 1;
    }

#ifndef CLASSIC
    int IsOnVehicle(Eluna* /*E*/, lua_State* L, Unit* unit)
    {
#ifndef TRINITY
        Eluna::Push(L, unit->IsBoarded());
#else
        Eluna::Push(L, unit->GetVehicle());
#endif
        return 1;
    }
#endif

    int IsInCombat(Eluna* /*E*/, lua_State* L, Unit* unit)
    {
#ifdef CMANGOS
        Eluna::Push(L, unit->isInCombat());
#else
        Eluna::Push(L, unit->IsInCombat());
#endif
        return 1;
    }

    int IsUnderWater(Eluna* /*E*/, lua_State* L, Unit* unit)
    {
        Eluna::Push(L, unit->IsUnderWater());
        return 1;
    }

    int IsInWater(Eluna* /*E*/, lua_State* L, Unit* unit)
    {
        Eluna::Push(L, unit->IsInWater());
        return 1;
    }

    int IsStopped(Eluna* /*E*/, lua_State* L, Unit* unit)
    {
        Eluna::Push(L, unit->IsStopped());
        return 1;
    }

    int IsQuestGiver(Eluna* /*E*/, lua_State* L, Unit* unit)
    {
#ifdef CMANGOS
        Eluna::Push(L, unit->isQuestGiver());
#else
        Eluna::Push(L, unit->IsQuestGiver());
#endif
        return 1;
    }

    int HealthBelowPct(Eluna* /*E*/, lua_State* L, Unit* unit)
    {
        Eluna::Push(L, unit->HealthBelowPct(Eluna::CHECKVAL<int32>(L, 2)));
        return 1;
    }

    int HealthAbovePct(Eluna* /*E*/, lua_State* L, Unit* unit)
    {
        Eluna::Push(L, unit->HealthAbovePct(Eluna::CHECKVAL<int32>(L, 2)));
        return 1;
    }

    int HasAura(Eluna* /*E*/, lua_State* L, Unit* unit)
    {
        uint32 spell = Eluna::CHECKVAL<uint32>(L, 2);

        Eluna::Push(L, unit->HasAura(spell));
        return 1;
    }

    int HasUnitState(Eluna* /*E*/, lua_State* L, Unit* unit)
    {
        uint32 state = Eluna::CHECKVAL<uint32>(L, 2);
#ifndef TRINITY
        Eluna::Push(L, unit->hasUnitState(state));
#else
        Eluna::Push(L, unit->HasUnitState(state));
#endif
        return 1;
    }

    /*int IsVisible(Eluna* E, lua_State* L, Unit* unit)
    {
    Eluna::Push(L, unit->IsVisible());
    return 1;
    }*/

    /*int IsMoving(Eluna* E, lua_State* L, Unit* unit)
    {
    Eluna::Push(L, unit->isMoving());
    return 1;
    }*/

    /*int IsFlying(Eluna* E, lua_State* L, Unit* unit)
    {
    Eluna::Push(L, unit->IsFlying());
    return 1;
    }*/

    /* GETTERS */
    int GetOwner(Eluna* /*E*/, lua_State* L, Unit* unit)
    {
        Eluna::Push(L, unit->GetOwner());
        return 1;
    }

    int GetOwnerGUID(Eluna* /*E*/, lua_State* L, Unit* unit)
    {
#ifndef TRINITY
        Eluna::Push(L, unit->GetOwnerGuid());
#else
        Eluna::Push(L, unit->GetOwnerGUID());
#endif
        return 1;
    }

    int GetMountId(Eluna* /*E*/, lua_State* L, Unit* unit)
    {
        Eluna::Push(L, unit->GetMountID());
        return 1;
    }

    int GetCreatorGUID(Eluna* /*E*/, lua_State* L, Unit* unit)
    {
#ifndef TRINITY
        Eluna::Push(L, unit->GetCreatorGuid());
#else
        Eluna::Push(L, unit->GetCreatorGUID());
#endif
        return 1;
    }

    int GetCharmerGUID(Eluna* /*E*/, lua_State* L, Unit* unit)
    {
#ifndef TRINITY
        Eluna::Push(L, unit->GetCharmerGuid());
#else
        Eluna::Push(L, unit->GetCharmerGUID());
#endif
        return 1;
    }

    int GetCharmGUID(Eluna* /*E*/, lua_State* L, Unit* unit)
    {
#ifndef TRINITY
        Eluna::Push(L, unit->GetCharmGuid());
#else
        Eluna::Push(L, unit->GetCharmGUID());
#endif
        return 1;
    }

    int GetPetGUID(Eluna* /*E*/, lua_State* L, Unit* unit)
    {
#ifndef TRINITY
        Eluna::Push(L, unit->GetPetGuid());
#else
        Eluna::Push(L, unit->GetPetGUID());
#endif
        return 1;
    }

    int GetControllerGUID(Eluna* /*E*/, lua_State* L, Unit* unit)
    {
#ifndef TRINITY
        Eluna::Push(L, unit->GetCharmerOrOwnerGuid());
#else
        Eluna::Push(L, unit->GetCharmerOrOwnerGUID());
#endif
        return 1;
    }

    int GetControllerGUIDS(Eluna* /*E*/, lua_State* L, Unit* unit)
    {
#ifndef TRINITY
        Eluna::Push(L, unit->GetCharmerOrOwnerOrOwnGuid());
#else
        Eluna::Push(L, unit->GetCharmerOrOwnerOrOwnGUID());
#endif
        return 1;
    }

    int GetStat(Eluna* /*E*/, lua_State* L, Unit* unit)
    {
        uint32 stat = Eluna::CHECKVAL<uint32>(L, 2);

        if (stat >= MAX_STATS)
            return 1;

        Eluna::Push(L, unit->GetStat((Stats)stat));
        return 1;
    }

    int GetBaseSpellPower(Eluna* /*E*/, lua_State* L, Unit* unit)
    {
        uint32 spellschool = Eluna::CHECKVAL<uint32>(L, 2);

        if (spellschool >= MAX_SPELL_SCHOOL)
            return 1;

        Eluna::Push(L, unit->GetUInt32Value(PLAYER_FIELD_MOD_DAMAGE_DONE_POS + spellschool));
        return 1;
    }

    int GetVictim(Eluna* /*E*/, lua_State* L, Unit* unit)
    {
#ifndef TRINITY
        Eluna::Push(L, unit->getVictim());
#else
        Eluna::Push(L, unit->GetVictim());
#endif
        return 1;
    }

    /**
     * Returns the currently casted [Spell] of given type or nil
     *
     * <pre>
     * enum CurrentSpellTypes
     * {
     *     CURRENT_MELEE_SPELL             = 0,
     *     CURRENT_GENERIC_SPELL           = 1,
     *     CURRENT_CHANNELED_SPELL         = 2,
     *     CURRENT_AUTOREPEAT_SPELL        = 3
     * };
     * </pre>
     *
     * @param [CurrentSpellTypes] spellType
     * @return [Spell] castedSpell
     */
    int GetCurrentSpell(Eluna* /*E*/, lua_State* L, Unit* unit)
    {
        uint32 type = Eluna::CHECKVAL<uint32>(L, 2);
        if (type >= CURRENT_MAX_SPELL)
            return luaL_argerror(L, 2, "valid CurrentSpellTypes expected");

        Eluna::Push(L, unit->GetCurrentSpell(type));
        return 1;
    }

    int GetStandState(Eluna* /*E*/, lua_State* L, Unit* unit)
    {
        Eluna::Push(L, unit->getStandState());
        return 0;
    }

    int GetDisplayId(Eluna* /*E*/, lua_State* L, Unit* unit)
    {
        Eluna::Push(L, unit->GetDisplayId());
        return 1;
    }

    int GetNativeDisplayId(Eluna* /*E*/, lua_State* L, Unit* unit)
    {
        Eluna::Push(L, unit->GetNativeDisplayId());
        return 1;
    }

    int GetLevel(Eluna* /*E*/, lua_State* L, Unit* unit)
    {
        Eluna::Push(L, unit->getLevel());
        return 1;
    }

    int GetHealth(Eluna* /*E*/, lua_State* L, Unit* unit)
    {
        Eluna::Push(L, unit->GetHealth());
        return 1;
    }

    Powers PowerSelectorHelper(Eluna* /*E*/, lua_State* L, Unit* unit, int powerType = -1)
    {
#ifdef TRINITY
        if (powerType == -1)
            return unit->getPowerType();
#else
        if (powerType == -1)
            return unit->GetPowerType();
#endif

        if (powerType < 0 || powerType >= int(MAX_POWERS))
            luaL_argerror(L, 2, "valid Powers expected");

        return (Powers)powerType;
    }

    int GetPower(Eluna* E, lua_State* L, Unit* unit)
    {
        int type = Eluna::CHECKVAL<int>(L, 2, -1);
        Powers power = PowerSelectorHelper(E, L, unit, type);

        Eluna::Push(L, unit->GetPower(power));
        return 1;
    }

    int GetMaxPower(Eluna* E, lua_State* L, Unit* unit)
    {
        int type = Eluna::CHECKVAL<int>(L, 2, -1);
        Powers power = PowerSelectorHelper(E, L, unit, type);

        Eluna::Push(L, unit->GetMaxPower(power));
        return 1;
    }

    int GetPowerPct(Eluna* E, lua_State* L, Unit* unit)
    {
        int type = Eluna::CHECKVAL<int>(L, 2, -1);
        Powers power = PowerSelectorHelper(E, L, unit, type);

#if (!defined(TRINITY) && defined(WOTLK))
        float percent = ((float)unit->GetPower(power) / (float)unit->GetMaxPower(power)) * 100.0f;
#else
        float percent = ((float)unit->GetPower(power) / (float)unit->GetMaxPower(power)) * 100.0f;
#endif
        Eluna::Push(L, percent);
        return 1;
    }

    int GetPowerType(Eluna* /*E*/, lua_State* L, Unit* unit)
    {
#ifdef TRINITY
        Eluna::Push(L, unit->getPowerType());
#else
        Eluna::Push(L, unit->GetPowerType());
#endif
        return 1;
    }

    int GetMaxHealth(Eluna* /*E*/, lua_State* L, Unit* unit)
    {
        Eluna::Push(L, unit->GetMaxHealth());
        return 1;
    }

    int GetHealthPct(Eluna* /*E*/, lua_State* L, Unit* unit)
    {
#ifndef TRINITY
        Eluna::Push(L, unit->GetHealthPercent());
#else
        Eluna::Push(L, unit->GetHealthPct());
#endif
        return 1;
    }

    int GetGender(Eluna* /*E*/, lua_State* L, Unit* unit)
    {
        Eluna::Push(L, unit->getGender());
        return 1;
    }

    int GetRace(Eluna* /*E*/, lua_State* L, Unit* unit)
    {
        Eluna::Push(L, unit->getRace());
        return 1;
    }

    int GetClass(Eluna* /*E*/, lua_State* L, Unit* unit)
    {
        Eluna::Push(L, unit->getClass());
        return 1;
    }

    int GetCreatureType(Eluna* /*E*/, lua_State* L, Unit* unit)
    {
        Eluna::Push(L, unit->GetCreatureType());
        return 1;
    }

    /**
     * Returns the [Unit]'s class' name in given or default locale or nil.
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
     * @param [LocaleConstant] locale = DEFAULT_LOCALE
     * @return string className : class name or nil
     */
    int GetClassAsString(Eluna* /*E*/, lua_State* L, Unit* unit)
    {
        uint8 locale = Eluna::CHECKVAL<uint8>(L, 2, DEFAULT_LOCALE);
        if (locale >= TOTAL_LOCALES)
            return luaL_argerror(L, 2, "valid LocaleConstant expected");

        const ChrClassesEntry* entry = sChrClassesStore.LookupEntry(unit->getClass());
        if (!entry)
            return 1;

        Eluna::Push(L, entry->name[locale]);
        return 1;
    }

    /**
     * Returns the [Unit]'s race's name in given or default locale or nil.
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
     * @param [LocaleConstant] locale = DEFAULT_LOCALE : locale to return the race name in
     * @return string raceName : race name or nil
     */
    int GetRaceAsString(Eluna* /*E*/, lua_State* L, Unit* unit)
    {
        uint8 locale = Eluna::CHECKVAL<uint8>(L, 2, DEFAULT_LOCALE);
        if (locale >= TOTAL_LOCALES)
            return luaL_argerror(L, 2, "valid LocaleConstant expected");

        const ChrRacesEntry* entry = sChrRacesStore.LookupEntry(unit->getRace());
        if (!entry)
            return 1;

        Eluna::Push(L, entry->name[locale]);
        return 1;
    }

    int GetFaction(Eluna* /*E*/, lua_State* L, Unit* unit)
    {
        Eluna::Push(L, unit->getFaction());
        return 1;
    }

    int GetAura(Eluna* /*E*/, lua_State* L, Unit* unit)
    {
        uint32 spellID = Eluna::CHECKVAL<uint32>(L, 2);
#ifndef TRINITY
        Eluna::Push(L, unit->GetAura(spellID, EFFECT_INDEX_0));
#else
        Eluna::Push(L, unit->GetAura(spellID));
#endif
        return 1;
    }

    int GetCombatTime(Eluna* /*E*/, lua_State* L, Unit* unit)
    {
        Eluna::Push(L, unit->GetCombatTimer());
        return 1;
    }

    int GetFriendlyUnitsInRange(Eluna* /*E*/, lua_State* L, Unit* unit)
    {
        float range = Eluna::CHECKVAL<float>(L, 2, SIZE_OF_GRIDS);

        std::list<Unit*> list;
#ifndef TRINITY
        MaNGOS::AnyFriendlyUnitInObjectRangeCheck checker(unit, range);
        MaNGOS::UnitListSearcher<MaNGOS::AnyFriendlyUnitInObjectRangeCheck> searcher(list, checker);
        Cell::VisitGridObjects(unit, searcher, range);
#else
        Trinity::AnyFriendlyUnitInObjectRangeCheck checker(unit, unit, range);
        Trinity::UnitListSearcher<Trinity::AnyFriendlyUnitInObjectRangeCheck> searcher(unit, list, checker);
        unit->VisitNearbyObject(range, searcher);
#endif
        ElunaUtil::ObjectGUIDCheck guidCheck(unit->GET_GUID());
        list.remove_if(guidCheck);

        lua_newtable(L);
        int tbl = lua_gettop(L);
        uint32 i = 0;

        for (std::list<Unit*>::const_iterator it = list.begin(); it != list.end(); ++it)
        {
            Eluna::Push(L, ++i);
            Eluna::Push(L, *it);
            lua_settable(L, tbl);
        }

        lua_settop(L, tbl);
        return 1;
    }

    int GetUnfriendlyUnitsInRange(Eluna* /*E*/, lua_State* L, Unit* unit)
    {
        float range = Eluna::CHECKVAL<float>(L, 2, SIZE_OF_GRIDS);

        std::list<Unit*> list;
#ifndef TRINITY
        MaNGOS::AnyUnfriendlyUnitInObjectRangeCheck checker(unit, range);
        MaNGOS::UnitListSearcher<MaNGOS::AnyUnfriendlyUnitInObjectRangeCheck> searcher(list, checker);
        Cell::VisitGridObjects(unit, searcher, range);
#else
        Trinity::AnyUnfriendlyUnitInObjectRangeCheck checker(unit, unit, range);
        Trinity::UnitListSearcher<Trinity::AnyUnfriendlyUnitInObjectRangeCheck> searcher(unit, list, checker);
        unit->VisitNearbyObject(range, searcher);
#endif
        ElunaUtil::ObjectGUIDCheck guidCheck(unit->GET_GUID());
        list.remove_if(guidCheck);

        lua_newtable(L);
        int tbl = lua_gettop(L);
        uint32 i = 0;

        for (std::list<Unit*>::const_iterator it = list.begin(); it != list.end(); ++it)
        {
            Eluna::Push(L, ++i);
            Eluna::Push(L, *it);
            lua_settable(L, tbl);
        }

        lua_settop(L, tbl);
        return 1;
    }

#if (!defined(TBC) && !defined(CLASSIC))
    int GetVehicleKit(Eluna* /*E*/, lua_State* L, Unit* unit)
    {
#ifndef TRINITY
        Eluna::Push(L, unit->GetVehicleInfo());
#else
        Eluna::Push(L, unit->GetVehicleKit());
#endif
        return 1;
    }

    /*
    int GetVehicle(Eluna* E, lua_State* L, Unit* unit)
    {
    Eluna::Push(L, unit->GetVehicle());
    return 1;
    }
    */

    int GetCritterGUID(Eluna* /*E*/, lua_State* L, Unit* unit)
    {
#ifndef TRINITY
        Eluna::Push(L, unit->GetCritterGuid());
#else
        Eluna::Push(L, unit->GetCritterGUID());
#endif
        return 1;
    }
#endif

    /**
     * Returns the [Unit]'s speed of given [UnitMoveType].
     *
     * <pre>
     * enum UnitMoveType
     * {
     *     MOVE_WALK           = 0,
     *     MOVE_RUN            = 1,
     *     MOVE_RUN_BACK       = 2,
     *     MOVE_SWIM           = 3,
     *     MOVE_SWIM_BACK      = 4,
     *     MOVE_TURN_RATE      = 5,
     *     MOVE_FLIGHT         = 6,
     *     MOVE_FLIGHT_BACK    = 7,
     *     MOVE_PITCH_RATE     = 8
     * };
     * </pre>
     *
     * @param [UnitMoveType] type
     * @return float speed
     */
    int GetSpeed(Eluna* /*E*/, lua_State* L, Unit* unit)
    {
        uint32 type = Eluna::CHECKVAL<uint32>(L, 2);
        if (type >= MAX_MOVE_TYPE)
            return luaL_argerror(L, 2, "valid UnitMoveType expected");

#ifndef TRINITY
        Eluna::Push(L, unit->GetSpeedRate((UnitMoveType)type));
#else
        Eluna::Push(L, unit->GetSpeed((UnitMoveType)type));
#endif
        return 1;
    }

#ifdef MANGOS
    /**
     * Returns the current movement type for this [Unit].
     *
     * <pre>
     * enum MovementGeneratorType
     * {
     *     IDLE_MOTION_TYPE                = 0,
     *     RANDOM_MOTION_TYPE              = 1,
     *     WAYPOINT_MOTION_TYPE            = 2,
     *     MAX_DB_MOTION_TYPE              = 3,
     * 
     *     CONFUSED_MOTION_TYPE            = 4,
     *     CHASE_MOTION_TYPE               = 5,
     *     HOME_MOTION_TYPE                = 6,
     *     FLIGHT_MOTION_TYPE              = 7,
     *     POINT_MOTION_TYPE               = 8,
     *     FLEEING_MOTION_TYPE             = 9,
     *     DISTRACT_MOTION_TYPE            = 10,
     *     ASSISTANCE_MOTION_TYPE          = 11,
     *     ASSISTANCE_DISTRACT_MOTION_TYPE = 12,          
     *     TIMED_FLEEING_MOTION_TYPE       = 13,
     *     FOLLOW_MOTION_TYPE              = 14,
     *     EFFECT_MOTION_TYPE              = 15,
     * };
     * </pre>
     *
     * @return MovementGeneratorType movementType
     */
    int GetMovementType(Eluna* /*E*/, lua_State* L, Unit* unit)
    {
        Eluna::Push(L, unit->GetMotionMaster()->GetCurrentMovementGeneratorType());
        return 1;
    }
#endif

    /* SETTERS */
    int SetOwnerGUID(Eluna* /*E*/, lua_State* L, Unit* unit)
    {
        uint64 guid = Eluna::CHECKVAL<uint64>(L, 2);

#ifndef TRINITY
        unit->SetOwnerGuid(ObjectGuid(guid));
#else
        unit->SetOwnerGUID(ObjectGuid(guid));
#endif
        return 0;
    }

    int SetPvP(Eluna* /*E*/, lua_State* L, Unit* unit)
    {
        bool apply = Eluna::CHECKVAL<bool>(L, 2, true);

        unit->SetPvP(apply);
        return 0;
    }

    int SetSheath(Eluna* /*E*/, lua_State* L, Unit* unit)
    {
        uint32 sheathed = Eluna::CHECKVAL<uint32>(L, 2);
        if (sheathed >= MAX_SHEATH_STATE)
            return luaL_argerror(L, 2, "valid SheathState expected");

        unit->SetSheath((SheathState)sheathed);
        return 0;
    }

    int SetName(Eluna* /*E*/, lua_State* L, Unit* unit)
    {
        const char* name = Eluna::CHECKVAL<const char*>(L, 2);
        if (std::string(name).length() > 0)
            unit->SetName(name);
        return 0;
    }

    /**
     * Sets the [Unit]'s speed of given [UnitMoveType] to given rate.
     * If forced, packets sent to clients forcing the visual change.
     *
     * <pre>
     * enum UnitMoveType
     * {
     *     MOVE_WALK           = 0,
     *     MOVE_RUN            = 1,
     *     MOVE_RUN_BACK       = 2,
     *     MOVE_SWIM           = 3,
     *     MOVE_SWIM_BACK      = 4,
     *     MOVE_TURN_RATE      = 5,
     *     MOVE_FLIGHT         = 6,
     *     MOVE_FLIGHT_BACK    = 7,
     *     MOVE_PITCH_RATE     = 8
     * };
     * </pre>
     *
     * @param [UnitMoveType] type
     * @param float rate
     * @param bool forced = false
     */
    int SetSpeed(Eluna* /*E*/, lua_State* L, Unit* unit)
    {
        uint32 type = Eluna::CHECKVAL<uint32>(L, 2);
        float rate = Eluna::CHECKVAL<float>(L, 3);
        bool forced = Eluna::CHECKVAL<bool>(L, 4, false);
        if (type >= MAX_MOVE_TYPE)
            return luaL_argerror(L, 2, "valid UnitMoveType expected");
#ifndef TRINITY
        unit->SetSpeedRate((UnitMoveType)type, rate, forced);
#else
        unit->SetSpeed((UnitMoveType)type, rate, forced);
#endif
        return 0;
    }

    int SetFaction(Eluna* /*E*/, lua_State* L, Unit* unit)
    {
        uint32 factionId = Eluna::CHECKVAL<uint32>(L, 2);
        unit->setFaction(factionId);
        return 0;
    }

    int SetLevel(Eluna* /*E*/, lua_State* L, Unit* unit)
    {
        uint32 newLevel = Eluna::CHECKVAL<uint32>(L, 2);
        unit->SetLevel(newLevel);
        return 0;
    }

    int SetHealth(Eluna* /*E*/, lua_State* L, Unit* unit)
    {
        uint32 amt = Eluna::CHECKVAL<uint32>(L, 2);
        unit->SetHealth(amt);
        return 0;
    }

    int SetMaxHealth(Eluna* /*E*/, lua_State* L, Unit* unit)
    {
        uint32 amt = Eluna::CHECKVAL<uint32>(L, 2);
        unit->SetMaxHealth(amt);
        return 0;
    }

    int SetPower(Eluna* E, lua_State* L, Unit* unit)
    {
        int type = Eluna::CHECKVAL<int>(L, 2, -1);
        uint32 amt = Eluna::CHECKVAL<uint32>(L, 3);
        Powers power = PowerSelectorHelper(E, L, unit, type);

        unit->SetPower(power, amt);
        return 0;
    }

    int SetMaxPower(Eluna* E, lua_State* L, Unit* unit)
    {
        int type = Eluna::CHECKVAL<int>(L, 2, -1);
        uint32 amt = Eluna::CHECKVAL<uint32>(L, 3);
        Powers power = PowerSelectorHelper(E, L, unit, type);

        unit->SetMaxPower(power, amt);
        return 0;
    }

    int SetPowerType(Eluna* /*E*/, lua_State* L, Unit* unit)
    {
        uint32 type = Eluna::CHECKVAL<uint32>(L, 2);
        if (type >= int(MAX_POWERS))
            return luaL_argerror(L, 2, "valid Powers expected");

#ifdef TRINITY
        unit->setPowerType((Powers)type);
#else
        unit->SetPowerType((Powers)type);
#endif
        return 0;
    }

    int SetDisplayId(Eluna* /*E*/, lua_State* L, Unit* unit)
    {
        uint32 model = Eluna::CHECKVAL<uint32>(L, 2);
        unit->SetDisplayId(model);
        return 0;
    }

    int SetNativeDisplayId(Eluna* /*E*/, lua_State* L, Unit* unit)
    {
        uint32 model = Eluna::CHECKVAL<uint32>(L, 2);
        unit->SetNativeDisplayId(model);
        return 0;
    }

    int SetFacing(Eluna* /*E*/, lua_State* L, Unit* unit)
    {
        float o = Eluna::CHECKVAL<float>(L, 2);
        unit->SetFacingTo(o);
        return 0;
    }

    int SetFacingToObject(Eluna* /*E*/, lua_State* L, Unit* unit)
    {
        WorldObject* obj = Eluna::CHECKOBJ<WorldObject>(L, 2);
        unit->SetFacingToObject(obj);
        return 0;
    }

    int SetCreatorGUID(Eluna* /*E*/, lua_State* L, Unit* unit)
    {
        uint64 guid = Eluna::CHECKVAL<uint64>(L, 2);
#ifndef TRINITY
        unit->SetCreatorGuid(ObjectGuid(guid));
#else
        unit->SetCreatorGUID(ObjectGuid(guid));
#endif
        return 0;
    }

    int SetCharmerGUID(Eluna* /*E*/, lua_State* L, Unit* unit)
    {
        uint64 guid = Eluna::CHECKVAL<uint64>(L, 2);
#ifndef TRINITY
        unit->SetCharmerGuid(ObjectGuid(guid));
#else
        unit->SetCharmerGUID(ObjectGuid(guid));
#endif
        return 0;
    }

    int SetPetGUID(Eluna* /*E*/, lua_State* L, Unit* unit)
    {
        uint64 guid = Eluna::CHECKVAL<uint64>(L, 2);
#ifndef TRINITY
        unit->SetPetGuid(ObjectGuid(guid));
#else
        unit->SetPetGUID(ObjectGuid(guid));
#endif
        return 0;
    }

    int SetWaterWalk(Eluna* /*E*/, lua_State* L, Unit* unit)
    {
        bool enable = Eluna::CHECKVAL<bool>(L, 2, true);
#ifndef TRINITY
        unit->SetWaterWalk(enable);
#else
        unit->SetWaterWalking(enable);
#endif
        return 0;
    }

    int SetStandState(Eluna* /*E*/, lua_State* L, Unit* unit)
    {
        uint8 state = Eluna::CHECKVAL<uint8>(L, 2);
        unit->SetStandState(state);
        return 0;
    }

#if (!defined(TBC) && !defined(CLASSIC))
    int SetFFA(Eluna* /*E*/, lua_State* L, Unit* unit)
    {
        bool apply = Eluna::CHECKVAL<bool>(L, 2, true);

#ifndef TRINITY
        unit->SetFFAPvP(apply);
#else
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
#endif
        return 0;
    }

    int SetSanctuary(Eluna* /*E*/, lua_State* L, Unit* unit)
    {
        bool apply = Eluna::CHECKVAL<bool>(L, 2, true);

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

    int SetPhaseMask(Eluna* /*E*/, lua_State* L, Unit* unit)
    {
        uint32 phaseMask = Eluna::CHECKVAL<uint32>(L, 2);
        bool Update = Eluna::CHECKVAL<bool>(L, 3, true);
        unit->SetPhaseMask(phaseMask, Update);
        return 0;
    }

    int SetCritterGUID(Eluna* /*E*/, lua_State* L, Unit* unit)
    {
        uint64 guid = Eluna::CHECKVAL<uint64>(L, 2);
#ifndef TRINITY
        unit->SetCritterGuid(ObjectGuid(guid));
#else
        unit->SetCritterGUID(ObjectGuid(guid));
#endif
        return 0;
    }
#endif

    /*int SetStunned(Eluna* E, lua_State* L, Unit* unit)
    {
    bool apply = Eluna::CHECKVAL<bool>(L, 2, true);
    unit->SetControlled(apply, UNIT_STATE_STUNNED);
    return 0;
    }*/

    /**
     * Roots the [Unit] to the ground, if 'false' specified, unroots the [Unit].
     *
     * @param bool apply = true
     */
    int SetRooted(Eluna* E, lua_State* L, Unit* unit)
    {
        bool apply = Eluna::CHECKVAL<bool>(L, 2, true);
#ifndef TRINITY
        unit->SetRoot(apply);
#else
        unit->SetControlled(apply, UNIT_STATE_ROOT);
#endif
        return 0;
    }

    /**
     * Confuses the [Unit], if 'false' specified, the [Unit] is no longer confused.
     *
     * @param bool apply = true
     */
    int SetConfused(Eluna* E, lua_State* L, Unit* unit)
    {
        bool apply = Eluna::CHECKVAL<bool>(L, 2, true);
#ifndef TRINITY
        unit->SetConfused(apply);
#else
        unit->SetControlled(apply, UNIT_STATE_CONFUSED);
#endif
    return 0;
    }

    /**
     * Fears the [Unit], if 'false' specified, the [Unit] is no longer feared.
     *
     * @param bool apply = true
     */
    int SetFeared(Eluna* E, lua_State* L, Unit* unit)
    {
        bool apply = Eluna::CHECKVAL<bool>(L, 2, true);
#ifndef TRINITY
        unit->SetFeared(apply);
#else
        unit->SetControlled(apply, UNIT_STATE_FLEEING);
#endif
        return 0;
    }

    /*int SetCanFly(Eluna* E, lua_State* L, Unit* unit)
    {
    bool apply = Eluna::CHECKVAL<bool>(L, 2, true);
    unit->SetCanFly(apply);
    return 0;
    }*/

    /*int SetVisible(Eluna* E, lua_State* L, Unit* unit)
    {
    bool x = Eluna::CHECKVAL<bool>(L, 2, true);
    unit->SetVisible(x);
    return 0;
    }*/

    /* OTHER */
    int ClearThreatList(Eluna* /*E*/, lua_State* /*L*/, Unit* unit)
    {
#ifdef MANGOS
        unit->GetThreatManager().clearReferences();
#else
        unit->getThreatManager().clearReferences();
#endif
        return 0;
    }

    int Mount(Eluna* /*E*/, lua_State* L, Unit* unit)
    {
        uint32 displayId = Eluna::CHECKVAL<uint32>(L, 2);

        unit->Mount(displayId);
        return 0;
    }

    int Dismount(Eluna* /*E*/, lua_State* /*L*/, Unit* unit)
    {
        if (unit->IsMounted())
        {
#ifndef TRINITY
            unit->Unmount();
            unit->RemoveSpellsCausingAura(SPELL_AURA_MOUNTED);
#else
            unit->Dismount();
            unit->RemoveAurasByType(SPELL_AURA_MOUNTED);
#endif
        }

        return 0;
    }

    int Emote(Eluna* /*E*/, lua_State* L, Unit* unit)
    {
        unit->HandleEmoteCommand(Eluna::CHECKVAL<uint32>(L, 2));
        return 0;
    }

    int CountPctFromCurHealth(Eluna* /*E*/, lua_State* L, Unit* unit)
    {
        Eluna::Push(L, unit->CountPctFromCurHealth(Eluna::CHECKVAL<int32>(L, 2)));
        return 1;
    }

    int CountPctFromMaxHealth(Eluna* /*E*/, lua_State* L, Unit* unit)
    {
        Eluna::Push(L, unit->CountPctFromMaxHealth(Eluna::CHECKVAL<int32>(L, 2)));
        return 1;
    }

    int SendChatMessageToPlayer(Eluna* /*E*/, lua_State* L, Unit* unit)
    {
        uint8 type = Eluna::CHECKVAL<uint8>(L, 2);
        uint32 lang = Eluna::CHECKVAL<uint32>(L, 3);
        std::string msg = Eluna::CHECKVAL<std::string>(L, 4);
        Player* target = Eluna::CHECKOBJ<Player>(L, 5);

        if (type >= MAX_CHAT_MSG_TYPE)
            return luaL_argerror(L, 2, "valid ChatMsg expected");
        if (lang >= LANGUAGES_COUNT)
            return luaL_argerror(L, 3, "valid Language expected");

        WorldPacket data;
#ifdef TRINITY
        ChatHandler::BuildChatPacket(data, ChatMsg(type), Language(lang), unit, target, msg);
#else
        ChatHandler::BuildChatPacket(data, ChatMsg(type), msg.c_str(), Language(lang), 0, unit->GET_GUID(), unit->GetName(), target->GET_GUID(), target->GetName());
#endif
        target->GetSession()->SendPacket(&data);
        return 0;
    }

    // static void PrepareMove(Unit* unit)
    // {
    //     unit->GetMotionMaster()->MovementExpired(); // Chase
    //     unit->StopMoving(); // Some
    //     unit->GetMotionMaster()->Clear(); // all
    // }

    int MoveStop(Eluna* /*E*/, lua_State* /*L*/, Unit* unit)
    {
        unit->StopMoving();
        return 0;
    }

    int MoveExpire(Eluna* /*E*/, lua_State* L, Unit* unit)
    {
        bool reset = Eluna::CHECKVAL<bool>(L, 2, true);
        unit->GetMotionMaster()->MovementExpired(reset);
        return 0;
    }

    int MoveClear(Eluna* /*E*/, lua_State* L, Unit* unit)
    {
        bool reset = Eluna::CHECKVAL<bool>(L, 2, true);
        unit->GetMotionMaster()->Clear(reset);
        return 0;
    }

    int MoveIdle(Eluna* /*E*/, lua_State* /*L*/, Unit* unit)
    {
        unit->GetMotionMaster()->MoveIdle();
        return 0;
    }

    int MoveRandom(Eluna* /*E*/, lua_State* L, Unit* unit)
    {
        float radius = Eluna::CHECKVAL<float>(L, 2);
        float x, y, z;
        unit->GetPosition(x, y, z);
#ifndef TRINITY
        unit->GetMotionMaster()->MoveRandomAroundPoint(x, y, z, radius);
#else
        unit->GetMotionMaster()->MoveRandom(radius);
#endif
        return 0;
    }

    int MoveHome(Eluna* /*E*/, lua_State* /*L*/, Unit* unit)
    {
        unit->GetMotionMaster()->MoveTargetedHome();
        return 0;
    }

    int MoveFollow(Eluna* /*E*/, lua_State* L, Unit* unit)
    {
        Unit* target = Eluna::CHECKOBJ<Unit>(L, 2);
        float dist = Eluna::CHECKVAL<float>(L, 3, 0.0f);
        float angle = Eluna::CHECKVAL<float>(L, 4, 0.0f);
        unit->GetMotionMaster()->MoveFollow(target, dist, angle);
        return 0;
    }

    int MoveChase(Eluna* /*E*/, lua_State* L, Unit* unit)
    {
        Unit* target = Eluna::CHECKOBJ<Unit>(L, 2);
        float dist = Eluna::CHECKVAL<float>(L, 3, 0.0f);
        float angle = Eluna::CHECKVAL<float>(L, 4, 0.0f);
        unit->GetMotionMaster()->MoveChase(target, dist, angle);
        return 0;
    }

    int MoveConfused(Eluna* /*E*/, lua_State* /*L*/, Unit* unit)
    {
        unit->GetMotionMaster()->MoveConfused();
        return 0;
    }

    int MoveFleeing(Eluna* /*E*/, lua_State* L, Unit* unit)
    {
        Unit* target = Eluna::CHECKOBJ<Unit>(L, 2);
        uint32 time = Eluna::CHECKVAL<uint32>(L, 3, 0);
        unit->GetMotionMaster()->MoveFleeing(target, time);
        return 0;
    }

    int MoveTo(Eluna* /*E*/, lua_State* L, Unit* unit)
    {
        uint32 id = Eluna::CHECKVAL<uint32>(L, 2);
        float x = Eluna::CHECKVAL<float>(L, 3);
        float y = Eluna::CHECKVAL<float>(L, 4);
        float z = Eluna::CHECKVAL<float>(L, 5);
        bool genPath = Eluna::CHECKVAL<bool>(L, 6, true);
        unit->GetMotionMaster()->MovePoint(id, x, y, z, genPath);
        return 0;
    }

#if (!defined(TBC) && !defined(CLASSIC))
    int MoveJump(Eluna* /*E*/, lua_State* L, Unit* unit)
    {
        float x = Eluna::CHECKVAL<float>(L, 2);
        float y = Eluna::CHECKVAL<float>(L, 3);
        float z = Eluna::CHECKVAL<float>(L, 4);
        float zSpeed = Eluna::CHECKVAL<float>(L, 5);
        float maxHeight = Eluna::CHECKVAL<float>(L, 6);
        uint32 id = Eluna::CHECKVAL<uint32>(L, 7, 0);
        unit->GetMotionMaster()->MoveJump(x, y, z, zSpeed, maxHeight, id);
        return 0;
    }
#endif

    int SendUnitWhisper(Eluna* /*E*/, lua_State* L, Unit* unit)
    {
        const char* msg = Eluna::CHECKVAL<const char*>(L, 2);
        uint32 lang = Eluna::CHECKVAL<uint32>(L, 3);
        Player* receiver = Eluna::CHECKOBJ<Player>(L, 4);
        bool bossWhisper = Eluna::CHECKVAL<bool>(L, 5, false);
        if (std::string(msg).length() > 0)
#ifdef TRINITY
            unit->Whisper(msg, (Language)lang, receiver, bossWhisper);
#else
            unit->MonsterWhisper(msg, receiver, bossWhisper);
#endif
        return 0;
    }

    int SendUnitEmote(Eluna* /*E*/, lua_State* L, Unit* unit)
    {
        const char* msg = Eluna::CHECKVAL<const char*>(L, 2);
        Unit* receiver = Eluna::CHECKOBJ<Unit>(L, 3, false);
        bool bossEmote = Eluna::CHECKVAL<bool>(L, 4, false);
        if (std::string(msg).length() > 0)
#ifdef TRINITY
            unit->TextEmote(msg, receiver, bossEmote);
#else
            unit->MonsterTextEmote(msg, receiver, bossEmote);
#endif
        return 0;
    }

    int SendUnitSay(Eluna* /*E*/, lua_State* L, Unit* unit)
    {
        const char* msg = Eluna::CHECKVAL<const char*>(L, 2);
        uint32 language = Eluna::CHECKVAL<uint32>(L, 3);
        if (std::string(msg).length() > 0)
#ifdef TRINITY
            unit->Say(msg, (Language)language, unit);
#else
            unit->MonsterSay(msg, language, unit);
#endif
        return 0;
    }

    int SendUnitYell(Eluna* /*E*/, lua_State* L, Unit* unit)
    {
        const char* msg = Eluna::CHECKVAL<const char*>(L, 2);
        uint32 language = Eluna::CHECKVAL<uint32>(L, 3);
        if (std::string(msg).length() > 0)
#ifdef TRINITY
            unit->Yell(msg, (Language)language, unit);
#else
            unit->MonsterYell(msg, language, unit);
#endif
        return 0;
    }

    int DeMorph(Eluna* /*E*/, lua_State* /*L*/, Unit* unit)
    {
        unit->DeMorph();
        return 0;
    }

    int CastSpell(Eluna* /*E*/, lua_State* L, Unit* unit)
    {
        Unit* target = Eluna::CHECKOBJ<Unit>(L, 2);
        uint32 spell = Eluna::CHECKVAL<uint32>(L, 3);
        bool triggered = Eluna::CHECKVAL<bool>(L, 4, false);
        SpellEntry const* spellEntry = sSpellStore.LookupEntry(spell);
        if (!spellEntry)
            return 0;

        unit->CastSpell(target, spell, triggered);
        return 0;
    }

    /**
     * Casts the [Spell] at target [Unit] with custom basepoints or casters.
     * See also [Unit:CastSpell].
     *
     * @param [Unit] target
     * @param uint32 spell
     * @param bool triggered = false
     * @param int32 bp0 = nil : custom basepoints for [Spell] effect 1. If nil, no change is made
     * @param int32 bp1 = nil : custom basepoints for [Spell] effect 2. If nil, no change is made
     * @param int32 bp2 = nil : custom basepoints for [Spell] effect 3. If nil, no change is made
     * @param [Item] castItem = nil
     * @param uint64 originalCaster = 0
     */
    int CastCustomSpell(Eluna* /*E*/, lua_State* L, Unit* unit)
    {
        Unit* target = Eluna::CHECKOBJ<Unit>(L, 2);
        uint32 spell = Eluna::CHECKVAL<uint32>(L, 3);
        bool triggered = Eluna::CHECKVAL<bool>(L, 4, false);
        bool has_bp0 = !lua_isnoneornil(L, 5);
        int32 bp0 = Eluna::CHECKVAL<int32>(L, 5, 0);
        bool has_bp1 = !lua_isnoneornil(L, 6);
        int32 bp1 = Eluna::CHECKVAL<int32>(L, 6, 0);
        bool has_bp2 = !lua_isnoneornil(L, 7);
        int32 bp2 = Eluna::CHECKVAL<int32>(L, 7, 0);
        Item* castItem = Eluna::CHECKOBJ<Item>(L, 8, false);
        uint64 originalCaster = Eluna::CHECKVAL<uint64>(L, 9, 0);

        unit->CastCustomSpell(target, spell, has_bp0 ? &bp0 : NULL, has_bp1 ? &bp1 : NULL, has_bp2 ? &bp2 : NULL, triggered, castItem, NULL, ObjectGuid(originalCaster));
        return 0;
    }

    int CastSpellAoF(Eluna* /*E*/, lua_State* L, Unit* unit)
    {
        float _x = Eluna::CHECKVAL<float>(L, 2);
        float _y = Eluna::CHECKVAL<float>(L, 3);
        float _z = Eluna::CHECKVAL<float>(L, 4);
        uint32 spell = Eluna::CHECKVAL<uint32>(L, 5);
        bool triggered = Eluna::CHECKVAL<bool>(L, 6, true);
        unit->CastSpell(_x, _y, _z, spell, triggered);
        return 0;
    }

    int ClearInCombat(Eluna* /*E*/, lua_State* /*L*/, Unit* unit)
    {
        unit->ClearInCombat();
        return 0;
    }

    int StopSpellCast(Eluna* /*E*/, lua_State* L, Unit* unit)
    {
        uint32 spellId = Eluna::CHECKVAL<uint32>(L, 2, 0);
        unit->CastStop(spellId);
        return 0;
    }

    int InterruptSpell(Eluna* /*E*/, lua_State* L, Unit* unit)
    {
        int spellType = Eluna::CHECKVAL<int>(L, 2);
        bool delayed = Eluna::CHECKVAL<bool>(L, 3, true);
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
                return luaL_argerror(L, 2, "valid CurrentSpellTypes expected");
        }

        unit->InterruptSpell((CurrentSpellTypes)spellType, delayed);
        return 0;
    }

    int AddAura(Eluna* /*E*/, lua_State* L, Unit* unit)
    {
        uint32 spellId = Eluna::CHECKVAL<uint32>(L, 2);
        Unit* target = Eluna::CHECKOBJ<Unit>(L, 3);
        SpellEntry const* spellInfo = sSpellStore.LookupEntry(spellId);
        if (!spellInfo)
            return 1;

#ifndef TRINITY
        if (!IsSpellAppliesAura(spellInfo) && !IsSpellHaveEffect(spellInfo, SPELL_EFFECT_PERSISTENT_AREA_AURA))
            return 1;

        SpellAuraHolder* holder = CreateSpellAuraHolder(spellInfo, target, unit);

        for (uint32 i = 0; i < MAX_EFFECT_INDEX; ++i)
        {
            uint8 eff = spellInfo->Effect[i];
            if (eff >= TOTAL_SPELL_EFFECTS)
                continue;
            if (IsAreaAuraEffect(eff) ||
                eff == SPELL_EFFECT_APPLY_AURA ||
                eff == SPELL_EFFECT_PERSISTENT_AREA_AURA)
            {
                Aura* aur = CreateAura(spellInfo, SpellEffIndex(i), NULL, holder, target);
                holder->AddAura(aur, SpellEffIndex(i));
            }
        }
        Eluna::Push(L, target->AddSpellAuraHolder(holder));
#else
        Eluna::Push(L, unit->AddAura(spellId, target));
#endif
        return 1;
    }

    int RemoveAura(Eluna* /*E*/, lua_State* L, Unit* unit)
    {
        uint32 spellId = Eluna::CHECKVAL<uint32>(L, 2);
        unit->RemoveAurasDueToSpell(spellId);
        return 0;
    }

    int RemoveAllAuras(Eluna* /*E*/, lua_State* /*L*/, Unit* unit)
    {
        unit->RemoveAllAuras();
        return 0;
    }

    int PlayDirectSound(Eluna* /*E*/, lua_State* L, Unit* unit)
    {
        uint32 soundId = Eluna::CHECKVAL<uint32>(L, 2);
        Player* player = Eluna::CHECKOBJ<Player>(L, 3, false);
        if (!sSoundEntriesStore.LookupEntry(soundId))
            return 0;

        if (player)
            unit->PlayDirectSound(soundId, player);
        else
            unit->PlayDirectSound(soundId);
        return 0;
    }

    int PlayDistanceSound(Eluna* /*E*/, lua_State* L, Unit* unit)
    {
        uint32 soundId = Eluna::CHECKVAL<uint32>(L, 2);
        Player* player = Eluna::CHECKOBJ<Player>(L, 3, false);
        if (!sSoundEntriesStore.LookupEntry(soundId))
            return 0;

        if (player)
            unit->PlayDistanceSound(soundId, player);
        else
            unit->PlayDistanceSound(soundId);
        return 0;
    }

    int AddUnitState(Eluna* /*E*/, lua_State* L, Unit* unit)
    {
        uint32 state = Eluna::CHECKVAL<uint32>(L, 2);

#ifndef TRINITY
        unit->addUnitState(state);
#else
        unit->AddUnitState(state);
#endif
        return 0;
    }

    int ClearUnitState(Eluna* /*E*/, lua_State* L, Unit* unit)
    {
        uint32 state = Eluna::CHECKVAL<uint32>(L, 2);

#ifndef TRINITY
        unit->clearUnitState(state);
#else
        unit->ClearUnitState(state);
#endif
        return 0;
    }

    int NearTeleport(Eluna* /*E*/, lua_State* L, Unit* unit)
    {
        float x = Eluna::CHECKVAL<float>(L, 2);
        float y = Eluna::CHECKVAL<float>(L, 3);
        float z = Eluna::CHECKVAL<float>(L, 4);
        float o = Eluna::CHECKVAL<float>(L, 5);

        unit->NearTeleportTo(x, y, z, o);
        return 1;
    }

    /**
     * Makes the [Unit] damage the target [Unit]
     *
     * <pre>
     * enum SpellSchools
     * {
     *     SPELL_SCHOOL_NORMAL  = 0,
     *     SPELL_SCHOOL_HOLY    = 1,
     *     SPELL_SCHOOL_FIRE    = 2,
     *     SPELL_SCHOOL_NATURE  = 3,
     *     SPELL_SCHOOL_FROST   = 4,
     *     SPELL_SCHOOL_SHADOW  = 5,
     *     SPELL_SCHOOL_ARCANE  = 6,
     *     MAX_SPELL_SCHOOL     = 7
     * };
     * </pre>
     *
     * @param [Unit] target : [Unit] to damage
     * @param uint32 damage : amount to damage
     * @param bool durabilityloss = true : if false, the damage does not do durability damage
     * @param [SpellSchools] school = MAX_SPELL_SCHOOL : school the damage is done in or MAX_SPELL_SCHOOL for direct damage
     * @param uint32 spell = 0 : spell that inflicts the damage
     */
    int DealDamage(Eluna* /*E*/, lua_State* L, Unit* unit)
    {
        Unit* target = Eluna::CHECKOBJ<Unit>(L, 2);
        uint32 damage = Eluna::CHECKVAL<uint32>(L, 3);
        bool durabilityloss = Eluna::CHECKVAL<bool>(L, 4, true);
        uint32 school = Eluna::CHECKVAL<uint32>(L, 5, MAX_SPELL_SCHOOL);
        uint32 spell = Eluna::CHECKVAL<uint32>(L, 6, 0);
        if (school > MAX_SPELL_SCHOOL)
            return luaL_argerror(L, 6, "valid SpellSchool expected");

        // flat melee damage without resistence/etc reduction
        if (school == MAX_SPELL_SCHOOL)
        {
            unit->DealDamage(target, damage, NULL, DIRECT_DAMAGE, SPELL_SCHOOL_MASK_NORMAL, NULL, durabilityloss);
#ifdef TRINITY
            unit->SendAttackStateUpdate(HITINFO_AFFECTS_VICTIM, target, 1, SPELL_SCHOOL_MASK_NORMAL, damage, 0, 0, VICTIMSTATE_HIT, 0);
#else
            unit->SendAttackStateUpdate(HITINFO_NORMALSWING2, target, 1, SPELL_SCHOOL_MASK_NORMAL, damage, 0, 0, VICTIMSTATE_NORMAL, 0);
#endif
            return 0;
        }

        SpellSchoolMask schoolmask = SpellSchoolMask(1 << school);

#ifdef TRINITY
        if (Unit::IsDamageReducedByArmor(schoolmask))
            damage = unit->CalcArmorReducedDamage(target, damage, NULL, BASE_ATTACK);
#else
        if (schoolmask & SPELL_SCHOOL_MASK_NORMAL)
            damage = unit->CalcArmorReducedDamage(target, damage);
#endif

        // melee damage by specific school
        if (!spell)
        {
            uint32 absorb = 0;
            uint32 resist = 0;
#ifdef TRINITY
            unit->CalcAbsorbResist(target, schoolmask, SPELL_DIRECT_DAMAGE, damage, &absorb, &resist);
#else
            target->CalculateDamageAbsorbAndResist(unit, schoolmask, SPELL_DIRECT_DAMAGE, damage, &absorb, &resist);
#endif

            if (damage <= absorb + resist)
                damage = 0;
            else
                damage -= absorb + resist;

            unit->DealDamageMods(target, damage, &absorb);
            unit->DealDamage(target, damage, NULL, DIRECT_DAMAGE, schoolmask, NULL, false);
#ifdef TRINITY
            unit->SendAttackStateUpdate(HITINFO_AFFECTS_VICTIM, target, 1, schoolmask, damage, absorb, resist, VICTIMSTATE_HIT, 0);
#else
            unit->SendAttackStateUpdate(HITINFO_NORMALSWING2, target, 1, schoolmask, damage, absorb, resist, VICTIMSTATE_NORMAL, 0);
#endif
            return 0;
        }

        // non-melee damage
        unit->SpellNonMeleeDamageLog(target, spell, damage);
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
    int DealHeal(Eluna* /*E*/, lua_State* L, Unit* unit)
    {
        Unit* target = Eluna::CHECKOBJ<Unit>(L, 2);
        uint32 spell = Eluna::CHECKVAL<uint32>(L, 3);
        uint32 amount = Eluna::CHECKVAL<uint32>(L, 4);
        bool critical = Eluna::CHECKVAL<bool>(L, 5, false);

#ifndef TRINITY
        if (const SpellInfo* info = sSpellStore.LookupEntry(spell))
            unit->DealHeal(target, amount, info, critical);
#else
        if (const SpellInfo* info = sSpellMgr->GetSpellInfo(spell))
            unit->HealBySpell(target, info, amount, critical);
#endif
        return 0;
    }

    /**
     * Makes the [Unit] kill the target [Unit]
     *
     * @param [Unit] target : [Unit] to kill
     * @param bool durLoss = true : when true, the target's items suffer durability loss
     */
    int Kill(Eluna* /*E*/, lua_State* L, Unit* unit)
    {
        Unit* target = Eluna::CHECKOBJ<Unit>(L, 2);
        bool durLoss = Eluna::CHECKVAL<bool>(L, 3, true);

#ifndef TRINITY
        unit->DealDamage(target, target->GetHealth(), NULL, DIRECT_DAMAGE, SPELL_SCHOOL_MASK_NORMAL, NULL, durLoss);
#else
        unit->Kill(target, durLoss);
#endif
        return 0;
    }

    /**
     * Adds threat to the [Unit] from the victim.
     *
     * <pre>
     * enum SpellSchoolMask
     * {
     *     SPELL_SCHOOL_MASK_NONE    = 0,
     *     SPELL_SCHOOL_MASK_NORMAL  = 1,
     *     SPELL_SCHOOL_MASK_HOLY    = 2,
     *     SPELL_SCHOOL_MASK_FIRE    = 4,
     *     SPELL_SCHOOL_MASK_NATURE  = 8,
     *     SPELL_SCHOOL_MASK_FROST   = 16,
     *     SPELL_SCHOOL_MASK_SHADOW  = 32,
     *     SPELL_SCHOOL_MASK_ARCANE  = 64,
     * }
     * </pre>
     *
     * @param [Unit] victim : [Unit] that caused the threat
     * @param float threat : threat amount
     * @param [SpellSchoolMask] schoolMask = 0 : [SpellSchoolMask] of the threat causer
     * @param uint32 spell = 0 : spell entry used for threat
     */
    int AddThreat(Eluna* /*E*/, lua_State* L, Unit* unit)
    {
        Unit* victim = Eluna::CHECKOBJ<Unit>(L, 2);
        float threat = Eluna::CHECKVAL<float>(L, 3, true);
        uint32 schoolMask = Eluna::CHECKVAL<uint32>(L, 3, 0);
        uint32 spell = Eluna::CHECKVAL<uint32>(L, 3, 0);

        if (schoolMask > SPELL_SCHOOL_MASK_ALL)
        {
            return luaL_argerror(L, 3, "valid SpellSchoolMask expected");
        }

#ifdef TRINITY
        unit->AddThreat(victim, threat, (SpellSchoolMask)schoolMask, spell ? sSpellMgr->GetSpellInfo(spell) : NULL);
#else
        unit->AddThreat(victim, threat, false, (SpellSchoolMask)schoolMask, spell ? sSpellStore.LookupEntry(spell) : NULL);
#endif
        return 0;
    }

    /*int RestoreDisplayId(Eluna* E, lua_State* L, Unit* unit)
    {
    unit->RestoreDisplayId();
    return 0;
    }*/

    /*int RestoreFaction(Eluna* E, lua_State* L, Unit* unit)
    {
    unit->RestoreFaction();
    return 0;
    }*/

    /*int RemoveBindSightAuras(Eluna* E, lua_State* L, Unit* unit)
    {
    unit->RemoveBindSightAuras();
    return 0;
    }*/

    /*int RemoveCharmAuras(Eluna* E, lua_State* L, Unit* unit)
    {
    unit->RemoveCharmAuras();
    return 0;
    }*/

    /*int DisableMelee(Eluna* E, lua_State* L, Unit* unit)
    {
    bool apply = Eluna::CHECKVAL<bool>(L, 2, true);

    if (apply)
    unit->AddUnitState(UNIT_STATE_CANNOT_AUTOATTACK);
    else
    unit->ClearUnitState(UNIT_STATE_CANNOT_AUTOATTACK);
    return 0;
    }*/

    /*int SummonGuardian(Eluna* E, lua_State* L, Unit* unit)
    {
    uint32 entry = Eluna::CHECKVAL<uint32>(L, 2);
    float x = Eluna::CHECKVAL<float>(L, 3);
    float y = Eluna::CHECKVAL<float>(L, 4);
    float z = Eluna::CHECKVAL<float>(L, 5);
    float o = Eluna::CHECKVAL<float>(L, 6);
    uint32 desp = Eluna::CHECKVAL<uint32>(L, 7, 0);

    SummonPropertiesEntry const* properties = sSummonPropertiesStore.LookupEntry(61);
    if (!properties)
    return 1;
    Position pos;
    pos.Relocate(x,y,z,o);
    TempSummon* summon = unit->GetMap()->SummonCreature(entry, pos, properties, desp, unit);

    if (!summon)
    return 1;

    if (summon->HasUnitTypeMask(UNIT_MASK_GUARDIAN))
    ((Guardian*)summon)->InitStatsForLevel(unit->getLevel());

    if (properties && properties->Category == SUMMON_CATEGORY_ALLY)
    summon->setFaction(unit->getFaction());
    if (summon->GetEntry() == 27893)
    {
    if (uint32 weapon = unit->GetUInt32Value(PLAYER_VISIBLE_ITEM_16_ENTRYID))
    {
    summon->SetDisplayId(11686);
    summon->SetUInt32Value(UNIT_VIRTUAL_ITEM_SLOT_ID, weapon);
    }
    else
    summon->SetDisplayId(1126);
    }
    summon->AI()->EnterEvadeMode();

    Eluna::Push(L, summon);
    return 1;
    }*/
};
#endif
