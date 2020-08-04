# mem++

[![codecov](https://codecov.io/gh/m4drat/memplusplus/branch/master/graph/badge.svg)](https://codecov.io/gh/m4drat/memplusplus)
![build](https://github.com/m4drat/memplusplus/workflows/C/C++%20CI/badge.svg?branch=master)

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
        -DMPP_BUILD_SHARED_LIBS=ON \
    ```

2. compile and install:

    ```bash
    sudo cmake \
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

4. After that you will be able to include library headers in your sources like that: `#include <mpplib/mpp.hpp>`

### How to use the library internally

1. just copy whole directory with libmemplusplus to your project root directory.

2. In your project's cmake file add this:

    ```cmake
    add_subdirectory(libmemplusplus)
    target_link_libraries(<YOUR_PROJECT_NAME> PRIVATE lib::mpp)
    ```

3. After that you will be able to include library headers in your sources like that: `#include <mpplib/mpp.hpp>`

## Build options

Global options:

- `MPP_ENABLE_COVERAGE` - build with code coverage support

- __currently not supported__. `MPP_BUILD_FUZZER` - build fuzzer project

- `MPP_BUILD_EXAMPLE` - build example project

- `MPP_BUILD_TESTS` - build tests

- `MPP_BUILD_DOCS` - build documentation

- __currently not supported__. `MPP_BUILD_BENCMARK` - build documentation

Library options:

- `MPP_BUILD_SHARED_LIBS` - build shared or static libraries

- __currently not supported__. `MPP_FULL_DEBUG` - build in full debug mode (adds extended security checks in debug build)

- __currently not supported__. `MPP_SECURE` - build in secure mode with additional security features

- `MPP_PROFILE` - enable profiling instrumentation

- `MPP_SANITIZERS` - add sanitizers to the build

- `MPP_COLOUR_DEBUG_OUTPUT` - Add colours to debug output

## Environment options

- __currently not supported__. `MPP_DUMP_OBJECTS_GRAPH=1` - dump objects graph, while performing `GC::Collect()`

- __currently not supported__. `MPP_SHOW_STATISTICS=1` - display statistics after program terminates

## Examples

- Manual memory managment

    ```c++
    #include <mpplib/mpp.hpp>

    ...

    // will call constructor automatically, like new
    Object* obj = mpp::MemoryAllocator::Allocate<Object>(<constructor params>);
    // create raw pointer (behaves like malloc)
    void* ptr = mpp::MemoryAllocator::Allocate(128);

    ...

    // will call destructor automatically, like delete
    mpp::MemoryAllocator::Deallocate(obj);
    // only deallocates raw pointer (behaves like free)
    mpp::MemoryAllocator::Deallocate(ptr);
    ```

- Automatic memory managment

    ```c++
    #include <mpplib/mpp.hpp>

    ...

    // create smart pointer, that will automatically deallocate object, when needed
    mpp::SharedGcPtr<Object> object = mpp::MakeSharedGcPtr<Object>(<constructor params>);

    ...

    // collect all garbage + compact memory (can be called manually)
    GC::Collect();
    ```

## Performance comparisons

## Documentation

- Install doxygen, sphinx, breathe

- Configure:

    ```bash
    cmake \
        -S . \
        -B build \
        -DCMAKE_BUILD_TYPE=Release \
        -DMPP_BUILD_FUZZER=OFF \
        -DMPP_BUILD_EXAMPLE=OFF \
        -DMPP_BUILD_TESTS=OFF \
        -DBUILD_SHARED_LIBS=OFF \
        -DMPP_BUILD_DOCS=ON
    ```

- Build docs:

    ```bash
    cmake \
        --build build \
        -j 8
    ```

- Now docs can be found in "./build/docs/doxygen/html" or "./build/docs/sphinx"

## Tests

- Configure tests:

    ```bash
    cmake \
        -S . \
        -B build \
        -DCMAKE_BUILD_TYPE=Release \
        -DBUILD_SHARED_LIBS=OFF \
        -DMPP_BUILD_TESTS=ON
    ```

- Build tests:

    ```bash
    cmake \
        --build build \
        --target unit_tests \
        -j 8
    ```

- Run tests:

    ```bash
    cd build && ctest
    ```

## clang-format and clang-tidy

- install clang-tidy and clang-format

- Configure:

    ```bash
    cmake \
        -S . \
        -B build \
        -DCMAKE_BUILD_TYPE=Release
    ```

- Use clang-format:

    ```bash
    cmake \
        --build build \
        --target clang-format
    ```

- Use clang-tidy:

    ```bash
    cmake \
        --build build \
        --target clang-tidy
    ```
