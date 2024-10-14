#include <algo/trees/fenwick/2d.hpp>
#include <algo/trees/segment_tree/statistics/sum.hpp>

#include <tests/framework/asserts.hpp>
#include "algo/utils/debug.hpp"
#include "tests/framework/test.hpp"

using namespace algo::trees::fenwick;
using namespace algo::trees::segment_tree::statistics;

TEST(Simple) {
  auto fenwick = Fenwick2D<IntSum>(5, 5);
  fenwick.Set(0, 0, 1);
  {
    auto res = fenwick.Get(0, 0);
    dbg(res);
    ASSERT_EQ(res, 1);
  }

  {
    auto res = fenwick.Get(1, 3);
    dbg(res);
  }

  fenwick.Set(1, 3, 2);
  {
    auto res = fenwick.Get(1, 3);
    dbg(res);
    ASSERT_EQ(res, 2);
  }

  {
    auto res = fenwick.GetFromRectangle(0, 4, 0, 4);
    ASSERT_EQ(res, 3);
  }
};

RUN_ALL_TESTS()
