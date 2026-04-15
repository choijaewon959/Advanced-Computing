//
// Created by Mohammed RHAZI on 14/04/2026.
//

#ifndef PHASE3_MARKET_SNAPSHOT_H
#define PHASE3_MARKET_SNAPSHOT_H
#include <map>

struct PriceLevel {
    double price;
    int quantity;

    PriceLevel(double p, int q) : price(p), quantity(q) {}
};

class MarketSnapshot {
    std::map<double, std::unique_ptr<PriceLevel>> bids;
    std::map<double, std::unique_ptr<PriceLevel>> asks;

public:
    void update_bid(double price, int qty);
    void update_ask(double price, int qty);
    const PriceLevel* get_best_bid() const;
    const PriceLevel* get_best_ask() const;
    void cancel_bid(double price, int qty);
    void cancel_ask(double price, int qty);
};






#endif //PHASE3_MARKET_SNAPSHOT_H