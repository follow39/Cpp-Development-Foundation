cmake_minimum_required(VERSION 3.10)
project(yellow_pages)

set(CMAKE_CXX_STANDARD 17)

find_package(Protobuf REQUIRED)
find_path(TEST_RUNNER_PATH test_runner.h)
#find_path(/Users/artemivanov/Documents/GitHub/Cpp-Development-Foundation/dev-lib/ test_runner.h)

include_directories(${Protobuf_INCLUDE_DIRS})
include_directories(${CMAKE_CURRENT_BINARY_DIR})
include_directories(${TEST_RUNNER_PATH})
#include_directories(/Users/artemivanov/Documents/GitHub/Cpp-Development-Foundation/dev-lib/)

protobuf_generate_cpp(
    PROTO_SRCS
    PROTO_HDRS
    protos/address.proto
    protos/company.proto
    protos/name.proto
    protos/phone.proto
    protos/provider.proto
    protos/signal.proto
    protos/url.proto
    protos/working_time.proto
)

add_executable(yellow_pages ${PROTO_SRCS} ${PROTO_HDRS} test.cpp merge.cpp)
target_link_libraries(yellow_pages ${Protobuf_LIBRARIES})
