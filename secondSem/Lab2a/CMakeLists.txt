cmake_minimum_required(VERSION 3.13)
project(Lab2a)

set(CMAKE_CXX_STANDARD 14)

include_directories("./texttable")
add_executable(Lab2a main.cpp Arraybased.h Vectorbased.h Listbased.h)