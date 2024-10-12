
#include <algo/ranges/range.hpp>
#include <algo/trees/segment_tree/updates/set_add.hpp>
#include <algo/trees/segment_tree/updates/set.hpp>
#include <algo/trees/segment_tree/updates/add.hpp>
#include <algo/trees/segment_tree/statistics/minimum.hpp>
#include <algo/trees/segment_tree/trees.hpp>

#include "algo/utils/debug.hpp"
#include "tests/framework/asserts.hpp"
#include "tests/framework/test.hpp"

using namespace algo::ranges;
using namespace algo::trees::segment_tree;
using namespace algo::trees::segment_tree::updates;
using namespace algo::trees::segment_tree::statistics;

template <typename SegmentTree>
void WithApplyOnRange(SegmentTree segment_tree) {
  // Starts with [inf, inf, inf]
  segment_tree.ApplyOnRange(IntSet(Range(0, 2), 0));

  segment_tree.ApplyAtIndex(IntAdd(Range(0, 0), 1));
  {
    auto stat = segment_tree.template GetAtIndex<IntMinimum>(0);
    auto expected = 1;
    ASSERT_EQ(stat.value, expected);
  }

  segment_tree.ApplyOnRange(IntAdd(Range(1, 2), 2));
  {
    auto stat = segment_tree.template GetFromRange<IntMinimum>(Range(1, 2));
    auto expected = 2;
    ASSERT_EQ(stat.value, expected);
  }
  {
    auto stat = segment_tree.template GetFromRange<IntMinimum>(Range(0, 2));
    auto expected = 1;
    ASSERT_EQ(stat.value, expected);
  }

  segment_tree.ApplyOnRange(IntSet(Range(0, 1), 3));
  {
    auto stat = segment_tree.template GetFromRange<IntMinimum>(Range(0, 2));
    auto expected = 2;
    ASSERT_EQ(stat.value, expected);
  }
}

template <typename SegmentTree>
void OnlyApplyAtIndex(SegmentTree segment_tree) {
  // Starts with [inf, inf, inf]

  for (int i = 0; i < 3; ++i) {
    segment_tree.ApplyAtIndex(IntSet(Range(i, i), 0));
  }

  segment_tree.ApplyAtIndex(IntSet(Range(0, 0), -3));
  segment_tree.ApplyAtIndex(IntSet(Range(1, 1), -2));
  segment_tree.ApplyAtIndex(IntAdd(Range(2, 2), -1));

  segment_tree.ApplyAtIndex(IntAdd(Range(0, 0), 1));
  segment_tree.ApplyAtIndex(IntSet(Range(1, 1), 2));
  segment_tree.ApplyAtIndex(IntSet(Range(2, 2), 3));

  {
    auto stat = segment_tree.template GetAtIndex<IntMinimum>(0);
    auto expected = -2;
    ASSERT_EQ(stat.value, expected);
  }
  {
    auto stat = segment_tree.template GetAtIndex<IntMinimum>(1);
    auto expected = 2;
    ASSERT_EQ(stat.value, expected);
  }
  {
    auto stat = segment_tree.template GetAtIndex<IntMinimum>(2);
    auto expected = 3;
    ASSERT_EQ(stat.value, expected);
  }
}

TEST(EagerPropagationStaticSegmentTree) {
  auto segment_tree =
      EagerPropagationStaticSegmentTree<IntSetAdd, IntMinimum>(3);
  OnlyApplyAtIndex(segment_tree);
}

TEST(LazyPropagationStaticSegmentTree) {
  auto segment_tree =
      LazyPropagationStaticSegmentTree<IntSetAdd, IntMinimum>(3);
  OnlyApplyAtIndex(segment_tree);
}

TEST(LazyPropagationDynamicSegmentTree) {
  auto segment_tree =
      LazyPropagationDynamicSegmentTree<IntSetAdd, IntMinimum>(0, 2);
  OnlyApplyAtIndex(segment_tree);
}

TEST(LazyPropagationStaticSegmentTreeWithRange) {
  auto segment_tree =
      LazyPropagationStaticSegmentTree<IntSetAdd, IntMinimum>(3);
  WithApplyOnRange(segment_tree);
}

TEST(LazyPropagationDynamicSegmentTreeWithRange) {
  auto segment_tree =
      LazyPropagationDynamicSegmentTree<IntSetAdd, IntMinimum>(0, 2);
  WithApplyOnRange(segment_tree);
}

RUN_ALL_TESTS()
