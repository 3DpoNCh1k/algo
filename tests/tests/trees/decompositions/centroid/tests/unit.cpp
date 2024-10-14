#include <algo/trees/decompositions/centroid.hpp>

#include <algo/ranges/segment_tree/operations/add.hpp>
#include <algo/ranges/statistics/sum.hpp>
#include "algo/ranges/segment_tree/operations/set.hpp"
#include "algo/ranges/statistics/minimum.hpp"
#include "algo/ranges/segment_tree/trees.hpp"
#include "algo/trees/entity/tree.hpp"

#include "algo/utils/debug.hpp"
#include "tests/framework/asserts.hpp"
#include "tests/framework/test.hpp"

using namespace algo::trees::decompositions;
using namespace algo::ranges::segment_tree;
using namespace algo::trees;

TEST(Simple1) {
  // 0 - 1
  Tree tree(2);
  tree.AddEdge(0, 1);

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
  // 0 - 1 - 2
  Tree tree(3);
  tree.AddEdge(0, 1);
  tree.AddEdge(1, 2);

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
