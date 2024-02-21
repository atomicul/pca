#ifndef P_TIME_H
#define P_TIME_H

#include <iostream>
#include <compare>

#include "time/Duration.h"

namespace time_utils {

    class Time {
        time_utils::Duration timestamp{};

    public:
        Time() = default;
        Time(const Time &other) = default;

        time_utils::Duration operator-(const Time &rhs) const;

        Time operator+(const Duration &rhs) const;

        Time& operator+=(const Duration &rhs);

        std::strong_ordering operator<=>(const Time &rhs) const;

    };
} // time_utils

#endif //P_TIME_H
