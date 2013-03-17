cmake_minimum_required (VERSION 2.6)
project (beaglebone_servo)

include_directories("./include")

add_library(${PROJECT_NAME} src/servo.cpp)

add_executable(test1 src/test1.cpp)
target_link_libraries(test1 ${PROJECT_NAME})
