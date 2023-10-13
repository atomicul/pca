#include <cmath>
#include <fstream>
#include <iomanip>
#include <iostream>
#include <vector>

class FenwickTree {
  std::vector<int> vec;

public:
  FenwickTree(int size) : vec(size, 0) {}

  void update(int p, int v) {
    for (; p < vec.size(); p = (p | (p + 1)))
      vec[p] += v;
  }

  int sum(int p) {
    if (p <= 0)
      return 0;
    int s{};
    for (; p >= 0; p = (p & (p + 1)) - 1)
      s += vec[p];
    return s;
  }

  int sum(int st, int end) {
    if (end < st)
      return sum(end, st);
    return sum(end) - sum(st - 1);
  }
};

FenwickTree *treeX = new FenwickTree{1000002},
            *treeY = new FenwickTree{1000002};

FenwickTree *getTree(int p) {
  if (p == 1)
    return treeX;
  return treeY;
}

int main() {
  std::ifstream fin{"dulciuri.in"};
  std::ofstream fout{"dulciuri.out"};

  int n;
  fin >> n;
  for (int i = 0; i < n; i++) {
    int p;
    fin >> p;
    if (p == 3) {
      int x1, y1, x2, y2;
      fin >> x1 >> y1 >> x2 >> y2;
      fout << std::setprecision(15)
           << treeX->sum(x1, x2) / (double)std::max(1, std::abs(x2 - x1)) +
                  treeY->sum(y1, y2) / (double)std::max(1, std::abs(y2 - y1))
           << '\n';
    } else {
      FenwickTree *tree = getTree(p);
      int p, v;
      fin >> p >> v;
      tree->update(p, v);
    }
  }
}
