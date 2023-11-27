#include <climits>
#include <fstream>
#include <iostream>
#include <vector>

#define int long long

class SegmentTree {
public:
  SegmentTree(std::vector<int> const &vec) : size(vec.size()) {
    tree.resize(size * 4 + 1);
    build(1, 0, size, vec);
  }

  void add(int l, int r, int val) { lazy_add(1, 0, size, l, r, val); }
  auto min(int l, int r) { return get_min(1, 0, size, l, r); }

private:
  struct node_t {
    int min{}, pos{}, lazy{};

    bool operator<(node_t const &rhs) const { return min <= rhs.min; }
  };

  void wake_up(int node, int l, int r) {
    if (!tree[node].lazy)
      return;

    tree[node].min += tree[node].lazy;

    if (r - l > 1) {
      tree[node * 2].lazy += tree[node].lazy;
      tree[node * 2 + 1].lazy += tree[node].lazy;
    }

    tree[node].lazy = 0;
  }

  void update_node(int n, int l, int r) {
    wake_up(n, l, r);
    if (r - l == 1)
      return;
    int mid = (l + r) / 2;
    wake_up(n * 2, l, mid);
    wake_up(n * 2 + 1, mid, r);

    tree[n] = std::min(tree[n * 2 + 1], tree[n * 2]);
  }

  void build(int node, int l, int r, std::vector<int> const &vec) {
    if (r - l == 1) {
      tree[node] = {vec[l], l, 0};
      return;
    }

    int mid = (l + r) / 2;
    build(node * 2, l, mid, vec);
    build(node * 2 + 1, mid, r, vec);

    update_node(node, l, r);
  }

  void lazy_add(int node, int l, int r, int ql, int qr, int val) {
    if (ql <= l && r <= qr) {
      tree[node].lazy += val;
      return;
    }
    if (r <= ql || l >= qr)
      return;

    int mid = (l + r) / 2;
    lazy_add(node * 2, l, mid, ql, qr, val);
    lazy_add(node * 2 + 1, mid, r, ql, qr, val);

    update_node(node, l, r);
  }

  node_t get_min(int node, int l, int r, int ql, int qr) {
    if (ql <= l && r <= qr) {
      wake_up(node, l, r);
      return tree[node];
    }
    if (r <= ql || l >= qr)
      return {INT_MAX, INT_MAX, INT_MAX};

    int mid = (l + r) / 2;
    return std::min(get_min(node * 2 + 1, mid, r, ql, qr),
                    get_min(node * 2, l, mid, ql, qr));
  }

  std::vector<node_t> tree;
  int size;
};

int32_t main() {
  std::ifstream fin("biscuiti.in");
  std::ofstream fout("biscuiti.out");

  int n;
  fin >> n;

  std::vector<int> vec(n);
  for (auto &i : vec)
    fin >> i;

  int acc{};

  for (auto el : vec)
    acc -= el;

  SegmentTree tree(vec);
  for (int day = 1; day <= n; day++) {
    auto min = tree.min(0, n);
    acc += min.min;
    tree.add(0, min.pos, day);
    tree.add(min.pos, min.pos + 1, 1LL << 60);
  }

  fout << acc << '\n';
}
