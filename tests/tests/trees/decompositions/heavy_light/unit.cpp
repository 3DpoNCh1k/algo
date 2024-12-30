
#include <algo/ranges/updates/add.hpp>
#include <algo/ranges/statistics/sum.hpp>
#include <algo/trees/decompositions/heavy_light.hpp>
#include <algo/trees/entity/tree.hpp>

#include <algo/debug/debug.hpp>
#include <tests/framework/asserts.hpp>
#include <tests/framework/test.hpp>

using algo::ranges::statistics::IntSum;
using algo::ranges::updates::IntAdd;

TEST(Simple1) {
  // 0 - 1 - 2
  algo::trees::Tree tree(3);
  tree.AddEdge(0, 1);
  tree.AddEdge(1, 2);

  algo::trees::decompositions::HLD<IntAdd, IntSum> hld(tree);
  {
    auto stat = hld.GetFromPath(0, 2);
    ASSERT_EQ(stat, 0);
  }
  hld.ApplyOnPath(0, 1, 1);
  {
    auto stat = hld.GetFromVertex(0);
    debug(stat);
    ASSERT_EQ(stat, 1);
  }
  {
    auto stat = hld.GetFromVertex(1);
    debug(stat);
    ASSERT_EQ(stat, 1);
  }
  {
    auto stat = hld.GetFromVertex(2);
    debug(stat);
    ASSERT_EQ(stat, 0);
  }
  {
    auto stat = hld.GetFromPath(0, 1);
    debug(stat);
    ASSERT_EQ(stat, 2);
  }
  {
    auto stat = hld.GetFromPath(1, 2);
    debug(stat);
    ASSERT_EQ(stat, 1);
  }
  {
    auto stat = hld.GetFromPath(0, 2);
    debug(stat);
    ASSERT_EQ(stat, 2);
  }
}

TEST(Simple2) {
  /*
       0
      / \
     1   2
  */
  algo::trees::Tree tree(3);
  tree.AddEdge(0, 1);
  tree.AddEdge(0, 2);

  algo::trees::decompositions::HLD<IntAdd, IntSum> hld(tree);
  {
    auto stat = hld.GetFromPath(0, 2);
    ASSERT_EQ(stat, 0);
  }
  hld.ApplyAtVertex(0, 1);
  hld.ApplyAtVertex(1, 2);
  hld.ApplyAtVertex(2, 3);
  {
    auto stat = hld.GetFromVertex(0);
    debug(stat);
    ASSERT_EQ(stat, 1);
  }
  {
    auto stat = hld.GetFromVertex(1);
    debug(stat);
    ASSERT_EQ(stat, 2);
  }
  {
    auto stat = hld.GetFromVertex(2);
    debug(stat);
    ASSERT_EQ(stat, 3);
  }
  {
    auto stat = hld.GetFromPath(0, 1);
    debug(stat);
    ASSERT_EQ(stat, 3);
  }
  {
    auto stat = hld.GetFromPath(1, 2);
    debug(stat);
    ASSERT_EQ(stat, 6);
  }
  {
    auto stat = hld.GetFromPath(0, 2);
    debug(stat);
    ASSERT_EQ(stat, 4);
  }
}

TEST(Simple3) {
  /*
       0
      / \
     1   3
     |   |
     4   2
  */
  algo::trees::Tree tree(5);
  tree.AddEdge(0, 1);
  tree.AddEdge(1, 4);
  tree.AddEdge(0, 3);
  tree.AddEdge(3, 2);

  algo::trees::decompositions::HLD<IntAdd, IntSum> hld(tree);
  {
    auto stat = hld.GetFromPath(2, 4);
    ASSERT_EQ(stat, 0);
  }
  hld.ApplyOnPath(3, 2, -1);
  {
    auto stat = hld.GetFromPath(0, 1);
    debug(stat);
    ASSERT_EQ(stat, 0);
  }
  {
    auto stat = hld.GetFromPath(2, 1);
    debug(stat);
    ASSERT_EQ(stat, -2);
  }
}

RUN_ALL_TESTS()
