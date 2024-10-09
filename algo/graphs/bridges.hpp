#pragma once

#include <algo/graphs/details/dfs_walker.hpp>
#include "algo/graphs/entity/graph.hpp"

namespace algo::graphs {
template <typename... EdgeProperties>
auto FindBridges(const UndirectedGraphWith<EdgeProperties...>& g) {
  return details::DfsWalker(g).GetBridges();
}
}  // namespace algo::graphs
