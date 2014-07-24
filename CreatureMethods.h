/*
* Copyright (C) 2010 - 2014 Eluna Lua Engine <http://emudevs.com/>
* This program is free software licensed under GPL version 3
* Please see the included DOCS/LICENSE.md for more information
*/

#ifndef CREATUREMETHODS_H
#define CREATUREMETHODS_H

namespace LuaCreature
{
    /* BOOLEAN */
    int IsReputationGainDisabled(lua_State* L, Creature* creature)
    {
        Eluna::Push(L, creature->IsReputationGainDisabled());
        return 1;
    }

    int IsRegeneratingHealth(lua_State* L, Creature* creature)
    {
#ifndef TRINITY
        Eluna::Push(L, creature->IsRegeneratingHealth());
#else
        Eluna::Push(L, creature->isRegeneratingHealth());
#endif
        return 1;
    }

    int HasInvolvedQuest(lua_State* L, Creature* creature)
    {
        uint32 quest_id = Eluna::CHECKVAL<uint32>(L, 2);

#ifndef TRINITY
        Eluna::Push(L, creature->HasInvolvedQuest(quest_id));
#else
        Eluna::Push(L, creature->hasInvolvedQuest(quest_id));
#endif
        return 1;
    }

    int IsTargetableForAttack(lua_State* L, Creature* creature)
    {
        bool inversAlive = Eluna::CHECKOBJ<bool>(L, 2);

#ifdef MANGOS
        Eluna::Push(L, creature->IsTargetableForAttack(inversAlive));
#else
        Eluna::Push(L, creature->isTargetableForAttack(inversAlive));
#endif
        return 1;
    }

    int CanAssistTo(lua_State* L, Creature* creature)
    {
        Unit* u = Eluna::CHECKOBJ<Unit>(L, 2);
        Unit* enemy = Eluna::CHECKOBJ<Unit>(L, 3);
        bool checkfaction = Eluna::CHECKVAL<bool>(L, 4, true);

        Eluna::Push(L, creature->CanAssistTo(u, enemy, checkfaction));
        return 1;
    }

    int HasSearchedAssistance(lua_State* L, Creature* creature)
    {
        Eluna::Push(L, creature->HasSearchedAssistance());
        return 1;
    }

    int IsTappedBy(lua_State* L, Creature* creature)
    {
        Player* player = Eluna::CHECKOBJ<Player>(L, 2);

#ifdef MANGOS
        Eluna::Push(L, creature->IsTappedBy(player));
#else
        Eluna::Push(L, creature->isTappedBy(player));
#endif
        return 1;
    }

    int HasLootRecipient(lua_State* L, Creature* creature)
    {
#ifndef TRINITY
        Eluna::Push(L, creature->HasLootRecipient());
#else
        Eluna::Push(L, creature->hasLootRecipient());
#endif
        return 1;
    }

    int IsCombatAllowed(lua_State* L, Creature* creature)
    {
#ifndef TRINITY
        if (CreatureAI* ai = creature->AI())
            Eluna::Push(L, ai->IsCombatMovement());
        else
            Eluna::Push(L, false);
#else
        Eluna::Push(L, !creature->HasReactState(REACT_PASSIVE));
#endif
        return 1;
    }

    int CanSwim(lua_State* L, Creature* creature)
    {
        Eluna::Push(L, creature->CanSwim());
        return 1;
    }

    int CanWalk(lua_State* L, Creature* creature)
    {
        Eluna::Push(L, creature->CanWalk());
        return 1;
    }

    int IsInEvadeMode(lua_State* L, Creature* creature)
    {
        Eluna::Push(L, creature->IsInEvadeMode());
        return 1;
    }

    int IsElite(lua_State* L, Creature* creature)
    {
#ifndef TRINITY
        Eluna::Push(L, creature->IsElite());
#else
        Eluna::Push(L, creature->isElite());
#endif
        return 1;
    }

    int IsGuard(lua_State* L, Creature* creature)
    {
        Eluna::Push(L, creature->IsGuard());
        return 1;
    }

    int IsCivilian(lua_State* L, Creature* creature)
    {
        Eluna::Push(L, creature->IsCivilian());
        return 1;
    }

    int IsRacialLeader(lua_State* L, Creature* creature)
    {
        Eluna::Push(L, creature->IsRacialLeader());
        return 1;
    }

    int IsWorldBoss(lua_State* L, Creature* creature)
    {
#ifndef TRINITY
        Eluna::Push(L, creature->IsWorldBoss());
#else
        Eluna::Push(L, creature->isWorldBoss());
#endif
        return 1;
    }

    int HasCategoryCooldown(lua_State* L, Creature* creature)
    {
        uint32 spell = Eluna::CHECKVAL<uint32>(L, 2);

        Eluna::Push(L, creature->HasCategoryCooldown(spell));
        return 1;
    }

    int HasSpell(lua_State* L, Creature* creature)
    {
        uint32 id = Eluna::CHECKVAL<uint32>(L, 2);

        Eluna::Push(L, creature->HasSpell(id));
        return 1;
    }

    int HasQuest(lua_State* L, Creature* creature)
    {
        uint32 questId = Eluna::CHECKVAL<uint32>(L, 2);

#ifndef TRINITY
        Eluna::Push(L, creature->HasQuest(questId));
#else
        Eluna::Push(L, creature->hasQuest(questId));
#endif
        return 1;
    }

    int HasSpellCooldown(lua_State* L, Creature* creature)
    {
        uint32 spellId = Eluna::CHECKVAL<uint32>(L, 2);

        Eluna::Push(L, creature->HasSpellCooldown(spellId));
        return 1;
    }

    int CanFly(lua_State* L, Creature* creature)
    {
        Eluna::Push(L, creature->CanFly());
        return 1;
    }

    /*int IsTrigger(lua_State* L, Creature* creature)
    {
    Eluna::Push(L, creature->IsTrigger());
    return 1;
    }*/

    /*int IsDamageEnoughForLootingAndReward(lua_State* L, Creature* creature)
    {
    Eluna::Push(L, creature->IsDamageEnoughForLootingAndReward());
    return 1;
    }*/

    /*int CanStartAttack(lua_State* L, Creature* creature) // TODO: Implement core side
    {
    Unit* target = Eluna::CHECKOBJ<Unit>(L, 2);
    bool force = Eluna::CHECKVAL<bool>(L, 3, true);

    Eluna::Push(L, creature->CanStartAttack(target, force));
    return 1;
    }*/

    /*int HasLootMode(lua_State* L, Creature* creature) // TODO: Implement LootMode features
    {
    uint16 lootMode = Eluna::CHECKVAL<uint16>(L, 2);

    Eluna::Push(L, creature->HasLootMode(lootMode));
    return 1;
    }*/

    /* GETTERS */
    int GetRespawnDelay(lua_State* L, Creature* creature)
    {
        Eluna::Push(L, creature->GetRespawnDelay());
        return 1;
    }

    int GetRespawnRadius(lua_State* L, Creature* creature)
    {
        Eluna::Push(L, creature->GetRespawnRadius());
        return 1;
    }

    int GetDefaultMovementType(lua_State* L, Creature* creature)
    {
        Eluna::Push(L, creature->GetDefaultMovementType());
        return 1;
    }

    int GetAggroRange(lua_State* L, Creature* creature)
    {
        Unit* target = Eluna::CHECKOBJ<Unit>(L, 2);

#ifndef TRINITY
        float AttackDist = creature->GetAttackDistance(target);
        float ThreatRadius = sWorld.getConfig(CONFIG_FLOAT_THREAT_RADIUS);
        Eluna::Push(L, ThreatRadius > AttackDist ? ThreatRadius : AttackDist);
#else
        Eluna::Push(L, creature->GetAggroRange(target));
#endif
        return 1;
    }

    int GetAttackDistance(lua_State* L, Creature* creature)
    {
        Unit* target = Eluna::CHECKOBJ<Unit>(L, 2);

        Eluna::Push(L, creature->GetAttackDistance(target));
        return 1;
    }

    int GetLootRecipientGroup(lua_State* L, Creature* creature)
    {
#ifndef TRINITY
        Eluna::Push(L, creature->GetGroupLootRecipient());
#else
        Eluna::Push(L, creature->GetLootRecipientGroup());
#endif
        return 1;
    }

    int GetLootRecipient(lua_State* L, Creature* creature)
    {
        Eluna::Push(L, creature->GetLootRecipient());
        return 1;
    }

    int GetScriptName(lua_State* L, Creature* creature)
    {
        Eluna::Push(L, creature->GetScriptName());
        return 1;
    }

    int GetAIName(lua_State* L, Creature* creature)
    {
        Eluna::Push(L, creature->GetAIName());
        return 1;
    }

    int GetScriptId(lua_State* L, Creature* creature)
    {
        Eluna::Push(L, creature->GetScriptId());
        return 1;
    }

    int GetCreatureSpellCooldownDelay(lua_State* L, Creature* creature)
    {
        uint32 spell = Eluna::CHECKVAL<uint32>(L, 2);

        Eluna::Push(L, creature->GetCreatureSpellCooldownDelay(spell));
        return 1;
    }

    int GetCorpseDelay(lua_State* L, Creature* creature)
    {
        Eluna::Push(L, creature->GetCorpseDelay());
        return 1;
    }

    int GetHomePosition(lua_State* L, Creature* creature)
    {
        float x, y, z, o;
#ifndef TRINITY
        creature->GetRespawnCoord(x, y, z, &o);
#else
        creature->GetHomePosition(x, y, z, o);
#endif

        Eluna::Push(L, x);
        Eluna::Push(L, y);
        Eluna::Push(L, z);
        Eluna::Push(L, o);
        return 4;
    }

    int GetAITarget(lua_State* L, Creature* creature)
    {
        uint32 targetType = Eluna::CHECKVAL<uint32>(L, 2);
        bool playerOnly = Eluna::CHECKVAL<bool>(L, 3, false);
        uint32 position = Eluna::CHECKVAL<uint32>(L, 4, 0);
        float dist = Eluna::CHECKVAL<float>(L, 5, 0.0f);
        int32 aura = Eluna::CHECKVAL<int32>(L, 6, 0);

#ifdef MANGOS
        ThreatList const& threatlist = creature->GetThreatManager().getThreatList();
#else
        ThreatList const& threatlist = creature->getThreatManager().getThreatList();
#endif
        if (threatlist.empty())
            return 1;
        if (position >= threatlist.size())
            return 1;

        std::list<Unit*> targetList;
        for (ThreatList::const_iterator itr = threatlist.begin(); itr != threatlist.end(); ++itr)
        {
            Unit* target = (*itr)->getTarget();
            if (!target)
                continue;
            if (playerOnly && target->GetTypeId() != TYPEID_PLAYER)
                continue;
            if (aura > 0 && !target->HasAura(aura))
                continue;
            else if (aura < 0 && target->HasAura(-aura))
                continue;
            if (dist > 0.0f && !creature->IsWithinDist(target, dist))
                continue;
            else if (dist < 0.0f && creature->IsWithinDist(target, -dist))
                continue;
            targetList.push_back(target);
        }

        if (targetList.empty())
            return 1;
        if (position >= targetList.size())
            return 1;

        if (targetType == SELECT_TARGET_NEAREST || targetType == SELECT_TARGET_FARTHEST)
            targetList.sort(ElunaUtil::ObjectDistanceOrderPred(creature));

        switch (targetType)
        {
        case SELECT_TARGET_NEAREST:
        case SELECT_TARGET_TOPAGGRO:
        {
            std::list<Unit*>::const_iterator itr = targetList.begin();
            if (position)
                std::advance(itr, position);
            Eluna::Push(L, *itr);
        }
        break;
        case SELECT_TARGET_FARTHEST:
        case SELECT_TARGET_BOTTOMAGGRO:
        {
            std::list<Unit*>::reverse_iterator ritr = targetList.rbegin();
            if (position)
                std::advance(ritr, position);
            Eluna::Push(L, *ritr);
        }
        break;
        case SELECT_TARGET_RANDOM:
        {
            std::list<Unit*>::const_iterator itr = targetList.begin();
            if (position)
                std::advance(itr, urand(0, position));
            Eluna::Push(L, *itr);
        }
        break;
        default:
            luaL_argerror(L, 2, "SelectAggroTarget expected");
        break;
        }

        return 1;
    }

    int GetAITargets(lua_State* L, Creature* creature)
    {
        lua_newtable(L);
        int tbl = lua_gettop(L);
        uint32 i = 0;
        
#ifdef MANGOS
        ThreatList const& threatlist = creature->GetThreatManager().getThreatList();
#else
        ThreatList const& threatlist = creature->getThreatManager().getThreatList();
#endif
        if (threatlist.empty())
            return 1;
        for (ThreatList::const_iterator itr = threatlist.begin(); itr != threatlist.end(); ++itr)
        {
            Unit* target = (*itr)->getTarget();
            if (!target)
                continue;
            ++i;
            Eluna::Push(L, i);
            Eluna::Push(L, target);
            lua_settable(L, tbl);
        }

        lua_settop(L, tbl);
        return 1;
    }

    int GetAITargetsCount(lua_State* L, Creature* creature)
    {
#ifdef MANGOS
        Eluna::Push(L, creature->GetThreatManager().getThreatList().size());
#else
        Eluna::Push(L, creature->getThreatManager().getThreatList().size());
#endif
        return 1;
    }

    int GetNPCFlags(lua_State* L, Creature* creature)
    {
        Eluna::Push(L, creature->GetUInt32Value(UNIT_NPC_FLAGS));
        return 1;
    }

#ifndef CATA
    int GetShieldBlockValue(lua_State* L, Creature* creature)
    {
        Eluna::Push(L, creature->GetShieldBlockValue());
        return 1;
    }
#endif

    /*int GetLootMode(lua_State* L, Creature* creature) // TODO: Implement LootMode features
    {
    Eluna::Push(L, creature->GetLootMode());
    return 1;
    }*/

    /* SETTERS */
    int SetNPCFlags(lua_State* L, Creature* creature)
    {
        uint32 flags = Eluna::CHECKVAL<uint32>(L, 2);

        creature->SetUInt32Value(UNIT_NPC_FLAGS, flags);
        return 0;
    }

    int SetDeathState(lua_State* L, Creature* creature)
    {
        int32 state = Eluna::CHECKVAL<int32>(L, 2);

#ifndef TRINITY
        creature->SetDeathState((DeathState)state);
#else
        creature->setDeathState((DeathState)state);
#endif
        return 0;
    }

    int SetWalk(lua_State* L, Creature* creature)           // TODO: Move same to Player ?
    {
        bool enable = Eluna::CHECKVAL<bool>(L, 2, true);

        creature->SetWalk(enable);
        return 0;
    }

    int SetAllowedCombat(lua_State* L, Creature* creature)
    {
        bool allow = Eluna::CHECKVAL<bool>(L, 2);

#ifndef TRINITY
        if (CreatureAI* ai = creature->AI())
            ai->SetCombatMovement(allow);
#else
        creature->SetReactState(allow ? REACT_AGGRESSIVE : REACT_PASSIVE);
#endif
        return 0;
    }

    int SetDisableReputationGain(lua_State* L, Creature* creature)
    {
        bool disable = Eluna::CHECKVAL<bool>(L, 2, true);

        creature->SetDisableReputationGain(disable);
        return 0;
    }

    int SetInCombatWithZone(lua_State* /*L*/, Creature* creature)
    {
        creature->SetInCombatWithZone();
        return 0;
    }

    int SetRespawnRadius(lua_State* L, Creature* creature)
    {
        float dist = Eluna::CHECKVAL<float>(L, 2);

        creature->SetRespawnRadius(dist);
        return 0;
    }

    int SetRespawnDelay(lua_State* L, Creature* creature)
    {
        uint32 delay = Eluna::CHECKVAL<uint32>(L, 2);

        creature->SetRespawnDelay(delay);
        return 0;
    }

    int SetDefaultMovementType(lua_State* L, Creature* creature)
    {
        int32 type = Eluna::CHECKVAL<int32>(L, 2);

        creature->SetDefaultMovementType((MovementGeneratorType)type);
        return 0;
    }

    int SetNoSearchAssistance(lua_State* L, Creature* creature)
    {
        bool val = Eluna::CHECKVAL<bool>(L, 2, true);

        creature->SetNoSearchAssistance(val);
        return 0;
    }

    int SetNoCallAssistance(lua_State* L, Creature* creature)
    {
        bool val = Eluna::CHECKVAL<bool>(L, 2, true);

        creature->SetNoCallAssistance(val);
        return 0;
    }

    int SetHover(lua_State* L, Creature* creature)
    {
        bool enable = Eluna::CHECKVAL<bool>(L, 2, true);

#ifndef TRINITY
        creature->SetLevitate(enable);
#else
        creature->SetHover(enable);
#endif
        return 0;
    }

    /*int SetLootMode(lua_State* L, Creature* creature) // TODO: Implement LootMode features
    {
    uint16 lootMode = Eluna::CHECKVAL<uint16>(L, 2);

    creature->SetLootMode(lootMode);
    return 0;
    }*/

    /*int SetDisableGravity(lua_State* L, Creature* creature)
    {
    bool disable = Eluna::CHECKVAL<bool>(L, 2, true);
    bool packetOnly = Eluna::CHECKVAL<bool>(L, 3, false);

    Eluna::Push(L, creature->SetDisableGravity(disable, packetOnly));
    return 1;
    }*/

    /* OTHER */
    int DespawnOrUnsummon(lua_State* L, Creature* creature)
    {
        uint32 msTimeToDespawn = Eluna::CHECKVAL<uint32>(L, 2, 0);

#ifndef TRINITY
        creature->ForcedDespawn(msTimeToDespawn);
#else
        creature->DespawnOrUnsummon(msTimeToDespawn);
#endif
        return 0;
    }

    int Respawn(lua_State* /*L*/, Creature* creature)
    {
        creature->Respawn();
        return 0;
    }

    int RemoveCorpse(lua_State* /*L*/, Creature* creature)
    {
        creature->RemoveCorpse();
        return 0;
    }

    int MoveWaypoint(lua_State* /*L*/, Creature* creature)
    {
#ifndef TRINITY
        creature->GetMotionMaster()->MoveWaypoint();
#else
        creature->GetMotionMaster()->MovePath(creature->GetWaypointPath(), true);
#endif
        return 0;
    }

    int CallAssistance(lua_State* /*L*/, Creature* creature)
    {
        creature->CallAssistance();
        return 0;
    }

    int CallForHelp(lua_State* L, Creature* creature)
    {
        float radius = Eluna::CHECKVAL<float>(L, 2);

        creature->CallForHelp(radius);
        return 0;
    }

    int FleeToGetAssistance(lua_State* /*L*/, Creature* creature)
    {
        creature->DoFleeToGetAssistance();
        return 0;
    }

    int AttackStart(lua_State* L, Creature* creature)
    {
        Unit* target = Eluna::CHECKOBJ<Unit>(L, 2);

        creature->AI()->AttackStart(target);
        return 0;
    }

    int SaveToDB(lua_State* /*L*/, Creature* creature)
    {
        creature->SaveToDB();
        return 0;
    }

    int SelectVictim(lua_State* L, Creature* creature)
    {
#ifndef TRINITY
        Eluna::Push(L, creature->SelectHostileTarget());
#else
        Eluna::Push(L, creature->SelectVictim());
#endif
        return 1;
    }

    int UpdateEntry(lua_State* L, Creature* creature)
    {
        uint32 entry = Eluna::CHECKVAL<uint32>(L, 2);
        uint32 dataGuidLow = Eluna::CHECKVAL<uint32>(L, 3, 0);

#ifndef TRINITY
        creature->UpdateEntry(entry, ALLIANCE, dataGuidLow ? eObjectMgr->GetCreatureData(dataGuidLow) : NULL);
#else
        creature->UpdateEntry(entry, dataGuidLow ? eObjectMgr->GetCreatureData(dataGuidLow) : NULL);
#endif
        return 0;
    }

    /*int ResetLootMode(lua_State* L, Creature* creature) // TODO: Implement LootMode features
    {
    creature->ResetLootMode();
    return 0;
    }*/

    /*int RemoveLootMode(lua_State* L, Creature* creature) // TODO: Implement LootMode features
    {
    uint16 lootMode = Eluna::CHECKVAL<uint16>(L, 2);

    creature->RemoveLootMode(lootMode);
    return 0;
    }*/

    /*int AddLootMode(lua_State* L, Creature* creature) // TODO: Implement LootMode features
    {
    uint16 lootMode = Eluna::CHECKVAL<uint16>(L, 2);

    creature->AddLootMode(lootMode);
    return 0;
    }*/
};
#endif
