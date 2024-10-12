#pragma once

#include <optional>
#include <sstream>

#include <algo/utils/meta.hpp>
#include <algo/trees/segment_tree/details/nodes/base.hpp>
#include "algo/ranges/range.hpp"
#include "algo/utils/debug.hpp"

namespace algo::trees::segment_tree::details {

template <typename Operation, typename StatisticsTuple>
struct LazyNode : BaseNode<Operation, StatisticsTuple> {
  using Base = BaseNode<Operation, StatisticsTuple>;
  std::optional<Operation> operation;

  LazyNode(int l, int r)
      : Base(l, r) {
  }

  void ApplyOperation(const Operation& op) {
    this->Base::ApplyOperation(op);
    if (operation.has_value()) {
      operation = operation.value().Compose(op);
    } else {
      operation = op;
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
    ss << "Operation = "
       << (operation.has_value() ? operation.value().ToString()
                                 : std::string("No op"));
    return ss.str();
  };
};
}  // namespace algo::trees::segment_tree::details
