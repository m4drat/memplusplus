# mem++

[![codecov](https://codecov.io/gh/m4drat/memplusplus/branch/master/graph/badge.svg)](https://codecov.io/gh/m4drat/memplusplus)
![build](https://github.com/m4drat/memplusplus/workflows/C/C++%20CI/badge.svg?branch=master)

C++ memory allocator with smart features, such as garbage collection, and heap compacting.

## Current version

Current library version: 2.3.5

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

    find_package(mpp 2.3.5 REQUIRED)

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

3. After that you will be able to include library headers in your sources like that: `#include "mpplib/mpp.hpp"`

## Build options

Global options:

- `MPP_ENABLE_COVERAGE` - build with code coverage support

- `MPP_BUILD_FUZZER` - build fuzzer project (will build library with sanitizers)

- `MPP_BUILD_EXAMPLE` - build example project

- `MPP_BUILD_TESTS` - build tests

- `MPP_BUILD_DOCS` - build documentation

- __currently not supported__. `MPP_BUILD_BENCMARK` - build benchmarks

Library options:

- `MPP_BUILD_SHARED_LIBS` - build shared or static libraries

- `MPP_FULL_DEBUG` - build in full debug mode (adds extended security checks in debug build)

- `MPP_SECURE` - build in secure mode with additional security features

- `MPP_PROFILE` - enable profiling instrumentation

- `MPP_SANITIZERS` - add sanitizers to the build

- `MPP_COLOUR_DEBUG_OUTPUT` - Add colours to debug output

- `MPP_STATS` - Add statistics instrumentation.

## Environment options

- `MPP_DUMP_OBJECTS_GRAPH=1` - dump objects graph to file `objects.dot`, while performing `GC::Collect()` (only exists in debug mode)

- `MPP_SHOW_STATISTICS=1` - display statistics after program termination (should be built with `MPP_STATS` set to ON)

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
    GC::GetInstance().Collect();
    ```

## Debugging / profiling library

If you want to use backtrace functionality add this flags to your project's CMakeLists.txt:

```cmake
target_compile_options(${PROJECT_NAME} PRIVATE -g -O0)
target_link_libraries(${PROJECT_NAME} PRIVATE lib::mpp -export-dynamic)
```

Memplusplus provides different debug-like features, such as: data visualizers, profiler, statistics collector.

- Data visualizers:
  
  In Debug builds you are able to dump .dot representation of ChunkTreap and GcGraph (only using specific environment variable). Later you can "render" this .dot files using dot from graphviz.  

  - ChunkTreap visualizer

    How to dump ChunkTreap in code (don't forget to redirect program output to file treap.dot):

    ```c++
    // 1. Get the arena you want to dump the tree for
    Arena* tmpArena = MemoryAllocator::GetArenaList()[0]

    // 2. Extract ChunkTreap from this arena, and dump it
    // (in this example everything was dumped to std::cout).
    tmpArena->freedChunks.GenerateGraphvizLayout(std::cout);
    ```

    How to generage .svg file with dot:

    ```bash
    dot -Tsvg treap.dot -o treap.svg
    ```

    After that you will get .svg file with your freed chunks treap:
    ![treap](./additional_info/images/treap.svg)

  - GcGraph visualizer

    Visualization of GcGraph is much simplier. Just build library in Debug mode, and set MPP_DUMP_OBJECTS_GRAPH=1 before running target app. On each GC cycle it will dump objects graph to file "objects_cycle\<current cycle number\>.dot". Then just generate .svg file with dot.

    ```bash
    dot -Tsvg objects_cycle<N>.dot -o objects_cycle<N>.svg
    ```

    For example, for this code (it creates simple linked list and tree):

    ```c++
    // Linked List node
    struct Node {
        uint32_t data;
        SharedGcPtr<Node> prev;
        SharedGcPtr<Node> next;

        Node(uint32_t t_data, SharedGcPtr<Node> t_p, SharedGcPtr<Node> t_n)
            : data{t_data}, prev{t_p}, next{t_n}
        {
        }
    };

    // Create Linked List
    SharedGcPtr<Node> n1 = MakeSharedGcPtr<Node>(1, nullptr, nullptr);
    SharedGcPtr<Node> n2 = MakeSharedGcPtr<Node>(2, nullptr, nullptr);
    SharedGcPtr<Node> n3 = MakeSharedGcPtr<Node>(3, nullptr, nullptr);
    SharedGcPtr<Node> n4 = MakeSharedGcPtr<Node>(4, nullptr, nullptr);

    n1->prev = nullptr;
    n1->next = n2;

    n2->prev = n1;
    n2->next = n3;

    n3->prev = n2;
    n3->next = n4;

    n4->prev = n3;
    n4->next = nullptr;

    // Tree node
    struct TreeNode {
        uint32_t data;
        SharedGcPtr<TreeNode> left;
        SharedGcPtr<TreeNode> right;
        SharedGcPtr<TreeNode> up;

        TreeNode(uint32_t t_data, SharedGcPtr<TreeNode> t_left, SharedGcPtr<TreeNode> t_right, SharedGcPtr<TreeNode> t_up)
            : data{t_data}, left{t_left}, right{t_right}, up{t_up}
        {
        }
    };

    // Create Random tree
    SharedGcPtr<TreeNode> root = MakeSharedGcPtr<TreeNode>(0, nullptr, nullptr, nullptr);
    SharedGcPtr<TreeNode> treeNode1 = MakeSharedGcPtr<TreeNode>(1, nullptr, nullptr, nullptr);
    SharedGcPtr<TreeNode> treeNode2 = MakeSharedGcPtr<TreeNode>(2, nullptr, nullptr, nullptr);
    SharedGcPtr<TreeNode> treeNode3 = MakeSharedGcPtr<TreeNode>(3, nullptr, nullptr, nullptr);
    SharedGcPtr<TreeNode> treeNode4 = MakeSharedGcPtr<TreeNode>(4, nullptr, nullptr, nullptr);
    SharedGcPtr<TreeNode> treeNode5 = MakeSharedGcPtr<TreeNode>(5, nullptr, nullptr, nullptr);

    root->up = nullptr;
    root->left = treeNode1;
    root->right = treeNode2;

    treeNode1->up = root;
    treeNode1->left = nullptr;
    treeNode1->right = nullptr;

    treeNode2->up = root;
    treeNode2->left = treeNode3;
    treeNode2->right = treeNode4;

    treeNode3->up = treeNode2;
    treeNode3->left = nullptr;
    treeNode3->right = nullptr;

    treeNode4->up = treeNode2;
    treeNode4->left = treeNode5;
    treeNode4->right = nullptr;

    treeNode5->up = treeNode4;
    treeNode5->left = nullptr;
    treeNode5->right = nullptr;

    GC::GetInstance().Collect();
    ```

    You will get this objects graph.
    ![objects](./additional_info/images/objects.svg)

- Profiler

  Using build flag `MPP_PROFILE` you are able to build library with additional debugging feature, which will add specific instrumentation to the code, to collect timing information. After successfull build just run the aplication until it exits, and after that in your current working directory you should find file called "mpplib-profilng.json", which can be viewed using chrome tracing tool. To do it, open chrome, and navigate to chrome://tracing, after that drag and drop profiling trace to chrome window.

  Example output:

  ![profiler](./additional_info/images/profiling.png)

- Statistics collector

  This feature allows you to dump memory allocator statistics. To build library with support of this feature add `MPP_STATS` while building project. You can use this feature in 2 ways:

    1. In runtime using c++ API:

        - Example code to dump statistics:

            ```c++
            utils::Statistics::GetInstance().DumpStats(std::cout, true, false, false) << std::endl;

            ```

        - Example output:

            ```none
            +============= STATISTICS DUMP START =============+
            MPP: MIN_CHUNK_SIZE     : 32 bytes
            MPP: CHUNK_HEADER_SIZE  : 16 bytes
            MPP: DEFAULT_ARENA_SIZE : 32.000 MB
            MPP: PAGE_SIZE          : 4.000 KB
            ~~~~~~~~~~~~~~~~ All active arenas ~~~~~~~~~~~~~~~~
            -------------- Arena: 0x1ffaf50 --------------
            MPP - Total arena size           : 32.000 MB
            MPP - Currently Allocated Space  : 960.000 Bytes
            MPP - Amount of free memory      : 31.999 MB (99.9971% of total arena size)
            MPP - Amount of allocated memory : 960.000 Bytes (0.0029% of total arena size)
            MPP - Allocated memory == 0      : false
            MPP - Memory used for metadata   : 160.000 Bytes (16.6667% of currently allocated space)
            MPP - TopChunk                   : [0x7f329dd803c0](96, 33553472|InUse:1|PrevInUse:1)
            MPP - Arena begin pointer        : 0x7f329dd80000
            MPP - Arena end pointer          : 0x7f329fd80000
            MPP - Freed chunks nodes (0)
            MPP - Chunks in use (10)

            ~~~~~~~~~~~~~~~~~~ General stats ~~~~~~~~~~~~~~~~~~
            -----------------  Arena: 1  -----------------
            MPP - Total amount of allocated memory inside arena : 960.000 Bytes
            MPP - Total amount of freed memory inside arena     : 0 bytes
            MPP - total freed == total allocated                : false
            MPP - Biggest allocation size                       : 96.000 Bytes
            MPP - Smallest allocation size                      : 96.000 Bytes
            MPP - Full size of arena                            : 32.000 MB
            MPP - Arena was allocated for big chunk             : false
            MPP - Arena was allocated by GC                     : false

            -----------------  Arena: 2  -----------------
            MPP - Total amount of allocated memory inside arena : 960.000 Bytes
            MPP - Total amount of freed memory inside arena     : 0 bytes
            MPP - total freed == total allocated                : false
            MPP - Biggest allocation size                       : "No allocations have been made yet"
            MPP - Smallest allocation size                      : "No allocations have been made yet"
            MPP - Full size of arena                            : 32.000 MB
            MPP - Arena was allocated for big chunk             : false
            MPP - Arena was allocated by GC                     : true

            ~~~~~~~~~~~~~ Garbage Collector stats ~~~~~~~~~~~~~
            -----------------  Cycle: 1  -----------------
            GC - Time wasted inside   GC::Collect() : 2.0000 ms
            GC - Memory cleaned after GC::Collect() : 0 bytes
            GC - Total size of active objects       : 960.000 Bytes

            +============== STATISTICS DUMP END ==============+
            ```

    2. After program termination, setting environment variable MPP_SHOW_STATISTICS=1.  
        Important note. Runtime stats cannot be dumped using this approach.

        - Example output:

            ```none
            +============= STATISTICS DUMP START =============+
            MPP: MIN_CHUNK_SIZE     : 32 bytes
            MPP: CHUNK_HEADER_SIZE  : 16 bytes
            MPP: DEFAULT_ARENA_SIZE : 32.000 MB
            MPP: PAGE_SIZE          : 4.000 KB
            ~~~~~~~~~~~~~~~~~~ General stats ~~~~~~~~~~~~~~~~~~
            -----------------  Arena: 1  -----------------
            MPP - Total amount of allocated memory inside arena : 960.000 Bytes
            MPP - Total amount of freed memory inside arena     : 0 bytes
            MPP - total freed == total allocated                : false
            MPP - Biggest allocation size                       : 96.000 Bytes
            MPP - Smallest allocation size                      : 96.000 Bytes
            MPP - Full size of arena                            : 32.000 MB
            MPP - Arena was allocated for big chunk             : false
            MPP - Arena was allocated by GC                     : false

            -----------------  Arena: 2  -----------------
            MPP - Total amount of allocated memory inside arena : 960.000 Bytes
            MPP - Total amount of freed memory inside arena     : 0 bytes
            MPP - total freed == total allocated                : false
            MPP - Biggest allocation size                       : "No allocations have been made yet"
            MPP - Smallest allocation size                      : "No allocations have been made yet"
            MPP - Full size of arena                            : 32.000 MB
            MPP - Arena was allocated for big chunk             : false
            MPP - Arena was allocated by GC                     : true

            ~~~~~~~~~~~~~ Garbage Collector stats ~~~~~~~~~~~~~
            -----------------  Cycle: 1  -----------------
            GC - Time wasted inside   GC::Collect() : 2 ms
            GC - Memory cleaned after GC::Collect() : 0 bytes
            GC - Total size of active objects       : 960.000 Bytes

            +============== STATISTICS DUMP END ==============+
            ```

- Allocate/Deallocate hooks

  This feature allows you to install your hooks on Allocate and Deallocate. Example:

  ```c++
  // Lambda as an Allocate hook. Important, all hooks should be static!
  static std::function<void*(std::size_t)> allocHook = [&](std::size_t t_AllocSize) {
      mpp::MemoryAllocator::SetAllocateHook(nullptr);
      void* ptr = mpp::MemoryAllocator::Allocate(t_AllocSize);
      mpp::MemoryAllocator::SetAllocateHook(allocHook);
      std::cout << "[mpp] Allocate(" << t_AllocSize << ") -> ";
      mpp::Chunk::DumpChunk(std::cout, mpp::Chunk::GetHeaderPtr(ptr)) << std::endl;
      return ptr;
  };
  // Set actual Allocate hook.
  mpp::MemoryAllocator::SetAllocateHook(allocHook);

  // Lambda as an Deallocate hook. Important, all hooks should be static!
  static std::function<bool(void*)> deallocHook = [&](void* t_Addr) {
      mpp::MemoryAllocator::SetDeallocateHook(nullptr);
      bool res = mpp::MemoryAllocator::Deallocate(t_Addr);
      mpp::MemoryAllocator::SetDeallocateHook(deallocHook);
      std::cout << "[mpp] Deallocate(" << t_Addr << ") -> " << res << std::endl;
      return res;
  };
  // Set actual Deallocate hook.
  mpp::MemoryAllocator::SetDeallocateHook(deallocHook);
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
