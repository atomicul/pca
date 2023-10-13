#include <iostream>
#include <queue>
#include <utility>
#include <vector>

using iPair = std::pair<int, int>;

constexpr int chessboard_size = 8;

std::vector<iPair> knight_moves = {{2, 1}, {2, -1}, {-2, 1}, {-2, -1},
                                   {1, 2}, {1, -2}, {-1, 2}, {-1, -2}};

bool in_bounds(iPair p) {
  for (int i : std::vector{p.first, p.second}) {
    if (i < 0 || i > chessboard_size - 1)
      return false;
  }
  return true;
}

iPair chess_notation_to_pair(const std::string &pos) {
  return {pos[0] - 'a', pos[1] - '1'};
}

int lee(iPair st, iPair end) {
  auto visited =
      std::vector(chessboard_size, std::vector(chessboard_size, false));
  std::queue<std::pair<int, iPair>> q;
  q.emplace(0, st);
  visited[st.first][st.second] = true;
  while (!q.empty()) {
    auto [dist, pos] = q.front();
    q.pop();

    if (pos == end)
      return dist;

    for (iPair d : knight_moves) {
      iPair p = {pos.first + d.first, pos.second + d.second};
      if (in_bounds(p) && !visited[p.first][p.second]) {
        visited[p.first][p.second] = true;
        q.emplace(dist + 1, p);
      }
    }
  }
  return -1;
}

int main() {
  std::string pos1, pos2;
  while (std::cin >> pos1 >> pos2) {
    std::cout << "To get from " << pos1 << " to " << pos2 << " takes "
              << lee(chess_notation_to_pair(pos1), chess_notation_to_pair(pos2))
              << " knight moves.\n";
  }
}
