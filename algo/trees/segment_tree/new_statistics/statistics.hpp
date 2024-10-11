#pragma once

#include <cassert>

namespace algo::trees::segment_tree::new_statistics {

template <typename Statistics>
auto CombineStatistics(Statistics stat1, Statistics stat2) {
  using Range = typename Statistics::Range;
  using Monoid = typename Statistics::Monoid;

  assert(stat1.range.r + 1 == stat2.range.l);

  return Statistics(Range(stat1.range.l, stat2.range.r),
                    Monoid::Combine(stat1.value, stat2.value));
};

}  // namespace algo::trees::segment_tree::new_statistics
