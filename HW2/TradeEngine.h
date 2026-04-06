//
// Created by Jae Won Choi on 6/4/2026.
//

#ifndef HW2_TRADINGENGINE_H
#define HW2_TRADINGENGINE_H

#include <chrono>
#include <unordered_map>
#include <iostream>
#include "MarketData.h"

struct alignas(64) Order {
    int instrument_id;
    double price;
    bool is_buy;
    std::chrono::high_resolution_clock::time_point timestamp;
};

class TradeEngine {
public:
    TradeEngine(const std::vector<MarketData>& feed)
        : market_data(feed) {}
    void process();
    void reportStats();

private:
    const std::vector<MarketData>& market_data;
    std::vector<Order> orders;
    std::vector<long long> latencies;
    std::unordered_map<int, std::vector<double>> price_history;

    void updateHistory(const MarketData& tick);
    double getAvg(int id);

    // Signal 1: Price thresholds
    bool signal1(const MarketData& tick);

    // Signal 2: Deviation from average
    bool signal2(const MarketData& tick);

    // Signal 3: Simple momentum
    bool signal3(const MarketData& tick);
};

#endif //HW2_TRADINGENGINE_H