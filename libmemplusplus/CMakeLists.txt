################# SET UP PROJECT + VERSION #################
project(mpp LANGUAGES CXX)
set(VERSION_MAJOR 2)
set(VERSION_MINOR 3)
set(VERSION_PATCH 5)
set(MPP_VERSION ${VERSION_MAJOR}.${VERSION_MINOR}.${VERSION_PATCH})

################# CHECK IF IT IS LINUX #################
if (WIN32)
	message(FATAL_ERROR "Windows is not currently supported!")
endif()

################# LIBRARY OPTIONS #################
if (CMAKE_CXX_COMPILER_ID STREQUAL "GNU" OR CMAKE_CXX_COMPILER_ID MATCHES ".*Clang")
	option(MPP_SANITIZERS "Build mpp with support of sanitizers" OFF)
endif()

option(MPP_BUILD_SHARED_LIBS "Request build of shared libraries" ON)
option(MPP_FULL_DEBUG "Build mpp in full debug mode. Added extended security checks" OFF)
option(MPP_SECURE "Build mpp in secure mode" OFF)
option(MPP_PROFILE "Build mpp with support of profiling" ON)
option(MPP_COLOUR "Build mpp with support of coloured output" ON)
option(MPP_STATS "Build mpp with support of statistics dumping" ON)

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
	set(MPP_DEBUG ON)
	list(APPEND MPP_DEFINES DEBUG=1)
	list(APPEND MPP_DEFINES MPP_DEBUG=1)
	list(APPEND MPP_DEFINES MPP_FILL_CHAR='\\x99')
else()
	set(MPP_DEBUG OFF)
	list(APPEND MPP_DEFINES MPP_DEBUG=0)
	list(APPEND MPP_DEFINES DEBUG=0)
endif()

################# SET DEFINES IF BUILDING WITH FUZZER #################
if (MPP_BUILD_FUZZER MATCHES "ON" OR MPP_USE_FUZZER_DEFINITIONS MATCHES "ON")
	set(MPP_SANITIZERS ON)
	list(APPEND MPP_DEFINES MPP_FUZZER_INSECURE=1)
else()
	list(APPEND MPP_DEFINES MPP_FUZZER_INSECURE=0)
endif()

# extended debug features, such as full free-list checks for double-free
if (MPP_FULL_DEBUG MATCHES "ON" AND MPP_DEBUG MATCHES "ON")
	message(STATUS "Building in full debug mode: MPP_FULL_DEBUG=1")
	set(MPP_FULL_DEBUG ON)
	list(APPEND MPP_DEFINES MPP_FULL_DEBUG=1)
	
	# In full debug mode we want to fill memory
    # with non-zero values, so we actually can easily crash
    # or spot a weird behaviour
	list(APPEND MPP_DEFINES MPP_FILL_CHAR='\\x99')
else()
	set(MPP_FULL_DEBUG OFF)
	list(APPEND MPP_DEFINES MPP_FULL_DEBUG=0)
endif()

if (MPP_SECURE MATCHES "ON")
	message(STATUS "Building in secure mode: MPP_SECURE=1")
	list(APPEND MPP_DEFINES MPP_SECURE=1)

	# In secure mode we want to fill memory with zeroes 
    # (prevents memleaks through string printing functions)
	if (MPP_FULL_DEBUG MATCHES "OFF" AND MPP_DEBUG MATCHES "OFF") 
		list(APPEND MPP_DEFINES MPP_FILL_CHAR='\\x00')
	endif()
else()
	list(APPEND MPP_DEFINES MPP_SECURE=0)
endif()

if (MPP_PROFILE MATCHES "ON")
	message(STATUS "Building in profiling mode: MPP_PROFILE=1")
	list(APPEND MPP_DEFINES MPP_PROFILE=1)
else()
	list(APPEND MPP_DEFINES MPP_PROFILE=0)
endif()

if (MPP_COLOUR MATCHES "ON")
	message(STATUS "Building with support of coloured output: MPP_COLOUR=1")
	list(APPEND MPP_DEFINES MPP_COLOUR=1)
else()
	list(APPEND MPP_DEFINES MPP_COLOUR=0)
endif()

if (MPP_STATS MATCHES "ON" AND MPP_DEBUG MATCHES "OFF")
	message(FATAL "Statistics cannot be enabled in non-debug mode!")
elseif (MPP_STATS MATCHES "ON" AND MPP_DEBUG MATCHES "ON")
	message(STATUS "Building with support of statistics dumping: MPP_STATS=1")
	list(APPEND MPP_DEFINES MPP_STATS=1)
else()
	list(APPEND MPP_DEFINES MPP_STATS=0)
endif()

if (MPP_BUILD_TESTS MATCHES "ON")
	list(APPEND MPP_DEFINES MPP_BUILD_TESTS=1)
endif()

message(STATUS "##################### LIBRARY OPTIONS #####################")
message(STATUS "MPP_SANITIZERS        : ${MPP_SANITIZERS}")
message(STATUS "MPP_BUILD_SHARED_LIBS : ${MPP_BUILD_SHARED_LIBS}")
message(STATUS "MPP_FULL_DEBUG        : ${MPP_FULL_DEBUG}")
message(STATUS "MPP_DEBUG             : ${MPP_DEBUG}")
message(STATUS "MPP_SECURE            : ${MPP_SECURE}")
message(STATUS "MPP_PROFILE           : ${MPP_PROFILE}")
message(STATUS "MPP_COLOUR            : ${MPP_COLOUR}")
message(STATUS "MPP_STATS             : ${MPP_STATS}")

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
list(APPEND MPP_SOURCES
	src/heuristics/heuristics.cpp
	src/containers/chunk_treap.cpp
	src/containers/gc_graph.cpp
	src/containers/node.cpp
	src/containers/vertex.cpp
	src/shared_gcptr.cpp
	src/arena.cpp
	src/memory_manager.cpp
	src/gc.cpp
	src/utils/utils.cpp
)

################# ADD SPECIFIC SOURCES #################
if(MPP_DEBUG MATCHES "ON" OR MPP_STATS MATCHES "ON")
	list(APPEND MPP_SOURCES src/utils/env_options.cpp)
endif()

if(MPP_STATS MATCHES "ON")
	list(APPEND MPP_SOURCES src/utils/statistics.cpp)
endif()

if(MPP_PROFILE MATCHES "ON" OR MPP_STATS MATCHES "ON")
	list(APPEND MPP_SOURCES src/utils/timer.cpp)
	if (MPP_PROFILE MATCHES "ON")
		list(APPEND MPP_SOURCES src/utils/profiler.cpp)
		list(APPEND MPP_SOURCES src/utils/profiler_timer.cpp)
	endif()
endif()

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

################# ENABLE LTO OPTIMIZATIONS #################
# target_compile_options(${PROJECT_NAME} PRIVATE -flto)

################# ALIAS TO USE AS AN INTERNAL PROJECT #################
add_library(lib::mpp ALIAS ${PROJECT_NAME})

################# SET DEBUG COMPILER OPTIONS #################
if (CMAKE_BUILD_TYPE MATCHES ".*(D|d)ebug$")
	# ADDED TO SUPPORT DEBUGGING
	target_compile_options(${PROJECT_NAME} PRIVATE -g -O0)	# to support backtrace dumping in debug mode
	target_link_libraries(${PROJECT_NAME} PRIVATE -ldl)
endif()

################# ENABLE SUPPORT OF SANITIZERS #################
if (MPP_SANITIZERS MATCHES "ON")
	target_compile_options(${PROJECT_NAME} INTERFACE -fsanitize=address -g -O2 -fno-omit-frame-pointer)
	target_link_libraries(${PROJECT_NAME} INTERFACE -fsanitize=address)
endif()

target_compile_definitions(${PROJECT_NAME} 
	PUBLIC ${MPP_DEFINES}
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