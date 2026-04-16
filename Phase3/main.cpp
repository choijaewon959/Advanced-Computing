#include <iostream>
#include "order_manager.h"
#include "feed_parser.h"

bool should_trade(MarketSnapshot& snapshot) {
    const PriceLevel* best_bid = snapshot.get_best_bid();
    if (best_bid==nullptr) {
        return false;
    }
    return best_bid->price > 100.0;
}

int main() {
    MarketSnapshot snapshot;
    OrderManager om(snapshot);

    for (auto& update : load_feed("sample_feed.txt")) {
        update.print();

        if (update.type == FeedType::BID) {
            snapshot.update_bid(update.price, update.quantity);
            std::cout << "[MARKET] BEST BID: "<< snapshot.get_best_bid()->price << "*" << snapshot.get_best_bid()->quantity << "\n";
        }
        else if (update.type == FeedType::ASK) {
            snapshot.update_ask(update.price, update.quantity);
            std::cout << "[MARKET] BEST ASK: "<< snapshot.get_best_ask()->price << "*" << snapshot.get_best_ask()->quantity << "\n";
        }
        else if (update.type == FeedType::EXECUTION) {
            om.handle_fill(update.order_id, update.quantity);
        }
        if ((update.type == FeedType::BID || update.type == FeedType::ASK) && should_trade(snapshot)) {
            int id = om.place_order(Side::Ask, snapshot.get_best_bid()->price, 10); // 10?
            std::cout << "ID "<< id << ": Placed SELL order at " << snapshot.get_best_bid()->price << "\n";
        }
    }
}
