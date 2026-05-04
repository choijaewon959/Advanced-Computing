## Phase 5: High-Frequency Trading (HFT) Order Book Implementations & Performance optimization

### Overview
The focus is on building a high-performance orderbook, simulating real world high frequency trading (HFT) conditions.
The goal is to create efficient, scalable, and optimized order book that can process millions of orders per second while maintaining low latency.

The project covers the following:

- implementation of an order book with string based order Ids
- performance analysis and measurement of execution times
- optimization of the order book to achieve the maximum speed and efficiency
- stress testing using generated orders to evaluate scalability 
- a report with execution time results and a performance chart

### Architecture

``````````
 --------              ------------------
|OrderBook|---------->|OptimizedOrderBook|
 --------              ------------------
      |      --------           |
      ----->|  main  |<----------
      |      --------
      |      
 ----------          ------------------
|  Timer   |        |  test_accuracy   |
 ----------          ------------------
``````````

### Project structure
```text
Phase5/
|--img
|--readME.md
|--CMakeLists.txt
|--report.md
|
|--main.cpp
|--OptimizedOrderBook.cpp
|--OptimizedOrderBook.h
|--OrderBook.cpp
|--OrderBook.h
|--Timer.cpp
|--Timer.h
|--test_accuracy.cpp

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
