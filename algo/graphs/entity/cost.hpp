#pragma once

#include <string>
#include <sstream>

namespace algo::graphs {
template <typename T>
struct Cost {
  explicit Cost(T cost)
      : cost(cost){};
  T cost;

  bool operator==(const Cost& that) {
    return cost == that.cost;
  }

  std::string ToString() const {
    std::stringstream ss;
    ss << "Cost: " << cost;
    return ss.str();
  };
};
}  // namespace algo::graphs
