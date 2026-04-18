//
// Created by Mohammed RHAZI on 17/04/2026.
//
#include <iostream>
#include <string>

struct Trade {
    std::string symbol;
    double price;

    Trade(const std::string& s, double p) : symbol(s), price(p) {
        std::cout << "Trade created: " << symbol << "\n";
    }

    ~Trade() {
        std::cout << "Trade destroyed: " << symbol << "\n";
    }
};

int main() {
    Trade* t1 = new Trade("AAPL", 150.0);
    Trade* t2 = new Trade("GOOG", 2800.0);
    delete t1;
    t1 = nullptr;
    //issue
    //this was a double delete, leading to undefined behaviour.
    //setting t1 to null pointer makes reuse safer
    delete t1; // safe now

    //issue
    //t2 was allocated dynamically but never deleted, leading to a memory leak
    delete t2;
    t2 = nullptr;

    Trade* t3 = new Trade("MSFT", 300.0);
    //issue
    //the only pointer to "MSFT" in the heap was never deleted, points now to TSLA causing memory leak
    delete t3;
    t3 = new Trade("TSLA", 750.0);
    delete t3;
    t3 = nullptr;

    Trade* trades = new Trade[3] {
        {"NVDA", 900.0},
        {"AMZN", 3200.0},
        {"META", 250.0}
    };
    delete[] trades;
    //issue
    //memory allocated with new[] should be deleted with delete[]. using delete leads to undefined behavior
    //fails to call all destructors
    trades = nullptr;
    return 0;
}