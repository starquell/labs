#pragma once

#include <random>
#include <vector>

namespace lab {

    auto random_vector(std::size_t size, std::pair<int, int> range = {0, 10000}) {
        static std::mt19937 gen{std::random_device{}()};
        std::uniform_int_distribution<> dist(range.first, range.second);

        std::vector<int> vec;
        vec.reserve(size);

        for (auto i = 0; i < size; ++i) {
            vec.push_back(dist(gen));
        }
        return vec;
    }
}