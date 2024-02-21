//
// Created by pijon on 2/21/24.
//

#include "time/Duration.h"

using namespace time_utils;

Duration Duration::minutes(int64_t minutes) {
    return Duration().addMinutes(minutes);
}

Duration Duration::operator-(const Duration &rhs) const {
    return Duration().addSeconds(duration_s - rhs.duration_s);
}

double Duration::operator/(const Duration &rhs) const {
    return (double) duration_s / rhs.duration_s;
}

Duration &Duration::addSeconds(int64_t seconds) {
    duration_s += seconds;
    return *this;
}

Duration &Duration::addMinutes(int64_t minutes) {
    duration_s += minutes * minute_duration_s;
    return *this;
}

Duration &Duration::addHours(int64_t hours) {
    duration_s += hours * hour_duration_s;
    return *this;
}

Duration &Duration::addDays(int64_t days) {
    duration_s += days * day_duration_s;
    return *this;
}

Duration &Duration::addMonths(int64_t months) {
    duration_s += months * month_duration_s;
    return *this;
}

int64_t Duration::hours() const {
    return duration_s % day_duration_s / hour_duration_s;
}

int64_t Duration::minutes() const {
    return duration_s % hour_duration_s / minute_duration_s;
}

Duration Duration::operator+(const Duration &rhs) const {
    return Duration().addSeconds(duration_s + rhs.duration_s);
}

Duration& Duration::operator+=(const Duration &rhs) {
    return *this = *this + rhs;
}

Duration& Duration::operator-=(const Duration &rhs) {
    return *this = *this - rhs;
}

Duration Duration::operator-() const {
    return Duration().addSeconds(-duration_s);
}

Duration Duration::hours(int64_t hours) {
    return Duration().addHours(hours);
}

std::strong_ordering Duration::operator<=>(const Duration &rhs) const {
    return duration_s <=> rhs.duration_s;
}
