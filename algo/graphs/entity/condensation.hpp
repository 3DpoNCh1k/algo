#pragma once

#include <algo/graphs/entity/graph.hpp>

namespace algo::graphs {

template <typename... Properties>
struct Condensation {
  using Graph = DirectedGraphWith<Properties...>;
  using Component = std::vector<int>;

  Graph graph;
  std::vector<Component> components;
};

}  // namespace algo::graphs
