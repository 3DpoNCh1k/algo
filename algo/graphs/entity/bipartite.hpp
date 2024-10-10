#pragma once

#include <algo/graphs/entity/graph.hpp>

namespace algo::graphs {

template <typename... Properties>
struct BipartiteGraphWith : DirectedGraphWith<Properties...> {
  using GraphBaseType = DirectedGraphWith<Properties...>;
  explicit BipartiteGraphWith(int n_left, int n_right)
      : GraphBaseType(n_left),
        n_right(n_right){};
  void AddEdge(const typename GraphBaseType::EdgeType& e) {
    this->edge_list[e.from].push_back(this->edges.size());
    this->edges.push_back(e);
  }

  // n == n_left
  int n_right;
};

using BipartiteGraph = BipartiteGraphWith<>;

}  // namespace algo::graphs
