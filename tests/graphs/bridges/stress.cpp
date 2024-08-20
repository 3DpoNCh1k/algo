#include <algorithm>
#include <deque>

#include <algo/graphs/entities.hpp>
#include <algo/graphs/bridges.hpp>
#include "algo/utils/generators/random.hpp"
#include "tests/testing/asserts.hpp"

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
      auto result = FindBridges(g);
      auto expected = GetBridges(g);
      ASSERT_EQ(result.size(), expected.size());
      for (auto edge : expected) {
        ASSERT_CONTAINS(result, edge);
      }
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

int main() {
  Tester(10, 10).Test(1000);
  Tester(25, 500).Test(100);
}
