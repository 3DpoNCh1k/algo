#include <algo/graphs/bipartite/matching.hpp>
#include <algo/graphs/entity/bipartite.hpp>
#include <algo/graphs/entity/edge.hpp>
#include <tests/framework/asserts.hpp>
#include <tests/framework/test.hpp>

void Test(bool use_kuhn) {
  /*
  0 -> {0, 1}
  1 -> {0}
  */

  algo::graphs::BipartiteGraph g(2, 2);
  g.AddEdge(algo::graphs::DirectedEdge(0, 0));
  g.AddEdge(algo::graphs::DirectedEdge(0, 1));
  g.AddEdge(algo::graphs::DirectedEdge(1, 0));

  auto matching = algo::graphs::bipartite::Matching(g, use_kuhn);

  ASSERT_EQ(matching.size(), 2);
  {
    auto edge = algo::graphs::DirectedEdge(0, 1);
    ASSERT_CONTAINS(matching, edge);
  }
  {
    auto edge = algo::graphs::DirectedEdge(1, 0);
    ASSERT_CONTAINS(matching, edge);
  }
}

TEST(Kuhn) {
  Test(true);
}
TEST(Dinitz) {
  Test(false);
}

RUN_ALL_TESTS()
