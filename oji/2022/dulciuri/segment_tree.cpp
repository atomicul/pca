#include <fstream>
#include <iomanip>
#include <iostream>
#include <tuple>
#include <vector>

class SegmentTree {
public:
  SegmentTree(int n) : size(n), tree(n * 4 + 1) {}

  void update(int pos, int val) { upd(1, 0, size, pos, val); }

  int query(int l, int r) { return qry(1, 0, size, l, r); }

private:
  void upd(int node, int l, int r, int pos, int val) {
    if (r - l == 1) {
      tree[node] += val;
      return;
    }

    int mid = (l + r) / 2;
    if (pos < mid)
      upd(node * 2, l, mid, pos, val);
    else
      upd(node * 2 + 1, mid, r, pos, val);

    tree[node] = tree[node * 2] + tree[node * 2 + 1];
  }

  int qry(int node, int l, int r, int ql, int qr) {
    if (ql <= l && r <= qr)
      return tree[node];
    if (qr <= l || r <= ql)
      return 0;

    int mid = (l + r) / 2;
    return qry(node * 2, l, mid, ql, qr) + qry(node * 2 + 1, mid, r, ql, qr);
  }

  int size;
  std::vector<int> tree;
};

SegmentTree treeX(1E6 + 16), treeY(1E6 + 16);
SegmentTree *getTree(int command) {
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

double add(SegmentTree &tree, int x, int y) {
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
