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
    decltype(SegmentTree<T, Aggregate>::tree) &tree;

    int mid() { return (l + r) / 2; }

  public:
    const T &operator*() const { return tree[index]; }
    const T *operator->() const { return tree[index]; }

    int leftBound() const { return l; }
    int rightBound() const { return r; }

    int segmentSize() const { return r - l; }

    ConstIterator(SegmentTree<T, Aggregate> const *parent)
        : tree(const_cast<decltype(tree)>(parent->tree)), index(1), l(0),
          r(parent->tree.size()) {}

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
      ConstIterator it(*this);
      it.advanceLeft();
      return it;
    }

    ConstIterator nextRight() const {
      ConstIterator it(*this);
      it.advanceRight();
      return it;
    }

    ConstIterator nextTowards(int x) const {
      ConstIterator it(*this);
      it.advanceTowards(x);
      return it;
    }
  };

  class Iterator : public ConstIterator {
  private:
    Iterator(ConstIterator const &other) : ConstIterator(other) {}

  public:
    using ConstIterator::ConstIterator;

    T &operator*() const { return this->tree[this->index]; }
    T *operator->() const { return this->tree[this->index]; }
    Iterator advanceLeft() { return Iterator(ConstIterator::advanceLeft()); }
    Iterator advanceRight() { return Iterator(ConstIterator::advanceRight()); }
    Iterator advanceTowards(int x) {
      return Iterator(ConstIterator::advanceTowards(x));
    }
    Iterator nextLeft() const { return Iterator(ConstIterator::nextLeft()); }
    Iterator nextRight() const { return Iterator(ConstIterator::nextRight()); }
    Iterator nextTowards(int x) const {
      return Iterator(ConstIterator::nextTowards(x));
    }
  };

  void build(Iterator const node, const std::vector<T> &vec) {
    if (node.segmentSize() == 1) {
      *node = vec[node.leftBound()];
      return;
    }

    build(node.nextLeft(), vec);
    build(node.nextRight(), vec);

    auto variant = _Aggregate()(*node.nextLeft(), *node.nextRight());
    const T *x = std::get_if<T>(&variant);
    assert(x != nullptr);

    *node = *x;
  }

  void upd(ConstIterator const node, int pos, const T &val) {
    if (node.segmentSize() == 1) {
      *node = val;
      return;
    }

    upd(node.nextTowards(pos), pos, val);

    tree[node] = _Aggregate()(*node.nextLeft(), *node.nextRight());
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
