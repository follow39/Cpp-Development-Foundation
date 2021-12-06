cmake_minimum_required(VERSION 3.20)
project(stats_aggregator)

set(CMAKE_CXX_STANDARD 17)

add_executable(stats_aggregator main.cpp stats_aggregator_test.cpp
        stats_aggregator.cpp stats_aggregator.h test_runner.h)
