#pragma once

#include <algo/trees/segment_tree/details/nodes/base.hpp>

namespace algo::trees::segment_tree::details {

template <typename Operation, typename StatisticsTuple>
struct EagerNode : BaseNode<Operation, StatisticsTuple> {};
}  // namespace algo::trees::segment_tree::details
