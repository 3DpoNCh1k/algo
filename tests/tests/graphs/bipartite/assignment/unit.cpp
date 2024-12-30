#include <algo/graphs/bipartite/assignment.hpp>
#include <algo/graphs/entity/bipartite.hpp>

#include <algo/graphs/entity/edge.hpp>
#include <tests/framework/asserts.hpp>
#include <tests/framework/test.hpp>

TEST(Simple1) {
  algo::graphs::BipartiteGraphWith<algo::graphs::Cost<int>> grid(2, 2);
  grid.AddEdge(algo::graphs::DirectedEdgeWith(0, 0, algo::graphs::Cost(0)));
  grid.AddEdge(algo::graphs::DirectedEdgeWith(0, 1, algo::graphs::Cost(0)));
  grid.AddEdge(algo::graphs::DirectedEdgeWith(1, 0, algo::graphs::Cost(0)));
  grid.AddEdge(algo::graphs::DirectedEdgeWith(1, 1, algo::graphs::Cost(1)));

  auto assignment = algo::graphs::bipartite::Assignment(grid);

  ASSERT_EQ(assignment.size(), 2);
  {
    auto edge = algo::graphs::DirectedEdgeWith(0, 1, algo::graphs::Cost(0));
    ASSERT_CONTAINS(assignment, edge);
  }
  {
    auto edge = algo::graphs::DirectedEdgeWith(1, 0, algo::graphs::Cost(0));
    ASSERT_CONTAINS(assignment, edge);
  }
}

TEST(Simple2) {
  algo::graphs::BipartiteGraphWith<algo::graphs::Cost<int>> grid(2, 2);

  grid.AddEdge(algo::graphs::DirectedEdgeWith(0, 1, algo::graphs::Cost(10)));
  grid.AddEdge(algo::graphs::DirectedEdgeWith(1, 0, algo::graphs::Cost(100)));
  grid.AddEdge(algo::graphs::DirectedEdgeWith(1, 1, algo::graphs::Cost(0)));

  auto assignment = algo::graphs::bipartite::Assignment(grid);

  ASSERT_EQ(assignment.size(), 2);
  {
    auto edge = algo::graphs::DirectedEdgeWith(0, 1, algo::graphs::Cost(10));
    ASSERT_CONTAINS(assignment, edge);
  }
  {
    auto edge = algo::graphs::DirectedEdgeWith(1, 0, algo::graphs::Cost(100));
    ASSERT_CONTAINS(assignment, edge);
  }
}

RUN_ALL_TESTS()
