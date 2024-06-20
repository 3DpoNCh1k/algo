#pragma once

#include <cassert>
#include <string>
#include <vector>


// Verification: https://judge.yosupo.jp/problem/suffixarray
namespace algo::strings {
struct SuffixArray {
  const int AS = 256;  // Alphabet size, can be 26 + 1;
  std::string s;
  std::vector<int> sa, isa, ce, cnt;
  explicit SuffixArray(const std::string& s)
      : s(s){};

  std::vector<int> Solve() {
    s.push_back(0);  // !
    int n = (int)s.size(), log = 0;
    while ((1 << log) < n) {
      log++;
    }
    sa.assign(n, 0), isa.assign(n, 0), ce.assign(n, 0), cnt.assign(AS, 0);
    // suf_ar, inv_suf_ar, class_eq, cnt

    for (int i = 0; i < n; ++i) {
      cnt[s[i]]++;
    }
    for (int i = 1; i < AS; ++i) {
      cnt[i] += cnt[i - 1];
    }
    for (int i = n - 1; i >= 0; --i) {
      sa[--cnt[s[i]]] = i;
    }
    ce[sa[0]] = 0;
    int n_ce = 1;

    for (int i = 1; i < n; ++i) {
      if (s[sa[i]] != s[sa[i - 1]]) {
        ce[sa[i]] = n_ce++;
      } else {
        ce[sa[i]] = ce[sa[i - 1]];
      }
    }

    for (int it = 1; it <= log; ++it) {
      int len = 1 << it;
      std::vector<int> buf(n);
      for (int i = 0; i < n; ++i) {
        buf[i] = (sa[i] - (len >> 1) + n) % n;
      }
      cnt.clear(), cnt.resize(n_ce);
      for (int i = 0; i < n; ++i) {
        cnt[ce[buf[i]]]++;
      }
      for (int i = 1; i < n_ce; ++i) {
        cnt[i] += cnt[i - 1];
      }
      for (int i = n - 1; i >= 0; --i) {
        sa[--cnt[ce[buf[i]]]] = buf[i];
      }
      buf[sa[0]] = 0;
      n_ce = 1;
      for (int i = 1; i < n; ++i) {
        int fir = sa[i], pfir = sa[i - 1];
        int sec = (fir + (len >> 1)) % n, psec = (pfir + (len >> 1)) % n;
        if (ce[fir] == ce[pfir] && ce[sec] == ce[psec]) {
          buf[fir] = buf[pfir];
        } else {
          buf[fir] = n_ce++;
        }
      }
      swap(ce, buf);
    }

    // sa[0] - nth suffix (pb(0))
    // or return vector(sa.begin() + 1, sa.end());
    return sa;
  }

  std::vector<int> LcpArray() {
    int n = sa.size();
    assert(n == (int)s.size());
    std::vector<int> lcp(n - 1);
    isa.assign(n, 0);
    for (int i = 0; i < n; ++i) {
      isa[sa[i]] = i;
    }
    int cur_lcp = 0;
    for (int i = 0; i < n; ++i) {
      int p = isa[i];
      if (p == 0) {
        continue;
      }
      int j = sa[p - 1];
      // or just s[i+cur_lcp]==s[j+cur_lcp], i.e s[-1] = 0
      while (i + cur_lcp < n && j + cur_lcp < n &&
             s[i + cur_lcp] == s[j + cur_lcp]) {
        cur_lcp++;
      }

      lcp[p - 1] = cur_lcp;
      cur_lcp--;
      cur_lcp = std::max(cur_lcp, 0);
    }

    // lcp[0] - lcp(sa[0], sa[1]) - must be 0
    // or return vector(lcp.begin() + 1, lcp.end());
    return lcp;
  }
};
}
