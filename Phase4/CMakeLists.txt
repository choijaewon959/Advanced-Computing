cmake_minimum_required(VERSION 4.1)
project(Phase4)

set(CMAKE_CXX_STANDARD 20)

add_executable(Phase4 main.cpp
        MarketData.cpp
        MarketData.h
        OrderBook.cpp
        OrderBook.h
        Order.h
        Timer.h
        OrderManager.cpp
        OrderManager.h
        MatchingEngine.cpp
        MatchingEngine.h
        TradeLogger.cpp
        TradeLogger.h
)

add_executable(test_latency test_latency.cpp
        Timer.cpp
        TradeLogger.cpp
        MarketData.cpp
)

target_include_directories(test_latency PRIVATE include)