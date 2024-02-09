#pragma once

#include <algorithm>
#include <array>
#include <bit>
#include <bitset>
#include <cassert>
#include <chrono>
#include <cmath>
#include <complex>
#include <cstddef>
#include <cstdint>
#include <deque>
#include <fstream>
#include <functional>
#include <iomanip>
#include <ios>
#include <iostream>
#include <limits>
#include <map>
#include <memory>
#include <numeric>
#include <ostream>
#include <queue>
#include <random>
#include <set>
#include <sstream>
#include <stack>
#include <stdio.h>
#include <string>
#include <type_traits>
#include <unordered_map>
#include <unordered_set>
#include <utility>
#include <vector>

// NOLINTBEGIN
using namespace std;

using i16 = int16_t;
using u16 = uint16_t;
using i32 = int32_t;
using u32 = uint32_t;
using i64 = int64_t;
using u64 = uint64_t;

#define all(x) (x).begin(), (x).end()

const int d4i[4] = {-1, 0, 1, 0};
const int d4j[4] = {0, 1, 0, -1};
const int d8i[8] = {-1, -1, 0, 1, 1, 1, 0, -1};
const int d8j[8] = {0, 1, 1, 1, 0, -1, -1, -1};

const int MOD = 1e9 + 7;
const int mxN = 2e5 + 5;
const i64 INF = 1e18;

// Helpers

template <class T>
struct rank<vector<T>>
    : std::integral_constant<std::size_t, rank<T>::value + 1> {};

template <class T, size_t N>
struct rank<array<T, N>>
    : std::integral_constant<std::size_t, rank<T>::value + 1> {};

template <typename T>
struct rank<T const> : rank<T> {};

template <typename T>
struct rank<T&> : rank<T> {};

template <typename T>
struct rank<T&&> : rank<T> {};

template <typename T>
struct is_std_vector : false_type {};

template <typename T>
struct is_std_vector<vector<T>> : true_type {};

template <typename T>
struct is_std_vector<T const> : is_std_vector<T> {};

template <typename T>
struct is_std_vector<T&> : is_std_vector<T> {};

template <typename T>
struct is_std_vector<T&&> : is_std_vector<T> {};

template <typename T>
constexpr bool is_std_vector_v = is_std_vector<T>::value;

template <typename T>
struct is_std_array : false_type {};

template <typename T, size_t N>
struct is_std_array<array<T, N>> : true_type {};

template <typename T>
struct is_std_array<T const> : is_std_array<T> {};

template <typename T>
struct is_std_array<T&> : is_std_array<T> {};

template <typename T>
struct is_std_array<T&&> : is_std_array<T> {};

template <typename T>
constexpr bool is_std_array_v = is_std_array<T>::value;

template <typename T, typename = void>
struct is_iterable : false_type {};

template <typename T>
struct is_iterable<T, std::void_t<decltype(std::begin(std::declval<T>()),
                                           std::end(std::declval<T>()))>>
    : true_type {};

template <typename T>
constexpr bool is_iterable_v = is_iterable<T>::value;

template <typename T, typename = void>
struct is_to_stringable : false_type {};

template <typename T>
struct is_to_stringable<T, std::void_t<decltype(to_string(std::declval<T>()))>>
    : true_type {};

template <typename T>
constexpr bool is_to_stringable_v = is_to_stringable<T>::value;

template <typename T, typename = void>
struct has_ToString : false_type {};

template <typename T>
struct has_ToString<T, std::void_t<decltype(std::declval<T>().ToString())>>
    : true_type {};

template <typename T>
constexpr bool has_ToString_v = has_ToString<T>::value;
// NOLINTEND

// ToString
template <typename T>
enable_if_t<is_to_stringable_v<T>, string> ToString(const T&);

template <typename T>
enable_if_t<has_ToString_v<T>, string> ToString(const T&);

template <typename T>
enable_if_t<is_std_array_v<T> || is_std_vector_v<T>, string> ToString(const T&);

template <typename T>
enable_if_t<!is_std_array_v<T> && !is_std_vector_v<T> && is_iterable_v<T>,
            string>
ToString(const T&);

string ToString(char c) {
  return string(1, c);
}
string ToString(bool b) {
  return b ? "true" : "false";
}
string ToString(const char* s) {
  return string(s);
}
string ToString(const string& s) {
  return s;
}
string ToString(const vector<bool>& v) {
  string result;
  for (const auto& x : v) {
    result += char('0' + static_cast<int>(x));
  }
  return result;
}

template <size_t N>
string ToString(const bitset<N>& b) {
  return b.ToString();
}

template <class T1, class T2>
string ToString(const pair<T1, T2>& p) {
  return "(" + ToString(p.first) + ", " + ToString(p.second) + ")";
}

template <typename T>
enable_if_t<is_to_stringable_v<T>, string> ToString(const T& value) {
  // return "to_stringable";
  return to_string(value);
}

template <typename T>
enable_if_t<has_ToString_v<T>, string> ToString(const T& value) {
  // return "has_ToString";
  return value.toString();
}

template <class T>
enable_if_t<is_std_array_v<T> || is_std_vector_v<T>, string> ToString(
    const T& arr_or_vec) {
  stringstream result;
  result << "[";
  for (int i = 0; i < int(arr_or_vec.size()); ++i) {
    if constexpr (rank_v<decltype(arr_or_vec[i])> > 0) {
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
enable_if_t<!is_std_array_v<T> && !is_std_vector_v<T> && is_iterable_v<T>,
            string>
ToString(const T& iterable) {
  stringstream result;
  result << "{";
  int i = 0;
  for (const auto& entry : iterable) {
    if constexpr (rank_v<decltype(entry)> > 0) {
      result << "\n";
    }
    result << ToString(entry);
    result << (i == int(iterable.size()) - 1 ? "" : ", ");
    ++i;
  }
  result << "}";
  return result.str();
}

void DBG() {
}
template <class Head, class... Tail>
void DBG(Head h, Tail... t) {
  cerr << ToString(h);
  if (sizeof...(t)) {
    cerr << ", ";
  }
  DBG(t...);
}
#ifdef LOCAL_DEBUG
#define dbg(...)                                                     \
  cerr << "LINE(" << __LINE__ << ") -> [" << #__VA_ARGS__ << "]: ["; \
  DBG(__VA_ARGS__);                                                  \
  cerr << "]\n";
#else
#define dbg(...) 0
#endif
