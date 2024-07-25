#include <iostream>
#include <vector>

#include <algo/trees/decompositions/centroid.hpp>
#include <algo/trees/segment_tree/operations/add.hpp>
#include <algo/trees/segment_tree/statistics/sum.hpp>
#include "algo/trees/segment_tree/operations/set.hpp"
#include "algo/trees/segment_tree/statistics/minimum.hpp"
#include "algo/trees/segment_tree/trees.hpp"

using namespace algo::trees::segment_tree;

int main() {
  std::ios::sync_with_stdio(false);
  std::cin.tie(nullptr);

  int n, m;
  std::cin >> n >> m;
  std::vector<std::vector<int>> g(n);
  for (int e = 0; e < n - 1; ++e) {
    int u, v;
    std::cin >> u >> v;
    --u;
    --v;
    g[u].push_back(v);
    g[v].push_back(u);
  }

  auto centroids = algo::trees::decompositions::Centroids<
      Operation<operations::SetOp>, Statistics<statistics::Minimum>>(g);

  for (int q = 0; q < m; ++q) {
    int v, d;
    std::cin >> v >> d;
    --v;

    int u = centroids.GetMin(v, d);
    u++;

    std::cout << u << "\n";
  }
}
