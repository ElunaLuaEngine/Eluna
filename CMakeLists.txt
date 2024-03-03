# Below is used for custom C module handling. 

target_compile_definitions(lualib PUBLIC LUA_COMPAT_MODULE)

file(GLOB modules_list LIST_DIRECTORIES true ${CMAKE_CURRENT_SOURCE_DIR}/modules/*)
foreach(dir ${modules_list})
  IF(IS_DIRECTORY ${dir})
    get_filename_component(module_name ${dir} NAME)
    file(GLOB sources_module ${dir}/*.c ${dir}/*.cpp ${dir}/*.h ${dir}/*.hpp)

    if(sources_module)
      add_library(${module_name} MODULE
        ${sources_module})
      target_include_directories(${module_name}
        INTERFACE
          ${PUBLIC_INCLUDES})
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