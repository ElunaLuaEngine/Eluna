#
# Copyright (C) 2010 - 2016 Eluna Lua Engine <http://emudevs.com/>
# This program is free software licensed under GPL version 3
# Please see the included DOCS/LICENSE.md for more information
#

if( ELUNA AND ${CMAKE_PROJECT_NAME} STREQUAL "MaNGOS" )

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

  include_directories(
    ${CMAKE_SOURCE_DIR}/dep/g3dlite
    ${CMAKE_SOURCE_DIR}/src/shared
    ${CMAKE_SOURCE_DIR}/src/shared/Common
    ${CMAKE_SOURCE_DIR}/src/shared/Utilities
    ${CMAKE_SOURCE_DIR}/src/shared/Log
    ${CMAKE_SOURCE_DIR}/src/shared/DataStores
    ${CMAKE_SOURCE_DIR}/src/shared/Threading
    ${CMAKE_SOURCE_DIR}/src/framework
    ${CMAKE_SOURCE_DIR}/src/framework/Platform
    ${CMAKE_SOURCE_DIR}/src/game/BattleGround
    ${CMAKE_SOURCE_DIR}/src/game/Server
    ${CMAKE_SOURCE_DIR}/src/game/vmap
    ${CMAKE_SOURCE_DIR}/src/game/Maps
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

# Eluna modules

file(GLOB modules_list LIST_DIRECTORIES true ${CMAKE_CURRENT_SOURCE_DIR}/modules/*)
foreach(dir ${modules_list})
  IF(IS_DIRECTORY ${dir})
    get_filename_component(module_name ${dir} NAME)
    file(GLOB sources_module ${dir}/*.c ${dir}/*.h)

    if( ELUNA_MODULES AND sources_module )
      add_library(${module_name} MODULE
        ${sources_module})
      target_include_directories(${module_name}
        PUBLIC
          ${CMAKE_SOURCE_DIR}/dep/lualib)
      target_link_libraries(${module_name}
        PUBLIC
          lualib)
      if(UNIX)
        set_target_properties(${module_name}
          PROPERTIES
            RUNTIME_OUTPUT_DIRECTORY bin/lua_scripts/modules
            RUNTIME_OUTPUT_DIRECTORY bin/lua_scripts/modules)
      elseif(WIN32)
        set_target_properties(${module_name}
          PROPERTIES
            RUNTIME_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/bin/lua_scripts/modules"
            LIBRARY_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/bin/lua_scripts/modules")
        if( MSVC )
          foreach(OUTPUTCONFIG ${CMAKE_CONFIGURATION_TYPES})
            string( TOUPPER ${OUTPUTCONFIG} OUTPUTCONFIG )
            set_target_properties(${module_name}
              PROPERTIES
                RUNTIME_OUTPUT_DIRECTORY_${OUTPUTCONFIG} "${CMAKE_BINARY_DIR}/bin/$<CONFIG>/lua_scripts/modules"
                LIBRARY_OUTPUT_DIRECTORY_${OUTPUTCONFIG} "${CMAKE_BINARY_DIR}/bin/$<CONFIG>/lua_scripts/modules")
          endforeach()
        endif()
      endif()
      message(STATUS "Added Eluna custom module: ${dir}")
    endif()

    list(APPEND list_module_names ${module_name})
    list(APPEND list_module_sources ${sources_module})
    list(APPEND list_module_includes ${dir})
  ELSE()
    CONTINUE()
  ENDIF()
endforeach()

# safeguard to remove module sources from all other build targets than the modules themselves

macro(get_all_targets_recursive targets dir)
    get_property(subdirectories DIRECTORY ${dir} PROPERTY SUBDIRECTORIES)
    foreach(subdir ${subdirectories})
        get_all_targets_recursive(${targets} ${subdir})
    endforeach()

    get_property(current_targets DIRECTORY ${dir} PROPERTY BUILDSYSTEM_TARGETS)
    list(APPEND ${targets} ${current_targets})
endmacro()

get_all_targets_recursive(all_targets ${CMAKE_SOURCE_DIR})
foreach(target ${all_targets})
  if (${target} IN_LIST list_module_names)
    continue()
  else()
    get_target_property(_sources ${target} SOURCES)
    if(_sources)
      foreach(item ${list_module_sources})
        list(REMOVE_ITEM _sources ${item})
      endforeach()
      set_property(TARGET ${target} PROPERTY SOURCES ${_sources})
    endif()
    get_target_property(_includes ${target} INCLUDE_DIRECTORIES)
    if(_includes)
      foreach(dir ${list_module_includes})
        list(REMOVE_ITEM _includes ${dir})
      endforeach()
      set_property(TARGET ${target} PROPERTY INCLUDE_DIRECTORIES ${_includes})
    endif()
  endif()
endforeach()
