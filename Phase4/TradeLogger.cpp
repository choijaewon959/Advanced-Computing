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
    log("[INFO]" + message);
}

void TradeLogger::error(const std::string& message) {
    log("[ERROR]" + message);
}

void TradeLogger::flush() {
    for (const auto& message : buffer) {
        file << message << '\n';
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
