/*
* Copyright (C) 2010 - 2024 Eluna Lua Engine <https://elunaluaengine.github.io/>
* This program is free software licensed under GPL version 3
* Please see the included DOCS/LICENSE.md for more information
*/

#ifndef LOOTMETHODS_H
#define LOOTMETHODS_H

/***
 * Inherits all methods from: none
 */
namespace LuaLoot
{
    /**
     * Returns `true` if the [Loot] is already looted, `false` otherwise.
     *
     * @return bool isLooted
     */
    int IsLooted(Eluna* E, Loot* loot)
    {
        E->Push(loot->isLooted());
        return 1;
    }

    /**
     * Add an item to the [Loot] object
     * 
     * @param uint32 itemid : The entry ID of the item to add.
     * @param float chance : The drop chance of the item, represented as a percentage (0-100%).
     * @param bool needs_quest : Specifies if the item is required for a quest (true if required, false otherwise).
     * @param uint16 lootmode : The mode of loot in which the item should be added. It determines under what circumstances the item can be looted.
     * @param uint8 groupid : The group ID for the item, used for grouping related items in the loot table.
     * @param int32 mincount : The minimum quantity of the item that can be dropped.
     * @param uint8 maxcount : The maximum quantity of the item that can be dropped.
     */
    int AddItem(Eluna* E, Loot* loot)
    {
        uint32 itemid = E->CHECKVAL<uint32>(2);
        float chance = E->CHECKVAL<float>(3);
        bool needs_quest = E->CHECKVAL<bool>(4);
        uint16 lootmode = E->CHECKVAL<uint16>(5);
        uint8 groupid = E->CHECKVAL<uint8>(6);
        int32 mincount = E->CHECKVAL<int32>(7);
        uint8 maxcount = E->CHECKVAL<uint8>(8);

        for (LootItem &lootitem : loot->items)
        {
            if (lootitem.itemid == itemid && lootitem.count < 255)
            {
                lootitem.count += mincount; // Todo: Update to get rand between mincount and maxcount
                break;
            }
        }

        LootStoreItem newLootStoreItem(itemid, 0, chance, needs_quest, lootmode, groupid, mincount, maxcount);
        loot->AddItem(newLootStoreItem);

        return 0;
    }

    /**
     * Returns `true` if the [Loot] have item, `false` otherwise.
     * 
     * @param uint32 itemid : The entry ID of the item to check (optionnal).
     * @param uint32 count : The count of item to check (optionnal).
     * @return bool hasItem : if not itemid return if [Loot] have any item.
     */
    int HasItem(Eluna* E, Loot* loot)
    {
        uint32 itemid = E->CHECKVAL<uint32>(2, false);
        uint32 count = E->CHECKVAL<uint32>(3, 0);

        bool hasItem = false;

        if (itemid)
        {
            for (const LootItem &lootitem : loot->items)
            {
                if (lootitem.itemid == itemid && (count == 0 || lootitem.count == count))
                {
                    hasItem = true;
                    break;
                }
            }
        }
        else
        {
            for (const LootItem &lootitem : loot->items)
            {
                if (lootitem.itemid && lootitem.itemid != 0)
                {
                    hasItem = true;
                    break;
                }
            }
        }

        E->Push(hasItem);
        return 1;
    }

    /**
     * Remove Item from the [Loot]. If there is no count there is delete all the specified itemid.
     * 
     * @param uint32 itemid : The entry ID of the item to check (optionnal).
     * @param uint32 count : The count of item to check (optionnal).
     */
    int RemoveItem(Eluna* E, Loot* loot)
    {
        uint32 itemid = E->CHECKVAL<uint32>(2);
        uint32 count = E->CHECKVAL<uint32>(3, 0);
        bool isCountSpecified = count != 0 ? true : false;

        for (auto it = loot->items.begin(); it != loot->items.end();)
        {
            if (it->itemid == itemid)
            {
                if (isCountSpecified)
                {
                    if (it->count > count)
                    {
                        it->count -= count;
                        break;
                    }
                }
                it = loot->items.erase(it);
            }
            else
                ++it;
        }

        return 0;
    }

    /**
     * Returns the copper amount on the [Loot].
     *
     * @return uint32 copper
     */
    int GetMoney(Eluna* E, Loot* loot)
    {
        E->Push(loot->gold);
        return 1;
    }

    /**
     * Set the specified copper amount to the [Loot].
     *
     * @param uint32 copper_amount : copper amount needed to add to the [Loot].
     */
    int SetMoney(Eluna* E, Loot* loot)
    {
        uint32 copper_amount = E->CHECKVAL<uint32>(2);
        loot->gold = copper_amount;

        return 0;
    }

    /**
     * Generate random copper amount to the [Loot].
     *
     * @param uint32 min_amount.
     * @param uint32 max_amount.
     */
    int GenerateMoney(Eluna* E, Loot* loot)
    {
        uint32 min_amount = E->CHECKVAL<uint32>(2);
        uint32 max_amount = E->CHECKVAL<uint32>(3);
        loot->generateMoneyLoot(min_amount, max_amount);

        return 0;
    }

    /**
     * Clear the [Loot].
     */
    int Clear(Eluna* /*E*/, Loot* loot)
    {
        loot->clear();
        return 0;
    }

    ElunaRegister<Loot> LootMethods[] =
    {
        // Getters
        { "GetMoney", &LuaLoot::GetMoney },

        // Setters
        { "SetMoney", &LuaLoot::SetMoney },

        // Boolean
        { "IsLooted", &LuaLoot::IsLooted },
        { "HasItem", &LuaLoot::HasItem },

        // Other
        { "AddItem", &LuaLoot::AddItem },
        { "RemoveItem", &LuaLoot::RemoveItem },
        { "GenerateMoney", &LuaLoot::GenerateMoney },
        { "Clear", &LuaLoot::Clear },
    };
}
#endif