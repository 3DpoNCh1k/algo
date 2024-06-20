#pragma once

#include "../utils/types.hpp"

// Verification:
// https://codeforces.com/group/CYMPFXi8zA/contest/240094/problem/B

struct Fenwick {
  static const int mxN = 5e5 + 10;
  i64 a[mxN];

  int GetLen(int i) {
    return ((i + 1) ^ i) & (i + 1);
  };

  void Add(int i, i64 val) {
    while (i < mxN) {
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
