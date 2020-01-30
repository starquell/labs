#include <chrono>
#include <thread>
#include <functional>

time_t benchAlgorithm (std::function <void ()> const &someSort) {

    using namespace std::chrono;

    auto begin = steady_clock::now();
    someSort ();
    auto end = steady_clock::now();

    return duration_cast<milliseconds>(end - begin).count();
}