#include <iostream>
#include <limits>
#include <vector>

int main() {
  int t;
  std::cin >> t;
  while (t--) {
    int n;
    std::cin >> n;
    long long ans{};
    bool zero_prefix = true;
    while (n-- > 1) {
      int x;
      std::cin >> x;
      if (!x && zero_prefix)
        continue;
      zero_prefix = false;
      ans += x ? x : 1;
    }
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    std::cout << ans << '\n';
  }
}
