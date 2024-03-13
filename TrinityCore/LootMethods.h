/*
* Copyright (C) 2010 - 2024 Eluna Lua Engine <https://elunaluaengine.github.io/>
* This program is free software licensed under GPL version 3
* Please see the included DOCS/LICENSE.md for more information
*/

#ifndef LOOTMETHODS_H
#define LOOTMETHODS_H

namespace LuaLoot
{
    /**
     * Returns a boolean indicating whether the [Loot] has been looted.
     *
     * @return bool : true if the [Loot] has been looted; false otherwise
     */
    int IsLooted(Eluna* E,  Loot* loot)
    {
        E->Push(loot->isLooted());
        return 1;
    }
    
    /**
     * Adds an item to the [Loot] with specified details.
     *
     * @param uint32 itemid : the ID of the item to be added
     * @param float chance : the loot chance of the item
     * @param bool needsquest : whether the item needs a quest to be looted, default is false
     * @param uint16 lootmode : the loot mode of the item
     * @param uint32 mincount : the minimum count of the item
     * @param uint32 maxcount : the maximum count of the item
     */
    int AddItem(Eluna* E,  Loot* loot)
    {
        uint32 item = E->CHECKVAL<uint32>(2);
        float chance = E->CHECKVAL<float>(3);
        bool needsquest = E->CHECKVAL<bool>(4, false);
        uint16 lootmode = E->CHECKVAL<bool>(5);
        uint32 mincount = E->CHECKVAL<uint32>(6);
        uint32 maxcount = E->CHECKVAL<uint32>(7);

        for (LootItem& lootitem : loot->items)
        {
            if (lootitem.itemid == item && lootitem.count < 255)
            {
                lootitem.count += lootitem.count + mincount;
                return 0;
            }
        }

        LootStoreItem newLootStoreItem(item, 0, chance, needsquest, lootmode, 0, mincount, maxcount);
        loot->AddItem(newLootStoreItem);
        return 0;
    }
    
    /**
     * Checks whether a specified item is in the [Loot].
     * 
     * If an Item ID is specified, the function checks for that specific item.
     * If no Item ID is provided, the function checks whether there is any item present in the loot.
     * 
     * @param uint32 itemid : the ID of the item to check for, defaults to false
     * @return bool : true if the item is in the [Loot], false otherwise
     */
    int HasItem(Eluna* E,  Loot* loot)
    {
        uint32 itemid = E->CHECKVAL<uint32>(2, false);
        bool has_item = false;

        if ( itemid )
        {
            for (LootItem& lootitem : loot->items)
            {
                if (lootitem.itemid == itemid)
                    has_item = true;
            }
        }
        else
        {
            for (LootItem& lootitem : loot->items)
            {
                if (lootitem.itemid && lootitem.itemid != 0)
                    has_item = true;
            }
        }

        E->Push(has_item);
        return 1;
    }
    
    /**
     * Removes all instances of a specified item from [Loot].
     *
     * @param uint32 itemid : the ID of the item to remove
     */
    int RemoveItem(Eluna* E, Loot* loot)
    {
        uint32 itemid = E->CHECKVAL<uint32>(2);
        loot->items.erase(
            std::remove_if(
                loot->items.begin(), loot->items.end(), [itemid](const LootItem& item)
                {
                    return item.itemid == itemid;
                }), loot->items.end());
        return 0;
    }
    
    /**
     * Returns the total money in [Loot].
     *
     * @return int : the total money in the [Loot]
     */
    int GetMoney(Eluna* E, Loot* loot)
    {
        E->Push(loot->gold);
        return 1;
    }
    
    /**
     * Sets the total money in [Loot].
     *
     * @param uint32 money : the total money to set
     */
    int SetMoney(Eluna* E, Loot* loot)
    {
        uint32 money = E->CHECKVAL<uint32>(2);
        loot->gold = money;
        return 0;
    }
    
    /**
    * Generates a random amount of money in the range [min, max] and adds it to [Loot].
    *
    * @param uint32 min : the minimum amount of money to generate
    * @param uint32 max : the maximum amount of money to generate
    */    
    int GenerateMoney(Eluna* E, Loot* loot)
    {
        uint32 min = E->CHECKVAL<uint32>(2);
        uint32 max = E->CHECKVAL<uint32>(3);
        loot->generateMoneyLoot(min, max);
        return 0;
    }

    ElunaRegister<Loot> LootMethods[] =
    {
        // Getters
        { "GetMoney", &LuaLoot::GetMoney },
        
        // Setters
        { "AddItem", &LuaLoot::AddItem },
        { "RemoveItem", &LuaLoot::RemoveItem },
        { "SetMoney", &LuaLoot::SetMoney },
        { "GenerateMoney", &LuaLoot::GenerateMoney },
        
        // Boolean
        { "IsLooted", &LuaLoot::IsLooted },
        { "HasItem", &LuaLoot::HasItem },
        
        // Other

        { NULL, NULL, METHOD_REG_NONE }
    };

}
#endif
