#ifndef SUFFIX_TREE_HPP
#define SUFFIX_TREE_HPP

// Verification: https://codeforces.com/group/CYMPFXi8zA/contest/261526/problem/F

#include <bits/stdc++.h>

using namespace std;

struct Suffix_tree {

    using ll = long long;

    int mxN = 2e5 + 100; // ! in constructor
    const int AS = 128;
    const int ROOT = 1;
    int INF = 1e9;
    int cnt = 2;
    string s;
    int type = 1;
     
    struct Node {
        Node() {}
        Node(int par, int left, int right, int leaf=0, int ref=0):
        par(par), left(left), right(right), leaf(leaf), ref(ref) {}
        int par=0, left=0, right=-1, leaf=0, ref=0;
        map<char,int> to;
    };

    vector<Node> tree;
    
    // see solve()
    Suffix_tree(int mxN):mxN(mxN) {
        tree.resize(mxN);
    };
    
    int len(int v) {
        return tree[v].right - tree[v].left + 1;
    }
    int cur_v, cur_p; // number of read chars on edge already

    void go(int u, int i) {
        assert(u && u != ROOT);
        int par = tree[u].par; // root.ref = root
        int k = tree[u].right - tree[u].left + 1;
        if (par == ROOT) {
            --k;
        }
        int v = tree[par].ref;
        cur_p = k;
        while(k) { // we sure about transitions
            v = tree[v].to[s[tree[u].right - k + 1]];
            if(len(v) < k)
                k-=len(v);
            else {
                cur_p=k;
                k = 0;
            }
        }
        cur_v = v;
        if (cur_p == len(cur_v)) { // we are in already existing node cur_v
            tree[u].ref = cur_v;
        }
        else {
            tree[u].ref = cnt; // we are on edge -> in next step we'll create node cnt
        }
    }

    void add(int i) {
        char c = s[i];
        while (1) {
            if (cur_p == len(cur_v)) {
                if (tree[cur_v].to[c]) {
                    cur_v = tree[cur_v].to[c], cur_p = 1;
                    break;
                }
                else {
                    tree[cnt] = Node(cur_v, i, INF, type); // (par, left, right, leaf, ref=0)
                    tree[cur_v].to[c] = cnt;
                    cnt++;
                    if (cur_v == ROOT) {
                        assert(cur_p == 0);
                        cur_p = 0;
                        break;
                    }
                    if (tree[cur_v].ref) { // it is node, not leaf
                        cur_v = tree[cur_v].ref;
                        cur_p = len(cur_v); 
                    }
                    else {
                        go(cur_v, i); // it'll update cur_v and cur_p and make ref for old cur_v
                    }
                }
            }
            else {
                int prev_pos = tree[cur_v].left+cur_p - 1;
                if (s[prev_pos+1] == c) {
                    cur_p++;
                    break;
                }
                else {
                    tree[cnt] = Node(tree[cur_v].par, tree[cur_v].left, prev_pos, 0); // PARENT FOR CUR
                    tree[tree[cur_v].par].to[s[tree[cur_v].left]] = cnt; // update previous parent of cur
                    tree[cnt].to[s[prev_pos+1]] = cur_v;
                    tree[cur_v].par = cnt, tree[cur_v].left = prev_pos + 1;
                    cnt++;
                    tree[cnt] = Node(cnt-1, i, INF, type); // LEAF
                    tree[cnt - 1].to[s[i]] = cnt;
                    cnt++;
                    go(cnt - 2, i); // cant be root case
                }
            }
        }
        if (c < 15)  // TASK dependent
            type <<= 1; // distinguish strings by their leaves type
    }

    // TASK depenndent
    int k; // # of strings
    int mxlen = 0, ind = -1;
    int dfs(int v, int curlen) {
        int cur_mask = tree[v].leaf;
        if (!cur_mask) {
            int mylen = len(v);
            for(auto e: tree[v].to) { // lexicographical order (from a..z)
                cur_mask |= dfs(e.second, curlen + mylen);
            }
            if (cur_mask == ((1 << k) - 1)) {
                if (mylen+curlen > mxlen) {
                    mxlen = mylen+curlen;
                    ind = v;
                }
            }
        }
        return cur_mask;
    }
    
    // TASK dependent
    // EXAMPLE: find longest (if some - lexicographically smallest) substr, which exists in every input string
    void solve() {
        tree[ROOT].ref = ROOT;
        int n, i;
        cin >> k;
        string t;
        for(i = 0; i < k; ++i) {
            cin >> t;
            t.push_back(i);
            s += t;
        }
        n = s.size();
        INF = n - 1;
        cur_v = ROOT;
        cur_p = 0;
        for(i = 0; i < n; ++i) {
            add(i);
        }
        
        if (dfs(ROOT, 0) == ((1 << k) - 1)) {
            vector<string> vans;
            while(ind != ROOT) {
                vans.push_back(s.substr(tree[ind].left, len(ind)));
                ind = tree[ind].par;
            }
            string ans;
            for(i = vans.size() - 1; i >= 0; --i)
                ans += vans[i];
            cout << ans;
        }
        else {
            cout << endl;
        }
    }
    
};

#endif
