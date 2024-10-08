#include <algo/trees/decompositions/centroid.hpp>

#include <algo/trees/segment_tree/operations/add.hpp>
#include <algo/trees/segment_tree/statistics/sum.hpp>
#include "algo/trees/segment_tree/operations/set.hpp"
#include "algo/trees/segment_tree/statistics/minimum.hpp"
#include "algo/trees/segment_tree/trees.hpp"
#include "algo/utils/debug.hpp"
#include "tests/framework/asserts.hpp"
#include "tests/framework/test.hpp"

using namespace algo::trees::decompositions;
using namespace algo::trees::segment_tree;

TEST(Simple1) {
  using Tree = std::vector<std::vector<int>>;
  // 0 - 1
  Tree tree = {{1}, {0}};
  Centroids<Operation<operations::SetOp>, Statistics<statistics::Minimum>>
      centroids(tree);

  {
    auto result = centroids.GetMin(0, 0);
    dbg(result);
    ASSERT_EQ(result, 0);
  }
  {
    auto result = centroids.GetMin(1, 1);
    dbg(result);
    ASSERT_EQ(result, 0);
  }
}

TEST(Simple2) {
  using Tree = std::vector<std::vector<int>>;
  // 0 - 1 - 2
  // clang-format off
  Tree tree = {
    {1},
    {0, 2},
    {1}
   };
  // clang-format on
  Centroids<Operation<operations::SetOp>, Statistics<statistics::Minimum>>
      centroids(tree);

  {
    auto result = centroids.GetMin(0, 0);
    dbg(result);
    ASSERT_EQ(result, 0);
  }
  {
    auto result = centroids.GetMin(1, 1);
    dbg(result);
    ASSERT_EQ(result, 0);
  }
  {
    auto result = centroids.GetMin(1, 2);
    dbg(result);
    ASSERT_EQ(result, 0);
  }
}

RUN_ALL_TESTS()
