#pragma once

#include "algo/trees/fenwick/statistics/base.hpp"
#include "algo/trees/fenwick/operations/add.hpp"
#include "algo/utils/types/fundamentals.hpp"
namespace algo::trees::fenwick::statistics {

struct Sum : Base {
  i64 result = 0;
  // using Statistics = Sum;

  Sum Merge(const Sum& that) const {
    auto result = *this;
    result.result += that.result;
    return result;
  };

  Sum Inverse() const {
    return Sum{L, R, -result};
  }
};

Sum UpdateStatistics(const Sum& stat, const operations::AddOp& op) {
  auto new_stat = stat;
  new_stat.result += (new_stat.R - new_stat.L + 1) * op.add;
  // dbg("UpdateStatistics", stat.L, stat.R, op.add);
  // dbg("UpdateStatistics", stat.result, new_stat.result);
  return new_stat;
};

}  // namespace algo::trees::fenwick::statistics
