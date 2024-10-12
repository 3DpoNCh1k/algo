#pragma once

#include <sstream>
#include <tuple>

#include <algo/utils/meta.hpp>

#include <algo/ranges/range.hpp>
#include "algo/utils/debug.hpp"

namespace algo::trees::segment_tree::details {

template <typename Op, typename... TStatistics>
struct BaseNode {
  using Operation = Op;
  using StatisticsTuple = std::tuple<TStatistics...>;
  ranges::IntRange range;
  StatisticsTuple statistics;

  BaseNode(int l, int r)
      : range(l, r),
        statistics(TStatistics(range)...) {
  }

  void ApplyOperation(const Operation& op) {
    dbg("BaseNode.ApplyOperation", range, op.range, op.add);
    assert(range == op.range);

    utils::meta::ForLoop<0, std::tuple_size_v<StatisticsTuple> - 1>(
        [&](auto index) {
          auto& stat = std::get<index.Value>(statistics);
          stat = op.Apply(stat);
        });
  }

  void Pull(const BaseNode& left, const BaseNode& right) {
    utils::meta::ForLoop<0, std::tuple_size_v<StatisticsTuple> - 1>(
        [&](auto index) {
          using Statistics = std::tuple_element_t<index.Value, StatisticsTuple>;
          using Monoid = typename Statistics::Monoid;

          auto& stat = std::get<index.Value>(statistics);
          stat.value =
              Monoid::Combine(left.Get<Statistics>(), right.Get<Statistics>());
        });
  };

  template <typename Statistics>
  auto Get() const {
    return std::get<Statistics>(statistics).value;
  }

  std::string ToString() const {
    std::stringstream ss;
    ss << "Node:" << std::endl;
    ss << range.ToString() << std::endl;
    return ss.str();
  };
};
}  // namespace algo::trees::segment_tree::details
