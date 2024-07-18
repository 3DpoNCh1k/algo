#pragma once

namespace algo::trees::segment_tree {
template <typename Statistics, typename Operation>
Statistics UpdateStatistics(const Statistics& stat, const Operation& op);

template <typename Operation>
auto CombineOperations(const Operation& op_old, const Operation& op_new);

struct NoOp {};

}  // namespace algo::trees::segment_tree
