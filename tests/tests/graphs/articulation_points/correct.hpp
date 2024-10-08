#include <algorithm>
#include <deque>

#include <algo/graphs/entities.hpp>
#include <algo/graphs/articulation_points.hpp>
#include "algo/utils/generators/random.hpp"
#include "tests/framework/asserts.hpp"

using namespace algo::graphs;

struct Correct {
  std::vector<int> GetArticulationPoints(const AdjacencyList& g) {
    std::vector<int> articulation_points;
    int n = g.size();
    int k = FindNumberOfConnectedComponents(g);
    for (int v = 0; v < n; ++v) {
      if (FindNumberOfConnectedComponents(g, v) > k) {
        articulation_points.push_back(v);
      }
    }
    return articulation_points;
  };

  int FindNumberOfConnectedComponents(const AdjacencyList& g,
                                      int forbidden = -1) {
    int k = 0;
    int n = g.size();
    std::vector<bool> visited(n, false);
    for (int v = 0; v < n; ++v) {
      if (!visited[v] && v != forbidden) {
        k++;
        visited[v] = true;
        std::deque<int> q{v};
        while (!q.empty()) {
          auto v = q.front();
          q.pop_front();
          for (int u : g[v]) {
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
