//
// Created by Jae Won Choi on 16/4/2026.
//

#ifndef PHASE3_LOGGER_H
#define PHASE3_LOGGER_H

#include <fstream>
#include <string>

class Logger {
    std::ofstream file;

public:
    Logger(const std::string& filename) {
        file.open(filename);
    }

    ~Logger() {
        if (file.is_open()) {
            file.close();
        }
    }

    void info(const std::string& msg) {
        file << "[INFO] " << msg << "\n";
    }

    void error(const std::string& msg) {
        file << "[ERROR] " << msg << "\n";
    }
};
#endif //PHASE3_LOGGER_H