#ifndef FENWICK_HPP
#define FENWICK_HPP

#include <bits/stdc++.h>

// Verification: https://codeforces.com/group/CYMPFXi8zA/contest/240094/problem/B


using namespace std;

struct Fenwick {
    
    using ll = long long;
    
    static const int mxN = 5e5 + 10;
    ll a[mxN];

    int get_len(int i) {
        return ((i + 1) ^ i) & (i + 1);
    };

    void add(int i, ll val) {
        while(i < mxN) {
            a[i] += val;
            i += get_len(i);
        }
    };

    ll sum(int i) {
        ll ans = 0;
        while(i >= 0) {
            ans += a[i];
            i -= get_len(i);
        }
        return ans;
    };

    void set_val(int i, ll val) {
        add(i, (val-(sum(i) - sum(i-1))));
    };

    ll get_sum(int l, int r) {
        return sum(r) - sum(l-1);
    };

};

struct Fenwick_3D {
    
    using ll = long long;
    static const int mxN = 128 + 5;
    int a[mxN][mxN][mxN];

    void add(int x, int y, int z, int val)
    {
        int i, j, k;
        for(i = x; i < mxN; i |= (i+1))
            for(j = y; j < mxN; j |= (j + 1))
                for(k = z; k < mxN; k |= (k + 1))
                    a[i][j][k] += val;
    }

    int get(int x, int y, int z)
    {
        if (x < 0 || y < 0 || z < 0)
            return 0;
        int res = 0;
        int i, j, k;
        for(i = x; i >= 0; i = (i&(i+1)) - 1)
            for(j = y; j >= 0; j = (j&(j + 1)) - 1)
                for(k = z; k >= 0; k = (k&(k + 1)) - 1)
                    res += a[i][j][k];
                
        return res;
    }

};



#endif
