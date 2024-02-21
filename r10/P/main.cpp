#include <iostream>
#include <vector>
#include <limits>

#include "cdvii/Bill.h"

int main() {
    using namespace cdvii;
    int t;
    std::cin >> t;
    for(int i = 0; i<2; i++)
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

    while (t--) {
        Bill bill(Fares::readFares(std::cin));
        std::vector<Record> records{};

        while(!std::cin.eof()) {
            std::string line;
            std::getline(std::cin, line);
            if(line.empty()) {
                break;
            }

            std::istringstream is(line);
            records.push_back(Record::readRecord(is));
        }

        bill.processRecords(std::move(records));
        for(auto [id, cost] : bill.getCosts()) {
            std::cout << id << " $" << cost/100 << "." << cost%100 << "\n";
        }
        std::cout << std::endl;
    }

    return 0;
}
