
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

TEST(Range) {
  auto range0_1 = Range(0, 1);
  auto range1_2 = Range(1, 2);
  auto range0_2 = Range(0, 2);

  ASSERT_TRUE(range0_1.IsInside(range0_2));
  ASSERT_TRUE(range1_2.IsInside(range0_2))
  ASSERT_FALSE(range0_1.IsOutside(range0_2));
  ASSERT_FALSE(range1_2.IsOutside(range0_2))

  auto range2_3 = Range(2, 3);
  ASSERT_FALSE(range0_1.IsInside(range2_3));
  ASSERT_TRUE(range0_1.IsOutside(range2_3));

  ASSERT_FALSE(range1_2.IsInside(range2_3));
  ASSERT_FALSE(range1_2.IsOutside(range2_3));
}

TEST(Add) {
  auto range = Range(0, 1);
  auto add_1 = Add(range, 1);
  auto add_2 = Add(range, 2);

  {
    auto result = add_1.Compose(add_2);
    ASSERT_EQ(result.add, 3);
  }

  {
    auto sum_stat = IntSum(range, 1);
    auto result = add_2.Apply(sum_stat);
    ASSERT_EQ(result.value, 5);
  }

  {
    auto min_stat = IntMinimum(range, 1);
    auto result = add_2.Apply(min_stat);
    ASSERT_EQ(result.value, 3);
  }
}

TEST(Set) {
  auto range = Range(0, 1);
  auto set_1 = Set(range, 1);
  auto set_2 = Set(range, 2);

  {
    auto result = set_1.Compose(set_2);
    ASSERT_EQ(result.value, 2);
  }

  {
    auto sum_stat = IntSum(range, 1);
    auto result = set_2.Apply(sum_stat);
    ASSERT_EQ(result.value, 4);
  }

  {
    auto min_stat = IntMinimum(range, 1);
    auto result = set_2.Apply(min_stat);
    ASSERT_EQ(result.value, 2);
  }
}

RUN_ALL_TESTS()
