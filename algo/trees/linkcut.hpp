#pragma once

#include <algorithm>
#include <cassert>
#include <string>
#include <vector>

// Verification:
// https://codeforces.com/group/CYMPFXi8zA/contest/243321/problem/H

// retrograd's implementation https://codeforces.com/blog/entry/75885

// with lca method and modified Access

namespace algo::trees {
struct LinkCut {
  struct Node {
    int p = 0, c[2] = {0, 0}, pp = 0;
    bool flip = false;
    int val = 0, dp = 0;
  };
  std::vector<Node> T;

  // 1 indexed, cuz node 0 - like neutral element
  explicit LinkCut(int n)
      : T(n + 1) {
  }

  // SPLAY TREE OPERATIONS START

  int Dir(int x, int y) {
    return static_cast<int>(T[x].c[1] == y);
  }

  void Set(int x, int d, int y) {
    if (x != 0) {
      T[x].c[d] = y, Pull(x);
    }
    if (y != 0) {
      T[y].p = x;
    }
  }

  void Pull(int x) {
    if (x == 0) {
      return;
    }
    int &l = T[x].c[0], &r = T[x].c[1];
    T[x].dp = std::max({T[x].val, T[l].dp, T[r].dp});
  }

  void Push(int x) {
    if ((x == 0) || !T[x].flip) {
      return;
    }
    int &l = T[x].c[0], &r = T[x].c[1];
    std::swap(l, r);
    T[l].flip ^= 1;
    T[r].flip ^= 1;
    T[x].flip = false;
  }

  void Rotate(int x, int d) {
    int y = T[x].p, z = T[y].p, w = T[x].c[d];
    std::swap(T[x].pp, T[y].pp);
    Set(y, static_cast<int>(d == 0), w);
    Set(x, d, y);
    Set(z, Dir(z, y), x);
  }

  void Splay(int x) {
    for (Push(x); T[x].p != 0;) {
      int y = T[x].p, z = T[y].p;
      Push(z);
      Push(y);
      Push(x);
      int dx = Dir(y, x), dy = Dir(z, y);
      if (z == 0) {
        Rotate(x, static_cast<int>(dx == 0));
      } else if (dx == dy) {
        Rotate(y, static_cast<int>(dx == 0));
        Rotate(x, static_cast<int>(dx == 0));
      } else {
        Rotate(x, dy), Rotate(x, dx);
      }
    }
  }

  // SPLAY TREE OPERATIONS END

  void MakeRoot(int u) {
    Access(u);
    int l = T[u].c[0];
    T[l].flip ^= 1;
    std::swap(T[l].p, T[l].pp);
    Set(u, 0, 0);
  }

  int Access(int _u) {
    int u, v;
    for (v = 0, u = _u; u != 0; u = T[v = u].pp) {
      Splay(u);
      Splay(v);
      int r = T[u].c[1];
      T[v].pp = 0;
      std::swap(T[r].p, T[r].pp);
      Set(u, 1, v);
    }
    Splay(_u);
    assert(T[_u].c[1] == 0);
    return v;
  }

  void Link(int u, int v) {
    assert(!Connected(u, v));
    MakeRoot(u);
    T[u].pp = v;
  }

  void Cut(int u, int v) {
    MakeRoot(u);
    Access(u);
    Splay(v);
    assert(T[v].pp == u);
    T[v].pp = 0;
  }

  bool Connected(int u, int v) {
    if (u == v) {
      return true;
    }
    MakeRoot(u);
    Access(v);
    return (T[u].p != 0) || (T[u].pp != 0);
  }

  int GetPath(int u, int v) {
    MakeRoot(u);
    Access(v);
    return v;
  }

  int GetLCA(int u, int v) {
    Access(u);
    return Access(v);
  }

  std::string ToString() {
    // TODO
    return "";
  }
};

}  // namespace algo::trees
