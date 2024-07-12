
#pragma once

#include <vector>
#include <algo/utils/debug.hpp>
namespace algo::trees::fenwick::statistics {

template <typename S, typename Stats>
struct StatisticsFromRange {
  using Statistics = S;
  int l;
  int r;
  Stats stat;
  StatisticsFromRange(int l, int r, Stats s)
      : l(l),
        r(r),
        stat(s) {
  }
};

template <typename Stats>
struct Get {
  using Statistics = Stats;

  auto From(int l, int r) {
    return StatisticsFromRange<Statistics, Statistics>(l, r, Statistics{});
  }

  template <typename... Args>
  auto From(int l, int r, Args... rest) {
    auto s = From(rest...);
    return StatisticsFromRange<Statistics, decltype(s)>(l, r, s);
  }

  auto At(int index) {
    return StatisticsFromRange<Statistics, Statistics>(index, index,
                                                       Statistics{});
  }

  template <typename... Args>
  auto At(int index, Args... rest) {
    auto s = At(rest...);
    return StatisticsFromRange<Statistics, decltype(s)>(index, index, s);
  }
};
}  // namespace algo::trees::fenwick::statistics
