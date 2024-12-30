#pragma once

#include <algo/ranges/range.hpp>
#include <algo/ranges/updates/add.hpp>
#include <algo/ranges/updates/set.hpp>
#include <algo/ranges/updates/set_add.hpp>

#include <algo/ranges/statistics/minimum.hpp>
#include <algo/ranges/segment_tree/trees.hpp>

#include <tests/framework/asserts.hpp>

using algo::ranges::statistics::IntMinimum;
using algo::ranges::updates::IntAdd;
using algo::ranges::updates::IntSet;

namespace unit::min {

template <typename SegmentTree>
void OnlyApplyAtIndex(SegmentTree segment_tree) {
  // Starts with [0, 0, 0]
  segment_tree.ApplyAtIndex(IntSet(0, -3));
  segment_tree.ApplyAtIndex(IntSet(1, -2));
  segment_tree.ApplyAtIndex(IntAdd(2, -1));

  segment_tree.ApplyAtIndex(IntAdd(0, 1));
  segment_tree.ApplyAtIndex(IntSet(1, 2));
  segment_tree.ApplyAtIndex(IntSet(2, 3));

  {
    auto value = segment_tree.template GetAtIndex<IntMinimum>(0);
    auto expected = -2;
    ASSERT_EQ(value, expected);
  }
  {
    auto value = segment_tree.template GetAtIndex<IntMinimum>(1);
    auto expected = 2;
    ASSERT_EQ(value, expected);
  }
  {
    auto value = segment_tree.template GetAtIndex<IntMinimum>(2);
    auto expected = 3;
    ASSERT_EQ(value, expected);
  }

  {
    auto value = segment_tree.template GetFromRange<IntMinimum>(0, 2);
    auto expected = -2;
    ASSERT_EQ(value, expected);
  }

  {
    auto value = segment_tree.template GetFromRange<IntMinimum>(
        algo::ranges::Range(1, 2));
    auto expected = 2;
    ASSERT_EQ(value, expected);
  }
}

template <typename SegmentTree>
void WithApplyOnRange(SegmentTree segment_tree) {
  // Starts with [0, 0, 0]
  segment_tree.ApplyAtIndex(IntAdd(0, 1));
  {
    auto value = segment_tree.template GetAtIndex<IntMinimum>(0);
    auto expected = 1;
    ASSERT_EQ(value, expected);
  }
  segment_tree.ApplyOnRange(IntAdd(1, 2, 2));
  {
    auto value = segment_tree.template GetFromRange<IntMinimum>(1, 2);
    auto expected = 2;
    ASSERT_EQ(value, expected);
  }

  {
    auto value = segment_tree.template GetFromRange<IntMinimum>(
        algo::ranges::Range(0, 2));
    auto expected = 1;
    ASSERT_EQ(value, expected);
  }

  segment_tree.ApplyOnRange(IntSet(algo::ranges::Range(0, 1), 3));

  {
    auto value = segment_tree.template GetFromRange<IntMinimum>(
        algo::ranges::Range(0, 2));
    auto expected = 2;
    ASSERT_EQ(value, expected);
  }
}
}  // namespace unit::min
