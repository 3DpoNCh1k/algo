#pragma once

#include <algo/graphs/entity/bipartite.hpp>
#include <algo/utils/random/random.hpp>

namespace algo::graphs::bipartite::details {
template <typename... EdgeProperties>
struct Kuhn {
  using Graph = BipartiteGraphWith<EdgeProperties...>;
  Graph g;
  explicit Kuhn(const Graph& g0)
      : g(0, 0) {
    if (g0.n > g0.n_right) {
      g = SwapSides(g0);
      swapped = true;
    } else {
      g = g0;
    }
  }

  bool swapped = false;
  std::vector<bool> visited;
  std::vector<int> matching;
  std::vector<bool> taken;

  Graph SwapSides(const Graph& g0) {
    Graph g(g0.n_right, g0.n);
    for (int v = 0; v < g0.n; ++v) {
      for (int e : g0.edge_list[v]) {
        auto edge = g0.edges[e];
        std::swap(edge.to, edge.from);
        g.AddEdge(edge);
      }
    }
    return g;
  }

  std::vector<typename Graph::EdgeType> Match() {
    matching.resize(g.n_right, -1);
    visited.assign(g.n_right, false);
    taken.resize(g.n, false);
    for (int v = 0; v < g.n; ++v) {
      utils::random::Shuffle(g.edge_list[v]);
    }

    while (true) {
      visited.assign(g.n_right, false);
      bool repeat = false;
      for (int v = 0; v < g.n; ++v) {
        if (taken[v]) {
          continue;
        }
        taken[v] = FindAugmentingPath(v);
        repeat |= taken[v];
      }
      if (!repeat) {
        break;
      }
    }

    std::vector<typename Graph::EdgeType> match;
    for (int u = 0; u < g.n_right; ++u) {
      if (matching[u] != -1) {
        if (swapped) {
          match.emplace_back(u, matching[u]);
        } else {
          match.emplace_back(matching[u], u);
        }
      }
    }
    return match;
  };

  bool FindAugmentingPath(int v) {
    for (int e : g.edge_list[v]) {
      int u = g.edges[e].to;
      if (visited[u]) {
        continue;
      }
      visited[u] = true;
      if (matching[u] == -1) {
        matching[u] = v;
        return true;
      }
      if (FindAugmentingPath(matching[u])) {
        matching[u] = v;
        return true;
      }
    }
    return false;
  }
};
}  // namespace algo::graphs::bipartite::details
