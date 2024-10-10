#pragma once

#include <vector>
#include <algo/graphs/entity/graph.hpp>

namespace algo::graphs {

template <typename... EdgeProperties>
std::vector<int> InDegrees(const DirectedGraphWith<EdgeProperties...>& g) {
  std::vector<int> in_degree(g.n);
  for (int v = 0; v < g.n; ++v) {
    for (int e : g.edge_list[v]) {
      auto edge = g.edges[e];
      in_degree[edge.to]++;
    }
  }
  return in_degree;
}

template <typename... EdgeProperties>
std::vector<int> InDegrees(const UndirectedGraphWith<EdgeProperties...>& g) {
  return OutDegrees(g);
}

template <typename Graph>
std::vector<int> OutDegrees(const Graph& g) {
  std::vector<int> out_degree(g.n);
  for (int v = 0; v < g.n; ++v) {
    out_degree[v] = g.edge_list[v].size();
  }
  return out_degree;
}
}  // namespace algo::graphs
