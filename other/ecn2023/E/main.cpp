#include <climits>
#include <iostream>
#include <map>
#include <numeric>
#include <stack>
#include <string>
#include <vector>

typedef long long ll;

template <typename T, typename Aggregate> class SegmentTree {
public:
  SegmentTree(std::vector<T> const &vec) : size(vec.size()) {
    tree.resize(4 * vec.size() + 1, 0);
    build(1, 0, size, vec);
  }

  void update(int pos, const T &val) { upd(1, 0, size, pos, val); }

  T query(int l, int r) const { return qry(1, 0, size, l, r); }

private:
  std::vector<T> tree;
  int size;

  void build(int node, int l, int r, const std::vector<T> &vec) {
    if (r - l == 1) {
      tree[node] = vec[l];
      return;
    }

    int mid = (l + r) / 2;
    build(node * 2, l, mid, vec);
    build(node * 2 + 1, mid, r, vec);

    tree[node] = Aggregate()(tree[node * 2], tree[node * 2 + 1]);
  }

  void upd(int node, int l, int r, int pos, const T &val) {
    if (r - l == 1) {
      tree[node] = val;
      return;
    }

    int mid = (l + r) / 2;
    if (pos < mid)
      upd(node * 2, l, mid, pos, val);
    else
      upd(node * 2 + 1, mid, r, pos, val);

    tree[node] = Aggregate()(tree[node * 2], tree[node * 2 + 1]);
  }

  T qry(int node, int l, int r, int ql, int qr) const {
    if (ql <= l && r <= qr)
      return tree[node];
    if (qr <= l || ql >= r)
      return 0;

    int mid = (l + r) / 2;
    return Aggregate()(qry(node * 2, l, mid, ql, qr),
                       qry(node * 2 + 1, mid, r, ql, qr));
  }
};

struct Max {
  ll operator()(ll a, ll b) { return std::max(a, b); }
};

int32_t main() {
  using namespace std;

  int t;
  cin >> t;
  while (t--) {
    int n, k;
    cin >> n >> k;
    vector<ll> a(n);
    for (ll &i : a)
      cin >> i;

    vector<ll> v1(a), v2(a);

    for (int i = 0; i < n; i++) {
      v1[i] += i;
      v2[n - i - 1] += i;
    }

    vector<ll> partsum(v2);
    partial_sum(partsum.begin(), partsum.end(), partsum.begin());
    const SegmentTree<ll, Max> maxTree(v1);

    ll minim = LONG_LONG_MAX;
    for (int i = 0; i < n - k + 1; i++) {
      ll maxim = maxTree.query(i, i + k);
      maxim -= i;
      maxim *= k;

      ll sum = 0;
      sum += partsum[i + k - 1];
      sum -= i > 0 ? partsum[i - 1] : 0;
      sum = sum - (ll)(n - k - i) * k;

      minim = min(maxim - sum, minim);
    }
    cout << minim << endl;
  }
}
