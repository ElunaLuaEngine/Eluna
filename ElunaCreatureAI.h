/*
 * Copyright (C) 2010 - 2024 Eluna Lua Engine <https://elunaluaengine.github.io/>
 * This program is free software licensed under GPL version 3
 * Please see the included DOCS/LICENSE.md for more information
 */

#ifndef _ELUNA_CREATURE_AI_H
#define _ELUNA_CREATURE_AI_H

#include "LuaEngine.h"
#if defined ELUNA_CMANGOS
#include "AI/BaseAI/CreatureAI.h"
#endif

#if defined ELUNA_TRINITY
struct ScriptedAI;
typedef ScriptedAI NativeScriptedAI;
#elif defined ELUNA_CMANGOS || ELUNA_MANGOS
class CreatureAI;
typedef CreatureAI NativeScriptedAI;
#elif defined ELUNA_VMANGOS
class BasicAI;
typedef BasicAI NativeScriptedAI;
#endif

struct ElunaCreatureAI : NativeScriptedAI
{
    // used to delay the spawn hook triggering on AI creation
    bool justSpawned;
    // used to delay movementinform hook (WP hook)
    std::vector< std::pair<uint32, uint32> > movepoints;
#if !defined ELUNA_TRINITY
#define me  m_creature
#endif
    ElunaCreatureAI(Creature* creature) : NativeScriptedAI(creature), justSpawned(true)
    {
    }
    ~ElunaCreatureAI() { }

    //Called at World update tick
#if !defined ELUNA_TRINITY
    void UpdateAI(const uint32 diff) override
#else
    void UpdateAI(uint32 diff) override
#endif
    {
#if !defined ELUNA_TRINITY
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
                    NativeScriptedAI::MovementInform(point.first, point.second);
            }
            movepoints.clear();
        }

        if (!me->GetEluna()->UpdateAI(me, diff))
        {
#if !defined ELUNA_MANGOS
            if (!me->HasFlag(UNIT_FIELD_FLAGS, UNIT_FLAG_IMMUNE_TO_NPC))
#else
            if (!me->HasFlag(UNIT_FIELD_FLAGS, UNIT_FLAG_PASSIVE))
#endif
                NativeScriptedAI::UpdateAI(diff);
        }
    }

#if defined ELUNA_TRINITY
    // Called for reaction when initially engaged - this will always happen _after_ JustEnteredCombat
    // Called at creature aggro either by MoveInLOS or Attack Start
    void JustEngagedWith(Unit* target) override
    {
        if (!me->GetEluna()->EnterCombat(me, target))
            NativeScriptedAI::JustEngagedWith(target);
    }
#else
    //Called for reaction at enter to combat if not in combat yet (enemy can be NULL)
    //Called at creature aggro either by MoveInLOS or Attack Start
    void EnterCombat(Unit* target) override
    {
        if (!me->GetEluna()->EnterCombat(me, target))
            NativeScriptedAI::EnterCombat(target);
    }
#endif

    // Called at any Damage from any attacker (before damage apply)
#if defined ELUNA_TRINITY || defined ELUNA_CMANGOS 
    void DamageTaken(Unit* attacker, uint32& damage, DamageEffectType damageType, SpellInfo const* spellInfo) override
#else
    void DamageTaken(Unit* attacker, uint32& damage) override
#endif
    {
        if (!me->GetEluna()->DamageTaken(me, attacker, damage))
        {
#if defined ELUNA_TRINITY || defined ELUNA_CMANGOS
            NativeScriptedAI::DamageTaken(attacker, damage, damageType, spellInfo);
#else
            NativeScriptedAI::DamageTaken(attacker, damage);
#endif
        }
    }

    //Called at creature death
    void JustDied(Unit* killer) override
    {
        if (!me->GetEluna()->JustDied(me, killer))
            NativeScriptedAI::JustDied(killer);
    }

    //Called at creature killing another unit
    void KilledUnit(Unit* victim) override
    {
        if (!me->GetEluna()->KilledUnit(me, victim))
            NativeScriptedAI::KilledUnit(victim);
    }

    // Called when the creature summon successfully other creature
    void JustSummoned(Creature* summon) override
    {
        if (!me->GetEluna()->JustSummoned(me, summon))
            NativeScriptedAI::JustSummoned(summon);
    }

    // Called when a summoned creature is despawned
    void SummonedCreatureDespawn(Creature* summon) override
    {
        if (!me->GetEluna()->SummonedCreatureDespawn(me, summon))
            NativeScriptedAI::SummonedCreatureDespawn(summon);
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
            NativeScriptedAI::AttackStart(target);
    }

#if defined ELUNA_TRINITY
    // Called for reaction at stopping attack at no attackers or targets
    void EnterEvadeMode(EvadeReason /*why*/) override
#else
    void EnterEvadeMode() override
#endif
    {
        if (!me->GetEluna()->EnterEvadeMode(me))
            NativeScriptedAI::EnterEvadeMode();
    }

#if defined ELUNA_TRINITY
    // Called when creature appears in the world (spawn, respawn, grid load etc...)
    void JustAppeared() override
    {
        if (!me->GetEluna()->JustRespawned(me))
            NativeScriptedAI::JustAppeared();
    }
#else
    // Called when creature is spawned or respawned (for reseting variables)
    void JustRespawned() override
    {
        if (!me->GetEluna()->JustRespawned(me))
            NativeScriptedAI::JustRespawned();
    }
#endif

    // Called at reaching home after evade
    void JustReachedHome() override
    {
        if (!me->GetEluna()->JustReachedHome(me))
            NativeScriptedAI::JustReachedHome();
    }

    // Called at text emote receive from player
    void ReceiveEmote(Player* player, uint32 emoteId) override
    {
        if (!me->GetEluna()->ReceiveEmote(me, player, emoteId))
            NativeScriptedAI::ReceiveEmote(player, emoteId);
    }

    // called when the corpse of this creature gets removed
    void CorpseRemoved(uint32& respawnDelay) override
    {
        if (!me->GetEluna()->CorpseRemoved(me, respawnDelay))
            NativeScriptedAI::CorpseRemoved(respawnDelay);
    }

#if !defined ELUNA_TRINITY && !defined ELUNA_VMANGOS
    // Enables use of MoveInLineOfSight
    bool IsVisible(Unit* who) const override
    {
        return true;
    }
#endif

    void MoveInLineOfSight(Unit* who) override
    {
        if (!me->GetEluna()->MoveInLineOfSight(me, who))
            NativeScriptedAI::MoveInLineOfSight(who);
    }

    // Called when hit by a spell
#if defined ELUNA_TRINITY
    void SpellHit(WorldObject* caster, SpellInfo const* spell) override
#elif defined ELUNA_VMANGOS
    void SpellHit(Unit* caster, SpellInfo const* spell)
#else
    void SpellHit(Unit* caster, SpellInfo const* spell) override
#endif
    {
        if (!me->GetEluna()->SpellHit(me, caster, spell))
            NativeScriptedAI::SpellHit(caster, spell);
    }

    // Called when spell hits a target
#if defined ELUNA_TRINITY
    void SpellHitTarget(WorldObject* target, SpellInfo const* spell) override
#else
    void SpellHitTarget(Unit* target, SpellInfo const* spell) override
#endif
    {
        if (!me->GetEluna()->SpellHitTarget(me, target, spell))
            NativeScriptedAI::SpellHitTarget(target, spell);
    }

#if defined ELUNA_TRINITY
    // Called when the creature is summoned successfully by other creature
    void IsSummonedBy(WorldObject* summoner) override
    {
        if (!summoner->ToUnit() || !me->GetEluna()->OnSummoned(me, summoner->ToUnit()))
            NativeScriptedAI::IsSummonedBy(summoner);
    }

    void SummonedCreatureDies(Creature* summon, Unit* killer) override
    {
        if (!me->GetEluna()->SummonedCreatureDies(me, summon, killer))
            NativeScriptedAI::SummonedCreatureDies(summon, killer);
    }

    // Called when owner takes damage
    void OwnerAttackedBy(Unit* attacker) override
    {
        if (!me->GetEluna()->OwnerAttackedBy(me, attacker))
            NativeScriptedAI::OwnerAttackedBy(attacker);
    }

    // Called when owner attacks something
    void OwnerAttacked(Unit* target) override
    {
        if (!me->GetEluna()->OwnerAttacked(me, target))
            NativeScriptedAI::OwnerAttacked(target);
    }
#endif

#if !defined ELUNA_TRINITY
#undef me
#endif
};

#endif
