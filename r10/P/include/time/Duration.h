#ifndef P_DURATION_H
#define P_DURATION_H

#include <cstdint>
#include <compare>

namespace time_utils {

    class Duration {
        int64_t duration_s{};
        static inline const int64_t minute_duration_s = 60;
        static inline const int64_t hour_duration_s = 60*minute_duration_s;
        static inline const int64_t day_duration_s = 24*hour_duration_s;
        static inline const int64_t month_duration_s = 30*day_duration_s;

    public:
        Duration() = default;
        Duration(const Duration &other) = default;

        static Duration minutes(int64_t minutes);
        static Duration hours(int64_t hours);

        std::strong_ordering operator<=>(const Duration &rhs) const;

        Duration operator-(const Duration &rhs) const;
        Duration operator+(const Duration &rhs) const;
        Duration& operator-=(const Duration &rhs);
        Duration& operator+=(const Duration &rhs);
        Duration operator-() const;

        double operator/(const Duration &rhs) const;

        Duration &addSeconds(int64_t seconds);
        Duration &addMinutes(int64_t minutes);
        Duration &addHours(int64_t hours);
        Duration &addDays(int64_t days);
        Duration &addMonths(int64_t months);

        int64_t minutes() const;
        int64_t hours() const;
    };

} // time_utils

#endif //P_DURATION_H
