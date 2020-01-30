#include "Arraybased.h"
#include "Listbased.h"
#include "Vectorbased.h"

#include "benchmark/benchmark.h"

auto dynamicQueue = Vectorbased<int>{};
auto staticQueue = Arraybased<int, 1000000>{};
auto listQueue = Listbased<int>{};

template <typename Queue>
static void pushBM (benchmark::State& state, Queue& queue) {
    for (auto _ : state)
        queue.push(50);
}

BENCHMARK_CAPTURE(pushBM, dynamicPushBM, dynamicQueue)->Iterations(1000000);
BENCHMARK_CAPTURE(pushBM, staticPushBM, staticQueue)->Iterations(1000000);
//BENCHMARK_CAPTURE(pushBM, listPushBM, listQueue)->Iterations(1000000);

template <typename Queue>
static void popBM (benchmark::State& state, Queue& queue) {
    for (auto _ : state)
        queue.pop();
}

BENCHMARK_CAPTURE(popBM, dynamicPopBM, dynamicQueue)->Iterations(1000000);
BENCHMARK_CAPTURE(popBM, staticPopBM, staticQueue)->Iterations(1000000);
//BENCHMARK_CAPTURE(popBM, listPopBM, listQueue)->Iterations(1000000);


BENCHMARK_MAIN();

