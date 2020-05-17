cmake_minimum_required(VERSION 3.10)

set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} ${CMAKE_CURRENT_SOURCE_DIR}/cmake)
set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/binaries/lib)
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/binaries/lib)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/binaries/bin)
project(memplusplus VERSION 1.0.0 LANGUAGES CXX)

# enable CTest testing
enable_testing()

option(BUILD_SHARED_LIBS "Request build of shared libraries." OFF)
option(CMAKE_EXPORT_COMPILE_COMMANDS "Request generate of json file with all build commands." ON)

if(NOT BUILD_SHARED_LIBS)
	set(STATIC_POSTFIX "s")
endif()

set(CMAKE_CXX_STANDARD 17)

# update all includes
set(EXAMPLE_PROJECT_INCLUDES ${ALL_INCLUDE_DIRECTORIES} ${PROJECT_SOURCE_DIR}/example_project/include)
set(FUZZING_HARNESS_INCLUDES ${ALL_INCLUDE_DIRECTORIES} ${PROJECT_SOURCE_DIR}/fuzzing_harness/include)
set(LIBMEMPLUSPLUS_INCLUDES ${ALL_INCLUDE_DIRECTORIES} ${PROJECT_SOURCE_DIR}/libmemplusplus/include)

add_subdirectory(example_project)
add_subdirectory(fuzzing_harness)
add_subdirectory(libmemplusplus)
add_subdirectory(docs)

# add clang-format and clang-tidy
include(cmake/clang-cxx-dev-tools.cmake)