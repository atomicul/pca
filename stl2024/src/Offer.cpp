#include "Offer.h"

#include <iostream>

std::istream &operator>>(std::istream &is, Offer &o) {
    return is >> o.productName >> o.price >> o.quantity;
}
