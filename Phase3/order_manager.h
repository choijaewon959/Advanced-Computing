//
// Created by Mohammed RHAZI on 14/04/2026.
//

#ifndef PHASE3_ORDER_MANAGER_H
#define PHASE3_ORDER_MANAGER_H
#include <map>
#include "market_snapshot.h"

enum class OrderStatus {New, Filled, PartiallyFilled, Cancelled};
enum class Side {Bid, Ask};

struct MyOrder {
    int id;
    Side side = Side::Bid;
    double price;
    int quantity;
    int filled = 0;
    OrderStatus status = OrderStatus::New;
};

class OrderManager {
    int new_id=0;
    std::map<int, std::unique_ptr<MyOrder>> orders;
    MarketSnapshot& market;

public:
    OrderManager(MarketSnapshot& m) : market(m) {};
    int place_order(Side side, double price, int qty);
    void cancel(int id);
    void handle_fill(int id, int filled_qty);
    void print_active_orders() const;
};


#endif //PHASE3_ORDER_MANAGER_H