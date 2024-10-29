#pragma once

#include <algorithm>
#include <limits>
#include <sstream>
#include <vector>
#include <cassert>
#include <algo/binary_search/binary_search.hpp>
#include <algo/utils/types/fundamentals.hpp>

namespace algo::data_structures::cht {

template <bool is_minimum, typename T = i64>
struct ConvexHullTrick {
  static constexpr bool IsMinimum = is_minimum;

  struct Line {
    T k, b;
    Line()
        : Line(0, 0) {
    }

    Line(T k, T b)
        : k(k),
          b(b) {
    }

    T Calculate(T x) const {
      return b + k * x;
    }

    bool operator<(const Line& that) const {
      if constexpr (IsMinimum) {
        return k == that.k ? b < that.b : k > that.k;
      } else {
        return k == that.k ? b > that.b : k < that.k;
      }
    }

    bool operator==(const Line& that) const {
      return k == that.k && b == that.b;
    }

    bool operator!=(const Line& that) const {
      return !(*this == that);
    }

    std::string ToString() const {
      std::stringstream ss;
      ss << "Line: k = " << k << " b = " << b;
      return ss.str();
    }
  };

  // Checks if intersection of (a, b) is on the left from (a, c)
  static bool Check(const Line& a, const Line& b, const Line& c) {
    // (b.b - a.b) / (a.k - b.k) < (c.b - a.b) / (a.k - c.k)
    bool sign = (b.b - a.b) * (a.k - c.k) < (c.b - a.b) * (a.k - b.k);
    bool change_sign = ((a.k - b.k) < 0) ^ ((a.k - c.k) < 0);
    return sign ^ change_sign;
  }

  // Checks if intersection of (a, b) is on the left from x
  static bool Check(const Line& a, const Line& b, T x) {
    // (b.b - a.b) / (a.k - b.k) < x
    bool sign = (b.b - a.b) < (a.k - b.k) * x;
    bool change_sign = (a.k - b.k) < 0;
    return sign ^ change_sign;
  }

  std::vector<Line> hull;
  void Add(Line l) {
    while ((hull.size()) >= 2 &&
           !Check(hull[hull.size() - 2], hull[hull.size() - 1], l)) {
      hull.pop_back();
    }
    hull.push_back(l);
  }

  int GetIndex(T x) const {
    if (hull.empty()) {
      return -1;
    }
    const auto& const_hull_ref = hull;
    int idx = binary_search::FindLastTrue(
        1, hull.size() - 1, [&const_hull_ref, x](int m) {
          return Check(const_hull_ref[m - 1], const_hull_ref[m], x);
        });
    assert(idx >= 0 && idx < hull.size());
    return idx;
  }

  auto GetValue(i64 x) const {
    if (hull.empty()) {
      if constexpr (IsMinimum) {
        return std::numeric_limits<T>::max();
      }
      return std::numeric_limits<T>::min();
    }
    int idx = GetIndex(x);
    return hull[idx].Calculate(x);
  }

  ConvexHullTrick() {
  }
  explicit ConvexHullTrick(std::vector<Line> lines) {
    std::sort(lines.begin(), lines.end());
    auto it = std::unique(lines.begin(), lines.end(),
                          [](const Line& a, const Line& b) {
                            return a.k == b.k;
                          });
    lines.erase(it, lines.end());
    for (Line& l : lines) {
      Add(l);
    }
  }

  explicit ConvexHullTrick(Line line) {
    Add(line);
  }

  ConvexHullTrick(const ConvexHullTrick& a, const ConvexHullTrick& b) {
    std::vector<Line> lines;
    lines.resize(a.hull.size() + b.hull.size(), Line(0, 0));
    std::merge(a.hull.begin(), a.hull.end(), b.hull.begin(), b.hull.end(),
               lines.begin());
    auto it = std::unique(lines.begin(), lines.end(),
                          [](const Line& a, const Line& b) {
                            return a.k == b.k;
                          });
    lines.erase(it, lines.end());
    for (Line& l : lines) {
      Add(l);
    }
  }
};

template <typename T = i64>
using MinimumCHT = ConvexHullTrick<true, T>;

template <typename T = i64>
using MaximumCHT = ConvexHullTrick<false, T>;

}  // namespace algo::data_structures::cht
