#pragma once

#include <algo/graphs/entities.hpp>
#include <algo/graphs/bipartite/details/hungarian.hpp>
#include <vector>

namespace algo::graphs::bipartite {
std::vector<DirectedEdgeWithCost> Assignment(const BipartiteGraphWithCost& g) {
  return details::Hungarian(g).Assign();
};
}  // namespace algo::graphs::bipartite
