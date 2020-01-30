#include <iostream>
#include <string>
#include "timsort.h"
#include "benchmarking.h"
#include <stack>
#include "cpp-TimSort-master/timsort.hpp"


//#define VECTOR


int main (int argc, char **argv) {
    constexpr int size = 500000;
#ifdef VECTOR
    std::vector <int> arr (size);
#else
    int arr [size];
#endif

    for (auto &i : arr)
        i = rand() % 10000;

    for (auto &i : arr)
        std::cout << i << "gg" << ' ';


    std::cout << "\n\n\n";


    auto elapsed = benchAlgorithm ([&arr] () mutable {
        gfx::timsort (arr, arr + size);
    });


    for (auto &i : arr)
        std::cout << i << ' ';

    std::cout << "\n\n\n\n\n" << elapsed;

    return 0;
}