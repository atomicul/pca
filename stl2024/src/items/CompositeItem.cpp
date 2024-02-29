//
// Created by pijon on 2/28/24.
//

#include "items/CompositeItem.h"

#include <algorithm>
#include <ranges>
#include <numeric>

namespace rng = std::ranges;
namespace vw = std::views;

namespace items {
    bool CompositeItem::isCompositeType() { return true; }

    float CompositeItem::availableQuantity() {
        std::unordered_map<items::Item *, float> quantities;

        forEachSimpleIngredient([&quantities](Ingredient i) {
            quantities[i.item] += i.quantity;
        });

        return rng::min(
                  quantities | vw::transform([](auto const &p) {
                      return p.first->availableQuantity() / p.second;
                  })
                );
    }

    CompositeItem &CompositeItem::setIngredients(std::vector<Ingredient> ingredients) {
        _ingredients = std::move(ingredients);
        return *this;
    }

    CompositeItem &CompositeItem::forEachSimpleIngredient(const std::function<void(Ingredient)> &f) {
        for (auto const &i : _ingredients) {
            if (i.item->isCompositeType()) {
                auto *ci = dynamic_cast<CompositeItem *>(i.item);
                ci->forEachSimpleIngredient(f);
            } else {
                f(i);
            }
        }
        return *this;
    }

    CompositeItem &CompositeItem::throwQuantity(float quantity) {
        for(auto &i : _ingredients) {
            i.item->throwQuantity(i.quantity * quantity);
        }
        return *this;
    }

float CompositeItem::price() const {
    return std::accumulate(_ingredients.begin(), _ingredients.end(), 0.0f,
                           [](float acc, Ingredient const &i) {
                               return acc + i.item->price() * i.quantity;
                           });
}

CompositeItem::CompositeItem(Market *market, std::string name) :
    Item(market, std::move(name), 0) {}
} // items