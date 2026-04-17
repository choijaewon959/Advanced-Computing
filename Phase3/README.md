# Local Order Book and Core Trading Infrastructure

## Overview

This project implements a simple event-driven trading system core in C++. It is designed to:

- maintain a local top-of-book market view
- track active orders and execution updates
- run a rule-based trading strategy
- log system activity to `output.log`

The system is built in a modular way so that market data handling, order tracking, strategy logic, and logging are separated clearly.

---

## Architecture

```text
+-------------------+
|  sample_feed.txt  |
+-------------------+
          |
          v
+-------------------+
|    Feed Parser    |
+-------------------+
          |
          v
+-------------------+
|     FeedEvent     |
+-------------------+
          |
          v
+-------------------+        +-------------------+
|  MarketSnapshot   | -----> |  Strategy Logic   |
+-------------------+        +-------------------+
          |                            |
          |                            v
          |                   +-------------------+
          +-----------------> |   OrderManager    |
                              +-------------------+
                                        |
                                        v
                              +-------------------+
                              |    output.log     |
                              +-------------------+
```
---
## Project Structure

```text
.
├── CMakeLists.txt
├── .gitignore
├── main.cpp
├── feed_parser.h
├── market_snapshot.h
├── market_snapshot.cpp
├── order_manager.h
├── order_manager.cpp
├── strategy.h
├── logger.h
├── sample_feed.txt
├── output.log
├── README.md
└── cmake-build-debug/
```

---

## Output
All the trading actions including price updates, order placements, and fills are logged in output.log. See *output.log* for more details.
```output.log
[INFO] [MARKET] BEST ASK: 100.180000*30
[INFO] [Strategy] Placed SELL order at 100.150000 (ID [5])
[INFO] [NEW ASK] 100.180000 x 0
[INFO] [MARKET] BEST ASK: 100.200000*250
[INFO] [Strategy] Placed SELL order at 100.150000 (ID [6])
[INFO] [NEW ASK] 100.250000 x 200
[INFO] [MARKET] BEST ASK: 100.200000*250
[INFO] [Strategy] Placed SELL order at 100.150000 (ID [7])
[INFO] [EXECUTION] Order 1 filled: 10
[INFO] [ORDER] order 1 completed and removed
```
---
## How to Run
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

