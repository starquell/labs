#define CATCH_CONFIG_MAIN

#include "Catch2/single_include/catch2/catch.hpp"
#include "Arraybased.h"
#include "Listbased.h"
#include "Vectorbased.h"

TEST_CASE("LinkedListImpl", "[list]") {

    Listbased<int> q;
    q.push(1);
    q.push(5);
    q.push(23);
    q.push(232);
    q.push(11);

    REQUIRE(q.getFront() == 1);
    q.pop();
    q.push(4343);
    REQUIRE(q.getFront() == 5);
    REQUIRE(!q.isEmpty());
}

TEST_CASE("Dynamic storage", "[dynamic]") {

    Vectorbased<int> q;
    q.push(1);
    q.push(5);
    q.push(23);
    q.push(232);
    q.push(11);

    REQUIRE(q.getFront() == 1);
    q.pop();
    q.push(4343);
    REQUIRE(q.getFront() == 5);
    REQUIRE(!q.isEmpty());
}

TEST_CASE("Static storage", "[static]") {

   Arraybased<int, 5> q;

    q.push(1);
    q.push(5);
    q.push(23);
    q.push(232);
    q.push(11);

    REQUIRE(q.getFront() == 1);
    q.pop();
    q.push(4343);
    REQUIRE(q.getFront() == 5);
    REQUIRE(!q.isEmpty());
}


