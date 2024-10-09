#pragma once

#include <algo/graphs/entities.hpp>
#include "algo/utils/random/random.hpp"

namespace algo::graphs::bipartite::details {
struct Kuhn {
  BipartiteGraph g;
  explicit Kuhn(const BipartiteGraph& g0) {
    if (g0.n_left_side > g0.n_right_side) {
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

  BipartiteGraph SwapSides(const BipartiteGraph& g0) {
    BipartiteGraph g(g0.n_right_side, g0.n_left_side);
    for (int v = 0; v < g0.n_left_side; ++v) {
      for (int u : g0[v]) {
        g[u].push_back(v);
      }
    }
    return g;
  }

  DirectedEdges Match() {
    matching.resize(g.n_right_side, -1);
    visited.assign(g.n_right_side, false);
    taken.resize(g.n_left_side, false);
    for (int v = 0; v < g.n_left_side; ++v) {
      utils::random::Shuffle(g[v]);
    }

    while (true) {
      visited.assign(g.n_right_side, false);
      bool repeat = false;
      for (int v = 0; v < g.n_left_side; ++v) {
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

    DirectedEdges match;
    for (int u = 0; u < g.n_right_side; ++u) {
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
    for (int u : g[v]) {
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
