#include <algo/graphs/entity/graph.hpp>
#include <algo/graphs/bridges.hpp>

#include <algo/graphs/entity/edge.hpp>
#include <tests/framework/asserts.hpp>
#include <tests/framework/test.hpp>

TEST(Tree) {
  // 0 - 1 - 2

  auto g = algo::graphs::UndirectedGraph(3);
  g.AddEdge(algo::graphs::UndirectedEdge(0, 1));
  g.AddEdge(algo::graphs::UndirectedEdge(1, 2));

  auto bridges = algo::graphs::FindBridges(g);
  ASSERT_EQ(bridges.size(), 2);
  {
    algo::graphs::UndirectedEdge bridge = {0, 1};
    ASSERT_CONTAINS(bridges, bridge)
  }
  {
    algo::graphs::UndirectedEdge bridge = {1, 2};
    ASSERT_CONTAINS(bridges, bridge)
  }
};

TEST(Graph) {
  /*
      1 ---- 4
     / \    / \
    0 - 2  3 - 5
  */

  algo::graphs::UndirectedGraph g(6);
  g.AddEdge(algo::graphs::UndirectedEdge(0, 1));
  g.AddEdge(algo::graphs::UndirectedEdge(0, 2));
  g.AddEdge(algo::graphs::UndirectedEdge(1, 2));
  g.AddEdge(algo::graphs::UndirectedEdge(1, 4));
  g.AddEdge(algo::graphs::UndirectedEdge(4, 3));
  g.AddEdge(algo::graphs::UndirectedEdge(4, 5));
  g.AddEdge(algo::graphs::UndirectedEdge(3, 5));

  auto bridges = algo::graphs::FindBridges(g);
  ASSERT_EQ(bridges.size(), 1);
  {
    algo::graphs::UndirectedEdge bridge = {1, 4};
    ASSERT_CONTAINS(bridges, bridge)
  }
};

RUN_ALL_TESTS()
