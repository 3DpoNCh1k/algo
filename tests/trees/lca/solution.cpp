#include <iostream>
#include <vector>
#include <algo/trees/lca.hpp>

int main() {
    int n, q;
    std::cin >> n >> q;

    std::vector<int> parent(n);
    parent[0] = -1;
    for(int u = 1; u < n; ++u) {
        std::cin >> parent[u];
    }
    auto lca = algo::trees::LCA(parent);
    lca.Solve();

    for(int query = 0; query < q; query++) {
        int u, v;
        std::cin >> u >> v;
        std::cout << lca.GetLCA(u, v) << std::endl;
    }
}