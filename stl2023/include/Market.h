#ifndef STL2023_MARKET_H
#define STL2023_MARKET_H

#include "items/Item.h"
#include "items/CompositeItem.h"
#include "Batch.h"
#include "Offer.h"

#include <memory>
#include <set>
#include <map>
#include <numeric>

class Market {
    using BatchPtr = std::unique_ptr<Batch>;
    std::unordered_map<std::string, std::unique_ptr<items::Item>> _items;
    std::map<std::string, std::set<BatchPtr>> _stock;
    int _day{};
    float _income{};

public:
    static std::unique_ptr<Market> readMarket(std::istream &is);

    float income() const;

    int day() const;

    Market const &advanceDay(int days = 1);

    friend float items::Item::sellItem(float quantity, float price);

    float processOffer(Offer const &offer);

    Market &throwExpired(std::string const &productName);

    Market &throwQuantity(std::string const &product_name, float quantity);

    float availableQuantity(std::string const &productName);

    items::Item *registerSimpleItem(std::string name, float price);

    items::CompositeItem *registerCompositeItem(std::string name, std::vector<std::pair<std::string, float>> const &ingredients);

    items::CompositeItem *registerCompositeItemFromIS(std::istream &is);

    items::Item *getItem(std::string const &itemName);
};



#endif //STL2023_MARKET_H
