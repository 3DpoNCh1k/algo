#include <algo/graphs/entity/graph.hpp>
#include <algo/graphs/bridges.hpp>
#include "algo/utils/random/random.hpp"
#include "algo/utils/generators/graph.hpp"
#include "tests/framework/asserts.hpp"
#include "tests/framework/test.hpp"

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
    auto result = FindBridges(g);
    auto expected = correct.GetBridges(g);
    ASSERT_EQ(result.size(), expected.size());
    for (auto edge : expected) {
      ASSERT_CONTAINS(result, edge);
    }
  }
}

TEST(StressSmall) {
  Stress(1000, 10, 10);
}

TEST(StressBig) {
  Stress(100, 25, 500);
}

RUN_ALL_TESTS()
