#include "src/Queue.hpp"

#include <benchmark/benchmark.h>

auto dynamicQueue = lab::Queue<int, lab::Storage::Dynamic>{};
auto staticQueue = lab::Queue<int, lab::Storage::Static, 1000000>{};
auto listQueue = lab::Queue<int, lab::Storage::LinkedList>{};

template <typename Queue>
static void pushBM (benchmark::State& state, Queue& queue) {
    for (auto _ : state)
        queue.push(50);
}

BENCHMARK_CAPTURE(pushBM, dynamicPushBM, dynamicQueue)->Iterations(1000000);
BENCHMARK_CAPTURE(pushBM, staticPushBM, staticQueue)->Iterations(1000000);
BENCHMARK_CAPTURE(pushBM, listPushBM, listQueue)->Iterations(1000000);

template <typename Queue>
static void popBM (benchmark::State& state, Queue& queue) {
    for (auto _ : state)
        queue.pop();
}

BENCHMARK_CAPTURE(popBM, dynamicPopBM, dynamicQueue)->Iterations(1000000);
BENCHMARK_CAPTURE(popBM, staticPopBM, staticQueue)->Iterations(1000000);
BENCHMARK_CAPTURE(popBM, listPopBM, listQueue)->Iterations(1000000);


BENCHMARK_MAIN();


