#pragma once

#include <string>
#include <sstream>

namespace algo::flows {
template <typename T>
struct Capacity {
  using CapacityType = T;
  explicit Capacity(CapacityType capacity)
      : capacity(capacity){};
  CapacityType capacity;

  bool operator==(const Capacity& that) const {
    return capacity == that.capacity;
  }

  std::string ToString() const {
    std::stringstream ss;
    ss << "Capacity: " << capacity;
    return ss.str();
  };
};
}  // namespace algo::flows
