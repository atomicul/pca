#include <algorithm>
#include <iostream>
#include <vector>

int main() {
  int n;
  std::cin >> n;
  std::vector<int> coins(n);
  for (int &i : coins)
    std::cin >> i;

  std::sort(coins.begin(), coins.end());

  int max = 1, c = 1;
  for (auto it = coins.begin() + 1; it < coins.end(); it++) {
    if (*it == it[-1])
      c++;
    else
      c = 1;
    max = std::max(max, c);
  }
  std::cout << max << std::endl;
}
