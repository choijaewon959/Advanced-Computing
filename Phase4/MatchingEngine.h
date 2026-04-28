//
// Created by Mohammed RHAZI on 27/04/2026.
//

#ifndef PHASE4_MATCHINGENGINE_H
#define PHASE4_MATCHINGENGINE_H
#include "OrderBook.h"

template<typename PriceType, typename OrderIdType>
struct TradeT {
    OrderIdType buyId;
    OrderIdType sellId;
    std::string symbol;
    PriceType price;
    int quantity;
    std::chrono::nanoseconds latency;
};
template<typename PriceType, typename OrderIdType>
class MatchingEngine {
    using TradeT = TradeT<PriceType, OrderIdType>;

    OrderBook<PriceType,OrderIdType>& book;
    std::vector<TradeT> trades;

public:
    MatchingEngine(OrderBook<PriceType, OrderIdType>& b);

    void matchOrders();
    const std::vector<TradeT>& matchedTrades() const;
};

#endif //PHASE4_MATCHINGENGINE_H