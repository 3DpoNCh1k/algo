#include <algorithm>
#include <set>

#include <algo/graphs/entities.hpp>
#include <algo/graphs/bipartite/assignment.hpp>
#include "algo/utils/generators/random.hpp"
#include "algo/utils/types/fundamentals.hpp"
#include "tests/testing/asserts.hpp"

using namespace algo::graphs;
using namespace algo::graphs::bipartite;

struct Tester {
  bool full;
  int min_n, max_n;
  i64 min_c, max_c;
  algo::utils::generators::RandomGenerator random;
  Tester(int min_n, int max_n, i64 min_c, i64 max_c, bool full)
      : min_n(min_n),
        max_n(max_n),
        min_c(min_c),
        max_c(max_c),
        full(full),
        random(min_n ^ max_n){};

  void Test(int k_rep) {
    for (int rep = 0; rep < k_rep; ++rep) {
      auto g = GenerateGraph();
      auto assignment = Assignment(g);
      Validate(assignment, g);
    }
  }

  BipartiteGraphWithCost GenerateGraph() {
    int n = random.GetInt(min_n, max_n);
    int m = random.GetInt(min_n, max_n);
    auto g = BipartiteGraphWithCost(n, m);
    if (full) {
      for (int v = 0; v < n; ++v) {
        for (int u = 0; u < m; ++u) {
          g.AddEdge(v, u, random.GetInt(min_c, max_c));
        }
      }
    } else {
      int e = random.GetInt(0, n * m);
      for (int i = 0; i < e; ++i) {
        int v = random.GetInt(0, n - 1);
        int u = random.GetInt(0, m - 1);
        i64 c = random.GetInt(min_c, max_c);
        g.AddEdge(v, u, c);
      }
    }
    return g;
  };

  i64 GetAssignmentCost(const BipartiteGraphWithCost& g) {
    int n = std::max(g.n_left_side, g.n_right_side);
    std::pair<int, i64> min_cost = {n, 0};
    std::vector<int> permutation(n);
    for (int i = 0; i < n; ++i) {
      permutation[i] = i;
    }
    do {
      std::pair<int, i64> cur_cost = {0, 0};
      for (int v = 0; v < g.n_left_side; ++v) {
        int u = permutation[v];
        if (u >= g.n_right_side) {
          cur_cost.first++;
        } else {
          std::pair<int, i64> edge_cost = {1, 0};
          for (int e : g[v]) {
            if (g.edges[e].to == u) {
              edge_cost = min(edge_cost, {0, g.edges[e].cost});
            }
          }
          cur_cost.first += edge_cost.first;
          cur_cost.second += edge_cost.second;
        }
      }
      min_cost = min(min_cost, cur_cost);
    } while (std::next_permutation(permutation.begin(), permutation.end()));
    return min_cost.second;
  };

  void Validate(const std::vector<DirectedEdgeWithCost>& assignment,
                const BipartiteGraphWithCost& g) {
    auto min_cost = GetAssignmentCost(g);
    i64 cost = 0;
    std::set<int> left;
    std::set<int> right;
    for (auto e : assignment) {
      ASSERT_TRUE(left.find(e.from) == left.end());
      ASSERT_TRUE(right.find(e.to) == right.end());
      ASSERT_CONTAINS(g.edges, e);
      left.insert(e.from);
      right.insert(e.to);
      cost += e.cost;
    }
    dbg(cost);
    ASSERT_EQ(cost, min_cost);
  };
};

void Test() {
  Tester(1, 5, -10, 10, true).Test(1000);
  Tester(1, 5, -10, 10, false).Test(1000);
  Tester(6, 8, -1e9, 1e9, true).Test(50);
  Tester(6, 8, -1e9, 1e9, false).Test(50);
}

int main() {
  Test();
}
