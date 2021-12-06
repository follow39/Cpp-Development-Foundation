cmake_minimum_required(VERSION 3.20)
project(load_from_ini)

set(CMAKE_CXX_STANDARD 17)

add_executable(load_from_ini main.cpp ini.cpp ini.h test_runner.h)
