#include "time/Time.h"

using namespace time_utils;

time_utils::Duration Time::operator-(const Time &rhs) const {
    return timestamp - rhs.timestamp;
}

Time& Time::operator+=(const Duration &rhs) {
    return *this = *this + rhs;
}

Time Time::operator+(const Duration &rhs) const {
    Time t{};
    t.timestamp = this->timestamp + rhs;
    return t;
}

std::strong_ordering Time::operator<=>(const Time &rhs) const {
    return timestamp <=> rhs.timestamp;
}
