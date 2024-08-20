#include <vector>

#include <algo/graphs/entities.hpp>
#include "algo/graphs/articulation_points.hpp"
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
  auto articulation_points = algo::graphs::FindArticulationPoints(g);
  ASSERT_EQ(articulation_points.size(), 1);
  ASSERT_CONTAINS(articulation_points, 1);
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
  auto articulation_points = algo::graphs::FindArticulationPoints(g);
  ASSERT_EQ(articulation_points.size(), 2);
  ASSERT_CONTAINS(articulation_points, 1);
  ASSERT_CONTAINS(articulation_points, 4);
};

int main() {
  TestTree();
  TestGraph();
}
