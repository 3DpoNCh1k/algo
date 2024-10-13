#pragma once

#include <type_traits>
#include <vector>
#include <algo/utils/bits.hpp>
#include "algo/utils/traits/traits.hpp"

namespace algo::trees::segment_tree::details {

template <typename Node>
struct StaticTree {
  using DataNode = Node;
  using Index = typename DataNode::Index;
  using Value = typename DataNode::Value;
  struct TreeNode : DataNode {
    TreeNode(int index, int l, int r, Value value)
        : DataNode(l, r, value),
          index(index) {
    }

    int index = -1;
  };

  std::vector<TreeNode> nodes;
  int B = -1;
  int ROOT = -1;

  template <typename T,
            typename = std::enable_if_t<utils::traits::is_subscriptable_v<T>>>
  explicit StaticTree(T values) {
    if (values.size() == 0) {
      return;
    }

    B = utils::bits::PowerOfTwoThatAtLeast(u64(values.size()));
    ROOT = 1;

    nodes.resize(2 * B, TreeNode(-1, -1, -1, values[0]));

    for (int idx = 0; idx < B; ++idx) {
      int i = idx + B;
      nodes[i] =
          TreeNode(i, idx, idx, idx < values.size() ? values[idx] : values[0]);
    }

    Pull();
  }

  template <typename T>
  explicit StaticTree(int n, T value) {
    B = utils::bits::PowerOfTwoThatAtLeast(u64(n));
    ROOT = 1;

    nodes.resize(2 * B, TreeNode(-1, -1, -1, value));

    for (int idx = 0; idx < B; ++idx) {
      int i = idx + B;
      nodes[i] = TreeNode(i, idx, idx, value);
    }

    Pull();
  }

  void Pull() {
    for (int i = B - 1; i >= ROOT; --i) {
      auto left = 2 * i;
      auto right = left + 1;
      nodes[i].index = i;
      nodes[i].range.l = nodes[left].range.l;
      nodes[i].range.r = nodes[right].range.r;
      nodes[i].Pull(nodes[left], nodes[right]);
    }
  }

  DataNode& GetRoot() {
    return nodes[ROOT];
  }

  DataNode& GetLeft(const DataNode& node) {
    const TreeNode& internal_node = static_cast<const TreeNode&>(node);
    int left_index = 2 * internal_node.index;
    return nodes[left_index];
  }

  DataNode& GetRight(const DataNode& node) {
    const TreeNode& internal_node = static_cast<const TreeNode&>(node);
    int right_index = 2 * internal_node.index + 1;
    return nodes[right_index];
  }

  DataNode& GetNodeAt(int range_index) {
    return nodes[range_index + B];
  }

  DataNode& GetParent(const DataNode& node) {
    const TreeNode& internal_node = static_cast<const TreeNode&>(node);
    int parent_index = internal_node.index / 2;
    return nodes[parent_index];
  }

  bool HasParent(const DataNode& node) {
    const TreeNode& internal_node = static_cast<const TreeNode&>(node);
    int parent_index = internal_node.index / 2;
    return parent_index >= ROOT;
  }
};

}  // namespace algo::trees::segment_tree::details
