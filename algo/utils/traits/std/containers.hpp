#pragma once

#include <array>
#include <cstddef>
#include <type_traits>
#include <vector>

namespace algo::utils::traits {
// NOLINTBEGIN
template <typename T>
struct is_std_vector : std::false_type {};

template <typename T>
struct is_std_vector<std::vector<T>> : std::true_type {};

template <typename T>
struct is_std_vector<T const> : is_std_vector<T> {};

template <typename T>
struct is_std_vector<T&> : is_std_vector<T> {};

template <typename T>
struct is_std_vector<T&&> : is_std_vector<T> {};

template <typename T>
constexpr bool is_std_vector_v = is_std_vector<T>::value;

template <typename T>
struct is_std_array : std::false_type {};

template <typename T, size_t N>
struct is_std_array<std::array<T, N>> : std::true_type {};

template <typename T>
struct is_std_array<T const> : is_std_array<T> {};

template <typename T>
struct is_std_array<T&> : is_std_array<T> {};

template <typename T>
struct is_std_array<T&&> : is_std_array<T> {};

template <typename T>
constexpr bool is_std_array_v = is_std_array<T>::value;
// NOLINTEND
}  // namespace algo::utils::traits
