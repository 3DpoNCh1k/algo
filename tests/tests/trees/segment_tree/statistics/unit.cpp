
#include <algo/ranges/range.hpp>
#include <algo/trees/segment_tree/updates/add.hpp>
#include <algo/trees/segment_tree/updates/set.hpp>

#include <algo/trees/segment_tree/statistics/sum.hpp>
#include "algo/trees/segment_tree/statistics/minimum.hpp"

#include "algo/utils/debug.hpp"
#include "tests/framework/asserts.hpp"
#include "tests/framework/test.hpp"

using namespace algo::ranges;
using namespace algo::trees::segment_tree::updates;
using namespace algo::trees::segment_tree::statistics;

TEST(IntSum) {
  auto stat01 = IntSum(Range(0, 1));
  auto stat0 = IntSum(Range(0, 0), 1);
  auto stat1 = IntSum(Range(1, 1), 2);
  stat01.value = IntSum::Monoid::Combine(stat0.value, stat1.value);
  ASSERT_EQ(stat01.value, 3);
}

TEST(IntMinimum) {
  auto stat01 = IntMinimum(Range(0, 1));
  auto stat0 = IntMinimum(Range(0, 0), 1);
  auto stat1 = IntMinimum(Range(1, 1), 2);
  stat01.value = IntMinimum::Monoid::Combine(stat0.value, stat1.value);
  ASSERT_EQ(stat01.value, 1);
}

RUN_ALL_TESTS()
