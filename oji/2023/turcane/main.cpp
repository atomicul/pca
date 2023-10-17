#include <fstream>
#include <iostream>
#include <vector>

int main() {
  std::ifstream fin("turcane.in");
  std::ofstream fout("turcane.out");

  int c, n, m, h, v, d;
  fin >> c >> n >> m >> h >> v >> d;

  if (c == 1) {
    std::vector<std::vector<int>> dp(n, std::vector<int>(m, 0));
    for (int i = 0; i < n; i++) {
      for (int j = 0; j < m; j++) {
      }
    }
  }
}
