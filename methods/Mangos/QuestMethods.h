/*
* Copyright (C) 2010 - 2024 Eluna Lua Engine <https://elunaluaengine.github.io/>
* This program is free software licensed under GPL version 3
* Please see the included DOCS/LICENSE.md for more information
*/

#ifndef QUESTMETHODS_H
#define QUESTMETHODS_H

/***
 * Inherits all methods from: none
 */
namespace LuaQuest
{
    /**
     * Returns 'true' if the [Quest] has the specified flag, false otherwise.
     * Below flags are based off of 3.3.5a. Subject to change.
     *
     * <pre>
     * enum QuestFlags
     * {
     *     // Flags used at server and sent to client
     *     QUEST_FLAGS_NONE                    = 0x0,
     *     QUEST_FLAGS_STAY_ALIVE              = 0x1,       // Not used currently
     *     QUEST_FLAGS_PARTY_ACCEPT            = 0x2,       // Not used currently. If player in party, all players that can accept this quest will receive confirmation box to accept quest CMSG_QUEST_CONFIRM_ACCEPT/SMSG_QUEST_CONFIRM_ACCEPT
     *     QUEST_FLAGS_EXPLORATION             = 0x4,       // Not used currently
     *     QUEST_FLAGS_SHARABLE                = 0x8,       // Can be shared: Player::CanShareQuest()
     *     QUEST_FLAGS_HAS_CONDITION           = 0x10,      // Not used currently
     *     QUEST_FLAGS_HIDE_REWARD_POI         = 0x20,      // Not used currently: Unsure of content
     *     QUEST_FLAGS_RAID                    = 0x40,      // Not used currently
     *     QUEST_FLAGS_TBC                     = 0x80,      // Not used currently: Available if TBC expansion enabled only
     *     QUEST_FLAGS_NO_MONEY_FROM_XP        = 0x100,     // Not used currently: Experience is not converted to gold at max level
     *     QUEST_FLAGS_HIDDEN_REWARDS          = 0x200,     // Items and money rewarded only sent in SMSG_QUESTGIVER_OFFER_REWARD (not in SMSG_QUESTGIVER_QUEST_DETAILS or in client quest log(SMSG_QUEST_QUERY_RESPONSE))
     *     QUEST_FLAGS_TRACKING                = 0x400,     // These quests are automatically rewarded on quest complete and they will never appear in quest log client side.
     *     QUEST_FLAGS_DEPRECATE_REPUTATION    = 0x800,     // Not used currently
     *     QUEST_FLAGS_DAILY                   = 0x1000,    // Used to know quest is Daily one
     *     QUEST_FLAGS_FLAGS_PVP               = 0x2000,    // Having this quest in log forces PvP flag
     *     QUEST_FLAGS_UNAVAILABLE             = 0x4000,    // Used on quests that are not generically available
     *     QUEST_FLAGS_WEEKLY                  = 0x8000,
     *     QUEST_FLAGS_AUTOCOMPLETE            = 0x10000,   // auto complete
     *     QUEST_FLAGS_DISPLAY_ITEM_IN_TRACKER = 0x20000,   // Displays usable item in quest tracker
     *     QUEST_FLAGS_OBJ_TEXT                = 0x40000,   // use Objective text as Complete text
     *     QUEST_FLAGS_AUTO_ACCEPT             = 0x80000,   // The client recognizes this flag as auto-accept. However, NONE of the current quests (3.3.5a) have this flag. Maybe blizz used to use it, or will use it in the future.
     *
     *     // ... 4.x added flags up to 0x80000000 - all unknown for now
     * };
     * </pre>
     *
     * @param [QuestFlags] flag : all available flags can be seen above
     * @return bool hasFlag
     */
    int HasFlag(Eluna* E, Quest* quest)
    {
        uint32 flag = E->CHECKVAL<uint32>(2);

        E->Push(quest->HasQuestFlag((QuestFlags)flag));
        return 1;
    }

#ifndef CLASSIC
    /**
     * Returns 'true' if the [Quest] is a daily quest, false otherwise.
     *
     * @return bool isDaily
     */
    int IsDaily(Eluna* E, Quest* quest)
    {
        E->Push(quest->IsDaily());
        return 1;
    }
#endif

    /**
     * Returns 'true' if the [Quest] is repeatable, false otherwise.
     *
     * @return bool isRepeatable
     */
    int IsRepeatable(Eluna* E, Quest* quest)
    {
        E->Push(quest->IsRepeatable());
        return 1;
    }

    /**
     * Returns entry ID of the [Quest].
     *
     * @return uint32 entryId
     */
    int GetId(Eluna* E, Quest* quest)
    {
        E->Push(quest->GetQuestId());
        return 1;
    }

    /**
     * Returns the [Quest]'s level.
     *
     * @return uint32 level
     */
    int GetLevel(Eluna* E, Quest* quest)
    {
        E->Push(quest->GetQuestLevel());
        return 1;
    }

    /**
     * Returns the minimum level required to pick up the [Quest].
     *
     * @return uint32 minLevel
     */
    int GetMinLevel(Eluna* E, Quest* quest)
    {
        E->Push(quest->GetMinLevel());
        return 1;
    }

    /**
     * Returns the next [Quest] entry ID.
     *
     * @return int32 entryId
     */
    int GetNextQuestId(Eluna* E, Quest* quest)
    {
        E->Push(quest->GetNextQuestId());
        return 1;
    }

    /**
     * Returns the previous [Quest] entry ID.
     *
     * @return int32 entryId
     */
    int GetPrevQuestId(Eluna* E, Quest* quest)
    {
        E->Push(quest->GetPrevQuestId());
        return 1;
    }

    /**
     * Returns the next [Quest] entry ID in the specific [Quest] chain.
     *
     * @return int32 entryId
     */
    int GetNextQuestInChain(Eluna* E, Quest* quest)
    {
        E->Push(quest->GetNextQuestInChain());
        return 1;
    }

    /**
     * Returns the [Quest]'s flags.
     *
     * @return [QuestFlags] flags
     */
    int GetFlags(Eluna* E, Quest* quest)
    {
        E->Push(quest->GetQuestFlags());
        return 1;
    }

    /**
     * Returns the [Quest]'s type.
     *
     * TODO: Document types available.
     *
     * @return uint32 type
     */
    int GetType(Eluna* E, Quest* quest)
    {
        E->Push(quest->GetType());
        return 1;
    }
    
    ElunaRegister<Quest> QuestMethods[] =
    {
        // Getters
        { "GetId", &LuaQuest::GetId },
        { "GetLevel", &LuaQuest::GetLevel },
        { "GetMinLevel", &LuaQuest::GetMinLevel },
        { "GetNextQuestId", &LuaQuest::GetNextQuestId },
        { "GetPrevQuestId", &LuaQuest::GetPrevQuestId },
        { "GetNextQuestInChain", &LuaQuest::GetNextQuestInChain },
        { "GetFlags", &LuaQuest::GetFlags },
        { "GetType", &LuaQuest::GetType },

        // Boolean
        { "HasFlag", &LuaQuest::HasFlag },
        { "IsRepeatable", &LuaQuest::IsRepeatable },
#ifndef CLASSIC
        { "IsDaily", &LuaQuest::IsDaily },
#else
        { "IsDaily", nullptr, METHOD_REG_NONE },
#endif

        // Not implemented methods
        { "GetMaxLevel", nullptr, METHOD_REG_NONE },  // not implemented

        { NULL, NULL, METHOD_REG_NONE }
    };
};
#endif
