cmake_minimum_required (VERSION 2.6)
project (beaglebone_servo)

include_directories("./include")

add_library(${PROJECT_NAME} src/servo.cpp)

add_library(motordriver src/motordriver.cpp src/motorpwm.cpp src/gpio.cpp src/pinmux.cpp)


add_executable(test1 src/test1.cpp)
target_link_libraries(test1 ${PROJECT_NAME})

add_executable(test3 src/test3.cpp)
target_link_libraries(test3 motordriver)
