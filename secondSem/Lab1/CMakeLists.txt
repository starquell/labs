cmake_minimum_required(VERSION 3.13)
project(Lab1)

set(CMAKE_CXX_STANDARD 14)

include_directories("./texttable")
add_executable(Lab1 main.cpp databaseFunctions.h benchmarkFunctions.h texttable/monster.h)
target_link_libraries(${PROJECT_NAME} PRIVATE stdc++fs)