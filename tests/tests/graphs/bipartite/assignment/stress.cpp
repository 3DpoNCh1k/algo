#include <algo/graphs/entity/bipartite.hpp>
#include <algo/graphs/bipartite/assignment.hpp>
#include <algo/utils/generators/graph.hpp>
#include <algo/utils/random/random.hpp>
#include <algo/utils/types/fundamentals.hpp>
#include <tests/framework/test.hpp>

#include "validate.hpp"

using algo::utils::random::RandomInt;

void Stress(int k_rep, int min_n, int max_n, i64 min_c, i64 max_c, bool full) {
  auto graph_generator = algo::utils::generators::GraphGenerator();
  for (int rep = 0; rep < k_rep; ++rep) {
    int n = RandomInt(min_n, max_n);
    int m = RandomInt(min_n, max_n);
    auto g = graph_generator.BipartiteGraphWithCost(n, m, full, min_c, max_c);
    auto assignment = algo::graphs::bipartite::Assignment(g);
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
