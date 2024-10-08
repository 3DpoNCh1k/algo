#include <algo/graphs/entities.hpp>
#include <algo/graphs/bridges.hpp>
#include "algo/utils/generators/random.hpp"
#include "tests/framework/asserts.hpp"
#include "tests/framework/test.hpp"

#include "correct.hpp"

using namespace algo::graphs;

AdjacencyList GenerateGraph(int n, int m,
                            algo::utils::generators::RandomGenerator& random) {
  AdjacencyList g(n);
  for (int i = 0; n > 0 && i < m; ++i) {
    int u = random.GetInt(0, n - 1);
    int v = random.GetInt(0, n - 1);
    g[u].push_back(v);
    g[v].push_back(u);
  }
  return g;
};

void Stress(int k_rep, int max_n, int max_m) {
  auto random = algo::utils::generators::RandomGenerator(max_n ^ max_m);
  auto correct = Correct{};
  for (int rep = 0; rep < k_rep; ++rep) {
    int n = random.GetInt(0, max_n);
    int m = random.GetInt(0, max_m);
    auto g = GenerateGraph(n, m, random);
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
