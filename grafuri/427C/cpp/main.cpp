#include <algorithm>
#include <coroutine>
#include <iostream>
#include <iterator>
#include <memory>
#include <optional>
#include <ranges>
#include <vector>

namespace rg = std::ranges;

std::generator<int> dfs(std::vector<std::vector<int>> const &adj, int k,
                        std::shared_ptr<std::vector<bool>> visited = nullptr) {
  if (!visited)
    visited = std::make_shared<std::vector<bool>>(adj.size(), false);

  if (visited->at(k))
    co_return;

  for (int n : adj[k])
    for (int node : dfs(adj, n, visited))
      co_yield node;
  co_yield k;
}

std::vector<std::vector<int>>
reverse_adj(std::vector<std::vector<int>> const &adj) {
  std::vector<std::vector<int>> out;
  for (int i = 0; i < adj.size(); i++)
    for (int j : adj[i])
      out[j].push_back(i);
  return out;
}

std::generator<std::generator<int>>
strongly_connected_components(std::vector<std::vector<int>> const &adj) {
  const int nodes = adj.size();
  auto visited = std::make_shared<std::vector<bool>>(adj.size(), false);
  std::vector<int> topological_order;
  for (int node = 0; node < nodes; node++) {
    if (visited->at(node))
      continue;
    rg::copy(dfs(adj, node, visited), std::back_inserter(topological_order));
  }
  rg::reverse(topological_order);

  visited->clear();
  visited->resize(nodes, false);
  auto radj = reverse_adj(adj);
  for (int node : topological_order) {
    if (visited->at(node))
      continue;
    co_yield dfs(radj, node, visited);
  }
}

int main() {
  using std::cin, std::cout, std::endl;
  using std::vector;
  int junctions;
  cin >> junctions;
  vector<int> prices(junctions);
  rg::copy_n(std::istream_iterator<int>(cin), junctions, prices.begin());

  vector<vector<int>> adj(junctions);
  int streets;
  cin >> streets;
  for (int i = 0; i < streets; i++) {
    int a, b;
    cin >> a >> b;
    adj[a].push_back(b);
    adj[b].push_back(a);
  }

  auto components = strongly_connected_components(adj);
  auto prices_with_components =
      components | rg::views::transform([&](auto component) {
        return component |
               rg::views::transform([&](int node) { return prices[node]; });
      });
}
