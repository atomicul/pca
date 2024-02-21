#ifndef P_TIMEINTERVAL_H
#define P_TIMEINTERVAL_H

#include <utility>

#include "time/Time.h"

namespace time_utils {
    using TimeInterval = std::pair<time_utils::Time, time_utils::Time>;
}

#endif //P_TIMEINTERVAL_H
