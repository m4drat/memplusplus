#include "benchmark/benchmark.h"
#include "mpplib/memory_allocator.hpp"


static void MppBenchmarkAllocate(benchmark::State& state) {
    for (auto _ : state)
    {
        benchmark::DoNotOptimize(mpp::MemoryAllocator::Allocate(128));
    }
}
BENCHMARK(MppBenchmarkAllocate)->Unit(benchmark::kMillisecond);