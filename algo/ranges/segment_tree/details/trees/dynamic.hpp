#pragma once

#include <functional>
#include <type_traits>
#include <vector>
#include <cassert>

#include <algo/utils/types/fundamentals.hpp>
#include <algo/utils/traits/traits.hpp>

namespace algo::ranges::segment_tree::details {

template <typename Node>
struct DynamicTree {
  using DataNode = Node;
  using Index = typename DataNode::Index;
  using Value = typename DataNode::Value;

  struct TreeNode : DataNode {
    TreeNode(int idx, int parent_idx, Index l, Index r, Value value)
        : DataNode(l, r, value),
          index(idx),
          parent_index(parent_idx) {
    }

    int index = -1;
    int left_index = -1;
    int right_index = -1;
    int parent_index = -1;
  };

  std::vector<TreeNode> nodes;
  int ROOT = -1;
  std::function<Value(Index, Index)> initializer;

  static constexpr std::size_t DefaultMaxSize = 1e6;
  // TODO: use allocator instead of reserve

  template <typename Initializer,
            typename = std::enable_if_t<
                std::is_invocable_r_v<Value, Initializer, Index, Index>>>
  explicit DynamicTree(Index l, Index r, Initializer f,
                       std::size_t max_size = DefaultMaxSize)
      : initializer(f) {
    nodes.reserve(max_size);
    ROOT = CreateNode(-1, l, r);
  }

  explicit DynamicTree(Index l, Index r, Value value,
                       std::size_t max_size = DefaultMaxSize)
      : initializer([value](Index, Index) {
          return value;
        }) {
    nodes.reserve(max_size);
    ROOT = CreateNode(-1, l, r);
  }

  int CreateNode(int parent_index, Index l, Index r) {
    assert(nodes.size() < nodes.capacity());
    int index = nodes.size();
    nodes.emplace_back(index, parent_index, l, r, initializer(l, r));
    return index;
  }

  void EnsureThatChildsExist(TreeNode& node) {
    Index m = node.range.l + (node.range.r - node.range.l) / 2;
    if (node.left_index == -1) {
      node.left_index = CreateNode(node.index, node.range.l, m);
    }
    if (node.right_index == -1) {
      node.right_index = CreateNode(node.index, m + 1, node.range.r);
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

  DataNode& GetNodeAt(Index range_index) {
    int current_index = ROOT;
    while (true) {
      TreeNode& node = nodes[current_index];
      if (node.range.l == range_index && node.range.r == range_index) {
        return node;
      }
      EnsureThatChildsExist(node);
      TreeNode& left = nodes[node.left_index];
      assert(left.range.l <= range_index);
      if (left.range.r >= range_index) {
        current_index = node.left_index;
        continue;
      }
      TreeNode& right = nodes[node.right_index];
      assert(right.range.l <= range_index);
      assert(right.range.r >= range_index);
      current_index = node.right_index;
    }
  }

  DataNode& GetParent(const DataNode& node) {
    const TreeNode& internal_node = static_cast<const TreeNode&>(node);
    return nodes[internal_node.parent_index];
  }

  bool HasParent(const DataNode& node) {
    const TreeNode& internal_node = static_cast<const TreeNode&>(node);
    return internal_node.parent_index != -1;
  }
};
}  // namespace algo::ranges::segment_tree::details
