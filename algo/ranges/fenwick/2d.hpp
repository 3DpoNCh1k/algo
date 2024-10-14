#pragma once

#include <cassert>
#include <vector>
#include <algo/utils/bits.hpp>

namespace algo::ranges::fenwick {

template <typename Statistics>
struct Fenwick2D {
  using Group = typename Statistics::Group;
  using Value = typename Statistics::Value;

  static_assert(Group::IsAbelian);

  int k_row, k_column;
  std::vector<std::vector<Value>> nodes;

  explicit Fenwick2D(int k_row, int k_column)
      : k_row(k_row),
        k_column(k_column),
        nodes(k_row, std::vector(k_column, Group::Identity())) {
  }

  void Set(int row, int col, Value value) {
    auto prev_value = Get(row, col);
    auto diff_value = Group::Combine(Group::Inverse(prev_value), value);

    auto row_node_index = row + 1;
    while (row_node_index <= k_row) {
      auto col_node_index = col + 1;
      while (col_node_index <= k_column) {
        auto& node_value = nodes[row_node_index - 1][col_node_index - 1];
        node_value = Group::Combine(node_value, diff_value);

        col_node_index +=
            utils::bits::LeastSignificantBitOnly(u64(col_node_index));
      }
      row_node_index +=
          utils::bits::LeastSignificantBitOnly(u64(row_node_index));
    }
  }

  auto Get(int row, int col) {
    return GetFromRectangle(row, row, col, col);
  }

  auto GetFromRectangle(int row_l, int row_r, int col_l, int col_r) {
    auto rr = GetFromPrefixRectangle(row_r, col_r);
    auto rl = GetFromPrefixRectangle(row_r, col_l - 1);
    auto lr = GetFromPrefixRectangle(row_l - 1, col_r);
    auto ll = GetFromPrefixRectangle(row_l - 1, col_l - 1);

    auto plus = Group::Combine(rr, ll);
    auto minus = Group::Inverse(Group::Combine(rl, lr));
    return Group::Combine(plus, minus);
  }

  auto GetFromPrefixRectangle(int row, int col) {
    auto result = Group::Identity();
    auto row_node_index = row + 1;
    while (row_node_index > 0) {
      auto col_node_index = col + 1;
      while (col_node_index > 0) {
        const auto& node_value = nodes[row_node_index - 1][col_node_index - 1];
        result = Group::Combine(result, node_value);

        col_node_index ^=
            utils::bits::LeastSignificantBitOnly(u64(col_node_index));
      }
      row_node_index ^=
          utils::bits::LeastSignificantBitOnly(u64(row_node_index));
    }
    return result;
  }
};
}  // namespace algo::ranges::fenwick
