#include <cstdint>
#include <iostream>
#include <limits>
#include <tuple>
#include <type_traits>
#include <utility>
#include <variant>
#include <vector>
#include "algo/utils/debug.hpp"
#include "algo/utils/types/types.hpp"
#include "tests/testing/asserts.hpp"

#include <algo/trees/segment_tree/tree.hpp>
#include <algo/trees/segment_tree/node.hpp>
#include <algo/trees/segment_tree/operation.hpp>
#include <algo/trees/segment_tree/statistics.hpp>

#include <algo/trees/segment_tree/lazy_propagation.hpp>

using std::cout;
using std::endl;

using namespace algo::trees::segment_tree;

template <typename T, typename... Us>
struct contains : std::disjunction<std::is_same<T, Us>...> {};

template <typename T, typename... Us>
constexpr bool contains_v = contains<T, Us...>::value;

template <typename... Types>
struct S {
  std::tuple<Types...> t;

  // template<typename O>
  // std::enable_if_t<std::disjunction_v<std::is_same<O, Types>...>> Update(O) {
  //   std::cout << "Update" << " O = " << typeid(O).name() << std::endl;
  // };
  template <typename O>
  std::enable_if_t<contains_v<O, Types...>> Update(O) {
    std::cout << "Update" << " O = " << typeid(O).name() << std::endl;
  };
};

// TODO: Add Trait that Statistics has Merge function

void TestStats() {
  auto sum1 = Sum{0, 3, 0};
  auto op1 = AddOp{2};
  auto new_s = UpdateStatistics(sum1, op1);
  std::cout << new_s.result << std::endl;

  auto op2 = AddOp{1};
  auto res1 = UpdateStatistics(UpdateStatistics(sum1, op1), op2);
  auto res2 = UpdateStatistics(sum1, CombineOperations(op1, op2));

  std::cout << res1.result << std::endl;
  std::cout << res2.result << std::endl;
}

// template<size_t I = 0; sizetypename F>


void TestTree() {
  // using UpdateType = Update<AddOp>;
  using StatisticsType = Value<Sum>;
  using TreeType = Tree<AddOp, StatisticsType>;

  // cout << tree.nodes[0].update.update.index() << endl;

  using TupleT = std::tuple<int, double>;
  std::tuple<int, double> t;
  // for(int i = 0; i < std::tuple_size_v<decltype(t)>; ++i) {
  //   cout << "i = " << i << endl;
  //   cout << "value = " << std::get<i>(t) << endl;
  // }
  std::variant<int, double> var;
  // int idx = var.index();
  // constexpr int idx = 0;
  // const int idx = 0;
  // for(constexpr int i = 0; i < 10; ++i) {

  // };

  auto f = [](int i) {
    cout << "f(" << i << ")" << endl;
  };

  // For(f, std::make_index_sequence<3>());

  // auto x = std::get<0>(var);
  // auto x = std::get<idx>(var);
  constexpr size_t N = std::variant_size_v<decltype(var)>;
  auto seq = std::make_index_sequence<N>{};
  For([&var](auto i){
    if (i.Value == var.index()) {
      auto x = std::get<i.Value>(var);
    }
  }, seq);


  auto tree = TreeType(3);
  tree.ApplyAtIndex(0, AddOp{1});
  auto res = tree.GetFromRange<Sum>(0, 0);
  {
    auto res = tree.GetFromRange<Sum>(0, 2);
    cout << "res.result = " << res.result << endl;
  }
  tree.ApplyAtIndex(1, AddOp{2});
  tree.ApplyAtIndex(1, AddOp{3});
  {
    auto res = tree.GetFromRange<Sum>(0, 2);
    cout << "res.result = " << res.result << endl;
  }
}

void TestLazyProp() {
  cout << "TestLazyProp.Start" << endl;
  using StatisticsType = Value<Sum>;
  const int n = 5;
  auto lazy = LazyProp<AddOp, StatisticsType>(n);
  {
    auto res = lazy.GetAtIndex<Sum>(0);    
  }

  cout << "TestLazyProp.End" << endl;
}

template<int... Ints>
using IntSeq = std::integer_sequence<int, Ints...>;

// template<int...value>
// struct Range;

// template<>
// struct Range<> {
//   using Value = IntSeq;
// };

template<int ...first, int... second>
auto Concat(IntSeq<first...>, IntSeq<second...>) {
  return IntSeq<first..., second...>{};
};

template<int first, int last>
auto RangeFunc() {
  if constexpr (first > last) {
    return IntSeq<>{};
  } else {
    return Concat(IntSeq<first>{}, RangeFunc<first + 1, last>());
  }
};


// template<int FROM, int TO>
// auto Generate() {
//   if constexpr (FROM > TO) {
//     return std::integer_sequence<int>{};
//   }
//   auto tail = Generate<FROM + 1, TO>();
//   return std::integer_sequence<int, FROM,>
// }

template<typename T>
struct MyStructT {
  
};

template<template<typename  T> typename  TT>
struct MyStructTT {
  
};

struct BaseA {
  int x;
};

struct A: BaseA {

};

int main() {
  auto s = S<char, int>();
  auto ss = S<>();
  // std::get<int>(s.t);
  // std::get<double>(s.t);
  s.Update(1);
  // s.Update(1.0);
  // s.Update("");

  using T = decltype(std::get<double>(s.t));
  std::cout << "T = " << typeid(T).name() << std::endl;

  using TupleT = std::tuple<char, int>;
  // std::cout << has_type<int, TupleT>::value << std::endl;
  // std::cout << has_type<double, TupleT>::value << std::endl;

  std::cout << contains_v<int> << std::endl;

  // TestStats();
  TestTree();

  auto res = RangeFunc<1, 0>();
  auto res2 = RangeFunc<0, 0>();
  auto res3 = RangeFunc<1, 5>();

  For([](auto number) {
    cout << number.Value << endl;
  }, RangeFunc<-3, 4>());

  // auto x = MyStruct<int>{};
  
  auto t = MyStructT<int>{};
  auto tt = MyStructTT<MyStructT>{};

  // TestLazyProp();

  // auto a = A{};
  // BaseA & ba = a;
  // auto& a2 = static_cast<A&>(ba);
  // cout << &a << endl;
  // cout << &a2 << endl;

  // auto inf = std::numeric_limits<algo::utils::i64>::max();
  // cout << std::numeric_limits<algo::utils::i64>::has_infinity << endl;
  // cout << "inf = " << inf << endl;

  auto ba = BaseA{};
  auto a = A{};
  auto x = BaseA(a);
  // auto y = A(ba);

  // auto node = LazyNode<SetAddOp, Value<Minimum>>();

  int var;
  dbg(&var);
  // dbg(size_t(&var));
  // auto st = std::to_string(uintptr_t(&var));
  // dbg(st);
}
