#include <iostream>
#include <set>
#include <tuple>

int main() {
  int n;
  std::cin >> n;
  std::set<std::tuple<int, int, int>> seats; // (passangers, width, row number)
  for (int i = 1; i <= n; i++) {
    int width;
    std::cin >> width;
    seats.emplace(0, width, i);
  }

  std::string people;
  std::cin >> people;
  for (char p : people) {
    if (p == '0') {
      auto seat = *seats.begin();
      seats.erase(seats.begin());
      std::get<0>(seat)++;
      seats.insert(seat);
      std::cout << std::get<2>(seat) << " ";
    } else {
      auto seat = *seats.rbegin();
      seats.erase(std::prev(seats.end()));
      std::cout << std::get<2>(seat) << " ";
    }
  }
  std::cout << std::endl;
}
