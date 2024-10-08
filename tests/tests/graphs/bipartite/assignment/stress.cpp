#include <algo/graphs/entities.hpp>
#include <algo/graphs/bipartite/assignment.hpp>
#include "algo/utils/generators/random.hpp"
#include "algo/utils/types/fundamentals.hpp"
#include "tests/framework/test.hpp"

#include "validate.hpp"

using namespace algo::graphs;
using namespace algo::graphs::bipartite;

BipartiteGraphWithCost GenerateGraph(
    int n, int m, i64 min_c, i64 max_c, bool full,
    algo::utils::generators::RandomGenerator& random) {
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

void Stress(int k_rep, int min_n, int max_n, i64 min_c, i64 max_c, bool full) {
  auto random =
      algo::utils::generators::RandomGenerator(min_n ^ max_n ^ min_c ^ max_c);
  for (int rep = 0; rep < k_rep; ++rep) {
    int n = random.GetInt(min_n, max_n);
    int m = random.GetInt(min_n, max_n);
    auto g = GenerateGraph(n, m, min_c, max_c, full, random);
    auto assignment = Assignment(g);
    Validate(assignment, g);
  }
}

TEST(StressSmallFull) {
  Stress(1000, 1, 5, -10, 10, true);
}

TEST(StressSmall) {
  Stress(1000, 1, 5, -10, 10, false);
}

TEST(StressBigFull) {
  Stress(50, 6, 8, -1e9, 1e9, true);
}

TEST(StressBig) {
  Stress(50, 6, 8, -1e9, 1e9, false);
}

RUN_ALL_TESTS()
