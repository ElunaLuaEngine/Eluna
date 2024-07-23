/*
* Copyright (C) 2010 - 2024 Eluna Lua Engine <https://elunaluaengine.github.io/>
* This program is free software licensed under GPL version 3
* Please see the included DOCS/LICENSE.md for more information
*/

#ifndef _ELUNA_INCLUDES_H
#define _ELUNA_INCLUDES_H

// Required
#if !defined CMANGOS
#include "AccountMgr.h"
#include "AuctionHouseMgr.h"
#include "Bag.h"
#include "Cell.h"
#include "CellImpl.h"
#include "Channel.h"
#include "Chat.h"
#include "DBCStores.h"
#include "GameEventMgr.h"
#include "GossipDef.h"
#include "GridNotifiers.h"
#include "GridNotifiersImpl.h"
#include "Group.h"
#include "Guild.h"
#include "GuildMgr.h"
#include "Language.h"
#include "Mail.h"
#include "MapManager.h"
#include "ObjectAccessor.h"
#include "ObjectMgr.h"
#include "Opcodes.h"
#include "Pet.h"
#include "Player.h"
#include "ReputationMgr.h"
#include "ScriptMgr.h"
#include "Spell.h"
#include "SpellAuras.h"
#include "SpellMgr.h"
#include "TemporarySummon.h"
#include "WorldPacket.h"
#include "WorldSession.h"
#if defined TRINITY
#include "Battleground.h"
#include "Config.h"
#include "DatabaseEnv.h"
#include "GitRevision.h"
#include "GroupMgr.h"
#include "MiscPackets.h"
#include "MotionMaster.h"
#include "ScriptedCreature.h"
#include "SpellHistory.h"
#include "SpellInfo.h"
#include "WeatherMgr.h"
#elif defined VMANGOS
#include "BasicAI.h"
#include "SQLStorages.h"
#endif  // TRINITY
#if EXPANSION > CLASSIC
#include "ArenaTeam.h"
#endif
#if EXPANSION >= WOTLK
#include "Vehicle.h"
#endif
#else
#include "Accounts/AccountMgr.h"
#include "AuctionHouse/AuctionHouseMgr.h"
#include "Chat/Channel.h"
#include "Chat/Chat.h"
#include "DBScripts/ScriptMgr.h"
#include "Entities/GossipDef.h"
#include "Entities/Pet.h"
#include "Entities/Player.h"
#include "Entities/TemporarySpawn.h"
#include "GameEvents/GameEventMgr.h"
#include "Globals/ObjectAccessor.h"
#include "Globals/ObjectMgr.h"
#include "Grids/Cell.h"
#include "Grids/CellImpl.h"
#include "Grids/GridNotifiers.h"
#include "Grids/GridNotifiersImpl.h"
#include "Groups/Group.h"
#include "Guilds/Guild.h"
#include "Guilds/GuildMgr.h"
#include "Mails/Mail.h"
#include "Maps/MapManager.h"
#include "Reputation/ReputationMgr.h"
#include "Server/DBCStores.h"
#include "Server/Opcodes.h"
#include "Server/WorldPacket.h"
#include "Server/WorldSession.h"
#include "Spells/Spell.h"
#include "Spells/SpellAuras.h"
#include "Spells/SpellMgr.h"
#include "Tools/Language.h"
#include "AI/BaseAI/UnitAI.h"
#include "Server/SQLStorages.h"
#if EXPANSION > CLASSIC
#include "Arena/ArenaTeam.h"
#endif
#if EXPANSION >= WOTLK
#include "Entities/Vehicle.h"
#endif
#if EXPANSION >= CATA
#include "AI/BaseAI/AggressorAI.h"
#endif
#endif

#if !defined TRINITY
#include "Config/Config.h"
#include "BattleGroundMgr.h"
#include "revision.h"
#endif

#if EXPANSION > CLASSIC
typedef Opcodes OpcodesList;
#endif

/*
 * Note: if you add or change a CORE_NAME or CORE_VERSION #define,
 *   please update LuaGlobalFunctions::GetCoreName or LuaGlobalFunctions::GetCoreVersion documentation example string.
 */
#if defined MANGOS
#define CORE_NAME               "MaNGOS"
#define CORE_VERSION            REVISION_NR
#if EXPANSION == CATA
#define NUM_MSG_TYPES           NUM_OPCODE_HANDLERS
#endif
#endif

#if defined CMANGOS
#define CORE_NAME               "cMaNGOS"
#define CORE_VERSION            REVISION_DATE " " REVISION_ID
#if EXPANSION == CATA
#define NUM_MSG_TYPES           MAX_OPCODE_TABLE_SIZE
#endif
#endif

#if defined VMANGOS
#define CORE_NAME               "vMaNGOS"
#define CORE_VERSION            REVISION_HASH
#define DEFAULT_LOCALE          LOCALE_enUS
#endif

#if defined TRINITY
#define CORE_NAME               "TrinityCore"
#define REGEN_TIME_FULL
#endif

#if defined TRINITY
#define CORE_VERSION            (GitRevision::GetFullVersion())
#define eWorld                  (sWorld)
#define eMapMgr                 (sMapMgr)
#define eGuildMgr               (sGuildMgr)
#define eObjectMgr              (sObjectMgr)
#define eAccountMgr             (sAccountMgr)
#define eAuctionMgr             (sAuctionMgr)
#define eGameEventMgr           (sGameEventMgr)
#define eObjectAccessor()       ObjectAccessor::
#else
#define eWorld                  (&sWorld)
#define eMapMgr                 (&sMapMgr)
#define eConfigMgr              (&sConfig)
#define eGuildMgr               (&sGuildMgr)
#define eObjectMgr              (&sObjectMgr)
#define eAccountMgr             (&sAccountMgr)
#define eAuctionMgr             (&sAuctionMgr)
#define eGameEventMgr           (&sGameEventMgr)
#define eObjectAccessor()       sObjectAccessor.
#define SERVER_MSG_STRING       SERVER_MSG_CUSTOM
#define TOTAL_LOCALES           MAX_LOCALE
#define TARGETICONCOUNT         TARGET_ICON_COUNT
#define MAX_TALENT_SPECS        MAX_TALENT_SPEC_COUNT
#if !defined VMANGOS
#define TEAM_NEUTRAL            TEAM_INDEX_NEUTRAL
#endif


#if EXPANSION >= CATA || defined VMANGOS
#define PLAYER_FIELD_LIFETIME_HONORABLE_KILLS   PLAYER_FIELD_LIFETIME_HONORBALE_KILLS
#endif

#if EXPANSION == TBC
#define SPELL_AURA_MOD_KILL_XP_PCT  SPELL_AURA_MOD_XP_PCT
#endif

#if EXPANSION >= WOTLK
#define UNIT_BYTE2_FLAG_SANCTUARY   UNIT_BYTE2_FLAG_SUPPORTABLE
#endif

#if !defined CMANGOS
typedef TemporarySummon TempSummon;
#else
typedef TemporarySpawn TempSummon;
#endif
typedef SpellEntry SpellInfo;
#endif // TRINITY

#endif // _ELUNA_INCLUDES_H
