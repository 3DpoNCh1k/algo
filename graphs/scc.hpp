#ifndef SCC_HPP
#define SCC_HPP

// Verification: https://judge.yosupo.jp/problem/scc

#include <bits/stdc++.h>

using namespace std;

struct SCC {
    
    using ll = long long int;

    const int mxN = 2e5;
    const int INF = 1e9;

    set<pair<int, int>> ans; // edges in SCC graph (w/o duplicate edges)
    vector<vector<int>> g, g_inv;
    vector<int> visited, order, scc;
    int n;
    // see solve()
    SCC(const vector<vector<int>> & G) {
        // 0 indexed
        g = G;
        n = g.size();
        g_inv.assign(n, {}), visited.assign(n, 0), scc.assign(n, 0);
        for(int u = 0; u < n; ++u) {
            for(int v: g[u])
                g_inv[v].push_back(u);
        }
    }

    void dfs(int v) {
        visited[v] = 1;
        for(int u: g[v]) {
            if (!visited[u]){
                dfs(u);
            }
        }
        order.push_back(v);
    }

    void dfs2(int v, int cmp) {
        scc[v] = cmp;
        visited[v] = 1;
        for(int u: g_inv[v]) {
            if (!visited[u]){
                dfs2(u, cmp);
            }
            else {
                if (scc[u] != scc[v]) {
                    ans.insert({scc[u], scc[v]});
                }
            }
        }
    }
    
    void solve(vector<int> & ret_scc, set<pair<int,int>> & ret_ans) {
        
        for(int i = 0; i < n; ++i) {
            if (!visited[i]) {
                dfs(i);
            }
        }
        visited.assign(n, 0);
        int cmp = 1;
        for(int i = n - 1; i >= 0; --i) {
            int u = order[i];
            if (!visited[u]) {
                dfs2(u, cmp);
                cmp++;
            }
        }
        
        //ret_scc.assign(scc.begin(), scc.end());
        //ret_ans.insert(ans.begin(), ans.end());
        
        ret_scc = scc;
        ret_ans = ans;
    }
    
    // EXAMPLE (cnt # edges in SCC graph) 
    // 1 indexed vertices
    void solve() {
        int n, m;
        cin >> n >> m;
        g.assign(n+1, {}), g_inv.assign(n+1, {}), visited.assign(n+1, 0), scc.assign(n+1, 0);
        
        for(int i = 0; i < m; ++i) {
            int u, v;
            cin >> u >> v;
            g[u].push_back(v);
            g_inv[v].push_back(u);
        }
        
        for(int i = 1; i <=n; ++i) {
            if (!visited[i]) {
                dfs(i);
            }
        }
        
        visited.assign(n+1, 0);
        int cmp = 1;
        for(int i = n - 1; i >= 0; --i) {
            int u = order[i];
            if (!visited[u]) {
                dfs2(u, cmp);
                cmp++;
            }
        }
        cout << ans.size();
    }

};

#endif
