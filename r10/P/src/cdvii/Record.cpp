//
// Created by pijon on 2/21/24.
//

#include "cdvii/Record.h"

namespace cdvii {
    std::strong_ordering Record::operator<=>(const Record &rhs) const {
        return time <=> rhs.time;
    }

    Record Record::readRecord(std::istream &in) {
        std::string line;
        std::getline(in, line);
        std::istringstream is(line);

        Record r{};
        is >> r.id;
        is >> r.time;
        std::string type;
        is >> type;
        if (type == "enter") {
            r.type = RecordType::entry;
        } else {
            r.type = RecordType::exit;
        }
        is >> r.distance;
        return r;
    }
} // cdvii