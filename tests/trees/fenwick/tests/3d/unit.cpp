#include "algo/trees/fenwick/operations/add.hpp"
#include "algo/trees/fenwick/statistics/sum.hpp"

#include "algo/trees/fenwick/trees.hpp"
#include "tests/testing/asserts.hpp"

using namespace algo::trees::fenwick;
using namespace operations;
using namespace statistics;

void Test() {
  auto fenwick = Fenwick3D<Operation<AddOp>, Statistics<Sum>>(3, 3, 3);
  {
    auto add = AddOp{1};
    fenwick.ApplyAtIndex(add, 0, 0, 0);
  }
  {
    auto res = fenwick.GetAtIndex<Sum>(0, 0, 0);
    ASSERT_EQ(res.result, 1);
  }

  {
    auto add = AddOp{2};
    fenwick.ApplyAtIndex(add, 0, 1, 2);
  }
  {
    auto res = fenwick.GetAtIndex<Sum>(0, 1, 2);
    ASSERT_EQ(res.result, 2);
  }

  {
    auto res = fenwick.GetFromRange<Sum>(0, 2, 0, 2, 0, 2);
    ASSERT_EQ(res.result, 3);
  }
};

int main() {
  Test();
}
