#include <cstdlib>
#include <iostream>
#include <sstream>
#include <vector>
#include <string>

#include "algo/trees/segment_tree/trees.hpp"
#include "algo/trees/segment_tree/operations/set_add.hpp"
#include "algo/trees/segment_tree/statistics/minimum.hpp"
#include "algo/utils/types/fundamentals.hpp"

using namespace algo::trees::segment_tree;

int main() {
  std::ios::sync_with_stdio(false);
  std::cin.tie(nullptr);

  int n;
  std::cin >> n;
  std::vector<i64> a(n);
  for (auto& value : a) {
    std::cin >> value;
  }
  auto segment_tree =
      algo::trees::segment_tree::LazyPropagationDynamicSegmentTree<
          Operation<operations::SetAddOp>, Statistics<statistics::Minimum>>(
          0, n - 1);
  for (int i = 0; i < n; ++i) {
    segment_tree.ApplyAtIndex(i, operations::SetOp{true, a[i]});
  }

  std::string line;
  while (std::getline(std::cin, line)) {
    if (line.empty()) {
      continue;
    }
    std::istringstream ss(line);
    std::string command;

    ss >> command;
    if (command == "set") {
      int i, j;
      i64 x;
      ss >> i >> j >> x;
      --i, --j;
      segment_tree.ApplyOnRange(i, j, operations::SetOp{true, x});
    } else if (command == "add") {
      int i, j;
      i64 x;
      ss >> i >> j >> x;
      --i, --j;
      segment_tree.ApplyOnRange(i, j, operations::AddOp{x});
    } else if (command == "min") {
      int i, j;
      ss >> i >> j;
      --i, --j;
      std::cout << segment_tree.GetFromRange<statistics::Minimum>(i, j).result
                << "\n";
    } else {
      std::abort();
    }
  }
}
