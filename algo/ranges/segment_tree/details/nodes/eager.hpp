#pragma once

#include <algo/ranges/segment_tree/details/nodes/base.hpp>

namespace algo::ranges::segment_tree::details {

template <typename Index, typename Update, typename... Statistics>
struct EagerNode : BaseNode<Index, Update, Statistics...> {
  template <typename... Args>
  explicit EagerNode(Args&&... args)
      : BaseNode<Index, Update, Statistics...>(std::forward<Args>(args)...) {
  }
};

}  // namespace algo::ranges::segment_tree::details
