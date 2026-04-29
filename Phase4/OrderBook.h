//
// Created by Mohammed RHAZI on 27/04/2026.
//

#ifndef PHASE4_ORDERBOOK_H
#define PHASE4_ORDERBOOK_H
#include "Order.h"
#include "TradeLogger.h"

template <typename PriceType, typename OrderIdType>
class OrderBook{
    using OrderT = Order<PriceType, OrderIdType>;
    std::multimap<PriceType, std::unique_ptr<OrderT>, std::greater<PriceType>> buys;
    std::multimap<PriceType, std::unique_ptr<OrderT>> sells;

    using BuyIt = typename decltype(buys)::iterator;
    using SellIt = typename decltype(sells)::iterator;

    std::unordered_map<OrderIdType, BuyIt> buyIndex;
    std::unordered_map<OrderIdType, SellIt> sellIndex;

public:
    MarketDataHandler& market;
    TradeLogger& logger;
    OrderBook(MarketDataHandler& m, TradeLogger& l);

    void placeOrder(OrderT o);
    void cancel(const OrderIdType& id);
    void handleFill(const OrderIdType& id, int qty);
};



#endif //PHASE4_ORDERBOOK_H