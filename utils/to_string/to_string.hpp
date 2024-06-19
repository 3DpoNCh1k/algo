#pragma once

#include <type_traits>
#include <sstream>
#include <string>

#include "../traits/traits.hpp"
#include "fundamentals.hpp"
#include "std/bitset.hpp"
#include "std/pair.hpp"
#include "std/string.hpp"
#include "std/vector_bool.hpp"

template <typename T>
std::enable_if_t<is_to_stringable_v<T>, std::string> ToString(const T&);

template <typename T>
std::enable_if_t<has_ToString_v<T>, std::string> ToString(const T&);

template <typename T>
std::enable_if_t<is_std_array_v<T> || is_std_vector_v<T>, std::string> ToString(
    const T&);

template <typename T>
std::enable_if_t<!is_std_array_v<T> && !is_std_vector_v<T> && is_iterable_v<T>,
                 std::string>
ToString(const T&);

template <typename T>
std::enable_if_t<is_to_stringable_v<T>, std::string> ToString(const T& value) {
  return std::to_string(value);
}

template <typename T>
std::enable_if_t<has_ToString_v<T>, std::string> ToString(const T& value) {
  return value.toString();
}

template <class T>
std::enable_if_t<is_std_array_v<T> || is_std_vector_v<T>, std::string> ToString(
    const T& arr_or_vec) {
  std::stringstream result;
  result << "[";
  for (int i = 0; i < int(arr_or_vec.size()); ++i) {
    if constexpr (std::rank_v<decltype(arr_or_vec[i])> > 0) {
      result << "\n";
    }
    result << "i=" + ToString(i) + ": ";
    result << ToString(arr_or_vec[i]);
    result << (i == int(arr_or_vec.size()) - 1 ? "" : ", ");
  }
  result << "]";
  return result.str();
}

template <typename T>
std::enable_if_t<!is_std_array_v<T> && !is_std_vector_v<T> && is_iterable_v<T>,
                 std::string>
ToString(const T& iterable) {
  std::stringstream result;
  result << "{";
  int i = 0;
  for (const auto& entry : iterable) {
    if constexpr (std::rank_v<decltype(entry)> > 0) {
      result << "\n";
    }
    result << ToString(entry);
    result << (i == int(iterable.size()) - 1 ? "" : ", ");
    ++i;
  }
  result << "}";
  return result.str();
}
