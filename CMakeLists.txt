cmake_minimum_required(VERSION 3.10)

set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} ${CMAKE_CURRENT_SOURCE_DIR}/cmake)
set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/binaries/lib)
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/binaries/lib)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/binaries/bin)
project(mempluspplus VERSION 1.0.0
					 LANGUAGES CXX)

option(BUILD_SHARED_LIBS "Request build of shared libraries." OFF)

if(NOT BUILD_SHARED_LIBS)
	set(STATIC_POSTFIX "s")
endif()

set(CMAKE_CXX_STANDARD 17)

add_subdirectory(example_project)
add_subdirectory(fuzzing_harness)
add_subdirectory(libmemplusplus)
add_subdirectory(docs)