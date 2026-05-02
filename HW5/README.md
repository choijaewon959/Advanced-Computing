# HW5 Performance Report

## Overview

This project implements and benchmarks several high-performance data structures and algorithms commonly used in trading systems:

1. Robin Hood Hash Table
2. Binary Max Heap / Priority Queue
3. SIMD Time Series Moving Average
4. Order Book with Fast ID Lookup and Price-Level Queries

The goal is to compare custom implementations against standard library alternatives and analyze their latency, memory behavior, and real-world applicability.

---

## Benchmark Results

### Part 1: Hash Table

| Operation | Custom Robin Hood Hash Table | `std::unordered_map` |
|---|-----------------------------:|---------------------:|
| Insert |                     `529 us` |            `1116 us` |
| Lookup |                     `324 us` |              `443us` |

### Part 2: Binary Heap

| Operation | Custom Max Heap | `std::priority_queue` |
|---|----------------:|----------------------:|
| Insert |        `109 us` |              `108 us` |
| Pop |        `828 us` |             `1312 us` |

### Part 3: Time Series Moving Average

| Operation | Naive Version | Optimized SIMD Version |
|---|--------------:|-----------------------:|
| Moving Average |       `75 us` |                `48 us` |

The SIMD version used ARM NEON because the benchmark was run on Apple Silicon. AVX2/SSE are only available on x86/x64 architectures.

### Part 4: Order Book

| Operation | Data Structure Used | Complexity |
|---|---|---:|
| Add Order | `unordered_map` + `map` | `O(log P)` |
| Modify Order | `unordered_map` | `O(1)` average |
| Delete Order | `unordered_map` + price level vector | `O(k)` |
| Query Price Level | `map` | `O(log P + k)` |
| Best Bid | `map.rbegin()` | `O(1)` |
| Best Ask | `map.begin()` | `O(1)` |

Where `P` is the number of price levels and `k` is the number of orders at a specific price level.

---

## Complexity Analysis

| Component | Insert | Lookup / Query | Delete / Pop | Best Price |
|---|---:|---:|---:|---:|
| Robin Hood Hash Table | `O(1)` average | `O(1)` average | `O(1)` average | N/A |
| `std::unordered_map` | `O(1)` average | `O(1)` average | `O(1)` average | N/A |
| Custom Max Heap | `O(log n)` | `O(1)` top | `O(log n)` | `O(1)` |
| `std::priority_queue` | `O(log n)` | `O(1)` top | `O(log n)` | `O(1)` |
| Moving Average Naive | `O(nw)` | N/A | N/A | N/A |
| Moving Average SIMD | `O(nw / vector_width)` | N/A | N/A | N/A |
| Order Book | `O(log P)` | `O(log P + k)` | `O(k)` | `O(1)` |

---

## Technical Report

This project demonstrates several performance-oriented data structures relevant to low-latency trading systems. The Robin Hood hash table provides fast average-case insert, lookup, and delete operations using open addressing. Compared with `std::unordered_map`, it can offer better cache locality because entries are stored in contiguous memory rather than separate node allocations. This is useful in trading systems where order IDs, symbol metadata, and market data records must be accessed with very low latency.

The binary heap implements a max-priority queue using a contiguous `std::vector`. Both insertion and deletion run in `O(log n)` time, while retrieving the top element is `O(1)`. The optimized custom heap uses reserved capacity and hole-style sift-up and sift-down operations to reduce unnecessary swaps. In the benchmark, the custom heap was close to `std::priority_queue`, with insert taking 109 microseconds versus 108 microseconds and pop taking 828 microseconds versus 1312 microseconds. The standard library remains only slightly faster in insertion because it is highly optimized, but the custom version demonstrates efficient heap behavior by showing faster heap pop and predictable memory layout.

For time series processing, the naive moving average recomputes each window from scratch, resulting in `O(nw)` complexity. The optimized SIMD implementation uses ARM NEON on Apple Silicon to process two double values at once. This reduced runtime from 75 microseconds to 48 microseconds, giving around a 1.56x speedup. This shows how vectorization can improve throughput for repeated numerical operations such as moving averages, volatility estimates, signal calculations, and market data feature generation.

The order book combines `std::unordered_map` and `std::map`. The unordered map provides fast lookup by order ID, which is necessary for modifications and cancellations. The ordered maps store bid and ask price levels, allowing quick best bid and best ask retrieval. The highest bid is obtained using `bids.rbegin()`, while the lowest ask is obtained using `asks.begin()`. This design supports efficient real-time updates and price-level queries.

In real HFT systems, latency, cache locality, and memory allocation are critical. Preallocating vectors, avoiding unnecessary copies, and using contiguous memory can significantly reduce overhead. However, standard library containers are often already highly optimized. Custom structures are most useful when they exploit domain-specific constraints, such as fixed price ranges, integer tick prices, or preallocated memory pools. Further improvements could include replacing floating-point prices with integer ticks, using linked lists for faster order deletion at each price level, and using custom memory allocators to reduce allocation latency.