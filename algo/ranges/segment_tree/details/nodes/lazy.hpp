#pragma once

#include <optional>
#include <sstream>

#include <algo/utils/meta.hpp>
#include <algo/ranges/segment_tree/details/nodes/base.hpp>

namespace algo::ranges::segment_tree::details {

template <typename Index, typename Update, typename... Statistics>
struct LazyNode : BaseNode<Index, Update, Statistics...> {
  using Base = BaseNode<Index, Update, Statistics...>;
  std::optional<Update> operation;

  template <typename... Args>
  explicit LazyNode(Args&&... args)
      : Base(std::forward<Args>(args)...) {
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
}  // namespace algo::ranges::segment_tree::details
