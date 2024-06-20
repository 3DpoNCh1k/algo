#pragma once

#include <string>
#include <type_traits>

#include <algo/utils/traits/std/containers.hpp>
#include <algo/utils/traits/std/rank.hpp>

// NOLINTBEGIN
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