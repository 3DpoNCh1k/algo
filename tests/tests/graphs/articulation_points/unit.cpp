#include <vector>

#include <algo/graphs/entity/edge.hpp>
#include <algo/graphs/entity/graph.hpp>
#include <algo/graphs/articulation_points.hpp>

#include <tests/framework/asserts.hpp>
#include <tests/framework/test.hpp>

TEST(Tree) {
  // 0 - 1 - 2
  algo::graphs::UndirectedGraph g(3);
  g.AddEdge(algo::graphs::UndirectedEdge(0, 1));
  g.AddEdge(algo::graphs::UndirectedEdge(1, 2));

  auto articulation_points = algo::graphs::FindArticulationPoints(g);
  ASSERT_EQ(articulation_points.size(), 1);
  ASSERT_CONTAINS(articulation_points, 1);
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
  auto articulation_points = algo::graphs::FindArticulationPoints(g);
  ASSERT_EQ(articulation_points.size(), 2);
  ASSERT_CONTAINS(articulation_points, 1);
  ASSERT_CONTAINS(articulation_points, 4);
};

RUN_ALL_TESTS()
