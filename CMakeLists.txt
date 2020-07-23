cmake_minimum_required(VERSION 3.13)

################# SET GLOBAL VARIABLES #################
set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} ${CMAKE_CURRENT_SOURCE_DIR}/cmake)
set(CMAKE_CXX_STANDARD 17)

################# DEFINE PROJECT #################
project(memplusplus LANGUAGES CXX)

################# OPTIONS #################
option(MPP_BUILD_SHARED_LIBS "Request build of shared libraries" ON)
option(MPP_BUILD_FUZZER "Build mpp fuzzing harness" OFF)
option(MPP_BUILD_EXAMPLE "Build mpp example project" OFF)
option(MPP_BUILD_TESTS "Build mpp tests" OFF)
option(MPP_BUILD_DOCS "Build mpp documentation" OFF)
# option(MPP_SECURE "Build mpp in secure mode" OFF)
option(CMAKE_EXPORT_COMPILE_COMMANDS "Request generate of json file with all build commands" ON)

message(STATUS "##################### OPTIONS #####################")
message(STATUS "MPP_BUILD_SHARED_LIBS: ${MPP_BUILD_SHARED_LIBS}")
message(STATUS "MPP_BUILD_FUZZER: ${MPP_BUILD_FUZZER}")
message(STATUS "MPP_BUILD_EXAMPLE: ${MPP_BUILD_EXAMPLE}")
message(STATUS "MPP_BUILD_TESTS: ${MPP_BUILD_TESTS}")
message(STATUS "MPP_BUILD_DOCS: ${MPP_BUILD_DOCS}")
# message(STATUS "MPP_SECURE: ${MPP_SECURE}")

# if (MPP_SECURE MATCHES "ON")
# 	message(STATUS "Building in secure mode: MPP_SECURE=1")
# 	list(APPEND MPP_DEFINES MPP_SECURE=1)
# endif()

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