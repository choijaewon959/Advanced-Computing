//
// Created by Jae Won Choi on 15/4/2026.
//

#ifndef HW3_TRADEHANDLE_H
#define HW3_TRADEHANDLE_H
struct Trade {
    std::string symbol;
    double price;

    Trade(const std::string& sym, double p)
        : symbol(sym), price(p) {}
};

class TradeHandle {
    Trade* ptr;

public:
    TradeHandle(Trade* p): ptr(p) {};

    // handle auto mem deletion
    ~TradeHandle() {
        std::cout << "Deleting TradeHandle..." << std::endl;
        delete ptr;
    };

    // disable copy operator
    TradeHandle(const TradeHandle&) = delete;
    TradeHandle& operator=(const TradeHandle&) = delete;

    // enable transfer ownership (rvalue reference)
    TradeHandle(TradeHandle&& other): ptr(other.ptr) {
        other.ptr = nullptr;
    };
    TradeHandle& operator=(TradeHandle&& other) {
        if (this != &other) {
            delete ptr;
            ptr = other.ptr;
            other.ptr = nullptr;
        }
        return *this;
    };
    Trade* operator->() { return ptr; };
    Trade& operator*() { return *ptr; } ;
};
#endif //HW3_TRADEHANDLE_H