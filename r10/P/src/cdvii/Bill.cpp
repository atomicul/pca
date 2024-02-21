//
// Created by pijon on 2/21/24.
//

#include "cdvii/Bill.h"

namespace cdvii {
    Bill &Bill::processRecord(Record r) {
        if (r.type == RecordType::entry) {
            entry_records[r.id] = std::move(r);
        } else {
            if(!entry_records.contains(r.id))
                return *this;

            Record &record = entry_records[r.id];
            cost[r.id] += fares.calculateFare(record.time.getTime(), r.distance - record.distance);
            entry_records.erase(r.id);
        }
        return *this;
    }

    Bill &Bill::processRecords(std::vector<Record> records) {
        std::sort(records.begin(), records.end());

        for (auto &r : records) {
            processRecord(std::move(r));
        }

        return *this;
    }

    std::vector<std::pair<std::string, int>> Bill::getCosts() const {
        std::vector<std::pair<std::string, int>> result{};
        result.reserve(cost.size());
        for (const auto &[id, cost] : cost) {
            result.emplace_back(id, cost + k_accountCost);
        }
        return result;
    }
} // cdvii