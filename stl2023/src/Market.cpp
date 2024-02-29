#include "Market.h"

#include <iostream>
#include <algorithm>
#include <ranges>
#include <cassert>

namespace rng = std::ranges;
namespace vw = std::views;

std::unique_ptr<Market> Market::readMarket(std::istream &is) {
    auto out = std::make_unique<Market>();

    int batchesCount;
    is >> batchesCount;

    while (batchesCount--) {
        BatchPtr batch = Batch::readBatch(is, out.get());
        out->_stock[batch->item()->name()].insert(std::move(batch));
    }

    return out;
}

float Market::income() const { return _income; }

int Market::day() const { return _day; }

Market const &Market::advanceDay(int days) {
    _day += days;
    return *this;
}

Market &Market::throwExpired(const std::string &productName) {
    std::set<BatchPtr> &batches = _stock[productName];

    while (!batches.empty() && (*batches.begin())->isExpired())
        batches.erase(batches.begin());

    return *this;
}

Market &Market::throwQuantity(const std::string &product_name, float quantity) {
    if(_items[product_name]->isCompositeType())
        throw std::runtime_error("Only simple items can be thrown from the market.");

    std::set<BatchPtr> &batches = _stock[product_name];

    while (!batches.empty() && (*batches.begin())->quantity() <= quantity) {
        quantity -= (*batches.begin())->quantity();
        batches.erase(batches.begin());
    }

    if (quantity > 0) {
        assert(!batches.empty());

        const BatchPtr &firstBatch = *batches.begin();
        assert(firstBatch->quantity() > quantity);

        firstBatch->setQuantity(firstBatch->quantity() - quantity );
    }
    return *this;
}

float Market::availableQuantity(const std::string &productName) {
    throwExpired(productName);

    const std::set<BatchPtr> &batches = _stock[productName];

    return std::accumulate(
            batches.begin(), batches.end(), 0.0f,
            [](float acc, BatchPtr const &batch) { return acc + batch->quantity(); });
}

items::Item *Market::registerSimpleItem(std::string name, float price) {
    auto item = std::make_unique<items::Item>(this, std::move(name), price);

    if(_items.contains(item->name()))
        throw std::runtime_error("Item names should be unique");

    return (_items[item->name()] = std::move(item)).get();
};

items::Item *Market::getItem(std::string const &itemName) {
    if (_items.contains(itemName))
        return _items[itemName].get();

    return nullptr;
}

items::CompositeItem *Market::registerCompositeItem(std::string name,
                                                    const std::vector<std::pair<std::string, float>> &ingredients) {
    auto item = std::make_unique<items::CompositeItem>(this, std::move(name));

    auto asIngredients = vw::transform(ingredients, [this](auto const &pair) {
        return Ingredient{
            pair.second,
            getItem(pair.first)};
    });

    if (rng::any_of(asIngredients, [](auto const &ingredient) { return ingredient.item == nullptr; }))
        throw std::runtime_error("All ingredients should be registered before creating a composite item");

    item->setIngredients(std::vector<Ingredient>(asIngredients.begin(), asIngredients.end()));

    return dynamic_cast<items::CompositeItem*>((_items[item->name()] = std::move(item)).get());
}

items::CompositeItem *Market::registerCompositeItemFromIS(std::istream &is) {
    std::string name;
    int ingredientsCount;
    is >> name >> ingredientsCount;

    std::vector<std::pair<std::string, float>> ingredients;
    while (ingredientsCount--) {
        std::string ingredientName;
        float quantity;
        is >> ingredientName >> quantity;
        ingredients.emplace_back(ingredientName, quantity);
    }

    return registerCompositeItem(std::move(name),  ingredients);
}

float Market::processOffer(const Offer &offer) {
  assert(offer.day >= day());

  advanceDay(offer.day - day());

  items::Item *item = getItem(offer.productName);
  assert(item != nullptr);
  float soldQuantity = item->sellItem(offer.quantity, offer.price);
  return soldQuantity;
}
