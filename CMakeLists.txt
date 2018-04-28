if( ELUNA )
	CU_SET_PATH("CMAKE_MOD_ELUNA_ENGINE_DIR" "${CMAKE_CURRENT_LIST_DIR}")
	add_subdirectory(lualib)
	add_subdirectory(LuaEngine)
	
	CU_ADD_HOOK(AFTER_WORLDSERVER_CMAKE "${CMAKE_CURRENT_LIST_DIR}/cmake/after_ws_install.cmake")
	install(FILES "${CMAKE_MOD_ELUNA_ENGINE_DIR}/conf/mod_LuaEngine.conf.dist" DESTINATION ${CONF_DIR})
endif()




