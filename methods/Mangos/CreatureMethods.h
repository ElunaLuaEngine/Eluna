/*
* Copyright (C) 2010 - 2024 Eluna Lua Engine <https://elunaluaengine.github.io/>
* This program is free software licensed under GPL version 3
* Please see the included DOCS/LICENSE.md for more information
*/

#ifndef CREATUREMETHODS_H
#define CREATUREMETHODS_H

/***
 * Non-[Player] controlled [Unit]s (i.e. NPCs).
 *
 * Inherits all methods from: [Object], [WorldObject], [Unit]
 */
namespace LuaCreature
{
    /**
     * Returns `true` if the [Creature] can regenerate health,
     *   and returns `false` otherwise.
     *
     * @return bool isRegenerating
     */
    int IsRegeneratingHealth(Eluna* E, Creature* creature)
    {
        E->Push(creature->IsRegeneratingHealth());
        return 1;
    }

    /**
     * Returns `true` if the [Creature] is set to not give reputation when killed,
     *   and returns `false` otherwise.
     *
     * @return bool reputationDisabled
     */
    int IsReputationGainDisabled(Eluna* E, Creature* creature)
    {
        E->Push(creature->IsReputationGainDisabled());
        return 1;
    }

    /**
     * Returns `true` if the [Creature] completes the [Quest] with the ID `questID`,
     *   and returns `false` otherwise.
     *
     * @param uint32 questID : the ID of a [Quest]
     * @return bool completesQuest
     */
    int CanCompleteQuest(Eluna* E, Creature* creature)
    {
        uint32 quest_id = E->CHECKVAL<uint32>(2);

        E->Push(creature->HasInvolvedQuest(quest_id));
        return 1;
    }

    /**
     * Returns `true` if the [Creature] can be targeted for attack,
     *   and returns `false` otherwise.
     *
     * @param bool mustBeDead = false : if `true`, only returns `true` if the [Creature] is also dead. Otherwise, it must be alive.
     * @return bool targetable
     */
    int IsTargetableForAttack(Eluna* E, Creature* creature)
    {
        bool mustBeDead = E->CHECKVAL<bool>(2, false);

        E->Push(creature->IsTargetableForAttack(mustBeDead));
        return 1;
    }

    /**
     * Returns `true` if the [Creature] can assist `friend` in combat against `enemy`,
     *   and returns `false` otherwise.
     *
     * @param [Unit] friend : the Unit we will be assisting
     * @param [Unit] enemy : the Unit that we would attack if we assist `friend`
     * @param bool checkFaction = true : if `true`, the [Creature] must be the same faction as `friend` to assist
     * @return bool canAssist
     */
    int CanAssistTo(Eluna* E, Creature* creature)
    {
        Unit* u = E->CHECKOBJ<Unit>(2);
        Unit* enemy = E->CHECKOBJ<Unit>(3);
        bool checkfaction = E->CHECKVAL<bool>(4, true);

        E->Push(creature->CanAssistTo(u, enemy, checkfaction));
        return 1;
    }

    /**
     * Returns `true` if the [Creature] has searched for combat assistance already,
     *   and returns `false` otherwise.
     *
     * @return bool searchedForAssistance
     */
    int HasSearchedAssistance(Eluna* E, Creature* creature)
    {
        E->Push(creature->HasSearchedAssistance());
        return 1;
    }

    /**
     * Returns `true` if the [Creature] will give its loot to `player`,
     *   and returns `false` otherwise.
     *
     * @return bool tapped
     */
    int IsTappedBy(Eluna* E, Creature* creature)
    {
        Player* player = E->CHECKOBJ<Player>(2);

        E->Push(creature->IsTappedBy(player));
        return 1;
    }

    /**
     * Returns `true` if the [Creature] will give its loot to a [Player] or [Group],
     *   and returns `false` otherwise.
     *
     * @return bool hasLootRecipient
     */
    int HasLootRecipient(Eluna* E, Creature* creature)
    {
        E->Push(creature->HasLootRecipient());
        return 1;
    }

    /**
     * Returns `true` if the [Creature] can start attacking nearby hostile [Unit]s,
     *   and returns `false` otherwise.
     *
     * @return bool canAggro
     */
    int CanAggro(Eluna* E, Creature* creature)
    {
        E->Push(!creature->HasFlag(UNIT_FIELD_FLAGS, UNIT_FLAG_PASSIVE));
        return 1;
    }

    /**
     * Returns `true` if the [Creature] can move through deep water,
     *   and returns `false` otherwise.
     *
     * @return bool canSwim
     */
    int CanSwim(Eluna* E, Creature* creature)
    {
        E->Push(creature->CanSwim());
        return 1;
    }

    /**
     * Returns `true` if the [Creature] can move on land,
     *   and returns `false` otherwise.
     *
     * @return bool canWalk
     */
    int CanWalk(Eluna* E, Creature* creature)
    {
        E->Push(creature->CanWalk());
        return 1;
    }

    /**
     * Returns `true` if the [Creature] is returning to its spawn position from combat,
     *   and returns `false` otherwise.
     *
     * @return bool inEvadeMode
     */
    int IsInEvadeMode(Eluna* E, Creature* creature)
    {
        E->Push(creature->IsInEvadeMode());
        return 1;
    }

    /**
     * Returns `true` if the [Creature]'s rank is Elite or Rare Elite,
     *   and returns `false` otherwise.
     *
     * @return bool isElite
     */
    int IsElite(Eluna* E, Creature* creature)
    {
        E->Push(creature->IsElite());
        return 1;
    }

    /**
     * Returns `true` if the [Creature] is a city guard,
     *   and returns `false` otherwise.
     *
     * @return bool isGuard
     */
    int IsGuard(Eluna* E, Creature* creature)
    {
        E->Push(creature->IsGuard());
        return 1;
    }

    /**
     * Returns `true` if the [Creature] is a civilian,
     *   and returns `false` otherwise.
     *
     * @return bool isCivilian
     */
    int IsCivilian(Eluna* E, Creature* creature)
    {
        E->Push(creature->IsCivilian());
        return 1;
    }

    /**
     * Returns `true` if the [Creature] is the leader of a player faction,
     *   and returns `false` otherwise.
     *
     * @return bool isLeader
     */
    int IsRacialLeader(Eluna* E, Creature* creature)
    {
        E->Push(creature->IsRacialLeader());
        return 1;
    }

    /**
     * Returns `true` if the [Creature]'s rank is Boss,
     *   and returns `false` otherwise.
     *
     * @return bool isWorldBoss
     */
    int IsWorldBoss(Eluna* E, Creature* creature)
    {
        E->Push(creature->IsWorldBoss());
        return 1;
    }

    /**
     * Returns `true` if the [Creature] cannot cast `spellId` due to a category cooldown,
     *   and returns `false` otherwise.
     *
     * @param uint32 spellId : the ID of a [Spell]
     * @return bool hasCooldown
     */
    int HasCategoryCooldown(Eluna* E, Creature* creature)
    {
        uint32 spell = E->CHECKVAL<uint32>(2);

        E->Push(creature->HasCategoryCooldown(spell));
        return 1;
    }

    /**
     * Returns `true` if the [Creature] can cast `spellId` when mind-controlled,
     *   and returns `false` otherwise.
     *
     * @param uint32 spellId : the ID of a [Spell]
     * @return bool hasSpell
     */
    int HasSpell(Eluna* E, Creature* creature)
    {
        uint32 id = E->CHECKVAL<uint32>(2);

        E->Push(creature->HasSpell(id));
        return 1;
    }

    /**
     * Returns `true` if the [Creature] starts the [Quest] `questId`,
     *   and returns `false` otherwise.
     *
     * @param uint32 questId : the ID of a [Quest]
     * @return bool hasQuest
     */
    int HasQuest(Eluna* E, Creature* creature)
    {
        uint32 questId = E->CHECKVAL<uint32>(2);

        E->Push(creature->HasQuest(questId));
        return 1;
    }

    /**
     * Returns `true` if the [Creature] has `spellId` on cooldown,
     *   and returns `false` otherwise.
     *
     * @param uint32 spellId : the ID of a [Spell]
     * @return bool hasCooldown
     */
    int HasSpellCooldown(Eluna* E, Creature* creature)
    {
        uint32 spellId = E->CHECKVAL<uint32>(2);

        E->Push(creature->HasSpellCooldown(spellId));
        return 1;
    }

    /**
     * Returns `true` if the [Creature] can fly,
     *   and returns `false` otherwise.
     *
     * @return bool canFly
     */
    int CanFly(Eluna* E, Creature* creature)
    {
        E->Push(creature->CanFly());
        return 1;
    }

    /**
     * Returns the time it takes for this [Creature] to respawn once killed.
     *
     * This value does not usually change over a [Creature]'s lifespan,
     *   but can be modified by [Creature:SetRespawnDelay].
     *
     * @return uint32 respawnDelay : the respawn delay, in seconds
     */
    int GetRespawnDelay(Eluna* E, Creature* creature)
    {
        E->Push(creature->GetRespawnDelay());
        return 1;
    }

    /**
     * Returns the radius the [Creature] is permitted to wander from its
     *   respawn point.
     *
     * @return float wanderRadius
     */
    int GetWanderRadius(Eluna* E, Creature* creature)
    {
        E->Push(creature->GetRespawnRadius());
        return 1;
    }

    /**
     * Returns the current waypoint ID of the [Creature].
     *
     * @return uint32 wpId
     */
    int GetCurrentWaypointId(Eluna* E, Creature* creature)
    {
        E->Push(creature->GetMotionMaster()->getLastReachedWaypoint());
        return 1;
    }

    /**
     * Returns the default movement type for this [Creature].
     *
     * @return [MovementGeneratorType] defaultMovementType
     */
    int GetDefaultMovementType(Eluna* E, Creature* creature)
    {
        E->Push(creature->GetDefaultMovementType());
        return 1;
    }

    /**
     * Returns the aggro range of the [Creature] for `target`.
     *
     * @param [Unit] target
     * @return float aggroRange
     */
    int GetAggroRange(Eluna* E, Creature* creature)
    {
        Unit* target = E->CHECKOBJ<Unit>(2);

        float AttackDist = creature->GetAttackDistance(target);
        float ThreatRadius = sWorld.getConfig(CONFIG_FLOAT_THREAT_RADIUS);
        E->Push(ThreatRadius > AttackDist ? ThreatRadius : AttackDist);
        return 1;
    }

    /**
     * Returns the effective aggro range of the [Creature] for `target`.
     *
     * If this is smaller than the minimum aggro range set in the config file,
     *   that is used as the aggro range instead.
     *
     * @param [Unit] target
     * @return float attackDistance
     */
    int GetAttackDistance(Eluna* E, Creature* creature)
    {
        Unit* target = E->CHECKOBJ<Unit>(2);

        E->Push(creature->GetAttackDistance(target));
        return 1;
    }

    /**
     * Returns the [Group] that can loot this [Creature].
     *
     * @return [Group] lootRecipientGroup : the group or `nil`
     */
    int GetLootRecipientGroup(Eluna* E, Creature* creature)
    {
        E->Push(creature->GetGroupLootRecipient());
        return 1;
    }

    /**
     * Returns the [Player] that can loot this [Creature].
     *
     * @return [Player] lootRecipient : the player or `nil`
     */
    int GetLootRecipient(Eluna* E, Creature* creature)
    {
        E->Push(creature->GetLootRecipient());
        return 1;
    }

    /**
     * Returns the [Creature]'s script name.
     *
     * This is used by the core to apply C++ scripts to the Creature.
     *
     * It is not used by Eluna. Eluna will override AI scripts.
     *
     * @return string scriptName
     */
    int GetScriptName(Eluna* E, Creature* creature)
    {
        E->Push(creature->GetScriptName());
        return 1;
    }

    /**
     * Returns the [Creature]'s AI name.
     *
     * This is used by the core to assign the Creature's default AI.
     *
     * If the Creature is scripted by Eluna, the AI is overriden.
     *
     * @return string AIName
     */
    int GetAIName(Eluna* E, Creature* creature)
    {
        E->Push(creature->GetAIName());
        return 1;
    }

    /**
     * Returns the [Creature]'s script ID.
     *
     * Every C++ script name is assigned a unique ID by the core.
     *   This returns the ID for this [Creature]'s script name.
     *
     * @return uint32 scriptID
     */
    int GetScriptId(Eluna* E, Creature* creature)
    {
        E->Push(creature->GetScriptId());
        return 1;
    }

    /**
     * Returns the [Creature]'s cooldown for `spellID`.
     *
     * @param uint32 spellID
     * @return uint32 cooldown : the cooldown, in milliseconds
     */
    int GetCreatureSpellCooldownDelay(Eluna* E, Creature* creature)
    {
        uint32 spell = E->CHECKVAL<uint32>(2);

        E->Push(creature->GetCreatureSpellCooldownDelay(spell));
        return 1;
    }

    /**
     * Returns the delay between when the [Creature] dies and when its body despawns.
     *
     * @return uint32 corpseDelay : the delay, in seconds
     */
    int GetCorpseDelay(Eluna* E, Creature* creature)
    {
        E->Push(creature->GetCorpseDelay());
        return 1;
    }

    /**
     * Returns position the [Creature] returns to when evading from combat
     *   or respawning.
     *
     * @return float x
     * @return float y
     * @return float z
     * @return float o
     */
    int GetHomePosition(Eluna* E, Creature* creature)
    {
        float x, y, z, o;
        creature->GetRespawnCoord(x, y, z, &o);

        E->Push(x);
        E->Push(y);
        E->Push(z);
        E->Push(o);
        return 4;
    }

    /**
     * Sets the position the [Creature] returns to when evading from combat
     *   or respawning.
     *
     * @param float x
     * @param float y
     * @param float z
     * @param float o
     */
    int SetHomePosition(Eluna* E, Creature* creature)
    {
        float x = E->CHECKVAL<float>(2);
        float y = E->CHECKVAL<float>(3);
        float z = E->CHECKVAL<float>(4);
        float o = E->CHECKVAL<float>(5);

        creature->SetRespawnCoord(x, y, z, o);
        return 0;
    }

    enum SelectAggroTarget
    {
        SELECT_TARGET_RANDOM = 0,   // Just selects a random target
        SELECT_TARGET_TOPAGGRO,     // Selects targes from top aggro to bottom
        SELECT_TARGET_BOTTOMAGGRO,  // Selects targets from bottom aggro to top
        SELECT_TARGET_NEAREST,
        SELECT_TARGET_FARTHEST
    };

    /**
    * Returns a target from the [Creature]'s threat list based on the
    *   supplied arguments.
    *
    *     enum SelectAggroTarget
    *     {
    *         SELECT_TARGET_RANDOM = 0,  //Just selects a random target
    *         SELECT_TARGET_TOPAGGRO,    //Selects targets from top aggro to bottom
    *         SELECT_TARGET_BOTTOMAGGRO, //Selects targets from bottom aggro to top
    *         SELECT_TARGET_NEAREST,
    *         SELECT_TARGET_FARTHEST
    *     };
    *
    * For example, if you wanted to select the third-farthest [Player]
    *   within 50 yards that has the [Aura] "Corrupted Blood" (ID 24328),
    *   you could use this function like so:
    *
    *     target = creature:GetAITarget(4, true, 3, 50, 24328)
    *
    * @param [SelectAggroTarget] targetType : how the threat list should be sorted
    * @param bool playerOnly = false : if `true`, skips targets that aren't [Player]s
    * @param uint32 position = 0 : used as an offset into the threat list. If `targetType` is random, used as the number of players from top of aggro to choose from
    * @param float distance = 0.0 : if positive, the maximum distance for the target. If negative, the minimum distance
    * @param int32 aura = 0 : if positive, the target must have this [Aura]. If negative, the the target must not have this Aura
    * @return [Unit] target : the target, or `nil`
    */
    int GetAITarget(Eluna* E, Creature* creature)
    {
        uint32 targetType = E->CHECKVAL<uint32>(2);
        bool playerOnly = E->CHECKVAL<bool>(3, false);
        uint32 position = E->CHECKVAL<uint32>(4, 0);
        float dist = E->CHECKVAL<float>(5, 0.0f);
        int32 aura = E->CHECKVAL<int32>(6, 0);

        ThreatList const& threatlist = creature->GetThreatManager().getThreatList();

        if (threatlist.empty())
            return 1;
        if (position >= threatlist.size())
            return 1;

        std::list<Unit*> targetList;

        for (auto itr = threatlist.begin(); itr != threatlist.end(); ++itr)
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
                    E->Push(*itr);
                }
                break;
            case SELECT_TARGET_FARTHEST:
            case SELECT_TARGET_BOTTOMAGGRO:
                {
                    std::list<Unit*>::reverse_iterator ritr = targetList.rbegin();
                    if (position)
                        std::advance(ritr, position);
                    E->Push(*ritr);
                }
                break;
            case SELECT_TARGET_RANDOM:
                {
                    std::list<Unit*>::const_iterator itr = targetList.begin();
                    if (position)
                        std::advance(itr, urand(0, position));
                    else
                        std::advance(itr, urand(0, targetList.size() - 1));
                    E->Push(*itr);
                }
                break;
            default:
                luaL_argerror(E->L, 2, "SelectAggroTarget expected");
                break;
        }

        return 1;
    }

    /**
     * Returns all [Unit]s in the [Creature]'s threat list.
     *
     * @return table targets
     */
    int GetAITargets(Eluna* E, Creature* creature)
    {
        ThreatList const& threatlist = creature->GetThreatManager().getThreatList();

        lua_createtable(E->L, threatlist.size(), 0);
        int tbl = lua_gettop(E->L);
        uint32 i = 0;

        for (auto itr = threatlist.begin(); itr != threatlist.end(); ++itr)
        {
            Unit* target = (*itr)->getTarget();

            if (!target)
                continue;
            E->Push(target);
            lua_rawseti(E->L, tbl, ++i);
        }

        lua_settop(E->L, tbl);
        return 1;
    }

    /**
     * Returns the number of [Unit]s in this [Creature]'s threat list.
     *
     * @return double targetsCount
     */
    int GetAITargetsCount(Eluna* E, Creature* creature)
    {
        E->Push((double)creature->GetThreatManager().getThreatList().size());
        return 1;
    }

    /**
     * Returns the [Creature]'s NPC flags.
     *
     * These are used to control whether the NPC is a vendor, can repair items,
     *   can give quests, etc.
     *
     * @return [NPCFlags] npcFlags
     */
    int GetNPCFlags(Eluna* E, Creature* creature)
    {
        E->Push(creature->GetUInt32Value(UNIT_NPC_FLAGS));
        return 1;
    }

    /**
     * Returns the [Creature]'s Extra flags.
     *
     * These are used to control whether the NPC is a civilian, uses pathfinding,
     *   if it's a guard, etc.
     *
     * @return [ExtraFlags] extraFlags
     */
    int GetExtraFlags(Eluna* E, Creature* creature)
    {
        E->Push(creature->GetCreatureInfo()->ExtraFlags);
        return 1;
    }

#if defined(CLASSIC) || defined(TBC) || defined(WOTLK)
    /**
     * Returns the [Creature]'s shield block value.
     *
     * @return uint32 shieldBlockValue
     */
    int GetShieldBlockValue(Eluna* E, Creature* creature)
    {
        E->Push(creature->GetShieldBlockValue());
        return 1;
    }
#endif

    /**
     * Returns the guid of the [Creature] that is used as the ID in the database
     *
     * @return uint32 dbguid
     */
    int GetDBTableGUIDLow(Eluna* E, Creature* creature)
    {
        // on mangos based this is same as lowguid
        E->Push(creature->GetGUIDLow());
        return 1;
    }

    /**
     * Sets the [Creature]'s NPC flags to `flags`.
     *
     * @param [NPCFlags] flags
     */
    int SetNPCFlags(Eluna* E, Creature* creature)
    {
        uint32 flags = E->CHECKVAL<uint32>(2);

        creature->SetUInt32Value(UNIT_NPC_FLAGS, flags);
        return 0;
    }

    /**
     * Makes the [Creature] able to fly if enabled.
     *
     * @param bool disable
     */
    int SetDisableGravity(Eluna* E, Creature* creature)
    {
        bool disable = E->CHECKVAL<bool>(2);

        creature->SetLevitate(disable);
        return 0;
    }

    /**
     * Sets the [Creature]'s death state to `deathState`.
     *
     * @param [DeathState] deathState
     */
    int SetDeathState(Eluna* E, Creature* creature)
    {
        int32 state = E->CHECKVAL<int32>(2);

        creature->SetDeathState((DeathState)state);
        return 0;
    }

    /**
     * Sets whether the [Creature] is currently walking or running.
     *
     * @param bool enable = true : `true` to enable walking, `false` for running
     */
    int SetWalk(Eluna* E, Creature* creature)           // TODO: Move same to Player ?
    {
        bool enable = E->CHECKVAL<bool>(2, true);

        creature->SetWalk(enable);
        return 0;
    }

    /**
     * Equips given [Item]s to the [Unit]. Using 0 removes the equipped [Item]
     *
     * @param uint32 main_hand : main hand [Item]'s entry
     * @param uint32 off_hand : off hand [Item]'s entry
     * @param uint32 ranged : ranged [Item]'s entry
     */
    int SetEquipmentSlots(Eluna* E, Creature* creature)
    {
        uint32 main_hand = E->CHECKVAL<uint32>(2);
        uint32 off_hand = E->CHECKVAL<uint32>(3);
        uint32 ranged = E->CHECKVAL<uint32>(4);

        creature->SetVirtualItem(VIRTUAL_ITEM_SLOT_0, main_hand);
        creature->SetVirtualItem(VIRTUAL_ITEM_SLOT_1, off_hand);
        creature->SetVirtualItem(VIRTUAL_ITEM_SLOT_2, ranged);
        return 0;
    }

    /**
     * Sets whether the [Creature] can be aggroed.
     *
     * @param bool allow = true : `true` to allow aggro, `false` to disable aggro
     */
    int SetAggroEnabled(Eluna* E, Creature* creature)
    {
        bool allow = E->CHECKVAL<bool>(2, true);

        if (allow)
            creature->RemoveFlag(UNIT_FIELD_FLAGS, UNIT_FLAG_PASSIVE);
        else
            creature->SetFlag(UNIT_FIELD_FLAGS, UNIT_FLAG_PASSIVE);

        return 0;
    }

    /**
     * Sets whether the [Creature] gives reputation or not.
     *
     * @param bool disable = true : `true` to disable reputation, `false` to enable
     */
    int SetDisableReputationGain(Eluna* E, Creature* creature)
    {
        bool disable = E->CHECKVAL<bool>(2, true);

        creature->SetDisableReputationGain(disable);
        return 0;
    }

    /**
     * Sets the [Creature] as in combat with all [Player]s in the dungeon instance.
     *
     * This is used by raid bosses to prevent Players from using out-of-combat
     *   actions once the encounter has begun.
     */
    int SetInCombatWithZone(Eluna* /*E*/, Creature* creature)
    {
        creature->SetInCombatWithZone();
        return 0;
    }

    /**
     * Sets the distance the [Creature] can wander from it's spawn point.
     *
     * @param float distance
     */
    int SetWanderRadius(Eluna* E, Creature* creature)
    {
        float dist = E->CHECKVAL<float>(2);

        creature->SetRespawnRadius(dist);
        return 0;
    }

    /**
     * Sets the time it takes for the [Creature] to respawn when killed.
     *
     * @param uint32 delay : the delay, in seconds
     */
    int SetRespawnDelay(Eluna* E, Creature* creature)
    {
        uint32 delay = E->CHECKVAL<uint32>(2);

        creature->SetRespawnDelay(delay);
        return 0;
    }

    /**
     * Sets the default movement type of the [Creature].
     *
     * @param [MovementGeneratorType] type
     */
    int SetDefaultMovementType(Eluna* E, Creature* creature)
    {
        int32 type = E->CHECKVAL<int32>(2);

        creature->SetDefaultMovementType((MovementGeneratorType)type);
        return 0;
    }

    /**
     * Sets whether the [Creature] can search for assistance at low health or not.
     *
     * @param bool enable = true : `true` to disable searching, `false` to allow
     */
    int SetNoSearchAssistance(Eluna* E, Creature* creature)
    {
        bool val = E->CHECKVAL<bool>(2, true);

        creature->SetNoSearchAssistance(val);
        return 0;
    }

    /**
     * Sets whether the [Creature] can call nearby enemies for help in combat or not.
     *
     * @param bool enable = true : `true` to disable calling for help, `false` to enable
     */
    int SetNoCallAssistance(Eluna* E, Creature* creature)
    {
        bool val = E->CHECKVAL<bool>(2, true);

        creature->SetNoCallAssistance(val);
        return 0;
    }

    /**
     * Sets whether the creature is hovering / levitating or not.
     *
     * @param bool enable = true : `true` to enable hovering, `false` to disable
     */
    int SetHover(Eluna* E, Creature* creature)
    {
        bool enable = E->CHECKVAL<bool>(2, true);

        // Copy paste from Aura::HandleAuraHover
        // TODO: implement core side properly
        WorldPacket data;
        if (enable)
            data.Initialize(SMSG_MOVE_SET_HOVER, 8 + 4);
        else
            data.Initialize(SMSG_MOVE_UNSET_HOVER, 8 + 4);
        data << creature->GetPackGUID();
        data << uint32(0);

        creature->SendMessageToSet(&data, true);
        return 0;
    }

    /**
     * Despawn this [Creature].
     *
     * @param uint32 delay = 0 : dely to despawn in milliseconds
     */
    int DespawnOrUnsummon(Eluna* E, Creature* creature)
    {
        uint32 msTimeToDespawn = E->CHECKVAL<uint32>(2, 0);

        creature->ForcedDespawn(msTimeToDespawn);
        return 0;
    }

    /**
     * Respawn this [Creature].
     */
    int Respawn(Eluna* /*E*/, Creature* creature)
    {
        creature->Respawn();
        return 0;
    }

    /**
     * Remove this [Creature]'s corpse.
     */
    int RemoveCorpse(Eluna* /*E*/, Creature* creature)
    {
        creature->RemoveCorpse();
        return 0;
    }

    /**
     * Make the [Creature] start following its waypoint path.
     */
    int MoveWaypoint(Eluna* /*E*/, Creature* creature)
    {
        creature->GetMotionMaster()->MoveWaypoint();
        return 0;
    }

    /**
     * Make the [Creature] call for assistance in combat from other nearby [Creature]s.
     */
    int CallAssistance(Eluna* /*E*/, Creature* creature)
    {
        creature->CallAssistance();
        return 0;
    }

    /**
     * Make the [Creature] call for help in combat from friendly [Creature]s within `radius`.
     *
     * @param float radius
     */
    int CallForHelp(Eluna* E, Creature* creature)
    {
        float radius = E->CHECKVAL<float>(2);

        creature->CallForHelp(radius);
        return 0;
    }

    /**
     * Make the [Creature] flee combat to get assistance from a nearby friendly [Creature].
     */
    int FleeToGetAssistance(Eluna* /*E*/, Creature* creature)
    {
        creature->DoFleeToGetAssistance();
        return 0;
    }

    /**
     * Make the [Creature] attack `target`.
     *
     * @param [Unit] target
     */
    int AttackStart(Eluna* E, Creature* creature)
    {
        Unit* target = E->CHECKOBJ<Unit>(2);

        creature->AI()->AttackStart(target);
        return 0;
    }

    /**
     * Save the [Creature] in the database.
     */
    int SaveToDB(Eluna* /*E*/, Creature* creature)
    {
        creature->SaveToDB();
        return 0;
    }

    /**
     * Make the [Creature] try to find a new target.
     *
     * This should be called every update cycle for the Creature's AI.
     */
    int SelectVictim(Eluna* E, Creature* creature)
    {
        E->Push(creature->SelectHostileTarget());
        return 1;
    }

    /**
     * Transform the [Creature] into another Creature.
     *
     * @param uint32 entry : the Creature ID to transform into
     * @param uint32 dataGUIDLow = 0 : use this Creature's model and equipment instead of the defaults
     */
    int UpdateEntry(Eluna* E, Creature* creature)
    {
        uint32 entry = E->CHECKVAL<uint32>(2);
        uint32 dataGuidLow = E->CHECKVAL<uint32>(3, 0);

        creature->UpdateEntry(entry, ALLIANCE, dataGuidLow ? eObjectMgr->GetCreatureData(dataGuidLow) : NULL);
        return 0;
    }

    /**
     * Returns the [Creature]'s creature family ID (enumerated in CreatureFamily.dbc).
     *
     * <pre>
     * enum CreatureFamily
     * {
     *     CREATURE_FAMILY_NONE                = 0,    // TrinityCore only
     *     CREATURE_FAMILY_WOLF                = 1,
     *     CREATURE_FAMILY_CAT                 = 2,
     *     CREATURE_FAMILY_SPIDER              = 3,
     *     CREATURE_FAMILY_BEAR                = 4,
     *     CREATURE_FAMILY_BOAR                = 5,
     *     CREATURE_FAMILY_CROCOLISK           = 6,
     *     CREATURE_FAMILY_CARRION_BIRD        = 7,
     *     CREATURE_FAMILY_CRAB                = 8,
     *     CREATURE_FAMILY_GORILLA             = 9,
     *     CREATURE_FAMILY_HORSE_CUSTOM        = 10,   // Does not exist in DBC but used for horse like beasts in DB
     *     CREATURE_FAMILY_RAPTOR              = 11,
     *     CREATURE_FAMILY_TALLSTRIDER         = 12,
     *     CREATURE_FAMILY_FELHUNTER           = 15,
     *     CREATURE_FAMILY_VOIDWALKER          = 16,
     *     CREATURE_FAMILY_SUCCUBUS            = 17,
     *     CREATURE_FAMILY_DOOMGUARD           = 19,
     *     CREATURE_FAMILY_SCORPID             = 20,
     *     CREATURE_FAMILY_TURTLE              = 21,
     *     CREATURE_FAMILY_IMP                 = 23,
     *     CREATURE_FAMILY_BAT                 = 24,
     *     CREATURE_FAMILY_HYENA               = 25,
     *     CREATURE_FAMILY_BIRD_OF_PREY        = 26,   // Named CREATURE_FAMILY_OWL in Mangos
     *     CREATURE_FAMILY_WIND_SERPENT        = 27,
     *     CREATURE_FAMILY_REMOTE_CONTROL      = 28,
     *     CREATURE_FAMILY_FELGUARD            = 29,   // This and below is TBC+
     *     CREATURE_FAMILY_DRAGONHAWK          = 30,
     *     CREATURE_FAMILY_RAVAGER             = 31,
     *     CREATURE_FAMILY_WARP_STALKER        = 32,
     *     CREATURE_FAMILY_SPOREBAT            = 33,
     *     CREATURE_FAMILY_NETHER_RAY          = 34,
     *     CREATURE_FAMILY_SERPENT             = 35,
     *     CREATURE_FAMILY_SEA_LION            = 36,   // TBC only
     *     CREATURE_FAMILY_MOTH                = 37,   // This and below is WotLK+
     *     CREATURE_FAMILY_CHIMAERA            = 38,
     *     CREATURE_FAMILY_DEVILSAUR           = 39,
     *     CREATURE_FAMILY_GHOUL               = 40,
     *     CREATURE_FAMILY_SILITHID            = 41,
     *     CREATURE_FAMILY_WORM                = 42,
     *     CREATURE_FAMILY_RHINO               = 43,
     *     CREATURE_FAMILY_WASP                = 44,
     *     CREATURE_FAMILY_CORE_HOUND          = 45,
     *     CREATURE_FAMILY_SPIRIT_BEAST        = 46
     * };
     * </pre>
     *
     * @return [CreatureFamily] creatureFamily
     */
    int GetCreatureFamily(Eluna* E, Creature* creature)
    {
        uint32 entry = creature->GetEntry();

        CreatureInfo const* cInfo = ObjectMgr::GetCreatureTemplate(entry);
        if (cInfo)
            E->Push(cInfo->Family);

        return 1;
    }

    ElunaRegister<Creature> CreatureMethods[] =
    {
        // Getters
        { "GetAITarget", &LuaCreature::GetAITarget },
        { "GetAITargets", &LuaCreature::GetAITargets },
        { "GetAITargetsCount", &LuaCreature::GetAITargetsCount },
        { "GetHomePosition", &LuaCreature::GetHomePosition },
        { "GetCorpseDelay", &LuaCreature::GetCorpseDelay },
        { "GetCreatureSpellCooldownDelay", &LuaCreature::GetCreatureSpellCooldownDelay },
        { "GetScriptId", &LuaCreature::GetScriptId },
        { "GetAIName", &LuaCreature::GetAIName },
        { "GetScriptName", &LuaCreature::GetScriptName },
        { "GetAttackDistance", &LuaCreature::GetAttackDistance },
        { "GetAggroRange", &LuaCreature::GetAggroRange },
        { "GetDefaultMovementType", &LuaCreature::GetDefaultMovementType },
        { "GetRespawnDelay", &LuaCreature::GetRespawnDelay },
        { "GetWanderRadius", &LuaCreature::GetWanderRadius },
        { "GetCurrentWaypointId", &LuaCreature::GetCurrentWaypointId },
        { "GetLootRecipient", &LuaCreature::GetLootRecipient },
        { "GetLootRecipientGroup", &LuaCreature::GetLootRecipientGroup },
        { "GetNPCFlags", &LuaCreature::GetNPCFlags },
        { "GetExtraFlags", &LuaCreature::GetExtraFlags },
        { "GetShieldBlockValue", &LuaCreature::GetShieldBlockValue },
        { "GetDBTableGUIDLow", &LuaCreature::GetDBTableGUIDLow },
        { "GetCreatureFamily", &LuaCreature::GetCreatureFamily },

        // Setters
        { "SetHover", &LuaCreature::SetHover },
        { "SetDisableGravity", &LuaCreature::SetDisableGravity },
        { "SetAggroEnabled", &LuaCreature::SetAggroEnabled },
        { "SetNoCallAssistance", &LuaCreature::SetNoCallAssistance },
        { "SetNoSearchAssistance", &LuaCreature::SetNoSearchAssistance },
        { "SetDefaultMovementType", &LuaCreature::SetDefaultMovementType },
        { "SetRespawnDelay", &LuaCreature::SetRespawnDelay },
        { "SetWanderRadius", &LuaCreature::SetWanderRadius },
        { "SetInCombatWithZone", &LuaCreature::SetInCombatWithZone },
        { "SetDisableReputationGain", &LuaCreature::SetDisableReputationGain },
        { "SetNPCFlags", &LuaCreature::SetNPCFlags },
        { "SetDeathState", &LuaCreature::SetDeathState },
        { "SetWalk", &LuaCreature::SetWalk },
        { "SetHomePosition", &LuaCreature::SetHomePosition },
        { "SetEquipmentSlots", &LuaCreature::SetEquipmentSlots },

        // Boolean
        { "IsRegeneratingHealth", &LuaCreature::IsRegeneratingHealth },
        { "IsWorldBoss", &LuaCreature::IsWorldBoss },
        { "IsRacialLeader", &LuaCreature::IsRacialLeader },
        { "IsCivilian", &LuaCreature::IsCivilian },
        { "IsGuard", &LuaCreature::IsGuard },
        { "IsElite", &LuaCreature::IsElite },
        { "IsInEvadeMode", &LuaCreature::IsInEvadeMode },
        { "HasCategoryCooldown", &LuaCreature::HasCategoryCooldown },
        { "CanWalk", &LuaCreature::CanWalk },
        { "CanSwim", &LuaCreature::CanSwim },
        { "CanAggro", &LuaCreature::CanAggro },
        { "HasSearchedAssistance", &LuaCreature::HasSearchedAssistance },
        { "IsTappedBy", &LuaCreature::IsTappedBy },
        { "HasLootRecipient", &LuaCreature::HasLootRecipient },
        { "CanAssistTo", &LuaCreature::CanAssistTo },
        { "IsTargetableForAttack", &LuaCreature::IsTargetableForAttack },
        { "CanCompleteQuest", &LuaCreature::CanCompleteQuest },
        { "IsReputationGainDisabled", &LuaCreature::IsReputationGainDisabled },
        { "HasSpell", &LuaCreature::HasSpell },
        { "HasQuest", &LuaCreature::HasQuest },
        { "HasSpellCooldown", &LuaCreature::HasSpellCooldown },
        { "CanFly", &LuaCreature::CanFly },

        // Other
        { "FleeToGetAssistance", &LuaCreature::FleeToGetAssistance },
        { "CallForHelp", &LuaCreature::CallForHelp },
        { "CallAssistance", &LuaCreature::CallAssistance },
        { "RemoveCorpse", &LuaCreature::RemoveCorpse },
        { "DespawnOrUnsummon", &LuaCreature::DespawnOrUnsummon },
        { "Respawn", &LuaCreature::Respawn },
        { "AttackStart", &LuaCreature::AttackStart },
        { "SaveToDB", &LuaCreature::SaveToDB },
        { "SelectVictim", &LuaCreature::SelectVictim },
        { "MoveWaypoint", &LuaCreature::MoveWaypoint },
        { "UpdateEntry", &LuaCreature::UpdateEntry },

        // Not implemented methods
        { "GetWaypointPath", nullptr, METHOD_REG_NONE },   // not implemented
        { "GetLootMode", nullptr, METHOD_REG_NONE },   // not implemented
        { "SetRegeneratingHealth", nullptr, METHOD_REG_NONE },   // not implemented
        { "SetLootMode", nullptr, METHOD_REG_NONE },   // not implemented
        { "SetReactState", nullptr, METHOD_REG_NONE },   // not implemented
        { "IsDungeonBoss", nullptr, METHOD_REG_NONE },   // not implemented
        { "IsTrigger", nullptr, METHOD_REG_NONE },   // not implemented
        { "CanStartAttack", nullptr, METHOD_REG_NONE },   // not implemented
        { "IsDamageEnoughForLootingAndReward", nullptr, METHOD_REG_NONE },   // not implemented
        { "HasLootMode", nullptr, METHOD_REG_NONE },   // not implemented
        { "AddLootMode", nullptr, METHOD_REG_NONE },   // not implemented
        { "ResetLootMode", nullptr, METHOD_REG_NONE },   // not implemented
        { "RemoveLootMode", nullptr, METHOD_REG_NONE },   // not implemented
        { "RemoveFromWorld", nullptr, METHOD_REG_NONE }, // not implemented

        { NULL, NULL, METHOD_REG_NONE }
    };
};
#endif
