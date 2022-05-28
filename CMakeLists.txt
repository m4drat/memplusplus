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
    add_compile_options(-Wall -Wextra -Wpedantic -Wno-unused-parameter -Wno-unused-variable -Wno-exceptions)
endif()

################# GLOBAL OPTIONS #################
if (CMAKE_CXX_COMPILER_ID STREQUAL "GNU" OR CMAKE_CXX_COMPILER_ID MATCHES ".*Clang")
	option(MPP_ENABLE_COVERAGE "Enable coverage reporting for gcc/clang" OFF)
endif()

option(MPP_BUILD_FUZZER "Build mpp fuzzing harness" OFF)
option(MPP_USE_FUZZER_DEFINITIONS "Build mpp with fuzzing-friendly defines" OFF)
option(MPP_BUILD_EXAMPLE "Build mpp example project" ON)
option(MPP_BUILD_TESTS "Build mpp tests" ON)
option(MPP_BUILD_DOCS "Build mpp documentation" OFF)
option(CMAKE_EXPORT_COMPILE_COMMANDS "Request generate of json file with all build commands" ON)

message(STATUS "##################### GLOBAL OPTIONS #####################")
message(STATUS "MPP_ENABLE_COVERAGE        : ${MPP_ENABLE_COVERAGE}")
message(STATUS "MPP_BUILD_FUZZER           : ${MPP_BUILD_FUZZER}")
message(STATUS "MPP_USE_FUZZER_DEFINITIONS : ${MPP_USE_FUZZER_DEFINITIONS}")
message(STATUS "MPP_BUILD_EXAMPLE          : ${MPP_BUILD_EXAMPLE}")
message(STATUS "MPP_BUILD_TESTS            : ${MPP_BUILD_TESTS}")
message(STATUS "MPP_BUILD_DOCS             : ${MPP_BUILD_DOCS}")

################# ADD PROJECTS + DOCS + TESTS #################
add_subdirectory(libmemplusplus)
if (MPP_ENABLE_COVERAGE)
	message(STATUS "[+] Building with code coverage support")
	target_compile_options(mpp PRIVATE --coverage -O0 -g -fno-inline)
	target_link_options(mpp INTERFACE --coverage)
endif()

if (MPP_BUILD_FUZZER)
	message(STATUS "[+] Building with fuzzer support!")
	message(STATUS "    WARNING: Library will be build with sanitizers + with insecure defines!")
	enable_testing()
	add_subdirectory(fuzzer)
endif()

if (MPP_BUILD_EXAMPLE)
	message(STATUS "[+] Building with example project")
	add_subdirectory(example_project)
endif()

if (MPP_BUILD_TESTS)
	message(STATUS "[+] Building with tests")
	enable_testing()

	add_subdirectory(libraries/Catch2)
	add_subdirectory(tests)

	if (MPP_ENABLE_COVERAGE)
		target_compile_options(unit_tests PRIVATE --coverage -O0 -g -fno-inline)
		target_link_options(unit_tests INTERFACE --coverage)
	endif()
endif()

if (MPP_BUILD_DOCS)
	message(STATUS "[+] Building with documentation")
	add_subdirectory(docs)
endif()

################# CLANG FORMAT / CLANG-TIDY #################
include(cmake/clang-cxx-dev-tools.cmake)