#define CATCH_CONFIG_MAIN

#include "QuickSort.hpp"
#include "TestUtils.hpp"

#include "catch.hpp"

#include <algorithm>
#include <functional>

TEST_CASE ("Single thread", "[single]") {

    SECTION("Less comparator") {

        for (auto i = 100; i <= 1000000; i *= 100) {
            auto vec = lab::random_vector(i, {0, i});

            lab::quick_sort(vec.begin(), vec.end());
            REQUIRE(std::is_sorted(vec.begin(), vec.end()));
        }
    }

    SECTION("Greater comparator") {

        for (auto i = 100; i <= 1000000; i *= 100) {
            auto vec = lab::random_vector(i, {0, i});

            lab::quick_sort(vec.begin(), vec.end(), std::greater{});
            REQUIRE(std::is_sorted(vec.begin(), vec.end(), std::greater{}));
        }
    }
}


TEST_CASE ("Parallel", "[parallel]") {

    SECTION("Less comparator") {

        for (auto i = 10000; i <= 100000; i *= 10) {
            auto vec = lab::random_vector(i, {0, i});

            lab::quick_sort(vec.begin(), vec.end(), lab::ExecutionPolicy::Parallel);
            REQUIRE(std::is_sorted(vec.begin(), vec.end()));
        }
    }

    SECTION("Greater comparator") {

        for (auto i = 10000; i <= 100000; i *= 10) {
            auto vec = lab::random_vector(i, {0, i});

            lab::quick_sort(vec.begin(), vec.end(), lab::ExecutionPolicy::Parallel, std::greater{});
            REQUIRE(std::is_sorted(vec.begin(), vec.end(), std::greater{}));
        }
    }
}
