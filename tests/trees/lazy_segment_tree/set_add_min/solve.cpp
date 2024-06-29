#include <cstdlib>
#include <iostream>
#include <sstream>
#include <vector>
#include <string>

#include <algo/trees/lazy_segment_tree.hpp>
#include "algo/utils/types/types.hpp"

int main() {
  std::ios::sync_with_stdio(false);
  std::cin.tie(nullptr);

  using algo::utils::i64;
  int n;
  std::cin >> n;
  std::vector<i64> a(n);
  for(auto & value: a) {
    std::cin >> value;
  }
  auto lazy = algo::trees::LazySegmentTree(a);

  std::string line;
  while(std::getline(std::cin, line)) {
    if (line.empty()) {
      continue;
    }
    std::istringstream ss(line);
    std::string command;
    
    ss >> command;
    if(command == "set") {
      int i, j;
      i64 x;
      ss >> i >> j >> x;
      --i, --j;
      lazy.SetValue(i, j, x);
    } else if (command == "add") {
      int i, j;
      i64 x;
      ss >> i >> j >> x;
      --i, --j;
      lazy.AddValue(i, j, x);
    } else if (command == "min") {
      int i, j;
      ss >> i >> j;
      --i, --j;
      std::cout << lazy.GetMin(i, j) << "\n";
    } else {
      std::abort();
    }
  }
}