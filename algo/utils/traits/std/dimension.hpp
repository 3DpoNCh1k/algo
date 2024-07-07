#pragma once

#include <array>
#include <cstddef>
#include <vector>

namespace algo::utils::traits {
// NOLINTBEGIN
template <class T>
struct dimension : std::integral_constant<size_t, 0> {};

template <class T>
struct dimension<std::vector<T>>
    : std::integral_constant<size_t, dimension<T>::value + 1> {};

template <class T, size_t N>
struct dimension<std::array<T, N>>
    : std::integral_constant<size_t, dimension<T>::value + 1> {};

template <typename T>
struct dimension<T const> : dimension<T> {};

template <typename T>
struct dimension<T&> : dimension<T> {};

template <typename T>
struct dimension<T&&> : dimension<T> {};

template <typename T>
constexpr size_t dimension_v = dimension<T>::value;
// NOLINTEND
}  // namespace algo::utils::traits
