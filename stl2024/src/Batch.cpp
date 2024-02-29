#include "Batch.h"
#include "items/Item.h"
#include "Market.h"

#include <iostream>

bool Batch::isExpired() { return expireDay() <= _market->day(); }

std::strong_ordering Batch::operator<=>(const Batch &other) const {
    return expireDay() <=> other.expireDay();
}

std::unique_ptr<Batch> Batch::readBatch(std::istream &is, Market *market) {
    auto out = std::make_unique<Batch>();
    out->_market = market;

    std::string itemName;
    float itemPrice;
    is >> itemName >> itemPrice >> out->_quantity >> out->_expireDay;

    if ((out->_item = out->_market->getItem(itemName))) {
        return out;
    }

    out->_item = out->_market->registerSimpleItem(std::move(itemName), itemPrice);
    return out;
}

int Batch::expireDay() const {
    return _expireDay;
}

float Batch::quantity() const {
    return _quantity;
}

Batch &Batch::setQuantity(float quantity) {
    _quantity = quantity;
    return *this;
}

items::Item *Batch::item() {
    return _item;
};
