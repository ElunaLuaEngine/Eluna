#
# Copyright (C) 2010 - 2015 Eluna Lua Engine <http://emudevs.com/>
# This program is free software licensed under GPL version 3
# Please see the included DOCS/LICENSE.md for more information
#

if ( USE_COREPCH )
  include_directories(${CMAKE_CURRENT_BINARY_DIR})
  include_directories(${CMAKE_SOURCE_DIR})
endif ()

# Iterates through all the source files and adds them to the solution
file(GLOB sources_localdir *.cpp *.h)

# Adds all the method headers to its own source group
file(GLOB method_headers  *Methods.h)
source_group("Methods" FILES ${method_headers})

set(LuaEngine_STAT_SRCS
  ${LuaEngine_STAT_SRCS}
  ${sources_localdir}
)

include_directories(
  ${CMAKE_SOURCE_DIR}/dep/zlib
  ${CMAKE_SOURCE_DIR}/dep/lualib
  ${CMAKE_BINARY_DIR}
  ${ACE_INCLUDE_DIR}
  ${MYSQL_INCLUDE_DIR}
  ${OPENSSL_INCLUDE_DIR}
)

add_library(LuaEngine STATIC
  ${LuaEngine_STAT_SRCS}
  ${game_STAT_SRCS}
  ${game_STAT_PCH_SRC}
)

if( ${CMAKE_PROJECT_NAME} STREQUAL "TrinityCore" )
  include_directories(
    ${CMAKE_SOURCE_DIR}/dep/recastnavigation/Detour
    ${CMAKE_SOURCE_DIR}/dep/recastnavigation/Detour/Include
    ${CMAKE_SOURCE_DIR}/dep/recastnavigation/Recast
    ${CMAKE_SOURCE_DIR}/dep/recastnavigation/Recast/Include
    ${CMAKE_SOURCE_DIR}/dep/g3dlite/include
    ${CMAKE_SOURCE_DIR}/dep/SFMT
    ${CMAKE_SOURCE_DIR}/dep/mersennetwister
    ${CMAKE_SOURCE_DIR}/src/server/shared
    ${CMAKE_SOURCE_DIR}/src/server/shared/Configuration
    ${CMAKE_SOURCE_DIR}/src/server/shared/Cryptography
    ${CMAKE_SOURCE_DIR}/src/server/shared/Cryptography/Authentication
    ${CMAKE_SOURCE_DIR}/src/server/shared/Database
    ${CMAKE_SOURCE_DIR}/src/server/shared/DataStores
    ${CMAKE_SOURCE_DIR}/src/server/shared/Debugging
    ${CMAKE_SOURCE_DIR}/src/server/shared/Dynamic/CountedReference
    ${CMAKE_SOURCE_DIR}/src/server/shared/Dynamic/LinkedReference
    ${CMAKE_SOURCE_DIR}/src/server/shared/Dynamic
    ${CMAKE_SOURCE_DIR}/src/server/shared/Logging
    ${CMAKE_SOURCE_DIR}/src/server/shared/Packets
    ${CMAKE_SOURCE_DIR}/src/server/shared/Policies
    ${CMAKE_SOURCE_DIR}/src/server/shared/Threading
    ${CMAKE_SOURCE_DIR}/src/server/shared/Utilities
    ${CMAKE_SOURCE_DIR}/src/server/ipc
    ${CMAKE_SOURCE_DIR}/src/server/collision
    ${CMAKE_SOURCE_DIR}/src/server/collision/Management
    ${CMAKE_SOURCE_DIR}/src/server/collision/Models
    ${CMAKE_SOURCE_DIR}/src/server/collision/Maps
    ${CMAKE_SOURCE_DIR}/src/server/shared
    ${CMAKE_SOURCE_DIR}/src/server/shared/Database
    ${CMAKE_SOURCE_DIR}/src/server/game/Accounts
    ${CMAKE_SOURCE_DIR}/src/server/game/Achievements
    ${CMAKE_SOURCE_DIR}/src/server/game/Addons
    ${CMAKE_SOURCE_DIR}/src/server/game/Handlers
    ${CMAKE_SOURCE_DIR}/src/server/game/AI
    ${CMAKE_SOURCE_DIR}/src/server/game/AI/CoreAI
    ${CMAKE_SOURCE_DIR}/src/server/game/AI/EventAI
    ${CMAKE_SOURCE_DIR}/src/server/game/AI/ScriptedAI
    ${CMAKE_SOURCE_DIR}/src/server/game/AI/SmartScripts
    ${CMAKE_SOURCE_DIR}/src/server/game/AuctionHouse
    ${CMAKE_SOURCE_DIR}/src/server/game/Battlegrounds
    ${CMAKE_SOURCE_DIR}/src/server/game/Battlegrounds/Zones
    ${CMAKE_SOURCE_DIR}/src/server/game/Calendar
    ${CMAKE_SOURCE_DIR}/src/server/game/Chat
    ${CMAKE_SOURCE_DIR}/src/server/game/Chat/Channels
    ${CMAKE_SOURCE_DIR}/src/server/game/Conditions
    ${CMAKE_SOURCE_DIR}/src/server/shared/Configuration
    ${CMAKE_SOURCE_DIR}/src/server/game/Combat
    ${CMAKE_SOURCE_DIR}/src/server/game/DataStores
    ${CMAKE_SOURCE_DIR}/src/server/game/DungeonFinding
    ${CMAKE_SOURCE_DIR}/src/server/game/Entities/AreaTrigger
    ${CMAKE_SOURCE_DIR}/src/server/game/Entities/Corpse
    ${CMAKE_SOURCE_DIR}/src/server/game/Entities/Creature
    ${CMAKE_SOURCE_DIR}/src/server/game/Entities/DynamicObject
    ${CMAKE_SOURCE_DIR}/src/server/game/Entities/Item
    ${CMAKE_SOURCE_DIR}/src/server/game/Entities/Item/Container
    ${CMAKE_SOURCE_DIR}/src/server/game/Entities/GameObject
    ${CMAKE_SOURCE_DIR}/src/server/game/Entities/Object
    ${CMAKE_SOURCE_DIR}/src/server/game/Entities/Object/Updates
    ${CMAKE_SOURCE_DIR}/src/server/game/Entities/Pet
    ${CMAKE_SOURCE_DIR}/src/server/game/Entities/Player
    ${CMAKE_SOURCE_DIR}/src/server/game/Entities/Transport
    ${CMAKE_SOURCE_DIR}/src/server/game/Entities/Unit
    ${CMAKE_SOURCE_DIR}/src/server/game/Entities/Vehicle
    ${CMAKE_SOURCE_DIR}/src/server/game/Events
    ${CMAKE_SOURCE_DIR}/src/server/game/Globals
    ${CMAKE_SOURCE_DIR}/src/server/game/Grids
    ${CMAKE_SOURCE_DIR}/src/server/game/Grids/Cells
    ${CMAKE_SOURCE_DIR}/src/server/game/Grids/Notifiers
    ${CMAKE_SOURCE_DIR}/src/server/game/Groups
    ${CMAKE_SOURCE_DIR}/src/server/game/Guilds
    ${CMAKE_SOURCE_DIR}/src/server/game/Instances
    ${CMAKE_SOURCE_DIR}/src/server/game/LookingForGroup
    ${CMAKE_SOURCE_DIR}/src/server/game/Loot
    ${CMAKE_SOURCE_DIR}/src/server/game/Mails
    ${CMAKE_SOURCE_DIR}/src/server/game/Miscellaneous
    ${CMAKE_SOURCE_DIR}/src/server/game/Maps
    ${CMAKE_SOURCE_DIR}/src/server/game/Movement
    ${CMAKE_SOURCE_DIR}/src/server/game/Movement/MovementGenerators
    ${CMAKE_SOURCE_DIR}/src/server/game/Movement/Waypoints
    ${CMAKE_SOURCE_DIR}/src/server/game/Movement/Spline
    ${CMAKE_SOURCE_DIR}/src/server/game/Opcodes
    ${CMAKE_SOURCE_DIR}/src/server/game/OutdoorPvP
    ${CMAKE_SOURCE_DIR}/src/server/game/Pools
    ${CMAKE_SOURCE_DIR}/src/server/game/PrecompiledHeaders
    ${CMAKE_SOURCE_DIR}/src/server/game/Quests
    ${CMAKE_SOURCE_DIR}/src/server/game/Reputation
    ${CMAKE_SOURCE_DIR}/src/server/game/Scripting
    ${CMAKE_SOURCE_DIR}/src/server/game/Server
    ${CMAKE_SOURCE_DIR}/src/server/game/Server/Protocol
    ${CMAKE_SOURCE_DIR}/src/server/game/Server/Protocol/Handlers
    ${CMAKE_SOURCE_DIR}/src/server/game/Skills
    ${CMAKE_SOURCE_DIR}/src/server/game/Spells
    ${CMAKE_SOURCE_DIR}/src/server/game/Spells/Auras
    ${CMAKE_SOURCE_DIR}/src/server/game/Texts
    ${CMAKE_SOURCE_DIR}/src/server/game/Tickets
    ${CMAKE_SOURCE_DIR}/src/server/game/Tools
    ${CMAKE_SOURCE_DIR}/src/server/game/Weather
    ${CMAKE_SOURCE_DIR}/src/server/game/World
    ${CMAKE_SOURCE_DIR}/src/server/scripts/PrecompiledHeaders
    ${Boost_LIBRARIES}
  )

  find_package(Boost COMPONENTS system filesystem REQUIRED)

  target_link_libraries(LuaEngine
    game
    ${Boost_LIBRARIES}
  )

  add_dependencies(LuaEngine game)
  
  if( WIN32 )
    if ( MSVC )
      add_custom_command(TARGET LuaEngine
        POST_BUILD
        COMMAND ${CMAKE_COMMAND} -E make_directory ${CMAKE_BINARY_DIR}/bin/$(ConfigurationName)/lua_scripts/extensions/
        COMMAND ${CMAKE_COMMAND} -E copy_directory ${CMAKE_CURRENT_SOURCE_DIR}/extensions ${CMAKE_BINARY_DIR}/bin/$(ConfigurationName)/lua_scripts/extensions/
      )
    elseif ( MINGW )
      add_custom_command(TARGET LuaEngine
        POST_BUILD
        COMMAND ${CMAKE_COMMAND} -E make_directory ${CMAKE_BINARY_DIR}/bin/lua_scripts/extensions/
        COMMAND ${CMAKE_COMMAND} -E copy_directory ${CMAKE_CURRENT_SOURCE_DIR}/extensions ${CMAKE_BINARY_DIR}/bin/lua_scripts/extensions/
      )
    endif()
  endif()
  
  if( UNIX )
    install(DIRECTORY extensions DESTINATION bin/lua_scripts/)
  elseif( WIN32 )
    install(DIRECTORY extensions DESTINATION "${CMAKE_BINARY_DIR}/bin/$(ConfigurationName)/lua_scripts/")
  endif()

elseif( ${CMAKE_PROJECT_NAME} STREQUAL "MaNGOS" )
  include_directories(
    ${CMAKE_SOURCE_DIR}/src/shared
    ${CMAKE_SOURCE_DIR}/src/framework
    ${CMAKE_SOURCE_DIR}/src/framework/Platform
    ${CMAKE_SOURCE_DIR}/src/game/BattleGround
    ${CMAKE_SOURCE_DIR}/src/game/Server
    ${CMAKE_SOURCE_DIR}/src/game/vmap
    ${CMAKE_SOURCE_DIR}/src/game/MotionGenerators
    ${CMAKE_SOURCE_DIR}/src/game/Tools
    ${CMAKE_SOURCE_DIR}/src/game/References
    ${CMAKE_SOURCE_DIR}/src/game/WorldHandlers
    ${CMAKE_SOURCE_DIR}/src/game/Object
  )
  
  if( WIN32 )
    if ( MSVC )
      add_custom_command(TARGET LuaEngine
        POST_BUILD
        COMMAND ${CMAKE_COMMAND} -E make_directory "${CMAKE_BINARY_DIR}/bin/$(ConfigurationName)/lua_scripts/extensions/"
        COMMAND ${CMAKE_COMMAND} -E copy_directory "${CMAKE_CURRENT_SOURCE_DIR}/extensions" "${CMAKE_BINARY_DIR}/bin/$(ConfigurationName)/lua_scripts/extensions/"
      )
    elseif ( MINGW )
      add_custom_command(TARGET LuaEngine
        POST_BUILD
        COMMAND ${CMAKE_COMMAND} -E make_directory "${CMAKE_BINARY_DIR}/bin/lua_scripts/extensions/"
        COMMAND ${CMAKE_COMMAND} -E copy_directory "${CMAKE_CURRENT_SOURCE_DIR}/extensions" "${CMAKE_BINARY_DIR}/bin/ua_scripts/extensions/"
      )
    endif()
  endif()
  
  install(DIRECTORY extensions DESTINATION "${BIN_DIR}/lua_scripts/")
  
endif()
