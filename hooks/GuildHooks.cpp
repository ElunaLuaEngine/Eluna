/*
 * Copyright (C) 2010 - 2024 Eluna Lua Engine <https://elunaluaengine.github.io/>
 * This program is free software licensed under GPL version 3
 * Please see the included DOCS/LICENSE.md for more information
 */

#include "Hooks.h"
#include "HookHelpers.h"
#include "LuaEngine.h"
#include "BindingMap.h"
#include "ElunaTemplate.h"

using namespace Hooks;

#define START_HOOK(EVENT) \
    auto key = EventKey<GuildEvents>(EVENT);\
    if (!GuildEventBindings->HasBindingsFor(key))\
        return;

void Eluna::OnAddMember(Guild* guild, Player* player, uint32 plRank)
{
    START_HOOK(GUILD_EVENT_ON_ADD_MEMBER);
    HookPush(guild);
    HookPush(player);
    HookPush(plRank);
    CallAllFunctions(GuildEventBindings, key);
}

void Eluna::OnRemoveMember(Guild* guild, Player* player, bool isDisbanding)
{
    START_HOOK(GUILD_EVENT_ON_REMOVE_MEMBER);
    HookPush(guild);
    HookPush(player);
    HookPush(isDisbanding);
    CallAllFunctions(GuildEventBindings, key);
}

void Eluna::OnMOTDChanged(Guild* guild, const std::string& newMotd)
{
    START_HOOK(GUILD_EVENT_ON_MOTD_CHANGE);
    HookPush(guild);
    HookPush(newMotd);
    CallAllFunctions(GuildEventBindings, key);
}

void Eluna::OnInfoChanged(Guild* guild, const std::string& newInfo)
{
    START_HOOK(GUILD_EVENT_ON_INFO_CHANGE);
    HookPush(guild);
    HookPush(newInfo);
    CallAllFunctions(GuildEventBindings, key);
}

void Eluna::OnCreate(Guild* guild, Player* leader, const std::string& name)
{
    START_HOOK(GUILD_EVENT_ON_CREATE);
    HookPush(guild);
    HookPush(leader);
    HookPush(name);
    CallAllFunctions(GuildEventBindings, key);
}

void Eluna::OnDisband(Guild* guild)
{
    START_HOOK(GUILD_EVENT_ON_DISBAND);
    HookPush(guild);
    CallAllFunctions(GuildEventBindings, key);
}

void Eluna::OnMemberWitdrawMoney(Guild* guild, Player* player, uint32& amount, bool isRepair)
{
    START_HOOK(GUILD_EVENT_ON_MONEY_WITHDRAW);
    HookPush(guild);
    HookPush(player);
    HookPush(amount);
    HookPush(isRepair); // isRepair not a part of Mangos, implement?
    int amountIndex = lua_gettop(L) - 1;
    int n = SetupStack(GuildEventBindings, key, 4);

    while (n > 0)
    {
        int r = CallOneFunction(n--, 4, 1);

        if (lua_isnumber(L, r))
        {
            amount = CHECKVAL<uint32>(r);
            // Update the stack for subsequent calls.
            ReplaceArgument(amount, amountIndex);
        }

        lua_pop(L, 1);
    }

    CleanUpStack(4);
}

#ifdef CATA
void Eluna::OnMemberWitdrawMoney(Guild* guild, Player* player, uint64& amount, bool isRepair)
{
    START_HOOK(GUILD_EVENT_ON_MONEY_WITHDRAW);
    HookPush(guild);
    HookPush(player);
    HookPush(amount);
    HookPush(isRepair); // isRepair not a part of Mangos, implement?
    int amountIndex = lua_gettop(L) - 1;
    int n = SetupStack(GuildEventBindings, key, 4);

    while (n > 0)
    {
        int r = CallOneFunction(n--, 4, 1);

        if (lua_isnumber(L, r))
        {
            amount = CHECKVAL<uint32>(r);
            // Update the stack for subsequent calls.
            ReplaceArgument(amount, amountIndex);
        }

        lua_pop(L, 1);
    }

    CleanUpStack(4);
}
#endif

void Eluna::OnMemberDepositMoney(Guild* guild, Player* player, uint32& amount)
{
    START_HOOK(GUILD_EVENT_ON_MONEY_DEPOSIT);
    HookPush(guild);
    HookPush(player);
    HookPush(amount);
    int amountIndex = lua_gettop(L);
    int n = SetupStack(GuildEventBindings, key, 3);

    while (n > 0)
    {
        int r = CallOneFunction(n--, 3, 1);

        if (lua_isnumber(L, r))
        {
            amount = CHECKVAL<uint32>(r);
            // Update the stack for subsequent calls.
            ReplaceArgument(amount, amountIndex);
        }

        lua_pop(L, 1);
    }

    CleanUpStack(3);
}

#ifdef CATA
void Eluna::OnMemberDepositMoney(Guild* guild, Player* player, uint64& amount)
{
    START_HOOK(GUILD_EVENT_ON_MONEY_DEPOSIT);
    HookPush(guild);
    HookPush(player);
    HookPush(amount);
    int amountIndex = lua_gettop(L);
    int n = SetupStack(GuildEventBindings, key, 3);

    while (n > 0)
    {
        int r = CallOneFunction(n--, 3, 1);

        if (lua_isnumber(L, r))
        {
            amount = CHECKVAL<uint32>(r);
            // Update the stack for subsequent calls.
            ReplaceArgument(amount, amountIndex);
        }

        lua_pop(L, 1);
    }

    CleanUpStack(3);
}
#endif

void Eluna::OnItemMove(Guild* guild, Player* player, Item* pItem, bool isSrcBank, uint8 srcContainer, uint8 srcSlotId,
    bool isDestBank, uint8 destContainer, uint8 destSlotId)
{
    START_HOOK(GUILD_EVENT_ON_ITEM_MOVE);
    HookPush(guild);
    HookPush(player);
    HookPush(pItem);
    HookPush(isSrcBank);
    HookPush(srcContainer);
    HookPush(srcSlotId);
    HookPush(isDestBank);
    HookPush(destContainer);
    HookPush(destSlotId);
    CallAllFunctions(GuildEventBindings, key);
}

void Eluna::OnEvent(Guild* guild, uint8 eventType, uint32 playerGuid1, uint32 playerGuid2, uint8 newRank)
{
    START_HOOK(GUILD_EVENT_ON_EVENT);
    HookPush(guild);
    HookPush(eventType);
    HookPush(playerGuid1);
    HookPush(playerGuid2);
    HookPush(newRank);
    CallAllFunctions(GuildEventBindings, key);
}

void Eluna::OnBankEvent(Guild* guild, uint8 eventType, uint8 tabId, uint32 playerGuid, uint32 itemOrMoney, uint16 itemStackCount, uint8 destTabId)
{
    START_HOOK(GUILD_EVENT_ON_BANK_EVENT);
    HookPush(guild);
    HookPush(eventType);
    HookPush(tabId);
    HookPush(playerGuid);
    HookPush(itemOrMoney);
    HookPush(itemStackCount);
    HookPush(destTabId);
    CallAllFunctions(GuildEventBindings, key);
}
