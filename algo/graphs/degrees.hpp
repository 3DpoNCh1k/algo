#pragma once

#include <vector>

namespace algo::graph {
using Graph = std::vector<std::vector<int>>;
std::vector<int> InDegrees(const Graph& g) {
  int n = g.size();
  std::vector<int> in_degree(n);
  for (int v = 0; v < n; ++v) {
    for (int u : g[v]) {
      in_degree[u]++;
    }
  }
  return in_degree;
}

std::vector<int> OutDegrees(const Graph& g) {
  int n = g.size();
  std::vector<int> out_degree(n);
  for (int v = 0; v < n; ++v) {
    for (int u : g[v]) {
      out_degree[v]++;
    }
  }
  return out_degree;
}
}  // namespace algo::graph
