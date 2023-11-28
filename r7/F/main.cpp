#include <iostream>
#include <unordered_map>
#include <vector>

/* typedef long long ll; */
using std::unordered_map, std::cin, std::cout, std::vector;

int main() {
  std::ios_base::sync_with_stdio(false), cin.tie(0), cout.tie(0);

  int t;
  cin >> t;
  while (t--) {
    unordered_map<int, vector<int>> index;
    int n, k;
    cin >> n >> k;
    index.reserve(n);
    for (int i = 0; i < n; i++) {
      int x;
      cin >> x;
      index[x].push_back(i);
    }

    while (k--) {
      int a, b;
      cin >> a >> b;
      if (index[a].empty() || index[b].empty()) {
        cout << "NO\n";
        continue;
      }
      if (index[b].back() < index[a].front())
        cout << "NO\n";
      else
        cout << "YES\n";
    }
  }
}
