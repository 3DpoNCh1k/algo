#include <vector>

#include <algo/graphs/entities.hpp>
#include <algo/graphs/bridges.hpp>
#include "algo/utils/debug.hpp"
#include "tests/testing/asserts.hpp"

void TestTree() {
  // 0 - 1 - 2
  // clang-format off
  std::vector<std::vector<int>> g = {
    {1},
    {0, 2},
    {1}
  };
  // clang-format on
  auto bridges = algo::graphs::FindBridges(g);
  ASSERT_EQ(bridges.size(), 2);
  {
    algo::graphs::Edge bridge = {0, 1};
    ASSERT_CONTAINS(bridges, bridge)
  }
  {
    algo::graphs::Edge bridge = {1, 2};
    ASSERT_CONTAINS(bridges, bridge)
  }
};

void TestGraph() {
  /*
      1 ---- 4
     / \    / \
    0 - 2  3 - 5
  */
  // clang-format off
  std::vector<std::vector<int>> g = {
    {1, 2},
    {0, 2, 4},
    {0, 1},
    {4, 5},
    {1, 3, 5},
    {3, 4}
  };
  // clang-format on
  auto bridges = algo::graphs::FindBridges(g);
  ASSERT_EQ(bridges.size(), 1);
  {
    algo::graphs::Edge bridge = {1, 4};
    ASSERT_CONTAINS(bridges, bridge)
  }
};

int main() {
  TestTree();
  TestGraph();
}
