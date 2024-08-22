#pragma once

#include <algo/utils/types/fundamentals.hpp>
#include <algo/flows/entities.hpp>
#include <algo/flows/details/dinitz.hpp>

namespace algo::flows {
std::pair<i64, std::pair<Flow, Cut>> MaxFlow(ResidualNetwork& network) {
  return details::Dinitz(network).MaxFlow();
}
}  // namespace algo::flows
