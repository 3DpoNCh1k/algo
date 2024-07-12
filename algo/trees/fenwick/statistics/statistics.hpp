
#pragma once

#include <vector>
#include <algo/utils/debug.hpp>
namespace algo::trees::fenwick::statistics {

template <typename Stats>
struct StatisticsFromRange {
  using Statistics = Stats;
  int l;
  int r;
  StatisticsFromRange(int l, int r)
      : l(l),
        r(r) {
  }
};

template <typename Stats>
struct Get {
  using Statistics = Stats;

  auto From(int l, int r) {
    return StatisticsFromRange<Statistics>(l, r);
  }

  template <typename... Args>
  auto From(int l, int r, Args... rest) {
    return StatisticsFromRange<Statistics>(l, r, From(rest...));
  }
};
}  // namespace algo::trees::fenwick::statistics
