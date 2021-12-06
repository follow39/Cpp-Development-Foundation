cmake_minimum_required(VERSION 3.20)
project(textures)

set(CMAKE_CXX_STANDARD 17)

add_executable(textures main.cpp Textures.cpp Textures.h Common.h Solution.cpp test_runner.h)
