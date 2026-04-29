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
    using tradeT = TradeT<PriceType, OrderIdType>;

    OrderBook<PriceType,OrderIdType>& book;
    std::vector<tradeT> trades;

public:
    MatchingEngine(OrderBook<PriceType, OrderIdType>& b) : book(b) {}

    void matchOrders() {
        while (!empty(book.buys) && !empty(book.sells)){
            auto buyIt = book.buys.begin();
            auto sellIt = book.sells.begin();

            auto& buy = *(buyIt->second);
            auto& sell = *(sellIt->second);

            book.logger.info("Best bid " + std::to_string(buy.price));
            book.logger.info("Best ask " + std::to_string(sell.price));

            if (buy.price < sell.price) break;

            auto start = std::chrono::high_resolution_clock::now();

            int traded = std::min(buy.quantity, sell.quantity);
            buy.quantity -= traded;
            sell.quantity -= traded;

            auto end = std::chrono::high_resolution_clock::now();

            trades.push_back({buy.id, sell.id, buy.symbol, sell.price, traded, std::chrono::duration_cast<std::chrono::nanoseconds>(end - start)});

            book.logger.info("matched trade for " + buy.symbol + " at: " + std::to_string(sell.price) +
                " between: " + std::to_string(buy.id) + " and " + std::to_string(sell.id));

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
    const std::vector<tradeT>& matchedTrades() {
        return trades;
    }
};

#endif //PHASE4_MATCHINGENGINE_H