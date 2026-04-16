#include <iostream>
#include "order_manager.h"
#include "feed_parser.h"
#include <fstream>
#include <string>
#include <sstream>
#include <vector>

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
