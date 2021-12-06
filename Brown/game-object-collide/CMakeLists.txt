cmake_minimum_required(VERSION 3.20)
project(game_object_collide)

set(CMAKE_CXX_STANDARD 17)

add_executable(game_object_collide main.cpp geo2d.cpp geo2d.h game_object.h test_runner.h)
