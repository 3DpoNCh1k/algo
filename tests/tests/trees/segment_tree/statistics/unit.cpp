
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
  auto value = IntSum::Monoid::Combine(1, 2);
  ASSERT_EQ(value, 3);
}

TEST(IntMinimum) {
  auto value = IntMinimum::Monoid::Combine(1, 2);
  ASSERT_EQ(value, 1);
}

RUN_ALL_TESTS()
