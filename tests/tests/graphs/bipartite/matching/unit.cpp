#include <algo/graphs/bipartite/matching.hpp>
#include "algo/graphs/entity/bipartite.hpp"
#include "algo/graphs/entity/edge.hpp"
#include "tests/framework/asserts.hpp"
#include "tests/framework/test.hpp"

using namespace algo::graphs;

void Test(bool use_kuhn) {
  /*
  0 -> {0, 1}
  1 -> {0}
  */

  BipartiteGraph g(2, 2);
  g.AddEdge(DirectedEdge(0, 0));
  g.AddEdge(DirectedEdge(0, 1));
  g.AddEdge(DirectedEdge(1, 0));

  auto matching = bipartite::Matching(g, use_kuhn);

  ASSERT_EQ(matching.size(), 2);
  {
    auto edge = DirectedEdge(0, 1);
    ASSERT_CONTAINS(matching, edge);
  }
  {
    auto edge = DirectedEdge(1, 0);
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
