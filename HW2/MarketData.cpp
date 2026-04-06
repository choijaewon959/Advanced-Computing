//
// Created by Jae Won Choi on 6/4/2026.
//

#include <random>

#include "MarketData.h"

void MarketDataFeed::generateData(int num_ticks) {
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_real_distribution<> price_dist(100.0, 200.0);

    data.reserve(num_ticks);
    for (int i = 0; i < num_ticks; ++i) {
        MarketData md;
        md.instrument_id = i % 10;
        md.price = price_dist(gen);
        md.timestamp = std::chrono::high_resolution_clock::now();
        data.push_back(md);
    }
}