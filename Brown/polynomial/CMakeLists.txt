cmake_minimum_required(VERSION 3.20)
project(polynomial)

set(CMAKE_CXX_STANDARD 17)

add_executable(polynomial main.cpp test_runner.h profile.h)
