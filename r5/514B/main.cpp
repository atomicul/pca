#include <coroutine>
#include <iostream>
#include <numeric>
#include <set>
#include <utility>

std::pair<int, int> simplify_fraction(std::pair<int, int> fraction) {
  int &a = fraction.first, &b = fraction.second;
  if (a == 0)
    return std::make_pair(0, 1);
  if (b == 0)
    return std::make_pair(1, 0);

  if (b < 0)
    a = -a, b = -b;

  int gcd = std::gcd(a, b);
  a /= gcd, b /= gcd;
  return fraction;
}

int main() {
  int stormtroopers;
  std::cin >> stormtroopers;
  std::pair<int, int> han_solo;
  std::cin >> han_solo.first >> han_solo.second;

  std::set<std::pair<int, int>> stormtrooper_slopes;
  for (int i = 0; i < stormtroopers; i++) {
    std::pair<int, int> stormtrooper;
    std::cin >> stormtrooper.first >> stormtrooper.second;
    stormtrooper.first -= han_solo.first,
        stormtrooper.second -= han_solo.second;
    stormtrooper_slopes.insert(simplify_fraction(stormtrooper));
  }
  std::cout << stormtrooper_slopes.size() << std::endl;
}
