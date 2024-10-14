
#include <algo/ranges/range.hpp>
#include <algo/ranges/updates/add.hpp>
#include <algo/ranges/updates/set.hpp>

#include <algo/ranges/statistics/value_of.hpp>
#include <algo/ranges/statistics/sum.hpp>

#include "algo/ranges/statistics/minimum.hpp"
#include "algo/debug/debug.hpp"
#include "tests/framework/asserts.hpp"
#include "tests/framework/test.hpp"

using namespace algo::ranges;
using namespace algo::ranges::updates;
using namespace algo::ranges::statistics;

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
    auto result = add_2.Apply(ValueOf<IntSum>(1));
    ASSERT_EQ(result, 5);
  }

  {
    auto result = add_2.Apply(ValueOf<IntMinimum>(1));
    ASSERT_EQ(result, 3);
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
    auto result = set_2.Apply(ValueOf<IntSum>(1));
    ASSERT_EQ(result, 4);
  }

  {
    auto result = set_2.Apply(ValueOf<IntMinimum>(1));
    ASSERT_EQ(result, 2);
  }
}

RUN_ALL_TESTS()
