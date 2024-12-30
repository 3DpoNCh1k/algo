#include <algo/trees/entity/tree.hpp>

#include <algo/debug/debug.hpp>
#include <tests/framework/asserts.hpp>
#include <tests/framework/test.hpp>

#include "centroid.hpp"

TEST(Bamboo) {
  // 0 - 1
  algo::trees::Tree tree(2);
  tree.AddEdge(0, 1);

  SumCentroid centroids(tree);

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
  algo::trees::Tree tree(5);
  tree.AddEdge(1, 2);
  tree.AddEdge(2, 3);
  tree.AddEdge(3, 0);
  tree.AddEdge(3, 4);

  SumCentroid centroids(tree);

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
