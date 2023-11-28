#include <algorithm>
#include <iostream>
#include <numeric>
#include <vector>

int main() {
  int n, q;
  std::cin >> n >> q;
  std::vector<long long> items(n + 1, 0);
  for (auto it = items.begin() + 1; it < items.end(); it++)
    std::cin >> *it;
  std::sort(items.begin() + 1, items.end());
  std::partial_sum(items.begin(), items.end(), items.begin());

  while (q--) {
    int purchase, free;
    std::cin >> purchase >> free;

    std::cout << items.end()[-purchase + free - 1] - items.end()[-purchase - 1]
              << '\n';
  }
}
