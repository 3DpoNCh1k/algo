#pragma once

#include <cassert>
#include <vector>
#include "algo/utils/types/fundamentals.hpp"

namespace algo::flows {

struct Flow {
  i64 flow;
  std::vector<i64> edge_flow;
};
}  // namespace algo::flows
