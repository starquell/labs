#define CATCH_CONFIG_MAIN

#include "../Catch2/single_include/catch2/catch.hpp"
#include "src/Queue.hpp"

TEST_CASE("LinkedListImpl", "[list]") {

    using namespace lab;
    Queue<int, Storage::LinkedList> q = {1, 5, 23, 232, 11};

    REQUIRE(q.front() == 1);
    REQUIRE(q.pop() == 1);
    q.push(4343);
    REQUIRE(q.front() == 5);
    REQUIRE(!q.empty());
}

TEST_CASE("Dynamic storage", "[dynamic]") {

    lab::Queue<int, lab::Storage::Dynamic> q = {1, 5, 23, 232, 11};

    REQUIRE(q.front() == 1);
    REQUIRE(q.pop() == 1);
    q.push(4343);

    REQUIRE(q.pop() == 5);
    REQUIRE(q.pop() == 23);
    REQUIRE(q.pop() == 232);
    REQUIRE(q.pop() == 11);
    REQUIRE(q.front() == 4343);
    REQUIRE(!q.empty());
}

TEST_CASE("Static storage", "[static]") {

    lab::Queue<int, lab::Storage::Static, 5> q = {1, 5, 23, 232, 11};

    REQUIRE(q.front() == 1);
    REQUIRE(q.pop() == 1);
    q.push(4343);

    REQUIRE(q.pop() == 5);
    REQUIRE(q.pop() == 23);
    REQUIRE(q.pop() == 232);
    REQUIRE(q.pop() == 11);
    REQUIRE(q.front() == 4343);
    REQUIRE(!q.empty());
}


