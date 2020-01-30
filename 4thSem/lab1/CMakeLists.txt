cmake_minimum_required(VERSION 3.15)
project(lab1)

set(CMAKE_CXX_STANDARD 17)

find_package(benchmark REQUIRED)

add_executable(lab1 test.cpp)
target_link_libraries(lab1 benchmark::benchmark)