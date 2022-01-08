cmake_minimum_required(VERSION 3.22)
project(mython_lexer)

set(CMAKE_CXX_STANDARD 17)

add_executable(mython_lexer lexer_test.cpp lexer.cpp lexer.h test_runner.h)
