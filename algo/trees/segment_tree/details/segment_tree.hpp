#pragma once

#include <utility>
#include "algo/ranges/range.hpp"

namespace algo::trees::segment_tree::details {

template <template <typename> typename PropagatorTemplate,
          template <typename> typename TreeTemplate,
          template <typename, typename...> typename NodeTemplate,
          typename Update, typename... Statistics>
struct SegmentTree {
  using Node = NodeTemplate<Update, Statistics...>;
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

  // void ApplyAtIndex(int idx, const Update& update) {
  //   propagator.ApplyAtIndex(idx, update);
  // }

  void ApplyAtIndex(const Update& update) {
    dbg("SegmentTree.ApplyAtIndex", update.range, update.add);
    propagator.ApplyAtIndex(update);
  }

  void ApplyOnRange(const Update& update) {
    propagator.ApplyOnRange(update);
  }

  template <typename Stats>
  Stats GetAtIndex(int idx) {
    return propagator.template GetAtIndex<Stats>(idx);
  }

  template <typename Stats>
  Stats GetFromRange(ranges::IntRange range) {
    return propagator.template GetFromRange<Stats>(range);
  }
};
}  // namespace algo::trees::segment_tree::details
