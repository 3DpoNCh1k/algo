#include <algo/graphs/bipartite/matching.hpp>
#include <algo/utils/generators/graph.hpp>
#include <algo/utils/random/random.hpp>
#include <tests/framework/asserts.hpp>
#include <tests/framework/test.hpp>

#include "validate.hpp"

using namespace algo::graphs;
using namespace algo::graphs::bipartite;
using namespace algo::utils::random;
using namespace algo::utils::generators;

void Stress(int k_rep, bool use_kuhn, int max_n, int max_m, int max_e) {
  auto graph_generator = GraphGenerator();
  for (int rep = 0; rep < k_rep; ++rep) {
    int n = RandomInt(0, max_n);
    int m = RandomInt(0, max_m);
    int e = RandomInt(0, max_e);
    auto g = graph_generator.BipartiteGraph(n, m, e);
    auto matching = Matching(g, use_kuhn);
    auto max_size = GetMatchingSize(g);
    ASSERT_EQ(matching.size(), max_size);
    Validate(matching, g);
  }
}

TEST(StressKuhnEqualSidesSmall) {
  Stress(1000, true, 5, 5, 10);
}
TEST(StressKuhnEqualSidesBig) {
  Stress(1000, true, 10, 10, 10);
}

TEST(StressKuhnLeftSideSmaller) {
  Stress(100, true, 5, 10, 15);
}
TEST(StressKuhnLeftSideBigger) {
  Stress(100, true, 10, 5, 15);
}

TEST(StressDinitzEqualSidesSmall) {
  Stress(1000, false, 5, 5, 10);
}
TEST(StressDinitzEqualSidesBig) {
  Stress(1000, false, 10, 10, 10);
}

TEST(StressDinitzLeftSideSmaller) {
  Stress(100, false, 5, 10, 15);
}
TEST(StressDinitzLeftSideBigger) {
  Stress(100, false, 10, 5, 15);
}

RUN_ALL_TESTS()
