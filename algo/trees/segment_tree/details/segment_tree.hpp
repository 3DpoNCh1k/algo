#pragma once

#include <utility>
#include "algo/ranges/range.hpp"

namespace algo::trees::segment_tree::details {

template <template <typename> typename PropagatorTemplate,
          template <typename> typename TreeTemplate,
          template <typename, typename...> typename NodeTemplate,
          typename Operation, typename... TStatistics>
struct SegmentTree {
  using Node = NodeTemplate<Operation, TStatistics...>;
  using Tree = TreeTemplate<Node>;
  using Propagator = PropagatorTemplate<Tree>;

  Tree tree;
  Propagator propagator;

  SegmentTree() = delete;

  template <typename... Args>
  explicit SegmentTree(Args&&... args)
      : tree(std::forward<Args>(args)...),
        propagator(tree) {
  }

  // void ApplyAtIndex(int idx, const Operation& op) {
  //   propagator.ApplyAtIndex(idx, op);
  // }

  void ApplyAtIndex(const Operation& op) {
    dbg("SegmentTree.ApplyAtIndex", op.range, op.add);
    propagator.ApplyAtIndex(op);
  }

  void ApplyOnRange(const Operation& op) {
    propagator.ApplyOnRange(op);
  }

  template <typename Statistics>
  Statistics GetAtIndex(int idx) {
    return propagator.template GetAtIndex<Statistics>(idx);
  }

  template <typename Statistics>
  Statistics GetFromRange(ranges::IntRange range) {
    return propagator.template GetFromRange<Statistics>(range);
  }
};
}  // namespace algo::trees::segment_tree::details
