cmake_minimum_required(VERSION 3.16)
project(lab3a)

set(CMAKE_CXX_STANDARD 17)

set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib)
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)

option(BUILD_BENCHMARK "Build benchmarks" ON)
option(BUILD_TESTS "Build tests" ON)

if (BUILD_BENCHMARK)
    set(CMAKE_BUILD_TYPE RELEASE)
    set(CMAKE_CXX_FLAGS_RELEASE "-O3")
    add_executable(benchmark benchmark.cpp)
    find_package(benchmark)
    target_link_libraries(benchmark benchmark::benchmark)
    target_link_libraries(benchmark pthread tbb)
endif()

if (BUILD_TESTS)
    add_executable(tests tests.cpp)
    target_link_libraries(tests pthread tbb)

endif()


add_executable(main main.cpp)
target_link_libraries(main pthread tbb)
