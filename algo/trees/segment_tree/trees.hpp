#pragma once

#include <algo/trees/segment_tree/details/trees/dynamic.hpp>
#include <algo/trees/segment_tree/details/trees/static.hpp>
#include <algo/trees/segment_tree/details/propagators/lazy.hpp>
#include <algo/trees/segment_tree/details/propagators/eager.hpp>
#include <algo/trees/segment_tree/details/segment_tree.hpp>

#include <tuple>
#include <algo/trees/segment_tree/details/nodes/eager.hpp>
#include <algo/trees/segment_tree/details/nodes/lazy.hpp>

namespace algo::trees::segment_tree {
template <typename Operation, typename StatisticsTuple>
using LazyPropagationStaticSegmentTree =
    details::SegmentTree<details::LazyPropagator, details::StaticTree,
                         details::LazyNode, Operation, StatisticsTuple>;

template <typename Operation, typename StatisticsTuple>
using LazyPropagationDynamicSegmentTree =
    details::SegmentTree<details::LazyPropagator, details::DynamicTree,
                         details::LazyNode, Operation, StatisticsTuple>;

template <typename Operation, typename StatisticsTuple>
using EagerPropagationStaticSegmentTree =
    details::SegmentTree<details::EagerPropagator, details::StaticTree,
                         details::EagerNode, Operation, StatisticsTuple>;

template <typename Op>
using Operation = Op;

template <typename... Stats>
using Statistics = std::tuple<Stats...>;

}  // namespace algo::trees::segment_tree
