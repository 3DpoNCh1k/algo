#pragma once

#include <vector>

#include <algo/graphs/entity/graph.hpp>

namespace algo::graphs::details {

template <typename... EdgeProperties>
struct DfsWalker {
  using Graph = UndirectedGraphWith<EdgeProperties...>;
  explicit DfsWalker(const Graph& graph)
      : g(graph) {
    counter = 0;
    index.assign(g.n, -1);
    min_index.assign(g.n, g.n);
    is_bridge.assign(g.edges.size(), false);
    is_articulation_point.assign(g.n, false);
  }

  const Graph& g;

  int counter;
  std::vector<int> index;
  std::vector<int> min_index;
  std::vector<bool> is_bridge;
  std::vector<bool> is_articulation_point;

  std::vector<typename Graph::EdgeType> GetBridges() {
    Walk();
    std::vector<typename Graph::EdgeType> bridges;
    for (int e = 0; e < g.edges.size(); ++e) {
      if (is_bridge[e]) {
        bridges.push_back(g.edges[e]);
      }
    }
    return bridges;
  }

  std::vector<int> GetArticulationPoints() {
    Walk();
    std::vector<int> articulation_points;
    for (int v = 0; v < g.n; ++v) {
      if (is_articulation_point[v]) {
        articulation_points.push_back(v);
      }
    }
    return articulation_points;
  }

  void Walk() {
    for (int v = 0; v < g.n; ++v) {
      if (index[v] == -1) {
        DFS(v, -1);
      }
    }
  }

  void DFS(int v, int parent_edge) {
    index[v] = counter++;
    min_index[v] = index[v];
    int k_child = 0;
    for (int e : g.edge_list[v]) {
      if (e != parent_edge) {
        int u = g.edges[e].Neighbor(v);
        if (index[u] == -1) {
          k_child++;
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
