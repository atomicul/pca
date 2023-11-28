#include <iostream>
#include <list>

int main() {
  std::string str;
  std::cin >> str;
  str.pop_back();

  std::list<int> list;
  int i = 1;
  list.push_back(i++);
  auto it = list.begin();
  for (char c : str) {
    if (c == 'l')
      list.insert(it, i++);
    else
      list.insert(++it, i++);
    it--;
  }

  for (int num : list)
    std::cout << num << "\n";
}
