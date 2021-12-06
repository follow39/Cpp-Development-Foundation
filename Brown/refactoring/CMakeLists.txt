cmake_minimum_required(VERSION 3.20)
project(refactoring)

set(CMAKE_CXX_STANDARD 17)

add_executable(refactoring main.cpp json.cpp json.h xml.cpp xml.h test_runner.h)
