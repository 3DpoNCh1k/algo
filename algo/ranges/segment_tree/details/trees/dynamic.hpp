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
    TreeNode(Index idx, Index l, Index r, Value value)
        : DataNode(l, r, value),
          index(idx) {
    }

    Index index = -1;
    Index left_index = -1;
    Index right_index = -1;
  };

  std::vector<TreeNode> nodes;
  Index ROOT = -1;
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
    ROOT = CreateNode(l, r);
  }

  explicit DynamicTree(Index l, Index r, Value value,
                       std::size_t max_size = DefaultMaxSize)
      : initializer([value](Index, Index) {
          return value;
        }) {
    nodes.reserve(max_size);
    ROOT = CreateNode(l, r);
  }

  Index CreateNode(Index l, Index r) {
    assert(nodes.size() < nodes.capacity());
    Index index = nodes.size();
    nodes.emplace_back(index, l, r, initializer(l, r));
    return index;
  }

  void EnsureThatChildsExist(TreeNode& node) {
    Index m = node.range.l + (node.range.r - node.range.l) / 2;
    if (node.left_index == -1) {
      node.left_index = CreateNode(node.range.l, m);
    }
    if (node.right_index == -1) {
      node.right_index = CreateNode(m + 1, node.range.r);
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
}  // namespace algo::ranges::segment_tree::details
