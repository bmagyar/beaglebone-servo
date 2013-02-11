cmake_minimum_required (VERSION 2.6)
project (beaglebone-servo)

add_library(servo servo.cpp)

add_executable(test1 test1.cpp)
target_link_libraries(test1 servo)
