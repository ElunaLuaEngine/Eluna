/*
 * Copyright (C) 2010 - 2015 Eluna Lua Engine <http://emudevs.com/>
 * This program is free software licensed under GPL version 3
 * Please see the included DOCS/LICENSE.md for more information
 */

#ifndef _GUILD_HOOKS_H
#define _GUILD_HOOKS_H

#include "Hooks.h"
#include "HookHelpers.h"
#include "LuaEngine.h"
#include "ElunaBinding.h"
#include "ElunaTemplate.h"

using namespace Hooks;

void Eluna::OnAddMember(Guild* guild, Player* player, uint32 plRank)
{
    if (!GuildEventBindings->HasEvents(GUILD_EVENT_ON_ADD_MEMBER))
        return;

    LOCK_ELUNA;
    Push(guild);
    Push(player);
    Push(plRank);
    CallAllFunctions(GuildEventBindings, GUILD_EVENT_ON_ADD_MEMBER);
}

void Eluna::OnRemoveMember(Guild* guild, Player* player, bool isDisbanding)
{
    if (!GuildEventBindings->HasEvents(GUILD_EVENT_ON_REMOVE_MEMBER))
        return;

    LOCK_ELUNA;
    Push(guild);
    Push(player);
    Push(isDisbanding);
    CallAllFunctions(GuildEventBindings, GUILD_EVENT_ON_REMOVE_MEMBER);
}

void Eluna::OnMOTDChanged(Guild* guild, const std::string& newMotd)
{
    if (!GuildEventBindings->HasEvents(GUILD_EVENT_ON_MOTD_CHANGE))
        return;

    LOCK_ELUNA;
    Push(guild);
    Push(newMotd);
    CallAllFunctions(GuildEventBindings, GUILD_EVENT_ON_MOTD_CHANGE);
}

void Eluna::OnInfoChanged(Guild* guild, const std::string& newInfo)
{
    if (!GuildEventBindings->HasEvents(GUILD_EVENT_ON_INFO_CHANGE))
        return;

    LOCK_ELUNA;
    Push(guild);
    Push(newInfo);
    CallAllFunctions(GuildEventBindings, GUILD_EVENT_ON_INFO_CHANGE);
}

void Eluna::OnCreate(Guild* guild, Player* leader, const std::string& name)
{
    if (!GuildEventBindings->HasEvents(GUILD_EVENT_ON_CREATE))
        return;

    LOCK_ELUNA;
    Push(guild);
    Push(leader);
    Push(name);
    CallAllFunctions(GuildEventBindings, GUILD_EVENT_ON_CREATE);
}

void Eluna::OnDisband(Guild* guild)
{
    if (!GuildEventBindings->HasEvents(GUILD_EVENT_ON_DISBAND))
        return;

    LOCK_ELUNA;
    Push(guild);
    CallAllFunctions(GuildEventBindings, GUILD_EVENT_ON_DISBAND);
}

void Eluna::OnMemberWitdrawMoney(Guild* guild, Player* player, uint32& amount, bool isRepair) // isRepair not a part of Mangos, implement?
{
    if (!GuildEventBindings->HasEvents(GUILD_EVENT_ON_MONEY_WITHDRAW))
        return;

    LOCK_ELUNA;
    Push(guild);
    Push(player);
    Push(amount);
    Push(isRepair); // isRepair not a part of Mangos, implement?
    int amountIndex = lua_gettop(L) - 1;
    int n = SetupStack(GuildEventBindings, GUILD_EVENT_ON_MONEY_WITHDRAW, 4);

    while (n > 0)
    {
        int r = CallOneFunction(n--, 4, 1);

        if (lua_isnumber(L, r))
        {
            amount = CHECKVAL<uint32>(L, r);
            // Update the stack for subsequent calls.
            ReplaceArgument(amount, amountIndex);
        }

        lua_pop(L, 1);
    }

    CleanUpStack(4);
}

void Eluna::OnMemberDepositMoney(Guild* guild, Player* player, uint32& amount)
{
    if (!GuildEventBindings->HasEvents(GUILD_EVENT_ON_MONEY_DEPOSIT))
        return;

    LOCK_ELUNA;
    Push(guild);
    Push(player);
    Push(amount);
    int amountIndex = lua_gettop(L);
    int n = SetupStack(GuildEventBindings, GUILD_EVENT_ON_MONEY_DEPOSIT, 3);

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

void Eluna::OnItemMove(Guild* guild, Player* player, Item* pItem, bool isSrcBank, uint8 srcContainer, uint8 srcSlotId,
    bool isDestBank, uint8 destContainer, uint8 destSlotId)
{
    if (!GuildEventBindings->HasEvents(GUILD_EVENT_ON_ITEM_MOVE))
        return;

    LOCK_ELUNA;
    Push(guild);
    Push(player);
    Push(pItem);
    Push(isSrcBank);
    Push(srcContainer);
    Push(srcSlotId);
    Push(isDestBank);
    Push(destContainer);
    Push(destSlotId);
    CallAllFunctions(GuildEventBindings, GUILD_EVENT_ON_ITEM_MOVE);
}

void Eluna::OnEvent(Guild* guild, uint8 eventType, uint32 playerGuid1, uint32 playerGuid2, uint8 newRank)
{
    if (!GuildEventBindings->HasEvents(GUILD_EVENT_ON_EVENT))
        return;

    LOCK_ELUNA;
    Push(guild);
    Push(eventType);
    Push(playerGuid1);
    Push(playerGuid2);
    Push(newRank);
    CallAllFunctions(GuildEventBindings, GUILD_EVENT_ON_EVENT);
}

void Eluna::OnBankEvent(Guild* guild, uint8 eventType, uint8 tabId, uint32 playerGuid, uint32 itemOrMoney, uint16 itemStackCount, uint8 destTabId)
{
    if (!GuildEventBindings->HasEvents(GUILD_EVENT_ON_BANK_EVENT))
        return;

    LOCK_ELUNA;
    Push(guild);
    Push(eventType);
    Push(tabId);
    Push(playerGuid);
    Push(itemOrMoney);
    Push(itemStackCount);
    Push(destTabId);
    CallAllFunctions(GuildEventBindings, GUILD_EVENT_ON_BANK_EVENT);
}

#endif // _GUILD_HOOKS_H
