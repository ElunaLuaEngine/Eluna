/*
* Copyright (C) 2010 - 2016 Eluna Lua Engine <http://emudevs.com/>
* This program is free software licensed under GPL version 3
* Please see the included DOCS/LICENSE.md for more information
*/

#ifndef _ELUNA_INCLUDES_H
#define _ELUNA_INCLUDES_H

// Required
#ifndef CMANGOS
#include "AccountMgr.h"
#include "AuctionHouseMgr.h"
#include "Cell.h"
#include "CellImpl.h"
#include "Chat.h"
#include "Channel.h"
#include "DBCStores.h"
#if defined CATA && defined TRINITY
#include "DB2Stores.h"
#endif
#include "GameEventMgr.h"
#include "GossipDef.h"
#include "GridNotifiers.h"
#include "GridNotifiersImpl.h"
#include "Group.h"
#include "Guild.h"
#include "GuildMgr.h"
#include "Language.h"
#include "Mail.h"
#include "ObjectAccessor.h"
#include "ObjectMgr.h"
#include "Opcodes.h"
#include "Player.h"
#include "Pet.h"
#include "ReputationMgr.h"
#include "ScriptMgr.h"
#include "Spell.h"
#include "SpellAuras.h"
#include "SpellMgr.h"
#include "TemporarySummon.h"
#include "WorldSession.h"
#include "WorldPacket.h"
#else
#include "Accounts/AccountMgr.h"
#include "AuctionHouse/AuctionHouseMgr.h"
#include "Grids/Cell.h"
#include "Grids/CellImpl.h"
#include "Chat/Chat.h"
#include "Chat/Channel.h"
#include "Server/DBCStores.h"
#include "GameEvents/GameEventMgr.h"
#include "Entities/GossipDef.h"
#include "Grids/GridNotifiers.h"
#include "Grids/GridNotifiersImpl.h"
#include "Groups/Group.h"
#include "Guilds/Guild.h"
#include "Guilds/GuildMgr.h"
#include "Tools/Language.h"
#include "Mails/Mail.h"
#include "Maps/MapManager.h"
#include "Globals/ObjectAccessor.h"
#include "Globals/ObjectMgr.h"
#include "Server/Opcodes.h"
#include "Entities/Player.h"
#include "Entities/Pet.h"
#include "Reputation/ReputationMgr.h"
#include "DBScripts/ScriptMgr.h"
#include "Spells/Spell.h"
#include "Spells/SpellAuras.h"
#include "Spells/SpellMgr.h"
#include "Entities/TemporarySpawn.h"
#include "Server/WorldSession.h"
#include "Server/WorldPacket.h"
#endif

#if defined TRINITY
#include "SpellHistory.h"
#endif

#if defined AZEROTHCORE
#include "MapMgr.h"
#elif !defined CMANGOS
#include "MapManager.h"
#endif

#if defined TRINITY || defined AZEROTHCORE
#include "Config.h"
#include "GameEventMgr.h"
#include "GitRevision.h"
#include "GroupMgr.h"
#include "ScriptedCreature.h"
#include "SpellInfo.h"
#include "WeatherMgr.h"
#include "Battleground.h"
#include "MotionMaster.h"
#include "DatabaseEnv.h"
#include "Bag.h"
#else
#include "Config/Config.h"
#if defined CMANGOS && defined CATA
#include "AI/BaseAI/AggressorAI.h"
#include "Server/SQLStorages.h"
#elif defined CMANGOS
#include "AI/BaseAI/UnitAI.h"
#include "Server/SQLStorages.h"
#else
#include "AggressorAI.h"
#include "SQLStorages.h"
#endif
#include "BattleGroundMgr.h"
#ifndef CMANGOS
#include "SQLStorages.h"
#else
#include "Server/SQLStorages.h"
#endif
#ifdef MANGOS
#include "GitRevision.h"
#else
#include "revision.h"
#endif
#endif

#if (!defined(TBC) && !defined(CLASSIC))
#ifndef CMANGOS
#include "Vehicle.h"
#else
#include "Entities/Vehicle.h"
#endif
#endif

#ifndef CLASSIC
#ifndef CMANGOS
#include "ArenaTeam.h"
#else
#include "Arena/ArenaTeam.h"
#endif
#endif

#if (defined(TRINITY) && defined(CATA))
typedef OpcodeServer            OpcodesList;

#elif !defined CLASSIC
typedef Opcodes                 OpcodesList;
#endif

/*
 * Note: if you add or change a CORE_NAME or CORE_VERSION #define,
 *   please update LuaGlobalFunctions::GetCoreName or LuaGlobalFunctions::GetCoreVersion documentation example string.
 */
#ifdef MANGOS
#define CORE_NAME               "MaNGOS"
#define CORE_VERSION            REVISION_NR
#ifdef CATA
#define NUM_MSG_TYPES           NUM_OPCODE_HANDLERS
#endif
#endif

#ifdef CMANGOS
#define CORE_NAME               "cMaNGOS"
#define CORE_VERSION            REVISION_DATE " " REVISION_ID
#ifdef CATA
#define NUM_MSG_TYPES           MAX_OPCODE_TABLE_SIZE
#endif
#endif

#ifdef TRINITY
#define CORE_NAME               "TrinityCore"
#define REGEN_TIME_FULL
#ifdef CATA
#define NUM_MSG_TYPES           NUM_OPCODE_HANDLERS
#endif
#endif

#ifdef AZEROTHCORE
#define CORE_NAME               "AzerothCore"
#endif

#if defined TRINITY || defined AZEROTHCORE
#define CORE_VERSION            (GitRevision::GetFullVersion())
#define eWorld                  (sWorld)
#define eMapMgr                 (sMapMgr)
#define eConfigMgr              (sConfigMgr)
#define eGuildMgr               (sGuildMgr)
#define eObjectMgr              (sObjectMgr)
#define eAccountMgr             (sAccountMgr)
#define eAuctionMgr             (sAuctionMgr)
#define eGameEventMgr           (sGameEventMgr)
#define eObjectAccessor()       ObjectAccessor::
#endif

#if !defined TRINITY && !AZEROTHCORE
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
#define TARGET_ICONS_COUNT         TARGET_ICON_COUNT
#define MAX_TALENT_SPECS        MAX_TALENT_SPEC_COUNT
#define TEAM_NEUTRAL            TEAM_INDEX_NEUTRAL


#if defined(CATA) && !defined(MANGOS)
#define PLAYER_FIELD_LIFETIME_HONORABLE_KILLS   PLAYER_FIELD_LIFETIME_HONORBALE_KILLS
#endif

#ifdef TBC
#define SPELL_AURA_MOD_KILL_XP_PCT  SPELL_AURA_MOD_XP_PCT
#endif

#if defined(CATA) || defined(MISTS) || (defined(WOTLK) && !defined(MANGOS))
#define UNIT_BYTE2_FLAG_SANCTUARY   UNIT_BYTE2_FLAG_SUPPORTABLE
#endif

#ifndef CMANGOS
typedef TemporarySummon TempSummon;
#else
typedef TemporarySpawn TempSummon;
#endif
typedef SpellEntry SpellInfo;
#endif // TRINITY

#endif // _ELUNA_INCLUDES_H
