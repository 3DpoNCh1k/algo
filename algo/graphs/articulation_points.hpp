#pragma once

#include <algo/graphs/details/dfs_walker.hpp>
#include <algo/graphs/entity/graph.hpp>

namespace algo::graphs {

template <typename... EdgeProperties>
auto FindArticulationPoints(const UndirectedGraphWith<EdgeProperties...>& g) {
  return details::DfsWalker(g).GetArticulationPoints();
}
}  // namespace algo::graphs
