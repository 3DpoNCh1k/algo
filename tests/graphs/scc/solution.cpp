#include <algorithm>
#include <deque>
#include <iostream>
#include <vector>

#include <algo/graphs/scc.hpp>
#include <algo/graphs/degrees.hpp>
#include "algo/utils/join.hpp"

using namespace algo::graphs;

int main() {
  std::ios::sync_with_stdio(false);
  std::cin.tie(nullptr);

  int n, m;
  std::cin >> n >> m;
  std::vector<std::vector<int>> graph(n);

  for (int edge = 0; edge < m; ++edge) {
    int u, v;
    std::cin >> u >> v;
    graph[u].push_back(v);
  }

  auto condensation = StronglyConnectedComponents(graph);
  auto& condensation_graph = condensation.first;
  auto& components = condensation.second;
  int k_component = components.size();

  // Determinated order of output

  auto in_degree = algo::graph::InDegrees(condensation_graph);
  for (auto& component : components) {
    std::sort(component.begin(), component.end());
  }
  std::deque<int> q;
  for (int c = 0; c < k_component; ++c) {
    if (in_degree[c] == 0) {
      q.push_back(c);
    }
  }

  std::cout << k_component << std::endl;
  while (!q.empty()) {
    std::sort(q.begin(), q.end(), [&components](int c0, int c1) {
      return components[c0][0] < components[c1][0];
    });
    for (int c : q) {
      auto& component = components[c];
      std::cout << component.size() << " "
                << algo::utils::JoinToString(component, {.separator = " "})
                << "\n";
    }

    std::deque<int> next;
    for (int c : q) {
      for (int nc : condensation_graph[c]) {
        in_degree[nc]--;
        if (in_degree[nc] == 0) {
          next.push_back(nc);
        }
      }
    }

    q = next;
  }
}
