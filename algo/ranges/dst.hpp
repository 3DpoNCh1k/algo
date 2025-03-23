#pragma once

#include <vector>
#include <algo/utils/bits.hpp>
#include <cassert>

namespace algo::ranges {
template<typename Statistics>
struct DisjointSparseTable {
  using Value = typename Statistics::Value;
  explicit DisjointSparseTable(const std::vector<Value> & a) {
    int k =
        utils::bits::ExponentOfPowerOfTwoThatAtLeast(std::max(a.size(), 2ul));
    int n = 1 << k;
    dp.assign(k , std::vector<Value>(n));
    for (int i = 0; i < a.size(); ++i) {
      dp[0][i] = a[i];
    }
    for (int lvl = 0; lvl < k; ++lvl) {
      const auto & values = dp[0];
      int len = 1 << lvl;
      for (int center = len; center < n; center += 2 * len) {
        // left
        dp[lvl][center - 1] = values[center - 1];
        for (int i = center - 2; i >= center - len; --i) {
          dp[lvl][i] = Statistics::Monoid::Combine(values[i], dp[lvl][i + 1]);
        }
        // right
        dp[lvl][center] = values[center];
        for (int i = center + 1; i < center + len; ++i) {
          dp[lvl][i] = Statistics::Monoid::Combine(dp[lvl][i - 1], values[i]);
        }
      }
    }
  }

  int Get(int l, int r) {
    if (l == r) {
      return dp[0][l];
    }
    int lvl = utils::bits::IndexOfMostSignificantBit(u64(l ^ r));
    return Statistics::Monoid::Combine(dp[lvl][l], dp[lvl][r]);
  }

  std::vector<std::vector<Value>> dp;
};

template<typename Statistics>
using DST = DisjointSparseTable<Statistics>;

}  // namespace algo::ranges
