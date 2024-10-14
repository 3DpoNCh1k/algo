
#include <algo/ranges/range.hpp>
#include <algo/ranges/updates/add.hpp>
#include <algo/ranges/updates/set.hpp>

#include <algo/ranges/statistics/sum.hpp>
#include "algo/ranges/statistics/minimum.hpp"

#include "algo/utils/debug.hpp"
#include "tests/framework/asserts.hpp"
#include "tests/framework/test.hpp"

using namespace algo::ranges;
using namespace algo::ranges::updates;
using namespace algo::ranges::statistics;

TEST(IntSum) {
  auto value = IntSum::Monoid::Combine(1, 2);
  ASSERT_EQ(value, 3);
}

TEST(IntMinimum) {
  auto value = IntMinimum::Monoid::Combine(1, 2);
  ASSERT_EQ(value, 1);
}

RUN_ALL_TESTS()
