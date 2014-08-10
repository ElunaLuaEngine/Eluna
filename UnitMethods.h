/*
* Copyright (C) 2010 - 2014 Eluna Lua Engine <http://emudevs.com/>
* This program is free software licensed under GPL version 3
* Please see the included DOCS/LICENSE.md for more information
*/

#ifndef UNITMETHODS_H
#define UNITMETHODS_H

namespace LuaUnit
{
    /* BOOLEAN */
    int Attack(lua_State* L, Unit* unit)
    {
        Unit* who = Eluna::CHECKOBJ<Unit>(L, 2);
        bool meleeAttack = Eluna::CHECKVAL<bool>(L, 3, false);

        Eluna::Push(L, unit->Attack(who, meleeAttack));
        return 1;
    }

    int AttackStop(lua_State* L, Unit* unit)
    {
        Eluna::Push(L, unit->AttackStop());
        return 1;
    }

    int IsStandState(lua_State* L, Unit* unit)
    {
        Eluna::Push(L, unit->IsStandState());
        return 1;
    }

    int IsMounted(lua_State* L, Unit* unit)
    {
        Eluna::Push(L, unit->IsMounted());
        return 1;
    }

    int IsWithinLoS(lua_State* L, Unit* unit)
    {
        float x = Eluna::CHECKVAL<float>(L, 2);
        float y = Eluna::CHECKVAL<float>(L, 3);
        float z = Eluna::CHECKVAL<float>(L, 4);

        Eluna::Push(L, unit->IsWithinLOS(x, y, z));
        return 1;
    }

    int IsRooted(lua_State* L, Unit* unit)
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

    int IsFullHealth(lua_State* L, Unit* unit)
    {
        Eluna::Push(L, unit->IsFullHealth());
        return 1;
    }

    int IsWithinDistInMap(lua_State* L, Unit* unit)
    {
        WorldObject* obj = Eluna::CHECKOBJ<WorldObject>(L, 2);
        float radius = Eluna::CHECKVAL<float>(L, 3);

        Eluna::Push(L, unit->IsWithinDistInMap(obj, radius));
        return 1;
    }

    int IsInAccessiblePlaceFor(lua_State* L, Unit* unit)
    {
        Creature* creature = Eluna::CHECKOBJ<Creature>(L, 2);

#ifndef TRINITY
        Eluna::Push(L, unit->isInAccessablePlaceFor(creature));
#else
        Eluna::Push(L, unit->isInAccessiblePlaceFor(creature));
#endif
        return 1;
    }

    int IsAuctioneer(lua_State* L, Unit* unit)
    {
#ifndef TRINITY
        Eluna::Push(L, unit->isAuctioner());
#else
        Eluna::Push(L, unit->IsAuctioner());
#endif
        return 1;
    }

    int IsGuildMaster(lua_State* L, Unit* unit)
    {
#ifdef CMANGOS
        Eluna::Push(L, unit->isGuildMaster());
#else
        Eluna::Push(L, unit->IsGuildMaster());
#endif
        return 1;
    }

    int IsInnkeeper(lua_State* L, Unit* unit)
    {
#ifdef CMANGOS
        Eluna::Push(L, unit->isInnkeeper());
#else
        Eluna::Push(L, unit->IsInnkeeper());
#endif
        return 1;
    }

    int IsTrainer(lua_State* L, Unit* unit)
    {
#ifdef CMANGOS
        Eluna::Push(L, unit->isTrainer());
#else
        Eluna::Push(L, unit->IsTrainer());
#endif
        return 1;
    }

    int IsGossip(lua_State* L, Unit* unit)
    {
#ifdef CMANGOS
        Eluna::Push(L, unit->isGossip());
#else
        Eluna::Push(L, unit->IsGossip());
#endif
        return 1;
    }

    int IsTaxi(lua_State* L, Unit* unit)
    {
#ifdef CMANGOS
        Eluna::Push(L, unit->isTaxi());
#else
        Eluna::Push(L, unit->IsTaxi());
#endif
        return 1;
    }

    int IsSpiritHealer(lua_State* L, Unit* unit)
    {
#ifdef CMANGOS
        Eluna::Push(L, unit->isSpiritHealer());
#else
        Eluna::Push(L, unit->IsSpiritHealer());
#endif
        return 1;
    }

    int IsSpiritGuide(lua_State* L, Unit* unit)
    {
#ifdef CMANGOS
        Eluna::Push(L, unit->isSpiritGuide());
#else
        Eluna::Push(L, unit->IsSpiritGuide());
#endif
        return 1;
    }

    int IsTabardDesigner(lua_State* L, Unit* unit)
    {
#ifdef CMANGOS
        Eluna::Push(L, unit->isTabardDesigner());
#else
        Eluna::Push(L, unit->IsTabardDesigner());
#endif
        return 1;
    }

    int IsServiceProvider(lua_State* L, Unit* unit)
    {
#ifdef CMANGOS
        Eluna::Push(L, unit->isServiceProvider());
#else
        Eluna::Push(L, unit->IsServiceProvider());
#endif
        return 1;
    }

    int IsSpiritService(lua_State* L, Unit* unit)
    {
#ifdef CMANGOS
        Eluna::Push(L, unit->isSpiritService());
#else
        Eluna::Push(L, unit->IsSpiritService());
#endif
        return 1;
    }

    int IsAlive(lua_State* L, Unit* unit)
    {
#ifdef CMANGOS
        Eluna::Push(L, unit->isAlive());
#else
        Eluna::Push(L, unit->IsAlive());
#endif
        return 1;
    }

    int IsDead(lua_State* L, Unit* unit)
    {
#ifdef MANGOS
        Eluna::Push(L, unit->IsDead());
#else
        Eluna::Push(L, unit->isDead());
#endif
        return 1;
    }

    int IsDying(lua_State* L, Unit* unit)
    {
#ifdef MANGOS
        Eluna::Push(L, unit->IsDying());
#else
        Eluna::Push(L, unit->isDying());
#endif
        return 1;
    }

    int IsBanker(lua_State* L, Unit* unit)
    {
#ifdef CMANGOS
        Eluna::Push(L, unit->isBanker());
#else
        Eluna::Push(L, unit->IsBanker());
#endif
        return 1;
    }

    int IsVendor(lua_State* L, Unit* unit)
    {
#ifdef CMANGOS
        Eluna::Push(L, unit->isVendor());
#else
        Eluna::Push(L, unit->IsVendor());
#endif
        return 1;
    }

    int IsBattleMaster(lua_State* L, Unit* unit)
    {
#ifdef CMANGOS
        Eluna::Push(L, unit->isBattleMaster());
#else
        Eluna::Push(L, unit->IsBattleMaster());
#endif
        return 1;
    }

    int IsCharmed(lua_State* L, Unit* unit)
    {
#ifdef CMANGOS
        Eluna::Push(L, unit->isCharmed());
#else
        Eluna::Push(L, unit->IsCharmed());
#endif
        return 1;
    }

    int IsArmorer(lua_State* L, Unit* unit)
    {
#ifdef CMANGOS
        Eluna::Push(L, unit->isArmorer());
#else
        Eluna::Push(L, unit->IsArmorer());
#endif
        return 1;
    }

    int IsAttackingPlayer(lua_State* L, Unit* unit)
    {
        Eluna::Push(L, unit->isAttackingPlayer());
        return 1;
    }

    int IsPvPFlagged(lua_State* L, Unit* unit)
    {
        Eluna::Push(L, unit->IsPvP());
        return 1;
    }

#ifndef CLASSIC
    int IsOnVehicle(lua_State* L, Unit* unit)
    {
#ifndef TRINITY
        Eluna::Push(L, unit->IsBoarded());
#else
        Eluna::Push(L, unit->GetVehicle());
#endif
        return 1;
    }
#endif

    int IsInCombat(lua_State* L, Unit* unit)
    {
#ifdef CMANGOS
        Eluna::Push(L, unit->isInCombat());
#else
        Eluna::Push(L, unit->IsInCombat());
#endif
        return 1;
    }

    int IsUnderWater(lua_State* L, Unit* unit)
    {
        Eluna::Push(L, unit->IsUnderWater());
        return 1;
    }

    int IsInWater(lua_State* L, Unit* unit)
    {
        Eluna::Push(L, unit->IsInWater());
        return 1;
    }

    int IsStopped(lua_State* L, Unit* unit)
    {
        Eluna::Push(L, unit->IsStopped());
        return 1;
    }

    int IsQuestGiver(lua_State* L, Unit* unit)
    {
#ifdef CMANGOS
        Eluna::Push(L, unit->isQuestGiver());
#else
        Eluna::Push(L, unit->IsQuestGiver());
#endif
        return 1;
    }

    int HealthBelowPct(lua_State* L, Unit* unit)
    {
        Eluna::Push(L, unit->HealthBelowPct(Eluna::CHECKVAL<int32>(L, 2)));
        return 1;
    }

    int HealthAbovePct(lua_State* L, Unit* unit)
    {
        Eluna::Push(L, unit->HealthAbovePct(Eluna::CHECKVAL<int32>(L, 2)));
        return 1;
    }

    int HasAura(lua_State* L, Unit* unit)
    {
        uint32 spell = Eluna::CHECKVAL<uint32>(L, 2);

        Eluna::Push(L, unit->HasAura(spell));
        return 1;
    }

    int HasUnitState(lua_State* L, Unit* unit)
    {
        uint32 state = Eluna::CHECKVAL<uint32>(L, 2);
#ifndef TRINITY
        Eluna::Push(L, unit->hasUnitState(state));
#else
        Eluna::Push(L, unit->HasUnitState(state));
#endif
        return 1;
    }

    /*int IsVisible(lua_State* L, Unit* unit)
    {
    Eluna::Push(L, unit->IsVisible());
    return 1;
    }*/

    /*int IsMoving(lua_State* L, Unit* unit)
    {
    Eluna::Push(L, unit->isMoving());
    return 1;
    }*/

    /*int IsFlying(lua_State* L, Unit* unit)
    {
    Eluna::Push(L, unit->IsFlying());
    return 1;
    }*/

    /* GETTERS */
    int GetOwner(lua_State* L, Unit* unit)
    {
        Eluna::Push(L, unit->GetOwner());
        return 1;
    }

    int GetOwnerGUID(lua_State* L, Unit* unit)
    {
#ifndef TRINITY
        Eluna::Push(L, unit->GetOwnerGuid());
#else
        Eluna::Push(L, unit->GetOwnerGUID());
#endif
        return 1;
    }

    int GetMountId(lua_State* L, Unit* unit)
    {
        Eluna::Push(L, unit->GetMountID());
        return 1;
    }

    int GetCreatorGUID(lua_State* L, Unit* unit)
    {
#ifndef TRINITY
        Eluna::Push(L, unit->GetCreatorGuid());
#else
        Eluna::Push(L, unit->GetCreatorGUID());
#endif
        return 1;
    }

    int GetMinionGUID(lua_State* L, Unit* unit)
    {
#ifndef TRINITY
        Eluna::Push(L, unit->GetPetGuid());
#else
        Eluna::Push(L, unit->GetPetGUID());
#endif
        return 1;
    }

    int GetCharmerGUID(lua_State* L, Unit* unit)
    {
#ifndef TRINITY
        Eluna::Push(L, unit->GetCharmerGuid());
#else
        Eluna::Push(L, unit->GetCharmerGUID());
#endif
        return 1;
    }

    int GetCharmGUID(lua_State* L, Unit* unit)
    {
#ifndef TRINITY
        Eluna::Push(L, unit->GetCharmGuid());
#else
        Eluna::Push(L, unit->GetCharmGUID());
#endif
        return 1;
    }

    int GetPetGUID(lua_State* L, Unit* unit)
    {
#ifndef TRINITY
        Eluna::Push(L, unit->GetPetGuid());
#else
        Eluna::Push(L, unit->GetPetGUID());
#endif
        return 1;
    }

    int GetControllerGUID(lua_State* L, Unit* unit)
    {
#ifndef TRINITY
        Eluna::Push(L, unit->GetCharmerOrOwnerGuid());
#else
        Eluna::Push(L, unit->GetCharmerOrOwnerGUID());
#endif
        return 1;
    }

    int GetControllerGUIDS(lua_State* L, Unit* unit)
    {
#ifndef TRINITY
        Eluna::Push(L, unit->GetCharmerOrOwnerOrOwnGuid());
#else
        Eluna::Push(L, unit->GetCharmerOrOwnerOrOwnGUID());
#endif
        return 1;
    }

    int GetStat(lua_State* L, Unit* unit)
    {
        uint32 stat = Eluna::CHECKVAL<uint32>(L, 2);

        if (stat >= MAX_STATS)
            return 1;

        Eluna::Push(L, unit->GetStat((Stats)stat));
        return 1;
    }

    int GetBaseSpellPower(lua_State* L, Unit* unit)
    {
        uint32 spellschool = Eluna::CHECKVAL<uint32>(L, 2);

        if (spellschool >= MAX_SPELL_SCHOOL)
            return 1;

        Eluna::Push(L, unit->GetUInt32Value(PLAYER_FIELD_MOD_DAMAGE_DONE_POS + spellschool));
        return 1;
    }

    int GetVictim(lua_State* L, Unit* unit)
    {
#ifndef TRINITY
        Eluna::Push(L, unit->getVictim());
#else
        Eluna::Push(L, unit->GetVictim());
#endif
        return 1;
    }

    int GetCurrentSpell(lua_State* L, Unit* unit)
    {
        uint32 type = Eluna::CHECKVAL<uint32>(L, 2);
        if (type >= CURRENT_MAX_SPELL)
            return luaL_argerror(L, 2, "valid CurrentSpellTypes expected");
        Eluna::Push(L, unit->GetCurrentSpell(type));
        return 1;
    }

    int GetStandState(lua_State* L, Unit* unit)
    {
        Eluna::Push(L, unit->getStandState());
        return 0;
    }

    int GetDisplayId(lua_State* L, Unit* unit)
    {
        Eluna::Push(L, unit->GetDisplayId());
        return 1;
    }

    int GetNativeDisplayId(lua_State* L, Unit* unit)
    {
        Eluna::Push(L, unit->GetNativeDisplayId());
        return 1;
    }

    int GetLevel(lua_State* L, Unit* unit)
    {
        Eluna::Push(L, unit->getLevel());
        return 1;
    }

    int GetHealth(lua_State* L, Unit* unit)
    {
        Eluna::Push(L, unit->GetHealth());
        return 1;
    }

    Powers PowerSelectorHelper(lua_State* L, Unit* unit, int powerType = -1)
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

    int GetPower(lua_State* L, Unit* unit)
    {
        int type = Eluna::CHECKVAL<int>(L, 2, -1);
        Powers power = PowerSelectorHelper(L, unit, type);

        Eluna::Push(L, unit->GetPower(power));
        return 1;
    }

    int GetMaxPower(lua_State* L, Unit* unit)
    {
        int type = Eluna::CHECKVAL<int>(L, 2, -1);
        Powers power = PowerSelectorHelper(L, unit, type);

        Eluna::Push(L, unit->GetMaxPower(power));
        return 1;
    }

    int GetPowerPct(lua_State* L, Unit* unit)
    {
        int type = Eluna::CHECKVAL<int>(L, 2, -1);
        Powers power = PowerSelectorHelper(L, unit, type);

#if (!defined(TRINITY) && defined(WOTLK))
        float percent = ((float)unit->GetPower(power) / (float)unit->GetMaxPower(power)) * 100.0f;
#else
        float percent = ((float)unit->GetPower(power) / (float)unit->GetMaxPower(power)) * 100.0f;
#endif
        Eluna::Push(L, percent);
        return 1;
    }

    int GetPowerType(lua_State* L, Unit* unit)
    {
#ifdef TRINITY
        Eluna::Push(L, unit->getPowerType());
#else
        Eluna::Push(L, unit->GetPowerType());
#endif
        return 1;
    }

    int GetMaxHealth(lua_State* L, Unit* unit)
    {
        Eluna::Push(L, unit->GetMaxHealth());
        return 1;
    }

    int GetHealthPct(lua_State* L, Unit* unit)
    {
#ifndef TRINITY
        Eluna::Push(L, unit->GetHealthPercent());
#else
        Eluna::Push(L, unit->GetHealthPct());
#endif
        return 1;
    }

    int GetGender(lua_State* L, Unit* unit)
    {
        Eluna::Push(L, unit->getGender());
        return 1;
    }

    int GetRace(lua_State* L, Unit* unit)
    {
        Eluna::Push(L, unit->getRace());
        return 1;
    }

    int GetClass(lua_State* L, Unit* unit)
    {
        Eluna::Push(L, unit->getClass());
        return 1;
    }

    int GetCreatureType(lua_State* L, Unit* unit)
    {
        Eluna::Push(L, unit->GetCreatureType());
        return 1;
    }

    int GetClassAsString(lua_State* L, Unit* unit)
    {
        const char* str = NULL;
        switch (unit->getClass())
        {
        case 1:
            str = "Warrior";
            break;
        case 2:
            str = "Paladin";
            break;
        case 3:
            str = "Hunter";
            break;
        case 4:
            str = "Rogue";
            break;
        case 5:
            str = "Priest";
            break;
        case 6:
            str = "Death Knight";
            break;
        case 7:
            str = "Shaman";
            break;
        case 8:
            str = "Mage";
            break;
        case 9:
            str = "Warlock";
            break;
        case 11:
            str = "Druid";
            break;
        default:
            str = NULL;
            break;
        }

        Eluna::Push(L, str);
        return 1;
    }

    int GetFaction(lua_State* L, Unit* unit)
    {
        Eluna::Push(L, unit->getFaction());
        return 1;
    }

    int GetAura(lua_State* L, Unit* unit)
    {
        uint32 spellID = Eluna::CHECKVAL<uint32>(L, 2);
#ifndef TRINITY
        Eluna::Push(L, unit->GetAura(spellID, EFFECT_INDEX_0));
#else
        Eluna::Push(L, unit->GetAura(spellID));
#endif
        return 1;
    }

    int GetCombatTime(lua_State* L, Unit* unit)
    {
        Eluna::Push(L, unit->GetCombatTimer());
        return 1;
    }

    int GetFriendlyUnitsInRange(lua_State* L, Unit* unit)
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

    int GetUnfriendlyUnitsInRange(lua_State* L, Unit* unit)
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
    int GetVehicleKit(lua_State* L, Unit* unit)
    {
#ifndef TRINITY
        Eluna::Push(L, unit->GetVehicleInfo());
#else
        Eluna::Push(L, unit->GetVehicleKit());
#endif
        return 1;
    }

    /*
    int GetVehicle(lua_State* L, Unit* unit)
    {
    Eluna::Push(L, unit->GetVehicle());
    return 1;
    }
    */

    int GetCritterGUID(lua_State* L, Unit* unit)
    {
#ifndef TRINITY
        Eluna::Push(L, unit->GetCritterGuid());
#else
        Eluna::Push(L, unit->GetCritterGUID());
#endif
        return 1;
    }
#endif

    /* SETTERS */
    int SetOwnerGUID(lua_State* L, Unit* unit)
    {
        uint64 guid = Eluna::CHECKVAL<uint64>(L, 2);

#ifndef TRINITY
        unit->SetOwnerGuid(ObjectGuid(guid));
#else
        unit->SetOwnerGUID(ObjectGuid(guid));
#endif
        return 0;
    }

    int SetPvP(lua_State* L, Unit* unit)
    {
        bool apply = Eluna::CHECKVAL<bool>(L, 2, true);

        unit->SetPvP(apply);
        return 0;
    }

    int SetSheath(lua_State* L, Unit* unit)
    {
        uint32 sheathed = Eluna::CHECKVAL<uint32>(L, 2);
        if (sheathed >= MAX_SHEATH_STATE)
            return luaL_argerror(L, 2, "valid SheathState expected");

        unit->SetSheath((SheathState)sheathed);
        return 0;
    }

    int SetName(lua_State* L, Unit* unit)
    {
        const char* name = Eluna::CHECKVAL<const char*>(L, 2);
        if (std::string(name).length() > 0)
            unit->SetName(name);
        return 0;
    }

    int SetSpeed(lua_State* L, Unit* unit)
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

    int SetFaction(lua_State* L, Unit* unit)
    {
        uint32 factionId = Eluna::CHECKVAL<uint32>(L, 2);
        unit->setFaction(factionId);
        return 0;
    }

    int SetLevel(lua_State* L, Unit* unit)
    {
        uint32 newLevel = Eluna::CHECKVAL<uint32>(L, 2);
        unit->SetLevel(newLevel);
        return 0;
    }

    int SetHealth(lua_State* L, Unit* unit)
    {
        uint32 amt = Eluna::CHECKVAL<uint32>(L, 2);
        unit->SetHealth(amt);
        return 0;
    }

    int SetMaxHealth(lua_State* L, Unit* unit)
    {
        uint32 amt = Eluna::CHECKVAL<uint32>(L, 2);
        unit->SetMaxHealth(amt);
        return 0;
    }

    int SetPower(lua_State* L, Unit* unit)
    {
        int type = Eluna::CHECKVAL<int>(L, 2, -1);
        uint32 amt = Eluna::CHECKVAL<uint32>(L, 3);
        Powers power = PowerSelectorHelper(L, unit, type);

        unit->SetPower(power, amt);
        return 0;
    }

    int SetMaxPower(lua_State* L, Unit* unit)
    {
        int type = Eluna::CHECKVAL<int>(L, 2, -1);
        uint32 amt = Eluna::CHECKVAL<uint32>(L, 3);
        Powers power = PowerSelectorHelper(L, unit, type);

        unit->SetMaxPower(power, amt);
        return 0;
    }

    int SetPowerType(lua_State* L, Unit* unit)
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

    int SetDisplayId(lua_State* L, Unit* unit)
    {
        uint32 model = Eluna::CHECKVAL<uint32>(L, 2);
        unit->SetDisplayId(model);
        return 0;
    }

    int SetNativeDisplayId(lua_State* L, Unit* unit)
    {
        uint32 model = Eluna::CHECKVAL<uint32>(L, 2);
        unit->SetNativeDisplayId(model);
        return 0;
    }

    int SetFacing(lua_State* L, Unit* unit)
    {
        float o = Eluna::CHECKVAL<float>(L, 2);
        unit->SetFacingTo(o);
        return 0;
    }

    int SetFacingToObject(lua_State* L, Unit* unit)
    {
        WorldObject* obj = Eluna::CHECKOBJ<WorldObject>(L, 2);
        unit->SetFacingToObject(obj);
        return 0;
    }

    int SetCreatorGUID(lua_State* L, Unit* unit)
    {
        uint64 guid = Eluna::CHECKVAL<uint64>(L, 2);
#ifndef TRINITY
        unit->SetOwnerGuid(ObjectGuid(guid));
#else
        unit->SetOwnerGUID(ObjectGuid(guid));
#endif
        return 0;
    }

    int SetMinionGUID(lua_State* L, Unit* unit)
    {
        uint64 guid = Eluna::CHECKVAL<uint64>(L, 2);
#ifndef TRINITY
        unit->SetPetGuid(ObjectGuid(guid));
#else
        unit->SetMinionGUID(ObjectGuid(guid));
#endif
        return 0;
    }

    int SetCharmerGUID(lua_State* L, Unit* unit)
    {
        uint64 guid = Eluna::CHECKVAL<uint64>(L, 2);
#ifndef TRINITY
        unit->SetCharmerGuid(ObjectGuid(guid));
#else
        unit->SetCharmerGUID(ObjectGuid(guid));
#endif
        return 0;
    }

    int SetPetGUID(lua_State* L, Unit* unit)
    {
        uint64 guid = Eluna::CHECKVAL<uint64>(L, 2);
#ifndef TRINITY
        unit->SetPetGuid(ObjectGuid(guid));
#else
        unit->SetPetGUID(ObjectGuid(guid));
#endif
        return 0;
    }

    int SetWaterWalk(lua_State* L, Unit* unit)
    {
        bool enable = Eluna::CHECKVAL<bool>(L, 2, true);
#ifndef TRINITY
        unit->SetWaterWalk(enable);
#else
        unit->SetWaterWalking(enable);
#endif
        return 0;
    }

    int SetStandState(lua_State* L, Unit* unit)
    {
        uint8 state = Eluna::CHECKVAL<uint8>(L, 2);
        unit->SetStandState(state);
        return 0;
    }

#if (!defined(TBC) && !defined(CLASSIC))
    int SetFFA(lua_State* L, Unit* unit)
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

    int SetSanctuary(lua_State* L, Unit* unit)
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

    int SetPhaseMask(lua_State* L, Unit* unit)
    {
        uint32 phaseMask = Eluna::CHECKVAL<uint32>(L, 2);
        bool Update = Eluna::CHECKVAL<bool>(L, 3, true);
        unit->SetPhaseMask(phaseMask, Update);
        return 0;
    }

    int SetCritterGUID(lua_State* L, Unit* unit)
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

    /*int SetStunned(lua_State* L, Unit* unit)
    {
    bool apply = Eluna::CHECKVAL<bool>(L, 2, true);
    unit->SetControlled(apply, UNIT_STATE_STUNNED);
    return 0;
    }*/

    /*int SetRooted(lua_State* L, Unit* unit)
    {
    bool apply = Eluna::CHECKVAL<bool>(L, 2, true);
    unit->SetControlled(apply, UNIT_STATE_ROOT);
    return 0;
    }*/

    /*int SetConfused(lua_State* L, Unit* unit)
    {
    bool apply = Eluna::CHECKVAL<bool>(L, 2, true);
    unit->SetControlled(apply, UNIT_STATE_CONFUSED);
    return 0;
    }*/

    /*int SetFeared(lua_State* L, Unit* unit)
    {
    bool apply = Eluna::CHECKVAL<bool>(L, 2, true);
    unit->SetControlled(apply, UNIT_STATE_FLEEING);
    return 0;
    }*/

    /*int SetCanFly(lua_State* L, Unit* unit)
    {
    bool apply = Eluna::CHECKVAL<bool>(L, 2, true);
    unit->SetCanFly(apply);
    return 0;
    }*/

    /*int SetVisible(lua_State* L, Unit* unit)
    {
    bool x = Eluna::CHECKVAL<bool>(L, 2, true);
    unit->SetVisible(x);
    return 0;
    }*/

    /* OTHER */
    int ClearThreatList(lua_State* /*L*/, Unit* unit)
    {
#ifdef MANGOS
        unit->GetThreatManager().clearReferences();
#else
        unit->getThreatManager().clearReferences();
#endif
        return 0;
    }

    int Mount(lua_State* L, Unit* unit)
    {
        uint32 displayId = Eluna::CHECKVAL<uint32>(L, 2);

        unit->Mount(displayId);
        return 0;
    }

    int Dismount(lua_State* /*L*/, Unit* unit)
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

    int Emote(lua_State* L, Unit* unit)
    {
        unit->HandleEmoteCommand(Eluna::CHECKVAL<uint32>(L, 2));
        return 0;
    }

    int CountPctFromCurHealth(lua_State* L, Unit* unit)
    {
        Eluna::Push(L, unit->CountPctFromCurHealth(Eluna::CHECKVAL<int32>(L, 2)));
        return 1;
    }

    int CountPctFromMaxHealth(lua_State* L, Unit* unit)
    {
        Eluna::Push(L, unit->CountPctFromMaxHealth(Eluna::CHECKVAL<int32>(L, 2)));
        return 1;
    }

    int SendChatMessageToPlayer(lua_State* L, Unit* unit)
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

    int MoveStop(lua_State* /*L*/, Unit* unit)
    {
        unit->StopMoving();
        return 0;
    }

    int MoveExpire(lua_State* L, Unit* unit)
    {
        bool reset = Eluna::CHECKVAL<bool>(L, 2, true);
        unit->GetMotionMaster()->MovementExpired(reset);
        return 0;
    }

    int MoveClear(lua_State* L, Unit* unit)
    {
        bool reset = Eluna::CHECKVAL<bool>(L, 2, true);
        unit->GetMotionMaster()->Clear(reset);
        return 0;
    }

    int MoveIdle(lua_State* /*L*/, Unit* unit)
    {
        unit->GetMotionMaster()->MoveIdle();
        return 0;
    }

    int MoveRandom(lua_State* L, Unit* unit)
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

    int MoveHome(lua_State* /*L*/, Unit* unit)
    {
        unit->GetMotionMaster()->MoveTargetedHome();
        return 0;
    }

    int MoveFollow(lua_State* L, Unit* unit)
    {
        Unit* target = Eluna::CHECKOBJ<Unit>(L, 2);
        float dist = Eluna::CHECKVAL<float>(L, 3, 0.0f);
        float angle = Eluna::CHECKVAL<float>(L, 4, 0.0f);
        unit->GetMotionMaster()->MoveFollow(target, dist, angle);
        return 0;
    }

    int MoveChase(lua_State* L, Unit* unit)
    {
        Unit* target = Eluna::CHECKOBJ<Unit>(L, 2);
        float dist = Eluna::CHECKVAL<float>(L, 3, 0.0f);
        float angle = Eluna::CHECKVAL<float>(L, 4, 0.0f);
        unit->GetMotionMaster()->MoveChase(target, dist, angle);
        return 0;
    }

    int MoveConfused(lua_State* /*L*/, Unit* unit)
    {
        unit->GetMotionMaster()->MoveConfused();
        return 0;
    }

    int MoveFleeing(lua_State* L, Unit* unit)
    {
        Unit* target = Eluna::CHECKOBJ<Unit>(L, 2);
        uint32 time = Eluna::CHECKVAL<uint32>(L, 3, 0);
        unit->GetMotionMaster()->MoveFleeing(target, time);
        return 0;
    }

    int MoveTo(lua_State* L, Unit* unit)
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
    int MoveJump(lua_State* L, Unit* unit)
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

    int SendUnitWhisper(lua_State* L, Unit* unit)
    {
        const char* msg = Eluna::CHECKVAL<const char*>(L, 2);
        Player* receiver = Eluna::CHECKOBJ<Player>(L, 3);
        bool bossWhisper = Eluna::CHECKVAL<bool>(L, 4, false);
        if (std::string(msg).length() > 0)
            unit->MonsterWhisper(msg, receiver, bossWhisper);
        return 0;
    }

    int SendUnitEmote(lua_State* L, Unit* unit)
    {
        const char* msg = Eluna::CHECKVAL<const char*>(L, 2);
        Unit* receiver = Eluna::CHECKOBJ<Unit>(L, 3, false);
        bool bossEmote = Eluna::CHECKVAL<bool>(L, 4, false);
        if (std::string(msg).length() > 0)
            unit->MonsterTextEmote(msg, receiver, bossEmote);
        return 0;
    }

    int SendUnitSay(lua_State* L, Unit* unit)
    {
        const char* msg = Eluna::CHECKVAL<const char*>(L, 2);
        uint32 language = Eluna::CHECKVAL<uint32>(L, 3);
        if (std::string(msg).length() > 0)
            unit->MonsterSay(msg, language, unit);
        return 0;
    }

    int SendUnitYell(lua_State* L, Unit* unit)
    {
        const char* msg = Eluna::CHECKVAL<const char*>(L, 2);
        uint32 language = Eluna::CHECKVAL<uint32>(L, 3);
        if (std::string(msg).length() > 0)
            unit->MonsterYell(msg, language, unit);
        return 0;
    }

    int DeMorph(lua_State* /*L*/, Unit* unit)
    {
        unit->DeMorph();
        return 0;
    }

    int CastSpell(lua_State* L, Unit* unit)
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
     * Casts the spell at target with modified basepoints or casters.
     * See also &Unit:CastSpell
     *
     * @param &Unit target
     * @param uint32 spell
     * @param bool triggered = false
     * @param int32 bp0 = nil : modifier for the base points of the spell. If left as nil, no change is made
     * @param int32 bp1 = nil : modifier for the base points of the spell. If left as nil, no change is made
     * @param int32 bp2 = nil : modifier for the base points of the spell. If left as nil, no change is made
     * @param &Item castItem = nil
     * @param uint64 originalCaster = 0
     */
    int CastCustomSpell(lua_State* L, Unit* unit)
    {
        Unit* target = Eluna::CHECKOBJ<Unit>(L, 2);
        uint32 spell = Eluna::CHECKVAL<uint32>(L, 3);
        bool triggered = Eluna::CHECKVAL<bool>(L, 4, false);
        bool has_bp0 = lua_isnoneornil(L, 5);
        int32 bp0 = Eluna::CHECKVAL<int32>(L, 5, 0);
        bool has_bp1 = lua_isnoneornil(L, 6);
        int32 bp1 = Eluna::CHECKVAL<int32>(L, 6, 0);
        bool has_bp2 = lua_isnoneornil(L, 7);
        int32 bp2 = Eluna::CHECKVAL<int32>(L, 7, 0);
        Item* castItem = Eluna::CHECKOBJ<Item>(L, 8, false);
        uint64 originalCaster = Eluna::CHECKVAL<uint64>(L, 9, 0);

        unit->CastCustomSpell(target, spell, has_bp0 ? &bp0 : NULL, has_bp1 ? &bp1 : NULL, has_bp2 ? &bp2 : NULL, triggered, castItem, NULL, ObjectGuid(originalCaster));
        return 0;
    }

    int CastSpellAoF(lua_State* L, Unit* unit)
    {
        float _x = Eluna::CHECKVAL<float>(L, 2);
        float _y = Eluna::CHECKVAL<float>(L, 3);
        float _z = Eluna::CHECKVAL<float>(L, 4);
        uint32 spell = Eluna::CHECKVAL<uint32>(L, 5);
        bool triggered = Eluna::CHECKVAL<bool>(L, 6, true);
        unit->CastSpell(_x, _y, _z, spell, triggered);
        return 0;
    }

    int ClearInCombat(lua_State* /*L*/, Unit* unit)
    {
        unit->ClearInCombat();
        return 0;
    }

    int StopSpellCast(lua_State* L, Unit* unit)
    {
        uint32 spellId = Eluna::CHECKVAL<uint32>(L, 2, 0);
        unit->CastStop(spellId);
        return 0;
    }

    int InterruptSpell(lua_State* L, Unit* unit)
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

    int AddAura(lua_State* L, Unit* unit)
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
            if (IsAreaAuraEffect(eff)           ||
                eff == SPELL_EFFECT_APPLY_AURA  ||
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

    int RemoveAura(lua_State* L, Unit* unit)
    {
        uint32 spellId = Eluna::CHECKVAL<uint32>(L, 2);
        unit->RemoveAurasDueToSpell(spellId);
        return 0;
    }

    int RemoveAllAuras(lua_State* /*L*/, Unit* unit)
    {
        unit->RemoveAllAuras();
        return 0;
    }

    int PlayDirectSound(lua_State* L, Unit* unit)
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

    int PlayDistanceSound(lua_State* L, Unit* unit)
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

    int RegisterEvent(lua_State* L, Unit* unit)
    {
        luaL_checktype(L, 2, LUA_TFUNCTION);
        uint32 delay = Eluna::CHECKVAL<uint32>(L, 3);
        uint32 repeats = Eluna::CHECKVAL<uint32>(L, 4);

        lua_pushvalue(L, 2);
        int functionRef = luaL_ref(L, LUA_REGISTRYINDEX);
        functionRef = sEluna->m_EventMgr->AddEvent(&unit->m_Events, functionRef, delay, repeats, unit);
        if (functionRef)
            Eluna::Push(L, functionRef);
        return 1;
    }

    int RemoveEventById(lua_State* L, Unit* unit)
    {
        int eventId = Eluna::CHECKVAL<int>(L, 2);
        sEluna->m_EventMgr->RemoveEvent(&unit->m_Events, eventId);
        return 0;
    }

    int RemoveEvents(lua_State* /*L*/, Unit* unit)
    {
        sEluna->m_EventMgr->RemoveEvents(&unit->m_Events);
        return 0;
    }

    int AddUnitState(lua_State* L, Unit* unit)
    {
        uint32 state = Eluna::CHECKVAL<uint32>(L, 2);

#ifndef TRINITY
        unit->addUnitState(state);
#else
        unit->AddUnitState(state);
#endif
        return 0;
    }

    int ClearUnitState(lua_State* L, Unit* unit)
    {
        uint32 state = Eluna::CHECKVAL<uint32>(L, 2);

#ifndef TRINITY
        unit->clearUnitState(state);
#else
        unit->ClearUnitState(state);
#endif
        return 0;
    }

    int NearTeleport(lua_State* L, Unit* unit)
    {
        float x = Eluna::CHECKVAL<float>(L, 2);
        float y = Eluna::CHECKVAL<float>(L, 3);
        float z = Eluna::CHECKVAL<float>(L, 4);
        float o = Eluna::CHECKVAL<float>(L, 5);

        unit->NearTeleportTo(x, y, z, o);
        return 1;
    }

    int DealDamage(lua_State* L, Unit* unit)
    {
        Unit* target = Eluna::CHECKOBJ<Unit>(L, 2);
        uint32 amount = Eluna::CHECKVAL<uint32>(L, 3);
        bool durabilityloss = Eluna::CHECKVAL<bool>(L, 4, true);

        unit->DealDamage(target, amount, NULL, DIRECT_DAMAGE, SPELL_SCHOOL_MASK_NORMAL, NULL, durabilityloss);
        return 0;
    }

    int DealHeal(lua_State* L, Unit* unit)
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

    int Kill(lua_State* L, Unit* unit)
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
     * Adds threat to the &Unit from the victim.
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
     * @param &Unit victim : &Unit that caused the threat
     * @param float threat : threat amount
     * @param SpellSchoolMask schoolMask = 0 : spell school mask of the threat causer
     * @param uint32 spell = 0 : spell entry used for threat
     */
    int AddThreat(lua_State* L, Unit* unit)
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

    /*int RestoreDisplayId(lua_State* L, Unit* unit)
    {
    unit->RestoreDisplayId();
    return 0;
    }*/

    /*int RestoreFaction(lua_State* L, Unit* unit)
    {
    unit->RestoreFaction();
    return 0;
    }*/

    /*int RemoveBindSightAuras(lua_State* L, Unit* unit)
    {
    unit->RemoveBindSightAuras();
    return 0;
    }*/

    /*int RemoveCharmAuras(lua_State* L, Unit* unit)
    {
    unit->RemoveCharmAuras();
    return 0;
    }*/

    /*int DisableMelee(lua_State* L, Unit* unit)
    {
    bool apply = Eluna::CHECKVAL<bool>(L, 2, true);

    if (apply)
    unit->AddUnitState(UNIT_STATE_CANNOT_AUTOATTACK);
    else
    unit->ClearUnitState(UNIT_STATE_CANNOT_AUTOATTACK);
    return 0;
    }*/

    /*int SummonGuardian(lua_State* L, Unit* unit)
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
