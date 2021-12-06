cmake_minimum_required(VERSION 3.20)
project(transport_directory_e)

set(CMAKE_CXX_STANDARD 17)

add_executable(transport_directory_e main.cpp bus.h json.cpp json.h manager.h stop.h
        graph.h router.h path.h test_runner.h)
