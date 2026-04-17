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
[INFO] [Strategy] Placed SELL order at 100.200000 (ID [6])
[INFO] [MARKET] Added ASK level 100.250000 x 200
[INFO] [MARKET] Best ASK: 100.200000*250
[INFO] [Strategy] Placed SELL order at 100.200000 (ID [7])
[INFO] [MARKET] Added EXECUTION order 1 x 10
[INFO] [EXECUTION] Order 1 filled: 10
[INFO] [ORDER] order 1 completed and removed
[INFO] [MARKET] Added EXECUTION order 1 x 20
[INFO] [ORDER] fill ignored: order 1 not active
[INFO] [MARKET] Added BID level 100.170000 x 100
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

