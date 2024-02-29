#ifndef STL2023_BATCH_H
#define STL2023_BATCH_H

#include "items/Item.h"

#include <compare>
#include <memory>


class Batch {
    Market *_market{};
    items::Item *_item{};
    float _quantity{};
    int _expireDay{};

public:
    int expireDay() const;

    float quantity() const;

    Batch &setQuantity(float quantity);

    items::Item *item();

    bool isExpired();

    std::strong_ordering operator<=>(Batch const &other) const;

    static std::unique_ptr<Batch> readBatch(std::istream &is, Market *market);
};

#endif //STL2023_BATCH_H
