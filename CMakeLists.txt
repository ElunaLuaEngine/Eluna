# Define variables for paths
set(MODULES_DIR "${CMAKE_CURRENT_SOURCE_DIR}/modules")
if(UNIX)
  set(MODULES_OUTPUT_DIR "bin/lua_scripts/modules")
elseif(WIN32)
  set(MODULES_OUTPUT_DIR "${CMAKE_BINARY_DIR}/bin/lua_scripts/modules")
  set(MODULES_OUTPUT_DIR_CONF "${CMAKE_BINARY_DIR}/bin/$<CONFIG>/lua_scripts/modules")
endif()

# Add Lua compatibility definition
if(NOT ${LUA_VERSION} MATCHES "luajit")
  target_compile_definitions(lualib PUBLIC LUA_COMPAT_MODULE) 
endif()

# Collect module directories
file(GLOB_RECURSE modules_list LIST_DIRECTORIES true ${MODULES_DIR}/*)
foreach(dir ${modules_list})
  if(IS_DIRECTORY ${dir})
    get_filename_component(module_name ${dir} NAME)
    
    # Gather all module source files
    file(GLOB sources_module
      ${dir}/*.c
      ${dir}/*.cpp
      ${dir}/*.h
      ${dir}/*.hpp)
    
    # Add module target and properties
    if(sources_module)
      add_library(${module_name} MODULE ${sources_module})
      target_include_directories(${module_name} INTERFACE ${PUBLIC_INCLUDES})
      target_link_libraries(${module_name} PUBLIC lualib)
      set_target_properties(${module_name} PROPERTIES RUNTIME_OUTPUT_DIRECTORY ${MODULES_OUTPUT_DIR})
      
      if(WIN32)
        set_target_properties(${module_name} PROPERTIES LIBRARY_OUTPUT_DIRECTORY ${MODULES_OUTPUT_DIR})
        if(MSVC)
          foreach(OUTPUTCONFIG ${CMAKE_CONFIGURATION_TYPES})
            string( TOUPPER ${OUTPUTCONFIG} OUTPUTCONFIG )
            set_target_properties(${module_name}
              PROPERTIES
              RUNTIME_OUTPUT_DIRECTORY_${OUTPUTCONFIG} ${MODULES_OUTPUT_DIR_CONF}
              LIBRARY_OUTPUT_DIRECTORY_${OUTPUTCONFIG} ${MODULES_OUTPUT_DIR_CONF})
          endforeach()
        endif()
      endif()
      
      message(STATUS "Added Eluna custom module: ${dir}")
    endif()
    
    # Append to lists
    list(APPEND list_module_names ${module_name})
    list(APPEND list_module_sources ${sources_module})
    list(APPEND list_module_includes ${dir})
  endif()
endforeach()

# Safeguard to remove module sources from all other build targets than the modules themselves
macro(remove_module_sources target)
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
endmacro()

foreach(target ${all_targets})
  if (NOT ${target} IN_LIST list_module_names)
    remove_module_sources(${target})
  endif()
endforeach()
