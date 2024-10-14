#include <algo/ranges/fenwick/3d.hpp>
#include <algo/ranges/statistics/sum.hpp>

#include <tests/framework/asserts.hpp>
#include "algo/utils/debug.hpp"
#include "tests/framework/test.hpp"

using namespace algo::ranges::fenwick;
using namespace algo::ranges::statistics;

TEST(Simple) {
  auto fenwick = Fenwick3D<IntSum>(3, 3, 3);
  fenwick.Set(0, 0, 0, 1);
  {
    auto res = fenwick.Get(0, 0, 0);
    ASSERT_EQ(res, 1);
  }

  fenwick.Set(0, 1, 2, 2);

  {
    auto res = fenwick.Get(0, 1, 2);
    ASSERT_EQ(res, 2);
  }

  {
    auto res = fenwick.GetFromCube(0, 2, 0, 2, 0, 2);
    ASSERT_EQ(res, 3);
  }
};

RUN_ALL_TESTS()