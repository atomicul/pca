//
// Created by pijon on 2/21/24.
//

#ifndef P_RECORD_H
#define P_RECORD_H

#include <sstream>

#include "time/DateTime.h"

namespace cdvii {
    enum class RecordType {
        entry,
        exit
    };


    struct Record {
        std::string id{};
        time_utils::DateTime time{};
        RecordType type{};
        int distance{};

        Record() = default;

        std::strong_ordering operator<=>(const Record &rhs) const;

        static Record readRecord(std::istream &in);
    };

} // cdvii

#endif //P_RECORD_H
