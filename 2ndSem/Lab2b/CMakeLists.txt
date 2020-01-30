cmake_minimum_required(VERSION 3.13)
project(Lab2b)

set(CMAKE_CXX_STANDARD 14)

add_executable(Lab2b main.cpp)
find_package(Threads REQUIRED)
target_link_libraries(${CMAKE_PROJECT_NAME} Threads::Threads)