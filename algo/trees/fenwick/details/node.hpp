#pragma once

#include <sstream>
#include <tuple>

#include <algo/utils/debug.hpp>
#include <algo/utils/meta.hpp>

namespace algo::trees::fenwick::details {

template <typename StatisticsTuple>
struct Node {
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

  template <typename OperationAtIndex>
  void Apply(const OperationAtIndex& op) {
    utils::meta::ForLoop<0, std::tuple_size_v<StatisticsTuple> - 1>(
        [&](auto index_number) {
          auto& stat = std::get<index_number.Value>(statistics);
          stat = UpdateStatistics(stat, op);
        });
  }

  template <typename Statistics>
  Statistics Get() const {
    auto& stat = std::get<Statistics>(statistics);
    dbg("Node.Get", L, R, stat.result);
    return stat;
  }

  // template <typename StatisticsFromRange>
  // typename StatisticsFromRange::Statistics GetFromRange(
  //     const StatisticsFromRange& range) {
  //   auto& stat = std::get<StatisticsFromRange::Statistics>(statistics);
  //   return stat;
  // }

  std::string ToString() const {
    std::stringstream ss;
    ss << "Node:" << std::endl;
    ss << "L = " << L << " R = " << R << std::endl;
    return ss.str();
  };
};
}  // namespace algo::trees::fenwick::details
