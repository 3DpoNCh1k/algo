#pragma once

#include <type_traits>
#include <sstream>

#include <vector>
#include <string>
#include <bitset>
#include <utility>

#include "traits/traits.hpp"

template <typename T>
std::enable_if_t<is_to_stringable_v<T>, std::string> ToString(const T&);

template <typename T>
std::enable_if_t<has_ToString_v<T>, std::string> ToString(const T&);

template <typename T>
std::enable_if_t<is_std_array_v<T> || is_std_vector_v<T>, std::string> ToString(const T&);

template <typename T>
std::enable_if_t<!is_std_array_v<T> && !is_std_vector_v<T> && is_iterable_v<T>,
            std::string>
ToString(const T&);

std::string ToString(char c) {
  return std::string(1, c);
}
std::string ToString(bool b) {
  return b ? "true" : "false";
}
std::string ToString(const char* s) {
  return std::string(s);
}
std::string ToString(const std::string& s) {
  return s;
}
std::string ToString(const std::vector<bool>& v) {
  std::string result;
  for (const auto& x : v) {
    result += char('0' + static_cast<int>(x));
  }
  return result;
}

template <size_t N>
std::string ToString(const std::bitset<N>& b) {
  return b.ToString();
}

template <class T1, class T2>
std::string ToString(const std::pair<T1, T2>& p) {
  return "(" + ToString(p.first) + ", " + ToString(p.second) + ")";
}

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
