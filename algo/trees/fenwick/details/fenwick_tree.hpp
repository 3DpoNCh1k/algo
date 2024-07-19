#pragma once

#include <cassert>
#include <vector>
#include <algo/utils/bits.hpp>

namespace algo::trees::fenwick::details {

template <typename Node>
struct FenwickTreeImpl {
  static constexpr int Dimension = Node::Dimension + 1;

  int n;
  std::vector<Node> nodes;

  FenwickTreeImpl() = delete;
  template <typename... Args>
  explicit FenwickTreeImpl(int n, Args... args)
      : n(n),
        nodes(n, Node(args...)) {
  }

  template <typename OperationAtIndex>
  void Apply(const OperationAtIndex& index_op) {
    auto node_index = index_op.index + 1;
    while (node_index <= n) {
      nodes[node_index - 1].Apply(index_op.operation);
      node_index += utils::bits::LeastSignificantBitOnly(u64(node_index));
    }
  }

  template <typename StatisticsFromRange>
  auto GetFromRange(const StatisticsFromRange& range) {
    auto result_r = GetFromPrefix<typename StatisticsFromRange::Statistics>(
        range.r, range.stat);
    auto result_l = GetFromPrefix<typename StatisticsFromRange::Statistics>(
        range.l - 1, range.stat);
    return result_r.Merge(result_l.Inverse());
  }

  template <typename StatisticsRes, typename Statistics>
  auto GetFromPrefix(int index, Statistics stat) {
    auto result = StatisticsRes{};
    auto node_index = index + 1;
    while (node_index > 0) {
      result = nodes[node_index - 1].Get(stat).Merge(result);
      node_index ^= utils::bits::LeastSignificantBitOnly(u64(node_index));
    }
    return result;
  }

  template <typename StatisticsFromRange>
  auto Get(StatisticsFromRange range) {
    return GetFromRange(range);
  }
};
}  // namespace algo::trees::fenwick::details
