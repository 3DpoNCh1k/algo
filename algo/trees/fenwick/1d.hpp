#pragma once

#include <cassert>
#include <vector>
#include <algo/utils/bits.hpp>

namespace algo::trees::fenwick {

template <typename Statistics>
struct Fenwick {
  using Group = typename Statistics::Group;
  using Value = typename Statistics::Value;

  static_assert(Group::IsAbelian);

  int n;
  std::vector<Value> nodes;

  explicit Fenwick(int n)
      : n(n),
        nodes(n, Group::Identity()) {
  }

  void Set(int index, Value value) {
    auto node_index = index + 1;

    auto prev_value = Get(index);

    auto diff_value = Group::Combine(Group::Inverse(prev_value), value);

    while (node_index <= n) {
      nodes[node_index - 1] = Group::Combine(nodes[node_index - 1], diff_value);
      node_index += utils::bits::LeastSignificantBitOnly(u64(node_index));
    }
  }

  auto Get(int index) {
    return GetFromRange(index, index);
  }

  auto GetFromRange(int l, int r) {
    auto plus = GetFromPrefix(r);
    auto minus = Group::Inverse(GetFromPrefix(l - 1));
    return Group::Combine(plus, minus);
  }

  auto GetFromPrefix(int r) {
    auto result = Group::Identity();
    auto node_index = r + 1;
    while (node_index > 0) {
      result = Group::Combine(result, nodes[node_index - 1]);
      node_index ^= utils::bits::LeastSignificantBitOnly(u64(node_index));
    }
    return result;
  }
};
}  // namespace algo::trees::fenwick
