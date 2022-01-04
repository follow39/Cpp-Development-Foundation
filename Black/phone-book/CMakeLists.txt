cmake_minimum_required(VERSION 3.20)
project(phone_book)

set(CMAKE_CXX_STANDARD 17)

set(ENV${TEST_RUNNER_PATH} "/Users/artemivanov/Documents/GitHub/Cpp-Development-Foundation/dev-lib/")
find_path(/Users/artemivanov/Documents/GitHub/Cpp-Development-Foundation/dev-lib/ test_runner.h)
include_directories(/Users/artemivanov/Documents/GitHub/Cpp-Development-Foundation/dev-lib/)
#find_path(TEST_RUNNER_PATH test_runner.h)
#include_directories(${TEST_RUNNER_PATH})

find_package(Protobuf REQUIRED)
include_directories(${Protobuf_INCLUDE_DIRS})
include_directories(${CMAKE_CURRENT_BINARY_DIR})

protobuf_generate_cpp(PROTO_SRCS PROTO_HDRS contact.proto)
add_executable(main main.cpp ${PROTO_SRCS} ${PROTO_HDRS} iterator_range.h phone_book.h phone_book.cpp)
target_link_libraries(main ${Protobuf_LIBRARIES})
