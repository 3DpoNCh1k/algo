#pragma once

#include <vector>
#include <algo/utils/debug.hpp>
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
  // OperationAtIndex(){};
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
    // dbg("At", idx);
    return OperationAtIndex(idx, operation);
  }

  template <typename... Args>
  auto At(int idx, Args... rest) {
    // dbg("At", idx, rest...);
    return OperationAtIndex(idx, At(rest...));
  }

  // template <typename... Args>
  // auto AtX(Args... rest, int idx) {
  //   dbg("AtX", rest..., idx);
  //   return 1;
  //   // return OperationAtIndex(idx, AtX(rest...));
  // }

  // auto AtX(int idx) {
  //   dbg("AtX", idx);
  //   // return OperationAtIndex(idx, operation);
  //   return 2;
  // }
};

}  // namespace algo::trees::fenwick::operations
