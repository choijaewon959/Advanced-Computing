#include <iostream>
#include <chrono>
#include <vector>
#include "hashtable.h"
#include "binaryheap.h"

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
    MaxHeap myHeap;
    std::priority_queue<Order, std::vector<Order>, Compare> stdHeap;

    std::vector<Order> orders;

    for (int i = 0; i < N; i++) {
        orders.push_back({i, 100.0 + (i % 100)});
    }

    start = timeNow();
    for (auto order : orders) {
        myHeap.push(order);
    }
    end = timeNow();
    std::cout << "Custom heap insert: " << end - start << " us\n";

    start = timeNow();
    for (auto order : orders) {
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

    return 0;
}