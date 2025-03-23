#pragma once

#include <algorithm>
#include <cassert>
#include <cmath>
#include <vector>
#include "algo/maths/geometry/point.hpp"

namespace algo::misc {
namespace details {
template <typename T>
struct Mo {
  using Point = algo::maths::geometry::Point<T>;
  explicit Mo(const std::vector<Point>& points0)
      : points(points0) {
  }

  std::vector<int> Order() {
    int n = points.size();

    if (n == 0) {
      return {};
    }

    auto [min_it, max_it] = std::minmax_element(
        points.begin(), points.end(), [](const auto& p0, const auto& p1) {
          return p0.x < p1.x;
        });

    auto min_x = min_it->x;
    auto max_x = max_it->x;

    auto k = std::max(int(std::sqrt(max_x - min_x)), 1);

    std::vector<std::pair<int, Point>> order;
    for (int i = 0; i < n; ++i) {
      order.push_back({i, points[i]});
    }

    std::sort(order.begin(), order.end(),
              [&min_x, &k](const auto& p0, const auto& p1) {
                auto [x0, y0] = p0.second;
                auto [x1, y1] = p1.second;

                return ((x0 + min_x) / k == (x1 + min_x) / k) ? y0 < y1
                                                              : x0 < x1;
              });

    std::vector<int> answer;
    for (const auto& p : order) {
      answer.push_back(p.first);
    }

    return answer;
  }

  const std::vector<Point>& points;
};
}  // namespace details

template <typename Index>
auto Mo(std::vector<std::pair<Index, Index>> segments) {
  std::vector<algo::maths::geometry::Point<Index>> points;
  for (int i = 0; i < segments.size(); ++i) {
    points.push_back(
        maths::geometry::Point<Index>(segments[i].first, segments[i].second));
  }
  return details::Mo(points).Order();
};

template <typename T>
auto Mo(const std::vector<algo::maths::geometry::Point<T>>& points) {
  return details::Mo(points).Order();
};

}  // namespace algo::misc
