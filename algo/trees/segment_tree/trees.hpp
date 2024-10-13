#pragma once

#include <algo/trees/segment_tree/details/trees/dynamic.hpp>
#include <algo/trees/segment_tree/details/trees/static.hpp>

#include <algo/trees/segment_tree/details/propagators/lazy.hpp>
#include <algo/trees/segment_tree/details/propagators/eager.hpp>

#include <algo/trees/segment_tree/details/nodes/eager.hpp>
#include <algo/trees/segment_tree/details/nodes/lazy.hpp>

#include <algo/trees/segment_tree/details/segment_tree.hpp>

namespace algo::trees::segment_tree {
template <typename Update, typename... Statistics>
using LazyPropagationStaticSegmentTree =
    details::SegmentTree<int, details::LazyPropagator, details::StaticTree,
                         details::LazyNode, Update, Statistics...>;

template <typename Update, typename... Statistics>
using EagerPropagationStaticSegmentTree =
    details::SegmentTree<int, details::EagerPropagator, details::StaticTree,
                         details::EagerNode, Update, Statistics...>;

template <typename Update, typename Statistics>
using LazyPropagationDynamicSegmentTree =
    details::SegmentTree<i64, details::LazyPropagator, details::DynamicTree,
                         details::LazyNode, Update, Statistics>;

}  // namespace algo::trees::segment_tree
