#ifndef Z_PREFIX_HPP
#define Z_PREFIX_HPP

// Verification z_f: https://judge.yosupo.jp/problem/zalgorithm
// Verification pref_f: https://codeforces.com/group/CYMPFXi8zA/contest/261526/problem/B

#include <bits/stdc++.h>
using namespace std;

using ll = long long;


vector<int> prefix_function(const string & s) {
    int n = s.size();
    vector<int> pref(n);
	for(int i = 1; i < n; ++i) {
		int p  = pref[i-1];
		while(1) {
			if (s[i] == s[p]) {
				pref[i] = p + 1;
				break;
			}
			if (p == 0)
				break;
			p = pref[p-1];
		}
	}
    return pref;
}


vector<int> z_function(const string & s) {
    int n = s.size();
	vector<int> zf(n);
    zf[0] = n;
	int l = 0, r = 0;
	for(int i = 1; i < n; ++i) {
		int cv = 0;
		if (r >= i)
			cv = min(zf[i-l], r-i+1);
		while(i + cv < n && s[i+cv] == s[cv])
			cv++;
		zf[i] = cv;
		if (i + zf[i] - 1 > r) {
			l = i, r =  i + zf[i] - 1;
		}
	}
    return zf;
}


#endif
