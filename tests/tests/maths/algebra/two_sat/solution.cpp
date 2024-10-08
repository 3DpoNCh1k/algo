#include <iostream>
#include <vector>
#include <string>

#include <algo/maths/algebra/two_sat.hpp>
#include <algo/utils/debug.hpp>

using namespace algo::maths::algebra;

int main() {
  int n, m;

  std::string unused;
  std::cin >> unused >> unused;
  std::cin >> n >> m;

  std::vector<std::pair<int, int>> clauses;

  for (int clause = 0; clause < m; ++clause) {
    int a, b;
    std::cin >> a >> b >> unused;
    clauses.emplace_back(a, b);
  }

  auto two_sat = TwoSat(n, clauses);
  auto [has_solution, solution] = two_sat.Solve();
  if (has_solution) {
    std::cout << "s SATISFIABLE" << std::endl;
    std::cout << "v ";
    for (int var = 1; var <= n; ++var) {
      auto value = solution.find(var) != solution.end() ? var : -var;
      std::cout << value << " ";
    }
    std::cout << 0 << std::endl;
  } else {
    std::cout << "s UNSATISFIABLE" << std::endl;
  }
  // algo::maths::algebra::TwoSat;
}
