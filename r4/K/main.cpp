#include <algorithm>
#include <iostream>
#include <vector>

int main() {
  int plates, a, b;
  std::cin >> plates >> a >> b;
  for (int i = std::min(a, b); i >= 1; i--) {
    if (a / i + b / i >= plates) {
      std::cout << i << std::endl;
      return 0;
    }
  }
  return 1;
}
