#include "algo/trees/fenwick/operations/add.hpp"
#include "algo/trees/fenwick/statistics/sum.hpp"

#include "algo/trees/fenwick/trees.hpp"
#include "tests/testing/asserts.hpp"

using namespace algo::trees::fenwick;
using namespace operations;
using namespace statistics;

void Test() {
  auto fenwick = Fenwick2D<Operation<AddOp>, Statistics<Sum>>(5, 5);
  {
    auto add = AddOp{1};
    fenwick.ApplyAtIndex(add, 0, 0);
  }
  {
    auto res = fenwick.GetAtIndex<Sum>(0, 0);
    ASSERT_EQ(res.result, 1);
  }

  {
    auto add = AddOp{2};
    fenwick.ApplyAtIndex(add, 1, 3);
  }
  {
    auto res = fenwick.GetAtIndex<Sum>(1, 3);
    ASSERT_EQ(res.result, 2);
  }

  {
    auto res = fenwick.GetFromRange<Sum>(0, 4, 0, 4);
    ASSERT_EQ(res.result, 3);
  }
};

int main() {
  Test();
}
