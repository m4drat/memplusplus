cmake_minimum_required(VERSION 3.13)

################# SET GLOBAL VARIABLES #################
set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} ${CMAKE_CURRENT_SOURCE_DIR}/cmake)
set(CMAKE_CXX_STANDARD 17)

################# DEFINE PROJECT #################
project(memplusplus LANGUAGES CXX)

################# GLOBAL OPTIONS #################
option(MPP_BUILD_FUZZER "Build mpp fuzzing harness" OFF)
option(MPP_BUILD_EXAMPLE "Build mpp example project" ON)
option(MPP_BUILD_TESTS "Build mpp tests" ON)
option(MPP_BUILD_DOCS "Build mpp documentation" OFF)
option(CMAKE_EXPORT_COMPILE_COMMANDS "Request generate of json file with all build commands" ON)

message(STATUS "##################### GLOBAL OPTIONS #####################")
message(STATUS "MPP_BUILD_FUZZER: ${MPP_BUILD_FUZZER}")
message(STATUS "MPP_BUILD_EXAMPLE: ${MPP_BUILD_EXAMPLE}")
message(STATUS "MPP_BUILD_TESTS: ${MPP_BUILD_TESTS}")
message(STATUS "MPP_BUILD_DOCS: ${MPP_BUILD_DOCS}")

################# ADD PROJECTS + DOCS + TESTS #################
add_subdirectory(libmemplusplus)

if (MPP_BUILD_FUZZER)
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