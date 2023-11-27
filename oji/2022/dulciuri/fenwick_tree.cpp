#include <fstream>
#include <iomanip>
#include <iostream>
#include <tuple>
#include <vector>

class FenwickTree {
public:
  FenwickTree(int n) : tree(n, 0) {}

  void update(int pos, int val) {
    for (; pos < tree.size(); pos |= (pos + 1))
      tree[pos] += val;
  }

  int query(int pos) {
    int sum{};
    for (; pos >= 0; pos = (pos & (pos + 1)) - 1)
      sum += tree[pos];
    return sum;
  }
  int query(int l, int r) { return query(r - 1) - query(l - 1); }

private:
  std::vector<int> tree;
};

FenwickTree treeX(1E6 + 16), treeY(1E6 + 16);
FenwickTree *getTree(int command) {
  if (command == 1)
    return &treeX;
  return &treeY;
}

void sortRange(int &x, int &y) {
  if (x <= y)
    return;
  std::swap(x, y);
  /* x++, y++; */
}

double add(FenwickTree &tree, int x, int y) {
  if (x == y)
    return tree.query(x, x + 1);
  return tree.query(x, y) / (double)std::abs(x - y);
}

int main() {
  std::ifstream fin("dulciuri.in");
  std::ofstream fout("dulciuri.out");

  int queries;
  fin >> queries;

  for (int i = 0; i < queries; i++) {
    int code;
    fin >> code;
    if (code == 3) {
      int x1, y1, x2, y2;
      fin >> x1 >> y1 >> x2 >> y2;

      sortRange(x1, x2);
      sortRange(y1, y2);

      double ans{};
      ans += add(treeX, x1, x2);
      ans += add(treeY, y1, y2);
      fout << std::setprecision(10) << ans << '\n';
    } else {
      auto tree = getTree(code);
      int pos, val;
      fin >> pos >> val;
      tree->update(pos, val);
    }
  }
}
