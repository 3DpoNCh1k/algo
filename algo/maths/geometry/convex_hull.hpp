#pragma once

#include <vector>
#include "algo/maths/geometry/point.hpp"
#include "algo/maths/geometry/vector.hpp"

namespace algo::maths::geometry {

template <typename T>
std::vector<Point<T>> ConvexHull(std::vector<Point<T>> points) {
  if (points.size() <= 1) {
    return points;
  }

  sort(points.begin(), points.end(), [&](const auto& a, const auto& b) {
    return a.x < b.x || a.x == b.x && a.y < b.y;
  });

  auto p1 = points[0];
  auto p2 = points.back();
  std::vector<Point<T>> up, down;
  up.push_back(p1);
  down.push_back(p1);

  for (int i = 1; i < points.size(); ++i) {
    if (i == points.size() - 1 || Clockwise(p1, points[i], p2)) {
      while (up.size() >= 2 &&
             !Clockwise(up[up.size() - 2], up[up.size() - 1], points[i])) {
        up.pop_back();
      }
      up.push_back(points[i]);
    }
    if (i == points.size() - 1 || CounterClockwise(p1, points[i], p2)) {
      while (down.size() >= 2 &&
             !CounterClockwise(down[down.size() - 2], down[down.size() - 1],
                               points[i])) {
        down.pop_back();
      }
      down.push_back(points[i]);
    }
  }

  std::vector<Point<T>> convex_hull;

  for (int i = 0; i < up.size(); ++i) {
    convex_hull.push_back(up[i]);
  };

  for (int i = down.size() - 2; i > 0; --i) {
    convex_hull.push_back(down[i]);
  };

  return convex_hull;
}

}  // namespace algo::maths::geometry
