#pragma once

#include <string>
#include <sstream>

#include <algo/utils/types/fundamentals.hpp>

namespace algo::trees::segment_tree::operations {
struct SetOp {
  bool should_set = false;
  i64 set;

  std::string ToString() const {
    std::stringstream ss;
    ss << "should_set = " << should_set << " set = " << set;
    return ss.str();
  };
};
auto CombineOperations(const SetOp& op_old, const SetOp& op_new) {
  return op_new;
}
}  // namespace algo::trees::segment_tree::operations
