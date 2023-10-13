#include <iostream>
#include <unordered_map>
#include <vector>

std::unordered_map<int, int> getLongestEq(std::vector<int> const &arr) {
  std::unordered_map<int, int> longest_eq_substr;
  int prev = -1, streak = 0;
  for (int el : arr) {
    if (el == prev) {
      streak++;
    } else {
      if (!longest_eq_substr.count(prev))
        longest_eq_substr[prev] = streak;
      else
        longest_eq_substr[prev] = std::max(longest_eq_substr[prev], streak);
      streak = 1;
      prev = el;
    }
  }
  if (!longest_eq_substr.count(prev))
    longest_eq_substr[prev] = streak;
  else
    longest_eq_substr[prev] = std::max(longest_eq_substr[prev], streak);
  return longest_eq_substr;
}

void solve() {
  int n;
  std::cin >> n;
  std::vector<int> a(n), b(n);
  for (int i = 0; i < n; ++i)
    std::cin >> a[i];
  for (int i = 0; i < n; ++i)
    std::cin >> b[i];

  const auto longest_eq_a = getLongestEq(a);
  int max = 0;
  for (auto [_, streak] : longest_eq_a)
    max = std::max(max, streak);
  for (const auto [num, streak] : getLongestEq(b)) {
    if (!longest_eq_a.count(num))
      max = std::max(max, streak);
    else
      max = std::max(max, streak + longest_eq_a.at(num));
  }
  std::cout << max << std::endl;
}

int main() {
  int t;
  std::cin >> t;
  while (t--)
    solve();
}
