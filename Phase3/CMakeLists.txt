cmake_minimum_required(VERSION 4.1)
project(Phase3)

set(CMAKE_CXX_STANDARD 20)

add_executable(Phase3 main.cpp
        market_snapshot.cpp
        market_snapshot.h
        order_manager.cpp
        order_manager.h
        feed_parser.h)
