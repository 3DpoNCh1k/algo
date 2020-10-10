#include <bits/stdc++.h>
using namespace std;

using ll = long long;
using ld = long double;

/*
 all with  l, ll versions
 
 __builtin_ffs(x) 1 + least significant 1; 0 for 0
 __builtin_clz(x)
 __builtin_popcount(x)

 */

constexpr int bit_len(int x) {return 32 - __builtin_clz(x);}



#define mp make_pair
#define pb push_back
#define eb emplace_back
#define sz(x) (int)(x).size()
#define all(x) (x).begin(), (x).end()


ll FIRSTTRUE(function<bool(ll)> f, ll lb, ll rb) {
    // F...FT...T, call (0, n) n-th is T 
	while(lb<rb) {
		ll mb=(lb+rb)/2;
		f(mb)?rb=mb:lb=mb+1; 
	} 
	return lb;
}
ll LASTTRUE(function<bool(ll)> f, ll lb, ll rb) {
	// T...TF...F, call (-1, n-1) -1-th is T
    while(lb<rb) {
		ll mb=(lb+rb+1)/2;
		f(mb)?lb=mb:rb=mb-1; 
	} 
	return lb;
}
 

string to_string(char c) {
	return string(1, c);
}
string to_string(bool b) {
	return b?"true":"false";
}
string to_string(const char* s) {
	return string(s);
}
string to_string(string s) {
	return s;
}
string to_string(vector<bool> v) {
	string res;
	for(auto x: v)
		res+=char('0'+x);
	return res;
}
 
template<size_t N> string to_string(bitset<N> b) {
	return b.to_string();
}
template<class T> string to_string(T v) {
    bool f=1;
    string res;
    for(auto x: v) {
		if(!f)
			res+=' ';
		f=0;
		res+=to_string(x);
	}
    return res;
}


void DBG() {
	cerr << "]" << endl;
}
template<class H, class... T> void DBG(H h, T... t) {
	cerr << to_string(h);
	if(sizeof...(t))
		cerr << ", ";
	DBG(t...);
}
#ifdef _DEBUG
#define dbg(...) cerr << "LINE(" << __LINE__ << ") -> [" << #__VA_ARGS__ << "]: ["; DBG(__VA_ARGS__)
#else
#define dbg(...) 0
#endif 

mt19937 mt_rng(chrono::steady_clock::now().time_since_epoch().count());
ll randint(ll a, ll b) {
	return uniform_int_distribution<ll>(a, b)(mt_rng);
}



const int d4i[4]={-1, 0, 1, 0}, d4j[4]={0, 1, 0, -1};
const int d8i[8]={-1, -1, 0, 1, 1, 1, 0, -1}, d8j[8]={0, 1, 1, 1, 0, -1, -1, -1};


const int MOD = 1e9+7; 
const int mxN = 2e5+5;
const ll INF = 1e18; // not too close to LLONG_MAX

int main() {
    ios::sync_with_stdio(0);
	cin.tie(0);
    
    
}
