cmake_minimum_required(VERSION 3.20)
project(transport_directory_j)

set(CMAKE_CXX_STANDARD 17)

#set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -fsanitize=address -fno-omit-frame-pointer -O0")
#set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -fsanitize=leak")
#set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -fsanitize=undefined")
#set(CMAKE_EXE_LINKER_FLAGS "${CMAKE_EXE_LINKER_FLAGS} -fsanitize=undefined")
#set(CMAKE_CXX_FLAGS_DEBUG "-DEBUG")

add_executable(transport_directory_g main.cpp descriptions.cpp json.cpp requests.cpp
        sphere.cpp transport_catalog.cpp transport_router.cpp utils.cpp svg.cpp map_renderer.cpp)
