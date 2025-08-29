/*
* Copyright (C) 2010 - 2025 Eluna Lua Engine <http://emudevs.com/>
* This program is free software licensed under GPL version 3
* Please see the included DOCS/LICENSE.md for more information
*/

#ifndef PETMETHODS_H
#define PETMETHODS_H

/***
 * Non-[Player] controlled companions that fight alongside their owners.
 *
 * Includes hunter pets, warlock demons, death knight ghouls, and other summoned creatures.
 * [Pet]s can be temporary or permanent and have various AI behaviors and spell abilities.
 *
 * Inherits all methods from: [Object], [WorldObject], [Unit], [Guardian]
 */
namespace LuaPet
{
    /**
     * Returns the [Pet]'s type.
     *
     * <pre>
     * enum PetType
     * {
     *      SUMMON_PET                  = 0,
     *      HUNTER_PET                  = 1,
     *      MAX_PET_TYPE                = 4
     * };
     * </pre>
     *
     * @return [PetType] petType
     */
    int GetPetType(lua_State* L, Pet* pet)
    {
        Eluna::Push(L, pet->getPetType());
        return 1;
    }

    /**
     * Sets the [Pet]'s type.
     *
     * <pre>
     * enum PetType
     * {
     *      SUMMON_PET                  = 0,
     *      HUNTER_PET                  = 1,
     *      MAX_PET_TYPE                = 4
     * };
     * </pre>
     *
     * @param [PetType] petType : the pet type to set
     */
    int SetPetType(lua_State* L, Pet* pet)
    {
        uint32 petType = Eluna::CHECKVAL<uint32>(L, 2);
        pet->setPetType(static_cast<PetType>(petType));
        return 0;
    }

    /**
     * Returns `true` if the [Pet] is controlled by a player, returns `false` otherwise.
     *
     * @return bool isControlled
     */
    int IsControlled(lua_State* L, Pet* pet)
    {
        Eluna::Push(L, pet->isControlled());
        return 1;
    }

    /**
     * Returns `true` if the [Pet] is temporarily summoned, returns `false` otherwise.
     *
     * @return bool isTemporary
     */
    int IsTemporarySummoned(lua_State* L, Pet* pet)
    {
        Eluna::Push(L, pet->isTemporarySummoned());
        return 1;
    }

    /**
     * Returns `true` if the [Pet] is a permanent pet for the specified [Player], returns `false` otherwise.
     *
     * @param [Player] owner : the player to check ownership for
     * @return bool isPermanent
     */
    int IsPermanentPetFor(lua_State* L, Pet* pet)
    {
        Player* owner = Eluna::CHECKOBJ<Player>(L, 2);
        Eluna::Push(L, pet->IsPermanentPetFor(owner));
        return 1;
    }

    /**
     * Creates the [Pet]'s base stats and properties from an existing [Creature].
     *
     * @param [Creature] creature : the creature to base the pet on
     * @return bool success : `true` if successful, `false` otherwise
     */
    int CreateBaseAtCreature(lua_State* L, Pet* pet)
    {
        Creature* creature = Eluna::CHECKOBJ<Creature>(L, 2);
        Eluna::Push(L, pet->CreateBaseAtCreature(creature));
        return 1;
    }

    /**
     * Returns the [Pet]'s remaining duration in milliseconds.
     *
     * @return uint32 duration : remaining time in milliseconds, 0 if permanent
     */
    int GetDuration(lua_State* L, Pet* pet)
    {
        Eluna::Push(L, pet->GetDuration().count());
        return 1;
    }

    /**
     * Sets the [Pet]'s duration in milliseconds.
     *
     * @param uint32 duration : duration in milliseconds, 0 for permanent
     */
    int SetDuration(lua_State* L, Pet* pet)
    {
        uint32 duration = Eluna::CHECKVAL<uint32>(L, 2);
        pet->SetDuration(Milliseconds(duration));
        return 0;
    }

    /**
     * Returns the [Pet]'s current happiness state.
     *
     * <pre>
     * enum HappinessState
     * {
     *      UNHAPPY                     = 1,
     *      CONTENT                     = 2,
     *      HAPPY                       = 3
     * };
     * </pre>
     *
     * @return [HappinessState] happinessState
     */
    int GetHappinessState(lua_State* L, Pet* pet)
    {
        Eluna::Push(L, pet->GetHappinessState());
        return 1;
    }

    /**
     * Gives experience points to the [Pet].
     *
     * @param uint32 xp : amount of experience to give
     */
    int GivePetXP(lua_State* L, Pet* pet)
    {
        uint32 xp = Eluna::CHECKVAL<uint32>(L, 2);
        pet->GivePetXP(xp);
        return 0;
    }

    /**
     * Sets the [Pet]'s level directly.
     *
     * @param uint8 level : the level to set
     */
    int GivePetLevel(lua_State* L, Pet* pet)
    {
        uint8 level = Eluna::CHECKVAL<uint8>(L, 2);
        pet->GivePetLevel(level);
        return 0;
    }

    /**
     * Synchronizes the [Pet]'s level with its owner's level.
     *
     * The pet's level will be adjusted based on the owner's level and pet scaling rules.
     */
    int SynchronizeLevelWithOwner(lua_State* /*L*/, Pet* pet)
    {
        pet->SynchronizeLevelWithOwner();
        return 0;
    }

    /**
     * Returns `true` if the [Pet] can eat the specified [Item], returns `false` otherwise.
     *
     * @param [Item] item : the item to check
     * @return bool canEat
     */
    int HaveInDiet(lua_State* L, Pet* pet)
    {
        Item* item = Eluna::CHECKOBJ<Item>(L, 2);
        Eluna::Push(L, pet->HaveInDiet(item->GetTemplate()));
        return 1;
    }

    /**
     * Returns the food benefit level for an item of the specified level.
     *
     * @param uint32 itemLevel : the level of the food item
     * @return uint32 benefitLevel
     */
    int GetCurrentFoodBenefitLevel(lua_State* L, Pet* pet)
    {
        uint32 itemLevel = Eluna::CHECKVAL<uint32>(L, 2);
        Eluna::Push(L, pet->GetCurrentFoodBenefitLevel(itemLevel));
        return 1;
    }

    /**
     * Toggles autocast on or off for the specified spell.
     *
     * @param uint32 spellId : the spell ID to toggle autocast for
     * @param bool apply : `true` to enable autocast, `false` to disable
     */
    int ToggleAutocast(lua_State* L, Pet* pet)
    {
        uint32 spellId = Eluna::CHECKVAL<uint32>(L, 2);
        bool apply = Eluna::CHECKVAL<bool>(L, 3);
        
        SpellInfo const* spellInfo = sSpellMgr->GetSpellInfo(spellId);
        if (spellInfo)
            pet->ToggleAutocast(spellInfo, apply);
        
        return 0;
    }

    /**
     * Makes the [Pet] learn all passive spells it should know.
     *
     * This includes racial passives and pet-specific passive abilities.
     */
    int LearnPetPassives(lua_State* /*L*/, Pet* pet)
    {
        pet->LearnPetPassives();
        return 0;
    }

    /**
     * Queues a spell to be cast when the [Pet] becomes available.
     *
     * @param uint32 spellId : the spell ID to cast
     * @param [Unit] target : the target for the spell
     * @param bool isPositive = false : whether the spell is beneficial
     */
    int CastWhenWillAvailable(lua_State* L, Pet* pet)
    {
        uint32 spellId = Eluna::CHECKVAL<uint32>(L, 2);
        Unit* target = Eluna::CHECKOBJ<Unit>(L, 3);
        ObjectGuid oldTarget = ObjectGuid::Empty;
        bool isPositive = Eluna::CHECKVAL<bool>(L, 4, false);
        
        pet->CastWhenWillAvailable(spellId, target, oldTarget, isPositive);
        return 0;
    }

    /**
     * Clears any queued spell that was set to cast when available.
     */
    int ClearCastWhenWillAvailable(lua_State* /*L*/, Pet* pet)
    {
        pet->ClearCastWhenWillAvailable();
        return 0;
    }

    /**
     * Adds a spell to the [Pet]'s spellbook.
     *
     * <pre>
     * enum ActiveStates : uint8
     * {
     *     ACT_PASSIVE  = 0x01,                                    // 0x01 - passive
     *     ACT_DISABLED = 0x81,                                    // 0x80 - castable
     *     ACT_ENABLED  = 0xC1,                                    // 0x40 | 0x80 - auto cast + castable
     *     ACT_COMMAND  = 0x07,                                    // 0x01 | 0x02 | 0x04
     *     ACT_REACTION = 0x06,                                    // 0x02 | 0x04
     *     ACT_DECIDE   = 0x00                                     // custom
     * };
     * </pre>
     *
     * <pre>
     * enum PetSpellState
     * {
     *     PETSPELL_UNCHANGED          = 0,
     *     PETSPELL_CHANGED            = 1,
     *     PETSPELL_NEW                = 2,
     *     PETSPELL_REMOVED            = 3
     * };
     * </pre>
     *
     * <pre>
     * enum PetSpellType
     * {
     *     PETSPELL_NORMAL             = 0,
     *     PETSPELL_FAMILY             = 1,
     *     PETSPELL_TALENT             = 2
     * };
     * </pre>
     *
     * @param uint32 spellId : the spell ID to add
     * @param [ActiveStates] active : the spell's active state by default is ACT_DECIDE
     * @param [PetSpellState] state : the spell's state by default is PETSPELL_NEW
     * @param [PetSpellType] type : the spell's type by default is PETSPELL_NORMAL
     * @return bool success : `true` if the spell was added successfully
     */
    int AddSpell(lua_State* L, Pet* pet)
    {
        uint32 spellId = Eluna::CHECKVAL<uint32>(L, 2);
        uint32 active = Eluna::CHECKVAL<uint32>(L, 3, ACT_DECIDE);
        uint32 state = Eluna::CHECKVAL<uint32>(L, 4, PETSPELL_NEW);
        uint32 type = Eluna::CHECKVAL<uint32>(L, 5, PETSPELL_NORMAL);
        
        Eluna::Push(L, pet->addSpell(spellId, static_cast<ActiveStates>(active), static_cast<PetSpellState>(state), static_cast<PetSpellType>(type)));
        return 1;
    }

    /**
     * Makes the [Pet] learn a spell.
     *
     * @param uint32 spellId : the spell ID to learn
     * @return bool success : `true` if the spell was learned successfully
     */
    int LearnSpell(lua_State* L, Pet* pet)
    {
        uint32 spellId = Eluna::CHECKVAL<uint32>(L, 2);
        Eluna::Push(L, pet->learnSpell(spellId));
        return 1;
    }

    /**
     * Makes the [Pet] learn the highest available rank of a spell.
     *
     * @param uint32 spellId : the base spell ID
     */
    int LearnSpellHighRank(lua_State* L, Pet* pet)
    {
        uint32 spellId = Eluna::CHECKVAL<uint32>(L, 2);
        pet->learnSpellHighRank(spellId);
        return 0;
    }

    /**
     * Initializes level-up spells for the [Pet]'s current level.
     *
     * This teaches the pet all spells it should know at its current level.
     */
    int InitLevelupSpellsForLevel(lua_State* /*L*/, Pet* pet)
    {
        pet->InitLevelupSpellsForLevel();
        return 0;
    }

    /**
     * Makes the [Pet] unlearn a spell.
     *
     * @param uint32 spellId : the spell ID to unlearn
     * @param bool learnPrev : if `true`, learns the previous rank by default is false
     * @param bool clearAb : if `true`, clears the spell from action bar by default is true
     * @return bool success : `true` if the spell was unlearned successfully
     */
    int UnlearnSpell(lua_State* L, Pet* pet)
    {
        uint32 spellId = Eluna::CHECKVAL<uint32>(L, 2);
        bool learnPrev = Eluna::CHECKVAL<bool>(L, 3, false);
        bool clearAb = Eluna::CHECKVAL<bool>(L, 4, true);
        
        Eluna::Push(L, pet->unlearnSpell(spellId, learnPrev, clearAb));
        return 1;
    }

    /**
     * Removes a spell from the [Pet]'s spellbook.
     *
     * @param uint32 spellId : the spell ID to remove
     * @param bool learnPrev : if `true`, learns the previous rank by default is false
     * @param bool clearAb : if `true`, clears the spell from action bar by default is true
     * @return bool success : `true` if the spell was removed successfully
     */
    int RemoveSpell(lua_State* L, Pet* pet)
    {
        uint32 spellId = Eluna::CHECKVAL<uint32>(L, 2);
        bool learnPrev = Eluna::CHECKVAL<bool>(L, 3, false);
        bool clearAb = Eluna::CHECKVAL<bool>(L, 4, true);
        
        Eluna::Push(L, pet->removeSpell(spellId, learnPrev, clearAb));
        return 1;
    }

    /**
     * Cleans up the [Pet]'s action bar, removing invalid spells.
     */
    int CleanupActionBar(lua_State* /*L*/, Pet* pet)
    {
        pet->CleanupActionBar();
        return 0;
    }

    /**
     * Generates action bar data for the [Pet].
     *
     * @return string actionBarData : the action bar data as a string
     */
    int GenerateActionBarData(lua_State* L, Pet* pet)
    {
        Eluna::Push(L, pet->GenerateActionBarData());
        return 1;
    }

    /**
     * Initializes the [Pet]'s creation spells.
     *
     * This sets up the basic spells the pet should have when first created.
     */
    int InitPetCreateSpells(lua_State* /*L*/, Pet* pet)
    {
        pet->InitPetCreateSpells();
        return 0;
    }

    /**
     * Resets all of the [Pet]'s talents.
     *
     * @return bool success : `true` if talents were reset successfully
     */
    int ResetTalents(lua_State* L, Pet* pet)
    {
        Eluna::Push(L, pet->resetTalents());
        return 1;
    }

    /**
     * Initializes talents for the [Pet]'s current level.
     *
     * This assigns talent points based on the pet's level.
     */
    int InitTalentForLevel(lua_State* /*L*/, Pet* pet)
    {
        pet->InitTalentForLevel();
        return 0;
    }

    /**
     * Returns the maximum number of talent points available at the specified level.
     *
     * @param uint8 level : the level to check
     * @return uint8 maxTalentPoints
     */
    int GetMaxTalentPointsForLevel(lua_State* L, Pet* pet)
    {
        uint8 level = Eluna::CHECKVAL<uint8>(L, 2);
        Eluna::Push(L, pet->GetMaxTalentPointsForLevel(level));
        return 1;
    }

    /**
     * Returns the number of unspent talent points the [Pet] has.
     *
     * @return uint8 freeTalentPoints
     */
    int GetFreeTalentPoints(lua_State* L, Pet* pet)
    {
        Eluna::Push(L, pet->GetFreeTalentPoints());
        return 1;
    }

    /**
     * Sets the number of unspent talent points for the [Pet].
     *
     * @param uint8 points : the number of free talent points to set
     */
    int SetFreeTalentPoints(lua_State* L, Pet* pet)
    {
        uint8 points = Eluna::CHECKVAL<uint8>(L, 2);
        pet->SetFreeTalentPoints(points);
        return 0;
    }

    /**
     * Returns the number of talents the [Pet] has used.
     *
     * @return uint32 usedTalentCount
     */
    int GetUsedTalentCount(lua_State* L, Pet* pet)
    {
        Eluna::Push(L, pet->m_usedTalentCount);
        return 1;
    }

    /**
     * Sets the number of talents the [Pet] has used.
     *
     * @param uint32 count : the number of used talents to set
     */
    int SetUsedTalentCount(lua_State* L, Pet* pet)
    {
        uint32 count = Eluna::CHECKVAL<uint32>(L, 2);
        pet->m_usedTalentCount = count;
        return 0;
    }

    /**
     * Returns the aura update mask for raid members.
     *
     * @return uint64 auraUpdateMask
     */
    int GetAuraUpdateMaskForRaid(lua_State* L, Pet* pet)
    {
        Eluna::Push(L, pet->GetAuraUpdateMaskForRaid());
        return 1;
    }

    /**
     * Sets an aura slot in the raid update mask.
     *
     * @param uint8 slot : the aura slot to set
     */
    int SetAuraUpdateMaskForRaid(lua_State* L, Pet* pet)
    {
        uint8 slot = Eluna::CHECKVAL<uint8>(L, 2);
        pet->SetAuraUpdateMaskForRaid(slot);
        return 0;
    }

    /**
     * Resets the aura update mask for raid members.
     */
    int ResetAuraUpdateMaskForRaid(lua_State* /*L*/, Pet* pet)
    {
        pet->ResetAuraUpdateMaskForRaid();
        return 0;
    }

    /**
     * Returns the [Player] who owns this [Pet].
     *
     * @return [Player] owner : the pet's owner
     */
    int GetOwner(lua_State* L, Pet* pet)
    {
        Eluna::Push(L, pet->GetOwner());
        return 1;
    }

    /**
     * Returns `true` if the [Pet] has a temporary spell queued, returns `false` otherwise.
     *
     * @return bool hasTempSpell
     */
    int HasTempSpell(lua_State* L, Pet* pet)
    {
        Eluna::Push(L, pet->HasTempSpell());
        return 1;
    }

    /**
     * Returns `true` if the [Pet] is marked as removed, returns `false` otherwise.
     *
     * @return bool isRemoved
     */
    int IsRemoved(lua_State* L, Pet* pet)
    {
        Eluna::Push(L, pet->m_removed);
        return 1;
    }

    /**
     * Sets whether the [Pet] is marked as removed.
     *
     * @param bool removed : `true` to mark as removed, `false` otherwise
     */
    int SetRemoved(lua_State* L, Pet* pet)
    {
        bool removed = Eluna::CHECKVAL<bool>(L, 2);
        pet->m_removed = removed;
        return 0;
    }

    /**
     * Returns the number of auto-spells the [Pet] has.
     *
     * @return uint8 autoSpellCount
     */
    int GetPetAutoSpellSize(lua_State* L, Pet* pet)
    {
        Eluna::Push(L, pet->GetPetAutoSpellSize());
        return 1;
    }

    /**
     * Returns the auto-spell at the specified position.
     *
     * @param uint8 pos : the position in the auto-spell list
     * @return uint32 spellId : the spell ID, or 0 if invalid position
     */
    int GetPetAutoSpellOnPos(lua_State* L, Pet* pet)
    {
        uint8 pos = Eluna::CHECKVAL<uint8>(L, 2);
        Eluna::Push(L, pet->GetPetAutoSpellOnPos(pos));
        return 1;
    }

    /**
     * Saves the [Pet] to the database.
     *
     * <pre>
     * enum PetSaveMode
     * {
     *     PET_SAVE_AS_DELETED         = -1,                        // not saved in fact
     *     PET_SAVE_AS_CURRENT         =  0,                        // in current slot (with player)
     *     PET_SAVE_FIRST_STABLE_SLOT  =  1,
     *     PET_SAVE_LAST_STABLE_SLOT   =  MAX_PET_STABLES,          // last in DB stable slot index (including), all higher have same meaning as PET_SAVE_NOT_IN_SLOT
     *     PET_SAVE_NOT_IN_SLOT        =  100                       // for avoid conflict with stable size grow will use 100
     * };
     * </pre>
     *
     * @param [PetSaveMode] mode : the save mode to use
     */
    int SavePetToDB(lua_State* L, Pet* pet)
    {
        uint32 mode = Eluna::CHECKVAL<uint32>(L, 2);
        pet->SavePetToDB(static_cast<PetSaveMode>(mode));
        return 0;
    }

    /**
     * Removes the [Pet] from the world.
     *
     * <pre>
     * enum PetSaveMode
     * {
     *     PET_SAVE_AS_DELETED         = -1,                        // not saved in fact
     *     PET_SAVE_AS_CURRENT         =  0,                        // in current slot (with player)
     *     PET_SAVE_FIRST_STABLE_SLOT  =  1,
     *     PET_SAVE_LAST_STABLE_SLOT   =  MAX_PET_STABLES,          // last in DB stable slot index (including), all higher have same meaning as PET_SAVE_NOT_IN_SLOT
     *     PET_SAVE_NOT_IN_SLOT        =  100                       // for avoid conflict with stable size grow will use 100
     * };
     * </pre>
     *
     * @param [PetSaveMode] mode : how to handle the removal
     * @param bool returnReagent = false : if `true`, returns reagents used to summon
     */
    int Remove(lua_State* L, Pet* pet)
    {
        uint32 mode = Eluna::CHECKVAL<uint32>(L, 2);
        bool returnReagent = Eluna::CHECKVAL<bool>(L, 3, false);
        pet->Remove(static_cast<PetSaveMode>(mode), returnReagent);
        return 0;
    }

    /**
     * Returns `true` if the [Pet] is currently being loaded from the database, returns `false` otherwise.
     *
     * @return bool isBeingLoaded
     */
    int IsBeingLoaded(lua_State* L, Pet* pet)
    {
        Eluna::Push(L, pet->isBeingLoaded());
        return 1;
    }
};
#endif // PETMETHODS_H

