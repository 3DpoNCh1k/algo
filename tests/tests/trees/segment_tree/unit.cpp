
#include <algo/trees/segment_tree/operations/add.hpp>
#include <algo/trees/segment_tree/statistics/sum.hpp>
#include <algo/trees/segment_tree/trees.hpp>

#include "algo/utils/debug.hpp"
#include "tests/framework/asserts.hpp"
#include "tests/framework/test.hpp"

using namespace algo::trees::segment_tree;

template <typename SegmentTree>
void WithApplyOnRange(SegmentTree segment_tree) {
  // Starts with [0, 0, 0]
  segment_tree.ApplyAtIndex(0, operations::AddOp{1});
  {
    auto stat = segment_tree.template GetAtIndex<statistics::Sum>(0);
    auto expected = 1;
    ASSERT_EQ(stat.result, expected);
  }
  segment_tree.ApplyOnRange(1, 2, operations::AddOp{2});
  {
    auto stat = segment_tree.template GetAtIndex<statistics::Sum>(2);
    auto expected = 2;
    ASSERT_EQ(stat.result, expected);
  }
  segment_tree.ApplyOnRange(0, 1, operations::AddOp{3});

  {
    auto stat = segment_tree.template GetAtIndex<statistics::Sum>(0);
    auto expected = 4;
    ASSERT_EQ(stat.result, expected);
  }
  {
    auto stat = segment_tree.template GetAtIndex<statistics::Sum>(1);
    auto expected = 5;
    ASSERT_EQ(stat.result, expected);
  }
  {
    auto stat = segment_tree.template GetAtIndex<statistics::Sum>(2);
    auto expected = 2;
    ASSERT_EQ(stat.result, expected);
  }
}

template <typename SegmentTree>
void OnlyApplyAtIndex(SegmentTree segment_tree) {
  // Starts with [0, 0, 0]
  segment_tree.ApplyAtIndex(0, operations::AddOp{-3});
  segment_tree.ApplyAtIndex(1, operations::AddOp{-2});
  segment_tree.ApplyAtIndex(2, operations::AddOp{-1});
  segment_tree.ApplyAtIndex(2, operations::AddOp{3});
  segment_tree.ApplyAtIndex(1, operations::AddOp{2});
  segment_tree.ApplyAtIndex(0, operations::AddOp{1});
  {
    auto stat = segment_tree.template GetAtIndex<statistics::Sum>(0);
    auto expected = -2;
    ASSERT_EQ(stat.result, expected);
  }
  {
    auto stat = segment_tree.template GetAtIndex<statistics::Sum>(1);
    auto expected = 0;
    ASSERT_EQ(stat.result, expected);
  }
  {
    auto stat = segment_tree.template GetAtIndex<statistics::Sum>(2);
    auto expected = 2;
    ASSERT_EQ(stat.result, expected);
  }
}

TEST(EagerPropagationStaticSegmentTree) {
  auto segment_tree =
      EagerPropagationStaticSegmentTree<Operation<operations::AddOp>,
                                        Statistics<statistics::Sum>>(3);
  OnlyApplyAtIndex(segment_tree);
}

TEST(LazyPropagationStaticSegmentTree) {
  auto segment_tree =
      LazyPropagationStaticSegmentTree<Operation<operations::AddOp>,
                                       Statistics<statistics::Sum>>(3);
  OnlyApplyAtIndex(segment_tree);
}

TEST(LazyPropagationDynamicSegmentTree) {
  auto segment_tree =
      LazyPropagationDynamicSegmentTree<Operation<operations::AddOp>,
                                        Statistics<statistics::Sum>>(0, 2);
  OnlyApplyAtIndex(segment_tree);
}

TEST(LazyPropagationStaticSegmentTreeWithRange) {
  auto segment_tree =
      LazyPropagationStaticSegmentTree<Operation<operations::AddOp>,
                                       Statistics<statistics::Sum>>(3);
  WithApplyOnRange(segment_tree);
}

TEST(LazyPropagationDynamicSegmentTreeWithRange) {
  auto segment_tree =
      LazyPropagationDynamicSegmentTree<Operation<operations::AddOp>,
                                        Statistics<statistics::Sum>>(0, 2);
  WithApplyOnRange(segment_tree);
}

RUN_ALL_TESTS()
