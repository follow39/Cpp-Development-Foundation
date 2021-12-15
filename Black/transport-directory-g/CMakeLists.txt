cmake_minimum_required(VERSION 3.20)
project(transport_directory_g)

set(CMAKE_CXX_STANDARD 17)

add_executable(transport_directory_g main.cpp descriptions.cpp json.cpp render.cpp requests.cpp
        sphere.cpp transport_catalog.cpp transport_router.cpp utils.cpp svg.cpp)
