#include <algorithm>
#include <cassert>
#include <deque>

#include <algo/graphs/entities.hpp>

using namespace algo::graphs;

struct Correct {
  Edges GetBridges(const AdjacencyList& g0) {
    Edges bridges;
    int n = g0.size();
    for (int v = 0; v < n; ++v) {
      for (int u : g0[v]) {
        if (v > u) {
          continue;
        }
        auto g = g0;
        {
          auto it = std::find(g[v].begin(), g[v].end(), u);
          assert(it != g[v].end());
          g[v].erase(it);
        }
        {
          auto it = std::find(g[u].begin(), g[u].end(), v);
          assert(it != g[u].end());
          g[u].erase(it);
        }
        if (!IsReachable(g, v, u)) {
          bridges.emplace_back(v, u);
        }
      }
    }
    return bridges;
  };

  bool IsReachable(const AdjacencyList& g, int from, int to) {
    int n = g.size();
    std::vector<bool> visited(n, false);
    visited[from] = true;
    std::deque<int> q = {from};
    while (!q.empty()) {
      int v = q.front();
      q.pop_front();

      if (v == to) {
        return true;
      }

      for (int u : g[v]) {
        if (!visited[u]) {
          visited[u] = true;
          q.push_back(u);
        }
      }
    }
    return false;
  };
};
