#include <algo/graphs/bipartite/matching.hpp>
#include "algo/graphs/entities.hpp"
#include "algo/utils/debug.hpp"
#include "tests/testing/asserts.hpp"

using namespace algo::graphs;

void Test() {
  /*
  0 -> {0, 1}
  1 -> {0}
  */
  // clang-format off
  BipartiteGraph g {
    2, 2, {
      {0, 1},
      {0}
    }
  };
  // clang-format on

  auto matching = bipartite::Matching(g);
  dbg(matching);

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

int main() {
  Test();
}
