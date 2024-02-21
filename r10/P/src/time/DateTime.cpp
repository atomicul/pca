#include "time/DateTime.h"

using namespace time_utils;

std::istream &time_utils::operator>>(std::istream &in, DateTime &x) {
    int64_t month, day, hour, minute;
    char _;
    in >> month >> _ >> day >> _ >> hour >> _ >> minute;

    x.timestamp.addMonths(month);
    x.timestamp.addDays(day);
    x.timestamp.addHours(hour);
    x.timestamp.addMinutes(minute);

    return in;
}

time_utils::Duration DateTime::operator-(const DateTime &rhs) const {
    return timestamp - rhs.timestamp;
}

DateTime DateTime::operator+(const Duration &rhs) const {
    DateTime t{};
    t.timestamp = this->timestamp + rhs;
    return t;
}

DateTime& DateTime::operator+=(const Duration &rhs) {
    return *this = *this + rhs;
}

time_utils::Time DateTime::getTime() const {
    Time result{};
    result += Duration().addMinutes(timestamp.minutes()).addHours(timestamp.hours());
    return result;
}

std::strong_ordering DateTime::operator<=>(const DateTime &rhs) const {
    return timestamp <=> rhs.timestamp;
}
