
#include <algo/trees/entity/tree.hpp>

#include <algo/debug/debug.hpp>
#include <tests/framework/asserts.hpp>
#include <tests/framework/test.hpp>

#include "centroid.hpp"

using namespace algo::trees;

TEST(Simple1) {
  // 0 - 1
  Tree tree(2);
  tree.AddEdge(0, 1);

  MinCentroid centroids(tree);

  {
    auto result = centroids.GetMin(0, 0);
    debug(result);
    ASSERT_EQ(result, 0);
  }
  {
    auto result = centroids.GetMin(1, 1);
    debug(result);
    ASSERT_EQ(result, 0);
  }
}

TEST(Simple2) {
  // 0 - 1 - 2
  Tree tree(3);
  tree.AddEdge(0, 1);
  tree.AddEdge(1, 2);

  MinCentroid centroids(tree);

  {
    auto result = centroids.GetMin(0, 0);
    debug(result);
    ASSERT_EQ(result, 0);
  }
  {
    auto result = centroids.GetMin(1, 1);
    debug(result);
    ASSERT_EQ(result, 0);
  }
  {
    auto result = centroids.GetMin(1, 2);
    debug(result);
    ASSERT_EQ(result, 0);
  }
}

RUN_ALL_TESTS()
