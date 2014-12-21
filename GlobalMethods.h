/*
* Copyright (C) 2010 - 2014 Eluna Lua Engine <http://emudevs.com/>
* This program is free software licensed under GPL version 3
* Please see the included DOCS/LICENSE.md for more information
*/

#ifndef GLOBALMETHODS_H
#define GLOBALMETHODS_H

namespace LuaGlobalFunctions
{
    /**
     * Returns lua engine name. Currently `ElunaEngine`
     *
     * @return string engineName
     */
    int GetLuaEngine(Eluna* /*E*/, lua_State* L)
    {
        Eluna::Push(L, "ElunaEngine");
        return 1;
    }

    /**
     * Returns emulator / core name.
     * For example `MaNGOS`, `cMaNGOS` or `TrinityCore`
     *
     * @return string coreName
     */
    int GetCoreName(Eluna* /*E*/, lua_State* L)
    {
        Eluna::Push(L, CORE_NAME);
        return 1;
    }

    /**
     * Returns emulator version
     *
     * * For TrinityCore returns for example `2014-08-13 17:27:22 +0300`
     * * For cMaNGOS returns for example `12708`
     * * For MaNGOS returns for example `20002`
     *
     * @return string version
     */
    int GetCoreVersion(Eluna* /*E*/, lua_State* L)
    {
        Eluna::Push(L, CORE_VERSION);
        return 1;
    }

    /**
     * Returns emulator expansion. Expansion is 0 for classic, 1 for TBC, 2 for WOTLK and 3 for cataclysm
     *
     * @return int32 version : emulator expansion ID
     */
    int GetCoreExpansion(Eluna* /*E*/, lua_State* L)
    {
#ifdef CLASSIC
        Eluna::Push(L, 0);
#elif defined(TBC)
        Eluna::Push(L, 1);
#elif defined(WOTLK)
        Eluna::Push(L, 2);
#elif defined(CATA)
        Eluna::Push(L, 3);
#endif
        return 1;
    }

    /**
     * Returns [Quest] template
     *
     * @param uint32 questId : [Quest] entry ID
     * @return [Quest] quest
     */
    int GetQuest(Eluna* /*E*/, lua_State* L)
    {
        uint32 questId = Eluna::CHECKVAL<uint32>(L, 1);

        Eluna::Push(L, eObjectMgr->GetQuestTemplate(questId));
        return 1;
    }

    /**
     * Finds and Returns [Player] by guid if found
     *
     * @param uint64 guid : guid of the [Player]
     * @return [Player] player
     */
    int GetPlayerByGUID(Eluna* /*E*/, lua_State* L)
    {
        uint64 guid = Eluna::CHECKVAL<uint64>(L, 1);
        Eluna::Push(L, eObjectAccessor->FindPlayer(ObjectGuid(guid)));
        return 1;
    }

    /**
     * Finds and Returns [Player] by name if found
     *
     * @param string name : name of the [Player]
     * @return [Player] player
     */
    int GetPlayerByName(Eluna* /*E*/, lua_State* L)
    {
        const char* name = Eluna::CHECKVAL<const char*>(L, 1);
        Eluna::Push(L, eObjectAccessor->FindPlayerByName(name));
        return 1;
    }

    /**
     * Returns game time in seconds
     *
     * @return uint32 time
     */
    int GetGameTime(Eluna* /*E*/, lua_State* L)
    {
        Eluna::Push(L, eWorld->GetGameTime());
        return 1;
    }

    /**
     * Returns a table with all the current [Player]s in the world
     *
     * <pre>
     * enum TeamId
     * {
     *     TEAM_ALLIANCE = 0,
     *     TEAM_HORDE = 1,
     *     TEAM_NEUTRAL = 2
     * };
     * </pre>
     *
     * @param [TeamId] team = TEAM_NEUTRAL : optional check team of the [Player], Alliance, Horde or Neutral (All)
     * @param bool onlyGM = false : optional check if GM only
     * @return table worldPlayers
     */
    int GetPlayersInWorld(Eluna* /*E*/, lua_State* L)
    {
        uint32 team = Eluna::CHECKVAL<uint32>(L, 1, TEAM_NEUTRAL);
        bool onlyGM = Eluna::CHECKVAL<bool>(L, 2, false);

        lua_newtable(L);
        int tbl = lua_gettop(L);
        uint32 i = 0;

        SessionMap const& sessions = eWorld->GetAllSessions();
        for (SessionMap::const_iterator it = sessions.begin(); it != sessions.end(); ++it)
        {
            if (Player* player = it->second->GetPlayer())
            {
#ifndef TRINITY
                if ((team == TEAM_NEUTRAL || player->GetTeamId() == team) && (!onlyGM || player->isGameMaster()))
#else
                if ((team == TEAM_NEUTRAL || player->GetTeamId() == team) && (!onlyGM || player->IsGameMaster()))
#endif
                {
                    ++i;
                    Eluna::Push(L, i);
                    Eluna::Push(L, player);
                    lua_settable(L, tbl);
                }
            }
        }

        lua_settop(L, tbl); // push table to top of stack
        return 1;
    }

    /**
     * Returns a table with all the current [Player]s in a map
     *
     * <pre>
     * enum TeamId
     * {
     *     TEAM_ALLIANCE = 0,
     *     TEAM_HORDE = 1,
     *     TEAM_NEUTRAL = 2
     * };
     * </pre>
     *
     * @param uint32 mapId : the [Map] entry ID
     * @param uint32 instanceId : the instance ID to search in the map
     * @param [TeamId] team : optional check team of the [Player], Alliance, Horde or Neutral (All)
     * @return table mapPlayers
     */
    int GetPlayersInMap(Eluna* /*E*/, lua_State* L)
    {
        uint32 mapID = Eluna::CHECKVAL<uint32>(L, 1);
        uint32 instanceID = Eluna::CHECKVAL<uint32>(L, 2, 0);
        uint32 team = Eluna::CHECKVAL<uint32>(L, 3, TEAM_NEUTRAL);

        lua_newtable(L);
        Map* map = eMapMgr->FindMap(mapID, instanceID);
        if (!map)
            return 1;

        int tbl = lua_gettop(L);
        uint32 i = 0;

        Map::PlayerList const& players = map->GetPlayers();
        for (Map::PlayerList::const_iterator itr = players.begin(); itr != players.end(); ++itr)
        {
#ifndef TRINITY
            Player* player = itr->getSource();
#else
            Player* player = itr->GetSource();
#endif
            if (!player)
                continue;
            if (player->GetSession() && (team >= TEAM_NEUTRAL || player->GetTeamId() == team))
            {
                ++i;
                Eluna::Push(L, i);
                Eluna::Push(L, player);
                lua_settable(L, tbl);
            }
        }

        lua_settop(L, tbl);
        return 1;
    }

    /**
     * Returns [Guild] by name
     *
     * @param string name : the name of a guild
     * @return [Guild] guild
     */
    int GetGuildByName(Eluna* /*E*/, lua_State* L)
    {
        const char* name = Eluna::CHECKVAL<const char*>(L, 1);
        Eluna::Push(L, eGuildMgr->GetGuildByName(name));
        return 1;
    }

    /**
     * Returns [Map] by ID
     *
     * @param uint32 mapId : the [Map] ID
     * @param uint32 instanceId : instance ID to search, use 0 if not instance
     * @return [Map] map
     */
    int GetMapById(Eluna* /*E*/, lua_State* L)
    {
        uint32 mapid = Eluna::CHECKVAL<uint32>(L, 1);
        uint32 instance = Eluna::CHECKVAL<uint32>(L, 2);

        Eluna::Push(L, eMapMgr->FindMap(mapid, instance));
        return 1;
    }

    /**
     * Returns [Guild] by the leader's GUID
     *
     * @param uint64 guid : the guid of a [Guild] leader
     * @return [Guild] guild
     */
    int GetGuildByLeaderGUID(Eluna* /*E*/, lua_State* L)
    {
        uint64 guid = Eluna::CHECKVAL<uint64>(L, 1);

        Eluna::Push(L, eGuildMgr->GetGuildByLeader(ObjectGuid(guid)));
        return 1;
    }

    /**
     * Returns the amount of [Player]s in the world
     *
     * @return uint32 count
     */
    int GetPlayerCount(Eluna* /*E*/, lua_State* L)
    {
        Eluna::Push(L, eWorld->GetActiveSessionCount());
        return 1;
    }

    /**
     * Returns a [Player]'s GUID
     * [Player] GUID consist of low GUID and type ID
     * [Player] and [Creature] for example can have the same low GUID but not GUID.
     *
     * @param uint32 lowguid : low GUID of the [Player]
     * @return uint64 guid
     */
    int GetPlayerGUID(Eluna* /*E*/, lua_State* L)
    {
        uint32 lowguid = Eluna::CHECKVAL<uint32>(L, 1);
        Eluna::Push(L, MAKE_NEW_GUID(lowguid, 0, HIGHGUID_PLAYER));
        return 1;
    }

    /**
     * Returns an [Item]'s GUID
     * [Item] GUID consist of low GUID and type ID
     * [Player] and [Item] for example can have the same low GUID but not GUID.
     *
     * @param uint32 lowguid : low GUID of the [Item]
     * @return uint64 guid
     */
    int GetItemGUID(Eluna* /*E*/, lua_State* L)
    {
        uint32 lowguid = Eluna::CHECKVAL<uint32>(L, 1);
        Eluna::Push(L, MAKE_NEW_GUID(lowguid, 0, HIGHGUID_ITEM));
        return 1;
    }

    /**
     * Returns a [GameObject]'s GUID
     * [GameObject] GUID consist of entry ID, low GUID and type ID
     * [Player] and [GameObject] for example can have the same low GUID but not GUID.
     *
     * @param uint32 lowguid : low GUID of the [GameObject]
     * @param uint32 entry : entry ID of the [GameObject]
     * @return uint64 guid
     */
    int GetObjectGUID(Eluna* /*E*/, lua_State* L)
    {
        uint32 lowguid = Eluna::CHECKVAL<uint32>(L, 1);
        uint32 entry = Eluna::CHECKVAL<uint32>(L, 2);
        Eluna::Push(L, MAKE_NEW_GUID(lowguid, entry, HIGHGUID_GAMEOBJECT));
        return 1;
    }

    /**
     * Returns a [Creature]'s GUID.
     * [Creature] GUID consist of entry ID, low GUID and type ID
     * [Player] and [Creature] for example can have the same low GUID but not GUID.
     *
     * @param uint32 lowguid : low GUID of the [Creature]
     * @param uint32 entry : entry ID of the [Creature]
     * @return uint64 guid
     */
    int GetUnitGUID(Eluna* /*E*/, lua_State* L)
    {
        uint32 lowguid = Eluna::CHECKVAL<uint32>(L, 1);
        uint32 entry = Eluna::CHECKVAL<uint32>(L, 2);
        Eluna::Push(L, MAKE_NEW_GUID(lowguid, entry, HIGHGUID_UNIT));
        return 1;
    }

    /**
     * Returns the low GUID from a GUID.
     * Low GUID is an ID to distinct the objects of the same type.
     * [Player] and [Creature] for example can have the same low GUID but not GUID.
     * GUID consist of entry ID, low GUID and type ID
     *
     * @param uint64 guid : GUID of an [Object]
     * @return uint32 lowguid : low GUID of the [Object]
     */
    int GetGUIDLow(Eluna* /*E*/, lua_State* L)
    {
        uint64 guid = Eluna::CHECKVAL<uint64>(L, 1);

        Eluna::Push(L, GUID_LOPART(guid));
        return 1;
    }

    /**
     * Returns an item chat link for given entry
     *
     * <pre>
     * enum LocaleConstant
     * {
     *     LOCALE_enUS = 0,
     *     LOCALE_koKR = 1,
     *     LOCALE_frFR = 2,
     *     LOCALE_deDE = 3,
     *     LOCALE_zhCN = 4,
     *     LOCALE_zhTW = 5,
     *     LOCALE_esES = 6,
     *     LOCALE_esMX = 7,
     *     LOCALE_ruRU = 8
     * };
     * </pre>
     *
     * @param uint32 entry : entry ID of an [Item]
     * @param [LocaleConstant] locale = DEFAULT_LOCALE : locale to return the [Item] name in
     * @return string itemLink
     */
    int GetItemLink(Eluna* /*E*/, lua_State* L)
    {
        uint32 entry = Eluna::CHECKVAL<uint32>(L, 1);
        uint8 locale = Eluna::CHECKVAL<uint8>(L, 2, DEFAULT_LOCALE);
        if (locale >= TOTAL_LOCALES)
            return luaL_argerror(L, 2, "valid LocaleConstant expected");

        const ItemTemplate* temp = eObjectMgr->GetItemTemplate(entry);
        if (!temp)
            return luaL_argerror(L, 1, "valid ItemEntry expected");

        std::string name = temp->Name1;
        if (ItemLocale const* il = eObjectMgr->GetItemLocale(entry))
            ObjectMgr::GetLocaleString(il->Name, locale, name);

        std::ostringstream oss;
        oss << "|c" << std::hex << ItemQualityColors[temp->Quality] << std::dec <<
            "|Hitem:" << entry << ":0:" <<
#ifndef CLASSIC
            "0:0:0:0:" <<
#endif
            "0:0:0:0|h[" << name << "]|h|r";

        Eluna::Push(L, oss.str());
        return 1;
    }

    /**
     * Returns the type ID from a GUID.
     * Type ID is different for each type ([Player], [Creature], [GameObject]...)
     * GUID consist of entry ID, low GUID and type ID
     *
     * @param uint64 guid : GUID of an [Object]
     * @return uint32 typeId : type ID of the [Object]
     */
    int GetGUIDType(Eluna* /*E*/, lua_State* L)
    {
        uint64 guid = Eluna::CHECKVAL<uint64>(L, 1);
        Eluna::Push(L, GUID_HIPART(guid));
        return 1;
    }

    /**
     * Returns the entry ID from a GUID.
     * Entry ID is different for each [Creature] and [GameObject].
     * [Item] GUIDs dont include the entry
     * GUID consist of entry ID, low GUID and type ID
     *
     * @param uint64 guid : GUID of an [Creature] or [GameObject], otherwise returns 0
     * @return uint32 entry : entry ID of the [Creature] or [GameObject]
     */
    int GetGUIDEntry(Eluna* /*E*/, lua_State* L)
    {
        uint64 guid = Eluna::CHECKVAL<uint64>(L, 1);
        Eluna::Push(L, GUID_ENPART(guid));
        return 1;
    }

    /**
     * Returns the area's or zone's name
     *
     * <pre>
     * enum LocaleConstant
     * {
     *     LOCALE_enUS = 0,
     *     LOCALE_koKR = 1,
     *     LOCALE_frFR = 2,
     *     LOCALE_deDE = 3,
     *     LOCALE_zhCN = 4,
     *     LOCALE_zhTW = 5,
     *     LOCALE_esES = 6,
     *     LOCALE_esMX = 7,
     *     LOCALE_ruRU = 8
     * };
     * </pre>
     *
     * @param uint32 areaOrZoneId : area ID or zone ID
     * @param [LocaleConstant] locale = DEFAULT_LOCALE : locale to return the name in
     * @return string areaOrZoneName
     */
    int GetAreaName(Eluna* /*E*/, lua_State* L)
    {
        uint32 areaOrZoneId = Eluna::CHECKVAL<uint32>(L, 1);
        uint8 locale = Eluna::CHECKVAL<uint8>(L, 2, DEFAULT_LOCALE);
        if (locale >= TOTAL_LOCALES)
            return luaL_argerror(L, 2, "valid LocaleConstant expected");

        AreaTableEntry const* areaEntry = GetAreaEntryByAreaID(areaOrZoneId);
        if (!areaEntry)
            return luaL_argerror(L, 1, "valid Area or Zone ID expected");

        Eluna::Push(L, areaEntry->area_name[locale]);
        return 1;
    }

    void RegisterEntryHelper(Eluna* E, lua_State* L, int regtype)
    {
        uint32 entry = Eluna::CHECKVAL<uint32>(L, 1);
        uint32 ev = Eluna::CHECKVAL<uint32>(L, 2);
        luaL_checktype(L, 3, LUA_TFUNCTION);
        uint32 shots = Eluna::CHECKVAL<uint32>(L, 4, 0);

        lua_pushvalue(L, 3);
        int functionRef = luaL_ref(L, LUA_REGISTRYINDEX);
        if (functionRef >= 0)
            E->Register(regtype, entry, ev, functionRef, shots);
        else
            luaL_argerror(L, 3, "unable to make a ref to function");
    }

    void RegisterEventHelper(Eluna* E, lua_State* L, int regtype)
    {
        uint32 ev = Eluna::CHECKVAL<uint32>(L, 1);
        luaL_checktype(L, 2, LUA_TFUNCTION);
        uint32 shots = Eluna::CHECKVAL<uint32>(L, 3, 0);

        lua_pushvalue(L, 2);
        int functionRef = luaL_ref(L, LUA_REGISTRYINDEX);
        if (functionRef >= 0)
            E->Register(regtype, 0, ev, functionRef, shots);
        else
            luaL_argerror(L, 2, "unable to make a ref to function");
    }

    /**
     * Registers a server event
     *
     * <pre>
     * enum ServerEvents
     * {
     *     // Server
     *     SERVER_EVENT_ON_NETWORK_START           =     1,       // Not Implemented
     *     SERVER_EVENT_ON_NETWORK_STOP            =     2,       // Not Implemented
     *     SERVER_EVENT_ON_SOCKET_OPEN             =     3,       // Not Implemented
     *     SERVER_EVENT_ON_SOCKET_CLOSE            =     4,       // Not Implemented
     *     SERVER_EVENT_ON_PACKET_RECEIVE          =     5,       // (event, packet, player) - Player only if accessible. Can return false or a new packet
     *     SERVER_EVENT_ON_PACKET_RECEIVE_UNKNOWN  =     6,       // Not Implemented
     *     SERVER_EVENT_ON_PACKET_SEND             =     7,       // (event, packet, player) - Player only if accessible. Can return false or a new packet
     *
     *     // World
     *     WORLD_EVENT_ON_OPEN_STATE_CHANGE        =     8,        // (event, open) - Needs core support on Mangos
     *     WORLD_EVENT_ON_CONFIG_LOAD              =     9,        // (event, reload)
     *     // UNUSED                               =     10,
     *     WORLD_EVENT_ON_SHUTDOWN_INIT            =     11,       // (event, code, mask)
     *     WORLD_EVENT_ON_SHUTDOWN_CANCEL          =     12,       // (event)
     *     WORLD_EVENT_ON_UPDATE                   =     13,       // (event, diff)
     *     WORLD_EVENT_ON_STARTUP                  =     14,       // (event)
     *     WORLD_EVENT_ON_SHUTDOWN                 =     15,       // (event)
     *
     *     // Eluna
     *     ELUNA_EVENT_ON_LUA_STATE_CLOSE          =     16,       // (event) - triggers just before shutting down eluna (on shutdown and restart)
     *     ELUNA_EVENT_ON_LUA_STATE_OPEN           =     33,       // (event) - triggers after all scripts are loaded
     *
     *     // Map
     *     MAP_EVENT_ON_CREATE                     =     17,       // (event, map)
     *     MAP_EVENT_ON_DESTROY                    =     18,       // (event, map)
     *     MAP_EVENT_ON_GRID_LOAD                  =     19,       // Not Implemented
     *     MAP_EVENT_ON_GRID_UNLOAD                =     20,       // Not Implemented
     *     MAP_EVENT_ON_PLAYER_ENTER               =     21,       // (event, map, player)
     *     MAP_EVENT_ON_PLAYER_LEAVE               =     22,       // (event, map, player)
     *     MAP_EVENT_ON_UPDATE                     =     23,       // (event, map, diff)
     *
     *     // Area trigger
     *     TRIGGER_EVENT_ON_TRIGGER                =     24,       // (event, player, triggerId)
     *
     *     // Weather
     *     WEATHER_EVENT_ON_CHANGE                 =     25,       // (event, weather, state, grade)
     *
     *     // Auction house
     *     AUCTION_EVENT_ON_ADD                    =     26,       // (event, AHObject)
     *     AUCTION_EVENT_ON_REMOVE                 =     27,       // (event, AHObject)
     *     AUCTION_EVENT_ON_SUCCESSFUL             =     28,       // (event, AHObject) // Not Implemented
     *     AUCTION_EVENT_ON_EXPIRE                 =     29,       // (event, AHObject) // Not Implemented
     *
     *     // AddOns
     *     ADDON_EVENT_ON_MESSAGE                  =     30,       // (event, sender, type, prefix, msg, target) - target can be nil/whisper_target/guild/group/channel
     *
     *     WORLD_EVENT_ON_DELETE_CREATURE          =     31,       // (event, creature)
     *     WORLD_EVENT_ON_DELETE_GAMEOBJECT        =     32,       // (event, gameobject)
     *
     *     SERVER_EVENT_COUNT
     * };
     * </pre>
     *
     * @param uint32 event : server event Id, refer to ServerEvents above
     * @param function function : function to register
     * @param uint32 shots = 0 : the number of times the function will be called, 0 means "always call this function"
     */
    int RegisterServerEvent(Eluna* E, lua_State* L)
    {
        RegisterEventHelper(E, L, HookMgr::REGTYPE_SERVER);
        return 0;
    }

    /**
     * Registers a [Player] event
     *
     * <pre>
     * enum PlayerEvents
     * {
     *     PLAYER_EVENT_ON_CHARACTER_CREATE        =     1,        // (event, player)
     *     PLAYER_EVENT_ON_CHARACTER_DELETE        =     2,        // (event, guid)
     *     PLAYER_EVENT_ON_LOGIN                   =     3,        // (event, player)
     *     PLAYER_EVENT_ON_LOGOUT                  =     4,        // (event, player)
     *     PLAYER_EVENT_ON_SPELL_CAST              =     5,        // (event, player, spell, skipCheck)
     *     PLAYER_EVENT_ON_KILL_PLAYER             =     6,        // (event, killer, killed)
     *     PLAYER_EVENT_ON_KILL_CREATURE           =     7,        // (event, killer, killed)
     *     PLAYER_EVENT_ON_KILLED_BY_CREATURE      =     8,        // (event, killer, killed)
     *     PLAYER_EVENT_ON_DUEL_REQUEST            =     9,        // (event, target, challenger)
     *     PLAYER_EVENT_ON_DUEL_START              =     10,       // (event, player1, player2)
     *     PLAYER_EVENT_ON_DUEL_END                =     11,       // (event, winner, loser, type)
     *     PLAYER_EVENT_ON_GIVE_XP                 =     12,       // (event, player, amount, victim) - Can return new XP amount
     *     PLAYER_EVENT_ON_LEVEL_CHANGE            =     13,       // (event, player, oldLevel)
     *     PLAYER_EVENT_ON_MONEY_CHANGE            =     14,       // (event, player, amount)
     *     PLAYER_EVENT_ON_REPUTATION_CHANGE       =     15,       // (event, player, factionId, standing, incremental) - Can return new standing
     *     PLAYER_EVENT_ON_TALENTS_CHANGE          =     16,       // (event, player, points)
     *     PLAYER_EVENT_ON_TALENTS_RESET           =     17,       // (event, player, noCost)
     *     PLAYER_EVENT_ON_CHAT                    =     18,       // (event, player, msg, Type, lang) - Can return false or new msg
     *     PLAYER_EVENT_ON_WHISPER                 =     19,       // (event, player, msg, Type, lang, receiver) - Can return false or new msg
     *     PLAYER_EVENT_ON_GROUP_CHAT              =     20,       // (event, player, msg, Type, lang, group) - Can return false or new msg
     *     PLAYER_EVENT_ON_GUILD_CHAT              =     21,       // (event, player, msg, Type, lang, guild) - Can return false or new msg
     *     PLAYER_EVENT_ON_CHANNEL_CHAT            =     22,       // (event, player, msg, Type, lang, channel) - Can return false or new msg
     *     PLAYER_EVENT_ON_EMOTE                   =     23,       // (event, player, emote) - Not triggered on any known emote
     *     PLAYER_EVENT_ON_TEXT_EMOTE              =     24,       // (event, player, textEmote, emoteNum, guid)
     *     PLAYER_EVENT_ON_SAVE                    =     25,       // (event, player)
     *     PLAYER_EVENT_ON_BIND_TO_INSTANCE        =     26,       // (event, player, difficulty, mapid, permanent)
     *     PLAYER_EVENT_ON_UPDATE_ZONE             =     27,       // (event, player, newZone, newArea)
     *     PLAYER_EVENT_ON_MAP_CHANGE              =     28,       // (event, player)
     *
     *     // Custom
     *     PLAYER_EVENT_ON_EQUIP                   =     29,       // (event, player, item, bag, slot)
     *     PLAYER_EVENT_ON_FIRST_LOGIN             =     30,       // (event, player)
     *     PLAYER_EVENT_ON_CAN_USE_ITEM            =     31,       // (event, player, itemEntry)
     *     PLAYER_EVENT_ON_LOOT_ITEM               =     32,       // (event, player, item, count)
     *     PLAYER_EVENT_ON_ENTER_COMBAT            =     33,       // (event, player, enemy)
     *     PLAYER_EVENT_ON_LEAVE_COMBAT            =     34,       // (event, player)
     *     PLAYER_EVENT_ON_REPOP                   =     35,       // (event, player)
     *     PLAYER_EVENT_ON_RESURRECT               =     36,       // (event, player)
     *     PLAYER_EVENT_ON_LOOT_MONEY              =     37,       // (event, player, amount)
     *     PLAYER_EVENT_ON_QUEST_ABANDON           =     38,       // (event, player, questId)
     *     // UNUSED                               =     39,       // (event, player)
     *     // UNUSED                               =     40,       // (event, player)
     *     // UNUSED                               =     41,       // (event, player)
     *     PLAYER_EVENT_ON_COMMAND                 =     42,       // (event, player, command) - player is nil if command used from console. Can return false
     *
     *     PLAYER_EVENT_COUNT
     * };
     * </pre>
     *
     * @param uint32 event : [Player] event Id, refer to PlayerEvents above
     * @param function function : function to register
     * @param uint32 shots = 0 : the number of times the function will be called, 0 means "always call this function"
     */
    int RegisterPlayerEvent(Eluna* E, lua_State* L)
    {
        RegisterEventHelper(E, L, HookMgr::REGTYPE_PLAYER);
        return 0;
    }

    /**
     * Registers a [Guild] event
     *
     * <pre>
     * enum GuildEvents
     * {
     *     // Guild
     *     GUILD_EVENT_ON_ADD_MEMBER               =     1,       // (event, guild, player, rank)
     *     GUILD_EVENT_ON_REMOVE_MEMBER            =     2,       // (event, guild, isDisbanding)
     *     GUILD_EVENT_ON_MOTD_CHANGE              =     3,       // (event, guild, newMotd)
     *     GUILD_EVENT_ON_INFO_CHANGE              =     4,       // (event, guild, newInfo)
     *     GUILD_EVENT_ON_CREATE                   =     5,       // (event, guild, leader, name)  // Not on TC
     *     GUILD_EVENT_ON_DISBAND                  =     6,       // (event, guild)
     *     GUILD_EVENT_ON_MONEY_WITHDRAW           =     7,       // (event, guild, player, amount, isRepair)
     *     GUILD_EVENT_ON_MONEY_DEPOSIT            =     8,       // (event, guild, player, amount)
     *     GUILD_EVENT_ON_ITEM_MOVE                =     9,       // (event, guild, player, item, isSrcBank, srcContainer, srcSlotId, isDestBank, destContainer, destSlotId)   // TODO
     *     GUILD_EVENT_ON_EVENT                    =     10,      // (event, guild, eventType, plrGUIDLow1, plrGUIDLow2, newRank)  // TODO
     *     GUILD_EVENT_ON_BANK_EVENT               =     11,      // (event, guild, eventType, tabId, playerGUIDLow, itemOrMoney, itemStackCount, destTabId)
     *
     *     GUILD_EVENT_COUNT
     * };
     * </pre>
     *
     * @param uint32 event : [Guild] event Id, refer to GuildEvents above
     * @param function function : function to register
     * @param uint32 shots = 0 : the number of times the function will be called, 0 means "always call this function"
     */
    int RegisterGuildEvent(Eluna* E, lua_State* L)
    {
        RegisterEventHelper(E, L, HookMgr::REGTYPE_GUILD);
        return 0;
    }

    /**
     * Registers a [Group] event
     *
     * <pre>
     * enum GroupEvents
     * {
     *     // Group
     *     GROUP_EVENT_ON_MEMBER_ADD               =     1,       // (event, group, guid)
     *     GROUP_EVENT_ON_MEMBER_INVITE            =     2,       // (event, group, guid)
     *     GROUP_EVENT_ON_MEMBER_REMOVE            =     3,       // (event, group, guid, method, kicker, reason)
     *     GROUP_EVENT_ON_LEADER_CHANGE            =     4,       // (event, group, newLeaderGuid, oldLeaderGuid)
     *     GROUP_EVENT_ON_DISBAND                  =     5,       // (event, group)
     *     GROUP_EVENT_ON_CREATE                   =     6,       // (event, group, leaderGuid, groupType)
     *
     *     GROUP_EVENT_COUNT
     * };
     * </pre>
     *
     * @param uint32 event : [Group] event Id, refer to GroupEvents above
     * @param function function : function to register
     * @param uint32 shots = 0 : the number of times the function will be called, 0 means "always call this function"
     */
    int RegisterGroupEvent(Eluna* E, lua_State* L)
    {
        RegisterEventHelper(E, L, HookMgr::REGTYPE_GROUP);
        return 0;
    }

    /**
     * Registers a [Battleground] event
     *
     * <pre>
     * enum BGEvents
     * {
     *     BG_EVENT_ON_START                               = 1,    // (event, bg, bgId, instanceId) - Needs to be added to TC
     *     BG_EVENT_ON_END                                 = 2,    // (event, bg, bgId, instanceId, winner) - Needs to be added to TC
     *     BG_EVENT_ON_CREATE                              = 3,    // (event, bg, bgId, instanceId) - Needs to be added to TC
     *     BG_EVENT_ON_PRE_DESTROY                         = 4,    // (event, bg, bgId, instanceId) - Needs to be added to TC
     *     BG_EVENT_COUNT
     * };
     * </pre>
     *
     * @param uint32 event : [Battleground] event Id, refer to BGEvents above
     * @param function function : function to register
     * @param uint32 shots = 0 : the number of times the function will be called, 0 means "always call this function"
     */
    int RegisterBGEvent(Eluna* E, lua_State* L)
    {
        RegisterEventHelper(E, L, HookMgr::REGTYPE_BG);
        return 0;
    }

    /**
     * Registers a packet event
     *
     * <pre>
     * enum PacketEvents
     * {
     *     PACKET_EVENT_ON_PACKET_RECEIVE          =     5,
     *     PACKET_EVENT_ON_PACKET_RECEIVE_UNKNOWN  =     6,
     *     PACKET_EVENT_ON_PACKET_SEND             =     7,
     *
     *     PACKET_EVENT_COUNT
     * };
     * </pre>
     *
     * @param uint32 entry : opcode
     * @param uint32 event : packet event Id, refer to PacketEvents above
     * @param function function : function to register
     * @param uint32 shots = 0 : the number of times the function will be called, 0 means "always call this function"
     */
    int RegisterPacketEvent(Eluna* E, lua_State* L)
    {
        RegisterEntryHelper(E, L, HookMgr::REGTYPE_PACKET);
        return 0;
    }

    /**
     * Registers a [Creature] gossip event
     *
     * <pre>
     * enum GossipEvents
     * {
     *     GOSSIP_EVENT_ON_HELLO                           = 1,    // (event, player, object) - Object is the Creature/GameObject/Item. For item gossip can return false to stop spell *casting.
     *     GOSSIP_EVENT_ON_SELECT                          = 2,    // (event, player, object, sender, intid, code, menu_id) - Object is the Creature/GameObject/Item/Player, menu_id is *only for player gossip
     *     GOSSIP_EVENT_COUNT
     * };
     * </pre>
     *
     * @param uint32 menu_id : [Creature] entry Id
     * @param uint32 event : [Creature] gossip event Id, refer to GossipEvents above
     * @param function function : function to register
     * @param uint32 shots = 0 : the number of times the function will be called, 0 means "always call this function"
     */
    int RegisterCreatureGossipEvent(Eluna* E, lua_State* L)
    {
        RegisterEntryHelper(E, L, HookMgr::REGTYPE_CREATURE_GOSSIP);
        return 0;
    }

    /**
     * Registers a [GameObject] gossip event
     *
     * <pre>
     * enum GossipEvents
     * {
     *     GOSSIP_EVENT_ON_HELLO                           = 1,    // (event, player, object) - Object is the Creature/GameObject/Item. For item gossip can return false to stop spell *casting.
     *     GOSSIP_EVENT_ON_SELECT                          = 2,    // (event, player, object, sender, intid, code, menu_id) - Object is the Creature/GameObject/Item/Player, menu_id is *only for player gossip
     *     GOSSIP_EVENT_COUNT
     * };
     * </pre>
     *
     * @param uint32 menu_id : [GameObject] entry Id
     * @param uint32 event : [GameObject] gossip event Id, refer to GossipEvents above
     * @param function function : function to register
     * @param uint32 shots = 0 : the number of times the function will be called, 0 means "always call this function"
     */
    int RegisterGameObjectGossipEvent(Eluna* E, lua_State* L)
    {
        RegisterEntryHelper(E, L, HookMgr::REGTYPE_GAMEOBJECT_GOSSIP);
        return 0;
    }

    /**
     * Registers an [Item] event
     *
     * <pre>
     * enum ItemEvents
     * {
     *     ITEM_EVENT_ON_DUMMY_EFFECT                      = 1,    // (event, caster, spellid, effindex, item)
     *     ITEM_EVENT_ON_USE                               = 2,    // (event, player, item, target) - Can return false to stop the spell casting
     *     ITEM_EVENT_ON_QUEST_ACCEPT                      = 3,    // (event, player, item, quest)
     *     ITEM_EVENT_ON_EXPIRE                            = 4,    // (event, player, itemid)
     *     ITEM_EVENT_ON_REMOVE                            = 5,    // (event, player, item)
     *     ITEM_EVENT_COUNT
     * };
     * </pre>
     *
     * @param uint32 entry : [Item] entry Id
     * @param uint32 event : [Item] event Id, refer to ItemEvents above
     * @param function function : function to register
     * @param uint32 shots = 0 : the number of times the function will be called, 0 means "always call this function"
     */
    int RegisterItemEvent(Eluna* E, lua_State* L)
    {
        RegisterEntryHelper(E, L, HookMgr::REGTYPE_ITEM);
        return 0;
    }

    /**
     * Registers an [Item] gossip event
     *
     * <pre>
     * enum GossipEvents
     * {
     *     GOSSIP_EVENT_ON_HELLO                           = 1,    // (event, player, object) - Object is the Creature/GameObject/Item. For item gossip can return false to stop spell *casting.
     *     GOSSIP_EVENT_ON_SELECT                          = 2,    // (event, player, object, sender, intid, code, menu_id) - Object is the Creature/GameObject/Item/Player, menu_id is *only for player gossip
     *     GOSSIP_EVENT_COUNT
     * };
     * </pre>
     *
     * @param uint32 entry : [Item] entry Id
     * @param uint32 event : [Item] gossip event Id, refer to GossipEvents above
     * @param function function : function to register
     * @param uint32 shots = 0 : the number of times the function will be called, 0 means "always call this function"
     */
    int RegisterItemGossipEvent(Eluna* E, lua_State* L)
    {
        RegisterEntryHelper(E, L, HookMgr::REGTYPE_ITEM_GOSSIP);
        return 0;
    }

    /**
     * Registers a [Player] gossip event
     *
     * <pre>
     * enum GossipEvents
     * {
     *     GOSSIP_EVENT_ON_HELLO                           = 1,    // (event, player, object) - Object is the Creature/GameObject/Item. For item gossip can return false to stop spell *casting.
     *     GOSSIP_EVENT_ON_SELECT                          = 2,    // (event, player, object, sender, intid, code, menu_id) - Object is the Creature/GameObject/Item/Player, menu_id is *only for player gossip
     *     GOSSIP_EVENT_COUNT
     * };
     * </pre>
     *
     * @param uint32 menu_id : [Player] gossip menu Id
     * @param uint32 event : [Player] gossip event Id, refer to GossipEvents above
     * @param function function : function to register
     * @param uint32 shots = 0 : the number of times the function will be called, 0 means "always call this function"
     */
    int RegisterPlayerGossipEvent(Eluna* E, lua_State* L)
    {
        RegisterEntryHelper(E, L, HookMgr::REGTYPE_PLAYER_GOSSIP);
        return 0;
    }

    /**
     * Registers a [Creature] event
     *
     * <pre>
     * enum CreatureEvents
     * {
     *     CREATURE_EVENT_ON_ENTER_COMBAT                    = 1,  // (event, creature, target)
     *     CREATURE_EVENT_ON_LEAVE_COMBAT                    = 2,  // (event, creature)
     *     CREATURE_EVENT_ON_TARGET_DIED                     = 3,  // (event, creature, victim)
     *     CREATURE_EVENT_ON_DIED                            = 4,  // (event, creature, killer)
     *     CREATURE_EVENT_ON_SPAWN                           = 5,  // (event, creature)
     *     CREATURE_EVENT_ON_REACH_WP                        = 6,  // (event, creature, type, id)
     *     CREATURE_EVENT_ON_AIUPDATE                        = 7,  // (event, creature, diff)
     *     CREATURE_EVENT_ON_RECEIVE_EMOTE                   = 8,  // (event, creature, player, emoteid)
     *     CREATURE_EVENT_ON_DAMAGE_TAKEN                    = 9,  // (event, creature, attacker, damage) - Can return new damage
     *     CREATURE_EVENT_ON_PRE_COMBAT                      = 10, // (event, creature, target)
     *     CREATURE_EVENT_ON_ATTACKED_AT                     = 11, // (event, creature, attacker)
     *     CREATURE_EVENT_ON_OWNER_ATTACKED                  = 12, // (event, creature, target)    // Not on mangos
     *     CREATURE_EVENT_ON_OWNER_ATTACKED_AT               = 13, // (event, creature, attacker)  // Not on mangos
     *     CREATURE_EVENT_ON_HIT_BY_SPELL                    = 14, // (event, creature, caster, spellid)
     *     CREATURE_EVENT_ON_SPELL_HIT_TARGET                = 15, // (event, creature, target, spellid)
     *     // UNUSED                                         = 16, // (event, creature)
     *     // UNUSED                                         = 17, // (event, creature)
     *     // UNUSED                                         = 18, // (event, creature)
     *     CREATURE_EVENT_ON_JUST_SUMMONED_CREATURE          = 19, // (event, creature, summon)
     *     CREATURE_EVENT_ON_SUMMONED_CREATURE_DESPAWN       = 20, // (event, creature, summon)
     *     CREATURE_EVENT_ON_SUMMONED_CREATURE_DIED          = 21, // (event, creature, summon, killer)    // Not on mangos
     *     CREATURE_EVENT_ON_SUMMONED                        = 22, // (event, creature, summoner)
     *     CREATURE_EVENT_ON_RESET                           = 23, // (event, creature)
     *     CREATURE_EVENT_ON_REACH_HOME                      = 24, // (event, creature)
     *     // UNUSED                                         = 25, // (event, creature)
     *     CREATURE_EVENT_ON_CORPSE_REMOVED                  = 26, // (event, creature, respawndelay) - Can return new respawndelay
     *     CREATURE_EVENT_ON_MOVE_IN_LOS                     = 27, // (event, creature, unit) - Does not actually check LOS. Just uses the sight range
     *     // UNUSED                                         = 28, // (event, creature)
     *     // UNUSED                                         = 29, // (event, creature)
     *     CREATURE_EVENT_ON_DUMMY_EFFECT                    = 30, // (event, caster, spellid, effindex, creature)
     *     CREATURE_EVENT_ON_QUEST_ACCEPT                    = 31, // (event, player, creature, quest)
     *     // UNUSED                                         = 32, // (event, creature)
     *     // UNUSED                                         = 33, // (event, creature)
     *     CREATURE_EVENT_ON_QUEST_REWARD                    = 34, // (event, player, creature, quest, opt)
     *     CREATURE_EVENT_ON_DIALOG_STATUS                   = 35, // (event, player, creature)
     *     CREATURE_EVENT_ON_ADD                             = 36, // (event, creature)
     *     CREATURE_EVENT_ON_REMOVE                          = 37, // (event, creature)
     *     CREATURE_EVENT_COUNT
     * };
     * </pre>
     *
     * @param uint32 entry : [Creature] entry Id
     * @param uint32 event : [Creature] event Id, refer to CreatureEvents above
     * @param function function : function to register
     * @param uint32 shots = 0 : the number of times the function will be called, 0 means "always call this function"
     */
    int RegisterCreatureEvent(Eluna* E, lua_State* L)
    {
        RegisterEntryHelper(E, L, HookMgr::REGTYPE_CREATURE);
        return 0;
    }

    /**
     * Registers a [GameObject] event
     *
     * <pre>
     * enum GameObjectEvents
     * {
     *     GAMEOBJECT_EVENT_ON_AIUPDATE                    = 1,    // (event, go, diff)
     *     GAMEOBJECT_EVENT_ON_SPAWN                       = 2,    // (event, go)
     *     GAMEOBJECT_EVENT_ON_DUMMY_EFFECT                = 3,    // (event, caster, spellid, effindex, go)
     *     GAMEOBJECT_EVENT_ON_QUEST_ACCEPT                = 4,    // (event, player, go, quest)
     *     GAMEOBJECT_EVENT_ON_QUEST_REWARD                = 5,    // (event, player, go, quest, opt)
     *     GAMEOBJECT_EVENT_ON_DIALOG_STATUS               = 6,    // (event, player, go)
     *     GAMEOBJECT_EVENT_ON_DESTROYED                   = 7,    // (event, go, player)
     *     GAMEOBJECT_EVENT_ON_DAMAGED                     = 8,    // (event, go, player)
     *     GAMEOBJECT_EVENT_ON_LOOT_STATE_CHANGE           = 9,    // (event, go, state)
     *     GAMEOBJECT_EVENT_ON_GO_STATE_CHANGED            = 10,   // (event, go, state)
     *     // UNUSED                                       = 11,   // (event, gameobject)
     *     GAMEOBJECT_EVENT_ON_ADD                         = 12,   // (event, gameobject)
     *     GAMEOBJECT_EVENT_ON_REMOVE                      = 13,   // (event, gameobject)
     *     GAMEOBJECT_EVENT_COUNT
     * };
     * </pre>
     *
     * @param uint32 entry : [GameObject] entry Id
     * @param uint32 event : [GameObject] event Id, refer to GameObjectEvents above
     * @param function function : function to register
     * @param uint32 shots = 0 : the number of times the function will be called, 0 means "always call this function"
     */
    int RegisterGameObjectEvent(Eluna* E, lua_State* L)
    {
        RegisterEntryHelper(E, L, HookMgr::REGTYPE_GAMEOBJECT);
        return 0;
    }

    /**
     * Reloads the Lua Engine
     *
     */
    int ReloadEluna(Eluna* /*E*/, lua_State* /*L*/)
    {
        Eluna::reload = true;
        return 0;
    }

    /**
     * Sends a message to the world
     *
     * @param string message : message to send
     */
    int SendWorldMessage(Eluna* /*E*/, lua_State* L)
    {
        const char* message = Eluna::CHECKVAL<const char*>(L, 1);
        eWorld->SendServerMessage(SERVER_MSG_STRING, message);
        return 0;
    }

    /**
     * Executes an sql to your world database instantly and returns [ElunaQuery]
     *
     * @param string sql : sql to run
     * @return [ElunaQuery] result
     */
    int WorldDBQuery(Eluna* /*E*/, lua_State* L)
    {
        const char* query = Eluna::CHECKVAL<const char*>(L, 1);

#ifdef TRINITY
        ElunaQuery result = WorldDatabase.Query(query);
        if (result)
            Eluna::Push(L, new ElunaQuery(result));
        else
            Eluna::Push(L);
#else
        ElunaQuery* result = WorldDatabase.QueryNamed(query);
        if (result)
            Eluna::Push(L, result);
        else
            Eluna::Push(L);
#endif
        return 1;
    }

    /**
     * Executes an sql to your character database. The SQL is not ran instantly.
     *
     * @param string sql : sql [ElunaQuery] to execute
     */
    int WorldDBExecute(Eluna* /*E*/, lua_State* L)
    {
        const char* query = Eluna::CHECKVAL<const char*>(L, 1);
        WorldDatabase.Execute(query);
        return 0;
    }

    /**
     * Executes an sql to your character database instantly and returns [ElunaQuery]
     *
     * @param string sql : sql to run
     * @return [ElunaQuery] result
     */
    int CharDBQuery(Eluna* /*E*/, lua_State* L)
    {
        const char* query = Eluna::CHECKVAL<const char*>(L, 1);

#ifdef TRINITY
        QueryResult result = CharacterDatabase.Query(query);
        if (result)
            Eluna::Push(L, new QueryResult(result));
        else
            Eluna::Push(L);
#else
        QueryNamedResult* result = CharacterDatabase.QueryNamed(query);
        if (result)
            Eluna::Push(L, result);
        else
            Eluna::Push(L);
#endif
        return 1;
    }

    /**
     * Executes an sql to your character database. The SQL is not ran instantly.
     *
     * @param string sql : sql to run
     */
    int CharDBExecute(Eluna* /*E*/, lua_State* L)
    {
        const char* query = Eluna::CHECKVAL<const char*>(L, 1);
        CharacterDatabase.Execute(query);
        return 0;
    }

    /**
     * Executes an sql to your auth database instantly and returns [ElunaQuery]
     *
     * @param string sql : sql to run
     * @return [ElunaQuery] result
     */
    int AuthDBQuery(Eluna* /*E*/, lua_State* L)
    {
        const char* query = Eluna::CHECKVAL<const char*>(L, 1);

#ifdef TRINITY
        QueryResult result = LoginDatabase.Query(query);
        if (result)
            Eluna::Push(L, new QueryResult(result));
        else
            Eluna::Push(L);
#else
        QueryNamedResult* result = LoginDatabase.QueryNamed(query);
        if (result)
            Eluna::Push(L, result);
        else
            Eluna::Push(L);
#endif
        return 1;
    }

    /**
     * Executes an sql to your auth database. The SQL is not ran instantly.
     *
     * @param string sql : sql to run
     */
    int AuthDBExecute(Eluna* /*E*/, lua_State* L)
    {
        const char* query = Eluna::CHECKVAL<const char*>(L, 1);
        LoginDatabase.Execute(query);
        return 0;
    }

    /**
     * Registers a global timed event
     * When the passed function is called, the parameters `(eventId, delay, repeats)` are passed to it.
     * Repeats will decrease on each call if the event does not repeat indefinitely
     *
     * @param function function : function to trigger when the time has passed
     * @param uint32 delay : set time in milliseconds for the event to trigger
     * @param uint32 repeats : how many times for the event to repeat, 0 is infinite
     * @return int eventId : unique ID for the timed event used to cancel it or nil
     */
    int CreateLuaEvent(Eluna* E, lua_State* L)
    {
        luaL_checktype(L, 1, LUA_TFUNCTION);
        uint32 delay = Eluna::CHECKVAL<uint32>(L, 2);
        uint32 repeats = Eluna::CHECKVAL<uint32>(L, 3);

        lua_pushvalue(L, 1);
        int functionRef = luaL_ref(L, LUA_REGISTRYINDEX);
        if (functionRef != LUA_REFNIL && functionRef != LUA_NOREF)
        {
            E->eventMgr->globalProcessor->AddEvent(functionRef, delay, repeats);
            Eluna::Push(L, functionRef);
        }
        return 1;
    }

    /**
     * Removes a global timed event specified by the event ID
     *
     * @param int eventId : event Id to remove
     * @param bool all_Events = false : remove from all events, not just global
     */
    int RemoveEventById(Eluna* E, lua_State* L)
    {
        int eventId = Eluna::CHECKVAL<int>(L, 1);
        bool all_Events = Eluna::CHECKVAL<bool>(L, 1, false);

        // not thread safe
        if (all_Events)
            E->eventMgr->RemoveEvent(eventId);
        else
            E->eventMgr->globalProcessor->RemoveEvent(eventId);
        return 0;
    }

    /**
     * Removes all global timed events
     *
     * @param bool all_Events = false : remove all events, not just global
     */
    int RemoveEvents(Eluna* E, lua_State* L)
    {
        bool all_Events = Eluna::CHECKVAL<bool>(L, 1, false);

        // not thread safe
        if (all_Events)
            E->eventMgr->RemoveEvents();
        else
            E->eventMgr->globalProcessor->RemoveEvents();
        return 0;
    }

    /**
     * Performs an ingame spawn and returns [Creature] or [GameObject] dependent on spawnType
     *
     * @param int32 spawnType : type of object to spawn, 1 = [Creature], 2 = [GameObject]
     * @param uint32 entry : entry ID of the [Creature] or [GameObject]
     * @param uint32 mapId : map ID to spawn the [Creature] or [GameObject] in
     * @param uint32 instanceId : instance ID to put the [Creature] or [GameObject] in. Non instance is 0
     * @param float x : x coordinate of the [Creature] or [GameObject]
     * @param float y : y coordinate of the [Creature] or [GameObject]
     * @param float z : z coordinate of the [Creature] or [GameObject]
     * @param float o : o facing/orientation of the [Creature] or [GameObject]
     * @param bool save = false : optional to save the [Creature] or [GameObject] to the database
     * @param uint32 durorresptime = 0 : despawn time of the [Creature] if it's not saved or respawn time of [GameObject]
     * @param uint32 phase = 1 : phase to put the [Creature] or [GameObject] in
     * @return [WorldObject] worldObject : returns [Creature] or [GameObject]
     */
    int PerformIngameSpawn(Eluna* /*E*/, lua_State* L)
    {
        int spawntype = Eluna::CHECKVAL<int>(L, 1);
        uint32 entry = Eluna::CHECKVAL<uint32>(L, 2);
        uint32 mapID = Eluna::CHECKVAL<uint32>(L, 3);
        uint32 instanceID = Eluna::CHECKVAL<uint32>(L, 4);
        float x = Eluna::CHECKVAL<float>(L, 5);
        float y = Eluna::CHECKVAL<float>(L, 6);
        float z = Eluna::CHECKVAL<float>(L, 7);
        float o = Eluna::CHECKVAL<float>(L, 8);
        bool save = Eluna::CHECKVAL<bool>(L, 9, false);
        uint32 durorresptime = Eluna::CHECKVAL<uint32>(L, 10, 0);
#if (!defined(TBC) && !defined(CLASSIC))
        uint32 phase = Eluna::CHECKVAL<uint32>(L, 11, PHASEMASK_NORMAL);
        if (!phase)
        {
            Eluna::Push(L);
            return 1;
        }
#endif

#ifndef TRINITY
        Map* map = eMapMgr->FindMap(mapID, instanceID);
        if (!map)
        {
            Eluna::Push(L);
            return 1;
        }

        if (spawntype == 1) // spawn creature
        {
            if (save)
            {
                CreatureInfo const* cinfo = ObjectMgr::GetCreatureTemplate(entry);
                if (!cinfo)
                {
                    Eluna::Push(L);
                    return 1;
                }

#if (defined(TBC) || defined(CLASSIC))
                CreatureCreatePos pos(map, x, y, z, o);
#else
                CreatureCreatePos pos(map, x, y, z, o, phase);
#endif
                Creature* pCreature = new Creature;
                // used guids from specially reserved range (can be 0 if no free values)
                uint32 lowguid = eObjectMgr->GenerateStaticCreatureLowGuid();
                if (!lowguid)
                {
                    Eluna::Push(L);
                    return 1;
                }

                if (!pCreature->Create(lowguid, pos, cinfo))
                {
                    delete pCreature;
                    Eluna::Push(L);
                    return 1;
                }

#ifdef TBC
                pCreature->SaveToDB(map->GetId(), (1 << map->GetSpawnMode()));
#elif defined(CLASSIC)
                pCreature->SaveToDB(map->GetId());
#else
                pCreature->SaveToDB(map->GetId(), (1 << map->GetSpawnMode()), phase);
#endif

                uint32 db_guid = pCreature->GetGUIDLow();

                // To call _LoadGoods(); _LoadQuests(); CreateTrainerSpells();
                pCreature->LoadFromDB(db_guid, map);

                map->Add(pCreature);
                eObjectMgr->AddCreatureToGrid(db_guid, eObjectMgr->GetCreatureData(db_guid));
                if (durorresptime)
                    pCreature->ForcedDespawn(durorresptime);

                Eluna::Push(L, pCreature);
            }
            else
            {
                CreatureInfo const* cinfo = ObjectMgr::GetCreatureTemplate(entry);
                if (!cinfo)
                {
                    Eluna::Push(L);
                    return 1;
                }

                TemporarySummon* pCreature = new TemporarySummon(ObjectGuid(uint64(0)));
#if (defined(TBC) || defined(CLASSIC))
                CreatureCreatePos pos(map, x, y, z, o);
#else
                CreatureCreatePos pos(map, x, y, z, o, phase);
#endif

                if (!pCreature->Create(map->GenerateLocalLowGuid(cinfo->GetHighGuid()), pos, cinfo, TEAM_NONE))
                {
                    delete pCreature;
                    {
                        Eluna::Push(L);
                        return 1;
                    }
                }

                pCreature->SetRespawnCoord(pos);

                // Active state set before added to map
                pCreature->SetActiveObjectState(false);

                // Also initializes the AI and MMGen
                pCreature->Summon(durorresptime ? TEMPSUMMON_TIMED_OR_DEAD_DESPAWN : TEMPSUMMON_MANUAL_DESPAWN, durorresptime);

                // Creature Linking, Initial load is handled like respawn
                if (pCreature->IsLinkingEventTrigger())
                    map->GetCreatureLinkingHolder()->DoCreatureLinkingEvent(LINKING_EVENT_RESPAWN, pCreature);

                Eluna::Push(L, pCreature);
            }

            return 1;
        }

        if (spawntype == 2) // Spawn object
        {
            if (save)
            {
                const GameObjectInfo* gInfo = ObjectMgr::GetGameObjectInfo(entry);
                if (!gInfo)
                {
                    Eluna::Push(L);
                    return 1;
                }

                // used guids from specially reserved range (can be 0 if no free values)
                uint32 db_lowGUID = eObjectMgr->GenerateStaticGameObjectLowGuid();
                if (!db_lowGUID)
                {
                    Eluna::Push(L);
                    return 1;
                }

                GameObject* pGameObj = new GameObject;
#if (defined(TBC) || defined(CLASSIC))
                if (!pGameObj->Create(db_lowGUID, gInfo->id, map, x, y, z, o))
#else
                if (!pGameObj->Create(db_lowGUID, gInfo->id, map, phase, x, y, z, o))
#endif
                {
                    delete pGameObj;
                    Eluna::Push(L);
                    return 1;
                }

                if (durorresptime)
                    pGameObj->SetRespawnTime(durorresptime);

                // fill the gameobject data and save to the db
#ifdef TBC
                pGameObj->SaveToDB(map->GetId(), (1 << map->GetSpawnMode()));
#elif defined(CLASSIC)
                pGameObj->SaveToDB(map->GetId());
#else
                pGameObj->SaveToDB(map->GetId(), (1 << map->GetSpawnMode()), phase);
#endif

                // this will generate a new guid if the object is in an instance
                if (!pGameObj->LoadFromDB(db_lowGUID, map))
                {
                    delete pGameObj;
                    Eluna::Push(L);
                    return 1;
                }

                // DEBUG_LOG(GetMangosString(LANG_GAMEOBJECT_CURRENT), gInfo->name, db_lowGUID, x, y, z, o);

                map->Add(pGameObj);

                eObjectMgr->AddGameobjectToGrid(db_lowGUID, eObjectMgr->GetGOData(db_lowGUID));

                Eluna::Push(L, pGameObj);
            }
            else
            {
                GameObject* pGameObj = new GameObject;

#if (defined(TBC) || defined(CLASSIC))
                if (!pGameObj->Create(map->GenerateLocalLowGuid(HIGHGUID_GAMEOBJECT), entry, map, x, y, z, o))
#else
                if (!pGameObj->Create(map->GenerateLocalLowGuid(HIGHGUID_GAMEOBJECT), entry, map, phase, x, y, z, o))
#endif
                {
                    delete pGameObj;
                    Eluna::Push(L);
                    return 1;
                }

                pGameObj->SetRespawnTime(durorresptime / IN_MILLISECONDS);

                map->Add(pGameObj);

                Eluna::Push(L, pGameObj);
            }
            return 1;
        }
#else
        Map* map = eMapMgr->FindMap(mapID, instanceID);
        if (!map)
        {
            Eluna::Push(L);
            return 1;
        }

        Position pos = { x, y, z, o };

        if (spawntype == 1) // spawn creature
        {
            if (save)
            {
                Creature* creature = new Creature();
                if (!creature->Create(eObjectMgr->GenerateLowGuid(HIGHGUID_UNIT), map, phase, entry, x, y, z, o))
                {
                    delete creature;
                    Eluna::Push(L);
                    return 1;
                }

                creature->SaveToDB(map->GetId(), (1 << map->GetSpawnMode()), phase);

                uint32 db_lowguid = creature->GetDBTableGUIDLow();
                if (!creature->LoadCreatureFromDB(db_lowguid, map))
                {
                    delete creature;
                    Eluna::Push(L);
                    return 1;
                }

                eObjectMgr->AddCreatureToGrid(db_lowguid, eObjectMgr->GetCreatureData(db_lowguid));
                Eluna::Push(L, creature);
            }
            else
            {
                TempSummon* creature = map->SummonCreature(entry, pos, NULL, durorresptime);
                if (!creature)
                {
                    Eluna::Push(L);
                    return 1;
                }

                if (durorresptime)
                    creature->SetTempSummonType(TEMPSUMMON_TIMED_OR_DEAD_DESPAWN);
                else
                    creature->SetTempSummonType(TEMPSUMMON_MANUAL_DESPAWN);

                Eluna::Push(L, creature);
            }

            return 1;
        }

        if (spawntype == 2) // Spawn object
        {
            const GameObjectTemplate* objectInfo = eObjectMgr->GetGameObjectTemplate(entry);
            if (!objectInfo)
            {
                Eluna::Push(L);
                return 1;
            }

            if (objectInfo->displayId && !sGameObjectDisplayInfoStore.LookupEntry(objectInfo->displayId))
            {
                Eluna::Push(L);
                return 1;
            }

            GameObject* object = new GameObject;
            uint32 lowguid = eObjectMgr->GenerateLowGuid(HIGHGUID_GAMEOBJECT);

            if (!object->Create(lowguid, objectInfo->entry, map, phase, x, y, z, o, 0.0f, 0.0f, 0.0f, 0.0f, 0, GO_STATE_READY))
            {
                delete object;
                Eluna::Push(L);
                return 1;
            }

            if (durorresptime)
                object->SetRespawnTime(durorresptime);

            if (save)
            {
                // fill the gameobject data and save to the db
                object->SaveToDB(map->GetId(), (1 << map->GetSpawnMode()), phase);

                // this will generate a new lowguid if the object is in an instance
                if (!object->LoadGameObjectFromDB(lowguid, map))
                {
                    delete object;
                    Eluna::Push(L);
                    return 1;
                }

                eObjectMgr->AddGameobjectToGrid(lowguid, eObjectMgr->GetGOData(lowguid));
            }
            else
                map->AddToMap(object);
            Eluna::Push(L, object);
            return 1;
        }
#endif
        Eluna::Push(L);
        return 1;
    }

    /**
     * Creates a [WorldPacket]
     *
     * @param uint32 opcode : opcode to create
     * @param uint32 size : size of opcode
     * @return [WorldPacket] packet
     */
    int CreatePacket(Eluna* /*E*/, lua_State* L)
    {
        uint32 opcode = Eluna::CHECKVAL<uint32>(L, 1);
        uint32 size = Eluna::CHECKVAL<uint32>(L, 2);
        if (opcode >= NUM_MSG_TYPES)
            return luaL_argerror(L, 1, "valid opcode expected");

        Eluna::Push(L, new WorldPacket((OpcodesList)opcode, size));
        return 1;
    }

    /**
     * Adds an [Item] to a vendor
     *
     * @param uint32 entry : [Creature] entry Id
     * @param uint32 item : [Item] entry Id
     * @param int32 maxcount : max [Item] stack count
     * @param uint32 incrtime : combined with maxcount, incrtime tells how often (in seconds) the vendor list is refreshed and the limited [Item] copies are restocked
     * @param uint32 extendedcost : unique cost of an [Item], such as conquest points for example
     */
    int AddVendorItem(Eluna* /*E*/, lua_State* L)
    {
        uint32 entry = Eluna::CHECKVAL<uint32>(L, 1);
        uint32 item = Eluna::CHECKVAL<uint32>(L, 2);
        int maxcount = Eluna::CHECKVAL<int>(L, 3);
        uint32 incrtime = Eluna::CHECKVAL<uint32>(L, 4);
        uint32 extendedcost = Eluna::CHECKVAL<uint32>(L, 5);

#ifndef TRINITY
        if (!eObjectMgr->IsVendorItemValid(false, "npc_vendor", entry, item, maxcount, incrtime, extendedcost, 0))
            return 0;
#ifndef CLASSIC
        eObjectMgr->AddVendorItem(entry, item, maxcount, incrtime, extendedcost);
#else
        eObjectMgr->AddVendorItem(entry, item, maxcount, incrtime);
#endif
#else
#ifdef CATA
        if (!eObjectMgr->IsVendorItemValid(entry, item, maxcount, incrtime, extendedcost, 1))
            return 0;
        eObjectMgr->AddVendorItem(entry, item, maxcount, incrtime, extendedcost, 1);
#else
        if (!eObjectMgr->IsVendorItemValid(entry, item, maxcount, incrtime, extendedcost))
            return 0;
        eObjectMgr->AddVendorItem(entry, item, maxcount, incrtime, extendedcost);
#endif
#endif
        return 0;
    }

    /**
     * Removes an [Item] from a vendor
     *
     * @param uint32 entry : [Creature] entry Id
     * @param uint32 item : [Item] entry Id
     */
    int VendorRemoveItem(Eluna* /*E*/, lua_State* L)
    {
        uint32 entry = Eluna::CHECKVAL<uint32>(L, 1);
        uint32 item = Eluna::CHECKVAL<uint32>(L, 2);
        if (!eObjectMgr->GetCreatureTemplate(entry))
            return luaL_argerror(L, 1, "valid CreatureEntry expected");

#ifdef CATA
        eObjectMgr->RemoveVendorItem(entry, item, 1);
#else
        eObjectMgr->RemoveVendorItem(entry, item);
#endif
        return 0;
    }

    /**
     * Removes all [Item]s from a vendor
     *
     * @param uint32 entry : [Creature] entry Id
     */
    int VendorRemoveAllItems(Eluna* /*E*/, lua_State* L)
    {
        uint32 entry = Eluna::CHECKVAL<uint32>(L, 1);

        VendorItemData const* items = eObjectMgr->GetNpcVendorItemList(entry);
        if (!items || items->Empty())
            return 0;

        VendorItemList const itemlist = items->m_items;
        for (VendorItemList::const_iterator itr = itemlist.begin(); itr != itemlist.end(); ++itr)
#ifdef CATA
            eObjectMgr->RemoveVendorItem(entry, (*itr)->item, 1);
#else
            eObjectMgr->RemoveVendorItem(entry, (*itr)->item);
#endif
        return 0;
    }

    /**
     * Kicks a [Player] from the server
     *
     * @param [Player] player : [Player] to kick
     */
    int Kick(Eluna* /*E*/, lua_State* L)
    {
        Player* player = Eluna::CHECKOBJ<Player>(L, 1);
        player->GetSession()->KickPlayer();
        return 0;
    }

    /**
     * Ban's a [Player]'s account, character or IP
     *
     * <pre>
     * enum BanMode
     * {
     *     BAN_ACCOUNT,
     *     BAN_CHARACTER,
     *     BAN_IP
     * };
     * </pre>
     *
     * @param int32 banMode : method of ban, refer to BanMode above
     * @param string nameOrIP : name of the [Player] or IP of the [Player]
     * @param uint32 duration : duration (in seconds) of the ban
     * @param string reason = "" : ban reason, this is optional
     * @param string whoBanned = "" : the [Player]'s name that banned the account, character or IP, this is optional
     */
    int Ban(Eluna* /*E*/, lua_State* L)
    {
        int banMode = Eluna::CHECKVAL<int>(L, 1);
        std::string nameOrIP = Eluna::CHECKVAL<std::string>(L, 2);
        uint32 duration = Eluna::CHECKVAL<uint32>(L, 3);
        const char* reason = Eluna::CHECKVAL<const char*>(L, 4, "");
        const char* whoBanned = Eluna::CHECKVAL<const char*>(L, 5, "");

        switch (banMode)
        {
            case BAN_ACCOUNT:
#ifdef CATA
                if (!Utf8ToUpperOnlyLatin(nameOrIP))
                    return 0;
#else
                if (!AccountMgr::normalizeString(nameOrIP))
                    return 0;
#endif
                break;
            case BAN_CHARACTER:
                if (!normalizePlayerName(nameOrIP))
                    return 0;
                break;
            case BAN_IP:
                if (!IsIPAddress(nameOrIP.c_str()))
                    return 0;
                break;
            default:
                return 0;
        }

        eWorld->BanAccount((BanMode)banMode, nameOrIP, duration, reason, whoBanned);
        return 0;
    }

    /**
     * Saves all [Player]s
     *
     */
    int SaveAllPlayers(Eluna* /*E*/, lua_State* /*L*/)
    {
        eObjectAccessor->SaveAllPlayers();
        return 0;
    }

    /**
     * Sends mail to a [Player]
     * There can be several item entry-amount pairs at the end of the function. There can be maximum of 12 different items.
     *
     * <pre>
     * enum MailStationery
     * {
     *     MAIL_STATIONERY_TEST = 1,
     *     MAIL_STATIONERY_DEFAULT = 41,
     *     MAIL_STATIONERY_GM = 61,
     *     MAIL_STATIONERY_AUCTION = 62,
     *     MAIL_STATIONERY_VAL = 64, // Valentine
     *     MAIL_STATIONERY_CHR = 65, // Christmas
     *     MAIL_STATIONERY_ORP = 67 // Orphan
     * };
     * </pre>
     *
     * @param string subject : title (subject) of the mail
     * @param string text : contents of the mail
     * @param uint32 receiverGUIDLow : low GUID of the receiver
     * @param uint32 senderGUIDLow = 0 : low GUID of the sender
     * @param uint32 stationary = MAIL_STATIONERY_DEFAULT : type of mail that is being sent as, refer to MailStationery above
     * @param uint32 delay = 0 : mail send delay in milliseconds
     * @param uint32 money = 0 : money to send
     * @param uint32 cod = 0 : cod money amount
     * @param uint32 entry = 0 : entry of an [Item] to send with mail
     * @param uint32 amount = 0 : amount of the [Item] to send with mail
     */
    int SendMail(Eluna* /*E*/, lua_State* L)
    {
        int i = 0;
        std::string subject = Eluna::CHECKVAL<std::string>(L, ++i);
        std::string text = Eluna::CHECKVAL<std::string>(L, ++i);
        uint32 receiverGUIDLow = Eluna::CHECKVAL<uint32>(L, ++i);
        uint32 senderGUIDLow = Eluna::CHECKVAL<uint32>(L, ++i, 0);
        uint32 stationary = Eluna::CHECKVAL<uint32>(L, ++i, MAIL_STATIONERY_DEFAULT);
        uint32 delay = Eluna::CHECKVAL<uint32>(L, ++i, 0);
        uint32 money = Eluna::CHECKVAL<uint32>(L, ++i, 0);
        uint32 cod = Eluna::CHECKVAL<uint32>(L, ++i, 0);
        int argAmount = lua_gettop(L);

        MailSender sender(MAIL_NORMAL, senderGUIDLow, (MailStationery)stationary);
        MailDraft draft(subject, text);

#ifdef TRINITY
        if (cod)
            draft.AddCOD(cod);
        if (money)
            draft.AddMoney(money);
#else
        if (cod)
            draft.SetCOD(cod);
        if (money)
            draft.SetMoney(money);
#endif

#ifdef TRINITY
        SQLTransaction trans = CharacterDatabase.BeginTransaction();
#endif
        uint8 addedItems = 0;
        while (addedItems <= MAX_MAIL_ITEMS && i + 2 <= argAmount)
        {
            uint32 entry = Eluna::CHECKVAL<uint32>(L, ++i);
            uint32 amount = Eluna::CHECKVAL<uint32>(L, ++i);

#ifndef TRINITY
            ItemTemplate const* item_proto = ObjectMgr::GetItemPrototype(entry);
#else
            ItemTemplate const* item_proto = eObjectMgr->GetItemTemplate(entry);
#endif
            if (!item_proto)
            {
                luaL_error(L, "Item entry %d does not exist", entry);
                continue;
            }
            if (amount < 1 || (item_proto->MaxCount > 0 && amount > uint32(item_proto->MaxCount)))
            {
                luaL_error(L, "Item entry %d has invalid amount %d", entry, amount);
                continue;
            }
            if (Item* item = Item::CreateItem(entry, amount))
            {
#ifndef TRINITY
                item->SaveToDB();
#else
                item->SaveToDB(trans);
#endif
                draft.AddItem(item);
                ++addedItems;
            }
        }

#ifndef TRINITY
        draft.SendMailTo(MailReceiver(MAKE_NEW_GUID(receiverGUIDLow, 0, HIGHGUID_PLAYER)), sender);
#else
        draft.SendMailTo(trans, MailReceiver(receiverGUIDLow), sender, MAIL_CHECK_MASK_NONE, delay);
        CharacterDatabase.CommitTransaction(trans);
#endif
        return 0;
    }

    /**
     * Returns the result of bitwise and: a & b
     *
     * @param uint32 a
     * @param uint32 b
     * @return uint32 result
     */
    int bit_and(Eluna* /*E*/, lua_State* L)
    {
        uint32 a = Eluna::CHECKVAL<uint32>(L, 1);
        uint32 b = Eluna::CHECKVAL<uint32>(L, 2);
        Eluna::Push(L, a & b);
        return 1;
    }

    /**
     * Returns the result of bitwise or: a | b
     *
     * @param uint32 a
     * @param uint32 b
     * @return uint32 result
     */
    int bit_or(Eluna* /*E*/, lua_State* L)
    {
        uint32 a = Eluna::CHECKVAL<uint32>(L, 1);
        uint32 b = Eluna::CHECKVAL<uint32>(L, 2);
        Eluna::Push(L, a | b);
        return 1;
    }

    /**
     * Returns the result of bitwise left shift: a << b
     *
     * @param uint32 a
     * @param uint32 b
     * @return uint32 result
     */
    int bit_lshift(Eluna* /*E*/, lua_State* L)
    {
        uint32 a = Eluna::CHECKVAL<uint32>(L, 1);
        uint32 b = Eluna::CHECKVAL<uint32>(L, 2);
        Eluna::Push(L, a << b);
        return 1;
    }

    /**
     * Returns the result of bitwise right shift: a >> b
     *
     * @param uint32 a
     * @param uint32 b
     * @return uint32 result
     */
    int bit_rshift(Eluna* /*E*/, lua_State* L)
    {
        uint32 a = Eluna::CHECKVAL<uint32>(L, 1);
        uint32 b = Eluna::CHECKVAL<uint32>(L, 2);
        Eluna::Push(L, a >> b);
        return 1;
    }

    /**
     * Returns the result of bitwise xor: a ^ b
     *
     * @param uint32 a
     * @param uint32 b
     * @return uint32 result
     */
    int bit_xor(Eluna* /*E*/, lua_State* L)
    {
        uint32 a = Eluna::CHECKVAL<uint32>(L, 1);
        uint32 b = Eluna::CHECKVAL<uint32>(L, 2);
        Eluna::Push(L, a ^ b);
        return 1;
    }

    /**
     * Returns the result of bitwise not: ~a
     *
     * @param uint32 a
     * @return uint32 result
     */
    int bit_not(Eluna* /*E*/, lua_State* L)
    {
        uint32 a = Eluna::CHECKVAL<uint32>(L, 1);
        Eluna::Push(L, ~a);
        return 1;
    }

    /**
     * Adds a taxi path to a specified map, returns the used pathId
     * Related function: [Player:StartTaxi]
     *
     * <pre>
     * -- Execute on startup
     * local pathTable = {{mapid, x, y, z}, {mapid, x, y, z}}
     * local path = AddTaxiPath(pathTable, 28135, 28135)
     * -- Execute when the player should fly
     * player:StartTaxi(path)
     * </pre>
     *
     * @param table waypoints : table containing waypoints: {map, x, y, z[, actionFlag, delay]}
     * @param uint32 mountA : alliance [Creature] entry
     * @param uint32 mountH : horde [Creature] entry
     * @param uint32 price = 0 : price of the taxi path
     * @param uint32 pathId = 0 : path Id of the taxi path
     * @return uint32 actualPathId
     */
    int AddTaxiPath(Eluna* /*E*/, lua_State* L)
    {
        luaL_checktype(L, 1, LUA_TTABLE);
        uint32 mountA = Eluna::CHECKVAL<uint32>(L, 2);
        uint32 mountH = Eluna::CHECKVAL<uint32>(L, 3);
        uint32 price = Eluna::CHECKVAL<uint32>(L, 4, 0);
        uint32 pathId = Eluna::CHECKVAL<uint32>(L, 5, 0);
        lua_pushvalue(L, 1);

        std::list<TaxiPathNodeEntry> nodes;

        int start = lua_gettop(L);
        int end = start;

        Eluna::Push(L);
        while (lua_next(L, -2) != 0)
        {
            luaL_checktype(L, -1, LUA_TTABLE);
            Eluna::Push(L);
            while (lua_next(L, -2) != 0)
            {
                lua_insert(L, end++);
            }
            if (start == end)
                continue;
            if (end - start < 4) // no mandatory args, dont add
            {
                while (end != start)
                    if (!lua_isnone(L, --end))
                        lua_remove(L, end);
                continue;
            }

            while (end - start < 8) // fill optional args with 0
            {
                Eluna::Push(L, 0);
                lua_insert(L, end++);
            }
            TaxiPathNodeEntry* entry = new TaxiPathNodeEntry();
            // mandatory
            entry->mapid = Eluna::CHECKVAL<uint32>(L, start);
            entry->x = Eluna::CHECKVAL<float>(L, start + 1);
            entry->y = Eluna::CHECKVAL<float>(L, start + 2);
            entry->z = Eluna::CHECKVAL<float>(L, start + 3);
            // optional
            entry->actionFlag = Eluna::CHECKVAL<uint32>(L, start + 4, 0);
            entry->delay = Eluna::CHECKVAL<uint32>(L, start + 5, 0);

            nodes.push_back(*entry);

            while (end != start) // remove args
                if (!lua_isnone(L, --end))
                    lua_remove(L, end);

            lua_pop(L, 1);
        }

        if (nodes.size() < 2)
        {
            Eluna::Push(L);
            return 1;
        }
        if (!pathId)
            pathId = sTaxiPathNodesByPath.size();
        if (sTaxiPathNodesByPath.size() <= pathId)
            sTaxiPathNodesByPath.resize(pathId + 1);
        sTaxiPathNodesByPath[pathId].clear();
        sTaxiPathNodesByPath[pathId].resize(nodes.size());
        static uint32 nodeId = 500;
        uint32 startNode = nodeId;
        uint32 index = 0;
        for (std::list<TaxiPathNodeEntry>::const_iterator it = nodes.begin(); it != nodes.end(); ++it)
        {
            TaxiPathNodeEntry entry = *it;
            entry.path = pathId;
            TaxiNodesEntry* nodeEntry = new TaxiNodesEntry();
            nodeEntry->ID = index;
            nodeEntry->map_id = entry.mapid;
            nodeEntry->MountCreatureID[0] = mountH;
            nodeEntry->MountCreatureID[1] = mountA;
            nodeEntry->x = entry.x;
            nodeEntry->y = entry.y;
            nodeEntry->z = entry.z;
            sTaxiNodesStore.SetEntry(nodeId, nodeEntry);
            entry.index = nodeId++;
            sTaxiPathNodesByPath[pathId].set(index++, TaxiPathNodePtr(new TaxiPathNodeEntry(entry)));
        }
        if (startNode >= nodeId)
        {
            Eluna::Push(L);
            return 1;
        }
        sTaxiPathSetBySource[startNode][nodeId - 1] = TaxiPathBySourceAndDestination(pathId, price);
        Eluna::Push(L, pathId);
        return 1;
    }

    /**
     * Adds a [Corpse] to the world
     *
     * @param [Corpse] corpse : [Corpse] to add
     */
    int AddCorpse(Eluna* /*E*/, lua_State* L)
    {
        Corpse* corpse = Eluna::CHECKOBJ<Corpse>(L, 1);

        eObjectAccessor->AddCorpse(corpse);
        return 0;
    }

    /**
     * Removes a [Corpse] from the world
     *
     * @param [Corpse] corpse : [Corpse] to remove
     */
    int RemoveCorpse(Eluna* /*E*/, lua_State* L)
    {
        Corpse* corpse = Eluna::CHECKOBJ<Corpse>(L, 1);
        eObjectAccessor->RemoveCorpse(corpse);
        Eluna::CHECKOBJ<ElunaObject>(L, 1)->Invalidate();
        return 1;
    }

    /**
     * Converts a [Corpse] by guid, also allows for insignia to be looted
     *
     * @param uint64 playerGUID : guid of the [Player]
     * @param bool insignia = false : if true, it allows insignia to be looted
     * @return [Corpse] corpse : returns converted [Corpse]
     */
    int ConvertCorpseForPlayer(Eluna* /*E*/, lua_State* L)
    {
        uint64 guid = Eluna::CHECKVAL<uint64>(L, 1);
        bool insignia = Eluna::CHECKVAL<bool>(L, 2, false);

        Eluna::Push(L, eObjectAccessor->ConvertCorpseForPlayer(ObjectGuid(guid), insignia));
        return 0;
    }

    /**
     * Removes old [Corpse]s from the world
     *
     */
    int RemoveOldCorpses(Eluna* /*E*/, lua_State* /*L*/)
    {
        eObjectAccessor->RemoveOldCorpses();
        return 0;
    }

    /**
     * Finds [Weather] in a zone, also returns [Weather]
     *
     * @param uint32 zoneId : zone Id to check for [Weather]
     * @return [Weather] weather
     */
    int FindWeather(Eluna* /*E*/, lua_State* L)
    {
        uint32 zoneId = Eluna::CHECKVAL<uint32>(L, 1);
#ifndef TRINITY
        Weather* weather = eWorld->FindWeather(zoneId);
#else
        Weather* weather = WeatherMgr::FindWeather(zoneId);
#endif
        Eluna::Push(L, weather);
        return 1;
    }

    /**
     * Adds [Weather] to a zone, also returns [Weather]
     *
     * @param uint32 zoneId : zone Id to add [Weather]
     * @return [Weather] weather
     */
    int AddWeather(Eluna* /*E*/, lua_State* L)
    {
        uint32 zoneId = Eluna::CHECKVAL<uint32>(L, 1);
#ifndef TRINITY
        Weather* weather = eWorld->AddWeather(zoneId);
#else
        Weather* weather = WeatherMgr::AddWeather(zoneId);
#endif
        Eluna::Push(L, weather);
        return 1;
    }

    /**
     * Removes [Weather] from a zone
     *
     * @param uint32 zoneId : zone Id to remove [Weather]
     */
    int RemoveWeather(Eluna* /*E*/, lua_State* L)
    {
        uint32 zoneId = Eluna::CHECKVAL<uint32>(L, 1);
#ifndef TRINITY
        eWorld->RemoveWeather(zoneId);
#else
        WeatherMgr::RemoveWeather(zoneId);
#endif
        return 0;
    }

    /**
     * Sends normal [Weather] to a [Player]
     *
     * @param [Player] player : [Player] to send the normal weather to
     */
    int SendFineWeatherToPlayer(Eluna* /*E*/, lua_State* L)
    {
        Player* player = Eluna::CHECKOBJ<Player>(L, 1);
#ifndef TRINITY
        Weather::SendFineWeatherUpdateToPlayer(player);
#else
        WeatherMgr::SendFineWeatherUpdateToPlayer(player);
#endif
        return 0;
    }

    /**
     * Returns true if the bag and slot is a valid inventory position, otherwise false
     *
     * <pre>
     * Possible and most commonly used combinations:
     *
     * bag = 255
     * slots 0-18 equipment
     * slots 19-22 equipped bag slots
     * slots 23-38 backpack
     * slots 39-66 bank main slots
     * slots 67-74 bank bag slots
     * slots 86-117 keyring
     *
     * bag = 19-22
     * slots 0-35 for equipped bags
     *
     * bag = 67-74
     * slots 0-35 for bank bags
     * </pre>
     *
     * @param uint8 bag : the bag the [Item] is in, you can get this with [Item:GetBagSlot]
     * @param uint8 slot : the slot the [Item] is in within the bag, you can get this with [Item:GetSlot]
     * @return bool isInventoryPos
     */
    int IsInventoryPos(Eluna* /*E*/, lua_State* L)
    {
        uint8 bag = Eluna::CHECKVAL<uint8>(L, 1);
        uint8 slot = Eluna::CHECKVAL<uint8>(L, 2);

        Eluna::Push(L, Player::IsInventoryPos(bag, slot));
        return 1;
    }

    /**
     * Returns true if the bag and slot is a valid equipment position, otherwise false
     *
     * <pre>
     * Possible and most commonly used combinations:
     *
     * bag = 255
     * slots 0-18 equipment
     * slots 19-22 equipped bag slots
     * slots 23-38 backpack
     * slots 39-66 bank main slots
     * slots 67-74 bank bag slots
     * slots 86-117 keyring
     *
     * bag = 19-22
     * slots 0-35 for equipped bags
     *
     * bag = 67-74
     * slots 0-35 for bank bags
     * </pre>
     *
     * @param uint8 bag : the bag the [Item] is in, you can get this with [Item:GetBagSlot]
     * @param uint8 slot : the slot the [Item] is in within the bag, you can get this with [Item:GetSlot]
     * @return bool isEquipmentPosition
     */
    int IsEquipmentPos(Eluna* /*E*/, lua_State* L)
    {
        uint8 bag = Eluna::CHECKVAL<uint8>(L, 1);
        uint8 slot = Eluna::CHECKVAL<uint8>(L, 2);

        Eluna::Push(L, Player::IsEquipmentPos(bag, slot));
        return 1;
    }

    /**
     * Returns true if the bag and slot is a valid bank position, otherwise false
     *
     * <pre>
     * Possible and most commonly used combinations:
     *
     * bag = 255
     * slots 0-18 equipment
     * slots 19-22 equipped bag slots
     * slots 23-38 backpack
     * slots 39-66 bank main slots
     * slots 67-74 bank bag slots
     * slots 86-117 keyring
     *
     * bag = 19-22
     * slots 0-35 for equipped bags
     *
     * bag = 67-74
     * slots 0-35 for bank bags
     * </pre>
     *
     * @param uint8 bag : the bag the [Item] is in, you can get this with [Item:GetBagSlot]
     * @param uint8 slot : the slot the [Item] is in within the bag, you can get this with [Item:GetSlot]
     * @return bool isBankPosition
     */
    int IsBankPos(Eluna* /*E*/, lua_State* L)
    {
        uint8 bag = Eluna::CHECKVAL<uint8>(L, 1);
        uint8 slot = Eluna::CHECKVAL<uint8>(L, 2);

        Eluna::Push(L, Player::IsBankPos(bag, slot));
        return 1;
    }

    /**
     * Returns true if the bag and slot is a valid bag position, otherwise false
     *
     * <pre>
     * Possible and most commonly used combinations:
     *
     * bag = 255
     * slots 0-18 equipment
     * slots 19-22 equipped bag slots
     * slots 23-38 backpack
     * slots 39-66 bank main slots
     * slots 67-74 bank bag slots
     * slots 86-117 keyring
     *
     * bag = 19-22
     * slots 0-35 for equipped bags
     *
     * bag = 67-74
     * slots 0-35 for bank bags
     * </pre>
     *
     * @param uint8 bag : the bag the [Item] is in, you can get this with [Item:GetBagSlot]
     * @param uint8 slot : the slot the [Item] is in within the bag, you can get this with [Item:GetSlot]
     * @return bool isBagPosition
     */
    int IsBagPos(Eluna* /*E*/, lua_State* L)
    {
        uint8 bag = Eluna::CHECKVAL<uint8>(L, 1);
        uint8 slot = Eluna::CHECKVAL<uint8>(L, 2);

        Eluna::Push(L, Player::IsBagPos((bag << 8) + slot));
        return 1;
    }

    /**
     * Returns current time in ms
     *
     * @return uint32 currTime
     */
    int GetCurrTime(Eluna* /*E*/, lua_State* L)
    {
        Eluna::Push(L, ElunaUtil::GetCurrTime());
        return 1;
    }

    /**
     * Returns difference from a [Global:GetCurrTime] time to now
     *
     * @param uint32 oldTime
     * @return uint32 timeDiff
     */
    int GetTimeDiff(Eluna* /*E*/, lua_State* L)
    {
        uint32 oldtimems = Eluna::CHECKVAL<uint32>(L, 1);

        Eluna::Push(L, ElunaUtil::GetTimeDiff(oldtimems));
        return 1;
    }

    std::string GetStackAsString(lua_State* L)
    {
        std::ostringstream oss;
        int top = lua_gettop(L);
        for (int i = 1; i <= top; ++i)
        {
            oss << luaL_tolstring(L, i, NULL);
            lua_pop(L, 1);
        }
        return oss.str();
    }

    /**
     * Prints given parameters to the info log
     *
     * @param ... variableArguments
     */
    int PrintInfo(Eluna* /*E*/, lua_State* L)
    {
        ELUNA_LOG_INFO("%s", GetStackAsString(L).c_str());
        return 0;
    }

    /**
     * Prints given parameters to the error log
     *
     * @param ... variableArguments
     */
    int PrintError(Eluna* /*E*/, lua_State* L)
    {
        ELUNA_LOG_ERROR("%s", GetStackAsString(L).c_str());
        return 0;
    }

    /**
     * Prints given parameters to the debug log
     *
     * @param ... variableArguments
     */
    int PrintDebug(Eluna* /*E*/, lua_State* L)
    {
        ELUNA_LOG_DEBUG("%s", GetStackAsString(L).c_str());
        return 0;
    }

    /**
     * Returns an object represeting long long.
     * The value by default is 0, but can be initialized to a value by passing a number or long long as a string.
     *
     * @proto value = ()
     * @proto value = (number)
     * @proto value = (longlong)
     * @proto value = (longlongstr)
     * @param int32 number : regular lua number
     * @param int64 longlong : a long long object
     * @param string longlongstr : a long long as a string
     * @return int64 value
     */
    int CreateLongLong(Eluna* /*E*/, lua_State* L)
    {
        long long init = 0;
        if (lua_isstring(L, 1))
        {
            std::string str = Eluna::CHECKVAL<std::string>(L, 1);
            if (sscanf(str.c_str(), SI64FMTD, &init) != 1)
                return luaL_argerror(L, 1, "long long (as string) could not be converted");
        }
        else if (!lua_isnoneornil(L, 1))
            init = Eluna::CHECKVAL<long long>(L, 1);

        Eluna::Push(L, init);
        return 1;
    }

    /**
     * Returns an object represeting unsigned long long.
     * The value by default is 0, but can be initialized to a value by passing a number or unsigned long long as a string.
     *
     * @proto value = ()
     * @proto value = (number)
     * @proto value = (ulonglong)
     * @proto value = (ulonglongstr)
     * @param uint32 number : regular lua number
     * @param uint64 ulonglong : an unsigned long long object
     * @param string ulonglongstr : an unsigned long long as a string
     * @return uint64 value
     */
    int CreateULongLong(Eluna* /*E*/, lua_State* L)
    {
        unsigned long long init = 0;
        if (lua_isstring(L, 1))
        {
            std::string str = Eluna::CHECKVAL<std::string>(L, 1);
            if (sscanf(str.c_str(), UI64FMTD, &init) != 1)
                return luaL_argerror(L, 1, "unsigned long long (as string) could not be converted");
        }
        else if (!lua_isnoneornil(L, 1))
            init = Eluna::CHECKVAL<unsigned long long>(L, 1);

        Eluna::Push(L, init);
        return 1;
    }
}
#endif
