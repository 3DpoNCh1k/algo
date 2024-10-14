#include <algo/trees/decompositions/centroid.hpp>

#include <algo/ranges/segment_tree/operations/add.hpp>
#include <algo/ranges/statistics/sum.hpp>
#include "algo/ranges/segment_tree/operations/set.hpp"
#include "algo/ranges/statistics/minimum.hpp"
#include "algo/ranges/segment_tree/trees.hpp"
#include "algo/trees/entity/tree.hpp"

#include "algo/debug/debug.hpp"
#include "tests/framework/asserts.hpp"
#include "tests/framework/test.hpp"

using namespace algo::trees::decompositions;
using namespace algo::ranges::segment_tree;
using namespace algo::trees;

TEST(Bamboo) {
  // 0 - 1
  Tree tree(2);
  tree.AddEdge(0, 1);

  Centroids<Operation<operations::SetOp>, Statistics<statistics::Minimum>>
      centroids(tree);

  {
    auto result = centroids.GetSum(0);
    debug(result);
    ASSERT_EQ(result, 1);
  }
  {
    auto result = centroids.GetSum(1);
    debug(result);
    ASSERT_EQ(result, 1);
  }
  centroids.ChangeColor(0);
  {
    auto result = centroids.GetSum(0);
    debug(result);
    ASSERT_EQ(result, 0);
  }
  {
    auto result = centroids.GetSum(1);
    debug(result);
    ASSERT_EQ(result, 0);
  }
  centroids.ChangeColor(1);
  {
    auto result = centroids.GetSum(0);
    debug(result);
    ASSERT_EQ(result, 1);
  }
  {
    auto result = centroids.GetSum(1);
    debug(result);
    ASSERT_EQ(result, 1);
  }
}

TEST(Tree) {
  /*
      2
     / \
    1   3
       / \
      0   4
  */
  Tree tree(5);
  tree.AddEdge(1, 2);
  tree.AddEdge(2, 3);
  tree.AddEdge(3, 0);
  tree.AddEdge(3, 4);

  Centroids<Operation<operations::SetOp>, Statistics<statistics::Minimum>>
      centroids(tree);

  {
    auto result = centroids.GetSum(0);
    debug(result);
    ASSERT_EQ(result, 8);
  }
  {
    auto result = centroids.GetSum(3);
    debug(result);
    ASSERT_EQ(result, 5);
  }
  centroids.ChangeColor(1);
  {
    auto result = centroids.GetSum(3);
    debug(result);
    ASSERT_EQ(result, 3);
  }
  {
    auto result = centroids.GetSum(1);
    debug(result);
    ASSERT_EQ(result, 0);
  }
}

RUN_ALL_TESTS()
