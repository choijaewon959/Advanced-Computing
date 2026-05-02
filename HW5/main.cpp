#include <iostream>
#include <chrono>
#include <queue>
#include <vector>
#include "hashtable.h"
#include "binaryheap.h"
#include "timeseries.h"
#include "orderbook.h"

long long timeNow() {
    return std::chrono::duration_cast<std::chrono::microseconds>(
        std::chrono::high_resolution_clock::now().time_since_epoch()
    ).count();
}

struct Compare {
    bool operator()(Order a, Order b) {
        return a.price < b.price; // max heap
    }
};

int main() {
    const int N = 20000;

    // Part 1: Robin Hood Hash Table
    RobinHoodHashTable table(50000);
    std::unordered_map<std::string, MarketData> stdMap;

    std::vector<std::string> symbols;
    for (int i = 0; i < N; i++) {
        symbols.push_back("SYM" + std::to_string(i));
    }

    long long start, end;

    start = timeNow();
    for (int i = 0; i < N; i++) {
        table.insert(symbols[i], {100.0 + i, i});
    }
    end = timeNow();
    std::cout << "Robin Hood insert: " << end - start << " us\n";

    start = timeNow();
    for (int i = 0; i < N; i++) {
        stdMap[symbols[i]] = {100.0 + i, i};
    }
    end = timeNow();
    std::cout << "unordered_map insert: " << end - start << " us\n";

    MarketData data{};
    volatile int checksum = 0;

    start = timeNow();
    for (int i = 0; i < N; i++) {
        if (table.lookup(symbols[i], data)) {
            checksum += data.volume;
        }
    }
    end = timeNow();
    std::cout << "Robin Hood lookup: " << end - start << " us\n";

    start = timeNow();
    for (int i = 0; i < N; i++) {
        auto it = stdMap.find(symbols[i]);
        if (it != stdMap.end()) {
            checksum += it->second.volume;
        }
    }
    end = timeNow();
    std::cout << "unordered_map lookup: " << end - start << " us\n";

    table.erase("SYM10");

    if (!table.lookup("SYM10", data)) {
        std::cout << "Delete works\n";
    }

    std::cout << "\n";

    // Part 2: Priority Queue / Heap
    MaxHeap myHeap(N);

    std::vector<Order> stdHeapStorage;
    stdHeapStorage.reserve(N);

    std::priority_queue<Order, std::vector<Order>, Compare> stdHeap(
        Compare(),
        std::move(stdHeapStorage)
    );

    std::vector<Order> orders;
    orders.reserve(N);

    for (int i = 0; i < N; i++) {
        orders.push_back({100.0 + (i % 100), i});
    }

    start = timeNow();
    for (const auto& order : orders) {
        myHeap.push(order);
    }
    end = timeNow();
    std::cout << "Custom heap insert: " << end - start << " us\n";

    start = timeNow();
    for (const auto& order : orders) {
        stdHeap.push(order);
    }
    end = timeNow();
    std::cout << "std::priority_queue insert: " << end - start << " us\n";

    start = timeNow();
    while (!myHeap.empty()) {
        myHeap.pop();
    }
    end = timeNow();
    std::cout << "Custom heap pop: " << end - start << " us\n";

    start = timeNow();
    while (!stdHeap.empty()) {
        stdHeap.pop();
    }
    end = timeNow();
    std::cout << "std::priority_queue pop: " << end - start << " us\n";

    std::cout << "Checksum: " << checksum << "\n";

    std::cout << "\n";

    // Part 3: Optimized Time Series Processing
    runTimeSeriesValidation();

    std::cout <<"\n";

    // Part 4: High-Performance Order Book
    OrderBook book;

    book.add_order(1, 100.50, 10, 'B');
    book.add_order(2, 100.75, 20, 'B');
    book.add_order(3, 101.00, 15, 'S');
    book.add_order(4, 101.25, 30, 'S');
    book.add_order(5, 100.75, 5, 'B');

    book.print_bbo();

    book.query_price_level(100.75, 'B');

    book.modify_order(2, 50);

    std::cout << "After modifying order 2:\n";
    book.query_price_level(100.75, 'B');

    book.delete_order(2);

    std::cout << "After deleting order 2:\n";
    book.query_price_level(100.75, 'B');

    book.print_bbo();
    return 0;
}