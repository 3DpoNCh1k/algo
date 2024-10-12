#pragma once

#include <vector>
#include <algo/utils/bits.hpp>

namespace algo::trees::segment_tree::details {

template <typename Node>
struct StaticTree {
  using DataNode = Node;
  struct TreeNode : DataNode {
    TreeNode(int index, int l, int r)
        : DataNode(l, r),
          index(index) {
    }

    int index = -1;
  };

  std::vector<TreeNode> nodes;
  int B = -1;
  int ROOT = -1;
  explicit StaticTree(int n) {
    B = utils::bits::PowerOfTwoThatAtLeast(u64(n));
    ROOT = 1;

    nodes.resize(2 * B, TreeNode(-1, -1, -1));

    for (int i = B; i < 2 * B; ++i) {
      int idx = i - B;
      nodes[i] = TreeNode(i, idx, idx);
    }
    for (int i = B - 1; i >= ROOT; --i) {
      auto left = 2 * i;
      auto right = left + 1;
      nodes[i] = TreeNode(i, nodes[left].range.l, nodes[right].range.r);
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
