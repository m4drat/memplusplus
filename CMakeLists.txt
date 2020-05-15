cmake_minimum_required(VERSION 3.10)

set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/binaries/lib)
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/binaries/lib)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/binaries/bin)
project(mempluspplus VERSION 1.0
					 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)

add_subdirectory(example_project)
add_subdirectory(fuzzing_harness)
add_subdirectory(libmemplusplus)