#ifndef LINKCUT_HPP
#define LINKCUT_HPP

// Verification: https://codeforces.com/group/CYMPFXi8zA/contest/243321/problem/H

// retrograd's implementation https://codeforces.com/blog/entry/75885

// with lca method and modified Access 

#include <bits/stdc++.h>
 
using namespace std;
 
 
struct LinkCut {
  struct Node {
    int p = 0, c[2] = {0, 0}, pp = 0;
    bool flip = 0;
    int val = 0, dp = 0;
  };
  vector<Node> T;
 
  LinkCut(int n) : T(n + 1) {} // 1 indexed, cuz node 0 - like neutral element
 
  // SPLAY TREE OPERATIONS START

  int dir(int x, int y) { return T[x].c[1] == y; }
 
  void set(int x, int d, int y) {
    if (x) T[x].c[d] = y, pull(x);
    if (y) T[y].p = x;
  }
 
  void pull(int x) {
    if (!x) return;
    int &l = T[x].c[0], &r = T[x].c[1];
    T[x].dp = max({T[x].val, T[l].dp, T[r].dp});
  }
 
  void push(int x) {
    if (!x || !T[x].flip) return;
    int &l = T[x].c[0], &r = T[x].c[1];
    swap(l, r); T[l].flip ^= 1; T[r].flip ^= 1;
    T[x].flip = 0;
  }
 
  void rotate(int x, int d) { 
    int y = T[x].p, z = T[y].p, w = T[x].c[d];
    swap(T[x].pp, T[y].pp);
    set(y, !d, w);
    set(x, d, y);
    set(z, dir(z, y), x);
  }
 
  void splay(int x) { 
    for (push(x); T[x].p;) {
      int y = T[x].p, z = T[y].p;
      push(z); push(y); push(x);
      int dx = dir(y, x), dy = dir(z, y);
      if (!z) 
        rotate(x, !dx); 
      else if (dx == dy) 
        rotate(y, !dx), rotate(x, !dx); 
      else
        rotate(x, dy), rotate(x, dx);
    }
  }
 
  // SPLAY TREE OPERATIONS END
 
  void MakeRoot(int u) {
    Access(u);
    int l = T[u].c[0];
    T[l].flip ^= 1;
    swap(T[l].p, T[l].pp);
    set(u, 0, 0);
  }
 
  int Access(int _u) {
	int u, v;
    for (v = 0, u = _u; u; u = T[v = u].pp) {
      splay(u); splay(v);
      int r = T[u].c[1];
      T[v].pp = 0;
      swap(T[r].p, T[r].pp);
      set(u, 1, v);
    }
    splay(_u);
	assert(T[_u].c[1]==0);
	return v;
  }

  void Link(int u, int v) { 
    assert(!Connected(u, v));
    MakeRoot(u);
    T[u].pp = v;
  }

  void Cut(int u, int v) {
    MakeRoot(u); Access(u);	splay(v);
    assert(T[v].pp == u);
    T[v].pp = 0;
  }

  bool Connected(int u, int v) {
    if (u == v) return true;
	MakeRoot(u); Access(v);
	return T[u].p || T[u].pp; 
  }

  int GetPath(int u, int v) {
    MakeRoot(u); Access(v); return v;
  }
  
  int lca(int u, int v) {
	  Access(u);
	  return Access(v);
  }
  
  //void print() {
	  //int n = T.size();
	  //cout << "PRINT\n";
	  //for(int i = 0; i < n; ++i) {
		  //cout << "i: " << i << " p = " << T[i].p << " left = " << T[i].c[0] \
				//<< " right = " << T[i].c[1] << " pp = " << T[i].pp << "\n"; 
	  //}
  //}
  
};



#endif
