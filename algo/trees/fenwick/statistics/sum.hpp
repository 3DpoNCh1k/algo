#pragma once

#include <algo/trees/fenwick/statistics/base.hpp>
#include <algo/trees/fenwick/operations/add.hpp>
#include <algo/utils/types/fundamentals.hpp>
namespace algo::trees::fenwick::statistics {

struct Sum : Base {
  i64 result = 0;

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
  return new_stat;
};

}  // namespace algo::trees::fenwick::statistics
