#include <algorithm>
#include <iostream>
#include <numeric>
#include <vector>

bool possible(std::vector<int> const &shoes) {
  for (auto it = shoes.begin(); it < shoes.end(); it++) {
    bool unique = true;
    if (it > shoes.begin())
      unique = unique && *it != it[-1];
    if (it < shoes.end() - 1)
      unique = unique && *it != it[1];
    if (unique)
      return false;
  }
  return true;
}

int main() {
  int t;
  std::cin >> t;
  while (t--) {
    int n;
    std::cin >> n;
    std::vector<int> shoes(n);
    for (int &i : shoes)
      std::cin >> i;

    if (!possible(shoes)) {
      std::cout << -1 << '\n';
      continue;
    }

    for (int i = 0, j = 1; i < j && j <= n;) {
      if (j < n && shoes[i] == shoes[j]) {
        std::cout << ++j << ' ';
        continue;
      }
      std::cout << i + 1 << ' ';
      i = j++;
    }
    std::cout << '\n';
  }
}
