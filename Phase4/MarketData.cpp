//
// Created by Mohammed RHAZI on 27/04/2026.
//

#include "MarketData.h"

void MarketDataHandler::handleTick(const Tick& tick) {
    if (tick.side == Bid){
        bids[tick.price].push_back(tick);
    }
    else {
        asks[tick.price].push_back(tick);
    }
}
double MarketDataHandler::get_best_bid() {
    if (!bids.empty()) return bids.begin()->first;
    return 0.0;
}
double MarketDataHandler::get_best_ask() {
    if (!asks.empty()) return asks.begin()->first;
}