#include <algorithm>
#include <iostream>
#include <vector>

#define int long long

int32_t main() {
  using std::vector, std::cin, std::cout;
  int n, k;
  cin >> n >> k;
  vector<int> vec(n);
  for (auto &i : vec)
    cin >> i;
  std::sort(vec.begin(), vec.end());

  int acc{};
  int max_range{}, max_number{};
  for (auto l = vec.begin(), r = vec.begin(); r < vec.end();) {
    if (l > r) {
      r++;
      continue;
    }

    int size = std::distance(l, r + 1);
    if (size > max_range)
      max_range = size, max_number = *r;

    if (r + 1 == vec.end())
      break;

    int diff = r[1] - *r;
    if (acc + diff * size > k) {
      acc -= *r - *l;
      l++;
    } else {
      acc += diff * size;
      r++;
    }
  }
  cout << max_range << ' ' << max_number << '\n';
}
