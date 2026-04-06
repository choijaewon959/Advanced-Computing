cmake_minimum_required(VERSION 4.1)
project(Phase2)

set(CMAKE_CXX_STANDARD 20)

add_executable(Phase2 main.cpp
        hft_client.cpp
        hft_server.cpp
)
