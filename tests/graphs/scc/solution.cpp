#include <iostream>
#include <map>
#include <vector>

#include <algo/graphs/scc.hpp>
#include <algo/utils/debug.hpp>

int main() {
  int n, m;
  std::cin >> n >> m;
  std::vector<std::vector<int>> graph(n);

  for (int edge = 0; edge < m; ++edge) {
    int u, v;
    std::cin >> u >> v;
    graph[u].push_back(v);
  }

  auto scc = algo::graphs::SCC(graph);
  std::vector<int> component;
  std::set<std::pair<int, int>> edges;
  scc.Solve(component, edges);

  // dbg(component);

  std::map<int, std::vector<int>> component_map;
  for (int u = 0; u < n; ++u) {
    component_map[component[u]].push_back(u);
  }

  std::cout << component_map.size() << std::endl;
  for (auto [key, component] : component_map) {
    std::cout << component.size();
    for (auto u : component) {
      std::cout << " " << u;
    }
    std::cout << std::endl;
  }
}
