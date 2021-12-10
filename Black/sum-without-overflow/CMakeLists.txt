cmake_minimum_required(VERSION 3.22)
project(sum_without_owerflow)

set(CMAKE_CXX_STANDARD 17)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -fsanitize=undefined")

add_executable(sum_without_owerflow main.cpp)
