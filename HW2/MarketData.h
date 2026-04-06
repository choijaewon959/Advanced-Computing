//
// Created by Jae Won Choi on 6/4/2026.
//

#ifndef HW2_MARKETDATA_H
#define HW2_MARKETDATA_H

#include <chrono>
#include <vector>

struct alignas(64) MarketData {
    int instrument_id;
    double price;
    std::chrono::high_resolution_clock::time_point timestamp;
};

class MarketDataFeed {
public:
    MarketDataFeed(std::vector<MarketData>& ref) : data(ref) {}
    void generateData(int num_ticks);

private:
    std::vector<MarketData>& data;
};


#endif //HW2_MARKETDATA_H