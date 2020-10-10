#ifndef HLD_HPP
#define HLD_HPP

// Verification: https://codeforces.com/group/CYMPFXi8zA/contest/243321/problem/G

#include <bits/stdc++.h>

using namespace std;

// HLD with lazy prop

struct HLD {    // sum of vertices values on path u-v; for calcs on edges - do some modifications
    
    using ll = long long int;

    struct Node {
        Node() {
            lazy = sum = sz = 0; // Neutral element
        }
        ll lazy, sum, sz;
    };

    //static const int mxN = 3 * 100'000 + 10; // !!!

    vector<vector<int>> g;
    vector<int> h, top, sz, index, parent;
    vector<Node> T;
    int root, n, B, id;
    
    HLD(const vector<vector<int>> & G, int root=0):root(root) { // !! INIT VALS
        n = G.size();
        g = G;
        B = 1;
        while(B < n)
            B <<= 1;
        T.assign(2*B, {});
        h.assign(n, 0), top.assign(n, 0), sz.assign(n, 0), index.assign(n, 0), parent.assign(n, 0);
        id = 0;
        dfs1(root);
        dfs2(root);
        
        for(int i = 0; i < n; ++i) { // INIT VALS
            T[B+index[i]].sz = 1;
        }
        for(int i = B-1; i > 0; --i) {
            pull(i);
        }
    }

    void dfs1(int v, int par=-1) {
        parent[v] = par;
        sz[v] = 1;
        for(int u: g[v]) {
            if (u != par) {
                h[u] = h[v] + 1;
                dfs1(u, v);
                sz[v] += sz[u];
            }
        }
    }

    void dfs2(int v, int par=-1, int top_v=-1) {
        index[v] = id++;
        top_v = top_v == -1? v: top_v;
        top[v] = top_v;
        int m_ind = -1;
        for(int u: g[v]) {
            if (u != par && (m_ind == -1 || sz[m_ind] < sz[u]))
                m_ind = u;
        }
        if (m_ind != -1) {
            dfs2(m_ind, v, top_v);
        }
        for(int u: g[v]) {
            if (u != par && u != m_ind)
                dfs2(u, v);
        }
    }
    
    void pull(int i) {
        assert(i < B);
        int left = 2*i, right = 2*i+1;
        T[i].sum = T[left].sum + T[right].sum;
    }
    
    Node pull(Node a, Node b) {
        a.sz += b.sz, a.sum += b.sum;
        return a;
    }

    void actualize(int v) { // v is already good
        int left = 2*v, right = 2*v + 1;
        if (T[v].lazy) {
            T[left].sum += T[v].lazy * T[left].sz, T[right].sum += T[v].lazy * T[right].sz;
            T[left].lazy += T[v].lazy, T[right].lazy += T[v].lazy;
            T[v].lazy = 0;
        }
    }
    // [L, R] - node segment     [l, r] - query segment  
    void add(int v, int L, int R, int l, int r, int val) {
        if (r < L || R < l)
            return;
        if (l <= L && R <= r) {
            T[v].lazy += val;
            T[v].sum += T[v].sz * val;
            return;
        }
        
        actualize(v);
        int left = 2*v, right = 2*v + 1;
        int M = (L + R) / 2;
        add(left, L, M, l, r, val);
        add(right, M+1, R, l, r, val);
        pull(v);
    }

    Node qry(int v, int L, int R, int l, int r) {
        if (r < L || R < l)
            return Node();
        if (l <= L && R <= r) {
            return T[v];
        }
        
        actualize(v);
        int left = 2*v, right = 2*v + 1;
        int M = (L + R) / 2;
        Node lans = qry(left, L, M, l, r);
        Node rans = qry(right, M+1, R, l, r);
        
        return pull(lans, rans);
    };
    
    
    ll query_uv(int u, int v) {
        //--u, --v; // 0 indexed
        Node res = {};
        while(top[u] != top[v]) {
            if (h[top[u]] < h[top[v]])
                swap(u, v);
            res = pull(res, qry(1, 0, B-1, index[top[u]], index[u])); // if not commutative -> 2 branch: u->lca, lca<-v
            u = parent[top[u]];
            assert(u != -1);
        }
        if (h[u] < h[v])
            swap(u, v);
        res = pull(res, qry(1, 0, B-1, index[v], index[u]));
        
        return res.sum; // !
    }
    
    void add_uv(int u, int v, int d) {
        //--u, --v; // 0 indexed
        while(top[u] != top[v]) {
            if (h[top[u]] < h[top[v]])
                swap(u, v);
            add(1, 0, B-1, index[top[u]], index[u], d);
            u = parent[top[u]];
            assert(u != -1);
        }
        if (h[u] < h[v])
            swap(u, v);
        add(1, 0, B-1, index[v], index[u], d);
    }
    
};

#endif
