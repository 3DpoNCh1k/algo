#include <algo/graphs/entities.hpp>
#include <algo/graphs/bipartite/details/kuhn.hpp>
#include <algo/graphs/bipartite/details/dinitz.hpp>

namespace algo::graphs::bipartite {
DirectedEdges Matching(const BipartiteGraph& g, bool use_kuhn = false) {
  if (use_kuhn) {
    return details::Kuhn(g).Match();
  }
  return details::Dinitz(g).Match();
};
}  // namespace algo::graphs::bipartite
