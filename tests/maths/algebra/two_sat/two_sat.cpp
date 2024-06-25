#include <iostream>
#include <vector>
#include <string>
#include <set>

#include <algo/maths/algebra/two_sat.hpp>
#include "algo/utils/debug.hpp"


int main() {
    // std::cout << "Hello!" << std::endl;
    int n, m;

    std::string unused;
    std::cin >> unused >> unused;
    std::cin >> n >> m;

    // dbg(n, m);

    std::vector<std::vector<int>> dependency_graph(2*n);

    auto negate_vertex = [&](int vertex) {
        if (vertex < n) {
            return vertex + n;
        }
        return vertex - n;
    };

    auto map_to_vertex = [&](int value) {
        if (value > 0) {
            // make zero-based
            return value - 1;
        } else {
            // negation
            auto vertex = abs(value) - 1;
            return negate_vertex(vertex);
        }
    };
    
    for(int clause = 0; clause < m; ++clause) {
        int a, b;
        std::cin >> a >> b >> unused;
        // dbg(a, b);
        int u = map_to_vertex(a);
        int v = map_to_vertex(b);
        
        dependency_graph[negate_vertex(u)].push_back(v);
        dependency_graph[negate_vertex(v)].push_back(u);
    }

    auto two_sat = algo::maths::algebra::TwoSat(dependency_graph);
    std::set<int> ret_ans;
    auto has_solution = two_sat.Solve(ret_ans);
    if (has_solution) {
        std::cout << "s SATISFIABLE" << std::endl;
        std::cout << "v ";
        for(int u = 0; u < n; ++u) {
            auto value = ret_ans.find(u) != ret_ans.end()? (u+1): -(u+1);
            std::cout << value << " ";
        }
        std:: cout << 0 << std::endl;
    } else {
        std::cout << "s UNSATISFIABLE" << std::endl;
    }
    // algo::maths::algebra::TwoSat;
}