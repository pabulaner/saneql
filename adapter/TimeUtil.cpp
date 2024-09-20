#include "TimeUtil.hpp"

namespace tutil {

int64_t getMillis() {
    auto now = std::chrono::system_clock::now();
    auto duration = now.time_since_epoch();
    auto millis = std::chrono::duration_cast<std::chrono::milliseconds>(duration).count();

    return millis;
}

int64_t parseDate(const std::string& date) {
    if (date.size() != sizeof("0000-00-00") - 1 || date.at(4) != '-' || date.at(7) != '-') {
        throw std::runtime_error("Invalid date string");
    }

    int year = std::stoi(date.substr(0, 4));
    int month = std::stoi(date.substr(5, 2));
    int day = std::stoi(date.substr(8, 2));
    
    unsigned a = (14 - month) / 12;
    unsigned y = year + 4800 - a;
    unsigned m = month + (12 * a) - 3;
    return day + ((153 * m + 2) / 5) + (365 * y) + (y / 4) - (y / 100) +
        (y / 400) - 32045;
}

}