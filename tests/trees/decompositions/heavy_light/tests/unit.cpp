
#include <algo/trees/segment_tree/operations/add.hpp>
#include <algo/trees/segment_tree/statistics/sum.hpp>
#include <algo/trees/decompositions/heavy_light.hpp>
#include "algo/trees/segment_tree/trees.hpp"
#include "algo/utils/debug.hpp"
#include "tests/framework/asserts.hpp"
#include "tests/framework/test.hpp"

using namespace algo::trees::decompositions;
using namespace algo::trees::segment_tree;

TEST(Simple1) {
  using Tree = std::vector<std::vector<int>>;
  // 0 - 1 - 2
  Tree tree = {{1}, {0, 2}, {1}};
  HLD<Operation<operations::AddOp>, Statistics<statistics::Sum>> hld(tree);
  {
    auto stat = hld.GetFromPath<statistics::Sum>(0, 2);
    ASSERT_EQ(stat.result, 0);
  }
  hld.ApplyOnPath(0, 1, operations::AddOp{1});
  {
    auto stat = hld.GetFromVertex<statistics::Sum>(0);
    dbg(stat.result);
    ASSERT_EQ(stat.result, 1);
  }
  {
    auto stat = hld.GetFromVertex<statistics::Sum>(1);
    dbg(stat.result);
    ASSERT_EQ(stat.result, 1);
  }
  {
    auto stat = hld.GetFromVertex<statistics::Sum>(2);
    dbg(stat.result);
    ASSERT_EQ(stat.result, 0);
  }
  {
    auto stat = hld.GetFromPath<statistics::Sum>(0, 1);
    dbg(stat.result);
    ASSERT_EQ(stat.result, 2);
  }
  {
    auto stat = hld.GetFromPath<statistics::Sum>(1, 2);
    dbg(stat.result);
    ASSERT_EQ(stat.result, 1);
  }
  {
    auto stat = hld.GetFromPath<statistics::Sum>(0, 2);
    dbg(stat.result);
    ASSERT_EQ(stat.result, 2);
  }
}

TEST(Simple2) {
  using Tree = std::vector<std::vector<int>>;
  /*
       0
      / \
     1   2
  */
  Tree tree = {{1, 2}, {0}, {0}};
  HLD<Operation<operations::AddOp>, Statistics<statistics::Sum>> hld(tree);
  {
    auto stat = hld.GetFromPath<statistics::Sum>(0, 2);
    ASSERT_EQ(stat.result, 0);
  }
  hld.ApplyAtVertex(0, operations::AddOp{1});
  hld.ApplyAtVertex(1, operations::AddOp{2});
  hld.ApplyAtVertex(2, operations::AddOp{3});
  {
    auto stat = hld.GetFromVertex<statistics::Sum>(0);
    dbg(stat.result);
    ASSERT_EQ(stat.result, 1);
  }
  {
    auto stat = hld.GetFromVertex<statistics::Sum>(1);
    dbg(stat.result);
    ASSERT_EQ(stat.result, 2);
  }
  {
    auto stat = hld.GetFromVertex<statistics::Sum>(2);
    dbg(stat.result);
    ASSERT_EQ(stat.result, 3);
  }
  {
    auto stat = hld.GetFromPath<statistics::Sum>(0, 1);
    dbg(stat.result);
    ASSERT_EQ(stat.result, 3);
  }
  {
    auto stat = hld.GetFromPath<statistics::Sum>(1, 2);
    dbg(stat.result);
    ASSERT_EQ(stat.result, 6);
  }
  {
    auto stat = hld.GetFromPath<statistics::Sum>(0, 2);
    dbg(stat.result);
    ASSERT_EQ(stat.result, 4);
  }
}

TEST(Simple3) {
  using Tree = std::vector<std::vector<int>>;
  /*
       0
      / \
     1   3
     |   |
     4   2
  */
  // clang-format off
  Tree tree = {
    {1, 3},
    {0, 4},
    {3},
    {0, 2},
    {1}};
  // clang-format on
  HLD<Operation<operations::AddOp>, Statistics<statistics::Sum>> hld(tree);
  {
    auto stat = hld.GetFromPath<statistics::Sum>(2, 4);
    ASSERT_EQ(stat.result, 0);
  }
  hld.ApplyOnPath(3, 2, operations::AddOp{-1});
  {
    auto stat = hld.GetFromPath<statistics::Sum>(0, 1);
    dbg(stat.result);
    ASSERT_EQ(stat.result, 0);
  }
  {
    auto stat = hld.GetFromPath<statistics::Sum>(2, 1);
    dbg(stat.result);
    ASSERT_EQ(stat.result, -2);
  }
}

RUN_ALL_TESTS()
