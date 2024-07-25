#include <iostream>
#include <vector>

#include <algo/trees/decompositions/heavy_light.hpp>
#include <algo/trees/segment_tree/operations/add.hpp>
#include <algo/trees/segment_tree/statistics/sum.hpp>
#include "algo/trees/segment_tree/trees.hpp"

using namespace algo::trees::segment_tree;

int main() {
  std::ios::sync_with_stdio(false);
  std::cin.tie(nullptr);

  int n;
  std::cin >> n;
  std::vector<std::vector<int>> g(n);
  for (int e = 0; e < n - 1; ++e) {
    int u, v;
    std::cin >> u >> v;
    --u;
    --v;
    g[u].push_back(v);
    g[v].push_back(u);
  }

  auto hld = algo::trees::decompositions::HeavyLightDecomposition<
      Operation<operations::AddOp>, Statistics<statistics::Sum>>(g);

  int m;
  std::cin >> m;
  for (int q = 0; q < m; ++q) {
    std::string command;
    std::cin >> command;
    if (command == "+") {
      int v, u, d;
      std::cin >> v >> u >> d;
      --v;
      --u;
      hld.ApplyOnPath(u, v, operations::AddOp{d});
    } else if (command == "?") {
      int v;
      std::cin >> v;
      --v;
      std::cout << hld.GetFromVertex<statistics::Sum>(v).result << "\n";
    } else {
      std::abort();
    }
  }
}
