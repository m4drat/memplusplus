# mem++

C++ memory allocator with smart features, such as garbage collection, and heap compacting.

## Features

- Garbage Collecting
- Fast memory allocations (using bump allocators techniques)
- Fast free algorithms
- Advanced compacting algorithms

## Supported systems / limitations

- All Unix-like systems (where it is possible to use mmap)
- g++ or clang++ compilers
- currently supports only single-threaded applications
- currently you cant use manual memory management and GarbageCollection simultaneously (e.g. you should only use smart pointers, or manually control memory using Allocate and Deallocate)

## Usage

1. Install latest build systems: `apt install cmake g++ clang`
2. Clone library sources: `git clone https://github.com/m4drat/memplusplus/`

### How to use the library as a dependency (external project)

1. run cmake from root directory (memplusplus):

    ```bash
    cmake \
        -S . \
        -B build \
        -DCMAKE_BUILD_TYPE=Release \
        -DBUILD_SHARED_LIBS=ON \
    ```

2. compile and install:

    ```bash
    cmake \
        --build build \
        --target install \
        -j 8
    ```

3. After the library is installed, in your CMakeLists.txt use find_package, to actually use the library:

    ```cmake
    cmake_minimum_required(VERSION 3.13)
    project(<YOUR_PROJECT_NAME>)

    find_package(mpp 1.0.0 REQUIRED)

    add_executable(<YOUR_PROJECT_NAME> <YOUR_SOURCES>)
    target_link_libraries(<YOUR_PROJECT_NAME> PRIVATE mpp::mpp)
    ```

4. After that you will be able to include library headers in your sources like that: `#include <mpplib/mpp.h>`

### How to use the library internally

1. just copy whole directory with libmemplusplus to your project root directory.

2. In your project's cmake file add this:

    ```cmake
    add_subdirectory(libmemplusplus)
    target_link_libraries(<YOUR_PROJECT_NAME> PRIVATE lib::mpp)
    ```

3. After that you will be able to include library headers in your sources like that: `#include <mpplib/mpp.h>`

## Examples

## Performance comparisons

## Documentation

## Tests

## clang-format and clang-tidy
