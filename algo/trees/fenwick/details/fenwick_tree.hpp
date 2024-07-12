#pragma once

#include <cassert>
#include <utility>
#include "algo/trees/fenwick/details/node.hpp"
#include "algo/trees/fenwick/operations/operation.hpp"
#include <algo/utils/bits.hpp>

namespace algo::trees::fenwick::details {

template <typename OperationAtIndex, typename StatisticsTuple>
struct FenwickTreeImpl {
  using DataNode = Node<StatisticsTuple>;
  FenwickTreeImpl() = delete;
  int n;
  std::vector<DataNode> nodes;
  explicit FenwickTreeImpl(int n)
      : n(n),
        nodes(n) {
  }

  void Apply(const OperationAtIndex& index_op) {
    // auto node_index = index_op.index + 1;
    // while (node_index <= n) {
    //   nodes[node_index - 1].Apply(index_op.operation);
    //   if (utils::bits::IsPowerOfTwo(u64(node_index))) {
    //     node_index *= 2;
    //     continue;
    //   }
    //   auto longest_interval_before =
    //       utils::bits::MostSignificantBitOnly(u64(node_index - 1));
    //   auto index_of_longest_interval = longest_interval_before;
    //   node_index = index_of_longest_interval + longest_interval_before;
    // }
    auto R = index_op.index + 1;
    auto Len = utils::bits::LeastSignificantBitOnly(u64(R));
    while (R <= n) {
      assert(R % Len == 0);
      assert(R >= Len);
      if ((R / Len) % 2 == 1) {
        dbg("Apply", R, Len);
        nodes[R - 1].Apply(index_op.operation);
        R += Len;
      }
      Len *= 2;
    }
  }

  template <typename StatisticsFromRange>
  auto GetFromRange(const StatisticsFromRange& range) {
    auto result_r =
        GetFromPrefix<typename StatisticsFromRange::Statistics>(range.r);
    auto result_l =
        GetFromPrefix<typename StatisticsFromRange::Statistics>(range.l - 1);
    return result_r.Merge(result_l.Inverse());
  }

  template <typename Statistics>
  auto GetFromPrefix(int index) {
    auto result = Statistics{};
    auto node_index = index + 1;
    auto length_left = node_index;
    auto prev_node_index = 0;
    while (length_left > 0) {
      auto longest_interval =
          utils::bits::MostSignificantBitOnly(u64(length_left));
      assert(longest_interval > 0);
      prev_node_index += longest_interval;
      length_left -= longest_interval;
      auto node_result = nodes[prev_node_index - 1].template Get<Statistics>();
      result = result.Merge(node_result);
    }
    return result;
  }
};
}  // namespace algo::trees::fenwick::details
