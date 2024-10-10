#pragma once

#include <string>
#include <sstream>

namespace algo::graphs {
template <typename T>
struct Cost {
  using CostType = T;
  explicit Cost(CostType cost)
      : cost(cost){};
  CostType cost;

  bool operator==(const Cost& that) const {
    return cost == that.cost;
  }

  std::string ToString() const {
    std::stringstream ss;
    ss << "Cost: " << cost;
    return ss.str();
  };
};
}  // namespace algo::graphs
