cmake_minimum_required(VERSION 3.20)
project(load_from_json)

set(CMAKE_CXX_STANDARD 17)

add_executable(load_from_json main.cpp json.cpp json.h test_runner.h)
