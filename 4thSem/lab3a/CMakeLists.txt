cmake_minimum_required(VERSION 3.16)
project(lab3a)

set(CMAKE_CXX_STANDARD 17)

option(RUN_BENCHMARK "Benchmark mode" ON)

if (RUN_BENCHMARK)
    add_executable(lab3a benchmark.cpp)
    find_package(benchmark)
    target_link_libraries(lab3a benchmark::benchmark)
    set(CMAKE_BUILD_TYPE RELEASE)
    set(CMAKE_CXX_FLAGS_RELEASE "-O3")
else()
    add_executable(lab3a main.cpp)
endif()

target_link_libraries(lab3a pthread tbb)


