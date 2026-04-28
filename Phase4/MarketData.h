//
// Created by Mohammed RHAZI on 27/04/2026.
//
#ifndef PHASE4_MARKETDATA_H
#define PHASE4_MARKETDATA_H
#include <string>
#include <map>
#include <chrono>
#include <vector>
#include <functional>

enum Side {
    Bid,
    Ask
};
struct Tick {
    std::string sym;
    double price;
    Side side;
    std::chrono::high_resolution_clock::time_point timest;
};

struct alignas(64) MarketData {
    std::string symbol;
    double bid_price;
    double ask_price;
    std::chrono::high_resolution_clock::time_point timestamp;
};

class MarketDataHandler{
    std::map<double, std::vector<Tick>, std::greater<double>> bids;
    std::map<double, std::vector<Tick>> asks;
public:
    void handleTick(const Tick& tick);
    double get_best_bid();
    double get_best_ask();
};


#endif //PHASE4_MARKETDATA_H