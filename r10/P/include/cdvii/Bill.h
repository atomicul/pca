//
// Created by pijon on 2/21/24.
//

#ifndef P_BILL_H
#define P_BILL_H

#include <map>

#include "cdvii/Fares.h"
#include "cdvii/Record.h"

namespace cdvii {

    class Bill {
        static inline const int k_accountCost = 200;
        Fares fares{};
        std::map<std::string, Record> entry_records{};
        std::map<std::string, int> cost{};

    public:
        Bill(Fares const &f) : fares(f) {}

        Bill &processRecord(Record r);

        Bill &processRecords(std::vector<Record> records);

        std::vector<std::pair<std::string, int>> getCosts() const;
    };

} // cdvii

#endif //P_BILL_H
