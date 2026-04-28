//
// Created by Mohammed RHAZI on 27/04/2026.
//

#ifndef PHASE4_ORDER_H
#define PHASE4_ORDER_H
#pragma once
#include <string>
#include <memory>
#include "MarketData.h"
#include <type_traits>

enum class State {
    New,
    Cancelled,
    Partial,
    Filled
};

template <typename PriceType, typename OrderIdType>
struct Order {
    static_assert(std::is_integral<OrderIdType>::value, "OrderIdType must be an integer type");

    OrderIdType id;
    std::string symbol;
    PriceType price;
    int quantity;
    bool is_buy;
    State state = State::New;
};
#endif //PHASE4_ORDER_H