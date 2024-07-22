#pragma once

#include <sstream>
#include <tuple>

#include <algo/utils/meta.hpp>

namespace algo::trees::fenwick::details {

template <typename OpAtIndex, typename StatisticsTuple>
struct Node {
  using OperationAtIndex = OpAtIndex;
  using Operation = typename OperationAtIndex::Operation;
  using Statistics = StatisticsTuple;
  constexpr static int Dimension = 0;

  Statistics statistics;

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

  void Apply(const Operation& op) {
    utils::meta::ForLoop<0, std::tuple_size_v<StatisticsTuple> - 1>(
        [&](auto index_number) {
          auto& stat = std::get<index_number.Value>(statistics);
          stat = UpdateStatistics(stat, op);
        });
  }

  template <typename Statistics>
  Statistics Get(Statistics) const {
    auto& stat = std::get<Statistics>(statistics);
    return stat;
  }

  std::string ToString() const {
    std::stringstream ss;
    ss << "Node:" << std::endl;
    ss << "L = " << L << " R = " << R << std::endl;
    return ss.str();
  };
};
}  // namespace algo::trees::fenwick::details
