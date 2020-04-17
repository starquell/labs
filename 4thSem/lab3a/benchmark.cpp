#include "QuickSort.hpp"
#include "TestUtils.hpp"

#include "benchmark/benchmark.h"

#include <algorithm>
#include <execution>

namespace {

    void default_sort (benchmark::State& state) {
        auto vec = lab::random_vector(state.range(0), {0, state.range(0)});

        for (auto _ : state) {
            lab::quick_sort(vec.begin(), vec.end());
        }
    }

    void stl_sort (benchmark::State& state) {
        auto vec = lab::random_vector(state.range(0), {0, state.range(0)});

        for (auto _ : state) {
            std::sort(vec.begin(), vec.end());
        }
    }

    void parallel_sort (benchmark::State& state) {
        auto vec = lab::random_vector(state.range(0), {0, state.range(0)});

        for (auto _ : state) {
            lab::quick_sort(vec.begin(), vec.end(), lab::ExecutionPolicy::Parallel);
        }
    }

    void parallel_stl (benchmark::State& state) {
        auto vec = lab::random_vector(state.range(0), {0, state.range(0)});

        for (auto _ : state) {
            std::sort(std::execution::par_unseq, vec.begin(), vec.end());
        }
    }
}

BENCHMARK(stl_sort)->RangeMultiplier(10)->Range(100, 10000000)->Unit(benchmark::kMillisecond);
BENCHMARK(default_sort)->RangeMultiplier(10)->Range(100, 10000000)->Unit(benchmark::kMillisecond);
BENCHMARK(parallel_stl)->RangeMultiplier(10)->Range(100, 10000000)->Unit(benchmark::kMillisecond);
BENCHMARK(parallel_sort)->RangeMultiplier(10)->Range(100, 10000000)->Unit(benchmark::kMillisecond);


BENCHMARK_MAIN();

