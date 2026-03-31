cmake_minimum_required(VERSION 3.20)

project(HW1)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

add_executable(HW1
        main.cpp
)

target_include_directories(HW1 PRIVATE ..)
