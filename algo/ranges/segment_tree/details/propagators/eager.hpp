#pragma once

namespace algo::ranges::segment_tree::details {

template <typename Tree>
struct EagerPropagator {
  using Node = typename Tree::DataNode;
  using Update = typename Node::Update;
  using Index = typename Node::Index;
  using Range = typename Node::Range;

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
  typename Stats::Value GetAtIndex(Index idx) {
    return tree.GetNodeAt(idx).template Get<Stats>();
  }

  template <typename Stats>
  typename Stats::Value GetFromRange(Range range) {
    return GetFromRangeTopDown<Stats>(range);
  }

  template <typename Stats>
  typename Stats::Value GetFromRangeTopDown(Range range) {
    return GetFromRangeTopDownImpl<Stats>(tree.GetRoot(), range);
  }

  template <typename Stats>
  typename Stats::Value GetFromRangeTopDownImpl(Node& node, Range range) {
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

}  // namespace algo::ranges::segment_tree::details
