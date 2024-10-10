#pragma once

#include <algo/utils/types/fundamentals.hpp>
#include <algo/flows/entity/residual_network.hpp>
#include <algo/flows/details/dinitz.hpp>

namespace algo::flows {
template <typename Capacity>
auto MaxFlow(ResidualNetworkWith<Capacity>& network) {
  return details::Dinitz(network).MaxFlow();
}
}  // namespace algo::flows
