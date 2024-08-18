#pragma once

#include <algo/utils/types/fundamentals.hpp>
#include "algo/maths/algebra/details/fft_impl.hpp"
#include "algo/maths/algebra/fft/roots.hpp"

namespace algo::maths::algebra::fft {
struct FastFourierTransform : details::FastFourierTransformImpl<Complex> {
  explicit FastFourierTransform(int n)
      : details::FastFourierTransformImpl<Complex>(UnityRoots(n)) {
  }
};

using FFT = FastFourierTransform;
}  // namespace algo::maths::algebra::fft
