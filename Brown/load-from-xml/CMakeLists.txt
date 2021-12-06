cmake_minimum_required(VERSION 3.20)
project(load_from_xml)

set(CMAKE_CXX_STANDARD 17)

add_executable(load_from_xml main.cpp xml.cpp xml.h test_runner.h)
