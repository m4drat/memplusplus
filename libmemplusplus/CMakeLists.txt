################# SET UP PROJECT + VERSION #################
project(mpp VERSION 1.0.0 LANGUAGES CXX)

################# ADD CONFIG FILE #################
configure_file(${PROJECT_SOURCE_DIR}/include/mpplib/config.h.in 
	${PROJECT_SOURCE_DIR}/include/mpplib/config.h @ONLY
)

################# COMPILE LIBRARY #################
add_library(${PROJECT_NAME}
	src/heuristics/heuristics.cpp
	src/containers/chunk_treap.cpp
	src/containers/gc_graph.cpp
	src/containers/node.cpp
	src/containers/vertex.cpp
	src/shared_gcptr.cpp
	src/arena.cpp
	src/memory_allocator.cpp
	src/memory_manager.cpp
	src/gc.cpp
)
add_library(lib::mpp ALIAS ${PROJECT_NAME})

################# UPDATE INCLUDE DIRECTORIES #################
target_include_directories(${PROJECT_NAME}
	PUBLIC ${PROJECT_SOURCE_DIR}/include
	PUBLIC ${PROJECT_SOURCE_DIR}/src
)

################# TARGET PROPERTIES #################
set_target_properties(${PROJECT_NAME}
	PROPERTIES
	VERSION ${PROJECT_VERSION}
	DEBUG_POSTFIX "-${STATIC_POSTFIX}d"
	RELEASE_POSTFIX "-${STATIC_POSTFIX}r"
	MINSIZEREL_POSTFIX "-${STATIC_POSTFIX}mr"
	RELWITHDEBINFO_POSTFIX "-${STATIC_POSTFIX}rd"
	ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib
	LIBRARY_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib
	RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin
)

################# INSTALL LIBRARY #################
include(GNUInstallDirs)

install(TARGETS ${PROJECT_NAME} 
	EXPORT MpplibConfig
    ARCHIVE DESTINATION ${CMAKE_INSTALL_LIBDIR}
    LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
    RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR})

install(DIRECTORY include/ DESTINATION ${CMAKE_INSTALL_INCLUDEDIR}/${PROJECT_NAME})
install(EXPORT MpplibConfig DESTINATION share/mpplib/cmake)

export(TARGETS ${PROJECT_NAME} FILE MyLibConfig.cmake)