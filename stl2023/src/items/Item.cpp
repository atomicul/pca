#include "items/Item.h"
#include "Market.h"

namespace items {
float Item::available_quantity() { return _market->availableQuantity(_name); }

float Item::sellItem(float quantity, float price) {
  const float availableQuantity = this->available_quantity();
  const float soldQuantity = std::min(quantity, availableQuantity);

  const float profitMargin = price - this->price();
  if (profitMargin <= 0)
    return 0;
  _market->_income += price * soldQuantity;
  throwQuantity(soldQuantity);

  return soldQuantity;
}

std::string Item::name() const { return _name; }

Item::Item(Market *market, std::string name, float price)
    : _market(market), _name(std::move(name)), _price(price) {}

bool Item::isCompositeType() { return false; }

Item &Item::throwQuantity(float quantity) {
  _market->throwQuantity(_name, quantity);
  return *this;
}

float Item::price() const {
  return _price;
}
}