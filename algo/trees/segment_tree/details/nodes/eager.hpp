#pragma once

#include <algo/trees/segment_tree/details/nodes/base.hpp>

namespace algo::trees::segment_tree::details {

template <typename Operation, typename... Statistics>
struct EagerNode : BaseNode<Operation, Statistics...> {
  EagerNode(int l, int r)
      : BaseNode<Operation, Statistics...>(l, r){};
};

}  // namespace algo::trees::segment_tree::details
