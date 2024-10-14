#pragma once

#include <sstream>
#include <tuple>

#include <algo/utils/meta.hpp>
#include <algo/ranges/range.hpp>
#include <algo/ranges/statistics/value_of.hpp>

#include "algo/utils/debug.hpp"

namespace algo::ranges::segment_tree::details {

template <typename IndexType, typename UpdateType, typename... Statistics>
struct BaseNode {
  static constexpr size_t N = sizeof...(Statistics);
  static_assert(N > 0);

  using Index = IndexType;
  using Range = ranges::Range<Index>;
  using Update = UpdateType;

  using StatisticsTuple = std::tuple<Statistics...>;
  using Value = typename std::tuple_element_t<0, StatisticsTuple>::Value;

  Range range;
  StatisticsTuple statistics;

  std::array<Value, N> values;

  BaseNode(Index l, Index r, Value value)
      : range(l, r),
        values(utils::meta::MakeArray<N>(value)) {
    dbg(l, r, range);
  }

  void ApplyOperation(const Update& update) {
    dbg("BaseNode.ApplyOperation", range, update.range, update.add);
    assert(range == update.range);

    utils::meta::ForLoop<0, std::tuple_size_v<StatisticsTuple> - 1>(
        [&](auto index) {
          using Stats = std::tuple_element_t<index.Value, StatisticsTuple>;

          auto& value = values[index.Value];
          value = update.Apply(statistics::ValueOf<Stats>(value));
        });
  }

  void Pull(const BaseNode& left, const BaseNode& right) {
    utils::meta::ForLoop<0, std::tuple_size_v<StatisticsTuple> - 1>(
        [&](auto index) {
          using Stats = std::tuple_element_t<index.Value, StatisticsTuple>;
          using Monoid = typename Stats::Monoid;

          auto& value = values[index.Value];
          value = Monoid::Combine(left.Get<Stats>(), right.Get<Stats>());
        });
  };

  template <typename Stats>
  auto Get() const {
    constexpr auto Index = utils::meta::IndexOf<Stats, Statistics...>();
    static_assert(Index != -1);

    return values[Index];
  }

  std::string ToString() const {
    std::stringstream ss;
    ss << "Node:" << std::endl;
    ss << range.ToString() << std::endl;
    return ss.str();
  };
};
}  // namespace algo::ranges::segment_tree::details
