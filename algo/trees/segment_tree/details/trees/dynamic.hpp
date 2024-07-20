#pragma once

#include <vector>
#include <cassert>

#include "algo/utils/types/fundamentals.hpp"

namespace algo::trees::segment_tree::details {

template <typename Node>
struct DynamicTree {
  using DataNode = Node;
  struct TreeNode : DataNode {
    int index = -1;
    int left_index = -1;
    int right_index = -1;
    void SetIndex(int idx) {
      index = idx;
    }
  };

  std::vector<TreeNode> nodes;
  int ROOT = -1;
  static constexpr int DefaultMaxSize = 1e6;
  // TODO: use allocator instead of reserve

  explicit DynamicTree(i64 l, i64 r, int max_size = DefaultMaxSize) {
    nodes.reserve(max_size);
    ROOT = CreateNode(l, r);
  }

  int CreateNode(int l, int r) {
    assert(nodes.size() < nodes.capacity());
    int index = nodes.size();
    nodes.emplace_back();
    TreeNode& node = nodes[index];
    node.SetInterval(l, r);
    node.SetIndex(index);
    return index;
  }

  void EnsureThatChildsExist(TreeNode& node) {
    int m = node.L + (node.R - node.L) / 2;
    if (node.left_index == -1) {
      node.left_index = CreateNode(node.L, m);
    }
    if (node.right_index == -1) {
      node.right_index = CreateNode(m + 1, node.R);
    }
  }

  DataNode& GetRoot() {
    return nodes[ROOT];
  }

  DataNode& GetLeft(DataNode& node) {
    TreeNode& internal_node = static_cast<TreeNode&>(node);
    EnsureThatChildsExist(internal_node);
    return nodes[internal_node.left_index];
  }

  DataNode& GetRight(DataNode& node) {
    TreeNode& internal_node = static_cast<TreeNode&>(node);
    EnsureThatChildsExist(internal_node);
    return nodes[internal_node.right_index];
  }
};
}  // namespace algo::trees::segment_tree::details