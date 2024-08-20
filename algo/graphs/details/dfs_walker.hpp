#pragma once

#include <vector>

#include <algo/graphs/entities.hpp>
#include "algo/utils/debug.hpp"

namespace algo::graphs::details {

struct DfsWalker {
  explicit DfsWalker(const AdjacencyList& graph) {
    auto [edges0, g0] = ToEdgeAdjacencyList(graph);
    edges = std::move(edges0);
    g = std::move(g0);
    n = g.size();
    counter = 0;
    index.assign(n, -1);
    min_index.assign(n, n);
    is_bridge.assign(edges.size(), false);
    is_articulation_point.assign(n, false);
  }

  int n;
  EdgeAdjacencyList g;
  Edges edges;

  int counter;
  std::vector<int> index;
  std::vector<int> min_index;
  std::vector<bool> is_bridge;
  std::vector<bool> is_articulation_point;

  Edges GetBridges() {
    Walk();
    Edges bridges;
    for (int e = 0; e < edges.size(); ++e) {
      if (is_bridge[e]) {
        bridges.push_back(edges[e]);
      }
    }
    return bridges;
  }

  std::vector<int> GetArticulationPoints() {
    Walk();
    std::vector<int> articulation_points;
    for (int v = 0; v < n; ++v) {
      if (is_articulation_point[v]) {
        articulation_points.push_back(v);
      }
    }
    // dbg(articulation_points);
    return articulation_points;
  }

  void Walk() {
    for (int v = 0; v < n; ++v) {
      if (index[v] == -1) {
        DFS(v, -1);
      }
    }
  }

  void DFS(int v, int parent_edge) {
    index[v] = counter++;
    min_index[v] = index[v];
    int k_child = 0;
    for (int e : g[v]) {
      if (e != parent_edge) {
        int u = edges[e].Neighbor(v);
        if (index[u] == -1) {
          k_child++;
          // dbg("go", v, u);
          DFS(u, e);
          if (min_index[u] >= index[u]) {
            is_bridge[e] = true;
          }
          if (parent_edge == -1) {
            if (k_child > 1) {
              is_articulation_point[v] = true;
            }
          } else {
            if (min_index[u] >= index[v]) {
              is_articulation_point[v] = true;
            }
          }
          min_index[v] = std::min(min_index[v], min_index[u]);
        } else {
          min_index[v] = std::min(min_index[v], index[u]);
        }
      }
    }
  };
};

}  // namespace algo::graphs::details
