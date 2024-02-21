//
// Created by pijon on 2/21/24.
//

#ifndef P_FARES_H
#define P_FARES_H

#include <vector>
#include <sstream>

#include "time/TimeInterval.h"

namespace cdvii {

    class Fares {
        using Rate = std::pair<time_utils::TimeInterval, int>;
        static inline const int k_tripCost = 100;
        std::vector<Rate> fares{};

    public:
        Fares() = default;

        static Fares readFares(std::istream &in);

        int calculateFare(time_utils::Time start_time, int distance) const;
    };

} // cdvii

#endif //P_FARES_H
