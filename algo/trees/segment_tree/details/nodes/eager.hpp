#pragma once

#include <algo/trees/segment_tree/details/nodes/base.hpp>

namespace algo::trees::segment_tree::details {

template <typename Update, typename... Statistics>
struct EagerNode : BaseNode<Update, Statistics...> {
  EagerNode(int l, int r)
      : BaseNode<Update, Statistics...>(l, r){};
};

}  // namespace algo::trees::segment_tree::details
