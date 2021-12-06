cmake_minimum_required(VERSION 3.20)
project(cache)

set(CMAKE_CXX_STANDARD 17)

add_executable(cache main.cpp Common.h Solution.cpp test_runner.h)
