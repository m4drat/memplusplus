cmake_minimum_required(VERSION 3.10)

################# ADDED TO SUPPORT DEBUGGING #################
set(CMAKE_C_FLAGS_DEBUG "-g2 -DDEBUG")
set(CMAKE_CXX_FLAGS_DEBUG "-g2 -DDEBUG")

################# SET GLOBAL VARIABLES #################
set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} ${CMAKE_CURRENT_SOURCE_DIR}/cmake)
set(CMAKE_CXX_STANDARD 17)

################# DEFINE PROJECT #################
project(memplusplus VERSION 1.0.0 LANGUAGES CXX)

################# OPTIONS #################
option(BUILD_SHARED_LIBS "Request build of shared libraries" ON)
option(MPP_BUILD_HARNESS "Build the mpp fuzzing harness" OFF)
option(MPP_BUILD_EXAMPLE "Build the mpp example project" OFF)
option(MPP_BUILD_TESTS "Build the mpp tests" OFF)
option(MPP_BUILD_DOCS "Build the mpp documentation" OFF)
option(CMAKE_EXPORT_COMPILE_COMMANDS "Request generate of json file with all build commands" ON)

message(STATUS "BUILD_SHARED_LIBS: ${BUILD_SHARED_LIBS}")
message(STATUS "MPP_BUILD_HARNESS: ${MPP_BUILD_HARNESS}")
message(STATUS "MPP_BUILD_EXAMPLE: ${MPP_BUILD_EXAMPLE}")
message(STATUS "MPP_BUILD_TESTS: ${MPP_BUILD_TESTS}")
message(STATUS "MPP_BUILD_DOCS: ${MPP_BUILD_DOCS}")

if(NOT BUILD_SHARED_LIBS)
	set(STATIC_POSTFIX "s")
endif()

################# UPDATE INCLUDE PATHS #################
set(EXAMPLE_PROJECT_INCLUDES ${ALL_INCLUDE_DIRECTORIES} ${PROJECT_SOURCE_DIR}/example_project/include)
set(FUZZING_HARNESS_INCLUDES ${ALL_INCLUDE_DIRECTORIES} ${PROJECT_SOURCE_DIR}/fuzzing_harness/include)
set(LIBMEMPLUSPLUS_INCLUDES ${ALL_INCLUDE_DIRECTORIES} ${PROJECT_SOURCE_DIR}/libmemplusplus/include)

################# ADD PROJECTS + DOCS + TESTS #################
add_subdirectory(libmemplusplus)

if (MPP_BUILD_HARNESS)
	add_subdirectory(fuzzing_harness)
endif()

if (MPP_BUILD_EXAMPLE)
	add_subdirectory(example_project)
endif()

if (MPP_BUILD_TESTS)
	enable_testing()
	add_subdirectory(tests)
endif()

if (MPP_BUILD_DOCS)
	add_subdirectory(docs)
endif()

################# CLANG FORMAT / CLANG-TIDY #################
include(cmake/clang-cxx-dev-tools.cmake)