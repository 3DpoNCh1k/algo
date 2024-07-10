#pragma once

#include <utility>

namespace algo::utils::meta {

template <int... ints>
using IntSeq = std::integer_sequence<int, ints...>;

template <int N>
struct IntNumber {
  static constexpr auto Value = N;
};

template <int... first_seq, int... second_seq>
auto Concat(IntSeq<first_seq...>, IntSeq<second_seq...>) {
  return IntSeq<first_seq..., second_seq...>{};
};

template <int from, int to>
auto IntRange() {
  if constexpr (from > to) {
    return IntSeq<>{};
  } else {
    return Concat(IntSeq<from>{}, IntRange<from + 1, to>());
  }
};

template <class F, int... ints>
void CallForIntSeq(F fun, IntSeq<ints...>) {
  (fun(IntNumber<ints>{}), ...);
}

template <int from, int to, class Body>
void ForLoop(Body body) {
  CallForIntSeq(body, IntRange<from, to>());
}
}  // namespace algo::utils::meta
