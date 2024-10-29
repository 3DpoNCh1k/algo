#pragma once

#include <algo/ranges/range.hpp>
#include <algo/ranges/updates/add.hpp>
#include <algo/ranges/statistics/sum.hpp>
#include <algo/ranges/segment_tree/trees.hpp>

#include <tests/framework/asserts.hpp>

using namespace algo::ranges;
using namespace algo::ranges::updates;
using namespace algo::ranges::statistics;
using namespace algo::ranges::segment_tree;

namespace unit::sum {

template <typename SegmentTree>
void OnlyApplyAtIndex(SegmentTree segment_tree) {
  // Starts with [0, 0, 0]
  segment_tree.ApplyAtIndex(IntAdd(0, -3));
  segment_tree.ApplyAtIndex(IntAdd(1, -2));
  segment_tree.ApplyAtIndex(IntAdd(2, -1));

  segment_tree.ApplyAtIndex(IntAdd(2, 3));
  segment_tree.ApplyAtIndex(IntAdd(1, 2));
  segment_tree.ApplyAtIndex(IntAdd(0, 1));

  {
    auto value = segment_tree.template GetAtIndex<IntSum>(0);
    auto expected = -2;
    ASSERT_EQ(value, expected);
  }
  {
    auto value = segment_tree.template GetAtIndex<IntSum>(1);
    auto expected = 0;
    ASSERT_EQ(value, expected);
  }
  {
    auto value = segment_tree.template GetAtIndex<IntSum>(2);
    auto expected = 2;
    ASSERT_EQ(value, expected);
  }

  {
    auto value = segment_tree.template GetFromRange<IntSum>(0, 1);
    auto expected = -2;
    ASSERT_EQ(value, expected);
  }

  {
    auto value = segment_tree.template GetFromRange<IntSum>(1, 2);
    auto expected = 2;
    ASSERT_EQ(value, expected);
  }

  {
    auto value = segment_tree.template GetFromRange<IntSum>(0, 2);
    auto expected = 0;
    ASSERT_EQ(value, expected);
  }
}

template <typename SegmentTree>
void WithApplyOnRange(SegmentTree segment_tree) {
  // Starts with [0, 0, 0]
  segment_tree.ApplyAtIndex(IntAdd(0, 1));
  {
    auto value = segment_tree.template GetAtIndex<IntSum>(0);
    auto expected = 1;
    ASSERT_EQ(value, expected);
  }
  segment_tree.ApplyOnRange(IntAdd(1, 2, 2));
  {
    auto value = segment_tree.template GetAtIndex<IntSum>(2);
    auto expected = 2;
    ASSERT_EQ(value, expected);
  }

  {
    auto value = segment_tree.template GetFromRange<IntSum>(Range(0, 2));
    auto expected = 5;
    ASSERT_EQ(value, expected);
  }

  segment_tree.ApplyOnRange(IntAdd(Range(0, 1), 3));

  {
    auto value = segment_tree.template GetAtIndex<IntSum>(0);
    auto expected = 4;
    ASSERT_EQ(value, expected);
  }
  {
    auto value = segment_tree.template GetAtIndex<IntSum>(1);
    auto expected = 5;
    ASSERT_EQ(value, expected);
  }
  {
    auto value = segment_tree.template GetAtIndex<IntSum>(2);
    auto expected = 2;
    ASSERT_EQ(value, expected);
  }

  {
    auto value = segment_tree.template GetFromRange<IntSum>(Range(0, 1));
    auto expected = 9;
    ASSERT_EQ(value, expected);
  }

  {
    auto value = segment_tree.template GetFromRange<IntSum>(Range(1, 2));
    auto expected = 7;
    ASSERT_EQ(value, expected);
  }
}
}  // namespace unit::sum
