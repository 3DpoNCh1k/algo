#pragma once

#include <deque>

#include <algo/graphs/entity/graph.hpp>
#include <algo/graphs/articulation_points.hpp>

using namespace algo::graphs;

struct Correct {
  std::vector<int> GetArticulationPoints(const UndirectedGraph& g) {
    std::vector<int> articulation_points;
    int k = FindNumberOfConnectedComponents(g);
    for (int v = 0; v < g.n; ++v) {
      if (FindNumberOfConnectedComponents(g, v) > k) {
        articulation_points.push_back(v);
      }
    }
    return articulation_points;
  };

  int FindNumberOfConnectedComponents(const UndirectedGraph& g,
                                      int forbidden = -1) {
    int k = 0;
    std::vector<bool> visited(g.n, false);
    for (int v = 0; v < g.n; ++v) {
      if (!visited[v] && v != forbidden) {
        k++;
        visited[v] = true;
        std::deque<int> q{v};
        while (!q.empty()) {
          auto v = q.front();
          q.pop_front();
          for (int e : g.edge_list[v]) {
            int u = g.edges[e].Neighbor(v);
            if (!visited[u] && u != forbidden) {
              visited[u] = true;
              q.push_back(u);
            }
          }
        }
      }
    }
    return k;
  };
};
