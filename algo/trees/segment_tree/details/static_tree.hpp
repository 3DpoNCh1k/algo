#pragma once

#include <vector>

#include <algo/trees/segment_tree/details/node.hpp>

namespace algo::trees::segment_tree::details {

template <typename Operation, typename Value>
struct StaticTree {
  using DataNode = Node<Operation, Value>;
  struct TreeNode : DataNode {
    int index = -1;
    void SetIndex(int idx) {
      index = idx;
    }
  };

  std::vector<TreeNode> nodes;
  int B = -1;
  int ROOT = -1;
  explicit StaticTree(int n) {
    B = 1;
    while (B < n) {
      B <<= 1;
    }
    ROOT = 1;

    nodes.resize(2 * B);

    for (int i = B; i < 2 * B; ++i) {
      int idx = i - B;
      nodes[i].SetInterval(idx, idx);
      nodes[i].SetIndex(i);
    }
    for (int i = B - 1; i >= ROOT; --i) {
      auto left = 2 * i;
      auto right = left + 1;
      nodes[i].SetInterval(nodes[left].L, nodes[right].R);
      nodes[i].SetIndex(i);
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
};

}  // namespace algo::trees::segment_tree
