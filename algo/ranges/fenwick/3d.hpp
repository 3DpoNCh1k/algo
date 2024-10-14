#pragma once

#include <cassert>
#include <vector>
#include <algo/utils/bits.hpp>

namespace algo::ranges::fenwick {

template <typename Statistics>
struct Fenwick3D {
  using Group = typename Statistics::Group;
  using Value = typename Statistics::Value;

  static_assert(Group::IsAbelian);

  int max_x, max_y, max_z;
  std::vector<std::vector<std::vector<Value>>> nodes;

  explicit Fenwick3D(int max_x, int max_y, int max_z)
      : max_x(max_x),
        max_y(max_y),
        max_z(max_z),
        nodes(max_x,
              std::vector(max_y, std::vector(max_z, Group::Identity()))) {
  }

  void Set(int x, int y, int z, Value value) {
    auto prev_value = Get(x, y, z);
    auto diff_value = Group::Combine(Group::Inverse(prev_value), value);

    auto x_node_index = x + 1;
    while (x_node_index <= max_x) {
      auto y_node_index = y + 1;
      while (y_node_index <= max_y) {
        auto z_node_index = z + 1;
        while (z_node_index <= max_z) {
          auto& node_value =
              nodes[x_node_index - 1][y_node_index - 1][z_node_index - 1];
          node_value = Group::Combine(node_value, diff_value);

          z_node_index +=
              utils::bits::LeastSignificantBitOnly(u64(z_node_index));
        }
        y_node_index += utils::bits::LeastSignificantBitOnly(u64(y_node_index));
      }
      x_node_index += utils::bits::LeastSignificantBitOnly(u64(x_node_index));
    }
  }

  auto Get(int x, int y, int z) {
    return GetFromCube(x, x, y, y, z, z);
  }

  auto GetFromCube(int x_l, int x_r, int y_l, int y_r, int z_l, int z_r) {
    auto plus = GetFromRectanglesUpToZ(x_l, x_r, y_l, y_r, z_r);
    auto minus =
        Group::Inverse(GetFromRectanglesUpToZ(x_l, x_r, y_l, y_r, z_l - 1));

    return Group::Combine(plus, minus);
  }

  auto GetFromRectanglesUpToZ(int x_l, int x_r, int y_l, int y_r, int z) {
    auto rr = GetFromPrefixCube(x_r, y_r, z);
    auto rl = GetFromPrefixCube(x_r, y_l - 1, z);
    auto lr = GetFromPrefixCube(x_l - 1, y_r, z);
    auto ll = GetFromPrefixCube(x_l - 1, y_l - 1, z);

    auto plus = Group::Combine(rr, ll);
    auto minus = Group::Inverse(Group::Combine(rl, lr));

    return Group::Combine(plus, minus);
  }

  auto GetFromPrefixCube(int x, int y, int z) {
    auto result = Group::Identity();
    auto x_node_index = x + 1;
    while (x_node_index > 0) {
      auto y_node_index = y + 1;
      while (y_node_index > 0) {
        auto z_node_index = z + 1;
        while (z_node_index > 0) {
          const auto& node_value =
              nodes[x_node_index - 1][y_node_index - 1][z_node_index - 1];
          result = Group::Combine(result, node_value);

          z_node_index ^=
              utils::bits::LeastSignificantBitOnly(u64(z_node_index));
        }
        y_node_index ^= utils::bits::LeastSignificantBitOnly(u64(y_node_index));
      }
      x_node_index ^= utils::bits::LeastSignificantBitOnly(u64(x_node_index));
    }
    return result;
  }
};
}  // namespace algo::ranges::fenwick
