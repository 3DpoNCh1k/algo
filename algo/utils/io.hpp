#pragma once

#include <iostream>

namespace algo::utils::io {

void UnsyncIO() {
  std::ios::sync_with_stdio(false);
  std::cin.tie(nullptr);
};

}  // namespace algo::utils::io
