#pragma once

#include <sstream>

#include <algo/utils/meta.hpp>
#include "algo/trees/segment_tree/details/nodes/base.hpp"

namespace algo::trees::segment_tree::details {

template <typename Operation, typename StatisticsTuple>
struct LazyNode : BaseNode<Operation, StatisticsTuple> {
  using Base = BaseNode<Operation, StatisticsTuple>;
  Operation operation;

  void ApplyOperation(const Operation& op) {
    this->Base::ApplyOperation(op);
    operation = CombineOperations(operation, op);
  }

  void Push(LazyNode& left, LazyNode& right) {
    left.ApplyOperation(operation);
    right.ApplyOperation(operation);
    operation = Operation{};
  };

  std::string ToString() const {
    std::stringstream ss;
    ss << this->Base::ToString();
    ss << "Operation = " << operation.ToString();
    return ss.str();
  };
};
}  // namespace algo::trees::segment_tree::details
