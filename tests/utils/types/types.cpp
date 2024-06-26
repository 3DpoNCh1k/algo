#include <algo/utils/types/128_t.hpp>
#include <iostream>

int main() {
  int T;
  std::cin >> T;
  for (int t = 0; t < T; ++t) {
    using algo::utils::i128;
    i128 a, b;
    std::cin >> a >> b;
    std::cout << (a + b) << std::endl;
  }
}
