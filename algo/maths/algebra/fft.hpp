#pragma once

#include <algorithm>
#include <cassert>
#include <complex>
#include <vector>

namespace algo::maths::algebra {
struct FFT {
  // NOLINTBEGIN
  using ld = long double;
  using clx = std::complex<ld>;
  // use 15-17 locally if SEGFAULT
  static const int mxK = 19;
  static const int mxN = 1 << mxK;
  // NOLINTEND
  clx unity_root[mxN];
  int pos[mxN];
  const ld PI = acos((ld)-1);

  FFT() {
    int n = mxN, k = mxK;
    for (int i = 0; i < n; ++i) {
      ld angle = (2 * PI * i) / n;
      unity_root[i] = {cos(angle), sin(angle)};
    }

    pos[0] = 0;
    int pow_2 = 0;
    for (int i = 1; i < n; ++i) {
      if ((i & (1 << pow_2)) != 0) {
        pow_2++;
      }
      int t = i ^ (1 << (pow_2 - 1));
      pos[i] = pos[t] | (1 << (k - pow_2));
    }
  }

  void DoFFT(std::vector<clx>& res, std::vector<clx> const& a) {
    int n = res.size(), k = mxK;
    //  for simplicity always use mxN vectors (mxN-1 order polynom)
    assert(n == mxN);
    for (int i = 0; i < n; ++i) {
      res[pos[i]] = a[i];
    }
    for (int lvl = 0; lvl < k; ++lvl) {
      int block = 1 << lvl;
      int root_shift = (1 << (k - lvl - 1));
      for (int st = 0; st < n; st += (block << 1)) {
        for (int j = 0; j < block; ++j) {
          clx x = unity_root[j * root_shift];
          clx f = res[st + j] + x * res[st + block + j];
          clx s = res[st + j] - x * res[st + block + j];
          res[st + j] = f;
          res[st + block + j] = s;
        }
      }
    }
  }

  void DoInverseFFT(std::vector<clx>& res, std::vector<clx>& a) {
    DoFFT(res, a);
    std::reverse(res.begin() + 1, res.end());
    int n = res.size();
    for (int i = 0; i < n; ++i) {
      res[i] /= n;
    }
  }
};

}  // namespace algo::maths::algebra
