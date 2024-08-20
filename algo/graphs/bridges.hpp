#pragma once

#include <algo/graphs/details/dfs_walker.hpp>
#include "algo/graphs/entities.hpp"

namespace algo::graphs {
Edges FindBridges(const AdjacencyList& g) {
  return details::DfsWalker(g).GetBridges();
}
}  // namespace algo::graphs
