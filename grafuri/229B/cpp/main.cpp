#include <iostream>
#include <queue>
#include <unordered_set>
#include <vector>

int planets, teleporters;
std::vector<std::vector<std::pair<int, int>>> adj;
std::vector<std::unordered_set<int>> busy_times;

std::vector<int> dijkstra(int begin) {
  std::vector<int> out(planets, 1 << 30);
  out[begin] = 0;
  std::priority_queue<std::pair<int, int>> pq;

  int t = 0;
  while (busy_times[begin].count(t))
    t++;

  pq.emplace(-t, begin);
  std::vector<bool> visited(planets, false);
  while (!pq.empty()) {
    auto [dist, node] = pq.top();
    dist *= -1;
    pq.pop();

    if (visited[node])
      continue;
    visited[node] = true;

    for (auto [adj_node, adj_dist] : adj[node]) {
      int t = dist + adj_dist;
      if (t >= out[adj_node])
        continue;
      out[adj_node] = t;
      while (busy_times[adj_node].count(t))
        t++;

      if (!visited[adj_node])
        pq.emplace(-t, adj_node);
    }
  }

  for (auto &x : out)
    if (x == (1 << 30))
      x = -1;
  return out;
}

int main() {
  std::cin >> planets >> teleporters;
  adj.resize(planets);
  for (int i = 0; i < teleporters; i++) {
    int a, b, dist;
    std::cin >> a >> b >> dist;
    a--, b--;
    adj[a].emplace_back(b, dist);
    adj[b].emplace_back(a, dist);
  }
  busy_times.resize(planets);
  for (int i = 0; i < planets; i++) {
    int l;
    std::cin >> l;
    for (int j = 0; j < l; j++) {
      int x;
      std::cin >> x;
      busy_times[i].insert(x);
    }
  }

  std::cout << dijkstra(0)[planets - 1] << std::endl;
}
