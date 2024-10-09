#include <iostream>

#include <algo/trees/fenwick/operations/operation.hpp>
#include <algo/trees/fenwick/statistics/base.hpp>
#include <algo/trees/fenwick/statistics/statistics.hpp>
#include <tests/framework/asserts.hpp>
#include "tests/framework/test.hpp"

using namespace algo::trees::fenwick;

using std::cout;
using std::endl;

TEST(Simple) {
  double op = 0;
  int i = 1;
  int j = 2;
  {
    auto c = operations::Apply(op).At(i, j);
    cout << c.index << " " << c.operation.index << endl;
    ASSERT_EQ(c.index, i);
    ASSERT_EQ(c.operation.index, j);
  }
  {
    auto c = statistics::Get<double>().From(i, j);
    ASSERT_EQ(c.l, i);
    ASSERT_EQ(c.r, j);
  }

  {
    auto c = statistics::Get<double>().From(i, i, j, j);
    ASSERT_EQ(c.l, i);
    ASSERT_EQ(c.r, i);
    ASSERT_EQ(c.stat.l, j);
    ASSERT_EQ(c.stat.r, j);
  }

  {
    auto c = statistics::Get<double>().At(i);
    ASSERT_EQ(c.l, i);
    ASSERT_EQ(c.r, i);
  }

  {
    auto c = statistics::Get<double>().At(i, j);
    ASSERT_EQ(c.l, i);
    ASSERT_EQ(c.r, i);
    ASSERT_EQ(c.stat.l, j);
    ASSERT_EQ(c.stat.r, j);
  }
};

RUN_ALL_TESTS()