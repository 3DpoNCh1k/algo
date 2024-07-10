#pragma  once

#include <string>
#include <sstream>

#include "algo/utils/types/types.hpp"
#include "algo/trees/segment_tree/operations/add.hpp"
#include "algo/trees/segment_tree/operations/set.hpp"

namespace algo::trees::segment_tree::operations {
struct SetAddOp {
  bool should_set = false;
  utils::i64 set;
  utils::i64 add = 0;
  SetAddOp(){};
  explicit SetAddOp(AddOp op): add(op.add) {};
  explicit SetAddOp(SetOp op): should_set(op.should_set), set(op.set) {};

  std::string ToString() const {
    std::stringstream ss;
    ss << "should_set = " << should_set << " set = " << set << " add = " << add;
    return ss.str();
  };
};


auto CombineOperations(const SetAddOp& op_old, const SetAddOp& op_new) {
  auto result_op = op_old;
  if (op_new.should_set) {
    result_op.should_set = true;
    result_op.set = op_new.set;
    result_op.add = 0;
  }

  result_op.add += op_new.add;
  return result_op;
}


}