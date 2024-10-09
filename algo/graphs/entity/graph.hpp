#pragma once

#include <vector>
#include "algo/graphs/entity/edge.hpp"
#include <algo/graphs/entity/cost.hpp>
#include <algo/graphs/entity/orientation.hpp>

namespace algo::graphs {
template <typename Edge>
struct Graph {
  int n;
  std::vector<Edge> edges;
  std::vector<std::vector<int>> edge_list;

  explicit Graph(int n)
      : n(n) {
    edge_list.resize(n);
  }
};

template <typename... Properties>
struct UndirectedGraphWith : Graph<UndirectedEdgeWith<Properties...>> {
  using EdgeType = UndirectedEdgeWith<Properties...>;
  explicit UndirectedGraphWith(int n)
      : Graph<EdgeType>(n){};
  void AddEdge(const EdgeType&& e) {
    this->edge_list[e.v].push_back(this->edges.size());
    this->edge_list[e.u].push_back(this->edges.size());
    this->edges.push_back(e);
  }
};

using UndirectedGraph = UndirectedGraphWith<>;

}  // namespace algo::graphs
