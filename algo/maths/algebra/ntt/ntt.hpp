#pragma once

#include <algo/maths/algebra/details/fft_impl.hpp>

namespace algo::maths::algebra::ntt {
template <typename Modular>
using NumberTheoreticTransform = details::FastFourierTransformImpl<Modular>;

template <typename Modular>
using NTT = NumberTheoreticTransform<Modular>;
}  // namespace algo::maths::algebra::ntt
