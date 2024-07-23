#pragma once

#include <string>
#include <sstream>

#include <algo/utils/types/fundamentals.hpp>
namespace algo::trees::fenwick::operations {
struct AddOp {
  i64 add = 0;

  std::string ToString() const {
    std::stringstream ss;
    ss << "add = " << add;
    return ss.str();
  };
};

auto CombineOperations(const AddOp& op_old, const AddOp& op_new) {
  auto new_op = op_old;
  new_op.add += op_new.add;
  return new_op;
}

}  // namespace algo::trees::fenwick::operations
