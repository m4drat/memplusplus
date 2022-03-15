project(benchmarks)

# Add a testing executable
add_executable(benchmarks 
    bench_main.cpp
    benchmark_mpp.cpp
)

target_link_libraries(${PROJECT_NAME}
    PRIVATE
    lib::mpp
    PRIVATE
    benchmark::benchmark
)

add_test(benchmark ${CMAKE_RUNTIME_OUTPUT_DIRECTORY}/${PROJECT_NAME})