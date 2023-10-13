#include <algorithm>
#include <iostream>
#include <iterator>
#include <numeric>
#include <utility>
#include <vector>

std::vector<bool> solve() {
  int n, unlucky;
  std::cin >> n >> unlucky;
  std::vector<std::pair<int, int>> arr(n);
  for (int i = 0; i < n; i++) {
    arr[i].first = i;
    std::cin >> arr[i].second;
  }

  std::ranges::sort(arr, {}, &std::pair<int, int>::second);
  std::vector<bool> coloring(n, false);
  for (int i = 0; i < n; i++) {
    int x = unlucky - arr[i].second;
    if (x < arr[i].second)
      break;

    if (x == arr[i].second) {
      int idx = std::distance(
          arr.begin(),
          std::ranges::upper_bound(arr.begin() + i, arr.end(), x, {},
                                   &std::pair<int, int>::second));
      for (int j = (i + idx) / 2; j < idx; j++)
        coloring[arr[j].first] = true;
      break;
    }

    auto range_iterators = std::ranges::equal_range(
        arr.begin() + i, arr.end(), x, {}, &std::pair<int, int>::second);
    std::pair<int, int> range{
        std::distance(arr.begin(), range_iterators.begin()),
        std::distance(arr.begin(), range_iterators.end())};

    for (int j = range.first; j < range.second; j++)
      coloring[arr[j].first] = true;
  }
  return coloring;
}

int main() {
  int t;
  std::cin >> t;
  while (t--) {
    std::ranges::copy(solve(), std::ostream_iterator<bool>(std::cout, " "));
    std::cout << '\n';
  }
}
