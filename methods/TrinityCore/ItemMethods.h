/*
* Copyright (C) 2010 - 2024 Eluna Lua Engine <https://elunaluaengine.github.io/>
* This program is free software licensed under GPL version 3
* Please see the included DOCS/LICENSE.md for more information
*/

#ifndef ITEMMETHODS_H
#define ITEMMETHODS_H

/***
 * Inherits all methods from: [Object]
 */
namespace LuaItem
{
    /**
     * Returns 'true' if the [Item] is soulbound, 'false' otherwise
     *
     * @return bool isSoulBound
     */
    int IsSoulBound(Eluna* E, Item* item)
    {
        E->Push(item->IsSoulBound());
        return 1;
    }

    /**
     * Returns 'true' if the [Item] is account bound, 'false' otherwise
     *
     * @return bool isAccountBound
     */
    int IsBoundAccountWide(Eluna* E, Item* item)
    {
        E->Push(item->IsBoundAccountWide());
        return 1;
    }

    /**
     * Returns 'true' if the [Item] is bound to a [Player] by an enchant, 'false' otehrwise
     *
     * @return bool isBoundByEnchant
     */
    int IsBoundByEnchant(Eluna* E, Item* item)
    {
        E->Push(item->IsBoundByEnchant());
        return 1;
    }

    /**
     * Returns 'true' if the [Item] is not bound to the [Player] specified, 'false' otherwise
     *
     * @param [Player] player : the [Player] object to check the item against
     * @return bool isNotBound
     */
    int IsNotBoundToPlayer(Eluna* E, Item* item)
    {
        Player* player = E->CHECKOBJ<Player>(2);

        E->Push(item->IsBindedNotWith(player));
        return 1;
    }

    /**
     * Returns 'true' if the [Item] is locked, 'false' otherwise
     *
     * @return bool isLocked
     */
    int IsLocked(Eluna* E, Item* item)
    {
        E->Push(item->IsLocked());
        return 1;
    }

    /**
     * Returns 'true' if the [Item] is a bag, 'false' otherwise
     *
     * @return bool isBag
     */
    int IsBag(Eluna* E, Item* item)
    {
        E->Push(item->IsBag());
        return 1;
    }

    /**
     * Returns 'true' if the [Item] is a currency token, 'false' otherwise
     *
     * @return bool isCurrencyToken
     */
    int IsCurrencyToken(Eluna* E, Item* item)
    {
        E->Push(item->IsCurrencyToken());
        return 1;
    }

    /**
     * Returns 'true' if the [Item] is a not an empty bag, 'false' otherwise
     *
     * @return bool isNotEmptyBag
     */
    int IsNotEmptyBag(Eluna* E, Item* item)
    {
        E->Push(item->IsNotEmptyBag());
        return 1;
    }

    /**
     * Returns 'true' if the [Item] is broken, 'false' otherwise
     *
     * @return bool isBroken
     */
    int IsBroken(Eluna* E, Item* item)
    {
        E->Push(item->IsBroken());
        return 1;
    }

    /**
     * Returns 'true' if the [Item] can be traded, 'false' otherwise
     *
     * @return bool isTradeable
     */
    int CanBeTraded(Eluna* E, Item* item)
    {
        bool mail = E->CHECKVAL<bool>(2, false);

        E->Push(item->CanBeTraded(mail));
        return 1;
    }

    /**
     * Returns 'true' if the [Item] is currently in a trade window, 'false' otherwise
     *
     * @return bool isInTrade
     */
    int IsInTrade(Eluna* E, Item* item)
    {
        E->Push(item->IsInTrade());
        return 1;
    }

    /**
     * Returns 'true' if the [Item] is currently in a bag, 'false' otherwise
     *
     * @return bool isInBag
     */
    int IsInBag(Eluna* E, Item* item)
    {
        E->Push(item->IsInBag());
        return 1;
    }

    /**
     * Returns 'true' if the [Item] is currently equipped, 'false' otherwise
     *
     * @return bool isEquipped
     */
    int IsEquipped(Eluna* E, Item* item)
    {
        E->Push(item->IsEquipped());
        return 1;
    }

    /**
     * Returns 'true' if the [Item] has the [Quest] specified tied to it, 'false' otherwise
     *
     * @param uint32 questId : the [Quest] id to be checked
     * @return bool hasQuest
     */
    int HasQuest(Eluna* E, Item* item)
    {
        uint32 quest = E->CHECKVAL<uint32>(2);

        E->Push(item->hasQuest(quest));
        return 1;
    }

    /**
     * Returns 'true' if the [Item] is a potion, 'false' otherwise
     *
     * @return bool isPotion
     */
    int IsPotion(Eluna* E, Item* item)
    {
        E->Push(item->IsPotion());
        return 1;
    }

#if ELUNA_EXPANSION < EXP_RETAIL
    /**
     * Returns 'true' if the [Item] is a weapon vellum, 'false' otherwise
     *
     * @return bool isWeaponVellum
     */
    int IsWeaponVellum(Eluna* E, Item* item)
    {
        E->Push(item->IsWeaponVellum());
        return 1;
    }

    /**
     * Returns 'true' if the [Item] is an armor vellum, 'false' otherwise
     *
     * @return bool isArmorVellum
     */
    int IsArmorVellum(Eluna* E, Item* item)
    {
        E->Push(item->IsArmorVellum());
        return 1;
    }
#endif

    /**
     * Returns 'true' if the [Item] is a conjured consumable, 'false' otherwise
     *
     * @return bool isConjuredConsumable
     */
    int IsConjuredConsumable(Eluna* E, Item* item)
    {
        E->Push(item->IsConjuredConsumable());
        return 1;
    }

    /**
     * Returns 'true' if the refund period has expired for this [Item], 'false' otherwise
     *
     * @return bool isRefundExpired
     */
    int IsRefundExpired(Eluna* E, Item* item)
    {
        E->Push(item->IsRefundExpired());
        return 1;
    }

#if ELUNA_EXPANSION < EXP_RETAIL
    /**
     * Returns the chat link of the [Item]
     *
     * @table
     * @columns [Locale, ID]
     * @values [LOCALE_enUS, 0]
     * @values [LOCALE_koKR, 1]
     * @values [LOCALE_frFR, 2]
     * @values [LOCALE_deDE, 3]
     * @values [LOCALE_zhCN, 4]
     * @values [LOCALE_zhTW, 5]
     * @values [LOCALE_esES, 6]
     * @values [LOCALE_esMX, 7]
     * @values [LOCALE_ruRU, 8]
     *
     * @param [LocaleConstant] locale = DEFAULT_LOCALE : locale to return the [Item]'s name in
     * @return string itemLink
     */
    int GetItemLink(Eluna* E, Item* item)
    {
        uint8 locale = E->CHECKVAL<uint8>(2, DEFAULT_LOCALE);
        if (locale >= TOTAL_LOCALES)
            return luaL_argerror(E->L, 2, "valid LocaleConstant expected");

        const ItemTemplate* temp = item->GetTemplate();

        std::string name = temp->Name1;
        if (ItemLocale const* il = eObjectMgr->GetItemLocale(temp->ItemId))
            ObjectMgr::GetLocaleString(il->Name, static_cast<LocaleConstant>(locale), name);

        if (int32 itemRandPropId = item->GetItemRandomPropertyId())
        {
            std::array<char const*, 16> const* suffix = NULL;
            if (itemRandPropId < 0)
            {
                const ItemRandomSuffixEntry* itemRandEntry = sItemRandomSuffixStore.LookupEntry(-item->GetItemRandomPropertyId());
                if (itemRandEntry)
                    suffix = &itemRandEntry->Name;
            }
            else
            {
                const ItemRandomPropertiesEntry* itemRandEntry = sItemRandomPropertiesStore.LookupEntry(item->GetItemRandomPropertyId());
                if (itemRandEntry)
                    suffix = &itemRandEntry->Name;
            }
            if (suffix)
            {
                name += ' ';
                name += (*suffix)[(name != temp->Name1) ? locale : uint8(DEFAULT_LOCALE)];
            }
        }

        std::ostringstream oss;
        oss << "|c" << std::hex << ItemQualityColors[temp->Quality] << std::dec <<
            "|Hitem:" << temp->ItemId << ":" <<
            item->GetEnchantmentId(PERM_ENCHANTMENT_SLOT) << ":" <<
            item->GetEnchantmentId(SOCK_ENCHANTMENT_SLOT) << ":" <<
            item->GetEnchantmentId(SOCK_ENCHANTMENT_SLOT_2) << ":" <<
            item->GetEnchantmentId(SOCK_ENCHANTMENT_SLOT_3) << ":" <<
            item->GetEnchantmentId(BONUS_ENCHANTMENT_SLOT) << ":" <<
            item->GetItemRandomPropertyId() << ":" << item->GetItemSuffixFactor() << ":" <<
            (uint32)item->GetOwner()->GetLevel() << "|h[" << name << "]|h|r";

        E->Push(oss.str());
        return 1;
    }
#endif

    /**
     * Returns GUID of the [Player] who currently owns the [Item]
     *
     * @return ObjectGuid guid : guid of the [Player] who owns the [Item]
     */
    int GetOwnerGUID(Eluna* E, Item* item)
    {
        E->Push(item->GetOwnerGUID());
        return 1;
    }

    /**
     * Returns the [Player] who currently owns the [Item]
     *
     * @return [Player] player : the [Player] who owns the [Item]
     */
    int GetOwner(Eluna* E, Item* item)
    {
        E->Push(item->GetOwner());
        return 1;
    }

    /**
     * Returns the [Item]s stack count
     *
     * @return uint32 count
     */
    int GetCount(Eluna* E, Item* item)
    {
        E->Push(item->GetCount());
        return 1;
    }

    /**
     * Returns the [Item]s max stack count
     *
     * @return uint32 maxCount
     */
    int GetMaxStackCount(Eluna* E, Item* item)
    {
        E->Push(item->GetMaxStackCount());
        return 1;
    }

    /**
     * Returns the [Item]s current slot
     *
     * @return uint8 slot
     */
    int GetSlot(Eluna* E, Item* item)
    {
        E->Push(item->GetSlot());
        return 1;
    }

    /**
     * Returns the [Item]s current bag slot
     *
     * @return uint8 bagSlot
     */
    int GetBagSlot(Eluna* E, Item* item)
    {
        E->Push(item->GetBagSlot());
        return 1;
    }

    /**
     * Returns the [Item]s enchantment ID by enchant slot specified
     *
     * @param [EnchantmentSlot] enchantSlot : the enchant slot specified
     * @return uint32 enchantId : the id of the enchant slot specified
     */
    int GetEnchantmentId(Eluna* E, Item* item)
    {
        uint32 enchant_slot = E->CHECKVAL<uint32>(2);

        if (enchant_slot >= MAX_INSPECTED_ENCHANTMENT_SLOT)
            return luaL_argerror(E->L, 2, "valid EnchantmentSlot expected");

        E->Push(item->GetEnchantmentId(EnchantmentSlot(enchant_slot)));
        return 1;
    }

#if ELUNA_EXPANSION < EXP_RETAIL
    /**
     * Returns the spell ID tied to the [Item] by spell index
     *
     * @param uint32 spellIndex : the spell index specified
     * @return uint32 spellId : the id of the spell
     */
    int GetSpellId(Eluna* E, Item* item)
    {
        uint32 index = E->CHECKVAL<uint32>(2);
        if (index >= MAX_ITEM_PROTO_SPELLS)
            return luaL_argerror(E->L, 2, "valid SpellIndex expected");

        E->Push(item->GetTemplate()->Spells[index].SpellId);
        return 1;
    }

    /**
     * Returns the spell trigger tied to the [Item] by spell index
     *
     * @param uint32 spellIndex : the spell index specified
     * @return uint32 spellTrigger : the spell trigger of the specified index
     */
    int GetSpellTrigger(Eluna* E, Item* item)
    {
        uint32 index = E->CHECKVAL<uint32>(2);
        if (index >= MAX_ITEM_PROTO_SPELLS)
            return luaL_argerror(E->L, 2, "valid SpellIndex expected");

        E->Push(item->GetTemplate()->Spells[index].SpellTrigger);
        return 1;
    }
#endif

    /**
     * Returns class of the [Item]
     *
     * @return uint32 class
     */
    int GetClass(Eluna* E, Item* item)
    {
#if ELUNA_EXPANSION >= EXP_CATA
        E->Push(item->GetTemplate()->GetClass());
#else
        E->Push(item->GetTemplate()->Class);
#endif
        return 1;
    }

    /**
     * Returns subclass of the [Item]
     *
     * @return uint32 subClass
     */
    int GetSubClass(Eluna* E, Item* item)
    {
#if ELUNA_EXPANSION >= EXP_CATA
        E->Push(item->GetTemplate()->GetSubClass());
#else
        E->Push(item->GetTemplate()->SubClass);
#endif
        return 1;
    }

    /**
    * Returns the ID of the [Item]
    *
    * @return uint32 itemId
    */
    int GetItemId(Eluna* E, Item* item)
    {
#if ELUNA_EXPANSION < EXP_RETAIL
        E->Push(item->GetTemplate()->ItemId);
#else
        E->Push(item->GetTemplate()->BasicData->ID);
#endif
        return 1;
    }

    /**
     * Returns the name of the [Item]
     *
     * @return string name
     */
    int GetName(Eluna* E, Item* item)
    {
#if ELUNA_EXPANSION >= EXP_CATA
        E->Push(item->GetTemplate()->GetDefaultLocaleName());
#else
        E->Push(item->GetTemplate()->Name1);
#endif
        return 1;
    }

    /**
     * Returns the display ID of the [Item]
     *
     * @return uint32 displayId
     */
    int GetDisplayId(Eluna* E, Item* item)
    {
#if ELUNA_EXPANSION < EXP_RETAIL
        E->Push(item->GetTemplate()->DisplayInfoID);
#else
        auto player = item->GetOwner();
        E->Push(item->GetDisplayId(player));
#endif
        return 1;
    }

    /**
     * Returns the quality of the [Item]
     *
     * @return uint32 quality
     */
    int GetQuality(Eluna* E, Item* item)
    {
#if ELUNA_EXPANSION >= EXP_CATA
        E->Push(item->GetTemplate()->GetQuality());
#else
        E->Push(item->GetTemplate()->Quality);
#endif
        return 1;
    }

    /**
    * Returns the flags of the [Item]
    *
    * @return uint32 flags
    */
    int GetFlags(Eluna* E, Item* item)
    {
#if ELUNA_EXPANSION < EXP_RETAIL
        E->Push(item->GetTemplate()->Flags);
#else
        E->Push(item->GetTemplate()->ExtendedData->Flags[0]);
#endif
        return 1;
    }

    /**
    * Returns the flags2 of the [Item]
    *
    * @return uint32 flags2
    */
    int GetFlags2(Eluna* E, Item* item)
    {
#if ELUNA_EXPANSION < EXP_RETAIL
        E->Push(item->GetTemplate()->Flags2);
#else
        E->Push(item->GetTemplate()->ExtendedData->Flags[1]);
#endif
        return 1;
    }

    /**
    * Returns the extraFlags of the [Item]
    *
    * @return uint32 extraFlags
    */
    int GetExtraFlags(Eluna* E, Item* item)
    {
        E->Push(item->GetTemplate()->FlagsCu);
        return 1;
    }

    /**
     * Returns the default purchase count of the [Item]
     *
     * @return uint32 count
     */
    int GetBuyCount(Eluna* E, Item* item)
    {
#if ELUNA_EXPANSION >= EXP_CATA
        E->Push(item->GetTemplate()->GetBuyCount());
#else
        E->Push(item->GetTemplate()->BuyCount);
#endif
        return 1;
    }

    /**
     * Returns the purchase price of the [Item]
     *
     * @return uint32 price
     */
    int GetBuyPrice(Eluna* E, Item* item)
    {
#if ELUNA_EXPANSION >= EXP_CATA
        E->Push(item->GetTemplate()->GetBuyPrice());
#else
        E->Push(item->GetTemplate()->BuyPrice);
#endif
        return 1;
    }

    /**
     * Returns the sell price of the [Item]
     *
     * @return uint32 price
     */
    int GetSellPrice(Eluna* E, Item* item)
    {
#if ELUNA_EXPANSION >= EXP_CATA
        E->Push(item->GetTemplate()->GetSellPrice());
#else
        E->Push(item->GetTemplate()->SellPrice);
#endif
        return 1;
    }

    /**
     * Returns the inventory type of the [Item]
     *
     * @return uint32 inventoryType
     */
    int GetInventoryType(Eluna* E, Item* item)
    {
#if ELUNA_EXPANSION >= EXP_CATA
        E->Push(item->GetTemplate()->GetInventoryType());
#else
        E->Push(item->GetTemplate()->InventoryType);
#endif
        return 1;
    }

    /**
     * Returns the [Player] classes allowed to use this [Item]
     *
     * @return uint32 allowableClass
     */
    int GetAllowableClass(Eluna* E, Item* item)
    {
#if ELUNA_EXPANSION >= EXP_CATA
        E->Push(item->GetTemplate()->GetAllowableClass());
#else
        E->Push(item->GetTemplate()->AllowableClass);
#endif
        return 1;
    }

    /**
     * Returns the [Player] races allowed to use this [Item]
     *
     * @return uint32 allowableRace
     */
    int GetAllowableRace(Eluna* E, Item* item)
    {
#if ELUNA_EXPANSION < EXP_RETAIL
        E->Push(item->GetTemplate()->AllowableRace);
#else
        E->Push(item->GetTemplate()->GetAllowableRace().RawValue);
#endif
        return 1;
    }

    /**
     * Returns the [Item]s level
     *
     * @return uint32 itemLevel
     */
    int GetItemLevel(Eluna* E, Item* item)
    {
#if ELUNA_EXPANSION >= EXP_CATA
        E->Push(item->GetTemplate()->GetBaseItemLevel());
#else
        E->Push(item->GetTemplate()->ItemLevel);
#endif
        return 1;
    }

    /**
     * Returns the minimum level required to use this [Item]
     *
     * @return uint32 requiredLevel
     */
    int GetRequiredLevel(Eluna* E, Item* item)
    {
#if ELUNA_EXPANSION == EXP_CATA
        E->Push(item->GetTemplate()->GetRequiredLevel());
#elif ELUNA_EXPANSION == EXP_RETAIL
        E->Push(item->GetTemplate()->GetBaseRequiredLevel());
#else
        E->Push(item->GetTemplate()->RequiredLevel);
#endif
        return 1;
    }

#if ELUNA_EXPANSION < EXP_RETAIL
    /**
     * Returns the amount of stat values on this [Item]
     *
     * @return uint32 statsCount
     */
    int GetStatsCount(Eluna* E, Item* item)
    {
        E->Push(item->GetTemplate()->StatsCount);
        return 1;
    }
#endif

    /**
     * Returns the stat info of the specified stat slot of this [Item]
     *
     * @param uint8 statSlot : the stat slot specified
     * @return int32 statValue
     * @return int32 statType
     */
    int GetStatInfo(Eluna* E, Item* item)
    {
        uint8 statSlot = E->CHECKVAL<uint8>(2);
        int32 statValue = 0;
        int32 statType = 0;

#if ELUNA_EXPANSION < EXP_RETAIL
        if (statSlot > 0 && statSlot <= item->GetTemplate()->StatsCount)
        {
            auto& statEntry = item->GetTemplate()->ItemStat[statSlot - 1];
            statValue = statEntry.ItemStatValue;
            statType = statEntry.ItemStatType;
        }
#else
        if (statSlot > 0 && statSlot <= MAX_ITEM_PROTO_STATS)
        {
            auto owner = item->GetOwner();
            statValue = item->GetItemStatValue(statSlot, owner);
            statType = item->GetItemStatType(statSlot);
        } 
#endif

        E->Push(statValue);
        E->Push(statType);
        return 2;
    }

    /**
     * Returns the damage info of the specified damage slot of this [Item]
     *
     * @param uint8 damageSlot : the damage slot specified (1 or 2)
     * @return uint32 damageType
     * @return float minDamage
     * @return float maxDamage
     */
    int GetDamageInfo(Eluna* E, Item* item)
    {
        [[maybe_unused]] uint8 damageSlot = E->CHECKVAL<uint8>(2); //Damage slot does not apply in retail
        uint32 damageType = 0;
        float damageMin = 0;
        float damageMax = 0;

#if ELUNA_EXPANSION < EXP_RETAIL
        if (damageSlot > 0 && damageSlot <= MAX_ITEM_PROTO_DAMAGES)
        {
            auto& damageEntry = item->GetTemplate()->Damage[damageSlot - 1];
            damageType = damageEntry.DamageType;
            damageMin = damageEntry.DamageMin;
            damageMax = damageEntry.DamageMax;
        }
#else
        auto owner = item->GetOwner();
        auto itemTemplate = item->GetTemplate();
        damageType = itemTemplate->GetDamageType();
        float dps = itemTemplate->GetDPS(item->GetItemLevel(owner));

        if (dps > 0.0f)
        {
            float avgDamage = dps * itemTemplate->GetDelay() * 0.001f;
            damageMin = (itemTemplate->GetDmgVariance() * -0.5f + 1.0f) * avgDamage;
            damageMax = floor(float(avgDamage * (itemTemplate->GetDmgVariance() * 0.5f + 1.0f) + 0.5f));
        }
#endif
        E->Push(damageType);
        E->Push(damageMin);
        E->Push(damageMax);
        return 3;
    }

    /**
     * Returns the base attack speed of this [Item]
     *
     * @return uint32 speed
     */
    int GetSpeed(Eluna* E, Item* item)
    {
#if ELUNA_EXPANSION < EXP_RETAIL
        E->Push(item->GetTemplate()->Delay);
#else
        E->Push(item->GetTemplate()->GetDelay());
#endif
        return 1;
    }

    /**
     * Returns the base armor of this [Item]
     *
     * @return uint32 armor
     */
    int GetArmor(Eluna* E, Item* item)
    {
#if ELUNA_EXPANSION < EXP_RETAIL
        E->Push(item->GetTemplate()->Armor);
#else
        auto itemLevel = item->GetItemLevel(item->GetOwner());
        E->Push(item->GetTemplate()->GetArmor(itemLevel));
#endif
        return 1;
    }

    /**
     * Returns the max durability of this [Item]
     *
     * @return uint32 maxDurability
     */
    int GetMaxDurability(Eluna* E, Item* item)
    {
#if ELUNA_EXPANSION < EXP_RETAIL
        E->Push(item->GetUInt32Value(ITEM_FIELD_MAXDURABILITY));
#else
        E->Push(item->m_itemData->MaxDurability);
#endif
        return 1;
    }

    /**
     * Returns the current durability of this [Item]
     *
     * @return uint32 durabiliy
     */
    int GetDurability(Eluna* E, Item* item)
    {
#if ELUNA_EXPANSION < EXP_RETAIL
        E->Push(item->GetUInt32Value(ITEM_FIELD_DURABILITY));
#else
        E->Push(item->m_itemData->Durability);
#endif
        return 1;
    }

#if ELUNA_EXPANSION < EXP_RETAIL
    /**
     * Returns the random property ID of this [Item]
     *
     * @return uint32 randomPropertyId
     */
    int GetRandomProperty(Eluna* E, Item* item)
    {
        E->Push(item->GetTemplate()->RandomProperty);
        return 1;
    }

    /**
     * Returns the random suffix ID of this [Item]
     *
     * @return uint32 suffixId
     */
    int GetRandomSuffix(Eluna* E, Item* item)
    {
        E->Push(item->GetTemplate()->RandomSuffix);
        return 1;
    }
#endif

    /**
     * Returns the item set ID of this [Item]
     *
     * @return uint32 itemSetId
     */
    int GetItemSet(Eluna* E, Item* item)
    {
#if ELUNA_EXPANSION >= EXP_CATA
        E->Push(item->GetTemplate()->GetItemSet());
#else
        E->Push(item->GetTemplate()->ItemSet);
#endif
        return 1;
    }

    /**
     * Returns the bag size of this [Item], 0 if [Item] is not a bag
     *
     * @return uint32 bagSize
     */
    int GetBagSize(Eluna* E, Item* item)
    {
        if (Bag* bag = item->ToBag())
            E->Push(bag->GetBagSize());
        else
            E->Push(0);
        return 1;
    }

    /**
     * Sets the [Player] specified as the owner of the [Item]
     *
     * @param [Player] player : the [Player] specified
     */
    int SetOwner(Eluna* E, Item* item)
    {
        Player* player = E->CHECKOBJ<Player>(2);

        item->SetOwnerGUID(player->GET_GUID());
        return 0;
    }

    /**
     * Sets the binding of the [Item] to 'true' or 'false'
     *
     * @param bool setBinding
     */
    int SetBinding(Eluna* E, Item* item)
    {
        bool soulbound = E->CHECKVAL<bool>(2);

        item->SetBinding(soulbound);
        item->SetState(ITEM_CHANGED, item->GetOwner());

        return 0;
    }

    /**
     * Sets the stack count of the [Item]
     *
     * @param uint32 count
     */
    int SetCount(Eluna* E, Item* item)
    {
        uint32 count = E->CHECKVAL<uint32>(2);
        item->SetCount(count);
        return 0;
    }

    /**
     * Sets the specified enchantment of the [Item] to the specified slot
     *
     * @param uint32 enchantId : the ID of the enchant to be applied
     * @param uint32 enchantSlot : the slot for the enchant to be applied to
     * @return bool enchantmentSuccess : if enchantment is successfully set to specified slot, returns 'true', otherwise 'false'
     */
    int SetEnchantment(Eluna* E, Item* item)
    {
        Player* owner = item->GetOwner();
        if (!owner)
        {
            E->Push(false);
            return 1;
        }

        uint32 enchant = E->CHECKVAL<uint32>(2);
        if (!sSpellItemEnchantmentStore.LookupEntry(enchant))
        {
            E->Push(false);
            return 1;
        }

        EnchantmentSlot slot = (EnchantmentSlot)E->CHECKVAL<uint32>(3);
        if (slot >= MAX_INSPECTED_ENCHANTMENT_SLOT)
            return luaL_argerror(E->L, 2, "valid EnchantmentSlot expected");

        owner->ApplyEnchantment(item, slot, false);
        item->SetEnchantment(slot, enchant, 0, 0);
        owner->ApplyEnchantment(item, slot, true);
        E->Push(true);
        return 1;
    }

    /* OTHER */
    /**
     * Removes an enchant from the [Item] by the specified slot
     *
     * @param uint32 enchantSlot : the slot for the enchant to be removed from
     * @return bool enchantmentRemoved : if enchantment is successfully removed from specified slot, returns 'true', otherwise 'false'
     */
    int ClearEnchantment(Eluna* E, Item* item)
    {
        Player* owner = item->GetOwner();
        if (!owner)
        {
            E->Push(false);
            return 1;
        }

        EnchantmentSlot slot = (EnchantmentSlot)E->CHECKVAL<uint32>(2);
        if (slot >= MAX_INSPECTED_ENCHANTMENT_SLOT)
            return luaL_argerror(E->L, 2, "valid EnchantmentSlot expected");

        if (!item->GetEnchantmentId(slot))
        {
            E->Push(false);
            return 1;
        }

        owner->ApplyEnchantment(item, slot, false);
        item->ClearEnchantment(slot);
        E->Push(true);
        return 1;
    }

    /**
     * Saves the [Item] to the database
     */
    int SaveToDB(Eluna* /*E*/, Item* item)
    {
        CharacterDatabaseTransaction trans = CharacterDatabaseTransaction(nullptr);
        item->SaveToDB(trans);
        return 0;
    }
    
    ElunaRegister<Item> ItemMethods[] =
    {
        // Getters
        { "GetOwnerGUID", &LuaItem::GetOwnerGUID },
        { "GetOwner", &LuaItem::GetOwner },
        { "GetCount", &LuaItem::GetCount },
        { "GetMaxStackCount", &LuaItem::GetMaxStackCount },
        { "GetSlot", &LuaItem::GetSlot },
        { "GetBagSlot", &LuaItem::GetBagSlot },
        { "GetEnchantmentId", &LuaItem::GetEnchantmentId },
        { "GetClass", &LuaItem::GetClass },
        { "GetSubClass", &LuaItem::GetSubClass },
        { "GetItemId", &LuaItem::GetItemId },
        { "GetName", &LuaItem::GetName },
        { "GetDisplayId", &LuaItem::GetDisplayId },
        { "GetQuality", &LuaItem::GetQuality },
        { "GetFlags", &LuaItem::GetFlags },
        { "GetFlags2", &LuaItem::GetFlags2 },
        { "GetExtraFlags", &LuaItem::GetExtraFlags },
        { "GetBuyCount", &LuaItem::GetBuyCount },
        { "GetBuyPrice", &LuaItem::GetBuyPrice },
        { "GetSellPrice", &LuaItem::GetSellPrice },
        { "GetInventoryType", &LuaItem::GetInventoryType },
        { "GetAllowableClass", &LuaItem::GetAllowableClass },
        { "GetAllowableRace", &LuaItem::GetAllowableRace },
        { "GetItemLevel", &LuaItem::GetItemLevel },
        { "GetRequiredLevel", &LuaItem::GetRequiredLevel },
        { "GetItemSet", &LuaItem::GetItemSet },
        { "GetBagSize", &LuaItem::GetBagSize },
        { "GetStatInfo", &LuaItem::GetStatInfo },
        { "GetDamageInfo", &LuaItem::GetDamageInfo },
        { "GetSpeed", &LuaItem::GetSpeed },
        { "GetArmor", &LuaItem::GetArmor },
        { "GetMaxDurability", &LuaItem::GetMaxDurability },
        { "GetDurability", &LuaItem::GetDurability },
#if ELUNA_EXPANSION < EXP_RETAIL
        { "GetSpellId", &LuaItem::GetSpellId },
        { "GetSpellTrigger", &LuaItem::GetSpellTrigger },
        { "GetItemLink", &LuaItem::GetItemLink },
        { "GetStatsCount", &LuaItem::GetStatsCount },
        { "GetRandomProperty", &LuaItem::GetRandomProperty },
        { "GetRandomSuffix", &LuaItem::GetRandomSuffix },
#else
        { "GetSpellId", METHOD_REG_NONE },
        { "GetSpellTrigger", METHOD_REG_NONE },
        { "GetItemLink", METHOD_REG_NONE },
        { "GetStatsCount", METHOD_REG_NONE },
        { "GetRandomProperty", METHOD_REG_NONE },
        { "GetRandomSuffix", METHOD_REG_NONE },
#endif

        // Setters
        { "SetOwner", &LuaItem::SetOwner },
        { "SetBinding", &LuaItem::SetBinding },
        { "SetCount", &LuaItem::SetCount },

        // Boolean
        { "IsSoulBound", &LuaItem::IsSoulBound },
        { "IsBoundAccountWide", &LuaItem::IsBoundAccountWide },
        { "IsBoundByEnchant", &LuaItem::IsBoundByEnchant },
        { "IsNotBoundToPlayer", &LuaItem::IsNotBoundToPlayer },
        { "IsLocked", &LuaItem::IsLocked },
        { "IsBag", &LuaItem::IsBag },
        { "IsCurrencyToken", &LuaItem::IsCurrencyToken },
        { "IsNotEmptyBag", &LuaItem::IsNotEmptyBag },
        { "IsBroken", &LuaItem::IsBroken },
        { "CanBeTraded", &LuaItem::CanBeTraded },
        { "IsInTrade", &LuaItem::IsInTrade },
        { "IsInBag", &LuaItem::IsInBag },
        { "IsEquipped", &LuaItem::IsEquipped },
        { "HasQuest", &LuaItem::HasQuest },
        { "IsPotion", &LuaItem::IsPotion },
        { "IsRefundExpired", &LuaItem::IsRefundExpired },
        { "IsConjuredConsumable", &LuaItem::IsConjuredConsumable },
        { "SetEnchantment", &LuaItem::SetEnchantment },
        { "ClearEnchantment", &LuaItem::ClearEnchantment },
#if ELUNA_EXPANSION < EXP_RETAIL
        { "IsWeaponVellum", &LuaItem::IsWeaponVellum },
        { "IsArmorVellum", &LuaItem::IsArmorVellum },
#else
        { "IsWeaponVellum", METHOD_REG_NONE },
        { "IsArmorVellum", METHOD_REG_NONE },
#endif

        // Other
        { "SaveToDB", &LuaItem::SaveToDB }
    };
};
#endif
