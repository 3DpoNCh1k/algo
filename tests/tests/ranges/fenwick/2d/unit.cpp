#include <algo/ranges/fenwick/2d.hpp>
#include <algo/ranges/statistics/sum.hpp>

#include <tests/framework/asserts.hpp>
#include "algo/debug/debug.hpp"
#include "tests/framework/test.hpp"

using namespace algo::ranges::fenwick;
using namespace algo::ranges::statistics;

TEST(Simple) {
  auto fenwick = Fenwick2D<IntSum>(5, 5);
  fenwick.Set(0, 0, 1);
  {
    auto res = fenwick.Get(0, 0);
    debug(res);
    ASSERT_EQ(res, 1);
  }

  {
    auto res = fenwick.Get(1, 3);
    debug(res);
  }

  fenwick.Set(1, 3, 2);
  {
    auto res = fenwick.Get(1, 3);
    debug(res);
    ASSERT_EQ(res, 2);
  }

  {
    auto res = fenwick.GetFromRectangle(0, 4, 0, 4);
    ASSERT_EQ(res, 3);
  }
};

RUN_ALL_TESTS()
