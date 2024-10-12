#pragma once

#include <optional>
#include <sstream>

#include <algo/utils/meta.hpp>
#include <algo/trees/segment_tree/details/nodes/base.hpp>
#include "algo/ranges/range.hpp"
#include "algo/utils/debug.hpp"

namespace algo::trees::segment_tree::details {

template <typename Update, typename... Statistics>
struct LazyNode : BaseNode<Update, Statistics...> {
  using Base = BaseNode<Update, Statistics...>;
  std::optional<Update> operation;

  LazyNode(int l, int r)
      : Base(l, r) {
  }

  void ApplyOperation(const Update& update) {
    this->Base::ApplyOperation(update);
    if (operation.has_value()) {
      operation = operation.value().Compose(update);
    } else {
      operation = update;
    }
  }

  void Push(LazyNode& left, LazyNode& right) {
    if (operation.has_value()) {
      left.ApplyOperation(operation.value().OnSubrange(left.range));
      right.ApplyOperation(operation.value().OnSubrange(right.range));
      operation.reset();
    }
  };

  std::string ToString() const {
    std::stringstream ss;
    ss << this->Base::ToString();
    ss << "Update = "
       << (operation.has_value() ? operation.value().ToString()
                                 : std::string("No update"));
    return ss.str();
  };
};
}  // namespace algo::trees::segment_tree::details
