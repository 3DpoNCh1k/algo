#pragma once

#include "../header.hpp"

// Verification:
// https://codeforces.com/group/CYMPFXi8zA/contest/261526/problem/F

struct SuffixTree {
  int mxN = 2e5 + 100;  // ! in constructor
  const int AS = 128;
  const int ROOT = 1;
  int INF = 1e9;
  int cnt = 2;
  string s;
  int type = 1;

  struct Node {
    Node() {
    }
    Node(int par, int left, int right, int leaf = 0, int ref = 0)
        : par(par),
          left(left),
          right(right),
          leaf(leaf),
          ref(ref) {
    }
    int par = 0, left = 0, right = -1, leaf = 0, ref = 0;
    map<char, int> to;
  };

  vector<Node> tree;

  // see solve()
  explicit SuffixTree(int mxN)
      : mxN(mxN) {
    tree.resize(mxN);
  };

  int Len(int v) {
    return tree[v].right - tree[v].left + 1;
  }
  int cur_v, cur_p;  // number of read chars on edge already

  void Go(int u, int i) {
    assert(u && u != ROOT);
    int par = tree[u].par;  // root.ref = root
    int k = tree[u].right - tree[u].left + 1;
    if (par == ROOT) {
      --k;
    }
    int v = tree[par].ref;
    cur_p = k;
    while (k != 0) {
      // we sure about transitions
      v = tree[v].to[s[tree[u].right - k + 1]];
      if (Len(v) < k) {
        k -= Len(v);
      } else {
        cur_p = k;
        k = 0;
      }
    }
    cur_v = v;
    if (cur_p == Len(cur_v)) {
      // we are in already existing node cur_v
      tree[u].ref = cur_v;
    } else {
      // we are on edge -> in next step we'll create node cnt
      tree[u].ref = cnt;
    }
  }

  void Add(int i) {
    char c = s[i];
    while (true) {
      if (cur_p == Len(cur_v)) {
        if (tree[cur_v].to[c] != 0) {
          cur_v = tree[cur_v].to[c], cur_p = 1;
          break;
        } else {
          // (par, left, right, leaf, ref=0)
          tree[cnt] = Node(cur_v, i, INF, type);
          tree[cur_v].to[c] = cnt;
          cnt++;
          if (cur_v == ROOT) {
            assert(cur_p == 0);
            cur_p = 0;
            break;
          }
          if (tree[cur_v].ref != 0) {  // it is node, not leaf
            cur_v = tree[cur_v].ref;
            cur_p = Len(cur_v);
          } else {
            // it'll update cur_v and cur_p and make ref for old cur_v
            Go(cur_v, i);
          }
        }
      } else {
        int prev_pos = tree[cur_v].left + cur_p - 1;
        if (s[prev_pos + 1] == c) {
          cur_p++;
          break;
        } else {
          // PARENT FOR CUR
          tree[cnt] = Node(tree[cur_v].par, tree[cur_v].left, prev_pos, 0);
          // update previous parent of cur
          tree[tree[cur_v].par].to[s[tree[cur_v].left]] = cnt;
          tree[cnt].to[s[prev_pos + 1]] = cur_v;
          tree[cur_v].par = cnt, tree[cur_v].left = prev_pos + 1;
          cnt++;
          tree[cnt] = Node(cnt - 1, i, INF, type);  // LEAF
          tree[cnt - 1].to[s[i]] = cnt;
          cnt++;
          Go(cnt - 2, i);  // cant be root case
        }
      }
    }
    if (c < 15) {  // TASK dependent
      type <<= 1;  // distinguish strings by their leaves type
    }
  }

  // TASK depenndent
  int k;  // # of strings
  int mxlen = 0, ind = -1;
  int dfs(int v, int curlen) {
    int cur_mask = tree[v].leaf;
    if (cur_mask == 0) {
      int mylen = Len(v);
      for (auto e : tree[v].to) {  // lexicographical order (from a..z)
        cur_mask |= dfs(e.second, curlen + mylen);
      }
      if (cur_mask == ((1 << k) - 1)) {
        if (mylen + curlen > mxlen) {
          mxlen = mylen + curlen;
          ind = v;
        }
      }
    }
    return cur_mask;
  }

  // TASK dependent
  // EXAMPLE: find longest (if some - lexicographically smallest) substr, which
  // exists in every input string
  void Solve() {
    tree[ROOT].ref = ROOT;
    int n, i;
    cin >> k;
    string t;
    for (i = 0; i < k; ++i) {
      cin >> t;
      t.push_back(i);
      s += t;
    }
    n = s.size();
    INF = n - 1;
    cur_v = ROOT;
    cur_p = 0;
    for (i = 0; i < n; ++i) {
      Add(i);
    }

    if (dfs(ROOT, 0) == ((1 << k) - 1)) {
      vector<string> vans;
      while (ind != ROOT) {
        vans.push_back(s.substr(tree[ind].left, Len(ind)));
        ind = tree[ind].par;
      }
      string ans;
      for (i = vans.size() - 1; i >= 0; --i) {
        ans += vans[i];
      }
      cout << ans;
    } else {
      cout << endl;
    }
  }
};
