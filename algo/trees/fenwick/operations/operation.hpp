#pragma once

namespace algo::trees::fenwick::operations {
template <typename Statistics, typename Operation>
Statistics UpdateStatistics(const Statistics& stat, const Operation& op);

template <typename Operation>
auto CombineOperations(const Operation& op_old, const Operation& op_new);

template <typename Op>
struct OperationAtIndex {
  using Operation = Op;
  int index;
  Operation operation;
  OperationAtIndex(int index, Operation operation)
      : index(index),
        operation(operation) {
  }
};

template <typename Operation>
struct Apply {
  Operation operation;

  explicit Apply(Operation op)
      : operation(op) {
  }

  auto At(int idx) {
    return OperationAtIndex(idx, operation);
  }

  template <typename... Args>
  auto At(int idx, Args... rest) {
    return OperationAtIndex(idx, At(rest...));
  }
};

}  // namespace algo::trees::fenwick::operations
