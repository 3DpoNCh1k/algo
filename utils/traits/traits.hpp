#pragma once

#include <array>
#include <cstddef>
#include <string>
#include <type_traits>
#include <utility>
#include <vector>

// NOLINTBEGIN
template <class T>
struct std::rank<std::vector<T>>
    : std::integral_constant<std::size_t, std::rank<T>::value + 1> {};

template <class T, size_t N>
struct std::rank<std::array<T, N>>
    : std::integral_constant<std::size_t, rank<T>::value + 1> {};

template <typename T>
struct std::rank<T const> : rank<T> {};

template <typename T>
struct std::rank<T&> : rank<T> {};

template <typename T>
struct std::rank<T&&> : rank<T> {};

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

template <typename T, typename = void>
struct is_iterable : std::false_type {};

template <typename T>
struct is_iterable<T, std::void_t<decltype(std::begin(std::declval<T>()),
                                           std::end(std::declval<T>()))>>
    : std::true_type {};

template <typename T>
constexpr bool is_iterable_v = is_iterable<T>::value;

template <typename T, typename = void>
struct is_to_stringable : std::false_type {};

template <typename T>
struct is_to_stringable<T, std::void_t<decltype(std::to_string(std::declval<T>()))>>
    : std::true_type {};

template <typename T>
constexpr bool is_to_stringable_v = is_to_stringable<T>::value;

template <typename T, typename = void>
struct has_ToString : std::false_type {};

template <typename T>
struct has_ToString<T, std::void_t<decltype(std::declval<T>().ToString())>>
    : std::true_type {};

template <typename T>
constexpr bool has_ToString_v = has_ToString<T>::value;
// NOLINTEND