cmake_minimum_required(VERSION 3.20)
project(booking_raii)

set(CMAKE_CXX_STANDARD 17)

add_executable(booking_raii main.cpp new_trip_manager.h new_booking_providers.h
        old_trip_manager.h old_booking_providers.h test_runner.h booking.h)
