#ifndef LAZY_SEGTREE_HPP
#define LAZY_SEGTREE_HPP

// Verification: https://codeforces.com/group/CYMPFXi8zA/contest/240094/problem/C

#include <bits/stdc++.h>
using namespace std;

struct Lazy_segtree {
    
    using ll = long long;
    static const ll INF = 1e18 + 100;
    // EXAMPLE: size, minimum, its count and one of its position
    
    struct Node {
        Node(){min_value = INF, pos = 1e9, cnt = 1, sz=1;}; // Neutral element
        Node(ll val, int pos, int cnt=1):
        min_value(val), pos(pos), cnt(cnt) {};
        int pos, cnt=1, sz=1;
        ll min_value=INF;
        ll lazy_add=0; // add value to elements of the node's segment
        ll lazy_set_flag=0; // 0/1; 1 - set value to childs
        ll lazy_set=0;
    };
    vector<Node> T;
    int n, B;
    
    Lazy_segtree(const vector<int> & a) {
        n = a.size();
        B = 1;
        while(B < n) {
            B <<= 1;
        }
        T.assign(2*B, {});
        for(int i = 0; i < n; ++i) {
            T[B+i].min_value = a[i];
            T[B+i].pos = i;
        }
        for(int i = B - 1; i > 0; --i) {
            pull(i);
        }
    }
    
    void pull(int i) { // better than next pull (try not pull lazy_add...)
        assert(i < B);
        int idx_min = 2*i, idx_max = 2*i+1;
        if (T[idx_min].min_value > T[idx_max].min_value)
            swap(idx_min, idx_max);
        T[i].min_value = T[idx_min].min_value;
        T[i].pos = T[idx_min].pos;
        T[i].cnt = T[idx_min].cnt;
        if (T[i].min_value == T[idx_max].min_value) {
            T[i].cnt += T[idx_max].cnt;
        }
        T[i].sz = T[idx_min].sz + T[idx_max].sz;
    }
    
    Node pull(Node a, Node b) { //  for qry - ok
        if (a.min_value > b.min_value)
            swap(a, b);
        if (a.min_value == b.min_value) {
            a.cnt += b.cnt;
        }
        a.sz += b.sz;
        return a;
    }
    
    void actualize(int v) { // v is already good 
        int left = 2*v, right = 2*v + 1;
        assert(left < 2*B && right < 2*B);
        if (T[v].lazy_set_flag) {
            T[left].min_value = T[v].lazy_set;
            T[left].lazy_set_flag = 1;
            T[left].lazy_set = T[v].lazy_set;
            T[left].lazy_add = 0;
            T[right].min_value = T[v].lazy_set;
            T[right].lazy_set_flag = 1;
            T[right].lazy_set = T[v].lazy_set;
            T[right].lazy_add = 0;
            T[v].lazy_set_flag = 0;
        }
        if (T[v].lazy_add) {
            T[left].min_value += T[v].lazy_add;
            T[left].lazy_add += T[v].lazy_add;
            T[right].min_value += T[v].lazy_add;
            T[right].lazy_add += T[v].lazy_add;
            T[v].lazy_add = 0;
        }
    };
    // [L, R] - node segment     [l, r] - query segment  
    void add(int v, int L, int R, int l, int r, ll val) {
        //cout << "add " << v << " L " << L << " R " << R << " l " << l << " r " << r << " val " << val << "\n";  
        //print();
        if (l > R || r < L)
            return;
        if (l <= L && R <= r) {
            T[v].min_value += val;
            T[v].lazy_add += val;
            return;
        }
        
        actualize(v);
        int left = 2*v, right = 2*v+1;
        int M = (L + R) / 2;
        add(left, L, M, l, r, val);
        add(right, M + 1, R, l, r, val);
        
        pull(v);
    };
    
    void set(int v, int L, int R, int l, int r, ll val) {
        if (l > R || r < L)
            return;
        if (l <= L && R <= r) {
            T[v].min_value = val;
            T[v].cnt = T[v].sz;
            T[v].lazy_add = 0;
            T[v].lazy_set_flag = 1;
            T[v].lazy_set = val;
            return;
        }
        
        actualize(v);
        int left = 2*v, right = 2*v+1;
        int M = (L + R) / 2;
        set(left, L, M, l, r, val);
        set(right, M + 1, R, l, r, val);
        
        pull(v);
    };
    
    // sz, min_val, cnt, pos
    Node qry(int v, int L, int R, int l, int r) {
        if (r < L || l > R)
            return Node();
        if (l <= L && R <= r)
            return T[v];

        actualize(v);
        int left = 2*v, right = 2*v+1;
        int M = (L + R) / 2;
        Node lans = qry(left, L, M, l, r);
        Node rans = qry(right, M + 1, R, l, r);
        
        return pull(lans, rans);
    };
    
    ll get_min(int l, int r) {
        Node ans = qry(1, 0, B-1, l, r);
        return ans.min_value;
    }
    
    void set_val(int l, int r, ll val) {
        set(1, 0, B-1, l, r, val);
    }
    void add_val(int l, int r, ll val) {
        add(1, 0, B-1, l, r, val);
    }
    
    void print() {
        cout << "B = " << B << " n = " << n << "\n";
        for(int i = 0; i < 2*B; ++i) {
            int pos=T[i].pos, cnt=T[i].cnt, sz=T[i].sz;
            ll min_value=T[i].min_value, lazy_add=T[i].lazy_add, lazy_set_flag=T[i].lazy_set_flag, lazy_set=T[i].lazy_set;
        
            cout << "i: " << i << " pos = " << pos << " cnt = " << cnt << " sz = " << sz;
            cout << " min_value = " << min_value << " lazy_add = " << lazy_add << " lazy_set_flag = " << lazy_set_flag;
            cout << " lazy_set = " << lazy_set << "\n";
        }
    }
};


#endif
