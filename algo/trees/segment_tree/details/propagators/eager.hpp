#pragma once

#include "algo/ranges/range.hpp"
namespace algo::trees::segment_tree::details {

template <typename Tree>
struct EagerPropagator {
  using Node = typename Tree::DataNode;
  using Operation = typename Node::Operation;

  Tree& tree;
  explicit EagerPropagator(Tree& tree)
      : tree(tree) {
  }

  void ApplyAtIndex(const Operation& op) {
    Node* current_node = &tree.GetNodeAt(op.range.l);
    current_node->ApplyOperation(op);
    while (tree.HasParent(*current_node)) {
      current_node = &tree.GetParent(*current_node);
      current_node->Pull(tree.GetLeft(*current_node),
                         tree.GetRight(*current_node));
    }
  }

  template <typename Statistics>
  Statistics GetAtIndex(int idx) {
    return Statistics(ranges::IntRange(idx, idx),
                      tree.GetNodeAt(idx).template Get<Statistics>());
  }

  template <typename Statistics>
  Statistics GetFromRange(ranges::IntRange range) {
    return Statistics(range, GetFromRangeTopDown<Statistics>(range));
  }

  template <typename Statistics>
  auto GetFromRangeTopDown(ranges::IntRange range) {
    return GetFromRangeTopDownImpl<Statistics>(tree.GetRoot(), range);
  }

  template <typename Statistics>
  auto GetFromRangeTopDownImpl(Node& node, ranges::IntRange range) {
    using Monoid = typename Statistics::Monoid;
    if (node.range.IsOutside(range)) {
      return Monoid::Identity();
    }
    if (node.range.IsInside(range)) {
      return node.template Get<Statistics>();
    }

    return Monoid::Combine(
        GetFromRangeTopDownImpl<Statistics>(tree.GetLeft(node), range),
        GetFromRangeTopDownImpl<Statistics>(tree.GetRight(node), range));
  }
};

}  // namespace algo::trees::segment_tree::details
