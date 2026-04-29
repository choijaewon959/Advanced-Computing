## Build & Benchmark a High-Frequency Trading System in C++
### Overview

This project implements a performance-optimized HFT trading system prototype in C++. The system will:

- Ingest market data

- Accept and manage client orders

- Match orders in a fast limit order book

- Report trades

- Measure and analyze tick-to-trade latency

- Apply advanced C++ concepts such as smart pointers, memory pools, templates, compile-time checks, and profiling tools.

- log info in "logs.log"

The design is modular and each component is separated clearly.
### System Architecture Overview

```text
|+------------------+    |    +-----------------+|    +------------------+|
| MarketDataFeed   |  -->  | OrderBook       | <---> | OrderManagement  |
+------------------+       +-----------------+       +------------------+
|     |
v     v
+-------------------+      +------------------+
| MatchingEngine    | ---> | TradeLogger      |
+-------------------+      +------------------+
```

### Project structure
```text
hft_project/
├── include/
│   ├── MarketData.hpp
│   ├── Order.hpp
│   ├── OrderBook.hpp
│   ├── MatchingEngine.hpp
│   ├── OrderManager.hpp
│   ├── TradeLogger.hpp
│   └── Timer.hpp
├── src/
│   ├── MarketData.cpp
│   ├── OrderBook.cpp
│   ├── MatchingEngine.cpp
│   ├── OrderManager.cpp
│   ├── TradeLogger.cpp
│   └── main.cpp
├── test/
│   └── test_latency.cpp
├── CMakeLists.txt
└── README.md
```
### Class-flow:
```text
Tick
-> MarketDataHandler::handleTick();

Order
-> OrderBook::placeOrder()
    -> buys / sells multimap
    -> buyIndex / sellIndex
    
MatchingEngine::matchOrders()
-> reads best bid/ask from OrderBook
-> updates order state (filled, partial etc)
-> creates trades
-> writes logs

Timer
-> measures tick-to-trade latency
```


### Output
All the trading actions inclusing best bid/asks and matched trades are logged in logs.log. See logs.log for more deta
```text
[INFO]Best bid 155.000000
[INFO]Best ask 150.000000
[INFO]matched trade for AAPL at: 150.000000*100 between: 0 and 1
```

### How to Run
Build
```Bash
mkdir build
cd build
cmake ..
make
```
Run
```Bash
./your_executable_name
```
