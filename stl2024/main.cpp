#include "Market.h"
#include "Offer.h"
#include "items/Item.h"

#include <iostream>
#include <algorithm>
#include <ranges>
#include <sstream>
#include <memory>

namespace rng = std::ranges;
namespace vw = rng::views;

int stl(const bool allowCompositeTypes = true) {
  std::unique_ptr<Market> market = Market::readMarket(std::cin);
  using namespace items;

  std::vector<Offer> offers;
  int days;
  std::cin >> days;
  while (days--) {
    int day, offersCount;
    std::cin >> day >> offersCount;
    while (offersCount--) {
      Offer offer{.day = day};
      std::cin >> offer;
      offers.push_back(std::move(offer));
    }

  }

  int noOfCompositeItems;
  std::cin >> noOfCompositeItems;
  std::cin.ignore();
  std::stringstream ss{};
  for (int _ : vw::iota(0, noOfCompositeItems)) {
    std::string line;
    std::getline(std::cin, line);
    ss << line << "\n";
  }

  while(allowCompositeTypes) {
    std::stringstream in(ss.str());
    bool failed = false;
    std::string line;
    for (int _ : vw::iota(0, noOfCompositeItems)) {
      try {
        market->registerCompositeItemFromIS(in);
        in.ignore();
      }catch (std::runtime_error &e) {
        if(std::string{e.what()}.find("INVALID_INGREDIENT") != std::string::npos)
          failed = true;
      }
    }

    if(!failed) {
      break;
    }
  }

  for (auto &offer : offers) {
    if(market->getItem(offer.productName) == nullptr)
      continue;
    float soldQuantity = market->processOffer(offer);
    if(soldQuantity > 0)
      std::cout << offer.productName << " " << soldQuantity << "\n";
  }
  std::cout << market->income() << "\n";
  return 0;
}

int main(int argc, char **argv) {
  std::vector<std::string> args(argv, argv + argc);
  if (rng::find(args, std::string{"--no-composite"}) != args.end())
    return stl(false);

  return stl(true);
}