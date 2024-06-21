#pragma once

#include <array>
#include <cstddef>
#include <vector>

namespace algo::utils::traits {
// NOLINTBEGIN
template <class T>
struct rank : std::rank<T> {};

template <class T>
struct rank<std::vector<T>>
    : std::integral_constant<size_t, std::rank<T>::value + 1> {};

template <class T, size_t N>
struct rank<std::array<T, N>>
    : std::integral_constant<size_t, rank<T>::value + 1> {};

template <typename T>
struct rank<T const> : rank<T> {};

template <typename T>
struct rank<T&> : rank<T> {};

template <typename T>
struct rank<T&&> : rank<T> {};
// NOLINTEND
}  // namespace algo::utils::traits
