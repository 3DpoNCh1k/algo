#ifndef ALG_HPP
#define ALG_HPP

// Verification for vector_least_prime: https://codeforces.com/group/CYMPFXi8zA/contest/279284/problem/B

#include <bits/stdc++.h>
using namespace std;

using ll = long long;
using ld = long double;


// a*x + b*y = g
ll gcd_ext(ll a, ll b, ll & x,ll & y) {
	if (a == 0) {
		x = 0; y = 1;
		return b;
	}
	ll x1, y1;
    //  (b%a)*x1 + a*y1 = g
    //  a*y1 + (b - (b/a) * a)*x1 = g
    //  a*(y1 - (b/a)*x1) + b*(x1) = g
	ll g = gcd_ext(b%a, a, x1, y1);
	x = y1 - (b / a) * x1;
	y = x1;
	return g;
}

// a*x = 1 (mod m) ~> a*x = 1 + m*y ~> a*x - m*y = 1
ll inv_mod(ll a, ll m) {
    ll x, y;
    ll g = gcd_ext(a, m, x, y);
    if (g != 1) {
        // no solution
        return -1;
    }
    return ((x % m) + m) % m;
}

vector<int> vector_inv_pmod(int m) {
    vector<int> inv(m); 
    inv[1] = 1;
    // m (mod i) = m - (m/i)*i ~> (mod m) ~> m (mod i) = -(m/i)*i ~> (*inv[m (mod i)], *inv[i]) ~> inv[i] = -(m/i) * inv[m (mod i)] 
    for(int i = 2; i < m; ++i)
        inv[i] = m - (((m / i) * inv[m % i]) % m);
    return inv;
}


vector<int> vector_least_prime(int N) {
    vector<int> lp(N+1);
    vector<int> pr;
    for(int i = 2; i <= N; ++i) {
        if (lp[i] == 0) {
            lp[i] = i;
            pr.push_back (i);
        }
        for (int j = 0; j < (int)pr.size() && pr[j] <= lp[i] && i * pr[j] <= N; ++j)
            lp[i * pr[j]] = pr[j];
    }
    return lp;
}


const ll MOD = 1e9+7;
ll add_mod(ll a, ll b) {
    ll res = a + b;
    return res < MOD? res: res - MOD;
}

int mult_mod(int a, int b) {
    ll res = a * b;
    return res % MOD;
}

ll mult_mod(ll a, ll b) {
    __int128 res = a * b; // choose appropriate compiler for __int128 (GNU G++17 9.2.0 (64 bit, msys 2) on CF)
    return res % MOD;
}


    
#endif
