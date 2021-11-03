cmake_minimum_required(VERSION 3.20)
project(red_final)

set(CMAKE_CXX_STANDARD 17)

add_executable(red_final main.cpp
        parse.h parse.cpp profile.h
        search_server.h search_server.cpp
        iterator_range.h test_runner.h
        paginator.h)
