#pragma once

#include <algo/graphs/entity/bipartite.hpp>
#include <algo/graphs/bipartite/details/kuhn.hpp>
#include <algo/graphs/bipartite/details/dinitz.hpp>

namespace algo::graphs::bipartite {
template <typename... EdgeProperties>
auto Matching(const BipartiteGraphWith<EdgeProperties...>& g,
              bool use_kuhn = false) {
  if (use_kuhn) {
    return details::Kuhn(g).Match();
  }
  return details::Dinitz(g).Match();
};
}  // namespace algo::graphs::bipartite
