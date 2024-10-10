#pragma once

#include <deque>

#include <algo/graphs/entity/bipartite.hpp>

namespace algo::graphs::bipartite::details {
template <typename... EdgeProperties>
struct Dinitz {
  using Graph = BipartiteGraphWith<EdgeProperties...>;
  const Graph& g;
  explicit Dinitz(const Graph& g)
      : g(g) {
  }

  std::vector<int> matching;
  std::vector<bool> taken;
  std::vector<int> distance;
  std::vector<int> next;

  std::vector<typename Graph::EdgeType> Match() {
    matching.resize(g.n_right, -1);
    taken.resize(g.n);

    while (FindAugmentingPaths()) {
    }

    std::vector<typename Graph::EdgeType> match;
    for (int u = 0; u < g.n_right; ++u) {
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
    next.assign(g.n, 0);
    for (int v = 0; v < g.n; ++v) {
      if (taken[v]) {
        continue;
      }
      taken[v] = FindAugmentingPath(v);
    }
    return true;
  }

  bool FindAugmentingPath(int v) {
    while (next[v] < g.edge_list[v].size()) {
      int e = g.edge_list[v][next[v]++];
      int u = g.edges[e].to;
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
    distance.assign(g.n, infinity);
    std::deque<int> q;
    for (int v = 0; v < g.n; ++v) {
      if (!taken[v]) {
        q.push_back(v);
        distance[v] = 0;
      }
    }

    bool found = false;
    while (!q.empty()) {
      auto v = q.front();
      q.pop_front();
      for (int e : g.edge_list[v]) {
        int u = g.edges[e].to;
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
