//
// Created by Jae Won Choi on 30/4/2026.
//

#ifndef HW5_HASHTABLE_H
#define HW5_HASHTABLE_H

#include <iostream>
#include <vector>
#include <string>
#include <unordered_map>

struct MarketData {
    double price;
    int volume;
};

class RobinHoodHashTable {
private:
    struct Entry {
        std::string key;
        MarketData value;
        bool used = false;
        bool deleted = false;
        int dist = 0;
    };

    std::vector<Entry> table;
    int capacity;

    int hashSymbol(const std::string& key) const {
        size_t h = 0;
        for (char c : key) {
            h = h * 31 + static_cast<unsigned char>(c);
        }
        return static_cast<int>(h % capacity);
    }

public:
    RobinHoodHashTable(int cap) : capacity(cap), table(cap) {}

    void insert(std::string key, MarketData value) {
        int idx = hashSymbol(key);
        int dist = 0;

        Entry item{key, value, true, false, dist};

        while (true) {
            Entry& cur = table[idx];

            if (!cur.used || cur.deleted) {
                item.dist = dist;
                table[idx] = item;
                return;
            }

            if (cur.key == key) {
                cur.value = value;
                return;
            }

            // Robin Hood idea: farther item steals the slot
            if (cur.dist < dist) {
                std::swap(cur, item);
                dist = item.dist;
            }

            idx = (idx + 1) % capacity;
            dist++;
        }
    }

    bool lookup(const std::string& key, MarketData& out) const {
        int idx = hashSymbol(key);
        int dist = 0;

        while (true) {
            const Entry& cur = table[idx];

            if (!cur.used) return false;

            if (!cur.deleted && cur.key == key) {
                out = cur.value;
                return true;
            }

            if (!cur.deleted && cur.dist < dist) return false;

            idx = (idx + 1) % capacity;
            dist++;
        }
    }

    bool erase(const std::string& key) {
        int idx = hashSymbol(key);
        int dist = 0;

        while (true) {
            Entry& cur = table[idx];

            if (!cur.used) return false;

            if (!cur.deleted && cur.key == key) {
                cur.deleted = true;
                return true;
            }

            if (!cur.deleted && cur.dist < dist) return false;

            idx = (idx + 1) % capacity;
            dist++;
        }
    }
};


#endif //HW5_HASHTABLE_H