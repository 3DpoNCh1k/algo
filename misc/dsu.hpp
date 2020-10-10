#ifndef DSU_HPP
#define DSU_HPP

// Verification: https://judge.yosupo.jp/problem/unionfind

#include <bits/stdc++.h>

using namespace std;

struct DSU {
    vector<int> par, h;

    DSU(int n) {
        par.resize(n), h.resize(n, 1);
        for(int i = 0; i < n; ++i)
            par[i] = i;
    }

    int find(int v) {
        if (par[v] == v)
            return v;
        return par[v] = find(par[v]);
    }

    void merge(int u, int v) {
        int pu = find(u);
        int pv = find(v);
        if (pu == pv)
            return;
        if (h[pu] < h[pv]) {
            par[pu] = pv;
        }
        else {
            par[pv] = pu;
            if (h[pu] == h[pv]) {
                h[pu]++;
            }
        }
    }

}; 


#endif
