#ifndef STL2023_OFFER_H
#define STL2023_OFFER_H

#include <string>

struct Offer {
    std::string productName;
    float price{}, quantity{};
    int day{};

    friend std::istream &operator>>(std::istream &is, Offer &o);
};


#endif //STL2023_OFFER_H
