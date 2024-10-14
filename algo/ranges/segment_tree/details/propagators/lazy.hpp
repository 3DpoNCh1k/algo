#pragma once

#include "algo/utils/debug.hpp"
namespace algo::ranges::segment_tree::details {

template <typename Tree>
struct LazyPropagator {
  using Node = typename Tree::DataNode;
  using Update = typename Node::Update;
  using Index = typename Node::Index;
  using Range = typename Node::Range;

  Tree& tree;
  explicit LazyPropagator(Tree& tree)
      : tree(tree) {
  }

  void ApplyAtIndex(const Update& update) {
    ApplyOnRange(update);
  }

  void ApplyOnRange(const Update& update) {
    ApplyOnRangeImpl(tree.GetRoot(), update);
  }

  void ApplyOnRangeImpl(Node& node, const Update& update) {
    dbg("LazyPropagator.ApplyOnRangeImpl", node.range, update.range,
        update.add);
    if (node.range.IsOutside(update.range)) {
      dbg("outside");
      return;
    }
    if (node.range.IsInside(update.range)) {
      dbg("inside");
      node.ApplyOperation(update.OnSubrange(node.range));
      return;
    }
    node.Push(tree.GetLeft(node), tree.GetRight(node));
    ApplyOnRangeImpl(tree.GetLeft(node), update);
    ApplyOnRangeImpl(tree.GetRight(node), update);
    node.Pull(tree.GetLeft(node), tree.GetRight(node));
  }

  template <typename Stats>
  auto GetAtIndex(Index idx) {
    return GetFromRange<Stats>(Range(idx, idx));
  }

  template <typename Stats>
  auto GetFromRange(Range range) {
    return GetFromRangeImpl<Stats>(tree.GetRoot(), range);
  }

  template <typename Stats>
  auto GetFromRangeImpl(Node& node, Range range) {
    using Monoid = typename Stats::Monoid;
    if (node.range.IsOutside(range)) {
      return Monoid::Identity();
    }
    if (node.range.IsInside(range)) {
      return node.template Get<Stats>();
    }
    node.Push(tree.GetLeft(node), tree.GetRight(node));
    auto left = GetFromRangeImpl<Stats>(tree.GetLeft(node), range);
    auto right = GetFromRangeImpl<Stats>(tree.GetRight(node), range);
    return Monoid::Combine(left, right);
  }
};

}  // namespace algo::ranges::segment_tree::details
