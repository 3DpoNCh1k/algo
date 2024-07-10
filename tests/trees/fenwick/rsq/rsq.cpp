#include <cstdlib>
#include <iostream>
#include <sstream>
#include <string>
#include "algo/utils/types/fundamentals.hpp"
#include <algo/utils/debug.hpp>
#include <algo/trees/fenwick.hpp>

int main() {
  using i64;
  int n;
  std::cin >> n;
  auto fenwick = algo::trees::Fenwick(n);
  for (int i = 0; i < n; ++i) {
    i64 a;
    std::cin >> a;
    fenwick.SetValue(i, a);
  }

  std::string line;
  while (std::getline(std::cin, line)) {
    if (line.empty()) {
      continue;
    }
    std::istringstream ss(line);
    std::string cmd;
    ss >> cmd;
    if (cmd == "sum") {
      int i, j;
      ss >> i >> j;
      --i;
      --j;
      std::cout << fenwick.GetSum(i, j) << "\n";
    } else if (cmd == "set") {
      int i;
      i64 x;
      ss >> i >> x;
      --i;
      fenwick.SetValue(i, x);
    } else {
      std::abort();
    }
  }
}
