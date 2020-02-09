cmake_minimum_required(VERSION 3.15)
project(lab1)

set(CMAKE_CXX_STANDARD 17)

find_package(benchmark REQUIRED)

set(CMAKE_CXX_FLAGS_DEBUG "-O3")

option(ENABLE_TEST "if OFF - tests is enabled, else - benchmark" OFF)
if (ENABLE_TEST)
    add_executable(lab1 test.cpp)
else()
    add_executable(lab1 benchmark.cpp)
    target_link_libraries(lab1 benchmark::benchmark)
endif()