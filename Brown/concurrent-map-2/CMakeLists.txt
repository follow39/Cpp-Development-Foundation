cmake_minimum_required(VERSION 3.20)
project(concurrent_map_2)

set(CMAKE_CXX_STANDARD 17)

add_executable(concurrent_map_2 main.cpp test_runner.h profile.h)
