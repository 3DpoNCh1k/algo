#pragma once

#include "algo/ranges/range.hpp"
#include "algo/utils/debug.hpp"
namespace algo::trees::segment_tree::details {

template <typename Tree>
struct LazyPropagator {
  using Node = typename Tree::DataNode;
  using Update = typename Node::Update;

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
  Stats GetAtIndex(int idx) {
    return GetFromRange<Stats>(ranges::IntRange(idx, idx));
  }

  template <typename Stats>
  Stats GetFromRange(ranges::IntRange range) {
    return Stats(range, GetFromRangeImpl<Stats>(tree.GetRoot(), range));
  }

  template <typename Stats>
  auto GetFromRangeImpl(Node& node, ranges::IntRange range) {
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

}  // namespace algo::trees::segment_tree::details
