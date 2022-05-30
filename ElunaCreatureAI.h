/*
 * Copyright (C) 2010 - 2016 Eluna Lua Engine <http://emudevs.com/>
 * This program is free software licensed under GPL version 3
 * Please see the included DOCS/LICENSE.md for more information
 */

#ifndef _ELUNA_CREATURE_AI_H
#define _ELUNA_CREATURE_AI_H

#include "LuaEngine.h"
#ifdef CMANGOS
#include "AI/BaseAI/CreatureAI.h"
#endif

#if defined TRINITY || AZEROTHCORE
struct ScriptedAI;
#elif defined CMANGOS
class CreatureAI;
#else
class AggressorAI;
typedef AggressorAI ScriptedAI;
#endif

#ifndef CMANGOS
struct ElunaCreatureAI : ScriptedAI
#else
struct ElunaCreatureAI : CreatureAI
#endif
{
    // used to delay the spawn hook triggering on AI creation
    bool justSpawned;
    // used to delay movementinform hook (WP hook)
    std::vector< std::pair<uint32, uint32> > movepoints;
#if defined MANGOS || defined CMANGOS
#define me  m_creature
#endif
#ifndef CMANGOS
    ElunaCreatureAI(Creature* creature) : ScriptedAI(creature), justSpawned(true)
#else
    ElunaCreatureAI(Creature* creature) : CreatureAI(creature), justSpawned(true)
#endif
    {
    }
    ~ElunaCreatureAI() { }

    //Called at World update tick
#ifndef TRINITY
    void UpdateAI(const uint32 diff) override
#else
    void UpdateAI(uint32 diff) override
#endif
    {
#ifdef TRINITY
        //Spawns are handled by Creature.cpp - in function Creature::Update() 
#else
        if (justSpawned)
        {
            justSpawned = false;

            JustRespawned();
        }
#endif

        if (!movepoints.empty())
        {
            for (auto& point : movepoints)
            {
#ifndef CMANGOS
                if (!sEluna->MovementInform(me, point.first, point.second))
                    ScriptedAI::MovementInform(point.first, point.second);
#else
                if (!sEluna->MovementInform(me, point.first, point.second))
                    CreatureAI::MovementInform(point.first, point.second);
#endif
            }
            movepoints.clear();
        }

        if (!sEluna->UpdateAI(me, diff))
        {
#if defined TRINITY || AZEROTHCORE
            if (!me->HasFlag(UNIT_FIELD_FLAGS, UNIT_FLAG_IMMUNE_TO_NPC))
                ScriptedAI::UpdateAI(diff);
#elif defined CMANGOS
            if (!me->HasFlag(UNIT_FIELD_FLAGS, UNIT_FLAG_IMMUNE_TO_NPC))
                CreatureAI::UpdateAI(diff);
#else
            if (!me->HasFlag(UNIT_FIELD_FLAGS, UNIT_FLAG_PASSIVE))
                ScriptedAI::UpdateAI(diff);
#endif
        }
    }

#ifdef TRINITY
    // Called for reaction when initially engaged - this will always happen _after_ JustEnteredCombat
    // Called at creature aggro either by MoveInLOS or Attack Start
    void JustEngagedWith(Unit* target) override
    {
        if (!sEluna->EnterCombat(me, target))
            ScriptedAI::JustEngagedWith(target);
    }
#else
    //Called for reaction at enter to combat if not in combat yet (enemy can be NULL)
    //Called at creature aggro either by MoveInLOS or Attack Start
    void EnterCombat(Unit* target) override
    {
#ifndef CMANGOS
        if (!sEluna->EnterCombat(me, target))
            ScriptedAI::EnterCombat(target);
#else
        if (!sEluna->EnterCombat(me, target))
            CreatureAI::EnterCombat(target);
#endif
    }
#endif

    // Called at any Damage from any attacker (before damage apply)
#if defined AZEROTHCORE
    void DamageTaken(Unit* attacker, uint32& damage, DamageEffectType damagetype, SpellSchoolMask damageSchoolMask) override
#elif defined(TRINITY) || CMANGOS
    void DamageTaken(Unit* attacker, uint32& damage, DamageEffectType damageType, SpellInfo const* spellInfo) override
#else
    void DamageTaken(Unit* attacker, uint32& damage) override
#endif
    {
        if (!sEluna->DamageTaken(me, attacker, damage))
        {
#if defined AZEROTHCORE
            ScriptedAI::DamageTaken(attacker, damage, damagetype, damageSchoolMask);
#elif defined TRINITY
            ScriptedAI::DamageTaken(attacker, damage, damageType, spellInfo);
#elif defined CMANGOS
            CreatureAI::DamageTaken(attacker, damage, damageType, spellInfo);
#else
            ScriptedAI::DamageTaken(attacker, damage);
#endif
        }
    }

    //Called at creature death
    void JustDied(Unit* killer) override
    {
#ifndef CMANGOS
        if (!sEluna->JustDied(me, killer))
            ScriptedAI::JustDied(killer);
#else
        if (!sEluna->JustDied(me, killer))
            CreatureAI::JustDied(killer);
#endif
    }

    //Called at creature killing another unit
    void KilledUnit(Unit* victim) override
    {
#ifndef CMANGOS
        if (!sEluna->KilledUnit(me, victim))
            ScriptedAI::KilledUnit(victim);
#else
        if (!sEluna->KilledUnit(me, victim))
            CreatureAI::KilledUnit(victim);
#endif
    }

    // Called when the creature summon successfully other creature
    void JustSummoned(Creature* summon) override
    {
#ifndef CMANGOS
        if (!sEluna->JustSummoned(me, summon))
            ScriptedAI::JustSummoned(summon);
#else
        if (!sEluna->JustSummoned(me, summon))
            CreatureAI::JustSummoned(summon);
#endif
    }

    // Called when a summoned creature is despawned
    void SummonedCreatureDespawn(Creature* summon) override
    {
#ifndef CMANGOS
        if (!sEluna->SummonedCreatureDespawn(me, summon))
            ScriptedAI::SummonedCreatureDespawn(summon);
#else
        if (!sEluna->SummonedCreatureDespawn(me, summon))
            CreatureAI::SummonedCreatureDespawn(summon);
#endif
    }

    //Called at waypoint reached or PointMovement end
    void MovementInform(uint32 type, uint32 id) override
    {
        // delayed since hook triggers before actually reaching the point
        // and starting new movement would bug
        movepoints.push_back(std::make_pair(type, id));
    }

    // Called before EnterCombat even before the creature is in combat.
    void AttackStart(Unit* target) override
    {
#ifndef CMANGOS
        if (!sEluna->AttackStart(me, target))
            ScriptedAI::AttackStart(target);
#else
        if (!sEluna->AttackStart(me, target))
           CreatureAI::AttackStart(target);
#endif
    }

#ifdef TRINITY
    // Called for reaction at stopping attack at no attackers or targets
    void EnterEvadeMode(EvadeReason /*why*/) override
    {
#ifndef CMANGOS
        if (!sEluna->EnterEvadeMode(me))
            ScriptedAI::EnterEvadeMode();
#else
        if (!sEluna->EnterEvadeMode(me))
            CreatureAI::EnterEvadeMode();
#endif
    }
#else
    // Called for reaction at stopping attack at no attackers or targets
    void EnterEvadeMode() override
    {
#ifndef CMANGOS
        if (!sEluna->EnterEvadeMode(me))
            ScriptedAI::EnterEvadeMode();
#else
        if (!sEluna->EnterEvadeMode(me))
            CreatureAI::EnterEvadeMode();
#endif
    }
#endif

#ifdef TRINITY
    // Called when creature appears in the world (spawn, respawn, grid load etc...)
    void JustAppeared() override
    {
        if (!sEluna->JustRespawned(me))
            ScriptedAI::JustAppeared();
    }
#else
    // Called when creature is spawned or respawned (for reseting variables)
    void JustRespawned() override
    {
#ifndef CMANGOS
        if (!sEluna->JustRespawned(me))
            ScriptedAI::JustRespawned();
#else
        if (!sEluna->JustRespawned(me))
            CreatureAI::JustRespawned();
#endif
    }
#endif

    // Called at reaching home after evade
    void JustReachedHome() override
    {
#ifndef CMANGOS
        if (!sEluna->JustReachedHome(me))
            ScriptedAI::JustReachedHome();
#else
        if (!sEluna->JustReachedHome(me))
            CreatureAI::JustReachedHome();
#endif
    }

    // Called at text emote receive from player
    void ReceiveEmote(Player* player, uint32 emoteId) override
    {
#ifndef CMANGOS
        if (!sEluna->ReceiveEmote(me, player, emoteId))
            ScriptedAI::ReceiveEmote(player, emoteId);
#else
        if (!sEluna->ReceiveEmote(me, player, emoteId))
            CreatureAI::ReceiveEmote(player, emoteId);
#endif
    }

    // called when the corpse of this creature gets removed
    void CorpseRemoved(uint32& respawnDelay) override
    {
#ifndef CMANGOS
        if (!sEluna->CorpseRemoved(me, respawnDelay))
            ScriptedAI::CorpseRemoved(respawnDelay);
#else
        if (!sEluna->CorpseRemoved(me, respawnDelay))
            CreatureAI::CorpseRemoved(respawnDelay);
#endif
    }

#if !defined TRINITY && !AZEROTHCORE
    // Enables use of MoveInLineOfSight
    bool IsVisible(Unit* who) const override
    {
        return true;
    }
#endif

    void MoveInLineOfSight(Unit* who) override
    {
#ifndef CMANGOS
        if (!sEluna->MoveInLineOfSight(me, who))
            ScriptedAI::MoveInLineOfSight(who);
#else
        if (!sEluna->MoveInLineOfSight(me, who))
            CreatureAI::MoveInLineOfSight(who);
#endif
    }

    // Called when hit by a spell
#if defined TRINITY
    void SpellHit(WorldObject* caster, SpellInfo const* spell) override
#else
    void SpellHit(Unit* caster, SpellInfo const* spell) override
#endif
    {
#ifndef CMANGOS
        if (!sEluna->SpellHit(me, caster, spell))
            ScriptedAI::SpellHit(caster, spell);
#else
        if (!sEluna->SpellHit(me, caster, spell))
            CreatureAI::SpellHit(caster, spell);
#endif
    }

    // Called when spell hits a target
#if defined TRINITY
    void SpellHitTarget(WorldObject* target, SpellInfo const* spell) override
#else
    void SpellHitTarget(Unit* target, SpellInfo const* spell) override
#endif
    {
#ifndef CMANGOS
        if (!sEluna->SpellHitTarget(me, target, spell))
            ScriptedAI::SpellHitTarget(target, spell);
#else
        if (!sEluna->SpellHitTarget(me, target, spell))
            CreatureAI::SpellHitTarget(target, spell);
#endif
    }

#if defined TRINITY || AZEROTHCORE

#if defined TRINITY
    // Called when the creature is summoned successfully by other creature
    void IsSummonedBy(WorldObject* summoner) override
    {
        if (!summoner->ToUnit() || !sEluna->OnSummoned(me, summoner->ToUnit()))
            ScriptedAI::IsSummonedBy(summoner);
    }
#else
    // Called when the creature is summoned successfully by other creature
    void IsSummonedBy(Unit* summoner) override
    {
        if (!sEluna->OnSummoned(me, summoner))
            ScriptedAI::IsSummonedBy(summoner);
    }
#endif

    void SummonedCreatureDies(Creature* summon, Unit* killer) override
    {
        if (!sEluna->SummonedCreatureDies(me, summon, killer))
            ScriptedAI::SummonedCreatureDies(summon, killer);
    }

    // Called when owner takes damage
    void OwnerAttackedBy(Unit* attacker) override
    {
        if (!sEluna->OwnerAttackedBy(me, attacker))
            ScriptedAI::OwnerAttackedBy(attacker);
    }

    // Called when owner attacks something
    void OwnerAttacked(Unit* target) override
    {
        if (!sEluna->OwnerAttacked(me, target))
            ScriptedAI::OwnerAttacked(target);
    }
#endif

#if defined MANGOS || defined CMANGOS
#undef me
#endif
};

#endif
