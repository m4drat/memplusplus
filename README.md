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

## Usage

1. Install latest build systems: `apt install cmake g++ clang`
2. Clone library sources: `git clone https://github.com/m4drat/memplusplus/`

### How to use the library internally
1. 

### How to use the library as a dependency (external project)
1. create `build` directory and enter it: `mkdir build && cd build`
2. run cmake: `cmake ..`
3. install targets: `cmake --build . --target install -j 8`


## Examples

## Performance comparisons

## Documentation

## Tests

## clang-format and clang-tidy