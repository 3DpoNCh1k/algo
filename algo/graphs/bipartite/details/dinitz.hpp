#pragma once

#include <deque>

#include <algo/graphs/entities.hpp>

namespace algo::graphs::bipartite::details {
struct Dinitz {
  const BipartiteGraph& g;
  explicit Dinitz(const BipartiteGraph& g)
      : g(g) {
  }

  std::vector<int> matching;
  std::vector<bool> taken;
  std::vector<int> distance;
  std::vector<int> next;

  DirectedEdges Match() {
    matching.resize(g.n_right_side, -1);
    taken.resize(g.n_left_side);

    while (FindAugmentingPaths()) {
    }

    DirectedEdges match;
    for (int u = 0; u < g.n_right_side; ++u) {
      if (matching[u] != -1) {
        match.emplace_back(matching[u], u);
      }
    }
    return match;
  }

  bool FindAugmentingPaths() {
    bool has_paths = BuildLayers();
    if (!has_paths) {
      return false;
    }
    next.assign(g.n_left_side, 0);
    for (int v = 0; v < g.n_left_side; ++v) {
      if (taken[v]) {
        continue;
      }
      taken[v] = FindAugmentingPath(v);
    }
    return true;
  }

  bool FindAugmentingPath(int v) {
    while (next[v] < g[v].size()) {
      int u = g[v][next[v]++];
      int w = matching[u];

      if (w == -1) {
        matching[u] = v;
        return true;
      }
      if (distance[w] == distance[v] + 2) {
        if (FindAugmentingPath(w)) {
          matching[u] = v;
          return true;
        }
      }
    }
    return false;
  };

  bool BuildLayers() {
    const int infinity = 1e9;
    distance.assign(g.n_left_side, infinity);
    std::deque<int> q;
    for (int v = 0; v < g.n_left_side; ++v) {
      if (!taken[v]) {
        q.push_back(v);
        distance[v] = 0;
      }
    }

    bool found = false;
    while (!q.empty()) {
      auto v = q.front();
      q.pop_front();
      for (int u : g[v]) {
        int w = matching[u];
        if (w == -1) {
          found = true;
          continue;
        }
        if (distance[w] == infinity) {
          distance[w] = distance[v] + 2;
          q.push_back(w);
        }
      }
    }

    return found;
  }
};
}  // namespace algo::graphs::bipartite::details
