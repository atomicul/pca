#include <cassert>
#include <climits>
#include <iostream>
#include <map>
#include <numeric>
#include <stack>
#include <string>
#include <variant>
#include <vector>

typedef long long ll;

template <typename T, typename Aggregate> class SegmentTree {
  struct _Aggregate : public Aggregate {
    struct NullElement {};
    NullElement operator()() { return NullElement(); }
    using R = std::variant<T, NullElement>;
    T operator()(T const &a, NullElement b) { return a; }
    T operator()(NullElement a, T const &b) { return b; }
    R operator()(R const &a, R const &b) {
      T const *ta, *tb;
      if ((ta = std::get_if<T>(&a)) && (tb = std::get_if<T>(&b)))
        return static_cast<Aggregate *>(this)->operator()(*ta, *tb);
      if ((ta = std::get_if<T>(&a)) || (ta = std::get_if<T>(&b)))
        return *ta;
      return this->operator()();
    }
  };

public:
  SegmentTree(std::vector<T> const &vec) : size(vec.size()) {
    tree.resize(4 * vec.size() + 1, 0);
    build(Iterator(this), vec);
  }

  void update(int pos, const T &val) { upd(Iterator(this), pos, val); }

  T query(int l, int r) const {
    auto var = qry(ConstIterator(this), l, r);
    auto *out = std::get_if<T>(&var);
    assert(out != nullptr);
    return *out;
  }

private:
  std::vector<T> tree;
  int size;

  class ConstIterator {
  protected:
    size_t index;
    int l, r;
    std::vector<T> const &tree;

    int mid() { return (l + r) / 2; }

  public:
    const T &operator*() const { return tree[index]; }
    const T *operator->() const { return tree[index]; }

    int leftBound() const { return l; }
    int rightBound() const { return r; }

    int segmentSize() const { return r - l; }

    ConstIterator(SegmentTree<T, Aggregate> const *parent)
        : tree(parent->tree), index(1), l(0), r(parent->size) {}

    ConstIterator(ConstIterator const &other) = default;

    ConstIterator &advanceLeft() {
      r = mid();
      index = 2 * index;
      return *this;
    }
    ConstIterator &advanceRight() {
      l = mid();
      index = 2 * index + 1;
      return *this;
    }

    ConstIterator &advanceTowards(int x) {
      assert(l <= x && x < r);
      if (x < mid())
        advanceLeft();
      else
        advanceRight();
      return *this;
    }

    ConstIterator nextLeft() const {
      return ConstIterator(*this).advanceLeft();
    }
    ConstIterator nextRight() const {
      return ConstIterator(*this).advanceRight();
    }
    ConstIterator nextTowards(int x) const {
      return ConstIterator(*this).advanceTowards(x);
    }
  };

  class Iterator : public ConstIterator {
  protected:
    std::vector<T> &tree;

  public:
    Iterator(SegmentTree<T, Aggregate> *parent)
        : tree(parent->tree), ConstIterator(parent) {}

    T &operator*() const { return tree[this->index]; }
    T *operator->() const { return tree[this->index]; }
    Iterator &advanceLeft() {
      ConstIterator::advanceLeft();
      return *this;
    }
    Iterator &advanceRight() {
      ConstIterator::advanceRight();
      return *this;
    }
    Iterator &advanceTowards(int x) {
      ConstIterator::advanceTowards(x);
      return *this;
    }
    Iterator nextLeft() const { return Iterator(*this).advanceLeft(); }
    Iterator nextRight() const { return Iterator(*this).advanceRight(); }
    Iterator nextTowards(int x) const {
      return Iterator(*this).advanceTowards(x);
    }
  };

  T evalChildren(ConstIterator const node) {
    assert(node.segmentSize() > 1);
    auto variant = _Aggregate()(*node.nextLeft(), *node.nextRight());
    const T *x = std::get_if<T>(&variant);
    assert(x != nullptr);
    return *x;
  }

  void build(Iterator const node, const std::vector<T> &vec) {
    if (node.segmentSize() == 1) {
      *node = vec[node.leftBound()];
      return;
    }

    build(node.nextLeft(), vec);
    build(node.nextRight(), vec);

    *node = evalChildren(node);
  }

  void upd(Iterator const node, int pos, const T &val) {
    if (node.segmentSize() == 1) {
      *node = val;
      return;
    }

    upd(node.nextTowards(pos), pos, val);

    *node = evalChildren(node);
  }

  std::variant<T, typename _Aggregate::NullElement>
  qry(ConstIterator const node, int l, int r) const {
    if (l <= node.leftBound() && node.rightBound() <= r)
      return *node;
    if (r <= node.leftBound() || l >= node.rightBound())
      return _Aggregate()();

    return _Aggregate()(qry(node.nextLeft(), l, r),
                        qry(node.nextRight(), l, r));
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
    vector<ll> pillars(n);
    for (ll &i : pillars)
      cin >> i;

    vector<ll> partsum(pillars.size());
    partial_sum(pillars.begin(), pillars.end(), partsum.begin());

    for (int i = 0; i < n; i++)
      pillars[i] += i;

    const SegmentTree<ll, Max> maxTree(pillars);

    ll minim = LONG_LONG_MAX;
    for (int i = 0; i + k <= n; i++) {
      ll maxim = maxTree.query(i, i + k) - i;
      maxim *= k;
      maxim -= k * (k - 1) / 2;

      ll sum = partsum[i + k - 1] - (i > 0 ? partsum[i - 1] : 0);
      minim = min(maxim - sum, minim);
    }
    cout << minim << endl;
  }
}
