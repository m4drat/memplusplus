cmake_minimum_required(VERSION 3.10)
project(memplusplus VERSION 1.0)

set(CMAKE_CXX_STANDARD 17)

add_subdirectory(example_project)
add_subdirectory(fuzzing_harness)
add_subdirectory(libmemplusplus)