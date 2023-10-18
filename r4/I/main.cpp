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
  std::vector<int> water_required(n, 0);
  for (int i = 1; i < n; i++) {
    const int height_diff = corals[i] - corals[i - 1];
    water_required[i] = water_required[i - 1] + height_diff * i;
  }
  auto it =
      std::upper_bound(water_required.begin(), water_required.end(), water);
  it--;
  water -= *it;
  int pos = std::distance(water_required.begin(), it);
  std::cout << corals[pos] + water / (pos + 1) << '\n';
}

int32_t main() {
  int t;
  std::cin >> t;
  while (t--)
    solve();
}
