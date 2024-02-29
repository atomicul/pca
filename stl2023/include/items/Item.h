#ifndef STL2023_ITEM_H
#define STL2023_ITEM_H

#include <memory>
#include <unordered_map>

class Market;

namespace items {
    class Item {
    protected:
        Market *_market;
        std::string _name;
        float _price;

    public:
        Item(Market *market, std::string name, float price);

        float sellItem(float quantity, float price);

        virtual bool isCompositeType();

        std::string name() const;

        virtual float price() const;

        virtual float available_quantity();

        virtual Item &throwQuantity(float quantity);
    };
};

#endif //STL2023_ITEM_H
