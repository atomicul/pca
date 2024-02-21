#ifndef P_DATETIME_H
#define P_DATETIME_H

#include <iostream>

#include "time/Duration.h"
#include "time/Time.h"

namespace time_utils {

    class DateTime {
        time_utils::Duration timestamp{};


    public:
        DateTime() = default;

        std::strong_ordering operator<=>(const DateTime &rhs) const;

        /* Reads object in the following format: "mm:dd:hh::mm" */
        friend std::istream& operator>>(std::istream &in, DateTime &x);

        time_utils::Duration operator-(const DateTime &rhs) const;

        DateTime operator+(const Duration &rhs) const;

        DateTime& operator+=(const Duration &rhs);

        time_utils::Time getTime() const;
    };

} // time_utils

#endif //P_DATETIME_H
