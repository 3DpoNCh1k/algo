#pragma once

#include <algorithm>
#include <cstdint>
#include <iostream>
#include <istream>

namespace algo::utils {
// NOLINTBEGIN
#ifdef __SIZEOF_INT128__
using int128_t = __int128;
using uint128_t = unsigned __int128;

namespace operators {
namespace details {
uint128_t ParseValue(std::string s) {
  uint128_t value = 0;
  for (int i = 0; i < s.size(); ++i) {
    value = value * 10 + (s[i] - '0');
  }
  return value;
}
}  // namespace details

std::istream& operator>>(std::istream& in, int128_t& value) {
  std::string s;
  in >> s;
  bool is_negative = s[0] == '-';
  int start = is_negative ? 1 : 0;
  value = details::ParseValue(s.substr(start));
  if (is_negative) {
    value *= -1;
  }
  return in;
}

std::istream& operator>>(std::istream& in, uint128_t& value) {
  std::string s;
  in >> s;
  value = details::ParseValue(s);
  return in;
}

std::string to_string(uint128_t value) {
  std::string s;
  do {
    s.push_back(value % 10 + '0');
    value /= 10;
  } while (value != 0);
  std::reverse(s.begin(), s.end());
  return s;
}

std::string to_string(const int128_t& value) {
  auto sign = value < 0 ? "-" : "";
  uint128_t absolute_value = value < 0 ? value * -1 : value;
  return sign + to_string(absolute_value);
}

std::ostream& operator<<(std::ostream& out, const int128_t& value) {
  out << to_string(value);
  return out;
}

std::ostream& operator<<(std::ostream& out, const uint128_t& value) {
  out << to_string(value);
  return out;
}
}  // namespace operators

using i128 = int128_t;
using u128 = uint128_t;
#else
// TODO: add naive implementation for any big integers
#endif
// NOLINTEND
}  // namespace algo::utils

// NOLINTNEXTLINE
using namespace algo::utils::operators;
