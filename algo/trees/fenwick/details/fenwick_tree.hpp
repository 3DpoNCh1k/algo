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
    auto R = index_op.index + 1;
    auto Len = utils::bits::LeastSignificantBitOnly(u64(R));
    while (R <= n) {
      assert(R % Len == 0);
      assert(R >= Len);
      if ((R / Len) % 2 == 1) {
        nodes[R - 1].Apply(index_op.operation);
        R += Len;
      }
      Len *= 2;
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
    auto length_left = node_index;
    auto prev_node_index = 0;
    while (length_left > 0) {
      auto longest_interval =
          utils::bits::MostSignificantBitOnly(u64(length_left));
      assert(longest_interval > 0);
      prev_node_index += longest_interval;
      length_left -= longest_interval;
      auto node_result = nodes[prev_node_index - 1].Get(stat);
      result = result.Merge(node_result);
    }
    return result;
  }

  template <typename StatisticsFromRange>
  auto Get(StatisticsFromRange range) {
    return GetFromRange(range);
  }
};
}  // namespace algo::trees::fenwick::details
