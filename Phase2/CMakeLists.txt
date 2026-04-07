cmake_minimum_required(VERSION 3.16)
project(Phase2)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

find_package(Threads REQUIRED)

add_executable(hft_server hft_server.cpp)
target_link_libraries(hft_server PRIVATE Threads::Threads)

add_executable(hft_client hft_client.cpp)
target_link_libraries(hft_client PRIVATE Threads::Threads)