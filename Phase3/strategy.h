//
// Created by Jae Won Choi on 16/4/2026.
//

#ifndef PHASE3_STRATEGY_H
#define PHASE3_STRATEGY_H

# include "order_manager.h"

enum class Signal {
    Buy,
    Sell,
    Hold
};

class Strategy {
public:
    Signal get_signal(const MarketSnapshot& snapshot) const{
        const PriceLevel* best_bid = snapshot.get_best_bid();
        const PriceLevel* best_ask = snapshot.get_best_ask();

        if (!best_bid || !best_ask) {
            return Signal::Hold;
        }

        if (best_ask->price < 100.0) {
            return Signal::Buy;
        }
        else if (best_bid->price > 100.0) {
            return Signal::Sell;
        }

        return Signal::Hold;
    }
};


#endif //PHASE3_STRATEGY_H