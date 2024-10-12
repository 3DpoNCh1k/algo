#pragma once

#include <sstream>
#include <tuple>

#include <algo/utils/meta.hpp>

#include <algo/ranges/range.hpp>
#include "algo/utils/debug.hpp"

namespace algo::trees::segment_tree::details {

template <typename Op, typename... Statistics>
struct BaseNode {
  using Update = Op;
  using StatisticsTuple = std::tuple<Statistics...>;
  ranges::IntRange range;
  StatisticsTuple statistics;

  BaseNode(int l, int r)
      : range(l, r),
        statistics(Statistics(range)...) {
  }

  void ApplyOperation(const Update& update) {
    dbg("BaseNode.ApplyOperation", range, update.range, update.add);
    assert(range == update.range);

    utils::meta::ForLoop<0, std::tuple_size_v<StatisticsTuple> - 1>(
        [&](auto index) {
          auto& stat = std::get<index.Value>(statistics);
          stat = update.Apply(stat);
        });
  }

  void Pull(const BaseNode& left, const BaseNode& right) {
    utils::meta::ForLoop<0, std::tuple_size_v<StatisticsTuple> - 1>(
        [&](auto index) {
          using Stats = std::tuple_element_t<index.Value, StatisticsTuple>;
          using Monoid = typename Stats::Monoid;

          auto& stat = std::get<index.Value>(statistics);
          stat.value = Monoid::Combine(left.Get<Stats>(), right.Get<Stats>());
        });
  };

  template <typename Stats>
  auto Get() const {
    return std::get<Stats>(statistics).value;
  }

  std::string ToString() const {
    std::stringstream ss;
    ss << "Node:" << std::endl;
    ss << range.ToString() << std::endl;
    return ss.str();
  };
};
}  // namespace algo::trees::segment_tree::details
