project(mpp)

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

target_include_directories(${PROJECT_NAME}
	PUBLIC ${PROJECT_SOURCE_DIR}/include
	PUBLIC ${PROJECT_SOURCE_DIR}/src
)

set_target_properties("${PROJECT_NAME}" PROPERTIES
	DEBUG_POSTFIX "-${STATIC_POSTFIX}d"
	RELEASE_POSTFIX "-${STATIC_POSTFIX}r"
	MINSIZEREL_POSTFIX "-${STATIC_POSTFIX}mr"
	RELWITHDEBINFO_POSTFIX "-${STATIC_POSTFIX}rd"
)

add_subdirectory(tests)