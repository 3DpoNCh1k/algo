#pragma once

#include <cassert>
#include <iostream>
#include <queue>
#include <string>
#include <vector>

// Verification:
// https://codeforces.com/group/CYMPFXi8zA/contest/261526/problem/I

struct AhoCorasick {
  int mxN = 2e6;  // ! in constructor
  static const int AlphabetSize = 26;
  const int ROOT = 1;  // !
  int cnt = 2;

  struct Node {
    int ch, par, ref;
    int terminal;       // 0 - not terminal, else - string_id (1-indexed)
    int prev_terminal;  // nearest terminal node through refs to ROOT
    std::vector<int>
        next_terminals;    // nearests terminal nodes through refs to LEAVES
    int to[AlphabetSize];  // or use map
    int go[AlphabetSize];
  };

  std::vector<Node> trie;

  std::vector<int> copy_s, left_index, right_index, st_to_node, visited, st_sz;

  // TASK dependent
  // copy_s - if there are duplicate pattern strings in input
  // left_index - most left entry of pattern in text string
  // right_index
  // st_to_node - map[patter_string_id] = node_id
  // visited - for cache computing
  // sz_sz - sizes of pattern strings

  // see make_trie and solve

  // see solve
  explicit AhoCorasick(int mxN)
      : mxN(mxN) {
    trie.resize(mxN);
  }

  void bfs(int r) {
    std::queue<int> q;
    q.push(r);
    while (!q.empty()) {
      int u = q.front();
      q.pop();
      for (int i = 0; i < AlphabetSize; ++i) {
        int v = trie[u].to[i];
        if (v != 0) {
          int prev_ref = trie[u].ref;
          while (prev_ref != ROOT && trie[prev_ref].to[i] == 0) {
            prev_ref = trie[prev_ref].ref;
          }
          if ((trie[prev_ref].to[i] != 0) && v != trie[prev_ref].to[i]) {
            trie[v].ref = trie[prev_ref].to[i];
          } else {
            trie[v].ref = ROOT;
          }

          trie[v].prev_terminal = trie[trie[v].ref].terminal != 0
                                      ? trie[v].ref
                                      : trie[trie[v].ref].prev_terminal;
          if (trie[v].terminal != 0) {
            trie[trie[v].prev_terminal].next_terminals.push_back(v);
          }

          q.push(v);
        }
      }
    }
  }

  int Go(int u, int i) {
    assert(u);
    if (u == ROOT) {
      trie[u].go[i] = trie[u].to[i];
      if (trie[u].go[i] == 0) {
        trie[u].go[i] = ROOT;
      }
    }
    if (trie[u].go[i] == 0) {
      if (trie[u].to[i] != 0) {
        trie[u].go[i] = trie[u].to[i];
      } else {
        trie[u].go[i] = Go(trie[u].ref, i);
      }
    }
    return trie[u].go[i];
  }

  // TASK dependent

  void Calc(int i) {
    if (visited[i] == 0) {
      visited[i] = 1;
      int u = st_to_node[i];
      for (int nx : trie[u].next_terminals) {
        Calc(trie[nx].terminal - 1);
      }
      for (int nx : trie[u].next_terminals) {
        left_index[i] = std::min(left_index[i], left_index[(trie[nx].terminal - 1)]);
        right_index[i] =
            std::max(right_index[i], right_index[(trie[nx].terminal - 1)]);
      }
    }
  }

  void MakeTrie(const std::vector<std::string>& vs) {
    trie[ROOT].ref = ROOT;
    int n = vs.size();  // # pattern strings
    copy_s.assign(n, -1), left_index.assign(n, mxN),
        right_index.assign(n, -mxN);
    st_to_node.assign(n, -1), visited.assign(n, 0), st_sz.assign(n, 0);

    for (int i = 0; i < n; ++i) {
      const std::string& s = vs[i];
      st_sz[i] = s.size();
      int cur_v = ROOT;
      for (char c : s) {
        if (trie[cur_v].to[c - 'a'] != 0) {
          cur_v = trie[cur_v].to[c - 'a'];
        } else {
          trie[cnt].ch = c;
          trie[cnt].par = cur_v;
          trie[cur_v].to[c - 'a'] = cnt;
          cur_v = cnt;
          ++cnt;
        }
      }
      if (trie[cur_v].terminal != 0) {
        copy_s[i] = trie[cur_v].terminal - 1;
      } else {
        trie[cur_v].terminal = (i + 1);
      }
      st_to_node[i] = cur_v;
    }

    bfs(ROOT);
  }

  // TASK dependent
  // EXAMPLE: leftmost and rightmost entries of pattern strings
  void Solve(const std::string& t) {
    int cur_v = ROOT;
    for (int i = 0; i < (int)t.size(); ++i) {
      int c = t[i] - 'a';
      cur_v = Go(cur_v, c);
      // calc
      int term_s =
          trie[cur_v].terminal != 0
              ? trie[cur_v].terminal
              : trie[trie[cur_v].prev_terminal].terminal;  // mb trie[0]
      if (term_s != 0) {
        term_s--;
        left_index[term_s] = std::min(left_index[term_s], i);
        right_index[term_s] = std::max(right_index[term_s], i);
      }
    }
    int n = copy_s.size();  // n - # pattern strings
    for (int i = 0; i < n; ++i) {
      int j = copy_s[i] == -1 ? i : copy_s[i];
      Calc(j);
      if (left_index[j] == mxN) {
        std::cout << "-1 -1";
      } else {
        std::cout << left_index[j] - st_sz[i] + 1 << " "
             << right_index[j] - st_sz[i] + 1;
      }
      std::cout << "\n";
    }
  }
};
