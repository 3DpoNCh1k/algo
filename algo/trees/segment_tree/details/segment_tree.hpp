#pragma once

#include <utility>

namespace algo::trees::segment_tree::details {

template <template <typename> typename PropagatorTemplate,
          template <typename> typename TreeTemplate,
          template <typename, typename> typename NodeTemplate,
          typename Operation, typename StatisticsTuple>
struct SegmentTree {
  using Node = NodeTemplate<Operation, StatisticsTuple>;
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

  void ApplyAtIndex(int idx, const Operation& op) {
    propagator.ApplyAtIndex(idx, op);
  }

  void ApplyOnRange(int l, int r, const Operation& op) {
    propagator.ApplyOnRange(l, r, op);
  }

  template <typename Statistics>
  Statistics GetAtIndex(int idx) {
    return propagator.template GetAtIndex<Statistics>(idx);
  }

  template <typename Statistics>
  Statistics GetFromRange(int l, int r) {
    return propagator.template GetFromRange<Statistics>(l, r);
  }
};
}  // namespace algo::trees::segment_tree::details
