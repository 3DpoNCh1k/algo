#pragma once

#include <algo/utils/types.hpp>
#include <vector>

// Verification:
// https://codeforces.com/group/CYMPFXi8zA/contest/240094/problem/B
namespace algo::trees {
using utils::i64;
struct Fenwick {
  std::vector<i64> a;
  int n;

  explicit Fenwick(int n): n(n) {
    a.assign(n, 0);
  }

  int GetLen(int i) {
    return ((i + 1) ^ i) & (i + 1);
  };

  void Add(int i, i64 val) {
    while (i < n) {
      a[i] += val;
      i += GetLen(i);
    }
  };

  i64 Sum(int i) {
    i64 ans = 0;
    while (i >= 0) {
      ans += a[i];
      i -= GetLen(i);
    }
    return ans;
  };

  void SetValue(int i, i64 val) {
    Add(i, (val - (Sum(i) - Sum(i - 1))));
  };

  i64 GetSum(int l, int r) {
    return Sum(r) - Sum(l - 1);
  };

  i64 GetValue(int i) {
    return GetSum(i, i);
  };
};

struct Fenwick3D {
  static const int mxN = 128 + 5;
  int a[mxN][mxN][mxN];

  void Add(int x, int y, int z, int val) {
    int i, j, k;
    for (i = x; i < mxN; i |= (i + 1)) {
      for (j = y; j < mxN; j |= (j + 1)) {
        for (k = z; k < mxN; k |= (k + 1)) {
          a[i][j][k] += val;
        }
      }
    }
  }

  int Get(int x, int y, int z) {
    if (x < 0 || y < 0 || z < 0) {
      return 0;
    }
    int res = 0;
    int i, j, k;
    for (i = x; i >= 0; i = (i & (i + 1)) - 1) {
      for (j = y; j >= 0; j = (j & (j + 1)) - 1) {
        for (k = z; k >= 0; k = (k & (k + 1)) - 1) {
          res += a[i][j][k];
        }
      }
    }

    return res;
  }
};

}  // namespace algo::trees
