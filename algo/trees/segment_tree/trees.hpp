#pragma once

#include <algo/trees/segment_tree/details/trees/dynamic_tree.hpp>
#include <algo/trees/segment_tree/details/trees/static_tree.hpp>
#include <algo/trees/segment_tree/details/propagators/lazy_propagator.hpp>
#include <algo/trees/segment_tree/details/propagators/eager_propagator.hpp>
#include <algo/trees/segment_tree/details/segment_tree.hpp>

#include <tuple>

namespace algo::trees::segment_tree {
template <typename Operation, typename StatisticsTuple>
using LazyPropagationStaticSegmentTree =
    details::SegmentTree<details::LazyPropagator, details::StaticTree,
                         Operation, StatisticsTuple>;

template <typename Operation, typename StatisticsTuple>
using LazyPropagationDynamicSegmentTree =
    details::SegmentTree<details::LazyPropagator, details::DynamicTree,
                         Operation, StatisticsTuple>;

template <typename Operation, typename StatisticsTuple>
using EagerPropagationStaticSegmentTree =
    details::SegmentTree<details::EagerPropagator, details::StaticTree,
                         Operation, StatisticsTuple>;

template <typename Op>
using Operation = Op;

template <typename... Stats>
using Statistics = std::tuple<Stats...>;

}  // namespace algo::trees::segment_tree
