#pragma once

#include <string>
#include <vector>
#include "algo/utils/join.hpp"
#include <algo/graphs/entity/cost.hpp>
#include <algo/graphs/entity/orientation.hpp>

namespace algo::graphs {

template <typename... Properties>
struct Edge : Properties... {
  explicit Edge(Properties... props)
      : Properties(props)... {
  }

  bool operator==(const Edge& that) {
    return (Properties::operator==(that) && ...);
  }

  std::string ToString() const {
    std::vector<std::string> property_strings;
    ((property_strings.push_back(Properties::ToString())), ...);
    return algo::utils::JoinToString(property_strings, {.separator = " "});
  };
};

template <typename... Properties>
struct UndirectedEdgeWith : Edge<orientation::Undirected, Properties...> {
  UndirectedEdgeWith(int u, int v, Properties... props)
      : Edge<orientation::Undirected, Properties...>(
            orientation::Undirected(u, v), props...) {
  }
};

using UndirectedEdge = UndirectedEdgeWith<>;

template <typename... Properties>
struct DirectedEdgeWith : Edge<orientation::Directed, Properties...> {
  DirectedEdgeWith(int from, int to, Properties... props)
      : Edge<orientation::Directed, Properties...>(
            orientation::Directed(from, to), props...) {
  }
};

using DirectedEdge = DirectedEdgeWith<>;

}  // namespace algo::graphs
