#ifndef FFT_HPP
#define FFT_HPP

// Verification: https://codeforces.com/group/CYMPFXi8zA/contest/279284/problem/F

#include <bits/stdc++.h>
using namespace std;

struct FFT {
    
    using ll = long long;
    using ld = long double;

    static const int mxK = 19; // use 15-17 locally if SEGFAULT
    static const int mxN = 1 << mxK;
    using clx = complex<ld>; 
    clx unity_root[mxN];
    int pos[mxN];
    const ld PI = acos((ld)-1);

    FFT() { // ! use FFT fft; insted of: FFT fft(); - function declaration;
        int n = mxN, k = mxK;
        for(int i = 0; i < n; ++i) {
            ld angle = (2 * PI * i) / n;
            // cout  <<" angle = " << angle << " cos = " << cos(angle) << "  sin = " << sin(angle) << "\n";
            unity_root[i] = {cos(angle), sin(angle)};
        }
        
        pos[0] = 0;
        int pow_2 = 0;
        for(int i = 1; i < n; ++i) {
            if (i & (1 << pow_2))
                pow_2++;
            int t = i ^ (1 << (pow_2 - 1));
            pos[i] = pos[t] | (1 << (k-pow_2));
        }
    }

    void fft(vector<clx> & res, vector<clx> const & a) {
        int n = res.size(), k = mxK;
        assert(n==mxN); //  for simplicity always use mxN vectors (mxN-1 order polynom)
        for(int i = 0; i < n; ++i) {
            res[pos[i]] = a[i];
        }
        for(int lvl = 0; lvl < k; ++lvl) {
            int block = 1 << lvl;
            int root_shift = (1<<(k-lvl-1));
            for(int st = 0; st < n; st += (block << 1)) {
                for(int j = 0; j < block; ++j) {
                    clx x = unity_root[j * root_shift];
                    clx f = res[st + j] + x * res[st + block + j];
                    clx s = res[st + j] - x * res[st + block + j];
                    res[st + j] = f;
                    res[st + block + j] = s;
                }
            }
        }
    }


    void inverse_fft(vector<clx> & res, vector<clx> & a) {
        fft(res, a);
        reverse(res.begin() + 1, res.end());
        int n = res.size();
        for(int i = 0; i < n; ++i) {
            res[i] /= n;
        }
    }

}; 


#endif
