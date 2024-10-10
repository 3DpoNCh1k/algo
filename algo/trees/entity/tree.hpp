#pragma once

#include <sstream>
#include <string>
#include <vector>

#include <algo/utils/to_string/to_string.hpp>

namespace algo::trees {

struct Tree {
  int n;
  std::vector<std::vector<int>> adjacency_list;

  explicit Tree(int n)
      : n(n) {
    adjacency_list.resize(n);
  }

  void AddEdge(int v, int u) {
    adjacency_list[v].push_back(u);
    adjacency_list[u].push_back(v);
  }

  std::string ToString() const {
    std::stringstream ss;
    ss << "Tree: n = " << n << "\n";
    ss << algo::utils::ToString(adjacency_list);
    return ss.str();
  };
};

}  // namespace algo::trees
