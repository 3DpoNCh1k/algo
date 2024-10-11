
#include <algo/trees/segment_tree/updates/range.hpp>
#include <algo/trees/segment_tree/updates/add.hpp>
#include <algo/trees/segment_tree/updates/set.hpp>

#include <algo/trees/segment_tree/new_statistics/sum.hpp>

#include "algo/trees/segment_tree/new_statistics/minimum.hpp"
#include "algo/utils/debug.hpp"
#include "tests/framework/asserts.hpp"
#include "tests/framework/test.hpp"

using namespace algo::trees::segment_tree::range_updates;
using namespace algo::trees::segment_tree::new_statistics;

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
  auto set_1_2 = Add(Range(1, 2), 1);
  auto set_0_3 = Add(Range(0, 3), 2);

  {
    auto result = set_1_2.Compose(set_0_3);
    ASSERT_EQ(result.add, 3);
  }

  {
    auto sum_stat = IntSum(Range(0, 1), 1);
    auto result = set_0_3.Apply(sum_stat);
    ASSERT_EQ(result.value, 5);
  }

  {
    auto min_stat = IntMinimum(Range(0, 1), 1);
    auto result = set_0_3.Apply(min_stat);
    ASSERT_EQ(result.value, 3);
  }
}

TEST(Set) {
  auto set_1_2 = Set(Range(1, 2), 1);
  auto set_0_3 = Set(Range(0, 3), 2);

  {
    auto result = set_1_2.Compose(set_0_3);
    ASSERT_EQ(result.value, 2);
  }

  {
    auto sum_stat = IntSum(Range(0, 1), 1);
    auto result = set_0_3.Apply(sum_stat);
    ASSERT_EQ(result.value, 4);
  }

  {
    auto min_stat = IntMinimum(Range(0, 1), 1);
    auto result = set_0_3.Apply(min_stat);
    ASSERT_EQ(result.value, 2);
  }
}

RUN_ALL_TESTS()
