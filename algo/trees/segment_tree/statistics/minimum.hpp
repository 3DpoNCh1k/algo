#pragma once

#include <algorithm>
#include <limits>
#include <algo/trees/segment_tree/operations/set_add.hpp>
#include <algo/trees/segment_tree/statistics/base.hpp>
#include <algo/utils/types/fundamentals.hpp>

namespace algo::trees::segment_tree::statistics {

struct Minimum : Base {
  i64 result = std::numeric_limits<i64>::max();

  Minimum Merge(const Minimum& that) const {
    auto result = *this;
    result.result = std::min(result.result, that.result);
    return result;
  };
};

Minimum UpdateStatistics(const Minimum& stat, const operations::SetAddOp& op) {
  auto new_stat = stat;
  if (op.should_set) {
    new_stat.result = op.set;
  }
  new_stat.result += op.add;
  return new_stat;
};

}  // namespace algo::trees::segment_tree::statistics
