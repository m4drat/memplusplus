cmake_minimum_required(VERSION 3.13)

################# SET GLOBAL VARIABLES #################
set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} ${CMAKE_CURRENT_SOURCE_DIR}/cmake)
set(CMAKE_CXX_STANDARD 17)

################# DEFINE PROJECT #################
project(memplusplus LANGUAGES CXX)

################# SET WARNING LEVELS #################
if (MSVC)
    add_compile_options(/W4)
else()
    add_compile_options(-Wall -Wextra -Wpedantic)
endif()

################# GLOBAL OPTIONS #################
if (CMAKE_COMPILER_IS_GNUCXX)
	option(MPP_ENABLE_COVERAGE "Enable coverage reporting for gcc/clang" OFF)
endif()

option(MPP_BUILD_FUZZER "Build mpp fuzzing harness" OFF)
option(MPP_BUILD_EXAMPLE "Build mpp example project" OFF)
option(MPP_BUILD_TESTS "Build mpp tests" ON)
option(MPP_BUILD_DOCS "Build mpp documentation" OFF)
option(CMAKE_EXPORT_COMPILE_COMMANDS "Request generate of json file with all build commands" ON)

message(STATUS "##################### GLOBAL OPTIONS #####################")
message(STATUS "MPP_ENABLE_COVERAGE : ${MPP_ENABLE_COVERAGE}")
message(STATUS "MPP_BUILD_FUZZER    : ${MPP_BUILD_FUZZER}")
message(STATUS "MPP_BUILD_EXAMPLE   : ${MPP_BUILD_EXAMPLE}")
message(STATUS "MPP_BUILD_TESTS     : ${MPP_BUILD_TESTS}")
message(STATUS "MPP_BUILD_DOCS      : ${MPP_BUILD_DOCS}")

################# ADD PROJECTS + DOCS + TESTS #################
add_subdirectory(libmemplusplus)
if (MPP_ENABLE_COVERAGE)
	target_compile_options(mpp PRIVATE --coverage -O0 -g -fno-inline)
	target_link_libraries(mpp --coverage)
endif()

if (MPP_BUILD_FUZZER)
	add_subdirectory(fuzzing_harness)
endif()

if (MPP_BUILD_EXAMPLE)
	add_subdirectory(example_project)
endif()

if (MPP_BUILD_TESTS)
	enable_testing()
	add_subdirectory(tests)
	if (MPP_ENABLE_COVERAGE)
		target_compile_options(mpp PRIVATE --coverage -O0 -g -fno-inline)
		target_link_libraries(unit_tests --coverage)
	endif()
endif()

if (MPP_BUILD_DOCS)
	add_subdirectory(docs)
endif()

################# CLANG FORMAT / CLANG-TIDY #################
include(cmake/clang-cxx-dev-tools.cmake)