#include <algorithm>
#include <iostream>
#include <vector>

int main() {
  using std::vector, std::cin, std::cout;
  int t;
  cin >> t;
  while (t--) {
    int n;
    cin >> n;
    vector<int> vec(n);
    for (auto &p : vec)
      cin >> p;

    std::sort(vec.begin(), vec.end());

    int duplicates{};
    for (auto it = vec.begin(); it + 1 < vec.end(); it++)
      duplicates += it[0] == it[1];
    cout << vec.size() - duplicates - duplicates % 2 << '\n';
  }
}
