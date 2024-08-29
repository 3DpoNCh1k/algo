#include <algo/graphs/bipartite/assignment.hpp>
#include "algo/graphs/entities.hpp"
#include "algo/utils/debug.hpp"
#include "tests/testing/asserts.hpp"

using namespace algo::graphs;

void Test() {
  // {
  //   BipartiteGraphWithCost grid(2, 2);
  //   grid.AddEdge(0, 0, 0);
  //   grid.AddEdge(0, 1, 1);
  //   grid.AddEdge(1, 0, 1);
  //   grid.AddEdge(1, 1, 0);

  //   auto assignment = bipartite::Assignment(grid);

  //   ASSERT_EQ(assignment.size(), 2);
  //   {
  //     auto edge = DirectedEdgeWithCost(0, 0, 0);
  //     ASSERT_CONTAINS(assignment, edge);
  //   }
  //   {
  //     auto edge = DirectedEdgeWithCost(1, 1, 0);
  //     ASSERT_CONTAINS(assignment, edge);
  //   }
  // }

  {
    BipartiteGraphWithCost grid(2, 2);
    grid.AddEdge(0, 0, 0);
    grid.AddEdge(0, 1, 0);
    grid.AddEdge(1, 0, 0);
    grid.AddEdge(1, 1, 1);

    auto assignment = bipartite::Assignment(grid);

    ASSERT_EQ(assignment.size(), 2);
    {
      auto edge = DirectedEdgeWithCost(0, 1, 0);
      ASSERT_CONTAINS(assignment, edge);
    }
    {
      auto edge = DirectedEdgeWithCost(1, 0, 0);
      ASSERT_CONTAINS(assignment, edge);
    }
  }

  {
    BipartiteGraphWithCost grid(2, 2);
    grid.AddEdge(0, 1, 10);
    grid.AddEdge(1, 0, 100);
    grid.AddEdge(1, 1, 0);

    auto assignment = bipartite::Assignment(grid);

    ASSERT_EQ(assignment.size(), 2);
    {
      auto edge = DirectedEdgeWithCost(0, 1, 10);
      ASSERT_CONTAINS(assignment, edge);
    }
    {
      auto edge = DirectedEdgeWithCost(1, 0, 100);
      ASSERT_CONTAINS(assignment, edge);
    }
  }
}

int main() {
  Test();
}
