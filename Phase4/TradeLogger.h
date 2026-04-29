//
// Created by Mohammed RHAZI on 28/04/2026.
//

#ifndef PHASE4_TRADELOGGER_H
#define PHASE4_TRADELOGGER_H
#pragma once
#include <iostream>
#include <string>
#include <fstream>

class TradeLogger {
    std::ofstream file;
    std::vector<std::string> buffer;

public:
    TradeLogger(const std::string& filename);
    ~TradeLogger();

    void info(const std::string& message);
    void error(const std::string& message);

private:
    void log(const std::string& message);
    void flush();

};
#endif //PHASE4_TRADELOGGER_H