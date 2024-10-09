#pragma once

#include <algo/utils/random/random.hpp>
#include <algo/graphs/entity/graph.hpp>
#include "algo/graphs/entity/edge.hpp"

namespace algo::utils::generators {

using namespace graphs;
using namespace random;

struct GraphGenerator {
  GraphGenerator() {
  }

  graphs::UndirectedGraph UndirectedGraph(int n, int m) {
    auto g = graphs::UndirectedGraph(n);
    if (n == 0) {
      return g;
    }
    for (int i = 0; i < m; ++i) {
      int u = RandomInt(0, n - 1);
      int v = RandomInt(0, n - 1);
      g.AddEdge(UndirectedEdge(u, v));
    }
    return g;
  }
};
}  // namespace algo::utils::generators
