#include <algo/ranges/fenwick/1d.hpp>
#include <algo/ranges/statistics/sum.hpp>

#include <tests/framework/asserts.hpp>
#include "tests/framework/test.hpp"

using namespace algo::ranges::fenwick;
using namespace algo::ranges::statistics;

TEST(Simple) {
  auto fenwick = Fenwick<IntSum>(3);
  fenwick.Set(0, 1);
  {
    auto value = fenwick.Get(0);
    ASSERT_EQ(value, 1)
  }

  {
    auto value = fenwick.Get(1);
    ASSERT_EQ(value, 0)
  }

  {
    auto value = fenwick.Get(2);
    ASSERT_EQ(value, 0)
  }

  {
    auto value = fenwick.GetFromRange(0, 2);
    ASSERT_EQ(value, 1)
  }

  // add
  fenwick.Set(1, fenwick.Get(1) + 2);

  {
    auto value = fenwick.Get(0);
    ASSERT_EQ(value, 1)
  }

  {
    auto value = fenwick.Get(1);
    ASSERT_EQ(value, 2)
  }

  {
    auto value = fenwick.Get(2);
    ASSERT_EQ(value, 0)
  }

  {
    auto value = fenwick.GetFromRange(0, 2);
    ASSERT_EQ(value, 3)
  }
};

RUN_ALL_TESTS()
