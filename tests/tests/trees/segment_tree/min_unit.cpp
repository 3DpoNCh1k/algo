
#include <algo/trees/segment_tree/operations/set_add.hpp>
#include <algo/trees/segment_tree/statistics/minimum.hpp>
#include <algo/trees/segment_tree/trees.hpp>

#include "algo/trees/segment_tree/operations/set.hpp"
#include "algo/utils/debug.hpp"
#include "tests/framework/asserts.hpp"
#include "tests/framework/test.hpp"

using namespace algo::trees::segment_tree;

template <typename SegmentTree>
void WithApplyOnRange(SegmentTree segment_tree) {
  // Starts with [inf, inf, inf]
  segment_tree.ApplyOnRange(0, 2, operations::SetOp{true, 0});

  segment_tree.ApplyAtIndex(0, operations::AddOp{1});
  {
    auto stat = segment_tree.template GetAtIndex<statistics::Minimum>(0);
    auto expected = 1;
    ASSERT_EQ(stat.result, expected);
  }

  segment_tree.ApplyOnRange(1, 2, operations::AddOp{2});
  {
    auto stat = segment_tree.template GetFromRange<statistics::Minimum>(1, 2);
    auto expected = 2;
    ASSERT_EQ(stat.result, expected);
  }
  {
    auto stat = segment_tree.template GetFromRange<statistics::Minimum>(0, 2);
    auto expected = 1;
    ASSERT_EQ(stat.result, expected);
  }

  segment_tree.ApplyOnRange(0, 1, operations::SetOp{true, 3});
  {
    auto stat = segment_tree.template GetFromRange<statistics::Minimum>(0, 2);
    auto expected = 2;
    ASSERT_EQ(stat.result, expected);
  }
}

template <typename SegmentTree>
void OnlyApplyAtIndex(SegmentTree segment_tree) {
  // Starts with [inf, inf, inf]
  for (int i = 0; i < 3; ++i) {
    segment_tree.ApplyAtIndex(i, operations::SetOp{true, 0});
  }

  segment_tree.ApplyAtIndex(0, operations::SetOp{true, -3});
  segment_tree.ApplyAtIndex(1, operations::SetOp{true, -2});
  segment_tree.ApplyAtIndex(2, operations::AddOp{-1});

  segment_tree.ApplyAtIndex(0, operations::AddOp{1});
  segment_tree.ApplyAtIndex(1, operations::SetOp{true, 2});
  segment_tree.ApplyAtIndex(2, operations::SetOp{true, 3});
  {
    auto stat = segment_tree.template GetAtIndex<statistics::Minimum>(0);
    auto expected = -2;
    ASSERT_EQ(stat.result, expected);
  }
  {
    auto stat = segment_tree.template GetAtIndex<statistics::Minimum>(1);
    auto expected = 2;
    ASSERT_EQ(stat.result, expected);
  }
  {
    auto stat = segment_tree.template GetAtIndex<statistics::Minimum>(2);
    auto expected = 3;
    ASSERT_EQ(stat.result, expected);
  }
}

TEST(EagerPropagationStaticSegmentTree) {
  auto segment_tree =
      EagerPropagationStaticSegmentTree<Operation<operations::SetAddOp>,
                                        Statistics<statistics::Minimum>>(3);
  OnlyApplyAtIndex(segment_tree);
}

TEST(LazyPropagationStaticSegmentTree) {
  auto segment_tree =
      LazyPropagationStaticSegmentTree<Operation<operations::SetAddOp>,
                                       Statistics<statistics::Minimum>>(3);
  OnlyApplyAtIndex(segment_tree);
}

TEST(LazyPropagationDynamicSegmentTree) {
  auto segment_tree =
      LazyPropagationDynamicSegmentTree<Operation<operations::SetAddOp>,
                                        Statistics<statistics::Minimum>>(0, 2);
  OnlyApplyAtIndex(segment_tree);
}

TEST(LazyPropagationStaticSegmentTreeWithRange) {
  auto segment_tree =
      LazyPropagationStaticSegmentTree<Operation<operations::SetAddOp>,
                                       Statistics<statistics::Minimum>>(3);
  WithApplyOnRange(segment_tree);
}

TEST(LazyPropagationDynamicSegmentTreeWithRange) {
  auto segment_tree =
      LazyPropagationDynamicSegmentTree<Operation<operations::SetAddOp>,
                                        Statistics<statistics::Minimum>>(0, 2);
  WithApplyOnRange(segment_tree);
}

RUN_ALL_TESTS()
