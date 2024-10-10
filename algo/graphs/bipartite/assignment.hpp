#pragma once

#include <algo/graphs/entity/bipartite.hpp>
#include <algo/graphs/bipartite/details/hungarian.hpp>

namespace algo::graphs::bipartite {
template <typename C, typename... EdgeProperties>
auto Assignment(const BipartiteGraphWith<Cost<C>, EdgeProperties...>& g) {
  return details::Hungarian(g).Assign();
};
}  // namespace algo::graphs::bipartite
