//
// Created by Mohammed RHAZI on 28/04/2026.
//

#include "TradeLogger.h"

TradeLogger::TradeLogger(const std::string &filename) : file(filename) {
    buffer.reserve(1024);
}

TradeLogger::~TradeLogger() {
    flush();
}

void TradeLogger::info(const std::string& message) {
    file << "[INFO]" << message << std::endl;
}

void TradeLogger::error(const std::string& message) {
    file << "[ERROR]" << message << std::endl;
}

void TradeLogger::flush() {
    for (const auto& msg : buffer) {
        file << msg << '\n';
    }
    buffer.clear();
    file.flush();
}

void TradeLogger::log(const std::string &message) {
    buffer.push_back(message);

    if (buffer.size() >= 1024) {
        flush();
    }
}
