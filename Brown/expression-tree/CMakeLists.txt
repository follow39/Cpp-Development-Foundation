cmake_minimum_required(VERSION 3.20)
project(expression_tree)

set(CMAKE_CXX_STANDARD 17)

add_executable(expression_tree main.cpp Common.h test_runner.h)
