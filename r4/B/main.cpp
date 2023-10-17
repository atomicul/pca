#include <iostream>
#include <string>

constexpr int TESTCASE_LINES = 8;

int main() {
  int t;
  std::cin >> t;
  std::cin.ignore();
  while (t--) {
    std::string out;
    for (int i = 0; i < TESTCASE_LINES; i++) {
      std::string line;
      std::getline(std::cin, line);
      const int pos = line.find_first_not_of(".");
      if (pos == std::string::npos)
        continue;
      out += line[pos];
    }
    std::cout << out << '\n';
  }
}
