#include <fstream>
#include <functional>
#include <iostream>
#include <iterator>
#include <queue>
#include <stack>
#include <vector>

int nodes, edges;
std::vector<std::vector<int>> adj, radj;

void cycles(int start, std::function<void(int, int)> fn) {
  std::vector<int> visits(nodes, 0);
  visits[start] = 1;
  std::queue<std::pair<int, int>> q;
  q.emplace(start, 0);
  while (!q.empty()) {
    int node, dist;
    std::tie(node, dist) = q.front();
    q.pop();

    for (int adj_node : adj[node]) {
      if (visits[adj_node] == 1) {
        fn(adj_node, dist + 1);
      } else if (visits[adj_node] == 0) {
        q.emplace(adj_node, dist + 1);
      }
      visits[adj_node]++;
    }
  }
}

std::vector<int> dist(int start, std::vector<std::vector<int>> const &a) {
  std::vector<int> out(nodes, 1 << 30);
  out[start] = 0;

  std::queue<std::pair<int, int>> q;
  q.emplace(start, 0);

  while (!q.empty()) {
    int node, dist;
    std::tie(node, dist) = q.front();
    q.pop();

    for (int adj_node : a[node]) {
      if (out[adj_node] == 1 << 30) {
        out[adj_node] = dist + 1;
        q.emplace(adj_node, dist + 1);
      }
    }
  }
  return out;
}

std::vector<int> path(int start, std::vector<int> const &dist) {
  std::vector<int> out;
  out.push_back(start);
  while (dist[out.back()]) {
    for (int adj_node : adj[out.back()]) {
      if (dist[adj_node] == dist[out.back()] - 1) {
        out.push_back(adj_node);
        break;
      }
    }
  }
  return out;
}

int main() {
  std::ifstream fin("veri.in");
  std::ofstream fout("veri.out");

  int c;
  fin >> c >> nodes >> edges;
  adj.resize(nodes);
  radj.resize(nodes);
  int start, a, b;
  fin >> start >> a >> b;
  start--, a--, b--;
  for (int i = 0; i < edges; i++) {
    int x, y;
    fin >> x >> y;
    x--, y--;
    adj[x].push_back(y);
    radj[y].push_back(x);
  }

  std::vector<int> a_dist = dist(a, radj);
  std::vector<int> b_dist = dist(b, radj);
  int min_dist = 1 << 30;
  int cycle_point;
  cycles(start, [&](int node, int dist) {
    int d = std::max(a_dist[node], b_dist[node]) + dist;
    if (d < min_dist) {
      cycle_point = node;
      min_dist = d;
    }
  });

  if (c == 1)
    fout << min_dist << std::endl;
  else {
    auto a_path = path(cycle_point, a_dist);
    auto b_path = path(cycle_point, b_dist);
    auto cycle_dist = dist(cycle_point, radj);
    auto cycle_dist_from = dist(cycle_point, adj);
    auto cycle_path = path(start, cycle_dist);
    int point = -1, dist_to_point = 1 << 30;
    for (int n = 0; n < nodes; n++) {
      int d = cycle_dist[n] + cycle_dist_from[n];
      if (n == cycle_point)
        continue;
      if (d < dist_to_point)
        dist_to_point = d, point = n;
    }
    auto point_dist = dist(point, radj);
    auto point_path = path(cycle_point, point_dist);
    std::copy(point_path.begin() + 1, point_path.end(),
              std::back_inserter(cycle_path));
    auto path_back_from_point = path(point, cycle_dist);
    std::copy(path_back_from_point.begin() + 1, path_back_from_point.end(),
              std::back_inserter(cycle_path));

    for (const auto &vec :
         std::vector<std::vector<int>>{cycle_path, a_path, b_path}) {
      fout << vec.size() - 1 << '\n';
      for (int x : vec)
        fout << x + 1 << ' ';
      fout << '\n';
    }
  }
}
