/*
* Copyright (C) 2010 - 2014 Eluna Lua Engine <http://emudevs.com/>
* This program is free software licensed under GPL version 3
* Please see the included DOCS/LICENSE.md for more information
*/

#ifndef _LUA_ENGINE_H
#define _LUA_ENGINE_H

#include "Common.h"
#include "SharedDefines.h"
#include "DBCEnums.h"

#include "Group.h"
#include "Item.h"
#ifndef TRINITY
#include "Player.h"
#endif
#include "Weather.h"
#include "World.h"
#include "HookMgr.h"

#ifdef TRINITY
struct ItemTemplate;
#else
struct ItemPrototype;
typedef ItemPrototype ItemTemplate;
typedef SpellEffectIndex SpellEffIndex;
#ifdef CLASSIC
typedef int Difficulty;
#endif
#endif

struct AreaTriggerEntry;
class AuctionHouseObject;
class Channel;
class Corpse;
class Creature;
class CreatureAI;
class GameObject;
#ifdef TRINITY
class GameObjectAI;
#endif
class Guild;
class Group;
class Item;
class Pet;
class Player;
class Quest;
class Spell;
class SpellCastTargets;
#ifdef TRINITY
class TempSummon;
#else
class TemporarySummon;
typedef TemporarySummon TempSummon;
#endif
// class Transport;
class Unit;
class Weather;
class WorldPacket;
#ifndef CLASSIC
#ifndef TBC
#ifdef TRINITY
class Vehicle;
#else
class VehicleInfo;
typedef VehicleInfo Vehicle;
#endif
#endif
#endif

struct lua_State;
class EventMgr;
template<typename T>
class ElunaTemplate;
template<typename T>
class EventBind;
template<typename T>
class EntryBind;

struct LuaScript
{
    std::string fileext;
    std::string filename;
    std::string filepath;
    std::string modulepath;
};

class Eluna
{
private:
    // prevent copy
    Eluna(Eluna const&);
    Eluna& operator=(const Eluna&);

public:
    typedef std::list<LuaScript> ScriptList;

    static Eluna* GEluna;
    static bool reload;

    lua_State* L;
    int userdata_table;

    EventMgr* m_EventMgr;

    EventBind<HookMgr::ServerEvents>*       ServerEventBindings;
    EventBind<HookMgr::PlayerEvents>*       PlayerEventBindings;
    EventBind<HookMgr::GuildEvents>*        GuildEventBindings;
    EventBind<HookMgr::GroupEvents>*        GroupEventBindings;
    EventBind<HookMgr::VehicleEvents>*      VehicleEventBindings;

    EntryBind<HookMgr::PacketEvents>*       PacketEventBindings;
    EntryBind<HookMgr::CreatureEvents>*     CreatureEventBindings;
    EntryBind<HookMgr::GossipEvents>*       CreatureGossipBindings;
    EntryBind<HookMgr::GameObjectEvents>*   GameObjectEventBindings;
    EntryBind<HookMgr::GossipEvents>*       GameObjectGossipBindings;
    EntryBind<HookMgr::ItemEvents>*         ItemEventBindings;
    EntryBind<HookMgr::GossipEvents>*       ItemGossipBindings;
    EntryBind<HookMgr::GossipEvents>*       playerGossipBindings;

    Eluna();
    ~Eluna();

    static ScriptList lua_scripts;
    static ScriptList lua_extensions;
    static std::string lua_folderpath;
    static void Initialize();
    static void Uninitialize();
    // Use Eluna::reload = true; instead.
    // This will be called on next update
    static void ReloadEluna();
    static void GetScripts(std::string path, ScriptList& scripts);
    static void AddScriptPath(std::string filename, std::string fullpath, ScriptList& scripts);

    static void report(lua_State*);
    static void ExecuteCall(lua_State* L, int params, int res);
    void Register(uint8 reg, uint32 id, uint32 evt, int func);
    void RunScripts();
    static void RemoveRef(const void* obj);

    // Pushes
    static void Push(lua_State*); // nil
    static void Push(lua_State*, const uint64);
    static void Push(lua_State*, const int64);
    static void Push(lua_State*, const uint32);
    static void Push(lua_State*, const int32);
    static void Push(lua_State*, const bool);
    static void Push(lua_State*, const float);
    static void Push(lua_State*, const double);
    static void Push(lua_State*, const char*);
    static void Push(lua_State*, const std::string);
    template<typename T> static void Push(lua_State* L, T const* ptr)
    {
        ElunaTemplate<T>::push(L, ptr);
    }
    static void Push(lua_State* L, Object const* obj);
    static void Push(lua_State* L, WorldObject const* obj);
    static void Push(lua_State* L, Unit const* unit);
    static void Push(lua_State* L, Pet const* pet);
    static void Push(lua_State* L, TempSummon const* summon);

    // Checks
    template<typename T> static T CHECKVAL(lua_State* L, int narg);
    template<typename T> static T CHECKVAL(lua_State* L, int narg, T def);
    template<typename T> static T* CHECKOBJ(lua_State* L, int narg, bool error = true)
    {
        return ElunaTemplate<T>::check(L, narg, error);
    }

    CreatureAI* GetAI(Creature* creature);
#ifdef TRINITY
    GameObjectAI* GetAI(GameObject* gameObject);
#endif

    /* Custom */
    bool OnCommand(Player* player, const char* text);
    void OnWorldUpdate(uint32 diff);
    void OnLootItem(Player* pPlayer, Item* pItem, uint32 count, uint64 guid);
    void OnLootMoney(Player* pPlayer, uint32 amount);
    void OnFirstLogin(Player* pPlayer);
    void OnEquip(Player* pPlayer, Item* pItem, uint8 bag, uint8 slot);
    void OnRepop(Player* pPlayer);
    void OnResurrect(Player* pPlayer);
    void OnQuestAbandon(Player* pPlayer, uint32 questId);
    InventoryResult OnCanUseItem(const Player* pPlayer, uint32 itemEntry);
    void OnLuaStateClose();
    bool OnAddonMessage(Player* sender, uint32 type, std::string& msg, Player* receiver, Guild* guild, Group* group, Channel* channel);

    /* Item */
    bool OnDummyEffect(Unit* pCaster, uint32 spellId, SpellEffIndex effIndex, Item* pTarget);
    bool OnQuestAccept(Player* pPlayer, Item* pItem, Quest const* pQuest);
    bool OnUse(Player* pPlayer, Item* pItem, SpellCastTargets const& targets);
    bool OnItemUse(Player* pPlayer, Item* pItem, SpellCastTargets const& targets);
    bool OnItemGossip(Player* pPlayer, Item* pItem, SpellCastTargets const& targets);
    bool OnExpire(Player* pPlayer, ItemTemplate const* pProto);
    bool OnRemove(Player* pPlayer, Item* item);
    void HandleGossipSelectOption(Player* pPlayer, Item* item, uint32 sender, uint32 action, std::string code);

    /* Creature */
    bool OnDummyEffect(Unit* pCaster, uint32 spellId, SpellEffIndex effIndex, Creature* pTarget);
    bool OnGossipHello(Player* pPlayer, Creature* pCreature);
    bool OnGossipSelect(Player* pPlayer, Creature* pCreature, uint32 sender, uint32 action);
    bool OnGossipSelectCode(Player* pPlayer, Creature* pCreature, uint32 sender, uint32 action, const char* code);
    bool OnQuestAccept(Player* pPlayer, Creature* pCreature, Quest const* pQuest);
    bool OnQuestComplete(Player* pPlayer, Creature* pCreature, Quest const* pQuest);
    bool OnQuestReward(Player* pPlayer, Creature* pCreature, Quest const* pQuest);
    uint32 GetDialogStatus(Player* pPlayer, Creature* pCreature);
    void OnSummoned(Creature* creature, Unit* summoner);

    /* GameObject */
    bool OnDummyEffect(Unit* pCaster, uint32 spellId, SpellEffIndex effIndex, GameObject* pTarget);
    bool OnGossipHello(Player* pPlayer, GameObject* pGameObject);
    bool OnGossipSelect(Player* pPlayer, GameObject* pGameObject, uint32 sender, uint32 action);
    bool OnGossipSelectCode(Player* pPlayer, GameObject* pGameObject, uint32 sender, uint32 action, const char* code);
    bool OnQuestAccept(Player* pPlayer, GameObject* pGameObject, Quest const* pQuest);
    bool OnQuestComplete(Player* pPlayer, GameObject* pGameObject, Quest const* pQuest);
    bool OnQuestReward(Player* pPlayer, GameObject* pGameObject, Quest const* pQuest);
    uint32 GetDialogStatus(Player* pPlayer, GameObject* pGameObject);
#ifndef CLASSIC
#ifndef TBC
    void OnDestroyed(GameObject* pGameObject, Player* pPlayer);
    void OnDamaged(GameObject* pGameObject, Player* pPlayer);
#endif
#endif
    void OnLootStateChanged(GameObject* pGameObject, uint32 state);
    void OnGameObjectStateChanged(GameObject* pGameObject, uint32 state);
    void UpdateAI(GameObject* pGameObject, uint32 diff);
    void OnSpawn(GameObject* gameobject);

    /* Packet */
    bool OnPacketSend(WorldSession* session, WorldPacket& packet);
    void OnPacketSendAny(Player* player, WorldPacket& packet, bool& result);
    void OnPacketSendOne(Player* player, WorldPacket& packet, bool& result);
    bool OnPacketReceive(WorldSession* session, WorldPacket& packet);
    void OnPacketReceiveAny(Player* player, WorldPacket& packet, bool& result);
    void OnPacketReceiveOne(Player* player, WorldPacket& packet, bool& result);

    /* Player */
    void OnPlayerEnterCombat(Player* pPlayer, Unit* pEnemy);
    void OnPlayerLeaveCombat(Player* pPlayer);
    void OnPVPKill(Player* pKiller, Player* pKilled);
    void OnCreatureKill(Player* pKiller, Creature* pKilled);
    void OnPlayerKilledByCreature(Creature* pKiller, Player* pKilled);
    void OnLevelChanged(Player* pPlayer, uint8 oldLevel);
    void OnFreeTalentPointsChanged(Player* pPlayer, uint32 newPoints);
    void OnTalentsReset(Player* pPlayer, bool noCost);
    void OnMoneyChanged(Player* pPlayer, int32& amount);
    void OnGiveXP(Player* pPlayer, uint32& amount, Unit* pVictim);
    void OnReputationChange(Player* pPlayer, uint32 factionID, int32& standing, bool incremental);
    void OnDuelRequest(Player* pTarget, Player* pChallenger);
    void OnDuelStart(Player* pStarter, Player* pChallenger);
    void OnDuelEnd(Player* pWinner, Player* pLoser, DuelCompleteType type);
    bool OnChat(Player* pPlayer, uint32 type, uint32 lang, std::string& msg);
    bool OnChat(Player* pPlayer, uint32 type, uint32 lang, std::string& msg, Group* pGroup);
    bool OnChat(Player* pPlayer, uint32 type, uint32 lang, std::string& msg, Guild* pGuild);
    bool OnChat(Player* pPlayer, uint32 type, uint32 lang, std::string& msg, Channel* pChannel);
    bool OnChat(Player* pPlayer, uint32 type, uint32 lang, std::string& msg, Player* pReceiver);
    void OnEmote(Player* pPlayer, uint32 emote);
    void OnTextEmote(Player* pPlayer, uint32 textEmote, uint32 emoteNum, uint64 guid);
    void OnSpellCast(Player* pPlayer, Spell* pSpell, bool skipCheck);
    void OnLogin(Player* pPlayer);
    void OnLogout(Player* pPlayer);
    void OnCreate(Player* pPlayer);
    void OnDelete(uint32 guid);
    void OnSave(Player* pPlayer);
    void OnBindToInstance(Player* pPlayer, Difficulty difficulty, uint32 mapid, bool permanent);
    void OnUpdateZone(Player* pPlayer, uint32 newZone, uint32 newArea);
    void OnMapChanged(Player* pPlayer);
    void HandleGossipSelectOption(Player* pPlayer, uint32 menuId, uint32 sender, uint32 action, std::string code);

#ifndef CLASSIC
#ifndef TBC
    /* Vehicle */
    void OnInstall(Vehicle* vehicle);
    void OnUninstall(Vehicle* vehicle);
    void OnInstallAccessory(Vehicle* vehicle, Creature* accessory);
    void OnAddPassenger(Vehicle* vehicle, Unit* passenger, int8 seatId);
    void OnRemovePassenger(Vehicle* vehicle, Unit* passenger);
#endif
#endif

    /* AreaTrigger */
    bool OnAreaTrigger(Player* pPlayer, AreaTriggerEntry const* pTrigger);

    /* Weather */
    void OnChange(Weather* weather, WeatherState state, float grade);

    /* Auction House */
    void OnAdd(AuctionHouseObject* auctionHouse);
    void OnRemove(AuctionHouseObject* auctionHouse);
    void OnSuccessful(AuctionHouseObject* auctionHouse);
    void OnExpire(AuctionHouseObject* auctionHouse);

    /* Guild */
    void OnAddMember(Guild* guild, Player* player, uint32 plRank);
    void OnRemoveMember(Guild* guild, Player* player, bool isDisbanding);
    void OnMOTDChanged(Guild* guild, const std::string& newMotd);
    void OnInfoChanged(Guild* guild, const std::string& newInfo);
    void OnCreate(Guild* guild, Player* leader, const std::string& name);
    void OnDisband(Guild* guild);
    void OnMemberWitdrawMoney(Guild* guild, Player* player, uint32& amount, bool isRepair);
    void OnMemberDepositMoney(Guild* guild, Player* player, uint32& amount);
    void OnItemMove(Guild* guild, Player* player, Item* pItem, bool isSrcBank, uint8 srcContainer, uint8 srcSlotId, bool isDestBank, uint8 destContainer, uint8 destSlotId);
    void OnEvent(Guild* guild, uint8 eventType, uint32 playerGuid1, uint32 playerGuid2, uint8 newRank);
    void OnBankEvent(Guild* guild, uint8 eventType, uint8 tabId, uint32 playerGuid, uint32 itemOrMoney, uint16 itemStackCount, uint8 destTabId);

    /* Group */
    void OnAddMember(Group* group, uint64 guid);
    void OnInviteMember(Group* group, uint64 guid);
    void OnRemoveMember(Group* group, uint64 guid, uint8 method);
    void OnChangeLeader(Group* group, uint64 newLeaderGuid, uint64 oldLeaderGuid);
    void OnDisband(Group* group);
    void OnCreate(Group* group, uint64 leaderGuid, GroupType groupType);

    /* Map */
    void OnCreate(Map* map);
    void OnDestroy(Map* map);
    void OnPlayerEnter(Map* map, Player* player);
    void OnPlayerLeave(Map* map, Player* player);
    void OnUpdate(Map* map, uint32 diff);
    void OnAddToWorld(Creature* creature);
    void OnRemoveFromWorld(Creature* creature);
    void OnAddToWorld(GameObject* gameobject);
    void OnRemoveFromWorld(GameObject* gameobject);
    void OnRemove(Creature* creature);
    void OnRemove(GameObject* gameobject);

    /* World */
    void OnOpenStateChange(bool open);
    void OnConfigLoad(bool reload);
    void OnShutdownInitiate(ShutdownExitCode code, ShutdownMask mask);
    void OnShutdownCancel();
    void OnUpdate(uint32 diff);
    void OnStartup();
    void OnShutdown();
};
template<> Unit* Eluna::CHECKOBJ<Unit>(lua_State* L, int narg, bool error);
template<> Player* Eluna::CHECKOBJ<Player>(lua_State* L, int narg, bool error);
template<> Creature* Eluna::CHECKOBJ<Creature>(lua_State* L, int narg, bool error);
template<> GameObject* Eluna::CHECKOBJ<GameObject>(lua_State* L, int narg, bool error);
template<> Corpse* Eluna::CHECKOBJ<Corpse>(lua_State* L, int narg, bool error);

#define sEluna Eluna::GEluna

#endif
