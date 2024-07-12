#include <cstdlib>
#include <iostream>
#include <sstream>
#include <string>
#include "algo/utils/types/fundamentals.hpp"
#include <algo/utils/debug.hpp>
#include <algo/trees/fenwick/operations/add.hpp>
#include <algo/trees/fenwick/operations/operation.hpp>
#include <algo/trees/fenwick/statistics/sum.hpp>
#include <algo/trees/fenwick/statistics/statistics.hpp>
#include <algo/trees/fenwick/trees.hpp>

using namespace algo::trees::fenwick;
using namespace operations;
using namespace statistics;

int main() {
  int n;
  std::cin >> n;
  auto fenwick = FenwickTree<Operation<AddOp>, Statistics<Sum>>(n);

  auto set_at_index = [&fenwick](int index, auto value) {
    auto res = fenwick.GetAtIndex<Sum>(index);
    auto add = AddOp{value - res.result};
    fenwick.ApplyAtIndex(add, index);
  };

  for (int i = 0; i < n; ++i) {
    i64 a;
    std::cin >> a;
    set_at_index(i, a);
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
      auto res = fenwick.GetFromRange<Sum>(i, j);
      std::cout << res.result << "\n";
    } else if (cmd == "set") {
      int i;
      i64 x;
      ss >> i >> x;
      --i;
      set_at_index(i, x);
    } else {
      std::abort();
    }
  }
}
