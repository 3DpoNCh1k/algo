#pragma once

#include <cassert>
#include <string>
#include <vector>

#include <algo/utils/types.hpp>

// Verification:
// https://codeforces.com/group/CYMPFXi8zA/contest/240094/problem/C
namespace algo::trees {
  using utils::i64;
struct LazySegmentTree {
  static const i64 INF = 1e18 + 100;
  // EXAMPLE: size, minimum, its count and one of its position

  struct Node {
    Node() {
      // Neutral element
      min_value = INF, pos = 1e9, cnt = 1, sz = 1;
    };
    Node(i64 val, int pos, int cnt = 1)
        : min_value(val),
          pos(pos),
          cnt(cnt){};
    int pos, cnt = 1, sz = 1;
    i64 min_value = INF;
    i64 lazy_add = 0;       // add value to elements of the node's segment
    i64 lazy_set_flag = 0;  // 0/1; 1 - set value to childs
    i64 lazy_set = 0;
  };
  std::vector<Node> T;
  int n, B;

  explicit LazySegmentTree(const std::vector<int>& a) {
    n = a.size();
    B = 1;
    while (B < n) {
      B <<= 1;
    }
    T.assign(2 * B, {});
    for (int i = 0; i < n; ++i) {
      T[B + i].min_value = a[i];
      T[B + i].pos = i;
    }
    for (int i = B - 1; i > 0; --i) {
      Pull(i);
    }
  }

  // better than next pull (try not pull lazy_add...)
  void Pull(int i) {
    assert(i < B);
    int idx_min = 2 * i, idx_max = 2 * i + 1;
    if (T[idx_min].min_value > T[idx_max].min_value) {
      std::swap(idx_min, idx_max);
    }
    T[i].min_value = T[idx_min].min_value;
    T[i].pos = T[idx_min].pos;
    T[i].cnt = T[idx_min].cnt;
    if (T[i].min_value == T[idx_max].min_value) {
      T[i].cnt += T[idx_max].cnt;
    }
    T[i].sz = T[idx_min].sz + T[idx_max].sz;
  }

  //  for Query - ok
  Node Pull(Node a, Node b) {
    if (a.min_value > b.min_value) {
      std::swap(a, b);
    }
    if (a.min_value == b.min_value) {
      a.cnt += b.cnt;
    }
    a.sz += b.sz;
    return a;
  }

  void Actualize(int v) {
    // v is already good
    int left = 2 * v, right = 2 * v + 1;
    assert(left < 2 * B && right < 2 * B);
    if (T[v].lazy_set_flag != 0) {
      T[left].min_value = T[v].lazy_set;
      T[left].lazy_set_flag = 1;
      T[left].lazy_set = T[v].lazy_set;
      T[left].lazy_add = 0;
      T[right].min_value = T[v].lazy_set;
      T[right].lazy_set_flag = 1;
      T[right].lazy_set = T[v].lazy_set;
      T[right].lazy_add = 0;
      T[v].lazy_set_flag = 0;
    }
    if (T[v].lazy_add != 0) {
      T[left].min_value += T[v].lazy_add;
      T[left].lazy_add += T[v].lazy_add;
      T[right].min_value += T[v].lazy_add;
      T[right].lazy_add += T[v].lazy_add;
      T[v].lazy_add = 0;
    }
  };
  // [L, R] - node segment     [l, r] - query segment
  void Add(int v, int L, int R, int l, int r, i64 val) {
    // cout << "add " << v << " L " << L << " R " << R << " l " << l << " r " <<
    // r << " val " << val << "\n"; print();
    if (l > R || r < L) {
      return;
    }
    if (l <= L && R <= r) {
      T[v].min_value += val;
      T[v].lazy_add += val;
      return;
    }

    Actualize(v);
    int left = 2 * v, right = 2 * v + 1;
    int M = (L + R) / 2;
    Add(left, L, M, l, r, val);
    Add(right, M + 1, R, l, r, val);

    Pull(v);
  };

  void Set(int v, int L, int R, int l, int r, i64 val) {
    if (l > R || r < L) {
      return;
    }
    if (l <= L && R <= r) {
      T[v].min_value = val;
      T[v].cnt = T[v].sz;
      T[v].lazy_add = 0;
      T[v].lazy_set_flag = 1;
      T[v].lazy_set = val;
      return;
    }

    Actualize(v);
    int left = 2 * v, right = 2 * v + 1;
    int M = (L + R) / 2;
    Set(left, L, M, l, r, val);
    Set(right, M + 1, R, l, r, val);

    Pull(v);
  };

  // sz, min_val, cnt, pos
  Node Query(int v, int L, int R, int l, int r) {
    if (r < L || l > R) {
      return Node();
    }
    if (l <= L && R <= r) {
      return T[v];
    }

    Actualize(v);
    int left = 2 * v, right = 2 * v + 1;
    int M = (L + R) / 2;
    Node lans = Query(left, L, M, l, r);
    Node rans = Query(right, M + 1, R, l, r);

    return Pull(lans, rans);
  };

  i64 GetMin(int l, int r) {
    Node ans = Query(1, 0, B - 1, l, r);
    return ans.min_value;
  }

  void SetValue(int l, int r, i64 val) {
    Set(1, 0, B - 1, l, r, val);
  }
  void AddValue(int l, int r, i64 val) {
    Add(1, 0, B - 1, l, r, val);
  }

  std::string ToString() {
    // TODO
    return "";
  }
};
}
