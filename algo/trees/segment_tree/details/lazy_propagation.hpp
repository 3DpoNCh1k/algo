#pragma once

#include <algo/trees/segment_tree/details/node.hpp>

#include "algo/trees/segment_tree/details/dynamic_tree.hpp"
#include "algo/trees/segment_tree/details/static_tree.hpp"

namespace algo::trees::segment_tree::details {

template <typename Operation, typename Value>
struct LazyProp {
  using TreeType = StaticTree<Operation, Value>;
  // using TreeType = DynamicTree<Operation, Value>;
  using NodeType = typename TreeType::DataNode;
  TreeType tree;
  explicit LazyProp(int n)
      : tree(n) {
  }

  // explicit LazyProp(int n)
  //     : tree(0, n-1) {
  // }

  void ApplyAtIndex(int idx, Operation op) {
    ApplyOnRange(idx, idx, op);
  }

  void ApplyOnRange(int l, int r, Operation op) {
    ApplyOnRangeImpl(tree.GetRoot(), l, r, op);
  }

  void ApplyOnRangeImpl(NodeType & node, int l, int r, Operation op) {
    if (node.IsOutside(l, r)) {
      return;
    }
    if (node.IsInside(l, r)) {
      node.ApplyOperation(op);
      return;
    }
    node.Push(tree.GetLeft(node), tree.GetRight(node));
    ApplyOnRangeImpl(tree.GetLeft(node), l, r, op);
    ApplyOnRangeImpl(tree.GetRight(node), l, r, op);
    node.Pull(tree.GetLeft(node), tree.GetRight(node));
  }

  template <typename Statistics>
  Statistics GetAtIndex(int idx) {
    return GetFromRange<Statistics>(idx, idx);
  }

  template <typename Statistics>
  Statistics GetFromRange(int l, int r) {
    return GetFromRangeImpl<Statistics>(tree.GetRoot(), l,r);
  }

  template <typename Statistics>
  Statistics GetFromRangeImpl(NodeType & node, int l, int r) {
    if (node.IsOutside(l, r)) {
      return Statistics{};
    }
    if (node.IsInside(l, r)) {
      return node.template Get<Statistics>();
    }
    node.Push(tree.GetLeft(node), tree.GetRight(node));
    auto left = GetFromRangeImpl<Statistics>(tree.GetLeft(node), l, r);
    auto right = GetFromRangeImpl<Statistics>(tree.GetRight(node), l, r);
    return left.Merge(right);
  }
};

}  // namespace algo::trees::segment_tree
