
#include <algo/trees/segment_tree/updates/range.hpp>
#include <algo/trees/segment_tree/updates/add.hpp>
#include <algo/trees/segment_tree/updates/set.hpp>

#include <algo/trees/segment_tree/new_statistics/sum.hpp>
#include <algo/trees/segment_tree/new_statistics/statistics.hpp>
#include "algo/trees/segment_tree/new_statistics/minimum.hpp"

#include "algo/utils/debug.hpp"
#include "tests/framework/asserts.hpp"
#include "tests/framework/test.hpp"

using namespace algo::trees::segment_tree::range_updates;
using namespace algo::trees::segment_tree::new_statistics;

TEST(IntSum) {
  auto stat01 = IntSum(Range(0, 1));
  auto stat0 = IntSum(Range(0, 0), 1);
  auto stat1 = IntSum(Range(1, 1), 2);
  stat01.value = IntSum::Monoid::Combine(stat0.value, stat1.value);
  ASSERT_EQ(stat01.value, 3);

  auto res = CombineStatistics(stat0, stat1);
  ASSERT_EQ(res.value, 3);
  ASSERT_EQ(res.range.l, 0);
  ASSERT_EQ(res.range.r, 1);
}

TEST(IntMinimum) {
  auto stat01 = IntMinimum(Range(0, 1));
  auto stat0 = IntMinimum(Range(0, 0), 1);
  auto stat1 = IntMinimum(Range(1, 1), 2);
  stat01.value = IntMinimum::Monoid::Combine(stat0.value, stat1.value);
  ASSERT_EQ(stat01.value, 1);

  auto res = CombineStatistics(stat0, stat1);
  ASSERT_EQ(res.value, 1);
  ASSERT_EQ(res.range.l, 0);
  ASSERT_EQ(res.range.r, 1);
}

RUN_ALL_TESTS()
