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

TEST(Bamboo) {
  using Tree = std::vector<std::vector<int>>;
  // 0 - 1
  Tree tree = {{1}, {0}};
  Centroids<Operation<operations::SetOp>, Statistics<statistics::Minimum>>
      centroids(tree);

  {
    auto result = centroids.GetSum(0);
    dbg(result);
    ASSERT_EQ(result, 1);
  }
  {
    auto result = centroids.GetSum(1);
    dbg(result);
    ASSERT_EQ(result, 1);
  }
  centroids.ChangeColor(0);
  {
    auto result = centroids.GetSum(0);
    dbg(result);
    ASSERT_EQ(result, 0);
  }
  {
    auto result = centroids.GetSum(1);
    dbg(result);
    ASSERT_EQ(result, 0);
  }
  centroids.ChangeColor(1);
  {
    auto result = centroids.GetSum(0);
    dbg(result);
    ASSERT_EQ(result, 1);
  }
  {
    auto result = centroids.GetSum(1);
    dbg(result);
    ASSERT_EQ(result, 1);
  }
}

TEST(Tree) {
  using Tree = std::vector<std::vector<int>>;
  /*
      2
     / \
    1   3
       / \
      0   4
  */
  // clang-format off
  Tree tree = {
{3}, 
{2}, 
{1,3}, 
{0,2,4}, 
{3}
  };
  // clang-format on
  Centroids<Operation<operations::SetOp>, Statistics<statistics::Minimum>>
      centroids(tree);

  {
    auto result = centroids.GetSum(0);
    dbg(result);
    ASSERT_EQ(result, 8);
  }
  {
    auto result = centroids.GetSum(3);
    dbg(result);
    ASSERT_EQ(result, 5);
  }
  centroids.ChangeColor(1);
  {
    auto result = centroids.GetSum(3);
    dbg(result);
    ASSERT_EQ(result, 3);
  }
  {
    auto result = centroids.GetSum(1);
    dbg(result);
    ASSERT_EQ(result, 0);
  }
}

RUN_ALL_TESTS()
