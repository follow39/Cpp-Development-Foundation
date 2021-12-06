cmake_minimum_required(VERSION 3.20)
project(banned_domains_tests)

set(CMAKE_CXX_STANDARD 17)

add_executable(banned_domains_tests main.cpp test_runner.h)
