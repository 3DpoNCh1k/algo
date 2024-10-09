#pragma once

#include <algo/graphs/entity/edge.hpp>
#include <algo/trees/entity/tree.hpp>

namespace algo::trees {

std::vector<graphs::UndirectedEdge> ToEdges(const Tree& tree) {
  std::vector<graphs::UndirectedEdge> edges;
  for (int v = 0; v < tree.n; ++v) {
    for (int u : tree.adjacency_list[v]) {
      if (v <= u) {
        edges.emplace_back(v, u);
      }
    }
  }
  return edges;
};

}  // namespace algo::trees
