cmake_minimum_required(VERSION 3.13)
project(Lab2a)

set(CMAKE_CXX_STANDARD 14)

find_package(benchmark REQUIRED)

include_directories("./texttable")
add_executable(Lab2a benchmark.cpp Arraybased.h Vectorbased.h Listbased.h)

target_link_libraries(Lab2a benchmark::benchmark)