#include <algo/ranges/fenwick/1d.hpp>
#include <algo/ranges/statistics/sum.hpp>
#include <algo/utils/random/random.hpp>
#include <tests/framework/asserts.hpp>
#include <tests/framework/test.hpp>

using namespace algo::ranges::fenwick;
using namespace algo::ranges::statistics;
using namespace algo::utils::random;

struct AddAndSumTester {
  int n;
  Fenwick<IntSum> fenwick;
  std::vector<i64> rival;

  explicit AddAndSumTester(int n)
      : n(n),
        fenwick(n),
        rival(n) {
  }

  void Test(int queries, i64 min_add_value, i64 max_add_value) {
    for (int i = 0; i < n; ++i) {
      auto res = fenwick.Get(i);
      ASSERT_EQ(res, 0);
      ASSERT_EQ(rival[i], 0);
    }

    for (int q = 0; q < queries; ++q) {
      if (Maybe()) {
        auto index = RandomInt(0, n - 1);
        auto value = RandomInt(min_add_value, max_add_value);
        fenwick.Set(index, fenwick.Get(index) + value);
        rival[index] += value;
        continue;
      }
      if (Maybe()) {
        auto index = RandomInt(0, n - 1);
        auto result = fenwick.Get(index);
        ASSERT_EQ(result, rival[index])
        continue;
      }
      auto l = RandomInt(0, n - 1);
      auto r = RandomInt(l, n - 1);
      auto result = fenwick.GetFromRange(l, r);
      i64 rival_result = 0;
      for (int i = l; i <= r; ++i) {
        rival_result += rival[i];
      }
      ASSERT_EQ(result, rival_result);
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
