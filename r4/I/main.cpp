#include <algorithm>
#include <iostream>
#include <vector>

#define int long long

void solve() {
  int n, water;
  std::cin >> n >> water;
  std::vector<int> corals(n);
  for (int i = 0; i < n; i++)
    std::cin >> corals[i];

  std::sort(corals.begin(), corals.end());
  int waterRequired = 0;
  int i = 0;
  for (; i + 1 < n; i++) {
    int heigthDiff = corals[i + 1] - corals[i];
    if (waterRequired + heigthDiff * (i + 1) > water)
      break;
    waterRequired += heigthDiff * (i + 1);
  }
  water -= waterRequired;
  std::cout << corals[i] + water / (i + 1) << '\n';
}

int32_t main() {
  int t;
  std::cin >> t;
  while (t--)
    solve();
}
