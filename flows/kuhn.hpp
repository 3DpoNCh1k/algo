#ifndef KUHN_HPP
#define KUHN_HPP

#include <bits/stdc++.h>

// https://judge.yosupo.jp/problem/bipartitematching

// TODO: fix TLE on random_03 test

using namespace std;

struct Kuhn {

    vector<vector<int>> L;
    vector<int> visited;
    vector<int> mt;
    int n1, n2; // left sz, right sz
    int k_mt; // # matchings
    Kuhn(const vector<vector<int>> & Left, int n2):n2(n2) {
        L = Left;
        n1 = L.size();
        visited.resize(n1, 0);
        mt.resize(n2,-1);
    }
    
    int solve(vector<int> & ret_mt) {
        vector<char> used1 (n1);
        k_mt = 0;
        set<pair<int, int>> Q;
        vector<vector<int>> R(n2);
        vector<int> degs(n1);
        for(int i = 0; i < n1; ++i) {
            degs[i] = L[i].size();
            Q.insert({L[i].size(), i});
            for(int v: L[i])
                R[v].push_back(i);
        }

        int k = 0;
        while(!Q.empty()) {
            ++k;
            auto it = Q.begin();
            int d = it->first, idx = it->second;
            Q.erase(it);
            for(int v: L[idx]) {
                if (mt[v] == -1) {
                    used1[idx] = 1;
                    k_mt++;
                    mt[v] = idx;
                    for(int u: R[v]) {
                        auto it2 = Q.find({degs[u],u});
                        if (it2 != Q.end()) {
                            degs[u]--;
                            Q.erase(it2);
                            if (degs[u])
                                Q.insert({degs[u], u});
                        }
                    }
                    break;
                }
            }
        }
        
        //for (int i=0; i<n1; ++i) {
            //if (used1[i])
                //continue;
            //for (size_t j=0; j < L[i].size(); ++j) {
                //if (mt[L[i][j]] == -1) {
                    //mt[L[i][j]] = i;
                    //used1[i] = true;
                    //k_mt++;
                    //break;
                //}
            //}
        //}
        
        for(int i = 0; i < n1; ++i) {
            if (used1[i])  continue;
            visited.assign(n1, 0);
            if (kuhn(i))
                k_mt++;
        }
        ret_mt = mt;
        return k_mt;
    }
    
    bool kuhn(int v) {
        if (visited[v])
            return 0;
        visited[v] = 1;
        for(int u: L[v]) {
            if (mt[u]==-1 || kuhn(mt[u])) {
                mt[u] = v;
                return 1;
            }
        }
        return 0;
    }
    
};

#endif
