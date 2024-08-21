#include <algo/graphs/entities.hpp>
#include <algo/graphs/bipartite/details/kuhn.hpp>

namespace algo::graphs::bipartite {
DirectedEdges Matching(const BipartiteGraph& g) {
  return details::Kuhn(g).Match();
};
}  // namespace algo::graphs::bipartite
