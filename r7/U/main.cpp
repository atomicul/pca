#include <algorithm>
#include <iostream>
#include <ranges>
#include <vector>

struct Monster {
  int hp, power;
};

using namespace std::ranges::views;
namespace rng = std::ranges;

int main() {
  int t;
  std::cin >> t;
  while (t--) {
    int n, hero_power;
    std::cin >> n >> hero_power;

    std::vector<Monster> monsters(n);
    for (auto property : {&Monster::hp, &Monster::power})
      for (auto &i : monsters)
        std::cin >> i.*property;

    rng::sort(monsters, {}, &Monster::hp);

    for (auto it = monsters.rbegin() + 1; it < monsters.rend(); it++)
      it->power = std::min(it->power, it[-1].power);

    int damaged_caused = 0;
    auto alive_monsters_begin = monsters.begin();
    while (hero_power > 0 && alive_monsters_begin < monsters.end()) {
      damaged_caused += hero_power;
      alive_monsters_begin =
          rng::upper_bound(alive_monsters_begin, monsters.end(), damaged_caused,
                           {}, &Monster::hp);
      hero_power -= alive_monsters_begin->power;
    }

    if (alive_monsters_begin >= monsters.end())
      std::cout << "YES\n";
    else
      std::cout << "NO\n";
  }
}
