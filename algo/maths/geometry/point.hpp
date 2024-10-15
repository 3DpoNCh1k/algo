#pragma once

namespace algo::maths::geometry {
template <typename T>
struct Point {
  T x, y;
  Point(T x, T y)
      : x(x),
        y(y){};

  bool operator==(const Point& that) const {
    return x == that.x && y == that.y;
  }
  bool operator!=(const Point& that) const {
    return !(*this == that);
  }
};
}  // namespace algo::maths::geometry
