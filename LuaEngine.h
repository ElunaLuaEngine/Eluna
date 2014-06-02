/*
* Copyright (C) 2010 - 2014 Eluna Lua Engine <http://emudevs.com/>
* This program is free software licensed under GPL version 3
* Please see the included DOCS/LICENSE.md for more information
*/

#ifndef __ELUNA__H
#define __ELUNA__H

extern "C"
{
#include "lua.h"
#include "lualib.h"
#include "lauxlib.h"
};

// Base
#include "Common.h"
#include "SharedDefines.h"
#include <ace/Singleton.h>
#include <ace/Atomic_Op.h>
// enums & singletons
#ifdef MANGOS
#include "AccountMgr.h"
#include "Config/Config.h"
#include "Player.h"
#else
#include "Config.h"
#include "GameObjectAI.h"
#endif
#include "Group.h"
#include "Item.h"
#include "Weather.h"
#include "World.h"

#ifdef MANGOS
typedef SpellEffectIndex SpellEffIndex;
typedef SpellEntry SpellInfo;
typedef ItemPrototype ItemTemplate;
#define GetTemplate GetProto
#ifdef CLASSIC
typedef int Difficulty;
#endif
#endif

struct AreaTriggerEntry;
#ifdef MANGOS
class ReactorAI;
typedef ReactorAI ScriptedAI;
#else
#undef UNORDERED_MAP
#define UNORDERED_MAP   std::unordered_map
struct ScriptedAI;
#endif
class AuctionHouseObject;
class Channel;
class Creature;
class CreatureAI;
class GameObject;
class Guild;
class Group;
class Item;
class Player;
class Quest;
class Spell;
class SpellCastTargets;
class TemporarySummon;
class Transport;
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

#ifdef MANGOS
#define eWorld                  (&sWorld)
#define eMapMgr                 (&sMapMgr)
#define eConfigMgr              (&sConfig)
#define eGuildMgr               (&sGuildMgr)
#define eObjectMgr              (&sObjectMgr)
#define eAccountMgr             (&sAccountMgr)
#define eObjectAccessor         (&sObjectAccessor)
#define MAKE_NEW_GUID(l, e, h)  ObjectGuid(h, e, l)
#define GET_GUID                GetObjectGuid
#define GetGameObjectTemplate   GetGameObjectInfo
#define GetItemTemplate         GetItemPrototype
#define ELUNA_LOG_INFO(...)     sLog.outString(__VA_ARGS__);
#define ELUNA_LOG_ERROR(...)    sLog.outErrorEluna(__VA_ARGS__);
#define ELUNA_LOG_DEBUG(...)    sLog.outDebug(__VA_ARGS__);
#define CORE_VERSION            REVISION_NR
#define CORE_NAME               "MaNGOS"
#define SERVER_MSG_STRING       SERVER_MSG_CUSTOM
#define MAX_LOCALES             MAX_LOCALE
#define DIALOG_STATUS_SCRIPTED_NO_STATUS    DIALOG_STATUS_UNDEFINED
#define TARGETICONCOUNT         TARGET_ICON_COUNT
typedef TemporarySummon TempSummon;
#ifndef CLASSIC
#define PLAYER_FIELD_LIFETIME_HONORABLE_KILLS   PLAYER_FIELD_LIFETIME_HONORBALE_KILLS
#endif
#define MAX_TALENT_SPECS        MAX_TALENT_SPEC_COUNT
#define GUID_ENPART(guid)       ObjectGuid(guid).GetEntry()
#define GUID_LOPART(guid)       ObjectGuid(guid).GetCounter()
#define GUID_HIPART(guid)       ObjectGuid(guid).GetHigh()
#define ASSERT  MANGOS_ASSERT
enum SelectAggroTarget
{
    SELECT_TARGET_RANDOM = 0,                               // Just selects a random target
    SELECT_TARGET_TOPAGGRO,                                 // Selects targes from top aggro to bottom
    SELECT_TARGET_BOTTOMAGGRO,                              // Selects targets from bottom aggro to top
    SELECT_TARGET_NEAREST,
    SELECT_TARGET_FARTHEST
};
#ifdef TBC
#define SPELL_AURA_MOD_KILL_XP_PCT  SPELL_AURA_MOD_XP_PCT
#endif
#else
#define eWorld                  (sWorld)
#define eMapMgr                 (sMapMgr)
#define eConfigMgr              (sConfigMgr)
#define eGuildMgr               (sGuildMgr)
#define eObjectMgr              (sObjectMgr)
#define eAccountMgr             (sAccountMgr)
#define eObjectAccessor         (sObjectAccessor)
#ifndef CATA
typedef uint64 ObjectGuid;
#endif
#define GET_GUID                GetGUID
#define CORE_VERSION            _DATE
#define CORE_NAME               "TrinityCore"
#define REGEN_TIME_FULL
#define ELUNA_LOG_INFO(...)     TC_LOG_INFO("eluna", __VA_ARGS__);
#define ELUNA_LOG_ERROR(...)    TC_LOG_ERROR("eluna", __VA_ARGS__);
#define ELUNA_LOG_DEBUG(...)    TC_LOG_DEBUG("eluna", __VA_ARGS__);
typedef ThreatContainer::StorageType ThreatList;
#ifdef CATA
#define NUM_MSG_TYPES           NUM_OPCODE_HANDLERS
#endif
#endif
#ifndef CLASSIC
typedef Opcodes                 OpcodesList;
#endif

class Eluna;

template<typename T>
struct ElunaRegister
{
    const char* name;
    int(*mfunc)(lua_State*, T*);
};

struct EventMgr
{
    struct LuaEvent;

    typedef std::set<LuaEvent*> EventSet;
    typedef std::map<EventProcessor*, EventSet> EventMap;
    // typedef UNORDERED_MAP<uint64, EventProcessor> ProcessorMap;
    Eluna& E;

    EventMap LuaEvents; // LuaEvents[processor] = {LuaEvent, LuaEvent...}
    // ProcessorMap Processors; // Processors[guid] = processor
    EventProcessor GlobalEvents;

    struct LuaEvent : public BasicEvent
    {
        LuaEvent(Eluna& _E, EventProcessor* _events, int _funcRef, uint32 _delay, uint32 _calls, Object* _obj);

        ~LuaEvent();

        // Should never execute on dead events
        bool Execute(uint64 time, uint32 diff);

        Eluna& E;
        EventProcessor* events; // Pointer to events (holds the timed event)
        int funcRef;    // Lua function reference ID, also used as event ID
        uint32 delay;   // Delay between event calls
        uint32 calls;   // Amount of calls to make, 0 for infinite
        Object* obj;    // Object to push
    };

    EventMgr(Eluna& _E) : E(_E)
    {
    }

    ~EventMgr()
    {
        RemoveEvents();
    }

    // Should be run on world tick
    void Update(uint32 diff)
    {
        GlobalEvents.Update(diff);
    }

    // Updates processor stored for guid || remove from Update()
    // Should be run on gameobject tick
    /*void Update(uint64 guid, uint32 diff)
    {
    if (Processors.find(guid) == Processors.end())
    return;
    Processors[guid].Update(diff);
    }*/

    // Aborts all lua events
    void KillAllEvents(EventProcessor* events)
    {
        if (!events)
            return;
        if (LuaEvents.empty())
            return;
        EventMap::const_iterator it = LuaEvents.find(events); // Get event set
        if (it == LuaEvents.end())
            return;
        if (it->second.empty())
            return;
        for (EventSet::const_iterator itr = it->second.begin(); itr != it->second.end();) // Loop events
            (*(itr++))->to_Abort = true; // Abort event
    }

    // Remove all timed events
    void RemoveEvents()
    {
        if (!LuaEvents.empty())
            for (EventMap::const_iterator it = LuaEvents.begin(); it != LuaEvents.end();) // loop processors
                KillAllEvents((it++)->first);
        LuaEvents.clear(); // remove pointers
        // This is handled automatically on delete
        // for (ProcessorMap::iterator it = Processors.begin(); it != Processors.end();)
        //    (it++)->second.KillAllEvents(true);
        // Processors.clear(); // remove guid saved processors
        GlobalEvents.KillAllEvents(true);
    }

    // Remove timed events from processor
    void RemoveEvents(EventProcessor* events)
    {
        if (!events)
            return;
        KillAllEvents(events);
        LuaEvents.erase(events); // remove pointer set
    }

    // Remove timed events from guid
    // void RemoveEvents(uint64 guid)
    //{
    //    if (Processors.empty())
    //        return;
    //    if (Processors.find(guid) != Processors.end())
    //        LuaEvents.erase(&Processors[guid]);
    //    // Processors[guid].KillAllEvents(true); // remove events
    //    Processors.erase(guid); // remove processor
    //}

    // Adds a new event to the processor and returns the eventID or 0 (Never negative)
    int AddEvent(EventProcessor* events, int funcRef, uint32 delay, uint32 calls, Object* obj = NULL)
    {
        if (!events || funcRef <= 0) // If funcRef <= 0, function reference failed
            return 0; // on fail always return 0. funcRef can be negative.
        events->AddEvent(new LuaEvent(E, events, funcRef, delay, calls, obj), events->CalculateTime(delay));
        return funcRef; // return the event ID
    }

    // Creates a processor for the guid if needed and adds the event to it
    // int AddEvent(uint64 guid, int funcRef, uint32 delay, uint32 calls, Object* obj = NULL)
    //{
    //    if (!guid) // 0 should be unused
    //        return 0;
    //    return AddEvent(&Processors[guid], funcRef, delay, calls, obj);
    //}

    // Finds the event that has the ID from events
    LuaEvent* GetEvent(EventProcessor* events, int eventId)
    {
        if (!events || !eventId)
            return NULL;
        if (LuaEvents.empty())
            return NULL;
        EventMap::const_iterator it = LuaEvents.find(events); // Get event set
        if (it == LuaEvents.end())
            return NULL;
        if (it->second.empty())
            return NULL;
        for (EventSet::const_iterator itr = it->second.begin(); itr != it->second.end(); ++itr) // Loop events
            if ((*itr) && (*itr)->funcRef == eventId) // Check if the event has our ID
                return *itr; // Return the event if found
        return NULL;
    }

    // Remove the event with the eventId from processor
    // Returns true if event is removed
    bool RemoveEvent(EventProcessor* events, int eventId) // eventId = funcRef
    {
        if (!events || !eventId)
            return false;
        LuaEvent* luaEvent = GetEvent(events, eventId);
        if (!luaEvent)
            return false;
        luaEvent->to_Abort = true; // Set to remove on next call
        LuaEvents[events].erase(luaEvent); // Remove pointer
        return true;
    }

    // Remove event by ID from processor stored for guid
    /*bool RemoveEvent(uint64 guid, int eventId)
    {
    if (Processors.empty())
    return false;
    if (!guid || Processors.find(guid) == Processors.end())
    return false;
    return RemoveEvent(&Processors[guid], eventId);
    }*/

    // Removes the eventId from all events
    void RemoveEvent(int eventId)
    {
        if (!eventId)
            return;
        if (LuaEvents.empty())
            return;
        for (EventMap::const_iterator it = LuaEvents.begin(); it != LuaEvents.end();) // loop processors
            if (RemoveEvent((it++)->first, eventId))
                break; // succesfully remove the event, stop loop.
    }
};

struct EventBind
{
    typedef std::vector<int> ElunaBindingMap;
    typedef std::map<int, ElunaBindingMap> ElunaEntryMap;
    Eluna& E;

    EventBind(Eluna& _E): E(_E)
    {
    }

    ~EventBind()
    {
        Clear();
    }

    void Clear(); // unregisters all registered functions and clears all registered events from the bind std::maps (reset)
    void Insert(int eventId, int funcRef); // Inserts a new registered event

    // Gets the binding std::map containing all registered events with the function refs for the entry
    ElunaBindingMap* GetBindMap(int eventId)
    {
        if (Bindings.empty())
            return NULL;
        ElunaEntryMap::iterator itr = Bindings.find(eventId);
        if (itr == Bindings.end())
            return NULL;

        return &itr->second;
    }

    // Checks if there are events for ID
    bool HasEvents(int eventId) const;

    ElunaEntryMap Bindings; // Binding store Bindings[eventId] = {funcRef};
};

struct EntryBind
{
    typedef std::map<int, int> ElunaBindingMap;
    typedef UNORDERED_MAP<uint32, ElunaBindingMap> ElunaEntryMap;
    Eluna& E;

    EntryBind(Eluna& _E): E(_E)
    {
    }

    ~EntryBind()
    {
        Clear();
    }

    void Clear(); // unregisters all registered functions and clears all registered events from the bind std::maps (reset)
    void Insert(uint32 entryId, int eventId, int funcRef); // Inserts a new registered event

    // Gets the function ref of an entry for an event
    int GetBind(uint32 entryId, int eventId) const
    {
        if (Bindings.empty())
            return 0;
        ElunaEntryMap::const_iterator itr = Bindings.find(entryId);
        if (itr == Bindings.end() || itr->second.empty())
            return 0;
        ElunaBindingMap::const_iterator itr2 = itr->second.find(eventId);
        if (itr2 == itr->second.end())
            return 0;
        return itr2->second;
    }

    // Gets the binding std::map containing all registered events with the function refs for the entry
    const ElunaBindingMap* GetBindMap(uint32 entryId) const
    {
        if (Bindings.empty())
            return NULL;
        ElunaEntryMap::const_iterator itr = Bindings.find(entryId);
        if (itr == Bindings.end())
            return NULL;

        return &itr->second;
    }

    // Returns true if the entry has registered binds
    bool HasBinds(uint32 entryId) const
    {
        if (Bindings.empty())
            return false;
        return Bindings.find(entryId) != Bindings.end();
    }

    ElunaEntryMap Bindings; // Binding store Bindings[entryId][eventId] = funcRef;
};

template<typename T>
class ElunaTemplate;

class Eluna
{
private:
    // prevent copy
    Eluna(Eluna const&);
    Eluna& operator=(const Eluna&);

public:
    typedef std::set<std::string> ScriptPaths;

    static Eluna* GEluna;

    lua_State* L;
    int userdata_table;

    EventMgr* m_EventMgr;

    // Use templates for EventBind
    EventBind* ServerEventBindings;
    EventBind* PlayerEventBindings;
    EventBind* GuildEventBindings;
    EventBind* GroupEventBindings;
    EventBind* VehicleEventBindings;

    EntryBind* PacketEventBindings;
    EntryBind* CreatureEventBindings;
    EntryBind* CreatureGossipBindings;
    EntryBind* GameObjectEventBindings;
    EntryBind* GameObjectGossipBindings;
    EntryBind* ItemEventBindings;
    EntryBind* ItemGossipBindings;
    EntryBind* playerGossipBindings;

    Eluna();
    ~Eluna();

    static ScriptPaths scripts;
    static void Initialize();
    static void Uninitialize();
    static void ReloadEluna();
    void static GetScripts(std::string path, ScriptPaths& scripts);

    static void report(lua_State*);
    static void ExecuteCall(lua_State* L, int params, int res);
    void Register(uint8 reg, uint32 id, uint32 evt, int func);
    void RunScripts(ScriptPaths& scripts);
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

    static inline uint32 GetCurrTime()
    {
#ifdef MANGOS
        return WorldTimer::getMSTime();
#else
        return getMSTime();
#endif
    }

    static inline uint32 GetTimeDiff(uint32 oldMSTime)
    {
#ifdef MANGOS
        return WorldTimer::getMSTimeDiff(oldMSTime, GetCurrTime());
#else
        return GetMSTimeDiffToNow(oldMSTime);
#endif
    }

    struct ObjectGUIDCheck
    {
        ObjectGUIDCheck(ObjectGuid guid): _guid(guid) {}
        bool operator()(WorldObject* object)
        {
            return object->GET_GUID() == _guid;
        }

        ObjectGuid _guid;
    };

    // Binary predicate to sort WorldObjects based on the distance to a reference WorldObject
    struct ObjectDistanceOrderPred
    {
        ObjectDistanceOrderPred(WorldObject const* pRefObj, bool ascending = true): m_refObj(pRefObj), m_ascending(ascending) {}
        bool operator()(WorldObject const* pLeft, WorldObject const* pRight) const
        {
            return m_ascending ? m_refObj->GetDistanceOrder(pLeft, pRight) : !m_refObj->GetDistanceOrder(pLeft, pRight);
        }

        WorldObject const* m_refObj;
        const bool m_ascending;
    };

    // Doesn't get self
    struct WorldObjectInRangeCheck
    {
        WorldObjectInRangeCheck(bool nearest, WorldObject const* obj, float range,
            uint16 typeMask = 0, uint32 entry = 0, uint32 hostile = 0): i_nearest(nearest),
            i_obj(obj), i_range(range), i_typeMask(typeMask), i_entry(entry), i_hostile(hostile)
        {
        }
        WorldObject const& GetFocusObject() const { return *i_obj; }
        bool operator()(WorldObject* u)
        {
            if (i_typeMask && !u->isType(TypeMask(i_typeMask)))
                return false;
            if (i_entry && u->GetEntry() != i_entry)
                return false;
            if (i_obj->GET_GUID() == u->GET_GUID())
                return false;
            if (!i_obj->IsWithinDistInMap(u, i_range))
                return false;
            if (Unit* unit = u->ToUnit())
            {
#ifdef MANGOS
                if (!unit->isAlive())
                    return false;
#else
                if (!unit->IsAlive())
                    return false;
#endif
                if (i_hostile)
                {
                    if (const Unit* obj = i_obj->ToUnit())
                    {
                        if ((i_hostile == 1) != obj->IsHostileTo(unit))
                            return false;
                    }
                }
            }
            if (i_nearest)
                i_range = i_obj->GetDistance(u);
            return true;
        }

        bool i_nearest;
        WorldObject const* i_obj;
        float i_range;
        uint16 i_typeMask;
        uint32 i_entry;
        uint32 i_hostile;

        WorldObjectInRangeCheck(WorldObjectInRangeCheck const&);
    };

    CreatureAI* GetAI(Creature* creature);
#ifndef MANGOS
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

// #define ELUNA_GUARD() ACE_Guard< ACE_Recursive_Thread_Mutex > ELUNA_GUARD_OBJECT(sEluna->lock);

template<typename T>
class ElunaTemplate
{
public:
    static const char* tname;
    static bool manageMemory;

    static int typeT(lua_State* L)
    {
        lua_pushstring(L, tname);
        return 1;
    }

    // name will be used as type name
    // If gc is true, lua will handle the memory management for object pushed
    // gc should be used if pushing for example WorldPacket,
    // that will only be needed on lua side and will not be managed by TC/mangos/<core>
    static void Register(lua_State* L, const char* name, bool gc = false)
    {
        tname = name;
        manageMemory = gc;

        lua_newtable(L);
        int methods = lua_gettop(L);

        // store method table in globals so that
        // scripts can add functions in Lua
        lua_pushvalue(L, methods);
        lua_setglobal(L, tname);

        luaL_newmetatable(L, tname);
        int metatable = lua_gettop(L);

        // hide metatable
        lua_pushvalue(L, methods);
        lua_setfield(L, metatable, "__metatable");

        // required to access methods
        lua_pushvalue(L, methods);
        lua_setfield(L, metatable, "__index");

        // metamethods
        lua_pushcfunction(L, tostringT);
        lua_setfield(L, metatable, "__tostring");

        lua_pushcfunction(L, gcT);
        lua_setfield(L, metatable, "__gc");

        // special method to get the object type
        lua_pushcfunction(L, typeT);
        lua_setfield(L, methods, "GetObjectType");

        lua_setmetatable(L, methods);

        lua_remove(L, methods);
    }

    template<typename C>
    static void SetMethods(lua_State* L, ElunaRegister<C>* methodTable)
    {
        if (!methodTable)
            return;

        luaL_getmetatable(L, tname);
        if (!lua_istable(L, -1))
        {
            lua_remove(L, -1);
            ELUNA_LOG_ERROR("%s missing metatable", tname);
            return;
        }

        lua_getfield(L, -1, "__metatable");
        lua_remove(L, -2);
        if (!lua_istable(L, -1))
        {
            lua_remove(L, -1);
            ELUNA_LOG_ERROR("%s missing method table from metatable", tname);
            return;
        }

        for (; methodTable && methodTable->name && methodTable->mfunc; ++methodTable)
        {
            lua_pushstring(L, methodTable->name);
            lua_pushlightuserdata(L, (void*)methodTable);
            lua_pushcclosure(L, thunk, 1);
            lua_settable(L, -3);
        }

        lua_remove(L, -1);
    }

    // Remember special case ElunaTemplate<Vehicle>::gcT
    static int gcT(lua_State* L)
    {
        if (!manageMemory)
            return 0;

        // Get object pointer (and check type, no error)
        T** ptrHold = static_cast<T**>(luaL_testudata(L, -1, tname));
        if (ptrHold)
            delete *ptrHold;
        return 0;
    }

    static int push(lua_State* L, T const* obj)
    {
        if (!obj)
        {
            lua_pushnil(L);
            return 1;
        }

        if (!manageMemory)
        {
            lua_rawgeti(L, LUA_REGISTRYINDEX, sEluna->userdata_table);
            lua_pushfstring(L, "%p", obj);
            lua_gettable(L, -2);
            if (!lua_isnoneornil(L, -1) && luaL_checkudata(L, -1, tname))
            {
                lua_remove(L, -2);
                return 1;
            }
            lua_remove(L, -1);
            // left userdata_table in stack
        }

        // Create new userdata
        T const** ptrHold = static_cast<T const**>(lua_newuserdata(L, sizeof(T const*)));
        if (!ptrHold)
        {
            ELUNA_LOG_ERROR("%s could not create new userdata", tname);
            lua_pop(L, manageMemory ? 1 : 2);
            lua_pushnil(L);
            return 1;
        }
        *ptrHold = obj;

        // Set metatable for it
        luaL_getmetatable(L, tname);
        if (!lua_istable(L, -1))
        {
            ELUNA_LOG_ERROR("%s missing metatable", tname);
            lua_pop(L, manageMemory ? 2 : 3);
            lua_pushnil(L);
            return 1;
        }
        lua_setmetatable(L, -2);

        if (!manageMemory)
        {
            lua_pushfstring(L, "%p", obj);
            lua_pushvalue(L, -2);
            lua_settable(L, -4);
            lua_remove(L, -2);
        }
        return 1;
    }

    static T* check(lua_State* L, int narg, bool error = true)
    {
        T** ptrHold = static_cast<T**>(error ? luaL_checkudata(L, narg, tname) : lua_touserdata(L, narg));
        if (!ptrHold)
        {
            if (error)
            {
                char buff[256];
                snprintf(buff, 256, "%s expected, got %s", tname, luaL_typename(L, narg));
                luaL_argerror(L, narg, buff);
            }
            return NULL;
        }

        if (!manageMemory)
        {
            // Check pointer validity
            lua_rawgeti(L, LUA_REGISTRYINDEX, sEluna->userdata_table);
            lua_pushfstring(L, "%p", *ptrHold);
            lua_gettable(L, -2);
            lua_remove(L, -2);
            bool valid = lua_isuserdata(L, -1);
            lua_remove(L, -1);
            if (!valid)
            {
                char buff[256];
                snprintf(buff, 256, "%s expected, got pointer to nonexisting object (%s). This should never happen", tname, luaL_typename(L, narg));
                if (error)
                {
                    luaL_argerror(L, narg, buff);
                }
                else
                {
                    ELUNA_LOG_ERROR("%s", buff);
                }
                return NULL;
            }
        }
        return *ptrHold;
    }

    static int thunk(lua_State* L)
    {
        T* obj = Eluna::CHECKOBJ<T>(L, 1); // get self
        if (!obj)
            return 0;
        ElunaRegister<T>* l = static_cast<ElunaRegister<T>*>(lua_touserdata(L, lua_upvalueindex(1)));
        int args = lua_gettop(L);
        int expected = l->mfunc(L, obj);
        args = lua_gettop(L) - args;
        if (args < 0 || args > expected) // Assert instead?
        {
            ELUNA_LOG_ERROR("[Eluna]: %s returned unexpected amount of arguments %i out of %i. Report to devs", l->name, args, expected);
        }
        for (; args < expected; ++args)
            lua_pushnil(L);
        return expected;
    }

    static int tostringT(lua_State* L)
    {
        T* obj = Eluna::CHECKOBJ<T>(L, 1); // get self
        if (obj)
        {
            lua_pushfstring(L, "%s: (%p)", tname, obj);
            return 1;
        }
        lua_pushnil(L);
        lua_replace(L, 1);
        luaL_tolstring(L, 1, NULL);
        return 1;
    }
};

#endif
