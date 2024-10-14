#pragma once

#include <optional>
#include <sstream>

#include <algo/utils/meta.hpp>
#include <algo/ranges/segment_tree/details/nodes/base.hpp>

namespace algo::ranges::segment_tree::details {

template <typename Index, typename Update, typename... Statistics>
struct LazyNode : BaseNode<Index, Update, Statistics...> {
  using Base = BaseNode<Index, Update, Statistics...>;
  std::optional<Update> node_update;

  template <typename... Args>
  explicit LazyNode(Args&&... args)
      : Base(std::forward<Args>(args)...) {
  }

  void Apply(const Update& update) {
    this->Base::Apply(update);
    if (node_update.has_value()) {
      node_update = node_update.value().Compose(update);
    } else {
      node_update = update;
    }
  }

  void Push(LazyNode& left, LazyNode& right) {
    if (node_update.has_value()) {
      left.Apply(node_update.value().OnSubrange(left.range));
      right.Apply(node_update.value().OnSubrange(right.range));
      node_update.reset();
    }
  };

  std::string ToString() const {
    std::stringstream ss;
    ss << this->Base::ToString();
    ss << "Update = "
       << (node_update.has_value() ? node_update.value().ToString()
                                   : std::string("No update"));
    return ss.str();
  };
};
}  // namespace algo::ranges::segment_tree::details
