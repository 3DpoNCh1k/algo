#pragma once

#include <array>
#include <utility>

namespace algo::utils::meta {

template <int... ints>
using IntSeq = std::integer_sequence<int, ints...>;

template <int N>
struct IntNumber {
  static constexpr auto Value = N;
};

template <int... first_seq, int... second_seq>
constexpr auto Concat(IntSeq<first_seq...>, IntSeq<second_seq...>) {
  return IntSeq<first_seq..., second_seq...>{};
};

template <int from, int to>
constexpr auto IntRange() {
  if constexpr (from > to) {
    return IntSeq<>{};
  } else {
    return Concat(IntSeq<from>{}, IntRange<from + 1, to>());
  }
};

namespace details {

template <class F, int... ints>
constexpr void CallForIntSeq(F fun, IntSeq<ints...>) {
  (fun(IntNumber<ints>{}), ...);
}

template <int... ints, typename T>
auto MakeArrayImpl(algo::utils::meta::IntSeq<ints...>, T value) {
  return std::array{((void)ints, value)...};
}

template <int Index, typename U>
constexpr int IndexOfImpl() {
  return -1;
};

template <int Index, typename U, typename T, typename... Types>
constexpr int IndexOfImpl() {
  return std::is_same_v<U, T> ? Index : IndexOfImpl<Index + 1, U, Types...>();
}
}  // namespace details

template <int from, int to, class Body>
constexpr void ForLoop(Body body) {
  details::CallForIntSeq(body, IntRange<from, to>());
}

template <std::size_t N, typename T>
auto MakeArray(T value) {
  return details::MakeArrayImpl(algo::utils::meta::IntRange<0, N - 1>(),
                                std::move(value));
}

template <typename T, typename... Types>
constexpr int IndexOf() {
  return details::IndexOfImpl<0, T, Types...>();
}

}  // namespace algo::utils::meta
