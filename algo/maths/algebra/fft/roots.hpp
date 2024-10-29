#pragma once

#include <vector>
#include <algo/utils/types/fundamentals.hpp>
#include <algo/maths/constants.hpp>

namespace algo::maths::algebra::fft {
std::vector<Complex> UnityRoots(int degree) {
  std::vector<Complex> roots(degree);
  for (int i = 0; i < degree; ++i) {
    auto angle = 2 * algo::maths::PI * i / degree;
    roots[i] = {cos(angle), sin(angle)};
  }
  return roots;
};
}  // namespace algo::maths::algebra::fft
