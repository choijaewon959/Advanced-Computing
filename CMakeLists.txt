cmake_minimum_required(VERSION 3.20)

project(Advanced-Computing)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

add_executable(Advanced-Computing
        main.cpp
        calculation.cpp
        calculation.h
)

add_executable(calculation_test
        calculation_test.cpp
        calculation.cpp
        calculation.h
)

target_include_directories(Advanced-Computing PRIVATE ${CMAKE_CURRENT_SOURCE_DIR})
target_include_directories(calculation_test PRIVATE ${CMAKE_CURRENT_SOURCE_DIR})