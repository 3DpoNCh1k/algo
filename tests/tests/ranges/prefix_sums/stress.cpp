#include <cstdlib>
#include <string>

#include <algo/ranges/prefix_sums.hpp>
#include <algo/utils/generators/random.hpp>
#include <tests/framework/asserts.hpp>
#include "tests/framework/test.hpp"

using namespace algo::ranges;

struct Tester {
  algo::utils::generators::RandomGenerator random;
  std::vector<int> a;
  int n;
  PrefixSums prefix_sums;
  explicit Tester(const std::vector<int>& a)
      : a(a),
        n(a.size()),
        prefix_sums(a) {
  }

  void Test(int k_queries) {
    for (int q = 0; q < k_queries; ++q) {
      int query_type = random.GetInt(1, 3);
      if (query_type == 1) {
        AskPrefix();
      } else if (query_type == 2) {
        AskSuffix();
      } else {
        AskRange();
      }
    }
  };

  void AskPrefix() {
    int p = random.GetInt(0, n - 1);
    auto result = prefix_sums.GetFromPrefix(p);
    i64 correct_result = 0;
    for (int i = 0; i <= p; ++i) {
      correct_result += a[i];
    }
    ASSERT_EQ(result, correct_result);
  }

  void AskSuffix() {
    int s = random.GetInt(0, n - 1);
    auto result = prefix_sums.GetFromSuffix(s);
    i64 correct_result = 0;
    for (int i = s; i < n; ++i) {
      correct_result += a[i];
    }
    ASSERT_EQ(result, correct_result);
  }

  void AskRange() {
    int l = random.GetInt(0, n - 1);
    int r = random.GetInt(l, n - 1);
    auto result = prefix_sums.GetFromRange(l, r);
    i64 correct_result = 0;
    for (int i = l; i <= r; ++i) {
      correct_result += a[i];
    }
    ASSERT_EQ(result, correct_result);
  }
};

void Stress(int rep, int max_n, int from, int to, int k_queries) {
  algo::utils::generators::RandomGenerator random;
  for (int r = 0; r < rep; ++r) {
    int n = random.GetInt(1, max_n);
    std::vector<int> a(n);
    for (int i = 0; i < n; ++i) {
      a[i] = random.GetInt(from, to);
    }
    Tester(a).Test(k_queries);
  }
}

TEST(StressSmall) {
  Stress(10, 100, -100, 100, 1000);
}

TEST(StressBig) {
  Stress(10, 1000, -1e9, 1e9, 1000);
}

RUN_ALL_TESTS()
