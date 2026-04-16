#include <iostream>
#include "order_manager.h"
#include "feed_parser.h"

bool should_trade(MarketSnapshot& snapshot) {
    const PriceLevel* best_bid = snapshot.get_best_bid();
    const PriceLevel* best_ask = snapshot.get_best_ask();

    if (best_bid==nullptr || best_ask == nullptr ) {
        return false;
    }
    return best_bid->price >= best_ask->price;
}

int main() {
    MarketSnapshot snapshot;
    OrderManager om(snapshot);

    for (auto& update : load_feed("sample_feed.txt")) {
        update.print();

        if (update.type == FeedType::BID) {
            snapshot.update_bid(update.price, update.quantity);
        }
        else if (update.type == FeedType::ASK) {
            snapshot.update_ask(update.price, update.quantity);
        }
        if (should_trade(snapshot)) {
            int id = om.place_order(Side::Bid, snapshot.get_best_bid()->price, 10); // 10?

            std::cout << "ID "<< id << ": Placed BUY order at " << snapshot.get_best_bid()->price << """\n";
        }
        if (update.type == FeedType::EXECUTION) {
            om.handle_fill(update.order_id, update.quantity);
        }
    }
}
