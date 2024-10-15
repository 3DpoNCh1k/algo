#pragma once

#include <algo/maths/geometry/point.hpp>

namespace algo::maths::geometry {
template <typename T>
using Vector = Point<T>;

template <typename T>
Vector<T> operator+(const Vector<T>& a, const Vector<T>& b) {
  return Vector<T>(a.x + b.x, a.y + b.y);
};

template <typename T>
Vector<T> operator-(const Vector<T>& a) {
  return Vector<T>(-a.x, -a.y);
};

template <typename T>
Vector<T> operator-(const Vector<T>& a, const Vector<T>& b) {
  return a + (-b);
};

template <typename T>
T Cross(const Vector<T>& a, const Vector<T>& b) {
  return a.x * b.y - a.y * b.x;
}

template <typename T>
T Dot(const Vector<T>& a, const Vector<T>& b) {
  return a.x * b.x + a.y * b.y;
}

template <typename T>
T Clockwise(const Vector<T>& a, const Vector<T>& b) {
  return Cross(a, b) < 0;
}

template <typename T>
T CounterClockwise(const Vector<T>& a, const Vector<T>& b) {
  return Cross(a, b) > 0;
}

template <typename T>
T Clockwise(const Point<T>& a, const Point<T>& b, const Point<T>& c) {
  return Clockwise(b - a, c - a);
}

template <typename T>
T CounterClockwise(const Point<T>& a, const Point<T>& b, const Point<T>& c) {
  return CounterClockwise(b - a, c - a);
}
}  // namespace algo::maths::geometry
