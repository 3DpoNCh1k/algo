#pragma once

#include "algo/ranges/range.hpp"
#include "algo/utils/debug.hpp"
namespace algo::trees::segment_tree::details {

template <typename Tree>
struct LazyPropagator {
  using Node = typename Tree::DataNode;
  using Operation = typename Node::Operation;

  Tree& tree;
  explicit LazyPropagator(Tree& tree)
      : tree(tree) {
  }

  void ApplyAtIndex(const Operation& op) {
    ApplyOnRange(op);
  }

  void ApplyOnRange(const Operation& op) {
    ApplyOnRangeImpl(tree.GetRoot(), op);
  }

  void ApplyOnRangeImpl(Node& node, const Operation& op) {
    dbg("LazyPropagator.ApplyOnRangeImpl", node.range, op.range, op.add);
    if (node.range.IsOutside(op.range)) {
      dbg("outside");
      return;
    }
    if (node.range.IsInside(op.range)) {
      dbg("inside");
      node.ApplyOperation(op.OnSubrange(node.range));
      return;
    }
    node.Push(tree.GetLeft(node), tree.GetRight(node));
    ApplyOnRangeImpl(tree.GetLeft(node), op);
    ApplyOnRangeImpl(tree.GetRight(node), op);
    node.Pull(tree.GetLeft(node), tree.GetRight(node));
  }

  template <typename Statistics>
  Statistics GetAtIndex(int idx) {
    return GetFromRange<Statistics>(ranges::IntRange(idx, idx));
  }

  template <typename Statistics>
  Statistics GetFromRange(ranges::IntRange range) {
    return Statistics(range,
                      GetFromRangeImpl<Statistics>(tree.GetRoot(), range));
  }

  template <typename Statistics>
  auto GetFromRangeImpl(Node& node, ranges::IntRange range) {
    using Monoid = typename Statistics::Monoid;
    if (node.range.IsOutside(range)) {
      return Monoid::Identity();
    }
    if (node.range.IsInside(range)) {
      return node.template Get<Statistics>();
    }
    node.Push(tree.GetLeft(node), tree.GetRight(node));
    auto left = GetFromRangeImpl<Statistics>(tree.GetLeft(node), range);
    auto right = GetFromRangeImpl<Statistics>(tree.GetRight(node), range);
    return Monoid::Combine(left, right);
  }
};

}  // namespace algo::trees::segment_tree::details
