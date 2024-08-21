#include <algorithm>

#include <algo/graphs/entities.hpp>
#include <algo/graphs/bipartite/matching.hpp>
#include "algo/utils/generators/random.hpp"
#include "algo/utils/bits.hpp"
#include "tests/testing/asserts.hpp"

using namespace algo::graphs;
using namespace algo::graphs::bipartite;

struct Tester {
  bool use_kuhn;
  int max_n, max_m, max_e;
  algo::utils::generators::RandomGenerator random;
  Tester(bool use_kuhn, int n, int m, int e)
      : use_kuhn(use_kuhn),
        max_n(n),
        max_m(m),
        max_e(e),
        random(n ^ m ^ e){};

  void Test(int k_rep) {
    for (int rep = 0; rep < k_rep; ++rep) {
      auto g = GenerateGraph();
      auto matching = Matching(g, use_kuhn);
      auto max_size = GetMatchingSize(g);
      ASSERT_EQ(matching.size(), max_size);
      Validate(matching, g);
    }
  }

  BipartiteGraph GenerateGraph() {
    int n = random.GetInt(0, max_n);
    int m = random.GetInt(0, max_m);
    int e = random.GetInt(0, max_e);
    BipartiteGraph g(n, m);
    for (int i = 0; n > 0 && m > 0 && i < e; ++i) {
      int v = random.GetInt(0, n - 1);
      int u = random.GetInt(0, m - 1);
      g[v].push_back(u);
    }
    return g;
  };

  int GetMatchingSize(const BipartiteGraph& g) {
    auto edges = g.Edges();
    int e = edges.size();
    int max_size = 0;
    for (int mask = 0; mask < (1 << e); ++mask) {
      std::vector<bool> left_side_taken(g.n_left_side);
      std::vector<bool> right_side_taken(g.n_right_side);
      bool ok = true;
      for (int i = 0; ok && i < e; ++i) {
        if (((1 << i) & mask) > 0) {
          auto [v, u] = edges[i];
          ok &= !left_side_taken[v];
          ok &= !right_side_taken[u];
          left_side_taken[v] = true;
          right_side_taken[u] = true;
        }
      }
      if (ok) {
        int cur_size = algo::utils::bits::CountOfOnes(u64(mask));
        max_size = std::max(max_size, cur_size);
      }
    }
    return max_size;
  };

  void Validate(const DirectedEdges& matching, const BipartiteGraph& g) {
    std::vector<bool> left_side_taken(g.n_left_side);
    std::vector<bool> right_side_taken(g.n_right_side);
    for (auto [v, u] : matching) {
      ASSERT_TRUE(v >= 0 && v < g.n_left_side);
      ASSERT_TRUE(u >= 0 && u < g.n_right_side);
      ASSERT_CONTAINS(g[v], u);

      ASSERT_FALSE(left_side_taken[v]);
      ASSERT_FALSE(right_side_taken[u]);

      left_side_taken[v] = true;
      right_side_taken[u] = true;
    }
  };
};

void TestKuhn() {
  Tester(true, 10, 10, 10).Test(1000);
  Tester(true, 5, 5, 10).Test(1000);
  Tester(true, 5, 10, 15).Test(100);
  Tester(true, 10, 5, 15).Test(100);
}

void TestDinitz() {
  Tester(false, 10, 10, 10).Test(1000);
  Tester(false, 5, 5, 10).Test(1000);
  Tester(false, 5, 10, 15).Test(100);
  Tester(false, 10, 5, 15).Test(100);
}

int main() {
  TestKuhn();
  TestDinitz();
}
