#pragma once

#include <sstream>
#include <tuple>

#include <algo/utils/debug.hpp>
#include <algo/utils/meta.hpp>

namespace algo::trees::segment_tree::details {

template <typename Operation, typename StatisticsTuple>
struct Node {
  Operation operation;
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
    operation = CombineOperations(operation, op);
  }

  void Pull(const Node& left, const Node& right) {
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

  void Push(Node& left, Node& right) {
    left.ApplyOperation(operation);
    right.ApplyOperation(operation);
    operation = Operation{};
  };

  template <typename Statistics>
  Statistics Get() const {
    auto& stat = std::get<Statistics>(statistics);
    dbg("Node.Get", L, R, stat.result);
    return stat;
  }

  std::string ToString() const {
    std::stringstream ss;
    ss << "Node:" << std::endl;
    ss << "L = " << L << " R = " << R << std::endl;
    ss << "Operation = " << operation.ToString();
    return ss.str();
  };
};
}  // namespace algo::trees::segment_tree::details
