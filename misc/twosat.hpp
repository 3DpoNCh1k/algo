#ifndef TWOSAT_HPP
#define TWOSAT_HPP

// Verification: https://judge.yosupo.jp/problem/two_sat

#include <bits/stdc++.h>

using namespace std;

struct TWOSAT {

    using ll = long long int;

    const int mxN = 2e5;
    const int INF = 1e9;

    vector<vector<int>> g, g_inv;
    vector<int> visited, order, val;

    int n;
    int flag = 1;
    
    // see solve()
    TWOSAT(vector<vector<int>> & G) {
        g = G;
        int n2 = G.size();
        assert((n2 % 2) == 0); // assume, it's 2 * # vertices: x: (0...n-1); !x: (n...2n-1)
        n = n2 / 2;
        g_inv.assign(2*n, {}), visited.assign(2*n, 0);
        for(int u; u < 2*n; ++u)
            for(int v: G[u])
                g_inv[v].push_back(u);
        
        //g.assign(2*n, {}), g_inv.assign(2*n, {}), visited.assign(2*n, 0);
        //for(int u = 0; u < 2*n; ++u) {
            //int nu = u < n? u + n: u - n;
            //for(int v: G[u]) {
                //int nv = v < n? v + n: v - n;
                //g[u].push_back(v);
                //g[nv].push_back(nu);
                
                //g_inv[v].push_back(u);
                //g_inv[nu].push_back(nv);
            //}
        //}
    }
    
    void dfs(int v) {
        visited[v] = 1;
        for(int u: g_inv[v]) {
            if (!visited[u])
                dfs(u);
        }
        order.push_back(v);
    }

    void dfs2(int v, int c) {
        visited[v] = 1;
        int nv = v < n? v + n: v - n;
        if (visited[nv] == 1)
            flag = 0; // no solution x -> !x
        
        val[v] = c;
        val[nv] = 1^c;
        
        for(int u: g[v]) {
            if (!visited[u])
                dfs2(u, c);
        }
        visited[v] = 2;
    }

    bool solve(set<int>  & ret_ans) { // ans - set TRUE vertices
        
        for(int i = 2*n-1; i >=0; --i) {
            if (!visited[i]) {
                dfs(i);
            }
        }
        visited.assign(2*n, 0);
        val.resize(2*n, -1);
        
        flag = 1;
        for(int i = 2 * n - 1; i >= 0; i--) {
            int u = order[i];
            if (visited[u])
                continue;
            int c = val[u];
            if (val[u] == -1) {
                c = 1; // if not marked -> mark as positive
            }
            dfs2(u, c);
        }
        
        ret_ans.clear();
        for(int i = 0; i < n; ++i) {
            if (val[i])
                ret_ans.insert(i);
        }
        return flag;
    }

};


#endif
