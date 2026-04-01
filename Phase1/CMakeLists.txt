cmake_minimum_required(VERSION 3.20)

project(Phase1)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

add_executable(Phase1
        main.cpp
        calculation.cpp
        calculation.h
        benchmark.cpp
        benchmark.h
)

add_executable(calculation_test
        calculation_test.cpp
        calculation.cpp
        calculation.h
        benchmark.cpp
        benchmark.h
)

target_compile_options(Phase1 PRIVATE -O3 -g)
target_include_directories(Phase1 PRIVATE ..)
target_include_directories(calculation_test PRIVATE ..)