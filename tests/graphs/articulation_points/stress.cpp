#include <algorithm>
#include <deque>

#include <algo/graphs/entities.hpp>
#include <algo/graphs/articulation_points.hpp>
#include "algo/utils/generators/random.hpp"
#include "tests/framework/asserts.hpp"

using namespace algo::graphs;

struct Tester {
  int max_n, max_m;
  algo::utils::generators::RandomGenerator random;
  Tester(int n, int m)
      : max_n(n),
        max_m(m),
        random(n ^ m){};

  void Test(int k_rep) {
    for (int rep = 0; rep < k_rep; ++rep) {
      auto g = GenerateGraph();
      auto result = FindArticulationPoints(g);
      auto expected = GetArticulationPoints(g);
      sort(result.begin(), result.end());
      sort(expected.begin(), expected.end());
      ASSERT_EQ(result, expected);
    }
  }

  AdjacencyList GenerateGraph() {
    int n = random.GetInt(0, max_n);
    int m = random.GetInt(0, max_m);
    AdjacencyList g(n);
    for (int i = 0; n > 0 && i < m; ++i) {
      int u = random.GetInt(0, n - 1);
      int v = random.GetInt(0, n - 1);
      g[u].push_back(v);
      g[v].push_back(u);
    }
    return g;
  };

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

int main() {
  Tester(10, 10).Test(1000);
  Tester(25, 5'000).Test(1000);
}
