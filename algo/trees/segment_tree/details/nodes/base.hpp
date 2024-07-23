#pragma once

#include <sstream>
#include <tuple>

#include <algo/utils/meta.hpp>

namespace algo::trees::segment_tree::details {

template <typename Op, typename Stats>
struct BaseNode {
  using Operation = Op;
  using StatisticsTuple = Stats;
  StatisticsTuple statistics;

  int L = -1;
  int R = -1;

  bool IsOutside(int l, int r) const {
    return L > r || R < l;
  }

  bool IsInside(int l, int r) const {
    return l <= L && R <= r;
  }

  void SetInterval(int l, int r) {
    L = l;
    R = r;
    utils::meta::ForLoop<0, std::tuple_size_v<StatisticsTuple> - 1>(
        [&](auto index_number) {
          auto& stat = std::get<index_number.Value>(statistics);
          stat.L = L;
          stat.R = R;
        });
  };

  void ApplyOperation(const Operation& op) {
    utils::meta::ForLoop<0, std::tuple_size_v<StatisticsTuple> - 1>(
        [&](auto index_number) {
          auto& stat = std::get<index_number.Value>(statistics);
          stat = UpdateStatistics(stat, op);
        });
  }

  void Pull(const BaseNode& left, const BaseNode& right) {
    utils::meta::ForLoop<0, std::tuple_size_v<StatisticsTuple> - 1>(
        [&](auto index_number) {
          auto& stat = std::get<index_number.Value>(statistics);
          const auto& left_stat = std::get<index_number.Value>(left.statistics);
          const auto& right_stat =
              std::get<index_number.Value>(right.statistics);
          stat = left_stat.Merge(right_stat);
          stat.L = L;
          stat.R = R;
        });
  };

  template <typename Statistics>
  Statistics Get() const {
    return std::get<Statistics>(statistics);
  }

  std::string ToString() const {
    std::stringstream ss;
    ss << "Node:" << std::endl;
    ss << "L = " << L << " R = " << R << std::endl;
    return ss.str();
  };
};
}  // namespace algo::trees::segment_tree::details
