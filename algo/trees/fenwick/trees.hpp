#pragma once

#include <type_traits>
#include <utility>
#include "algo/trees/fenwick/operations/operation.hpp"
#include "algo/trees/fenwick/statistics/statistics.hpp"
#include <algo/trees/fenwick/details/fenwick_tree.hpp>

#include <tuple>

namespace algo::trees::fenwick {

template <typename Operation, typename StatisticsTuple>
struct FenwickTree {
  FenwickTree() = delete;
  using IndexOperation =
      decltype(std::declval<operations::Apply<Operation>>().At(1));

  details::FenwickTreeImpl<IndexOperation, StatisticsTuple> impl;

  explicit FenwickTree(int n)
      : impl(n) {
  }

  template <typename... Args>
  void ApplyAtIndex(const Operation& op, Args... indexes) {
    auto operation = operations::Apply(op).At(indexes...);
    // static_assert(std::is_same_v<decltype(operation), IndexOperation>);
    // auto iop = IndexOperation(operation);
    impl.Apply(operation);
  }

  template <typename Statistics>
  Statistics GetAtIndex(int idx) {
    return GetFromRange<Statistics>(idx, idx);
  }

  template <typename Statistics>
  Statistics GetFromRange(int l, int r) {
    auto range_stat = statistics::StatisticsFromRange<Statistics>(l, r);
    return impl.GetFromRange(range_stat);
  }
};

// template <typename Operation, typename StatisticsTuple>
// using LazyPropagationStaticSegmentTree =

// template <typename Operation, typename StatisticsTuple>
// using LazyPropagationDynamicSegmentTree =

// template <typename Operation, typename StatisticsTuple>
// using EagerPropagationStaticSegmentTree =

template <typename Op>
using Operation = Op;

template <typename... Stats>
using Statistics = std::tuple<Stats...>;

}  // namespace algo::trees::fenwick
