#include <algorithm>
#include <iostream>
#include <numeric>
#include <vector>

#define DEBUG 0
#if DEBUG
#include <fstream>
namespace std {
ifstream fin("input.txt");
}
#define cin fin
#endif

int main() {
  int n, time;
  std::cin >> n >> time;
  std::vector<int> books(n + 1, 0);
  for (int i = 1; i <= n; ++i)
    std::cin >> books[i];

  std::partial_sum(books.begin(), books.end(), books.begin());
  int ans = 0;
  for (auto it = books.begin() + 1; it < books.end(); it++) {
    ans =
        std::max(ans, (int)std::distance(it, std::upper_bound(it, books.end(),
                                                              it[-1] + time)));
  }
  std::cout << ans << std::endl;
}
