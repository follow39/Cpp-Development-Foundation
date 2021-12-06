cmake_minimum_required(VERSION 3.20)
project(comment_server)

set(CMAKE_CXX_STANDARD 17)

add_executable(comment_server main.cpp test_runner.h)
