#include <algorithm>

#include <algo/graphs/articulation_points.hpp>
#include <algo/utils/generators/graph.hpp>
#include <algo/utils/random/random.hpp>

#include <tests/framework/asserts.hpp>
#include <tests/framework/test.hpp>

#include "correct.hpp"

using namespace algo::graphs;
using namespace algo::utils::random;
using namespace algo::utils::generators;

void Stress(int k_rep, int max_n, int max_m) {
  auto correct = Correct{};
  auto graph_generator = GraphGenerator();
  for (int rep = 0; rep < k_rep; ++rep) {
    int n = RandomInt(0, max_n);
    int m = RandomInt(0, max_m);
    auto g = graph_generator.UndirectedGraph(n, m);
    auto result = FindArticulationPoints(g);
    auto expected = correct.GetArticulationPoints(g);
    sort(result.begin(), result.end());
    sort(expected.begin(), expected.end());
    ASSERT_EQ(result, expected);
  }
}

TEST(StressSmall) {
  Stress(1000, 10, 10);
}

TEST(StressBig) {
  Stress(1000, 25, 5'000);
}

RUN_ALL_TESTS()
