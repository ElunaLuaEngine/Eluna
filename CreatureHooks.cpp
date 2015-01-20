/*
 * Copyright (C) 2010 - 2015 Eluna Lua Engine <http://emudevs.com/>
 * This program is free software licensed under GPL version 3
 * Please see the included DOCS/LICENSE.md for more information
 */

#ifndef _CREATURE_HOOKS_H
#define _CREATURE_HOOKS_H

#include "Hooks.h"
#include "HookHelpers.h"
#include "LuaEngine.h"
#include "ElunaBinding.h"
#include "ElunaIncludes.h"
#include "ElunaTemplate.h"

using namespace Hooks;

bool Eluna::OnDummyEffect(Unit* pCaster, uint32 spellId, SpellEffIndex effIndex, Creature* pTarget)
{
    if (!CreatureEventBindings->HasEvents(CREATURE_EVENT_ON_DUMMY_EFFECT, pTarget->GetEntry()))
        if (!CreatureUniqueBindings->HasEvents(CREATURE_EVENT_ON_DUMMY_EFFECT, pTarget->GET_GUID(), pTarget->GetInstanceId()))
            return false;

    LOCK_ELUNA;
    Push(pCaster);
    Push(spellId);
    Push(effIndex);
    Push(pTarget);
    return CallAllFunctionsBool(CreatureEventBindings, CreatureUniqueBindings, CREATURE_EVENT_ON_DUMMY_EFFECT, pTarget->GetEntry(), pTarget->GET_GUID(), pTarget->GetInstanceId());
}

bool Eluna::OnGossipHello(Player* pPlayer, Creature* pCreature)
{
    if (!CreatureGossipBindings->HasEvents(GOSSIP_EVENT_ON_HELLO, pCreature->GetEntry()))
        return false;

    LOCK_ELUNA;
    pPlayer->PlayerTalkClass->ClearMenus();
    Push(pPlayer);
    Push(pCreature);
    return CallAllFunctionsBool(CreatureGossipBindings, GOSSIP_EVENT_ON_HELLO, pCreature->GetEntry(), true);
}

bool Eluna::OnGossipSelect(Player* pPlayer, Creature* pCreature, uint32 sender, uint32 action)
{
    if (!CreatureGossipBindings->HasEvents(GOSSIP_EVENT_ON_SELECT, pCreature->GetEntry()))
        return false;

    LOCK_ELUNA;
    pPlayer->PlayerTalkClass->ClearMenus();
    Push(pPlayer);
    Push(pCreature);
    Push(sender);
    Push(action);
    return CallAllFunctionsBool(CreatureGossipBindings, GOSSIP_EVENT_ON_SELECT, pCreature->GetEntry(), true);
}

bool Eluna::OnGossipSelectCode(Player* pPlayer, Creature* pCreature, uint32 sender, uint32 action, const char* code)
{
    if (!CreatureGossipBindings->HasEvents(GOSSIP_EVENT_ON_SELECT, pCreature->GetEntry()))
        return false;

    LOCK_ELUNA;
    pPlayer->PlayerTalkClass->ClearMenus();
    Push(pPlayer);
    Push(pCreature);
    Push(sender);
    Push(action);
    Push(code);
    return CallAllFunctionsBool(CreatureGossipBindings, GOSSIP_EVENT_ON_SELECT, pCreature->GetEntry(), true);
}

bool Eluna::OnQuestAccept(Player* pPlayer, Creature* pCreature, Quest const* pQuest)
{
    if (!CreatureEventBindings->HasEvents(CREATURE_EVENT_ON_QUEST_ACCEPT, pCreature->GetEntry()))
        if (!CreatureUniqueBindings->HasEvents(CREATURE_EVENT_ON_QUEST_ACCEPT, pCreature->GET_GUID(), pCreature->GetInstanceId()))
            return false;

    LOCK_ELUNA;
    Push(pPlayer);
    Push(pCreature);
    Push(pQuest);
    return CallAllFunctionsBool(CreatureEventBindings, CreatureUniqueBindings, CREATURE_EVENT_ON_QUEST_ACCEPT, pCreature->GetEntry(), pCreature->GET_GUID(), pCreature->GetInstanceId());
}

bool Eluna::OnQuestReward(Player* pPlayer, Creature* pCreature, Quest const* pQuest, uint32 opt)
{
    if (!CreatureEventBindings->HasEvents(CREATURE_EVENT_ON_QUEST_REWARD, pCreature->GetEntry()))
        if (!CreatureUniqueBindings->HasEvents(CREATURE_EVENT_ON_QUEST_REWARD, pCreature->GET_GUID(), pCreature->GetInstanceId()))
            return false;

    LOCK_ELUNA;
    Push(pPlayer);
    Push(pCreature);
    Push(pQuest);
    Push(opt);
    return CallAllFunctionsBool(CreatureEventBindings, CreatureUniqueBindings, CREATURE_EVENT_ON_QUEST_REWARD, pCreature->GetEntry(), pCreature->GET_GUID(), pCreature->GetInstanceId());
}

uint32 Eluna::GetDialogStatus(Player* pPlayer, Creature* pCreature)
{
    if (!CreatureEventBindings->HasEvents(CREATURE_EVENT_ON_DIALOG_STATUS, pCreature->GetEntry()))
        if (!CreatureUniqueBindings->HasEvents(CREATURE_EVENT_ON_DIALOG_STATUS, pCreature->GET_GUID(), pCreature->GetInstanceId()))
            return DIALOG_STATUS_SCRIPTED_NO_STATUS;

    LOCK_ELUNA;
    Push(pPlayer);
    Push(pCreature);
    CallAllFunctions(CreatureEventBindings, CreatureUniqueBindings, CREATURE_EVENT_ON_DIALOG_STATUS, pCreature->GetEntry(), pCreature->GET_GUID(), pCreature->GetInstanceId());
    return DIALOG_STATUS_SCRIPTED_NO_STATUS;
}

void Eluna::OnAddToWorld(Creature* creature)
{
    if (!CreatureEventBindings->HasEvents(CREATURE_EVENT_ON_ADD, creature->GetEntry()))
        if (!CreatureUniqueBindings->HasEvents(CREATURE_EVENT_ON_ADD, creature->GET_GUID(), creature->GetInstanceId()))
            return;

    LOCK_ELUNA;
    Push(creature);
    CallAllFunctions(CreatureEventBindings, CreatureUniqueBindings, CREATURE_EVENT_ON_ADD, creature->GetEntry(), creature->GET_GUID(), creature->GetInstanceId());
}

void Eluna::OnRemoveFromWorld(Creature* creature)
{
    if (!CreatureEventBindings->HasEvents(CREATURE_EVENT_ON_REMOVE, creature->GetEntry()))
        if (!CreatureUniqueBindings->HasEvents(CREATURE_EVENT_ON_REMOVE, creature->GET_GUID(), creature->GetInstanceId()))
            return;

    LOCK_ELUNA;
    Push(creature);
    CallAllFunctions(CreatureEventBindings, CreatureUniqueBindings, CREATURE_EVENT_ON_REMOVE, creature->GetEntry(), creature->GET_GUID(), creature->GetInstanceId());
}

bool Eluna::OnSummoned(Creature* pCreature, Unit* pSummoner)
{
    if (!CreatureEventBindings->HasEvents(CREATURE_EVENT_ON_SUMMONED, pCreature->GetEntry()))
        if (!CreatureUniqueBindings->HasEvents(CREATURE_EVENT_ON_SUMMONED, pCreature->GET_GUID(), pCreature->GetInstanceId()))
            return false;

    LOCK_ELUNA;
    Push(pCreature);
    Push(pSummoner);
    return CallAllFunctionsBool(CreatureEventBindings, CreatureUniqueBindings, CREATURE_EVENT_ON_SUMMONED, pCreature->GetEntry(), pCreature->GET_GUID(), pCreature->GetInstanceId());
}

bool Eluna::UpdateAI(Creature* me, const uint32 diff)
{
    if (!CreatureEventBindings->HasEvents(CREATURE_EVENT_ON_AIUPDATE, me->GetEntry()))
        if (!CreatureUniqueBindings->HasEvents(CREATURE_EVENT_ON_AIUPDATE, me->GET_GUID(), me->GetInstanceId()))
            return false;

    LOCK_ELUNA;
    Push(me);
    Push(diff);
    return CallAllFunctionsBool(CreatureEventBindings, CreatureUniqueBindings, CREATURE_EVENT_ON_AIUPDATE, me->GetEntry(), me->GET_GUID(), me->GetInstanceId());
}

//Called for reaction at enter to combat if not in combat yet (enemy can be NULL)
//Called at creature aggro either by MoveInLOS or Attack Start
bool Eluna::EnterCombat(Creature* me, Unit* target)
{
    if (!CreatureEventBindings->HasEvents(CREATURE_EVENT_ON_ENTER_COMBAT, me->GetEntry()))
        if (!CreatureUniqueBindings->HasEvents(CREATURE_EVENT_ON_ENTER_COMBAT, me->GET_GUID(), me->GetInstanceId()))
            return false;

    LOCK_ELUNA;
    Push(me);
    Push(target);
    return CallAllFunctionsBool(CreatureEventBindings, CreatureUniqueBindings, CREATURE_EVENT_ON_ENTER_COMBAT, me->GetEntry(), me->GET_GUID(), me->GetInstanceId());
}

// Called at any Damage from any attacker (before damage apply)
bool Eluna::DamageTaken(Creature* me, Unit* attacker, uint32& damage)
{
    if (!CreatureEventBindings->HasEvents(CREATURE_EVENT_ON_DAMAGE_TAKEN, me->GetEntry()))
        if (!CreatureUniqueBindings->HasEvents(CREATURE_EVENT_ON_DAMAGE_TAKEN, me->GET_GUID(), me->GetInstanceId()))
            return false;

    LOCK_ELUNA;
    bool result = false;
    Push(me);
    Push(attacker);
    Push(damage);
    int damageIndex = lua_gettop(L);
    int n = SetupStack(CreatureEventBindings, CreatureUniqueBindings, CREATURE_EVENT_ON_DAMAGE_TAKEN, me->GetEntry(), me->GET_GUID(), me->GetInstanceId(), 3);

    while (n > 0)
    {
        int r = CallOneFunction(n--, 3, 2);

        if (lua_isboolean(L, r + 0) && lua_toboolean(L, r + 0))
            result = true;

        if (lua_isnumber(L, r + 1))
        {
            damage = Eluna::CHECKVAL<uint32>(L, r + 1);
            // Update the stack for subsequent calls.
            ReplaceArgument(damage, damageIndex);
        }

        lua_pop(L, 2);
    }

    CleanUpStack(3);
    return result;
}

//Called at creature death
bool Eluna::JustDied(Creature* me, Unit* killer)
{
    On_Reset(me);

    if (!CreatureEventBindings->HasEvents(CREATURE_EVENT_ON_DIED, me->GetEntry()))
        if (!CreatureUniqueBindings->HasEvents(CREATURE_EVENT_ON_DIED, me->GET_GUID(), me->GetInstanceId()))
            return false;

    LOCK_ELUNA;
    Push(me);
    Push(killer);
    return CallAllFunctionsBool(CreatureEventBindings, CreatureUniqueBindings, CREATURE_EVENT_ON_DIED, me->GetEntry(), me->GET_GUID(), me->GetInstanceId());
}

//Called at creature killing another unit
bool Eluna::KilledUnit(Creature* me, Unit* victim)
{
    if (!CreatureEventBindings->HasEvents(CREATURE_EVENT_ON_TARGET_DIED, me->GetEntry()))
        if (!CreatureUniqueBindings->HasEvents(CREATURE_EVENT_ON_TARGET_DIED, me->GET_GUID(), me->GetInstanceId()))
            return false;

    LOCK_ELUNA;
    Push(me);
    Push(victim);
    return CallAllFunctionsBool(CreatureEventBindings, CreatureUniqueBindings, CREATURE_EVENT_ON_TARGET_DIED, me->GetEntry(), me->GET_GUID(), me->GetInstanceId());
}

// Called when the creature summon successfully other creature
bool Eluna::JustSummoned(Creature* me, Creature* summon)
{
    if (!CreatureEventBindings->HasEvents(CREATURE_EVENT_ON_JUST_SUMMONED_CREATURE, me->GetEntry()))
        if (!CreatureUniqueBindings->HasEvents(CREATURE_EVENT_ON_JUST_SUMMONED_CREATURE, me->GET_GUID(), me->GetInstanceId()))
            return false;

    LOCK_ELUNA;
    Push(me);
    Push(summon);
    return CallAllFunctionsBool(CreatureEventBindings, CreatureUniqueBindings, CREATURE_EVENT_ON_JUST_SUMMONED_CREATURE, me->GetEntry(), me->GET_GUID(), me->GetInstanceId());
}

// Called when a summoned creature is despawned
bool Eluna::SummonedCreatureDespawn(Creature* me, Creature* summon)
{
    if (!CreatureEventBindings->HasEvents(CREATURE_EVENT_ON_SUMMONED_CREATURE_DESPAWN, me->GetEntry()))
        if (!CreatureUniqueBindings->HasEvents(CREATURE_EVENT_ON_SUMMONED_CREATURE_DESPAWN, me->GET_GUID(), me->GetInstanceId()))
            return false;

    LOCK_ELUNA;
    Push(me);
    Push(summon);
    return CallAllFunctionsBool(CreatureEventBindings, CreatureUniqueBindings, CREATURE_EVENT_ON_SUMMONED_CREATURE_DESPAWN, me->GetEntry(), me->GET_GUID(), me->GetInstanceId());
}

//Called at waypoint reached or PointMovement end
bool Eluna::MovementInform(Creature* me, uint32 type, uint32 id)
{
    if (!CreatureEventBindings->HasEvents(CREATURE_EVENT_ON_REACH_WP, me->GetEntry()))
        if (!CreatureUniqueBindings->HasEvents(CREATURE_EVENT_ON_REACH_WP, me->GET_GUID(), me->GetInstanceId()))
            return false;

    LOCK_ELUNA;
    Push(me);
    Push(type);
    Push(id);
    return CallAllFunctionsBool(CreatureEventBindings, CreatureUniqueBindings, CREATURE_EVENT_ON_REACH_WP, me->GetEntry(), me->GET_GUID(), me->GetInstanceId());
}

// Called before EnterCombat even before the creature is in combat.
bool Eluna::AttackStart(Creature* me, Unit* target)
{
    if (!CreatureEventBindings->HasEvents(CREATURE_EVENT_ON_PRE_COMBAT, me->GetEntry()))
        if (!CreatureUniqueBindings->HasEvents(CREATURE_EVENT_ON_PRE_COMBAT, me->GET_GUID(), me->GetInstanceId()))
            return false;

    LOCK_ELUNA;
    Push(me);
    Push(target);
    return CallAllFunctionsBool(CreatureEventBindings, CreatureUniqueBindings, CREATURE_EVENT_ON_PRE_COMBAT, me->GetEntry(), me->GET_GUID(), me->GetInstanceId());
}

// Called for reaction at stopping attack at no attackers or targets
bool Eluna::EnterEvadeMode(Creature* me)
{
    On_Reset(me);

    if (!CreatureEventBindings->HasEvents(CREATURE_EVENT_ON_LEAVE_COMBAT, me->GetEntry()))
        if (!CreatureUniqueBindings->HasEvents(CREATURE_EVENT_ON_LEAVE_COMBAT, me->GET_GUID(), me->GetInstanceId()))
            return false;

    LOCK_ELUNA;
    Push(me);
    return CallAllFunctionsBool(CreatureEventBindings, CreatureUniqueBindings, CREATURE_EVENT_ON_LEAVE_COMBAT, me->GetEntry(), me->GET_GUID(), me->GetInstanceId());
}

// Called when the creature is target of hostile action: swing, hostile spell landed, fear/etc)
bool Eluna::AttackedBy(Creature* me, Unit* attacker)
{
    if (!CreatureEventBindings->HasEvents(CREATURE_EVENT_ON_ATTACKED_AT, me->GetEntry()))
        if (!CreatureUniqueBindings->HasEvents(CREATURE_EVENT_ON_ATTACKED_AT, me->GET_GUID(), me->GetInstanceId()))
            return false;

    LOCK_ELUNA;
    Push(me);
    Push(attacker);
    return CallAllFunctionsBool(CreatureEventBindings, CreatureUniqueBindings, CREATURE_EVENT_ON_ATTACKED_AT, me->GetEntry(), me->GET_GUID(), me->GetInstanceId());
}

// Called when creature is spawned or respawned (for reseting variables)
bool Eluna::JustRespawned(Creature* me)
{
    On_Reset(me);

    if (!CreatureEventBindings->HasEvents(CREATURE_EVENT_ON_SPAWN, me->GetEntry()))
        if (!CreatureUniqueBindings->HasEvents(CREATURE_EVENT_ON_SPAWN, me->GET_GUID(), me->GetInstanceId()))
            return false;

    LOCK_ELUNA;
    Push(me);
    return CallAllFunctionsBool(CreatureEventBindings, CreatureUniqueBindings, CREATURE_EVENT_ON_SPAWN, me->GetEntry(), me->GET_GUID(), me->GetInstanceId());
}

// Called at reaching home after evade
bool Eluna::JustReachedHome(Creature* me)
{
    if (!CreatureEventBindings->HasEvents(CREATURE_EVENT_ON_REACH_HOME, me->GetEntry()))
        if (!CreatureUniqueBindings->HasEvents(CREATURE_EVENT_ON_REACH_HOME, me->GET_GUID(), me->GetInstanceId()))
            return false;

    LOCK_ELUNA;
    Push(me);
    return CallAllFunctionsBool(CreatureEventBindings, CreatureUniqueBindings, CREATURE_EVENT_ON_REACH_HOME, me->GetEntry(), me->GET_GUID(), me->GetInstanceId());
}

// Called at text emote receive from player
bool Eluna::ReceiveEmote(Creature* me, Player* player, uint32 emoteId)
{
    if (!CreatureEventBindings->HasEvents(CREATURE_EVENT_ON_RECEIVE_EMOTE, me->GetEntry()))
        if (!CreatureUniqueBindings->HasEvents(CREATURE_EVENT_ON_RECEIVE_EMOTE, me->GET_GUID(), me->GetInstanceId()))
            return false;

    LOCK_ELUNA;
    Push(me);
    Push(player);
    Push(emoteId);
    return CallAllFunctionsBool(CreatureEventBindings, CreatureUniqueBindings, CREATURE_EVENT_ON_RECEIVE_EMOTE, me->GetEntry(), me->GET_GUID(), me->GetInstanceId());
}

// called when the corpse of this creature gets removed
bool Eluna::CorpseRemoved(Creature* me, uint32& respawnDelay)
{
    if (!CreatureEventBindings->HasEvents(CREATURE_EVENT_ON_CORPSE_REMOVED, me->GetEntry()))
        if (!CreatureUniqueBindings->HasEvents(CREATURE_EVENT_ON_CORPSE_REMOVED, me->GET_GUID(), me->GetInstanceId()))
            return false;

    LOCK_ELUNA;
    bool result = false;
    Push(me);
    Push(respawnDelay);
    int respawnDelayIndex = lua_gettop(L);
    int n = SetupStack(CreatureEventBindings, CreatureUniqueBindings, CREATURE_EVENT_ON_CORPSE_REMOVED, me->GetEntry(), me->GET_GUID(), me->GetInstanceId(), 2);

    while (n > 0)
    {
        int r = CallOneFunction(n--, 2, 2);

        if (lua_isboolean(L, r + 0) && lua_toboolean(L, r + 0))
            result = true;

        if (lua_isnumber(L, r + 1))
        {
            respawnDelay = Eluna::CHECKVAL<uint32>(L, r + 1);
            // Update the stack for subsequent calls.
            ReplaceArgument(respawnDelay, respawnDelayIndex);
        }

        lua_pop(L, 2);
    }

    CleanUpStack(2);
    return result;
}

bool Eluna::MoveInLineOfSight(Creature* me, Unit* who)
{
    if (!CreatureEventBindings->HasEvents(CREATURE_EVENT_ON_MOVE_IN_LOS, me->GetEntry()))
        if (!CreatureUniqueBindings->HasEvents(CREATURE_EVENT_ON_MOVE_IN_LOS, me->GET_GUID(), me->GetInstanceId()))
            return false;

    LOCK_ELUNA;
    Push(me);
    Push(who);
    return CallAllFunctionsBool(CreatureEventBindings, CreatureUniqueBindings, CREATURE_EVENT_ON_MOVE_IN_LOS, me->GetEntry(), me->GET_GUID(), me->GetInstanceId());
}

// Called on creature initial spawn, respawn, death, evade (leave combat)
void Eluna::On_Reset(Creature* me) // Not an override, custom
{
    if (!CreatureEventBindings->HasEvents(CREATURE_EVENT_ON_RESET, me->GetEntry()))
        if (!CreatureUniqueBindings->HasEvents(CREATURE_EVENT_ON_RESET, me->GET_GUID(), me->GetInstanceId()))
            return;

    LOCK_ELUNA;
    Push(me);
    CallAllFunctions(CreatureEventBindings, CreatureUniqueBindings, CREATURE_EVENT_ON_RESET, me->GetEntry(), me->GET_GUID(), me->GetInstanceId());
}

// Called when hit by a spell
bool Eluna::SpellHit(Creature* me, Unit* caster, SpellInfo const* spell)
{
    if (!CreatureEventBindings->HasEvents(CREATURE_EVENT_ON_HIT_BY_SPELL, me->GetEntry()))
        if (!CreatureUniqueBindings->HasEvents(CREATURE_EVENT_ON_HIT_BY_SPELL, me->GET_GUID(), me->GetInstanceId()))
            return false;

    LOCK_ELUNA;
    Push(me);
    Push(caster);
    Push(spell->Id); // Pass spell object?
    return CallAllFunctionsBool(CreatureEventBindings, CreatureUniqueBindings, CREATURE_EVENT_ON_HIT_BY_SPELL, me->GetEntry(), me->GET_GUID(), me->GetInstanceId());
}

// Called when spell hits a target
bool Eluna::SpellHitTarget(Creature* me, Unit* target, SpellInfo const* spell)
{
    if (!CreatureEventBindings->HasEvents(CREATURE_EVENT_ON_SPELL_HIT_TARGET, me->GetEntry()))
        if (!CreatureUniqueBindings->HasEvents(CREATURE_EVENT_ON_SPELL_HIT_TARGET, me->GET_GUID(), me->GetInstanceId()))
            return false;

    LOCK_ELUNA;
    Push(me);
    Push(target);
    Push(spell->Id); // Pass spell object?
    return CallAllFunctionsBool(CreatureEventBindings, CreatureUniqueBindings, CREATURE_EVENT_ON_SPELL_HIT_TARGET, me->GetEntry(), me->GET_GUID(), me->GetInstanceId());
}

#ifdef TRINITY

bool Eluna::SummonedCreatureDies(Creature* me, Creature* summon, Unit* killer)
{
    if (!CreatureEventBindings->HasEvents(CREATURE_EVENT_ON_SUMMONED_CREATURE_DIED, me->GetEntry()))
        if (!CreatureUniqueBindings->HasEvents(CREATURE_EVENT_ON_SUMMONED_CREATURE_DIED, me->GET_GUID(), me->GetInstanceId()))
            return false;

    LOCK_ELUNA;
    Push(me);
    Push(summon);
    Push(killer);
    return CallAllFunctionsBool(CreatureEventBindings, CreatureUniqueBindings, CREATURE_EVENT_ON_SUMMONED_CREATURE_DIED, me->GetEntry(), me->GET_GUID(), me->GetInstanceId());
}

// Called when owner takes damage
bool Eluna::OwnerAttackedBy(Creature* me, Unit* attacker)
{
    if (!CreatureEventBindings->HasEvents(CREATURE_EVENT_ON_OWNER_ATTACKED_AT, me->GetEntry()))
        if (!CreatureUniqueBindings->HasEvents(CREATURE_EVENT_ON_OWNER_ATTACKED_AT, me->GET_GUID(), me->GetInstanceId()))
            return false;

    LOCK_ELUNA;
    Push(me);
    Push(attacker);
    return CallAllFunctionsBool(CreatureEventBindings, CreatureUniqueBindings, CREATURE_EVENT_ON_OWNER_ATTACKED_AT, me->GetEntry(), me->GET_GUID(), me->GetInstanceId());
}

// Called when owner attacks something
bool Eluna::OwnerAttacked(Creature* me, Unit* target)
{
    if (!CreatureEventBindings->HasEvents(CREATURE_EVENT_ON_OWNER_ATTACKED, me->GetEntry()))
        if (!CreatureUniqueBindings->HasEvents(CREATURE_EVENT_ON_OWNER_ATTACKED, me->GET_GUID(), me->GetInstanceId()))
            return false;

    LOCK_ELUNA;
    Push(me);
    Push(target);
    return CallAllFunctionsBool(CreatureEventBindings, CreatureUniqueBindings, CREATURE_EVENT_ON_OWNER_ATTACKED, me->GetEntry(), me->GET_GUID(), me->GetInstanceId());
}

#endif // TRINITY
#endif // _CREATURE_HOOKS_H
