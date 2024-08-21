#include <iostream>
#include <algo/graphs/bipartite/matching.hpp>
#include "algo/graphs/entities.hpp"

int main() {
  std::ios::sync_with_stdio(false);
  std::cin.tie(nullptr);

  int l, r, m;
  std::cin >> l >> r >> m;

  auto g = algo::graphs::BipartiteGraph(l, r);
  for (int edge = 0; edge < m; ++edge) {
    int u, v;
    std::cin >> u >> v;
    g[u].push_back(v);
  }

  auto matching = algo::graphs::bipartite::Matching(g);
  std::cout << matching.size() << std::endl;
  for (auto [v, u] : matching) {
    std::cout << v << " " << u << std::endl;
  }
}
