//
// Created by Mohammed RHAZI on 27/04/2026.
//

#include "MatchingEngine.h"

template <typename PriceType, typename OrderIdType>
MatchingEngine<PriceType, OrderIdType>::MatchingEngine(OrderBook<PriceType, OrderIdType>& b) : book(b) {}

template <typename PriceType, typename OrderIdType>
void MatchingEngine<PriceType, OrderIdType>::matchOrders() {
    while (!empty(book.buys) && !empty(book.sells)){
        auto buyIt = book.buys.begin();
        auto sellIt = book.sells.begin();

        auto& buy = *(buyIt->second);
        auto& sell = *(sellIt->second);

        book.logger.info("Best bid: ", buy.price);
        book.logger.info("Best sell: ", sell.price);

        if (buy.price < sell.price) break;

        auto start = std::chrono::high_resolution_clock::now();

        int traded = std::min(buy.quantity, sell.quantity);
        buy.quantity -= traded;
        sell.quantity -= traded;

        auto end = std::chrono::high_resolution_clock::now();

        trades.push_back({buy.id, sell.id, buy.symbol, sell.price, traded, std::chrono::duration_cast<std::chrono::nanoseconds>(end - start).count()});

        book.logger.info("matched trade for ", buy.symbol, " at: ", sell.price, " between: ", buy.id, " and ", sell.id);

        if (buy.quantity == 0) {
            buyIt->second->state = State::Filled;
            book.buyIndex.erase(buy.id);
            book.buys.erase(buyIt);
        }
        else {
            buyIt->second->state = State::Partial;
        }
        if (sell.quantity == 0) {
            sellIt->second->state = State::Filled;
            book.sellIndex.erase(sell.id);
            book.sells.erase(sellIt);
        }
        else {
            sellIt->second->state = State::Partial;
        }
    }
}

template <typename PriceType, typename OrderIdType>
const std::vector<TradeT<PriceType, OrderIdType>>& MatchingEngine<PriceType, OrderIdType>::matchedTrades() {
    return trades;
}