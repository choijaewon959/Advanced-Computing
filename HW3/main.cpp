#include <iostream>
#include <string>
#include "TradeHandle.h"

int main() {
    //Task1
    Trade* t1 = new Trade("AAPL", 175.0);

    std::cout << "Single Trade:" << std::endl;
    std::cout << t1->symbol << " @ " << t1->price << std::endl;

    //Task2
    Trade* trades = new Trade[5]{
        {"AAPL", 175.5},
        {"MSFT", 320.1},
        {"GOOG", 2800.0},
        {"AMZN", 3400.2},
        {"TSLA", 900.8}
        };

        std::cout << "\nTrade Array:" << std::endl;
        for (int i = 0; i < 5; ++i) {
            std::cout << trades[i].symbol << " @ " << trades[i].price << std::endl;
        }

        delete t1;
        delete[] trades;

        return 0;
    }