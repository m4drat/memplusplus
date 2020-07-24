################# SET UP PROJECT + VERSION #################
project(mpp LANGUAGES CXX)
set(VERSION_MAJOR 1)
set(VERSION_MINOR 0)
set(VERSION_PATCH 0)
set(MPP_VERSION ${VERSION_MAJOR}.${VERSION_MINOR}.${VERSION_PATCH})

################# CHECK IF IT IS LINUX #################
if (WIN32)
	message(FATAL_ERROR "Windows is not currently supported!")
endif()

################# LIBRARY OPTIONS #################
option(MPP_BUILD_SHARED_LIBS "Request build of shared libraries" ON)
option(MPP_FULL_DEBUG "Build mpp in full debug mode. Added extended security checks (ON by default in Debug mode)" OFF)
option(MPP_SECURE "Build mpp in secure mode" OFF)

################# DEFAULT BUILD TYPE #################
if (NOT CMAKE_BUILD_TYPE)
	if ("${CMAKE_BINARY_DIR}" MATCHES ".*(D|d)ebug$")
		message(STATUS "No build type selected, default to: Debug")
		set(CMAKE_BUILD_TYPE "Debug")
	else()
		message(STATUS "No build type selected, default to: Release")
		set(CMAKE_BUILD_TYPE "Release")
	endif()
endif()

################# SET DEFINES FOR DEBUG MODE #################
if (CMAKE_BUILD_TYPE MATCHES ".*(D|d)ebug$")
	# standart debug defines
	list(APPEND MPP_DEFINES DEBUG=1)
	list(APPEND MPP_DEFINES MPP_DEBUG=1)

	# use extended debug features
	set(MPP_FULL_DEBUG ON)
else()
	list(APPEND MPP_DEFINES MPP_DEBUG=0)
	list(APPEND MPP_DEFINES DEBUG=0)
endif()

# extended debug features, such as full free-list checks for double-free
if (MPP_FULL_DEBUG MATHCES "ON")
	message(STATUS "Building in full debug mode: MPP_FULL_DEBUG=1")
	list(APPEND MPP_DEFINES MPP_FULL_DEBUG=1)
else()
	list(APPEND MPP_DEFINES MPP_FULL_DEBUG=0)
endif()

message(STATUS "MPP_BUILD_SHARED_LIBS: ${MPP_BUILD_SHARED_LIBS}")
message(STATUS "MPP_SECURE: ${MPP_SECURE}")
message(STATUS "MPP_DEBUG: ${MPP_DEBUG}")
message(STATUS "MPP_FULL_DEBUG: ${MPP_FULL_DEBUG}")

if (MPP_SECURE MATCHES "ON")
	message(STATUS "Building in secure mode: MPP_SECURE=1")
	list(APPEND MPP_DEFINES MPP_SECURE=1)
endif()

################# ADD CONFIG FILE #################
configure_file(${PROJECT_SOURCE_DIR}/src/config.hpp.in 
	${PROJECT_SOURCE_DIR}/include/mpplib/config.hpp @ONLY
)

################# ADD INSTALL PATHS #################
#  - CMAKE_INSTALL_LIBDIR
#  - CMAKE_INSTALL_BINDIR
#  - CMAKE_INSTALL_INCLUDEDIR
include(GNUInstallDirs)

################# SET SOURCES #################
set(MPP_SOURCES
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

################# SET TARGET NAME #################
if(MPP_SECURE MATCHES "ON")
	set(MPP_BASENAME "${PROJECT_NAME}-secure")
else()
	set(MPP_BASENAME ${PROJECT_NAME})
endif()

string(TOLOWER ${CMAKE_BUILD_TYPE} CMAKE_BUILD_TYPE_LC)

if(NOT(CMAKE_BUILD_TYPE_LC MATCHES "^(release|relwithdebinfo|minsizerel)$"))
	set(MPP_BASENAME "${MPP_BASENAME}-${CMAKE_BUILD_TYPE_LC}") #append build type (e.g. -debug) if not a release version
endif()

if(MPP_BUILD_SHARED_LIBS)
	list(APPEND MPP_BUILD_TARGETS "shared")
else()
	list(APPEND MPP_BUILD_TARGETS "static")
endif()

################# OUTPUT LIBRARY INFO #################
message(STATUS "##################### LIBRARY INFO #####################")
message(STATUS "Library base name: ${MPP_BASENAME}")
message(STATUS "Build type       : ${CMAKE_BUILD_TYPE_LC}")
message(STATUS "Install directory: ${CMAKE_INSTALL_LIBDIR}")
message(STATUS "Build targets    : ${MPP_BUILD_TARGETS}")

################# COMPILE LIBRARY #################
if (MPP_BUILD_SHARED_LIBS)
	add_library(${PROJECT_NAME} SHARED ${MPP_SOURCES})
else()
	add_library(${PROJECT_NAME} STATIC ${MPP_SOURCES})
endif()

################# ALIAS TO USE AS AN INTERNAL PROJECT #################
add_library(lib::mpp ALIAS ${PROJECT_NAME})

################# SET DEBUG FLAG FOR DEBUG BUILDS #################
if (CMAKE_BUILD_TYPE MATCHES ".*(D|d)ebug$")
	# ADDED TO SUPPORT DEBUGGING
	target_compile_options(${PROJECT_NAME} PRIVATE "-g")
endif()

target_compile_definitions(${PROJECT_NAME} 
	PRIVATE ${MPP_DEFINES}
)

set_target_properties(${PROJECT_NAME} 
	PROPERTIES 
	VERSION ${MPP_VERSION} 
	OUTPUT_NAME ${MPP_BASENAME}
)

################# UPDATE INCLUDE DIRECTORIES #################
target_include_directories(${PROJECT_NAME} PUBLIC
	$<BUILD_INTERFACE:${PROJECT_SOURCE_DIR}/include>
	$<BUILD_INTERFACE:${PROJECT_SOURCE_DIR}/src>
	$<INSTALL_INTERFACE:${CMAKE_INSTALL_INCLUDEDIR}>
)

message(STATUS "Used defines : ${MPP_DEFINES}")

################# INSTALL LIBRARY #################

# Install targets
install(TARGETS ${PROJECT_NAME} 
	EXPORT ${PROJECT_NAME}-config
    ARCHIVE DESTINATION ${CMAKE_INSTALL_LIBDIR}
    LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
	RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
	INCLUDES DESTINATION ${CMAKE_INSTALL_INCLUDEDIR}
)

# Install headers
install(DIRECTORY ${CMAKE_CURRENT_LIST_DIR}/include/ 
	DESTINATION ${CMAKE_INSTALL_INCLUDEDIR})

# Install Config
set(CONFIG_INSTALL_DIR ${CMAKE_INSTALL_LIBDIR}/cmake/${PROJECT_NAME})

install(EXPORT ${PROJECT_NAME}-config 
	NAMESPACE ${PROJECT_NAME}::
	DESTINATION ${CONFIG_INSTALL_DIR}
)

# Install version file
include(CMakePackageConfigHelpers)
set(VERSION_CONFIG_FILE ${CMAKE_CURRENT_BINARY_DIR}/cmake/${PROJECT_NAME}-config-version.cmake)

write_basic_package_version_file(${VERSION_CONFIG_FILE}
	VERSION ${MPP_VERSION}
	COMPATIBILITY SameMajorVersion
)

install(FILES ${VERSION_CONFIG_FILE}
	DESTINATION ${CONFIG_INSTALL_DIR}
)