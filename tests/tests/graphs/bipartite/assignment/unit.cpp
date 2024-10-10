#include <algo/graphs/bipartite/assignment.hpp>
#include <algo/graphs/entity/bipartite.hpp>

#include "algo/graphs/entity/edge.hpp"
#include "tests/framework/asserts.hpp"
#include "tests/framework/test.hpp"

using namespace algo::graphs;

TEST(Simple1) {
  BipartiteGraphWith<Cost<int>> grid(2, 2);
  grid.AddEdge(DirectedEdgeWith<Cost<int>>(0, 0, Cost(0)));
  grid.AddEdge(DirectedEdgeWith<Cost<int>>(0, 1, Cost(0)));
  grid.AddEdge(DirectedEdgeWith<Cost<int>>(1, 0, Cost(0)));
  grid.AddEdge(DirectedEdgeWith<Cost<int>>(1, 1, Cost(1)));

  auto assignment = bipartite::Assignment(grid);

  ASSERT_EQ(assignment.size(), 2);
  {
    auto edge = DirectedEdgeWith<Cost<int>>(0, 1, Cost(0));
    ASSERT_CONTAINS(assignment, edge);
  }
  {
    auto edge = DirectedEdgeWith<Cost<int>>(1, 0, Cost(0));
    ASSERT_CONTAINS(assignment, edge);
  }
}

TEST(Simple2) {
  BipartiteGraphWith<Cost<int>> grid(2, 2);

  grid.AddEdge(DirectedEdgeWith<Cost<int>>(0, 1, Cost(10)));
  grid.AddEdge(DirectedEdgeWith<Cost<int>>(1, 0, Cost(100)));
  grid.AddEdge(DirectedEdgeWith<Cost<int>>(1, 1, Cost(0)));

  auto assignment = bipartite::Assignment(grid);

  ASSERT_EQ(assignment.size(), 2);
  {
    auto edge = DirectedEdgeWith<Cost<int>>(0, 1, Cost(10));
    ASSERT_CONTAINS(assignment, edge);
  }
  {
    auto edge = DirectedEdgeWith<Cost<int>>(1, 0, Cost(100));
    ASSERT_CONTAINS(assignment, edge);
  }
}

RUN_ALL_TESTS()
