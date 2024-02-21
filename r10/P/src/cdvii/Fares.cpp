//
// Created by pijon on 2/21/24.
//

#include "cdvii/Fares.h"

namespace cdvii {
    Fares Fares::readFares(std::istream &in) {
        std::string line;
        std::getline(in, line);
        std::istringstream is(line);

        Fares f{};
        const int k_HoursInDay = 24;
        for(int hour = 0; hour < k_HoursInDay; ++hour) {
            auto start = time_utils::Time{} + time_utils::Duration::hours(hour);
            auto end = start + time_utils::Duration::hours(1);
            time_utils::TimeInterval interval{start, end};

            int price;
            is >> price;

            Rate rate{interval, price};
            f.fares.push_back(rate);
        }
        return f;
    }

    int Fares::calculateFare(time_utils::Time start_time, int distance) const {
        auto rate_it = std::find_if(fares.begin(), fares.end(), [start_time](const Rate &rate) {
            return rate.first.first <= start_time && start_time < rate.first.second;
        });

        if (rate_it >= fares.end())
            return k_tripCost;

        return k_tripCost + rate_it->second * distance;
    }
} // cdvii