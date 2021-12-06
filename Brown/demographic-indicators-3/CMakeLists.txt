cmake_minimum_required(VERSION 3.20)
project(demographic_indicators_3)

set(CMAKE_CXX_STANDARD 17)

add_executable(demographic_indicators_3 main.cpp bug1_bad.cpp bug2_bad.cpp bug3_bad.cpp
        bug4_bad.cpp bug5_bad.cpp bug6_bad.cpp test_runner.h)
