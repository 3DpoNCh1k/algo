#pragma once

#include <algo/trees/fenwick/operations/operation.hpp>
#include <algo/trees/fenwick/statistics/statistics.hpp>
#include <algo/trees/fenwick/details/fenwick_tree.hpp>
#include <algo/trees/fenwick/details/node.hpp>

#include <tuple>

namespace algo::trees::fenwick {

template <typename FenwickTreeImpl>
struct FenwickTree {
  static constexpr int Dimension = FenwickTreeImpl::Dimension;
  FenwickTreeImpl impl;

  FenwickTree() = delete;
  template <typename... Args>
  explicit FenwickTree(Args... args)
      : impl(args...) {
  }

  template <typename Operation, typename... Args>
  void ApplyAtIndex(const Operation& op, Args... indexes) {
    auto operation = operations::Apply(op).At(indexes...);
    impl.Apply(operation);
  }

  template <typename Statistics, typename... Args>
  Statistics GetAtIndex(Args... args) {
    auto range_stat = statistics::Get<Statistics>().At(args...);
    return impl.GetFromRange(range_stat);
  }

  template <typename Statistics, typename... Args>
  Statistics GetFromRange(Args... args) {
    auto range_stat = statistics::Get<Statistics>().From(args...);
    return impl.GetFromRange(range_stat);
  }
};

template <typename Operation, typename Statistics>
using Fenwick1DImpl = details::FenwickTreeImpl<
    details::Node<operations::OperationAtIndex<Operation>, Statistics>>;

template <typename Operation, typename Statistics>
using Fenwick2DImpl =
    details::FenwickTreeImpl<Fenwick1DImpl<Operation, Statistics>>;

template <typename Operation, typename Statistics>
using Fenwick3DImpl =
    details::FenwickTreeImpl<Fenwick2DImpl<Operation, Statistics>>;

template <typename Operation, typename Statistics>
using Fenwick = FenwickTree<Fenwick1DImpl<Operation, Statistics>>;

template <typename Operation, typename Statistics>
using Fenwick2D = FenwickTree<Fenwick2DImpl<Operation, Statistics>>;

template <typename Operation, typename Statistics>
using Fenwick3D = FenwickTree<Fenwick3DImpl<Operation, Statistics>>;

template <typename Op>
using Operation = Op;

template <typename... Stats>
using Statistics = std::tuple<Stats...>;

}  // namespace algo::trees::fenwick
