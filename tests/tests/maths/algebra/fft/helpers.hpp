#pragma once

#include <cstdlib>
#include <vector>

#include <algo/maths/algebra/fft/fft.hpp>
#include <algo/maths/constants.hpp>

using FFT = algo::maths::algebra::fft::FFT;
using Coefficient = FFT::Coefficient;
using Value = FFT::Value;

std::vector<int> AsInts(const std::vector<Complex>& a) {
  std::vector<int> b(a.size());
  for (int i = 0; i < a.size(); ++i) {
    b[i] = std::round(a[i].real());
  }
  return b;
}

std::vector<Complex> AsComplexes(const std::vector<int>& a) {
  std::vector<Complex> b(a.size());
  for (int i = 0; i < a.size(); ++i) {
    b[i] = Complex(a[i], 0);
  }
  return b;
}

bool AreEqual(Complex a, Complex b, Real eps = 1e-6) {
  return std::abs(a.real() - b.real()) <= eps &&
         std::abs(a.imag() - b.imag()) <= eps;
};

bool AreEqual(std::vector<Complex> a, std::vector<Complex> b) {
  bool ok = a.size() == b.size();
  for (int i = 0; ok && i < a.size(); ++i) {
    ok &= AreEqual(a[i], b[i]);
  }
  return ok;
};
