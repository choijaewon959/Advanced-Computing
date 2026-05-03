cmake_minimum_required(VERSION 4.1)
project(Phase5)

set(CMAKE_CXX_STANDARD 20)

add_executable(Phase5 main.cpp
        OrderBook.cpp
        OrderBook.h
        Timer.cpp
        Timer.h
        OptimizedOrderBook.cpp
        OptimizedOrderBook.h)

add_executable(tests
        test_accuracy.cpp)