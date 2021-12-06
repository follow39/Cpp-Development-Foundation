cmake_minimum_required(VERSION 3.20)
project(transport_directory_d)

set(CMAKE_CXX_STANDARD 17)

add_executable(transport_directory_d main.cpp json.cpp json.h bus.h stop.h manager.h)
