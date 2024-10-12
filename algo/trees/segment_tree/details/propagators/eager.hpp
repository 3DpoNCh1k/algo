#pragma once

#include "algo/ranges/range.hpp"
namespace algo::trees::segment_tree::details {

template <typename Tree>
struct EagerPropagator {
  using Node = typename Tree::DataNode;
  using Update = typename Node::Update;

  Tree& tree;
  explicit EagerPropagator(Tree& tree)
      : tree(tree) {
  }

  void ApplyAtIndex(const Update& update) {
    Node* current_node = &tree.GetNodeAt(update.range.l);
    current_node->ApplyOperation(update);
    while (tree.HasParent(*current_node)) {
      current_node = &tree.GetParent(*current_node);
      current_node->Pull(tree.GetLeft(*current_node),
                         tree.GetRight(*current_node));
    }
  }

  template <typename Stats>
  Stats GetAtIndex(int idx) {
    return Stats(ranges::IntRange(idx, idx),
                 tree.GetNodeAt(idx).template Get<Stats>());
  }

  template <typename Stats>
  Stats GetFromRange(ranges::IntRange range) {
    return Stats(range, GetFromRangeTopDown<Stats>(range));
  }

  template <typename Stats>
  auto GetFromRangeTopDown(ranges::IntRange range) {
    return GetFromRangeTopDownImpl<Stats>(tree.GetRoot(), range);
  }

  template <typename Stats>
  auto GetFromRangeTopDownImpl(Node& node, ranges::IntRange range) {
    using Monoid = typename Stats::Monoid;
    if (node.range.IsOutside(range)) {
      return Monoid::Identity();
    }
    if (node.range.IsInside(range)) {
      return node.template Get<Stats>();
    }

    return Monoid::Combine(
        GetFromRangeTopDownImpl<Stats>(tree.GetLeft(node), range),
        GetFromRangeTopDownImpl<Stats>(tree.GetRight(node), range));
  }
};

}  // namespace algo::trees::segment_tree::details
