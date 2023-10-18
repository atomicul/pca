#include <algorithm>
#include <iostream>
#include <vector>

int main() {
  int n, m;
  std::cin >> n >> m;
  std::vector<int> song_start_time(n, 0);
  for (int i = 1; i <= n; i++) {
    int song_length, song_repeats;
    std::cin >> song_length >> song_repeats;
    if (i == n)
      break;
    song_start_time[i] = song_start_time[i - 1] + song_length * song_repeats;
  }
  for (int i = 0; i < m; i++) {
    int x;
    std::cin >> x;
    std::cout << std::distance(song_start_time.begin(),
                               std::lower_bound(song_start_time.begin(),
                                                song_start_time.end(), x))
              << '\n';
  }
}
