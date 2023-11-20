#include <algorithm>
#include <iostream>
#include <iterator>
#include <numeric>
#include <vector>

#define int long long

int32_t main() {
  int n, k;
  std::cin >> n >> k;
  std::vector<int> nums(n);
  std::copy_n(std::istream_iterator<int>(std::cin), n, nums.begin());
  for (int &x : nums)
    x += 1LL << 32;

  std::sort(nums.begin(), nums.end());
  std::vector<int> part_sum(n + 1, 0);
  std::partial_sum(nums.begin(), nums.end(), part_sum.begin() + 1);

  int occurences = 0, number{};
  for (int i = 0; i < n;) {
    auto it = nums.begin() + i;
    int next =
        std::distance(nums.begin(), std::upper_bound(it + 1, nums.end(), *it));
    int l = 0, r = i;
    while (l < r) {
      int mid = (l + r) / 2;
      int x = (part_sum[i] - (*it) * i) - (part_sum[mid] - (*it) * mid);
      if (-k > x)
        l = mid + 1;
      else
        r = mid;
    }
    if (next - l > occurences)
      occurences = next - l, number = *it;
    i = next;
  }
  std::cout << occurences << ' ' << number - (1LL << 32) << std::endl;
}
