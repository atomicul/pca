//
// Created by pijon on 2/28/24.
//

#ifndef STL2023_COMPOSITEITEM_H
#define STL2023_COMPOSITEITEM_H

#include "Item.h"
#include "Ingredient.h"

#include <vector>
#include <functional>

namespace items {

    class CompositeItem : public Item {
        std::vector<Ingredient> _ingredients{};

    public:
        CompositeItem(Market *market, std::string name);

        bool isCompositeType() override;

        float available_quantity() override;

        float price() const override;

        CompositeItem &setIngredients(std::vector<Ingredient> ingredients);

        CompositeItem &throwQuantity(float quantity) override;
    private:
        CompositeItem &forEachSimpleIngredient(std::function<void(Ingredient)> const &f);
    };

} // items

#endif //STL2023_COMPOSITEITEM_H
