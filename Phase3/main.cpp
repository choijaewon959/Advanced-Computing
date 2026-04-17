#include <iostream>
#include "order_manager.h"
#include "feed_parser.h"
#include "strategy.h"
#include "logger.h"

int main() {
    Logger log("output.log");
    MarketSnapshot snapshot;
    OrderManager om(snapshot, log);
    Strategy s;

    log.info("Backtest started...");

    for (auto& update : load_feed("sample_feed.txt")) {
        update.print(log);

        if (update.type == FeedType::BID) {
            snapshot.update_bid(update.price, update.quantity);
            log.info("[MARKET] Best BID: " + std::to_string(snapshot.get_best_bid()->price) + "*" + std::to_string(snapshot.get_best_bid()->quantity));
        }
        else if (update.type == FeedType::ASK) {
            snapshot.update_ask(update.price, update.quantity);
            log.info("[MARKET] Best ASK: " + std::to_string(snapshot.get_best_ask()->price) + "*" +  std::to_string(snapshot.get_best_ask()->quantity));
        }
        else if (update.type == FeedType::EXECUTION) {
            om.handle_fill(update.order_id, update.quantity);
        }

        // strategy execution
        if ((update.type == FeedType::BID || update.type == FeedType::ASK)) {
            Signal sig = s.get_signal(snapshot);
            if (sig == Signal::Buy) {
                int id = om.place_order(Side::Bid, snapshot.get_best_bid()->price, 10); // arbitrary size of order 10
                log.info("[Strategy] Placed BUY order at " + std::to_string(snapshot.get_best_bid()->price) + " (ID [" + std::to_string(id) +"])");
            }
            else if (sig == Signal::Sell) {
                int id = om.place_order(Side::Ask, snapshot.get_best_ask()->price, 10);
                log.info("[Strategy] Placed SELL order at " + std::to_string(snapshot.get_best_ask()->price) + " (ID [" + std::to_string(id) + "])");
            }

        }
    }
}
