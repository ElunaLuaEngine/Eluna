/*
 * Copyright (C) 2010 - 2024 Eluna Lua Engine <https://elunaluaengine.github.io/>
 * This program is free software licensed under GPL version 3
 * Please see the included DOCS/LICENSE.md for more information
 */

#ifndef _ELUNA_CREATURE_AI_H
#define _ELUNA_CREATURE_AI_H

#include "LuaEngine.h"
#ifdef CMANGOS
#include "AI/BaseAI/CreatureAI.h"
#endif

#if defined TRINITY
struct ScriptedAI;
typedef ScriptedAI ElunaScriptedAI;
#elif defined CMANGOS
class CreatureAI;
typedef CreatureAI ElunaScriptedAI;
#elif defined VMANGOS
class BasicAI;
typedef BasicAI ElunaScriptedAI;
#else
class AggressorAI;
typedef AggressorAI ElunaScriptedAI;
#endif

struct ElunaCreatureAI : ElunaScriptedAI
{
    // used to delay the spawn hook triggering on AI creation
    bool justSpawned;
    // used to delay movementinform hook (WP hook)
    std::vector< std::pair<uint32, uint32> > movepoints;
#ifndef TRINITY
#define me  m_creature
#endif
    ElunaCreatureAI(Creature* creature) : ElunaScriptedAI(creature), justSpawned(true)
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
#ifndef TRINITY
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
                if (!me->GetEluna()->MovementInform(me, point.first, point.second))
                    ElunaScriptedAI::MovementInform(point.first, point.second);
            }
            movepoints.clear();
        }

        if (!me->GetEluna()->UpdateAI(me, diff))
        {
#ifdef MANGOS
            if (!me->HasFlag(UNIT_FIELD_FLAGS, UNIT_FLAG_PASSIVE))
#else
            if (!me->HasFlag(UNIT_FIELD_FLAGS, UNIT_FLAG_IMMUNE_TO_NPC))
#endif
                ElunaScriptedAI::UpdateAI(diff);
        }
    }

#ifdef TRINITY
    // Called for reaction when initially engaged - this will always happen _after_ JustEnteredCombat
    // Called at creature aggro either by MoveInLOS or Attack Start
    void JustEngagedWith(Unit* target) override
    {
        if (!me->GetEluna()->EnterCombat(me, target))
            ElunaScriptedAI::JustEngagedWith(target);
    }
#else
    //Called for reaction at enter to combat if not in combat yet (enemy can be NULL)
    //Called at creature aggro either by MoveInLOS or Attack Start
    void EnterCombat(Unit* target) override
    {
        if (!me->GetEluna()->EnterCombat(me, target))
            ElunaScriptedAI::EnterCombat(target);
    }
#endif

    // Called at any Damage from any attacker (before damage apply)
#if defined TRINITY || defined CMANGOS 
    void DamageTaken(Unit* attacker, uint32& damage, DamageEffectType damageType, SpellInfo const* spellInfo) override
#else
    void DamageTaken(Unit* attacker, uint32& damage) override
#endif
    {
        if (!me->GetEluna()->DamageTaken(me, attacker, damage))
        {
#if defined TRINITY || defined CMANGOS
            ElunaScriptedAI::DamageTaken(attacker, damage, damageType, spellInfo);
#else
            ElunaScriptedAI::DamageTaken(attacker, damage);
#endif
        }
    }

    //Called at creature death
    void JustDied(Unit* killer) override
    {
        if (!me->GetEluna()->JustDied(me, killer))
            ElunaScriptedAI::JustDied(killer);
    }

    //Called at creature killing another unit
    void KilledUnit(Unit* victim) override
    {
        if (!me->GetEluna()->KilledUnit(me, victim))
            ElunaScriptedAI::KilledUnit(victim);
    }

    // Called when the creature summon successfully other creature
    void JustSummoned(Creature* summon) override
    {
        if (!me->GetEluna()->JustSummoned(me, summon))
            ElunaScriptedAI::JustSummoned(summon);
    }

    // Called when a summoned creature is despawned
    void SummonedCreatureDespawn(Creature* summon) override
    {
        if (!me->GetEluna()->SummonedCreatureDespawn(me, summon))
            ElunaScriptedAI::SummonedCreatureDespawn(summon);
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
        if (!me->GetEluna()->AttackStart(me, target))
            ElunaScriptedAI::AttackStart(target);
    }

#ifdef TRINITY
    // Called for reaction at stopping attack at no attackers or targets
    void EnterEvadeMode(EvadeReason /*why*/) override
#else
    void EnterEvadeMode() override
#endif
    {
        if (!me->GetEluna()->EnterEvadeMode(me))
            ElunaScriptedAI::EnterEvadeMode();
    }

#ifdef TRINITY
    // Called when creature appears in the world (spawn, respawn, grid load etc...)
    void JustAppeared() override
    {
        if (!me->GetEluna()->JustRespawned(me))
            ElunaScriptedAI::JustAppeared();
    }
#else
    // Called when creature is spawned or respawned (for reseting variables)
    void JustRespawned() override
    {
        if (!me->GetEluna()->JustRespawned(me))
            ElunaScriptedAI::JustRespawned();
    }
#endif

    // Called at reaching home after evade
    void JustReachedHome() override
    {
        if (!me->GetEluna()->JustReachedHome(me))
            ElunaScriptedAI::JustReachedHome();
    }

    // Called at text emote receive from player
    void ReceiveEmote(Player* player, uint32 emoteId) override
    {
        if (!me->GetEluna()->ReceiveEmote(me, player, emoteId))
            ElunaScriptedAI::ReceiveEmote(player, emoteId);
    }

    // called when the corpse of this creature gets removed
    void CorpseRemoved(uint32& respawnDelay) override
    {
        if (!me->GetEluna()->CorpseRemoved(me, respawnDelay))
            ElunaScriptedAI::CorpseRemoved(respawnDelay);
    }

#if !defined(TRINITY) && !defined(VMANGOS)
    // Enables use of MoveInLineOfSight
    bool IsVisible(Unit* who) const override
    {
        return true;
    }
#endif

    void MoveInLineOfSight(Unit* who) override
    {
        if (!me->GetEluna()->MoveInLineOfSight(me, who))
            ElunaScriptedAI::MoveInLineOfSight(who);
    }

    // Called when hit by a spell
#ifdef TRINITY
    void SpellHit(WorldObject* caster, SpellInfo const* spell) override
#elif VMANGOS
    void SpellHit(Unit* caster, SpellInfo const* spell)
#else
    void SpellHit(Unit* caster, SpellInfo const* spell) override
#endif
    {
        if (!me->GetEluna()->SpellHit(me, caster, spell))
            ElunaScriptedAI::SpellHit(caster, spell);
    }

    // Called when spell hits a target
#ifdef TRINITY
    void SpellHitTarget(WorldObject* target, SpellInfo const* spell) override
#else
    void SpellHitTarget(Unit* target, SpellInfo const* spell) override
#endif
    {
        if (!me->GetEluna()->SpellHitTarget(me, target, spell))
            ElunaScriptedAI::SpellHitTarget(target, spell);
    }

#ifdef TRINITY
    // Called when the creature is summoned successfully by other creature
    void IsSummonedBy(WorldObject* summoner) override
    {
        if (!summoner->ToUnit() || !me->GetEluna()->OnSummoned(me, summoner->ToUnit()))
            ElunaScriptedAI::IsSummonedBy(summoner);
    }

    void SummonedCreatureDies(Creature* summon, Unit* killer) override
    {
        if (!me->GetEluna()->SummonedCreatureDies(me, summon, killer))
            ElunaScriptedAI::SummonedCreatureDies(summon, killer);
    }

    // Called when owner takes damage
    void OwnerAttackedBy(Unit* attacker) override
    {
        if (!me->GetEluna()->OwnerAttackedBy(me, attacker))
            ElunaScriptedAI::OwnerAttackedBy(attacker);
    }

    // Called when owner attacks something
    void OwnerAttacked(Unit* target) override
    {
        if (!me->GetEluna()->OwnerAttacked(me, target))
            ElunaScriptedAI::OwnerAttacked(target);
    }
#endif

#if defined MANGOS || defined CMANGOS
#undef me
#endif
};

#endif
