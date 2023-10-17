#include <iostream>
#include <limits>
#include <string>
#include <unordered_map>

template <typename T> class CountingSet {
  std::unordered_map<T, int> mp;

public:
  void add(const T &x) {
    if (mp.count(x) == 0)
      mp[x] = 1;
    else
      mp[x]++;
  }

  void remove(const T &x) {
    if (mp.count(x) == 0)
      return;
    if (mp[x] == 1)
      mp.erase(x);
    else
      mp[x]--;
  }

  int size() const { return mp.size(); }
};

int main() {
  int t;
  std::cin >> t;
  while (t--) {
    int len;
    std::cin >> len;
    std::string str;
    std::cin >> str;

    CountingSet<char> a, b;
    for (char x : str)
      a.add(x);

    int ans = 0;
    for (char ch : str) {
      if (!a.size())
        break;
      a.remove(ch);
      b.add(ch);
      ans = std::max(ans, a.size() + b.size());
    }
    std::cout << ans << '\n';
  }
}
