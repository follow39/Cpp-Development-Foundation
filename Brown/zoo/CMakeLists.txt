cmake_minimum_required(VERSION 3.20)
project(zoo)

set(CMAKE_CXX_STANDARD 17)

add_executable(zoo main.cpp animals.h test_runner.h)
