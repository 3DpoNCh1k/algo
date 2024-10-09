#include <algo/trees/fenwick/operations/add.hpp>
#include <algo/trees/fenwick/statistics/sum.hpp>
#include <algo/trees/fenwick/trees.hpp>
#include <algo/utils/random/random.hpp>
#include <tests/framework/asserts.hpp>
#include "tests/framework/test.hpp"

using namespace algo::trees::fenwick;
using namespace algo::utils::random;
using namespace operations;
using namespace statistics;

struct AddAndSumTester {
  int n;
  Fenwick<Operation<AddOp>, Statistics<Sum>> fenwick;
  std::vector<i64> rival;

  explicit AddAndSumTester(int n)
      : n(n),
        fenwick(Fenwick<Operation<AddOp>, Statistics<Sum>>(n)),
        rival(n) {
  }

  void Test(int queries, i64 min_add_value, i64 max_add_value) {
    for (int i = 0; i < n; ++i) {
      auto res = fenwick.GetAtIndex<Sum>(i);
      ASSERT_EQ(res.result, 0);
      ASSERT_EQ(rival[i], 0);
    }

    for (int q = 0; q < queries; ++q) {
      if (Maybe()) {
        auto index = RandomInt(0, n - 1);
        auto value = RandomInt(min_add_value, max_add_value);
        {
          auto add_operation = AddOp{value};
          fenwick.ApplyAtIndex(add_operation, index);
        }
        { rival[index] += value; }
        continue;
      }
      if (Maybe()) {
        auto index = RandomInt(0, n - 1);
        auto result = fenwick.GetAtIndex<Sum>(index);
        ASSERT_EQ(result.result, rival[index])
        continue;
      }
      auto l = RandomInt(0, n - 1);
      auto r = RandomInt(l, n - 1);
      auto result = fenwick.GetFromRange<Sum>(l, r);
      i64 rival_result = 0;
      for (int i = l; i <= r; ++i) {
        rival_result += rival[i];
      }
      ASSERT_EQ(result.result, rival_result);
    }
  }
};

TEST(StressSmall) {
  AddAndSumTester(5).Test(10, -10, 10);
}

TEST(StressMedium) {
  AddAndSumTester(333).Test(100, -1000, 10);
}

TEST(StressBig) {
  AddAndSumTester(11111).Test(1000, -1e9, 1e9);
}

RUN_ALL_TESTS()
