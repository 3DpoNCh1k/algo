#pragma once

#include <algo/graphs/details/dfs_walker.hpp>
#include "algo/graphs/entities.hpp"

namespace algo::graphs {
std::vector<int> FindArticulationPoints(const AdjacencyList& g) {
  return details::DfsWalker(g).GetArticulationPoints();
}
}  // namespace algo::graphs
