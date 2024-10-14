#pragma once

#include <utility>

namespace algo::ranges::segment_tree::details {

template <typename Index, template <typename> typename PropagatorTemplate,
          template <typename> typename TreeTemplate,
          template <typename, typename, typename...> typename NodeTemplate,
          typename Update, typename... Statistics>
struct SegmentTree {
  using Node = NodeTemplate<Index, Update, Statistics...>;
  using Tree = TreeTemplate<Node>;
  using Propagator = PropagatorTemplate<Tree>;

  using Range = typename Node::Range;

  Tree tree;
  Propagator propagator;

  SegmentTree() = delete;

  template <typename... Args>
  explicit SegmentTree(Args&&... args)
      : tree(std::forward<Args>(args)...),
        propagator(tree) {
  }

  void ApplyAtIndex(const Update& update) {
    dbg("SegmentTree.ApplyAtIndex", update.range, update.add);
    propagator.ApplyAtIndex(update);
  }

  void ApplyOnRange(const Update& update) {
    propagator.ApplyOnRange(update);
  }

  template <typename Stats>
  typename Stats::Value GetAtIndex(Index idx) {
    return propagator.template GetAtIndex<Stats>(idx);
  }

  template <typename Stats>
  typename Stats::Value GetFromRange(Range range) {
    return propagator.template GetFromRange<Stats>(range);
  }

  template <typename Stats>
  typename Stats::Value GetFromRange(Index l, Index r) {
    return propagator.template GetFromRange<Stats>(Range(l, r));
  }
};
}  // namespace algo::ranges::segment_tree::details
