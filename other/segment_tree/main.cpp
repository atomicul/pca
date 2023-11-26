#include <fstream>
#include <iostream>
#include <vector>

#define int long long

class SegmentTree {
public:
  SegmentTree(std::vector<int> const &vec) : size(vec.size()) {
    tree.resize(4 * vec.size() + 1, 0);
    build(1, 0, size, vec);
  }

  void update(int pos, int val) { upd(1, 0, size, pos, val); }

  int query(int l, int r) { return qry(1, 0, size, l, r); }

private:
  std::vector<int> tree;
  int size;

  void build(int node, int l, int r, const std::vector<int> &vec) {
    if (r - l == 1) {
      tree[node] = vec[l];
      return;
    }

    int mid = (l + r) / 2;
    build(node * 2, l, mid, vec);
    build(node * 2 + 1, mid, r, vec);

    tree[node] = tree[node * 2] + tree[node * 2 + 1];
  }

  void upd(int node, int l, int r, int pos, int val) {
    if (r - l == 1) {
      tree[node] = val;
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
    if (qr <= l || ql >= r)
      return 0;

    int mid = (l + r) / 2;
    return qry(node * 2, l, mid, ql, qr) + qry(node * 2 + 1, mid, r, ql, qr);
  }
};

int32_t main() {
  std::ifstream fin("datorii.in");
  std::ofstream fout("datorii.out");

  int n, queries;
  fin >> n >> queries;

  std::vector<int> loan(n);
  for (int &i : loan)
    fin >> i;

  SegmentTree tree(loan);
  for (int i = 0; i < queries; i++) {
    int command;
    fin >> command;
    if (command == 0) {
      int day, payment;
      fin >> day >> payment;
      day--;
      loan[day] -= payment;
      tree.update(day, loan[day]);
    } else if (command == 1) {
      int l, r;
      fin >> l >> r;
      l--, r--;
      fout << tree.query(l, r + 1) << '\n';
    }
  }
}
