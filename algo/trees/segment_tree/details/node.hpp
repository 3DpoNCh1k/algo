#pragma once

#include <sstream>
#include <tuple>
#include <algo/utils/debug.hpp>

namespace algo::trees::segment_tree::details {

template<typename... StatisticsTypes>
struct Value {
  std::tuple<StatisticsTypes...> value;
};

template<std::size_t N>
struct Number { static const constexpr auto Value = N; };

template <class F, std::size_t... Is>
void For(F fun, std::index_sequence<Is...>)
{
  (fun(Number<Is>{}), ...);
}

template<int N>
struct IntNumber { static const constexpr auto Value = N; };

template <class F, int... Is>
void For(F fun, std::integer_sequence<int,Is...>)
{
  (fun(IntNumber<Is>{}), ...);
}

template <typename Operation, typename Value>
struct Node {
  Operation update;
  Value value;

  int L = -1;
  int R = -1;

  bool IsOutside(int l, int r) const {
    return L > r || R < l;
  }

  bool IsInside(int l, int r) const {
    return l <= L && R <= r;
  }

  void SetInterval(int l, int r) {
    L = l;
    R = r;
    For([&](auto index) {
      auto & stat = std::get<index.Value>(value.value);
      stat.L = L;
      stat.R = R;
    }, std::make_index_sequence<std::tuple_size_v<decltype(value.value)>>{});
  };

  void ApplyOperation(const Operation & op) {
    // auto seq = std::make_index_sequence<std::tuple_size_v<decltype(value)>>{};
    For([&](auto index) {
      auto & stat = std::get<index.Value>(value.value);
      stat = UpdateStatistics(stat, op);
    }, std::make_index_sequence<std::tuple_size_v<decltype(value.value)>>{});
    update = CombineOperations(update, op);
  }

  void Pull(const Node & left, const Node & right) {
    For([&](auto index) {
      auto & stat = std::get<index.Value>(value.value);
      const auto & left_stat = std::get<index.Value>(left.value.value);
      const auto & right_stat = std::get<index.Value>(right.value.value);
      stat = left_stat.Merge(right_stat);
      stat.L = L;
      stat.R = R;
    }, std::make_index_sequence<std::tuple_size_v<decltype(value.value)>>{});
  };

  void Push(Node & left, Node & right) {
    left.ApplyOperation(update);
    right.ApplyOperation(update);
    update = Operation{};
  };

  template<typename Statistics>
  Statistics Get() const {
    auto & stat = std::get<Statistics>(value.value);
    dbg("Node.Get", L, R, stat.result);
    return stat;
  }

  std::string ToString() const {
    std::stringstream ss;
    ss << "Node:" << std::endl;
    ss << "L = " << L << " R = " << R << std::endl;
    ss << "Operation = " << update.ToString();
    return ss.str();
  };
};
}