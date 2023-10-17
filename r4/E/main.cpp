#include <iostream>
#include <string>

int main() {
  std::string str;
  std::getline(std::cin, str);
  for (int i = 0; i + 1 < str.size();) {
    int l = i, r = i + 1;
    while (l >= 0 && r < str.size() && str[l] == str[r])
      l--, r++;
    str.erase(str.begin() + l + 1, str.begin() + r);
    i = l + 1;
  }
  std::cout << str << std::endl;
}
