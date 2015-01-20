/*
 * Copyright (C) 2010 - 2015 Eluna Lua Engine <http://emudevs.com/>
 * This program is free software licensed under GPL version 3
 * Please see the included DOCS/LICENSE.md for more information
 */

#ifndef _PLAYER_HOOKS_H
#define _PLAYER_HOOKS_H

#include "Hooks.h"
#include "HookHelpers.h"
#include "LuaEngine.h"
#include "ElunaBinding.h"
#include "ElunaIncludes.h"
#include "ElunaTemplate.h"

using namespace Hooks;

void Eluna::OnLearnTalents(Player* pPlayer, uint32 talentId, uint32 talentRank, uint32 spellid)
{
    if (!PlayerEventBindings->HasEvents(PLAYER_EVENT_ON_LEARN_TALENTS))
        return;

    LOCK_ELUNA;
    Push(pPlayer);
    Push(talentId);
    Push(talentRank);
    Push(spellid);
    CallAllFunctions(PlayerEventBindings, PLAYER_EVENT_ON_LEARN_TALENTS);
}

void Eluna::HandleGossipSelectOption(Player* pPlayer, Item* item, uint32 sender, uint32 action, const std::string& code)
{
    if (!ItemGossipBindings->HasEvents(GOSSIP_EVENT_ON_SELECT, item->GetEntry()))
        return;

    LOCK_ELUNA;
    pPlayer->PlayerTalkClass->ClearMenus();

    Push(pPlayer);
    Push(item);
    Push(sender);
    Push(action);
    if (code.empty())
        Push();
    else
        Push(code);

    CallAllFunctions(ItemGossipBindings, GOSSIP_EVENT_ON_SELECT, item->GetEntry());
}

void Eluna::HandleGossipSelectOption(Player* pPlayer, uint32 menuId, uint32 sender, uint32 action, const std::string& code)
{
    if (!playerGossipBindings->HasEvents(GOSSIP_EVENT_ON_SELECT, menuId))
        return;

    LOCK_ELUNA;
    pPlayer->PlayerTalkClass->ClearMenus();

    Push(pPlayer); // receiver
    Push(pPlayer); // sender, just not to mess up the amount of args.
    Push(sender);
    Push(action);
    if (code.empty())
        Push();
    else
        Push(code);

    CallAllFunctions(playerGossipBindings, GOSSIP_EVENT_ON_SELECT, menuId);
}

// Player
bool Eluna::OnCommand(Player* player, const char* text)
{
    // If from console, player is NULL
    std::string fullcmd(text);
    if (!player || player->GetSession()->GetSecurity() >= SEC_ADMINISTRATOR)
    {
        char* creload = strtok((char*)text, " ");
        char* celuna = strtok(NULL, "");
        if (creload && celuna)
        {
            std::string reload(creload);
            std::string eluna(celuna);
            std::transform(reload.begin(), reload.end(), reload.begin(), ::tolower);
            if (reload == "reload")
            {
                std::transform(eluna.begin(), eluna.end(), eluna.begin(), ::tolower);
                if (std::string("eluna").find(eluna) == 0)
                {
                    ReloadEluna();
                    return false;
                }
            }
        }
    }

    if (!PlayerEventBindings->HasEvents(PLAYER_EVENT_ON_COMMAND))
        return true;

    LOCK_ELUNA;
    Push(player);
    Push(fullcmd);
    return CallAllFunctionsBool(PlayerEventBindings, PLAYER_EVENT_ON_COMMAND, true);
}

void Eluna::OnLootItem(Player* pPlayer, Item* pItem, uint32 count, uint64 guid)
{
    if (!PlayerEventBindings->HasEvents(PLAYER_EVENT_ON_LOOT_ITEM))
        return;

    LOCK_ELUNA;
    Push(pPlayer);
    Push(pItem);
    Push(count);
    Push(guid);
    CallAllFunctions(PlayerEventBindings, PLAYER_EVENT_ON_LOOT_ITEM);
}

void Eluna::OnLootMoney(Player* pPlayer, uint32 amount)
{
    if (!PlayerEventBindings->HasEvents(PLAYER_EVENT_ON_LOOT_MONEY))
        return;

    LOCK_ELUNA;
    Push(pPlayer);
    Push(amount);
    CallAllFunctions(PlayerEventBindings, PLAYER_EVENT_ON_LOOT_MONEY);
}

void Eluna::OnFirstLogin(Player* pPlayer)
{
    if (!PlayerEventBindings->HasEvents(PLAYER_EVENT_ON_FIRST_LOGIN))
        return;

    LOCK_ELUNA;
    Push(pPlayer);
    CallAllFunctions(PlayerEventBindings, PLAYER_EVENT_ON_FIRST_LOGIN);
}

void Eluna::OnRepop(Player* pPlayer)
{
    if (!PlayerEventBindings->HasEvents(PLAYER_EVENT_ON_REPOP))
        return;

    LOCK_ELUNA;
    Push(pPlayer);
    CallAllFunctions(PlayerEventBindings, PLAYER_EVENT_ON_REPOP);
}

void Eluna::OnResurrect(Player* pPlayer)
{
    if (!PlayerEventBindings->HasEvents(PLAYER_EVENT_ON_RESURRECT))
        return;

    LOCK_ELUNA;
    Push(pPlayer);
    CallAllFunctions(PlayerEventBindings, PLAYER_EVENT_ON_RESURRECT);
}

void Eluna::OnQuestAbandon(Player* pPlayer, uint32 questId)
{
    if (!PlayerEventBindings->HasEvents(PLAYER_EVENT_ON_QUEST_ABANDON))
        return;

    LOCK_ELUNA;
    Push(pPlayer);
    Push(questId);
    CallAllFunctions(PlayerEventBindings, PLAYER_EVENT_ON_QUEST_ABANDON);
}

void Eluna::OnEquip(Player* pPlayer, Item* pItem, uint8 bag, uint8 slot)
{
    if (!PlayerEventBindings->HasEvents(PLAYER_EVENT_ON_EQUIP))
        return;

    LOCK_ELUNA;
    Push(pPlayer);
    Push(pItem);
    Push(bag);
    Push(slot);
    CallAllFunctions(PlayerEventBindings, PLAYER_EVENT_ON_EQUIP);
}

InventoryResult Eluna::OnCanUseItem(const Player* pPlayer, uint32 itemEntry)
{
    if (!PlayerEventBindings->HasEvents(PLAYER_EVENT_ON_CAN_USE_ITEM))
        return EQUIP_ERR_OK;

    LOCK_ELUNA;
    InventoryResult result = EQUIP_ERR_OK;
    Push(pPlayer);
    Push(itemEntry);
    int n = SetupStack(PlayerEventBindings, PLAYER_EVENT_ON_CAN_USE_ITEM, 2);

    while (n > 0)
    {
        int r = CallOneFunction(n--, 2, 1);

        if (lua_isnumber(L, r))
            result = (InventoryResult)CHECKVAL<uint32>(L, r);

        lua_pop(L, 1);
    }

    CleanUpStack(2);
    return result;
}
void Eluna::OnPlayerEnterCombat(Player* pPlayer, Unit* pEnemy)
{
    if (!PlayerEventBindings->HasEvents(PLAYER_EVENT_ON_ENTER_COMBAT))
        return;

    LOCK_ELUNA;
    Push(pPlayer);
    Push(pEnemy);
    CallAllFunctions(PlayerEventBindings, PLAYER_EVENT_ON_ENTER_COMBAT);
}

void Eluna::OnPlayerLeaveCombat(Player* pPlayer)
{
    if (!PlayerEventBindings->HasEvents(PLAYER_EVENT_ON_LEAVE_COMBAT))
        return;

    LOCK_ELUNA;
    Push(pPlayer);
    CallAllFunctions(PlayerEventBindings, PLAYER_EVENT_ON_LEAVE_COMBAT);
}

void Eluna::OnPVPKill(Player* pKiller, Player* pKilled)
{
    if (!PlayerEventBindings->HasEvents(PLAYER_EVENT_ON_KILL_PLAYER))
        return;

    LOCK_ELUNA;
    Push(pKiller);
    Push(pKilled);
    CallAllFunctions(PlayerEventBindings, PLAYER_EVENT_ON_KILL_PLAYER);
}

void Eluna::OnCreatureKill(Player* pKiller, Creature* pKilled)
{
    if (!PlayerEventBindings->HasEvents(PLAYER_EVENT_ON_KILL_CREATURE))
        return;

    LOCK_ELUNA;
    Push(pKiller);
    Push(pKilled);
    CallAllFunctions(PlayerEventBindings, PLAYER_EVENT_ON_KILL_CREATURE);
}

void Eluna::OnPlayerKilledByCreature(Creature* pKiller, Player* pKilled)
{
    if (!PlayerEventBindings->HasEvents(PLAYER_EVENT_ON_KILLED_BY_CREATURE))
        return;

    LOCK_ELUNA;
    Push(pKiller);
    Push(pKilled);
    CallAllFunctions(PlayerEventBindings, PLAYER_EVENT_ON_KILLED_BY_CREATURE);
}

void Eluna::OnLevelChanged(Player* pPlayer, uint8 oldLevel)
{
    if (!PlayerEventBindings->HasEvents(PLAYER_EVENT_ON_LEVEL_CHANGE))
        return;

    LOCK_ELUNA;
    Push(pPlayer);
    Push(oldLevel);
    CallAllFunctions(PlayerEventBindings, PLAYER_EVENT_ON_LEVEL_CHANGE);
}

void Eluna::OnFreeTalentPointsChanged(Player* pPlayer, uint32 newPoints)
{
    if (!PlayerEventBindings->HasEvents(PLAYER_EVENT_ON_TALENTS_CHANGE))
        return;

    LOCK_ELUNA;
    Push(pPlayer);
    Push(newPoints);
    CallAllFunctions(PlayerEventBindings, PLAYER_EVENT_ON_TALENTS_CHANGE);
}

void Eluna::OnTalentsReset(Player* pPlayer, bool noCost)
{
    if (!PlayerEventBindings->HasEvents(PLAYER_EVENT_ON_TALENTS_RESET))
        return;

    LOCK_ELUNA;
    Push(pPlayer);
    Push(noCost);
    CallAllFunctions(PlayerEventBindings, PLAYER_EVENT_ON_TALENTS_RESET);
}

void Eluna::OnMoneyChanged(Player* pPlayer, int32& amount)
{
    if (!PlayerEventBindings->HasEvents(PLAYER_EVENT_ON_MONEY_CHANGE))
        return;

    LOCK_ELUNA;
    Push(pPlayer);
    Push(amount);
    int amountIndex = lua_gettop(L);
    int n = SetupStack(PlayerEventBindings, PLAYER_EVENT_ON_MONEY_CHANGE, 2);

    while (n > 0)
    {
        int r = CallOneFunction(n--, 2, 1);

        if (lua_isnumber(L, r))
        {
            amount = CHECKVAL<int32>(L, r);
            // Update the stack for subsequent calls.
            ReplaceArgument(amount, amountIndex);
        }

        lua_pop(L, 1);
    }

    CleanUpStack(2);
}

void Eluna::OnGiveXP(Player* pPlayer, uint32& amount, Unit* pVictim)
{
    if (!PlayerEventBindings->HasEvents(PLAYER_EVENT_ON_GIVE_XP))
        return;

    LOCK_ELUNA;
    Push(pPlayer);
    Push(amount);
    Push(pVictim);
    int amountIndex = lua_gettop(L) - 1;
    int n = SetupStack(PlayerEventBindings, PLAYER_EVENT_ON_GIVE_XP, 3);

    while (n > 0)
    {
        int r = CallOneFunction(n--, 3, 1);

        if (lua_isnumber(L, r))
        {
            amount = CHECKVAL<uint32>(L, r);
            // Update the stack for subsequent calls.
            ReplaceArgument(amount, amountIndex);
        }

        lua_pop(L, 1);
    }

    CleanUpStack(3);
}

void Eluna::OnReputationChange(Player* pPlayer, uint32 factionID, int32& standing, bool incremental)
{
    if (!PlayerEventBindings->HasEvents(PLAYER_EVENT_ON_REPUTATION_CHANGE))
        return;

    LOCK_ELUNA;
    Push(pPlayer);
    Push(factionID);
    Push(standing);
    Push(incremental);
    int standingIndex = lua_gettop(L) - 1;
    int n = SetupStack(PlayerEventBindings, PLAYER_EVENT_ON_REPUTATION_CHANGE, 4);

    while (n > 0)
    {
        int r = CallOneFunction(n--, 4, 1);

        if (lua_isnumber(L, r))
        {
            standing = CHECKVAL<int32>(L, r);
            // Update the stack for subsequent calls.
            ReplaceArgument(standing, standingIndex);
        }

        lua_pop(L, 1);
    }

    CleanUpStack(4);
}

void Eluna::OnDuelRequest(Player* pTarget, Player* pChallenger)
{
    if (!PlayerEventBindings->HasEvents(PLAYER_EVENT_ON_DUEL_REQUEST))
        return;

    LOCK_ELUNA;
    Push(pTarget);
    Push(pChallenger);
    CallAllFunctions(PlayerEventBindings, PLAYER_EVENT_ON_DUEL_REQUEST);
}

void Eluna::OnDuelStart(Player* pStarter, Player* pChallenger)
{
    if (!PlayerEventBindings->HasEvents(PLAYER_EVENT_ON_DUEL_START))
        return;

    LOCK_ELUNA;
    Push(pStarter);
    Push(pChallenger);
    CallAllFunctions(PlayerEventBindings, PLAYER_EVENT_ON_DUEL_START);
}

void Eluna::OnDuelEnd(Player* pWinner, Player* pLoser, DuelCompleteType type)
{
    if (!PlayerEventBindings->HasEvents(PLAYER_EVENT_ON_DUEL_END))
        return;

    LOCK_ELUNA;
    Push(pWinner);
    Push(pLoser);
    Push(type);
    CallAllFunctions(PlayerEventBindings, PLAYER_EVENT_ON_DUEL_END);
}

void Eluna::OnEmote(Player* pPlayer, uint32 emote)
{
    if (!PlayerEventBindings->HasEvents(PLAYER_EVENT_ON_EMOTE))
        return;

    LOCK_ELUNA;
    Push(pPlayer);
    Push(emote);
    CallAllFunctions(PlayerEventBindings, PLAYER_EVENT_ON_EMOTE);
}

void Eluna::OnTextEmote(Player* pPlayer, uint32 textEmote, uint32 emoteNum, uint64 guid)
{
    if (!PlayerEventBindings->HasEvents(PLAYER_EVENT_ON_TEXT_EMOTE))
        return;

    LOCK_ELUNA;
    Push(pPlayer);
    Push(textEmote);
    Push(emoteNum);
    Push(guid);
    CallAllFunctions(PlayerEventBindings, PLAYER_EVENT_ON_TEXT_EMOTE);
}

void Eluna::OnSpellCast(Player* pPlayer, Spell* pSpell, bool skipCheck)
{
    if (!PlayerEventBindings->HasEvents(PLAYER_EVENT_ON_SPELL_CAST))
        return;

    LOCK_ELUNA;
    Push(pPlayer);
    Push(pSpell);
    Push(skipCheck);
    CallAllFunctions(PlayerEventBindings, PLAYER_EVENT_ON_SPELL_CAST);
}

void Eluna::OnLogin(Player* pPlayer)
{
    if (!PlayerEventBindings->HasEvents(PLAYER_EVENT_ON_LOGIN))
        return;

    LOCK_ELUNA;
    Push(pPlayer);
    CallAllFunctions(PlayerEventBindings, PLAYER_EVENT_ON_LOGIN);
}

void Eluna::OnLogout(Player* pPlayer)
{
    if (!PlayerEventBindings->HasEvents(PLAYER_EVENT_ON_LOGOUT))
        return;

    LOCK_ELUNA;
    Push(pPlayer);
    CallAllFunctions(PlayerEventBindings, PLAYER_EVENT_ON_LOGOUT);
}

void Eluna::OnCreate(Player* pPlayer)
{
    if (!PlayerEventBindings->HasEvents(PLAYER_EVENT_ON_CHARACTER_CREATE))
        return;

    LOCK_ELUNA;
    Push(pPlayer);
    CallAllFunctions(PlayerEventBindings, PLAYER_EVENT_ON_CHARACTER_CREATE);
}

void Eluna::OnDelete(uint32 guidlow)
{
    if (!PlayerEventBindings->HasEvents(PLAYER_EVENT_ON_CHARACTER_DELETE))
        return;

    LOCK_ELUNA;
    Push(guidlow);
    CallAllFunctions(PlayerEventBindings, PLAYER_EVENT_ON_CHARACTER_DELETE);
}

void Eluna::OnSave(Player* pPlayer)
{
    if (!PlayerEventBindings->HasEvents(PLAYER_EVENT_ON_SAVE))
        return;

    LOCK_ELUNA;
    Push(pPlayer);
    CallAllFunctions(PlayerEventBindings, PLAYER_EVENT_ON_SAVE);
}

void Eluna::OnBindToInstance(Player* pPlayer, Difficulty difficulty, uint32 mapid, bool permanent)
{
    if (!PlayerEventBindings->HasEvents(PLAYER_EVENT_ON_BIND_TO_INSTANCE))
        return;

    LOCK_ELUNA;
    Push(pPlayer);
    Push(difficulty);
    Push(mapid);
    Push(permanent);
    CallAllFunctions(PlayerEventBindings, PLAYER_EVENT_ON_BIND_TO_INSTANCE);
}

void Eluna::OnUpdateZone(Player* pPlayer, uint32 newZone, uint32 newArea)
{
    if (!PlayerEventBindings->HasEvents(PLAYER_EVENT_ON_UPDATE_ZONE))
        return;

    LOCK_ELUNA;
    Push(pPlayer);
    Push(newZone);
    Push(newArea);
    CallAllFunctions(PlayerEventBindings, PLAYER_EVENT_ON_UPDATE_ZONE);
}

void Eluna::OnMapChanged(Player* player)
{
    if (!PlayerEventBindings->HasEvents(PLAYER_EVENT_ON_MAP_CHANGE))
        return;

    LOCK_ELUNA;
    Push(player);
    CallAllFunctions(PlayerEventBindings, PLAYER_EVENT_ON_MAP_CHANGE);
}

// AddOns
bool Eluna::OnAddonMessage(Player* sender, uint32 type, std::string& msg, Player* receiver, Guild* guild, Group* group, Channel* channel)
{
    if (!ServerEventBindings->HasEvents(ADDON_EVENT_ON_MESSAGE))
        return true;

    LOCK_ELUNA;
    Push(sender);
    Push(type);
    const char* c_msg = msg.c_str();
    Push(strtok((char*)c_msg, "\t")); // prefix
    Push(strtok(NULL, "")); // msg
    if (receiver)
        Push(receiver);
    else if (guild)
        Push(guild);
    else if (group)
        Push(group);
    else if (channel)
        Push(channel->GetChannelId());
    else
        Push();

    return CallAllFunctionsBool(ServerEventBindings, ADDON_EVENT_ON_MESSAGE, true);
}

bool Eluna::OnChat(Player* pPlayer, uint32 type, uint32 lang, std::string& msg)
{
    if (lang == LANG_ADDON)
        return OnAddonMessage(pPlayer, type, msg, NULL, NULL, NULL, NULL);

    if (!PlayerEventBindings->HasEvents(PLAYER_EVENT_ON_CHAT))
        return true;

    LOCK_ELUNA;
    bool result = true;
    Push(pPlayer);
    Push(msg);
    Push(type);
    Push(lang);
    int n = SetupStack(PlayerEventBindings, PLAYER_EVENT_ON_CHAT, 4);

    while (n > 0)
    {
        int r = CallOneFunction(n--, 4, 2);

        if (lua_isboolean(L, r + 0) && !lua_toboolean(L, r + 0))
            result = false;

        if (lua_isstring(L, r + 1))
            msg = std::string(lua_tostring(L, r + 1));

        lua_pop(L, 2);
    }

    CleanUpStack(4);
    return result;
}

bool Eluna::OnChat(Player* pPlayer, uint32 type, uint32 lang, std::string& msg, Group* pGroup)
{
    if (lang == LANG_ADDON)
        return OnAddonMessage(pPlayer, type, msg, NULL, NULL, pGroup, NULL);

    if (!PlayerEventBindings->HasEvents(PLAYER_EVENT_ON_GROUP_CHAT))
        return true;

    LOCK_ELUNA;
    bool result = true;
    Push(pPlayer);
    Push(msg);
    Push(type);
    Push(lang);
    Push(pGroup);
    int n = SetupStack(PlayerEventBindings, PLAYER_EVENT_ON_GROUP_CHAT, 5);

    while (n > 0)
    {
        int r = CallOneFunction(n--, 5, 2);

        if (lua_isboolean(L, r + 0) && !lua_toboolean(L, r + 0))
            result = false;

        if (lua_isstring(L, r + 1))
            msg = std::string(lua_tostring(L, r + 1));

        lua_pop(L, 2);
    }

    CleanUpStack(5);
    return result;
}

bool Eluna::OnChat(Player* pPlayer, uint32 type, uint32 lang, std::string& msg, Guild* pGuild)
{
    if (lang == LANG_ADDON)
        return OnAddonMessage(pPlayer, type, msg, NULL, pGuild, NULL, NULL);

    if (!PlayerEventBindings->HasEvents(PLAYER_EVENT_ON_GUILD_CHAT))
        return true;

    LOCK_ELUNA;
    bool result = true;
    Push(pPlayer);
    Push(msg);
    Push(type);
    Push(lang);
    Push(pGuild);
    int n = SetupStack(PlayerEventBindings, PLAYER_EVENT_ON_GUILD_CHAT, 5);

    while (n > 0)
    {
        int r = CallOneFunction(n--, 5, 2);

        if (lua_isboolean(L, r + 0) && !lua_toboolean(L, r + 0))
            result = false;

        if (lua_isstring(L, r + 1))
            msg = std::string(lua_tostring(L, r + 1));

        lua_pop(L, 2);
    }

    CleanUpStack(5);
    return result;
}

bool Eluna::OnChat(Player* pPlayer, uint32 type, uint32 lang, std::string& msg, Channel* pChannel)
{
    if (lang == LANG_ADDON)
        return OnAddonMessage(pPlayer, type, msg, NULL, NULL, NULL, pChannel);

    if (!PlayerEventBindings->HasEvents(PLAYER_EVENT_ON_CHANNEL_CHAT))
        return true;

    LOCK_ELUNA;
    bool result = true;
    Push(pPlayer);
    Push(msg);
    Push(type);
    Push(lang);
    Push(pChannel->GetChannelId());
    int n = SetupStack(PlayerEventBindings, PLAYER_EVENT_ON_CHANNEL_CHAT, 5);

    while (n > 0)
    {
        int r = CallOneFunction(n--, 5, 2);

        if (lua_isboolean(L, r + 0) && !lua_toboolean(L, r + 0))
            result = false;

        if (lua_isstring(L, r + 1))
            msg = std::string(lua_tostring(L, r + 1));

        lua_pop(L, 2);
    }

    CleanUpStack(5);
    return result;
}

bool Eluna::OnChat(Player* pPlayer, uint32 type, uint32 lang, std::string& msg, Player* pReceiver)
{
    if (lang == LANG_ADDON)
        return OnAddonMessage(pPlayer, type, msg, pReceiver, NULL, NULL, NULL);

    if (!PlayerEventBindings->HasEvents(PLAYER_EVENT_ON_WHISPER))
        return true;

    LOCK_ELUNA;
    bool result = true;
    Push(pPlayer);
    Push(msg);
    Push(type);
    Push(lang);
    Push(pReceiver);
    int n = SetupStack(PlayerEventBindings, PLAYER_EVENT_ON_WHISPER, 5);

    while (n > 0)
    {
        int r = CallOneFunction(n--, 5, 2);

        if (lua_isboolean(L, r + 0) && !lua_toboolean(L, r + 0))
            result = false;

        if (lua_isstring(L, r + 1))
            msg = std::string(lua_tostring(L, r + 1));

        lua_pop(L, 2);
    }

    CleanUpStack(5);
    return result;
}

#endif // _PLAYER_HOOKS_H
