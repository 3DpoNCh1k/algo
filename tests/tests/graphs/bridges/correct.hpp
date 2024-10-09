#pragma once

#include <algorithm>
#include <cassert>
#include <deque>

#include <algo/graphs/entity/graph.hpp>
#include "algo/graphs/entity/edge.hpp"

using namespace algo::graphs;

struct Correct {
  auto GetBridges(const UndirectedGraph& g0) {
    std::vector<UndirectedEdge> bridges;
    int n = g0.n;
    for (int v = 0; v < n; ++v) {
      for (int e : g0.edge_list[v]) {
        int u = g0.edges[e].Neighbor(v);
        if (v > u) {
          continue;
        }
        auto g = g0;
        {
          auto it = std::find(g.edge_list[v].begin(), g.edge_list[v].end(), e);
          assert(it != g.edge_list[v].end());
          g.edge_list[v].erase(it);
        }
        {
          auto it = std::find(g.edge_list[u].begin(), g.edge_list[u].end(), e);
          assert(it != g.edge_list[u].end());
          g.edge_list[u].erase(it);
        }
        if (!IsReachable(g, v, u)) {
          bridges.emplace_back(v, u);
        }
      }
    }
    return bridges;
  };

  bool IsReachable(const UndirectedGraph& g, int from, int to) {
    std::vector<bool> visited(g.n, false);
    visited[from] = true;
    std::deque<int> q = {from};
    while (!q.empty()) {
      int v = q.front();
      q.pop_front();

      if (v == to) {
        return true;
      }

      for (int e : g.edge_list[v]) {
        int u = g.edges[e].Neighbor(v);
        if (!visited[u]) {
          visited[u] = true;
          q.push_back(u);
        }
      }
    }
    return false;
  };
};
