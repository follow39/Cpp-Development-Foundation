cmake_minimum_required(VERSION 3.22)
project(Nucleotide)

set(CMAKE_CXX_STANDARD 17)

find_path(TEST_RUNNER_PATH test_runner.h)
include_directories(${TEST_RUNNER_PATH})

add_executable(Nucleotide nucleotide.h nucleotide_test.cpp)
