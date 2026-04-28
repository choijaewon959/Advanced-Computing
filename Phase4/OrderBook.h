//
// Created by Mohammed RHAZI on 27/04/2026.
//

#ifndef PHASE4_ORDERBOOK_H
#define PHASE4_ORDERBOOK_H
#include "Order.h"

template <typename PriceType, typename OrderIdType>
class OrderBook{
    using OrderT = Order<PriceType, OrderIdType>;
    std::multimap<OrderIdType, std::unique_ptr<OrderT>> orders;

public:
    MarketDataHandler& market;
    OrderBook(MarketDataHandler& m);

    void placeOrder(OrderT o);
    void cancel(const OrderIdType& id);
    void handleFill(const OrderIdType& id, int qty);
};



#endif //PHASE4_ORDERBOOK_H