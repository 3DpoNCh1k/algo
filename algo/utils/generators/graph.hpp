#pragma once

#include <algo/utils/random/random.hpp>
#include <algo/graphs/entity/graph.hpp>
#include <algo/graphs/entity/bipartite.hpp>
#include <algo/graphs/entity/edge.hpp>
#include <algo/flows/entity/residual_network.hpp>

namespace algo::utils::generators {

using random::RandomInt;

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
      g.AddEdge(graphs::UndirectedEdge(u, v));
    }
    return g;
  }

  graphs::BipartiteGraph BipartiteGraph(int n, int m, int e) {
    auto g = graphs::BipartiteGraph(n, m);
    if (n == 0 || m == 0) {
      return g;
    }
    for (int i = 0; i < e; ++i) {
      int v = RandomInt(0, n - 1);
      int u = RandomInt(0, m - 1);
      g.AddEdge(graphs::DirectedEdge(v, u));
    }
    return g;
  };

  template <typename C>
  graphs::BipartiteGraphWith<graphs::Cost<C>> BipartiteGraphWithCost(
      int n, int m, bool full, C min_c, C max_c) {
    auto g = graphs::BipartiteGraphWith<graphs::Cost<C>>(n, m);
    if (full) {
      for (int v = 0; v < n; ++v) {
        for (int u = 0; u < m; ++u) {
          C c = RandomInt(min_c, max_c);
          g.AddEdge(graphs::DirectedEdgeWith(v, u, graphs::Cost(c)));
        }
      }
    } else {
      int e = RandomInt(0, n * m);
      for (int i = 0; i < e; ++i) {
        int v = RandomInt(0, n - 1);
        int u = RandomInt(0, m - 1);
        C c = RandomInt(min_c, max_c);
        g.AddEdge(graphs::DirectedEdgeWith(v, u, graphs::Cost(c)));
      }
    }
    return g;
  };

  flows::ResidualNetwork ResidualNetwork(int n, int source, int sink, int e,
                                         i64 max_capacity) {
    flows::ResidualNetwork network(n, source, sink);
    for (int i = 0; i < e; ++i) {
      int from;
      do {
        from = RandomInt(0, n - 1);
      } while (from == sink);
      int to;
      do {
        to = RandomInt(0, n - 1);
      } while (to == source);
      int capacity = RandomInt(0, max_capacity);
      network.AddEdge(from, to, capacity);
    }
    return network;
  };
};
}  // namespace algo::utils::generators
