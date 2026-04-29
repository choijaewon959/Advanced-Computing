//
// Created by Mohammed RHAZI on 29/04/2026.
//
#include <cassert>
#include <iostream>
#include <vector>
#include <numeric>
#include <algorithm>
#include "Order.h"
#include "Timer.h"
#include "OrderBook.h"
#include "MarketData.h"
#include "TradeLogger.h"
#include "MatchingEngine.h"

using OrderType = Order<double, int>;

void analyzeLatencies(std::vector<long long> latencies) {
    if (latencies.empty()) return;

    std::sort(latencies.begin(), latencies.end());

    auto min=latencies.front();
    auto max=latencies.back();

    double mean = std::accumulate(latencies.begin(), latencies.end(), 0.0)/latencies.size();

    double variance = 0.0;
    for (auto l : latencies) {
        variance+=(l-mean)*(l-mean);
    }

    variance /= latencies.size();
    double stddev = std::sqrt(variance);

    size_t p99Index = static_cast<size_t>(0.99*(latencies.size()-1));
    long long p99 = latencies[p99Index];

    std::cout << "Tick-to-Trade Latency (nanoseconds) \n";
    std::cout << "Min: " << min
              << "\nMax: " << max
              << "\nMean: " << mean
              << "\nStddev: " << stddev
              << "\nP99: " << p99 << "\n";
}
int main() {
    std::vector<long long> latencies;
    latencies.reserve(10000);

    const int num_ticks = 10000;

    MarketDataHandler mkt;
    TradeLogger logger("/Users/simorhazi/CLionProjects/advanced computing/Advanced-Computing/Phase4/logs.log");

    OrderBook<double, int> orderBook(mkt, logger);
    MatchingEngine matchingEngine(orderBook);

    for (int i = 0; i < num_ticks; ++i) {
        Timer timer;
        timer.start();

        bool isBuy = (i%2==0);
        double price = (i%2 == 0) ? 155.0 : 150.0;

        Tick t{"AAPL", price, isBuy ? Side::Bid : Side::Ask, std::chrono::high_resolution_clock::now()};

        mkt.handleTick(t);

        OrderType order{i, "AAPL", price, 100, isBuy};

        orderBook.placeOrder(order);
        matchingEngine.matchOrders();

        latencies.push_back(timer.stop());
    }

    assert(!latencies.empty());
    assert(matchingEngine.matchedTrades().size() > 0);

    analyzeLatencies(latencies);
}